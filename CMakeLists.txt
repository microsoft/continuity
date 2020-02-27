cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

project(
    Microsoft::Continuity
    VERSION 0.1
    DESCRIPTION "Microsoft Continuity: Libraries, tools and documentation for using react-native in native applications."
    HOMEPAGE_URL "https://github.com/microsoft/continuity"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CTest)
include(FetchContent)

include(NuGet)
nuget(install ${CMAKE_CURRENT_SOURCE_DIR}/packages.config)

include(folly)

add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
