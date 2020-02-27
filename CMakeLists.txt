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

## Arrange IDE projects/files into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CTest)
include(FetchContent)

#FetchContent_Declare(
#    double_conversion
#    URL "https://github.com/google/double-conversion/archive/v3.1.5.tar.gz"
#    URL_HASH SHA512=0aeabdbfa06c3c4802905ac4bf8c2180840577677b47d45e1c91034fe07746428c9db79260ce6bdbdf8b584746066cea9247ba43a9c38155caf1ef44e214180a)


#### HERE -- FetchContent is failing because folly's cmakelists.txt wants boost. which probably doesn't matter.
###          take a look at RN4W to see what minimal pieces of folly are needed. maybe just check them in, or write
###             a custom unpacker to pull them out of the tarball. do what RN4W does. shouldn't be too hard.

FetchContent_Declare(
    folly
    URL "https://github.com/facebook/folly/archive/v2019.09.30.00.zip"
    URL_HASH SHA512=2edb1e0b50a75604530d8bdcc35cacef500cb8b1466d546b3a201882da69cfba1b91493225b71d5bcf99f610d5b1668b115edebcfb25f9e36dc75e8632afaa58)
FetchContent_MakeAvailable(folly)

add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
