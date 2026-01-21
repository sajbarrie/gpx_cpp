#include "gpx/document.h"

namespace gpx 
{

    const Metadata& Document::metadata() const noexcept
    {
        return metadata_;
    }

    const std::vector<Waypoint>& Document::waypoints() const noexcept
    {
        return waypoints_;
    }

    const std::vector<Route>& Document::routes() const noexcept
    {
        return routes_;
    }

    const std::vector<Track>& Document::tracks() const noexcept
    {
        return tracks_;
    }

    bool Document::empty() const noexcept
    {
        return waypoints_.empty() && routes_.empty() && tracks_.empty();
    }

    void Document::clear()
    {
        metadata_ = Metadata{};
        waypoints_.clear();
        routes_.clear();
        tracks_.clear();
    }

    void Document::set_metadata(const Metadata& md)
    {
        metadata_ = md;
    }

    void Document::add_waypoint(const Waypoint& wp)
    {
        waypoints_.push_back(wp);
    }

    void Document::add_route(const Route& rte)
    {
        routes_.push_back(rte);
    }

    void Document::add_track(const Track& trk)
    {
        tracks_.push_back(trk);
    }

} // namespace gpx
