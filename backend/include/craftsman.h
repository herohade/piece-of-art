#ifndef CRAFTSMAN_HPP
#define CRAFTSMAN_HPP

#include <iostream>
#include <string>
#include <array>

class Craftsman {
public:
    // Default constructor
    Craftsman()
            : id_(0),
              firstname_(""),
              lastname_(""),
              city_(""),
              street_(""),
              house_number_(""),
              lon_(0.0),
              lat_(0.0),
              max_driving_distance_(0.0),
              profile_picture_score_(0.0),
              profile_description_score_(0.0) {}

    // Parameterized constructor
    Craftsman(int id,
              const std::string& firstname,
              const std::string& lastname,
              const std::string& city,
              const std::string& street,
              const std::string& house_number,
              double lon,
              double lat,
              double max_driving_distance,
              double profile_picture_score,
              double profile_description_score)
            : id_(id),
              firstname_(firstname),
              lastname_(lastname),
              city_(city),
              street_(street),
              house_number_(house_number),
              lon_(lon),
              lat_(lat),
              max_driving_distance_(max_driving_distance),
              profile_picture_score_(profile_picture_score),
              profile_description_score_(profile_description_score) {}

    // Getter for id
    int getId() const {
        return id_;
    }

    // Setter for id
    void setId(int id) {
        id_ = id;
    }

    // Getter for name
    const std::string& getFirstName() const {
        return firstname_;
    }

    // Setter for name
    void setFirstName(const std::string& firstname) {
        firstname_ = firstname;
    }

    // Getter for last name
    const std::string& getLastName() const {
        return lastname_;
    }

    // Setter for last name
    void setLastName(const std::string& lastname) {
        lastname_ = lastname;
    }

    // Getter for city
    const std::string& getCity() const {
        return city_;
    }

    // Setter for city
    void setCity(const std::string& city) {
        city_ = city;
    }

    // Getter for street
    const std::string& getStreet() const {
        return street_;
    }

    // Setter for street
    void setStreet(const std::string& street) {
        street_ = street;
    }

    // Getter for house number
    const std::string& getHouseNumber() const {
        return house_number_;
    }

    // Setter for house number
    void setHouseNumber(const std::string& house_number) {
        house_number_ = house_number;
    }

    // Getter for longitude
    double getLon() const {
        return lon_;
    }

    // Setter for longitude
    void setLon(double lon) {
        lon_ = lon;
    }

    // Getter for latitude
    double getLat() const {
        return lat_;
    }

    // Setter for latitude
    void setLat(double lat) {
        lat_ = lat;
    }

    // Getter for max driving distance
    double getMaxDrivingDistance() const {
        return max_driving_distance_;
    }

    // Setter for max driving distance
    void setMaxDrivingDistance(double max_driving_distance) {
        max_driving_distance_ = max_driving_distance;
    }

    // Getter for profile picture score
    double getProfilePictureScore() const {
        return profile_picture_score_;
    }

    // Setter for profile picture score
    void setProfilePictureScore(double profile_picture_score) {
        profile_picture_score_ = profile_picture_score;
    }

    // Getter for profile description score
    double getProfileDescriptionScore() const {
        return profile_description_score_;
    }

    // Setter for profile description score
    void setProfileDescriptionScore(double profile_description_score) {
        profile_description_score_ = profile_description_score;
    }

private:
    int id_;
    std::string firstname_;
    std::string lastname_;
    int rank_;
    std::string postalcode_;
    std::string city_;
    std::string street_;
    std::string house_number_;
    double lon_;
    double lat_;
    double max_driving_distance_;
    double profile_picture_score_;
    double profile_description_score_;
};

#endif  // CRAFTSMAN_HPP
