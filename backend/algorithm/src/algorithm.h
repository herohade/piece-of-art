// craftsman_ranking.h

#ifndef CRAFTSMAN_RANKING_H
#define CRAFTSMAN_RANKING_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <map>
#include "../../include/craftsman.h"
#include "../include/json.hpp"
#include "../../adaptive-radix-tree/include/art.hpp"

const double defaultDistance = 80000;
const double EARTH_RADIUS = 6371.0;

struct PostcodeInfo {
    double lon;
    double lat;
    std::string extension_group;
};

std::unordered_map<std::string, PostcodeInfo> readPostcodes(std::string filename);

std::unordered_map<int, Craftsman> readCraftsmen(std::string profile_filename, std::string score_filename);

double calculateDistance(double lat1, double lon1, double lat2, double lon2);

double calculateRank(double distance, const Craftsman& craftsman);

std::vector<std::pair<Craftsman, double>> getTopNRankedCraftsmen(
    std::string customerPostcode,
    const std::unordered_map<std::string, PostcodeInfo>& postcodes,
    const std::unordered_map<int, Craftsman>& all_craftsmen,
    int n
);

std::unordered_map<std::string, std::vector<std::pair<Craftsman, double>>> getAllRankings(
    std::unordered_map<std::string, PostcodeInfo>& postcodes,
    std::unordered_map<int, Craftsman>& craftsmen
);

art::art<std::vector<std::pair<Craftsman, double>>> fill_the_tree(int n, std::unordered_map<std::string, PostcodeInfo>& postcodes, std::unordered_map<int, Craftsman>& craftsmen);

#endif  // CRAFTSMAN_RANKING_H
