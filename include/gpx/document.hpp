#pragma once
#include "types.hpp"

namespace gpx 
{
    class Document 
    {
    public:
        std::vector<Waypoint> waypoints;
        std::vector<Route>    routes;
        std::vector<Track>    tracks;

        void clear();
        bool empty() const;
    };
}
