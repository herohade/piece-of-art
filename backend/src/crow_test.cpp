#include <../include/crow_all.h>
#include <iostream>
#include <vector>
#include "../include/craftsman.h"
#include <nlohmann/json.hpp> // Include the correct JSON library
#include <string>
#include <algorithm>


// In-memory data store
std::vector<Craftsman> craftsmenData;
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
    std::vector<Craftsman> matchingCraftsmen;
    // Assuming craftsmenData is a vector of Craftsman objects
    for (const auto &craftsman : craftsmenData) {
        if (craftsman.getPostalcode() == postalCode) {
            matchingCraftsmen.push_back(craftsman);
        }
    }
    nlohmann::json response;
    response["craftsmen"] = nlohmann::json::array();
    // Check if any craftsmen were found
    if (!matchingCraftsmen.empty()) {
        for (const auto &craftsman : matchingCraftsmen) {
            nlohmann::json craftsmanObject;
            craftsmanObject["id"] = craftsman.getId();
            craftsmanObject["name"] = std::string(craftsman.getFirstName()) + " " + std::string(craftsman.getLastName());
            craftsmanObject["rankingScore"] = craftsman.getRank();
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
        res.end();
    }
    else {
        res.body = response.dump();
    }
    res.code = 200;
    res.set_header("Content-Type", "application/json");
    res.set_header("Access-Control-Allow-Origin", "http://localhost:5173");
    // Send the response
    res.end();
}


// Function to update a craftsman's profile information
void updateCraftsmanProfile(crow::response &res, int craftsmanId) {
    // Extract data from request body and update craftsman profile
    // For simplicity, just acknowledge the update here
    res.code = 200;
    res.body = "Craftsman profile updated successfully";
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
    craftsmenData.push_back(Craftsman(1, "John", "Smith", 74, "81927"));
    craftsmenData.push_back(Craftsman(2, "Jane", "Long", 85, "81927"));
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
    // Start the server
    app.port(3000).multithreaded().run();

    return 0;
}