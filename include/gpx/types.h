#pragma once

#include <optional>
#include <vector>
#include <string>
#include <cstdint>

namespace gpx 
{

    using TimeMs = std::int64_t;

    struct Waypoint
    {
        double latitude = 0.0;      // required
        double longitude = 0.0;     // required
        std::optional<double> elevation;   // meters
        std::optional<TimeMs> time;         // ms since epoch
    };

    struct TrackSegment
    {
        std::vector<Waypoint> points;
    };

    struct Track
    {
        std::optional<std::string> name;
        std::vector<TrackSegment> segments;
    };

    struct Route
    {
        std::optional<std::string> name;
        std::vector<Waypoint> points;
    };

    struct Metadata
    {
        std::optional<std::string> name;
        std::optional<TimeMs> time;
        std::optional<std::string> description;
    };

} // namespace gpx




