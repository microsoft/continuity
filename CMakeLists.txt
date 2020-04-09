cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
cmake_policy(SET CMP0092 NEW)

project(
    Microsoft.ReactNative.SDK
    HOMEPAGE_URL "https://github.com/microsoft/continuity"
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(RNSDK_SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(RNSDK_BIN_ROOT ${CMAKE_CURRENT_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

include(rnsdk)
include(CTest)
include(NuGet)
include(FetchContent)


### External dependencies

# boost
if("$ENV{BOOST_ROOT_1_72_0}" STREQUAL "")
    nuget(install boost -Version 1.72.0.0 -Framework native -OutputDirectory ${RNSDK_NUGET_ROOT} -NonInteractive)
    set(BOOST_ROOT ${RNSDK_NUGET_ROOT}/boost.1.72.0.0/lib/native)
else()
    if(EXISTS $ENV{BOOST_ROOT_1_72_0}/lib/native)
        set(BOOST_ROOT $ENV{BOOST_ROOT_1_72_0}/lib/native)
    else()
        set(BOOST_ROOT $ENV{BOOST_ROOT_1_72_0})
    endif()
endif()
list(APPEND RNSDK_COMPILE_DEFINITIONS
    BOOST_ALL_NO_LIB=1
    BOOST_ASIO_HAS_IOCP
    BOOST_ERROR_CODE_HEADER_ONLY
    BOOST_NO_RTTI
    BOOST_NO_TYPEID
    BOOST_SYSTEM_SOURCE)

file(TO_CMAKE_PATH ${BOOST_ROOT} BOOST_ROOT)
message(STATUS "Boost: ${BOOST_ROOT}")


# GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        2fe3bd994b3189899d93f1d5a881e725e046fdc2
    GIT_SHALLOW    1)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

message(STATUS "Downloading GoogleTest...")
FetchContent_MakeAvailable(googletest)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    list(APPEND GOOGLETEST_COMPILE_DEFINITIONS
            _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
            GTEST_HAS_RTTI=0)
    target_compile_definitions(gtest PRIVATE ${GOOGLETEST_COMPILE_DEFINITIONS})
    target_compile_definitions(gtest_main PRIVATE ${GOOGLETEST_COMPILE_DEFINITIONS})
    target_compile_definitions(gmock PRIVATE ${GOOGLETEST_COMPILE_DEFINITIONS})
    target_compile_definitions(gmock_main PRIVATE ${GOOGLETEST_COMPILE_DEFINITIONS})
endif()
list(APPEND RNSDK_COMPILE_DEFINITIONS GTEST_HAS_RTTI=0)


# Mso
FetchContent_Declare(
    Mso
    GIT_REPOSITORY  https://github.com/microsoft/Mso.git
    GIT_TAG         @microsoft/mso_v0.0.18)
if(RNSDK_TARGET_PLATFORM STREQUAL "Win32")
    set(MSO_LIBLET_PLATFORM WIN32 CACHE STRING "" FORCE)
elseif(RNSDK_TARGET_PLATFORM STREQUAL "macOS")
    set(MSO_LIBLET_PLATFORM MAC CACHE STRING "" FORCE)
elseif(RNSDK_TARGET_PLATFORM STREQUAL "iOS")
    set(MSO_LIBLET_PLATFORM IOS CACHE STRING "" FORCE)
elseif(RNSDK_TARGET_PLATFORM STREQUAL "Android")
    set(MSO_LIBLET_PLATFORM ANDROID CACHE STRING "" FORCE)
endif()
set(MSO_LIBLET_TEST GTEST CACHE STRING "" FORCE) # GTEST XCTEST
set(MSO_ENABLE_UNIT_TESTS ON CACHE BOOL "" FORCE)
set(MSO_ENABLE_INCLUDES_CHECKS OFF CACHE BOOL "" FORCE)

message(STATUS "Downloading Mso...")
FetchContent_MakeAvailable(Mso)


### Project directories

add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
