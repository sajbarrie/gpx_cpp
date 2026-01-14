#include <gpx/gpx_types.h>
#include <gpx/document.hpp>
#include <gpx/parser.hpp>
#include <iostream>

int main() 
{
    /* 1 gpx::GpxDocument doc;
    gpx::GpxPoint p;
    doc.waypoints.push_back(p);
    return 0;*/

    /* 2gpx::Document doc;
    doc.clear();
    return doc.empty() ? 0 : 1; */
    
    gpx::Parser parser;
    gpx::Document doc;

    std::string error;
    bool ok = parser.loadFromFile("test.gpx", doc, &error);

    if (!ok) 
    {
        std::cout << "Expected failure: " << error << std::endl;
    }
}
