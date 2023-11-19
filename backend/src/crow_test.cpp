#include "../include/crow_all.h"
#include <iostream>
#include <vector>
#include "../include/craftsman.h"
#include "../include/json.hpp"
#include <string>
#include <algorithm>
#include <map>
#include "../adaptive-radix-tree/include/art.hpp"

using namespace std;

struct PostcodeInfo {
    double lon;
    double lat;
    std::string extension_group;
};

const double defaultDistance = 80000;
const double EARTH_RADIUS = 6371.0;

unordered_map<string, PostcodeInfo> readPostcodes(string filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return {};
    }

    nlohmann::json data;
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


// Returns a map of craftsmans from service craftsman and quality factor files
unordered_map<int, Craftsman> readCraftsmen(string profile_filename, string score_filename) {
    ifstream file(profile_filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return {};
    }

    nlohmann::json data;
    file >> data;
    file.close();

    unordered_map<int, Craftsman> craftmansMap;

    for (const auto& entry : data) {
        Craftsman craftsman = Craftsman(entry["id"], entry["first_name"], entry["last_name"], entry["city"], entry["street"], entry["house_number"],
                            entry["lon"], entry["lat"], entry["max_driving_distance"], 0.0, 0.0);
        craftmansMap.insert({entry["id"], craftsman});
    }

    ifstream scoreFile(score_filename);

    if (!scoreFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return {};
    }

    scoreFile >> data;
    scoreFile.close();

    for (const auto& entry : data) {
        craftmansMap[entry["profile_id"]].setProfilePictureScore(entry["profile_picture_score"]);
        craftmansMap[entry["profile_id"]].setProfileDescriptionScore(entry["profile_description_score"]);
    }

    return craftmansMap;
}

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

art::art<std::vector<std::pair<Craftsman, double>>> fill_the_tree(int n, unordered_map<std::string, PostcodeInfo>& postcodes, std::unordered_map<int, Craftsman>& all_craftsmen) {
    art::art<std::vector<pair<Craftsman, double>>> tree;
    for (const auto& postcode : postcodes) {
        vector<pair<Craftsman, double>> craftsmen = getTopNRankedCraftsmans(postcode.first, postcodes, all_craftsmen, n);
        tree.set(postcode.first.c_str(), craftsmen);
    }
    return tree;
}


// In-memory data store
std::unordered_map<int, Craftsman> craftsmenData;
std::unordered_map<std::string, PostcodeInfo> postcodeData;
art::art<std::vector<std::pair<Craftsman, double>>> art_tree;
// Function to retrieve craftsmen based on postal code
void getCraftsmen(crow::response &res, const crow::request &req) {
    // Extract postal code from query parameter
    auto postalCode = req.url_params.get("postalcode");
    // Check if postal code is provided
    if (postalCode == nullptr || *postalCode == '\0') {
        res.code = 400;
        res.body = "Postal code is required.";
        res.set_header("Content-Type", "text/plain");
        res.end();
        return;
    }
    nlohmann::json response;
    std::vector<std::pair<Craftsman, double>> matchingCraftsmen;
    response["craftsmen"] = nlohmann::json::array();
    if (req.url_params.get("maximum") != nullptr) {
        int limit = std::stoi(req.url_params.get("maximum"));
        if (limit <= 20) matchingCraftsmen = art_tree.get(postalCode);
        else {
            art_tree = fill_the_tree(limit, postcodeData, craftsmenData);
        }
        nlohmann::json newResponse;
        newResponse["craftsmen"] = nlohmann::json::array();
        limit = fmin(limit, response["craftsmen"].size());
        for (int i = 0; i < limit; ++i) {
            newResponse["craftsmen"][i] = response["craftsmen"][i];
        }
        res.body = newResponse.dump();
    }
    else {
        res.body = response.dump();
    }
    // Perform your logic to filter craftsmen based on postal code
    // For simplicity, just return all craftsmen here
    // Check if any craftsmen were found
    if (!matchingCraftsmen.empty()) {
        for (const auto &craftsman : matchingCraftsmen) {
            nlohmann::json craftsmanObject;
            craftsmanObject["id"] = craftsman.first.getId();
            craftsmanObject["name"] = std::string(craftsman.first.getFirstName()) + " " + std::string(craftsman.first.getLastName());
            craftsmanObject["rankingScore"] = craftsman.second;
            response["craftsmen"].push_back(craftsmanObject);
        }
    } else {
        // No craftsmen found
        res.body = response.dump();
        res.code = 200;
        res.end();
        return;
    }
    res.code = 200;
    res.add_header("Content-Type", "application/json");
    res.add_header("Access-Control-Allow-Origin", "*");
    // Send the response
    res.end();
}


// Function to handle PATCH request
void updateCraftsman(crow::response &res, const crow::request &req, int craftsmanId) {
    // Parse JSON from request body
    auto jsonRequest = crow::json::load(req.body);
    res.add_header("Content-Type", "application/json");
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, PATCH, DELETE");
    if (!jsonRequest) {
        res.code = 400; // Bad Request
        res.body = "Invalid JSON in request body";
        res.end();
        return;
    }
    // Get the Craftsman object based on craftsmanId (you need to implement this)
    Craftsman craftsman = craftsmenData[craftsmanId];
    // Check if at least one attribute is defined in the request
    if ((!jsonRequest["maxDrivingDistance"] || jsonRequest["maxDrivingDistance"].t()  == crow::json::type::Null) &&
            (!jsonRequest["profilePictureScore"] || jsonRequest["profilePictureScore"].t() == crow::json::type::Null) &&
            (!jsonRequest["profileDescriptionScore"] || jsonRequest["profileDescriptionScore"].t() == crow::json::type::Null)) {
        res.code = 400; // Bad Request:
        res.body = "At least one attribute should be defined in the request";
        res.set_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        res.end();
        return;
    }
    // Update attributes if they are defined in the request
    if (jsonRequest["maxDrivingDistance"] && jsonRequest["maxDrivingDistance"].t() != crow::json::type::Null) {
        craftsman.setMaxDrivingDistance(jsonRequest["maxDrivingDistance"].d());
    }

    if (jsonRequest["profilePictureScore"] && jsonRequest["profilePictureScore"].t() != crow::json::type::Null) {
        craftsman.setProfilePictureScore( jsonRequest["profilePictureScore"].d());
    }

    if (jsonRequest["profileDescriptionScore"] && jsonRequest["profileDescriptionScore"].t() != crow::json::type::Null) {
        craftsman.setProfileDescriptionScore(jsonRequest["profileDescriptionScore"].d());
    }
    art_tree = fill_the_tree(20, postcodeData, craftsmenData);
    // Prepare response
    nlohmann::json updatedObject;
    updatedObject["maxDrivingDistance"] = craftsman.getMaxDrivingDistance();
    updatedObject["profilePictureScore"] = craftsman.getProfilePictureScore();
    updatedObject["profileDescriptionScore"] = craftsman.getProfileDescriptionScore();
    nlohmann::json jsonResponse;
    jsonResponse["id"] = craftsman.getId();
    jsonResponse["updated"] = updatedObject;
    // Set response code and body
    res.code = 200; // OK
    res.set_header("Content-Type", "application/json");
    res.add_header("Access-Control-Allow-Origin", "*");
    res.body = jsonResponse.dump();
    std::cout << res.body << std::endl;
    res.end();
}

// Function to expose api json
void getEndpoints(crow::response &res) {
    try {
        // Convert YAML to JSON
        res.body = "{\"openapi\":\"3.0.0\",\"info\":{\"title\":\"Craftsmen Service API\",\"version\":\"1.0.0\"},\"servers\":[{\"url\":\"http://localhost:3000\"}],\"paths\":{\"/craftsmen\":{\"get\":{\"summary\":\"Retrieves a list of craftsmen based on postal code\",\"parameters\":[{\"in\":\"query\",\"name\":\"postalcode\",\"schema\":{\"type\":\"string\"},\"required\":true,\"description\":\"Postal code to filter craftsmen\"},{\"in\":\"query\",\"name\":\"maximum\",\"schema\":{\"type\":\"number\",\"required\":false,\"description\":\"Maximum craftsmen to attach to response\"}}],\"responses\":{\"200\":{\"description\":\"List of craftsmen\",\"content\":{\"application/json\":{\"schema\":{\"$ref\":\"#/components/schemas/Response\"}}}}}}},\"/craftman/{craftman_id}\":{\"patch\":{\"summary\":\"Updates a craftsman's profile information\",\"parameters\":[{\"in\":\"path\",\"name\":\"craftman_id\",\"schema\":{\"type\":\"integer\"},\"required\":true,\"description\":\"Unique ID of the craftsman\"}],\"requestBody\":{\"required\":true,\"content\":{\"application/json\":{\"schema\":{\"$ref\":\"#/components/schemas/PatchRequest\"}}}},\"responses\":{\"200\":{\"description\":\"Craftsman updated successfully\",\"content\":{\"application/json\":{\"schema\":{\"$ref\":\"#/components/schemas/PatchResponse\"}}}}}}}},\"components\":{\"schemas\":{\"Craftsman\":{\"type\":\"object\",\"properties\":{\"id\":{\"type\":\"integer\"},\"name\":{\"type\":\"string\"},\"rankingScore\":{\"type\":\"number\"}}},\"Response\":{\"type\":\"object\",\"properties\":{\"craftsmen\":{\"type\":\"array\",\"items\":{\"$ref\":\"#/components/schemas/Craftsman\"}}}},\"PatchRequest\":{\"type\":\"object\",\"properties\":{\"maxDrivingDistance\":{\"type\":\"number\",\"nullable\":true},\"profilePictureScore\":{\"type\":\"number\",\"nullable\":true},\"profileDescriptionScore\":{\"type\":\"number\",\"nullable\":true}}},\"PatchResponse\":{\"type\":\"object\",\"properties\":{\"id\":{\"type\":\"integer\"},\"updated\":{\"type\":\"object\",\"properties\":{\"maxDrivingDistance\":{\"type\":\"number\"},\"profilePictureScore\":{\"type\":\"number\"},\"profileDescriptionScore\":{\"type\":\"number\"}}}}}}}}";
        res.code = 200;
        res.end();
    } catch (const std::exception &e) {
        // Handle YAML parsing errors
        res.code = 500;
        res.body = "Error parsing YAML: " + std::string(e.what());
        res.end();
    }

}


int main() {
    craftsmenData = readCraftsmen("data/service_provider_profile.json", "data/quality_factor_score.json");
    postcodeData = readPostcodes("data/postcode.json");
    art_tree = fill_the_tree(20, postcodeData, craftsmenData);
    // Define route for retrieving craftsmen
    crow::SimpleApp app;

    // Define route for retrieving craftsmen
    CROW_ROUTE(app, "/craftsmen")
            .methods("GET"_method)
                    ([&](const crow::request &req, crow::response &res) {
                        getCraftsmen(res, req);
                    });

    CROW_ROUTE(app, "/api-json")
            .methods("GET"_method)
                    ([&](const crow::request &req, crow::response &res) {
                        getEndpoints(res);
                    });

    CROW_ROUTE(app, "/craftman/<int>")
            .methods("PATCH"_method)
                    ([&](const crow::request &req, crow::response &res, int craftsmanId) {
                        updateCraftsman(res, req, craftsmanId);
                    });

    // Start the server
    app.port(3000).multithreaded().run();

    return 0;
}