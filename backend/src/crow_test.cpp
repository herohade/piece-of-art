#include "../include/crow_all.h"
#include <iostream>
#include <vector>
#include "../include/craftsman.h"
#include "../algorithm/include/json.hpp"
#include "../algorithm/src/algorithm.h"
#include <string>
#include <algorithm>


// In-memory data store
std::vector<Craftsman> craftsmenData;
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

    // Perform your logic to filter craftsmen based on postal code
    // For simplicity, just return all craftsmen here
    std::vector<std::pair<Craftsman, double>> matchingCraftsmen = art_tree.get(postalCode);
    nlohmann::json response;
    response["craftsmen"] = nlohmann::json::array();
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
        response["error"] = "No craftsmen found for the provided postal code.";
        res.body = response.dump();
        res.code = 400;
        res.end();
    }
    if (req.url_params.get("maximum") != nullptr) {
        int limit = std::stoi(req.url_params.get("maximum"));
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
    Craftsman craftsman;
    // Get the Craftsman object based on craftsmanId (you need to implement this)
    if (craftsmanId % 2) {
        craftsman = craftsmenData[0];
    }
    else {
        craftsman = craftsmenData[1];
    }
    // Check if at least one attribute is defined in the request
    if (!jsonRequest["maxDrivingDistance"] &&
        !jsonRequest["profilePictureScore"] &&
        !jsonRequest["profileDescriptionScore"]) {
        res.code = 400; // Bad Request
        res.body = "At least one attribute should be defined in the request";
        res.set_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        res.end();
        return;
    }
    // Update attributes if they are defined in the request
    if (jsonRequest["maxDrivingDistance"]) {
        craftsman.setMaxDrivingDistance(jsonRequest["maxDrivingDistance"].d());
    }

    if (jsonRequest["profilePictureScore"]) {
        craftsman.setProfilePictureScore( jsonRequest["profilePictureScore"].d());
    }

    if (jsonRequest["profileDescriptionScore"]) {
        craftsman.setProfileDescriptionScore(jsonRequest["profileDescriptionScore"].d());
    }
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
    std::unordered_map<int, Craftsman> craftsmenData = readCraftsmen("data/service_provider_profile.json", "data/quality_factor_score.json");
    std::unordered_map<std::string, PostcodeInfo> postcodeData = readPostcodes("data/postcode.json");
    art::art<std::vector<std::pair<Craftsman, double>>> art_tree = fill_the_tree(20, postcodeData, craftsmenData);
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