#include <optional>
#include "gpx/gpx_parser.h"

namespace gpx 
{

    struct Point 
    {
    double latitude;     // required
    double longitude;    // required
    std::optional<double> elevation;   // meters
    std::optional<std::int64_t> time;   // milliseconds since Unix epoch
    };

    struct TrackSegment 
    {
    std::vector<Point> points;
    };

    struct Track 
    {
    std::string name;
    std::vector<TrackSegment> segments;
    };

    struct Route 
    {
    std::string name;
    std::vector<Point> points;
    };

    using Waypoint = Point;

} // namespace gpx