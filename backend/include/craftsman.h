#ifndef CRAFTSMAN_HPP
#define CRAFTSMAN_HPP

#include <iostream>
#include <string>
#include <array>

class Craftsman {
public:
    // Default constructor
    Craftsman() : id_(0), name_(""), rank_(0) {}

    // Parameterized constructor
    Craftsman(int id, const std::string& name, int rank)
            : id_(id), name_(name), rank_(rank) {}

    // Getter for id
    int getId() const {
        return id_;
    }

    // Getter for name
    const std::string& getName() const {
        return name_;
    }

    // Getter for rank
    int getRank() const {
        return rank_;
    }

private:
    int id_;
    std::string name_;
    int rank_;
};

#endif  // CRAFTSMAN_HPP
