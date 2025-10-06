# Geocoder - K-D Tree Nearest Neighbor Search

A high-performance C++ geocoding library that uses a K-D Tree data structure to efficiently find the nearest geographic location to a given query point.

## Features

- **Fast Nearest Neighbor Search**: Uses a K-D Tree for O(log n) average case performance
- **Haversine Distance Calculation**: Accurate distance calculations on Earth's surface
- **CSV Data Loading**: Easy loading of location data from CSV files
- **Memory Efficient**: Optimized data structures for handling large datasets

## Project Structure

```
geocoder/
├── README.md
├── data/
│   └── locations.csv        # Sample location data
├── include/
│   └── geocoder.h          # Header file with declarations
└── src/
    ├── geocoder.cpp        # Implementation of geocoder functions
    └── main.cpp            # Example usage
```

## Requirements

- C++17 compatible compiler (GCC, Clang, MSVC)
- Standard C++ libraries

## Building

### Quick Build

```bash
g++ src/main.cpp src/geocoder.cpp -I include/ -o geocoder -std=c++17 -O2
```

### For Development (with debugging)

```bash
g++ src/main.cpp src/geocoder.cpp -I include/ -o geocoder -std=c++17 -g -Wall -Wextra
```

## Usage

### Basic Example

```cpp
#include "geocoder.h"
#include <iostream>

int main() {
    // Load locations from CSV file
    std::vector<Location> locations = loadLocations("data/locations.csv");

    if (locations.empty()) {
        std::cerr << "Could not load location data." << std::endl;
        return 1;
    }

    // Build the K-D Tree
    KDTree geocoder(locations);

    // Query for nearest location to Paris coordinates
    Location query = {"", 48.8566, 2.3522};
    Location nearest = geocoder.findNearestNeighbor(query);

    std::cout << "Nearest location: " << nearest.name << std::endl;
    return 0;
}
```

### Running the Example

```bash
./geocoder
```

Expected output:

```
The nearest location to (48.8566, 2.3522) is: Paris
```

## Data Format

The CSV file should contain location data in the following format:

```csv
Name,Latitude,Longitude
New York,40.7128,-74.0060
London,51.5074,-0.1278
Tokyo,35.6762,139.6503
Sydney,-33.8688,151.2093
Paris,48.8566,2.3522
```

## API Reference

### Data Structures

#### `Location`

```cpp
struct Location {
    std::string name;      // Name of the location
    double latitude;       // Latitude in decimal degrees
    double longitude;      // Longitude in decimal degrees
};
```

### Functions

#### `loadLocations(const std::string& filename)`

- **Description**: Loads location data from a CSV file
- **Parameters**: `filename` - Path to the CSV file
- **Returns**: `std::vector<Location>` - Vector of loaded locations
- **Example**:
  ```cpp
  auto locations = loadLocations("data/cities.csv");
  ```

#### `haversineDistance(const Location& loc1, const Location& loc2)`

- **Description**: Calculates the great-circle distance between two points on Earth
- **Parameters**: Two `Location` objects
- **Returns**: `double` - Distance in kilometers
- **Example**:
  ```cpp
  Location nyc = {"New York", 40.7128, -74.0060};
  Location london = {"London", 51.5074, -0.1278};
  double distance = haversineDistance(nyc, london);
  ```

### Classes

#### `KDTree`

##### Constructor

```cpp
KDTree(std::vector<Location>& locations)
```

- **Description**: Builds a K-D Tree from the provided locations
- **Parameters**: `locations` - Vector of locations to index

##### Methods

```cpp
Location findNearestNeighbor(const Location& query)
```

- **Description**: Finds the nearest location to the query point
- **Parameters**: `query` - The location to search near
- **Returns**: `Location` - The nearest location in the dataset

## Algorithm Details

### K-D Tree

- **Time Complexity**:
  - Build: O(n log n)
  - Search: O(log n) average case, O(n) worst case
- **Space Complexity**: O(n)

### Haversine Formula

The distance calculation uses the Haversine formula to account for Earth's curvature:

$$d = 2r \arcsin\left(\sqrt{\sin^2\left(\frac{\Delta\phi}{2}\right) + \cos(\phi_1)\cos(\phi_2)\sin^2\left(\frac{\Delta\lambda}{2}\right)}\right)$$

Where:

- $r$ = Earth's radius (6,371 km)
- $\phi$ = latitude in radians
- $\lambda$ = longitude in radians

## Performance

The K-D Tree provides excellent performance for nearest neighbor searches:

- **Small datasets** (<1,000 locations): Near-instantaneous
- **Medium datasets** (1,000-100,000 locations): Sub-millisecond searches
- **Large datasets** (>100,000 locations): Still very fast due to logarithmic complexity

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new functionality
5. Submit a pull request

## License

This project is open source. Feel free to use, modify, and distribute as needed.

## Future Enhancements

- [ ] Support for different distance metrics
- [ ] Multi-threaded tree building
- [ ] Range queries (find all locations within a radius)
- [ ] Dynamic insertion/deletion of locations
- [ ] Serialization of built trees for faster startup
- [ ] Integration with mapping APIs
