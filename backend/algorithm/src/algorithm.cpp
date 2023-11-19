#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <map>

#include "../include/json.hpp"

using namespace std;
using json = nlohmann::json;


const double defaultDistance = 80000;
const double EARTH_RADIUS = 6371.0;

struct ServiceProvider {
    int id;
    string first_name;
    string last_name;
    string city;
    string street;
    string house_number;
    double lon;
    double lat;
    double max_driving_distance;
    double profile_picture_score;
    double profile_description_score; 
};

struct PostcodeInfo {
    double lon;
    double lat;
    string created_at;
    string updated_at;
    string extension_group;
};

//  Returns a map of postcodes from a json file
unordered_map<string, PostcodeInfo> readPostcodes(string filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return {};
    }

    json data;
    file >> data;
    file.close();

    unordered_map<string, PostcodeInfo> postcodeMap;

    for (const auto& entry : data) {
        PostcodeInfo info;
        info.lon = entry["lon"];
        info.lat = entry["lat"];
        info.created_at = entry["created_at"];
        info.updated_at = entry["updated_at"];
        info.extension_group = entry["postcode_extension_distance_group"];
        postcodeMap[entry["postcode"]] = info;
    }
    return postcodeMap;
}


// Returns a map of providers from service provider and quality factor files
unordered_map<int, ServiceProvider> readProviders(string profile_filename, string score_filename) {
    ifstream file(profile_filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return {};
    }

    json data;
    file >> data;
    file.close();

    unordered_map<int, ServiceProvider> providersMap;

    for (const auto& entry : data) {
        ServiceProvider provider;
        provider.id = entry["id"];
        provider.first_name = entry["first_name"];
        provider.last_name = entry["last_name"];
        provider.city = entry["city"];
        provider.street = entry["street"];
        provider.house_number = entry["house_number"];
        provider.lon = entry["lon"];
        provider.lat = entry["lat"];
        provider.max_driving_distance = entry["max_driving_distance"];
        providersMap[entry["id"]] = provider;
    }

    ifstream scoreFile(score_filename);

    if (!scoreFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return {};
    }

    scoreFile >> data;
    scoreFile.close();

    for (const auto& entry : data) {
        providersMap[entry["profile_id"]].profile_picture_score = entry["profile_picture_score"];
        providersMap[entry["profile_id"]].profile_description_score = entry["profile_description_score"];
    }

    return providersMap;
}

// Calculates distance in meters between two coordinates
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    return 1000 * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2)) * EARTH_RADIUS;
}

// Calculates the rank of a provider given the certain distance from the post code
double calculateRank(double distance, const ServiceProvider& provider) {
    double distanceScore = 1.0 - (distance / defaultDistance);
    double distanceWeight = (distance > defaultDistance) ? 0.01 : 0.15;
    double profileScore = 0.4 * provider.profile_picture_score + 0.6 * provider.profile_description_score;

    return distanceWeight * distanceScore + (1 - distanceWeight) * profileScore;
}

// Returns a sorted vector of service providers according to their ranks
vector<pair<ServiceProvider, double>> getTopRankedProviders(string customerPostcode, const unordered_map<string, PostcodeInfo>& postcodes, const unordered_map<int, ServiceProvider>& all_providers) {
    auto it = postcodes.find(customerPostcode);
    if (it == postcodes.end()) return {};
    PostcodeInfo info = it->second;
    
    int delta_distance = 0;
    if (info.extension_group == "group_b") {
        delta_distance = 2000;
    } else if (info.extension_group == "group_c") {
        delta_distance = 5000;
    }

    vector<pair<ServiceProvider, double>> providers;

    for (const auto& provider : all_providers) {
        const ServiceProvider& curr = provider.second;
        double distance = calculateDistance(curr.lat, curr.lon, info.lat, info.lon);
        if (distance <= curr.max_driving_distance + delta_distance) {
            providers.push_back({curr, calculateRank(distance, curr)});
        }
    }


    sort(providers.begin(), providers.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });

 /*   vector<ServiceProvider> sortedProviders;
    for (const auto& pair : providers) {
        sortedProviders.push_back(pair.first);
    }

    return sortedProviders;
*/
    return providers;
}

// Returns a mapping of each postcode to all the available providers with their rank
unordered_map<string, vector<pair<ServiceProvider, double>>> getAllRankings(unordered_map<string, PostcodeInfo>& postcodes, unordered_map<int, ServiceProvider>& providers) {
    unordered_map<string, vector<pair<ServiceProvider, double>>> sortedProviders;
    
    for (auto it = postcodes.begin(); it != postcodes.end(); it++) {
        sortedProviders.insert({it->first, getTopRankedProviders(it->first, postcodes, providers)});
    }

    return sortedProviders;
}


int main() {
    unordered_map<string, PostcodeInfo> postcodes = readPostcodes("data/postcode.json");
    unordered_map<int, ServiceProvider> all_providers = readProviders("data/service_provider_profile.json", "data/quality_factor_score.json");

    string postcode;
    cin >> postcode;

    vector<pair<ServiceProvider, double>> lol = getTopRankedProviders(postcode, postcodes, all_providers);


    for (int i = 0; i < 20; i++) {
        cout << lol[i].first.id << " " << lol[i].second << "\n";
    }

    auto start = chrono::high_resolution_clock::now();
    unordered_map<string, vector<pair<ServiceProvider, double>>> ans = getAllRankings(postcodes, all_providers);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Execution Time: " << duration << " ms\n";

    return 0;
}