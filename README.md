# gpx_cpp
A lightweight, modern C++17 library for parsing GPX files, and handling ISO-8601 timestamps.

The project aims to provide:
- Clean and understandable C++ APIs
- No dependencies except TinyXML2
- High-accuracy timestamp extraction
- Track, route, and waypoint parsing
- GoogleTest unit tests
- Example programs

## Features
- Parse GPX 1.1 files (tracks, waypoints, routes)
- Extract latitude, longitude, elevation, and timestamps
- Convert ISO-8601 timestamps to epoch milliseconds
- Store points in a structured format

## Build

### With CMake

```bash
mkdir build
cd build
cmake ..
make

