#pragma once
#include "types.h"

namespace gpx 
{
    class Document 
    {
        public:
            // --- Data access (read-only) ---

            const std::vector<Waypoint>& waypoints() const noexcept;
            const std::vector<Route>&    routes() const noexcept;
            const std::vector<Track>&    tracks() const noexcept;


        // --- Data mutation (parser use only) ---
        void add_waypoint(const Waypoint& wp);
        void add_route(const Route& rte);
        void add_track(const Track& trk);

        // --- Utilities ---
        void clear();
        bool empty() const noexcept;

        private:
            std::vector<Waypoint> waypoints_;
            std::vector<Route>    routes_;
            std::vector<Track>    tracks_;
        };
}
