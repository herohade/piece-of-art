// MyResource.hpp

#ifndef MY_RESOURCE_HPP
#define MY_RESOURCE_HPP

#include <iostream>

class MyResource {
public:
    // Default constructor
    MyResource() {
        std::cout << "MyResource Default Constructor\n";
    }

    // Constructor with a custom message
    explicit MyResource(const std::string& message) : message_(message) {
        std::cout << "MyResource Constructor: " << message_ << "\n";
    }

    // Destructor
    ~MyResource() {
        std::cout << "MyResource Destructor: " << message_ << "\n";
    }

    // Getter for the message
    const std::string& getMessage() const {
        return message_;
    }

private:
    std::string message_;
};

#endif  // MY_RESOURCE_HPP
