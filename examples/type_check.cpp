#include <gpx/types.h>
#include <gpx/document.h>
#include <gpx/gpx_parser.h>
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

    bool ok = parser.loadFromFile("test.gpx", doc);

    if (!ok) 
    {
        std::cout << "Expected failure: " << parser.lastError() << std::endl;
    }
}
