#pragma once

#include <vector>
#include <iostream>
#include "gpx/document.h"

namespace gpx::testutils 
{
    std::vector<TimeMs> collect_times(const Document& doc);

    void print_times(const Document& doc);
}
