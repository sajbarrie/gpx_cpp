#ifndef GPX_TYPES_H
#define GPX_TYPES_H

#include <optional>
#include <vector>
#include <string>
#include <cstdint>

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace gpx 
{

    // Time is stored as milliseconds since Unix epoch (UTC)
    using TimeMs = std::int64_t;

    struct GpxPoint 
    {
        double latitude = 0.0;
        double longitude = 0.0;
        std::optional<double> elevation;     // meters
        std::optional<TimeMs> time;           // ms since epoch
    };

    struct GpxTrackSegment 
    {
        std::vector<GpxPoint> points;
    };

    struct GpxTrack 
    {
        std::optional<std::string> name;
        std::vector<GpxTrackSegment> segments;
    };

    struct GpxRoute 
    {
        std::optional<std::string> name;
        std::vector<GpxPoint> points;
    };

    struct GpxMetadata 
    {
        std::optional<std::string> name;
        std::optional<TimeMs> time;
        std::optional<std::string> description;
    };

    struct GpxDocument 
    {
        GpxMetadata metadata;
        std::vector<GpxPoint> waypoints;
        std::vector<GpxTrack> tracks;
        std::vector<GpxRoute> routes;
    };

} // namespace gpx

#endif



