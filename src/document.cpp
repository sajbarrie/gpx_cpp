#include "gpx/document.hpp"

namespace gpx 
{
    void Document::clear() 
    {
        waypoints.clear();
        routes.clear();
        tracks.clear();
    }

    bool Document::empty() const 
    {
        return waypoints.empty() && routes.empty() && tracks.empty();
    }
}
