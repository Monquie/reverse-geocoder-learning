#ifndef GEOCODER_H
#define GEOCODER_H

#include <string>
#include <vector>

struct Location {
    std::string name;
    double latitude;
    double longitude;
};

// Function to load data from a CSV file
std::vector<Location> loadLocations(const std::string& filename);

// The KDTree class for nearest neighbor search
class KDTree {
public:
    KDTree(std::vector<Location>& locations);
    ~KDTree();
    Location findNearestNeighbor(const Location& query);

private:
    struct KDNode {
        Location location;
        KDNode* left;
        KDNode* right;
    };

    KDNode* root;
    KDNode* buildTree(std::vector<Location>& locations, int depth);
    void findNearestNeighbor(KDNode* node, const Location& query, int depth, Location& nearest, double& min_dist);
    void destroyTree(KDNode* node);
};

// Haversine distance calculation
double haversineDistance(const Location& loc1, const Location& loc2);

#endif // GEOCODER_H