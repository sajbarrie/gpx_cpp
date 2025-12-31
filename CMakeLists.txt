cmake_minimum_required(VERSION 3.20)

project(gpx_cpp
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(gpx_cpp
    src/gpx_parser.cpp
)

target_include_directories(gpx_cpp
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)