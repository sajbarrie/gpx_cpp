#pragma once

#include <optional>
#include "gpx/types.h"
#include "gpx/document.h"

namespace gpx
{
    struct StateVector
    {
        TimeMs time;                       // ms since Unix epoch (UTC)

        double latitude = 0.0;             // degrees
        double longitude = 0.0;            // degrees
        std::optional<double> elevation;  // meters
    };

    std::optional<StateVector>
    query_state_interpolated(const Document& doc, TimeMs t);
}
