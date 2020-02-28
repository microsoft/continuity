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

set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(NUGET_ROOT ${CMAKE_CURRENT_BINARY_DIR}/nuget)
file(MAKE_DIRECTORY ${NUGET_ROOT})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
source_group(TREE ${INC_ROOT} PREFIX "Header Files" FILES ${HEADERS})

include(CTest)

add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
