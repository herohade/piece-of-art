#include "../include/craftsman.h"
#include <art.hpp>

int main() {
    // Create an instance of the tree with MyData as the value type
    art::art<std::array<Craftsman, 3>> m;  // Example with an array of size 3

    // Set a key-value pair in the tree
    m.set("k", {Craftsman(1, "John", 85), Craftsman(2, "Alice", 92), Craftsman(3, "Bob", 78)});

    // Get the value associated with the key
    std::array<Craftsman, 3> data = m.get("k");

    // Display the data
    for (const auto& item : data) {
        std::cout << "ID: " << item.getId()
                  << ", Name: " << item.getName()
                  << ", Rank: " << item.getRank() << "\n";
    }

    // Delete the key from the tree
    m.del("k");

    return 0;
}
