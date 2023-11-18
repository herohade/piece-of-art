#ifndef CRAFTSMAN_HPP
#define CRAFTSMAN_HPP

#include <iostream>
#include <string>
#include <array>

class Craftsman {
public:
    // Default constructor
    Craftsman() : id_(0), firstname_(""), lastname_(""), rank_(0), postalcode_("") {}

    // Parameterized constructor
    Craftsman(int id, const std::string& firstname, const std::string& lastname, int rank, const std::string& postalcode)
            : id_(id), firstname_(firstname),lastname_(lastname), rank_(rank), postalcode_(postalcode) {}

    // Getter for id
    int getId() const {
        return id_;
    }

    // Getter for name
    const std::string& getFirstName() const {
        return firstname_;
    }

    // Getter for name
    const std::string& getLastName() const {
        return lastname_;
    }

    // Getter for rank
    int getRank() const {
        return rank_;
    }

    // Getter for postalcode
    const std::string& getPostalcode() const {
        return postalcode_;
    }

private:
    int id_;
    std::string firstname_;
    std::string lastname_;
    int rank_;
    std::string postalcode_;
};

#endif  // CRAFTSMAN_HPP
