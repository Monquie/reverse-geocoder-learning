#include "geocoder.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iostream>
#include <vector>
#include <string>

const double EARTH_RADIUS_KM = 6371.0;
const double PI = 3.14159265358979323846;

double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

double haversineDistance(const Location& loc1, const Location& loc2) {
    double lat1 = toRadians(loc1.latitude);
    double lon1 = toRadians(loc1.longitude);
    double lat2 = toRadians(loc2.latitude);
    double lon2 = toRadians(loc2.longitude);

    double d_lat = lat2 - lat1;
    double d_lon = lon2 - lon1;

    double a = std::sin(d_lat / 2.0) * std::sin(d_lat / 2.0) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(d_lon / 2.0) * std::sin(d_lon / 2.0);
    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    return EARTH_RADIUS_KM * c;
}

std::vector<Location> loadLocations(const std::string& filename) {
    std::vector<Location> locations;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return locations;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, lat_str, lon_str;
        if (std::getline(ss, name, ',') &&
            std::getline(ss, lat_str, ',') &&
            std::getline(ss, lon_str, ',')) {
            try {
                locations.push_back({name, std::stod(lat_str), std::stod(lon_str)});
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << " -> " << e.what() << std::endl;
            }
        }
    }
    return locations;
}

// KDTree implementation
KDTree::KDTree(std::vector<Location>& locations) {
    root = buildTree(locations, 0);
}

KDTree::~KDTree() {
    destroyTree(root);
}

Location KDTree::findNearestNeighbor(const Location& query) {
    Location nearest = root->location;
    double min_dist = haversineDistance(query, nearest);
    findNearestNeighbor(root, query, 0, nearest, min_dist);
    return nearest;
}

KDTree::KDNode* KDTree::buildTree(std::vector<Location>& locations, int depth) {
    if (locations.empty()) {
        return nullptr;
    }

    int axis = depth % 2; // 0 for latitude, 1 for longitude
    std::sort(locations.begin(), locations.end(), [axis](const Location& a, const Location& b) {
        return (axis == 0) ? a.latitude < b.latitude : a.longitude < b.longitude;
    });

    size_t median_index = locations.size() / 2;
    KDNode* node = new KDNode{locations[median_index], nullptr, nullptr};
    
    std::vector<Location> left_subset(locations.begin(), locations.begin() + median_index);
    std::vector<Location> right_subset(locations.begin() + median_index + 1, locations.end());

    node->left = buildTree(left_subset, depth + 1);
    node->right = buildTree(right_subset, depth + 1);

    return node;
}

void KDTree::findNearestNeighbor(KDNode* node, const Location& query, int depth, Location& nearest, double& min_dist) {
    if (!node) {
        return;
    }

    double current_dist = haversineDistance(query, node->location);
    if (current_dist < min_dist) {
        min_dist = current_dist;
        nearest = node->location;
    }

    int axis = depth % 2;
    double query_coord = (axis == 0) ? query.latitude : query.longitude;
    double node_coord = (axis == 0) ? node->location.latitude : node->location.longitude;

    KDNode* first_branch = (query_coord < node_coord) ? node->left : node->right;
    KDNode* second_branch = (query_coord < node_coord) ? node->right : node->left;

    findNearestNeighbor(first_branch, query, depth + 1, nearest, min_dist);

    // Pruning step: check if the other side could contain a closer point
    double axis_diff_km = (axis == 0) ? 
        haversineDistance({"", query.latitude, query.longitude}, {"", node->location.latitude, query.longitude}) :
        haversineDistance({"", query.latitude, query.longitude}, {"", query.latitude, node->location.longitude});

    if (axis_diff_km < min_dist) {
        findNearestNeighbor(second_branch, query, depth + 1, nearest, min_dist);
    }
}

void KDTree::destroyTree(KDNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}