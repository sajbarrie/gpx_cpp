#include "test_utils.h"
#include <algorithm>

namespace gpx::testutils 
{
    std::vector<TimeMs> collect_times(const Document& doc)
    {
        std::vector<TimeMs> times;

        for (const auto& trk : doc.tracks())
            for (const auto& seg : trk.segments)
                for (const auto& pt : seg.points)
                    if (pt.time)
                        times.push_back(*pt.time);

        std::sort(times.begin(), times.end());
        return times;
    }

    void print_times(const Document& doc)
    {
        auto times = collect_times(doc);

        std::cout << "\nGPX timestamps:\n";
        for (auto t : times)
            std::cout << "  " << t << "\n";
    }
}
