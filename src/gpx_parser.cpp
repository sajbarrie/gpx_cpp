#include "gpx/gpx_parser.h"
#include "gpx/document.h"
#include "gpx/types.h"
#include <fstream>
#include <optional>
#include <chrono>
#include "tinyxml2.h"

#include <sstream>
#include <iomanip>
#include <ctime>

using namespace tinyxml2;

namespace gpx
{

    static std::optional<TimeMs> parseTime(const char* iso)
    {
        if (!iso) return std::nullopt;

        std::tm tm{};
        std::istringstream ss(iso);
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
        if (ss.fail()) return std::nullopt;

    #if defined(_WIN32)
        std::time_t t = _mkgmtime(&tm);
    #else
        std::time_t t = timegm(&tm);
    #endif

        if (t < 0) return std::nullopt;
        return static_cast<TimeMs>(t) * 1000;
    }

    static XMLElement* child(XMLElement* parent, const char* name)
    {
        for (auto* e = parent->FirstChildElement(); e; e = e->NextSiblingElement())
        {
            if (std::strcmp(e->Name(), name) == 0) return e;
        }
        return nullptr;
    }

    static void parsePoint(XMLElement* el, Waypoint& out)
    {
        el->QueryDoubleAttribute("lat", &out.latitude);
        el->QueryDoubleAttribute("lon", &out.longitude);

        if (auto* e = child(el, "ele"))
        {
            double v{};
            if (e->QueryDoubleText(&v) == XML_SUCCESS)
                out.elevation = v;
        }

        if (auto* t = child(el, "time"))
        {
            out.time = parseTime(t->GetText());
        }
    }

    // -----------------------------
    // Parser
    // -----------------------------

    bool Parser::loadFromStream(std::istream& input, Document& outDoc)
    {
        outDoc.clear();
        m_lastError.clear();

        std::ostringstream oss;
        oss << input.rdbuf();
        std::string xml = oss.str();

        XMLDocument doc;
        if (doc.Parse(xml.c_str()) != XML_SUCCESS)
        {
            m_lastError = "XML parse error";
            return false;
        }

        auto* gpx = doc.RootElement();
        if (!gpx || std::strcmp(gpx->Name(), "gpx") != 0)
        {
            m_lastError = "Missing <gpx> root element";
            return false;
        }

        // ---- metadata ----
        if (auto* md = child(gpx, "metadata"))
        {
            Metadata meta;

            if (auto* n = child(md, "name"))
                if (n->GetText()) meta.name = n->GetText();

            if (auto* t = child(md, "time"))
                meta.time = parseTime(t->GetText());

            if (auto* d = child(md, "desc"))
                if (d->GetText()) meta.description = d->GetText();

            outDoc.set_metadata(meta);
        }

        // ---- waypoints ----
        for (auto* wpt = child(gpx, "wpt"); wpt; wpt = wpt->NextSiblingElement("wpt"))
        {
            Waypoint p{};
            if (wpt->QueryDoubleAttribute("lat", &p.latitude) == XML_SUCCESS &&
                wpt->QueryDoubleAttribute("lon", &p.longitude) == XML_SUCCESS)
            {
                parsePoint(wpt, p);
                outDoc.add_waypoint(p);
            }
        }

        // ---- routes ----
        for (auto* rte = child(gpx, "rte"); rte; rte = rte->NextSiblingElement("rte"))
        {
            Route route;

            if (auto* n = child(rte, "name"))
                if (n->GetText()) route.name = n->GetText();

            for (auto* pt = child(rte, "rtept"); pt; pt = pt->NextSiblingElement("rtept"))
            {
                Waypoint p{};
                if (pt->QueryDoubleAttribute("lat", &p.latitude) == XML_SUCCESS &&
                    pt->QueryDoubleAttribute("lon", &p.longitude) == XML_SUCCESS)
                {
                    parsePoint(pt, p);
                    route.points.push_back(p);
                }
            }

            if (!route.points.empty())
                outDoc.add_route(route);
        }

        // ---- tracks ----
        for (auto* trk = child(gpx, "trk"); trk; trk = trk->NextSiblingElement("trk"))
        {
            Track track;

            if (auto* n = child(trk, "name"))
                if (n->GetText()) track.name = n->GetText();

            for (auto* seg = child(trk, "trkseg"); seg; seg = seg->NextSiblingElement("trkseg"))
            {
                TrackSegment ts;

                for (auto* pt = child(seg, "trkpt"); pt; pt = pt->NextSiblingElement("trkpt"))
                {
                    Waypoint p{};
                    if (pt->QueryDoubleAttribute("lat", &p.latitude) == XML_SUCCESS &&
                        pt->QueryDoubleAttribute("lon", &p.longitude) == XML_SUCCESS)
                    {
                        parsePoint(pt, p);
                        ts.points.push_back(p);
                    }
                }

                if (!ts.points.empty())
                    track.segments.push_back(std::move(ts));
            }

            if (!track.segments.empty())
                outDoc.add_track(track);
        }

        return !outDoc.empty();
    }

    bool Parser::loadFromFile(const std::string& path, Document& outDoc)
    {
        std::ifstream file(path);
        if (!file)
        {
            m_lastError = "Cannot open file: " + path;
            return false;
        }
        return loadFromStream(file, outDoc);
    }

    const std::string& Parser::lastError() const noexcept
    {
        return m_lastError;
    }

} 
