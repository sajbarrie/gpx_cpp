#include <gtest/gtest.h>

#include "gpx/gpx_parser.h"
#include "gpx/state.h"
#include "test_utils.h"
#include <algorithm>

using namespace gpx;

static const char* TEST_FILE = "test_data/valid_simple.gpx";

TEST(utilstests, TimeCollection)
{
    Parser parser;
    Document doc;

    ASSERT_TRUE(parser.loadFromFile(TEST_FILE, doc)) << parser.lastError();

    auto times = gpx::testutils::collect_times(doc);

    ASSERT_FALSE(times.empty());
    EXPECT_TRUE(std::is_sorted(times.begin(), times.end()));
}

TEST(utilstests, TimePrinting)
{
    Parser parser;
    Document doc;

    ASSERT_TRUE(parser.loadFromFile(TEST_FILE, doc)) << parser.lastError();

    testing::internal::CaptureStdout();
    gpx::testutils::print_times(doc);
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_FALSE(output.empty());
    EXPECT_NE(output.find("GPX timestamps:"), std::string::npos);
}

TEST(utilstests, CollectionAndPrinting)
{
    Parser parser;
    Document doc;

    ASSERT_TRUE(parser.loadFromFile(TEST_FILE, doc)) << parser.lastError();

    auto times = gpx::testutils::collect_times(doc);
    ASSERT_FALSE(times.empty());
    ASSERT_TRUE(std::is_sorted(times.begin(), times.end()));

    testing::internal::CaptureStdout();
    gpx::testutils::print_times(doc);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("GPX timestamps:"), std::string::npos);
    EXPECT_NE(output.find(std::to_string(times.front())), std::string::npos);
}

TEST(utilstests, PrintAllTimes)
{
    Parser parser;
    Document doc;
    ASSERT_TRUE(parser.loadFromFile(TEST_FILE, doc));

    gpx::testutils::print_times(doc);
}

