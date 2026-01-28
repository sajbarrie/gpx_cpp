#include "gpx/state.h"
#include <algorithm>
#include <vector>

namespace gpx
{
    static std::vector<const Waypoint*>
    collect_time_ordered_points(const Document& doc)
    {
        std::vector<const Waypoint*> out;

        for (const auto& trk : doc.tracks())
            for (const auto& seg : trk.segments)
                for (const auto& pt : seg.points)
                    if (pt.time)
                        out.push_back(&pt);

        std::sort(out.begin(), out.end(),
            [](const Waypoint* a, const Waypoint* b)
            {
                return *a->time < *b->time;
            });

        return out;
    }

    std::optional<StateVector>
    query_state_interpolated(const Document& doc, TimeMs t)
    {
        auto pts = collect_time_ordered_points(doc);
        if (pts.empty())
            return std::nullopt;


        if (t <= *pts.front()->time)
        {
            const auto& p = *pts.front();
            return StateVector{ *p.time, p.latitude, p.longitude, p.elevation };
        }

        if (t >= *pts.back()->time)
        {
            const auto& p = *pts.back();
            return StateVector{ *p.time, p.latitude, p.longitude, p.elevation };
        }

        auto it = std::lower_bound(
            pts.begin(), pts.end(), t,
            [](const Waypoint* p, TimeMs value)
            {
                return *p->time < value;
            });

        const Waypoint& p2 = **it;
        const Waypoint& p1 = **(it - 1);

        TimeMs t1 = *p1.time;
        TimeMs t2 = *p2.time;

        if (t2 == t1)
            return StateVector{ t, p1.latitude, p1.longitude, p1.elevation };

        double alpha = double(t - t1) / double(t2 - t1);

        auto lerp = [&](double a, double b)
        {
            return a + alpha * (b - a);
        };

        StateVector s;
        s.time = t;
        s.latitude  = lerp(p1.latitude,  p2.latitude);
        s.longitude = lerp(p1.longitude, p2.longitude);

        if (p1.elevation && p2.elevation)
            s.elevation = lerp(*p1.elevation, *p2.elevation);

        return s;
    }
}
