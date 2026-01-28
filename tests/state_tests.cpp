#include <gtest/gtest.h>

#include "gpx/gpx_parser.h"
#include "gpx/state.h"
#include "test_utils.h"

using namespace gpx;

static const char* TEST_FILE = "test_data/valid_simple.gpx";

TEST(state_tests, LoadFileSuccessfully)
{
    Parser parser;
    Document doc;

    bool ok = parser.loadFromFile(TEST_FILE, doc);
    ASSERT_TRUE(ok) << parser.lastError();
    ASSERT_FALSE(doc.empty());
}

TEST(state_tests, QueryExactTime)
{
    Parser parser;
    Document doc;
    ASSERT_TRUE(parser.loadFromFile(TEST_FILE, doc));

    const auto& p = doc.tracks()[0].segments[0].points[0];
    ASSERT_TRUE(p.time.has_value());

    auto state = query_state_interpolated(doc, *p.time);
    ASSERT_TRUE(state.has_value());

    EXPECT_NEAR(state->latitude,  p.latitude,  1e-9);
    EXPECT_NEAR(state->longitude, p.longitude, 1e-9);
}

TEST(state_tests, QueryBetweenTwoPointsInterpolates)
{
    Parser parser;
    Document doc;
    ASSERT_TRUE(parser.loadFromFile(TEST_FILE, doc));

    const auto& p1 = doc.tracks()[0].segments[0].points[0];
    const auto& p2 = doc.tracks()[0].segments[0].points[1];

    ASSERT_TRUE(p1.time && p2.time);

    TimeMs mid = (*p1.time + *p2.time) / 2;

    auto state = query_state_interpolated(doc, mid);
    ASSERT_TRUE(state.has_value());

    double alpha = double(mid - *p1.time) / double(*p2.time - *p1.time);

    double lat = p1.latitude  + alpha * (p2.latitude  - p1.latitude);
    double lon = p1.longitude + alpha * (p2.longitude - p1.longitude);

    EXPECT_NEAR(state->latitude, lat, 1e-9);
    EXPECT_NEAR(state->longitude, lon, 1e-9);
}

TEST(state_tests, QueryBeforeFirstClamps)
{
    Parser parser;
    Document doc;
    ASSERT_TRUE(parser.loadFromFile(TEST_FILE, doc));

    const auto& p = doc.tracks()[0].segments[0].points[0];
    auto state = query_state_interpolated(doc, *p.time - 100000);

    ASSERT_TRUE(state.has_value());
    EXPECT_NEAR(state->latitude, p.latitude, 1e-9);
}

TEST(state_tests, QueryAfterLastClamps)
{
    Parser parser;
    Document doc;
    ASSERT_TRUE(parser.loadFromFile(TEST_FILE, doc));

    const auto& seg = doc.tracks()[0].segments[0];
    const auto& p = seg.points.back();

    auto state = query_state_interpolated(doc, *p.time + 100000);

    ASSERT_TRUE(state.has_value());
    EXPECT_NEAR(state->latitude, p.latitude, 1e-9);
}
