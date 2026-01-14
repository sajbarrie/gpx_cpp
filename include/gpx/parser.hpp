#pragma once
#include <string>
#include "document.hpp"

namespace gpx 
{
    class Parser {
    public:
        Parser() = default;

        // Load and parse a GPX file
        bool loadFromFile(const std::string& path, Document& outDoc, std::string* error = nullptr);

        // Load and parse GPX data from memory
        bool loadFromString(const std::string& xml, Document& outDoc, std::string* error = nullptr);
    };
}
