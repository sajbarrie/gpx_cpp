#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace gpx 
{

    struct Point 
    {
        double lat = 0.0;
        double lon = 0.0;
        double ele = 0.0;
        std::uint64_t time_ms = 0;
    };

    struct Waypoint 
    {
        Point point;
        std::string name;
    };

    struct TrackPoint : public Point {};

    struct TrackSegment 
    {
        std::vector<TrackPoint> points;
    };

    struct Track 
    {
        std::string name;
        std::vector<TrackSegment> segments;
    };

    struct RoutePoint : public Point {};

    struct Route 
    {
        std::string name;
        std::vector<RoutePoint> points;
    };

} // namespace gpx
