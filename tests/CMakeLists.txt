add_executable(gpx_cpp_tests 
    state_tests.cpp 
    utilstests.cpp 
    test_utils.cpp    
)


target_link_libraries(gpx_cpp_tests 
    PRIVATE 
    gpx_cpp::gpx_cpp
    GTest::gtest_main
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/test_data" 
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

include(GoogleTest)
gtest_discover_tests(gpx_cpp_tests)

