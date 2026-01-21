#pragma once

#include <string>
#include <istream>
#include "gpx/document.h"

namespace gpx 
{

    class Parser
    {
    public:
        bool loadFromFile(const std::string& path, Document& outDoc);
        bool loadFromStream(std::istream& input, Document& outDoc);

        const std::string& lastError() const noexcept;

    private:
        std::string m_lastError;
    };

} // namespace gpx
