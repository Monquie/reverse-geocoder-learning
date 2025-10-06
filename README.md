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

## Usage

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
