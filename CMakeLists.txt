cmake_minimum_required(VERSION 3.20)

project(gpx_cpp
    VERSION 0.1.0
    DESCRIPTION "Modern C++ GPX parsing and trajectory query library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(gpx_cpp
    src/gpx_parser.cpp
    src/document.cpp
    src/state.cpp
    external/tinyxml2/tinyxml2.cpp
)

add_library(gpx_cpp::gpx_cpp ALIAS gpx_cpp)

target_include_directories(gpx_cpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/tinyxml2
)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.15.2
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()

include(GNUInstallDirs)

install(TARGETS gpx_cpp
    EXPORT gpx_cppTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT gpx_cppTargets
    FILE gpx_cppTargets.cmake
    NAMESPACE gpx_cpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gpx_cpp
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/gpx_cppConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/gpx_cppConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/gpx_cppConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gpx_cpp
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/gpx_cppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/gpx_cppConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gpx_cpp
)
