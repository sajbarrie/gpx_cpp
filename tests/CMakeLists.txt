add_executable(tests
    parser_tests.cpp
)

target_link_libraries(tests
    PRIVATE gpx_cpp
)

add_test(NAME tests COMMAND tests)


