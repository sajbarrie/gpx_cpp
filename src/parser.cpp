#include "gpx/parser.h"

namespace gpx 
{
    bool Parser::loadFromFile(const std::string&, Document& outDoc, std::string* error) {
        outDoc.clear();
        if (error) *error = "Parser not implemented yet";
        return false;
    }

    bool Parser::loadFromString(const std::string&, Document& outDoc, std::string* error) {
        outDoc.clear();
        if (error) *error = "Parser not implemented yet";
        return false;
    }
}
