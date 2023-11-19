
#include <unordered_map>
#include <vector>
#include <string>
#include "../include/craftsman.h"  
#include "../include/json.hpp"
#include <iostream>

using namespace std;
using json = nlohmann::json;



const double defaultDistance = 80000;
const double EARTH_RADIUS = 6371.0;

struct PostcodeInfo {
    double lon;
    double lat;
    std::string extension_group;
};



// Calculates distance in meters between two coordinates
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    return 1000 * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2)) * EARTH_RADIUS;
}

// Calculates the rank of a craftsman given the certain distance from the post code
double calculateRank(double distance, const Craftsman& craftsman) {
    double distanceScore = 1.0 - (distance / defaultDistance);
    double distanceWeight = (distance > defaultDistance) ? 0.01 : 0.15;
    double profileScore = 0.4 * craftsman.getProfilePictureScore() + 0.6 * craftsman.getProfileDescriptionScore();

    return distanceWeight * distanceScore + (1 - distanceWeight) * profileScore;
}

// Returns a sorted vector of service craftsmans according to their ranks
vector<pair<Craftsman, double>> getTopNRankedCraftsmans(string customerPostcode, const unordered_map<string, PostcodeInfo>& postcodes, const unordered_map<int, Craftsman>& all_craftsmans, int n) {
    auto it = postcodes.find(customerPostcode);
    if (it == postcodes.end()) return {};
    PostcodeInfo info = it->second;
    
    int delta_distance = 0;
    if (info.extension_group == "group_b") {
        delta_distance = 2000;
    } else if (info.extension_group == "group_c") {
        delta_distance = 5000;
    }

    vector<pair<Craftsman, double>> craftsmans;

    short cnt6 = 0;
    short cnt5 = 0;
    short cnt4 = 0;

    for (const auto& craftsman : all_craftsmans) {
        const Craftsman& curr = craftsman.second;
        
        if (cnt4 >= n && (curr.getProfileDescriptionScore() + curr.getProfilePictureScore() < 4)) continue;
        if (cnt5 >= n && (curr.getProfileDescriptionScore() + curr.getProfilePictureScore() < 5)) continue;
        if (cnt6 >= n && (curr.getProfileDescriptionScore() + curr.getProfilePictureScore() < 6)) continue;
        
        double distance = calculateDistance(curr.getLat(), curr.getLon(), info.lat, info.lon);
        
        if (distance <= curr.getMaxDrivingDistance() + delta_distance) {
            if (cnt6 < n && (curr.getProfileDescriptionScore() + curr.getProfilePictureScore() >= 6)) cnt6++;
            if (cnt5 < n && (curr.getProfileDescriptionScore() + curr.getProfilePictureScore() >= 5)) cnt5++;
            if (cnt4 < n && (curr.getProfileDescriptionScore() + curr.getProfilePictureScore() >= 4)) cnt4++;            
            craftsmans.push_back({curr, calculateRank(distance, curr)});
        }
    }

    sort(craftsmans.begin(), craftsmans.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; 
    });
    
    return craftsmans;
}

// Returns a mapping of each postcode to the available craftsmans with their rank
unordered_map<string, vector<pair<Craftsman, double>>> getAllRankings(unordered_map<string, PostcodeInfo>& postcodes, unordered_map<int, Craftsman>& craftsmans) {
    unordered_map<string, vector<pair<Craftsman, double>>> sortedcraftsmans;
    
    for (auto it = postcodes.begin(); it != postcodes.end(); it++) {
        sortedcraftsmans.insert({it->first, getTopNRankedCraftsmans(it->first, postcodes, craftsmans, 20)});
    }

    return sortedcraftsmans;
}
