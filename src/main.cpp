#include <iostream>
#include "geocoder.h"

int main() {
    // Note: The main function from the previous response can be placed here.
    // Ensure the path to the CSV file is correct, e.g., "data/locations.csv"
    std::vector<Location> locations = loadLocations("data/locations.csv");
    if (locations.empty()) {
        std::cerr << "Could not load location data." << std::endl;
        return 1;
    }

    KDTree geocoder(locations);

    Location query = {"", 48.8566, 2.3522}; // Paris
    Location nearest = geocoder.findNearestNeighbor(query);

    std::cout << "The nearest location to (" << query.latitude << ", " << query.longitude << ") is: " << nearest.name << std::endl;

    return 0;
}