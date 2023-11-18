#include <iostream>
#include <fstream>
#include "../include/json.hpp"
#include <cmath>
#include <map>

using namespace std;
using json = nlohmann::json;

double defaultDistance = 80000;

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
    string extension_group;
};

const double EARTH_RADIUS = 6371.0;


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
        info.extension_group = entry["postcode_extension_distance_group"];
        postcodeMap[entry["postcode"]] = info;
    }
    return postcodeMap;
}

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
        ServiceProvider provider = providersMap[entry["profile_id"]];
        provider.profile_picture_score = entry["profile_picture_score"];
        provider.profile_description_score = entry["profile_description_score"];
    }

    return providersMap;
}

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    double dist = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2)) * EARTH_RADIUS;
    return dist * 1000;
}

double calculateRank(double distance, const ServiceProvider& provider) {
    double distanceScore = 1.0 - (distance / defaultDistance);
    double distanceWeight = (distance > defaultDistance) ? 0.01 : 0.15;
    double profileScore = 0.4 * provider.profile_picture_score + 0.6 * provider.profile_description_score;

    double rank = distanceWeight * distanceScore + (1 - distanceWeight) * profileScore;
    return rank;
}

vector<ServiceProvider> getTopRankedProviders(string customerPostcode, const unordered_map<string, PostcodeInfo>& postcodes, const unordered_map<int, ServiceProvider>& all_providers) {
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
        ServiceProvider curr = provider.second;
        double distance = calculateDistance(curr.lat, curr.lon, info.lat, info.lon);
        if (distance <= curr.max_driving_distance + delta_distance) {
            providers.push_back(make_pair(curr, calculateRank(distance, curr)));
        }
    }

    sort(providers.begin(), providers.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });

    vector<ServiceProvider> sortedProviders;

    for (const auto& pair : providers) {
        const ServiceProvider& serviceProvider = pair.first;
        sortedProviders.push_back(serviceProvider);
    }

    return sortedProviders;
}


int main() {
    unordered_map<string, PostcodeInfo> postcodes = readPostcodes("data/postcode.json");
    unordered_map<int, ServiceProvider> all_providers = readProviders("data/service_provider_profile.json", "data/quality_factor_score.json");
    cout << "nr of postcodes: " << postcodes.size() << "\n";
    cout << "nr of providers: " << all_providers.size() << "\n";

    string postcode;
    cin >> postcode;

    vector<ServiceProvider> ans = getTopRankedProviders(postcode, postcodes, all_providers);

    for (int i = 0; i < 20; i++) {
        cout << ans[i].first_name << " " << ans[i].last_name << "\n";
    }

    return 0;
}