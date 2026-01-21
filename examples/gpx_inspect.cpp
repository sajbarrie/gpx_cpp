#include <iostream>
#include <iomanip>
#include "gpx/gpx_parser.h"

static void printTime(const std::optional<gpx::TimeMs>& t)
{
    if (!t) 
    {
        std::cout << "N/A";
        return;
    }

    std::time_t sec = static_cast<std::time_t>(*t / 1000);
    std::tm utc{};
    gmtime_s(&utc, &sec);

    std::cout << std::put_time(&utc, "%Y-%m-%d %H:%M:%S UTC");
}

int main(int argc, char** argv)
{
    if (argc < 2) 
    {
        std::cerr << "Usage: gpx_inspect <file.gpx>\n";
        return 1;
    }

    gpx::Parser parser;
    gpx::Document doc;

    if (!parser.loadFromFile(argv[1], doc)) 
    {
        std::cerr << "Error: " << parser.lastError() << "\n";
        return 2;
    }

    std::cout << "===== GPX SUMMARY =====\n";

    std::cout << "Waypoints: " << doc.waypoints().size() << "\n";
    std::cout << "Routes:    " << doc.routes().size() << "\n";
    std::cout << "Tracks:    " << doc.tracks().size() << "\n";

    if (!doc.tracks().empty()) 
    {
        const auto& trk = doc.tracks().front();
        std::cout << "\nFirst track:\n";
        std::cout << "Segments: " << trk.segments.size() << "\n";

        if (!trk.segments.empty()) 
        {
            const auto& seg = trk.segments.front();
            std::cout << "Points: " << seg.points.size() << "\n";

            if (!seg.points.empty()) 
            {
                std::cout << "Start time: ";
                printTime(seg.points.front().time);
                std::cout << "\n";

                std::cout << "End time:   ";
                printTime(seg.points.back().time);
                std::cout << "\n";
            }
        }
    }

    std::cout << "========================\n";
}
