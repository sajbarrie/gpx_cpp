#pragma once

#include <vector>
#include "gpx/types.h"

namespace gpx 
{

    class Document
    {
    public:
        // ---- Read-only API ----
        const Metadata& metadata()  const noexcept;
        const std::vector<Waypoint>& waypoints() const noexcept;
        const std::vector<Route>&    routes()    const noexcept;
        const std::vector<Track>&    tracks()    const noexcept;

        bool empty() const noexcept;

        // ---- Parser-only mutation ----
        void clear();

        void set_metadata(const Metadata& md);

        void add_waypoint(const Waypoint& wp);
        void add_route(const Route& rte);
        void add_track(const Track& trk);

    private:
        Metadata metadata_;
        std::vector<Waypoint> waypoints_;
        std::vector<Route>    routes_;
        std::vector<Track>    tracks_;
    };

} // namespace gpx
