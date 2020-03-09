cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

message(STATUS "CMake Source: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMake Binary: ${CMAKE_BINARY_DIR}")

project(
    MicrosoftContinuity
    VERSION 0.1
    DESCRIPTION "Microsoft Continuity: Libraries, tools and documentation for using react-native in native applications."
    HOMEPAGE_URL "https://github.com/microsoft/continuity"
    LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()


### Common paths

set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(NUGET_ROOT ${CMAKE_CURRENT_BINARY_DIR}/nuget)
file(MAKE_DIRECTORY ${NUGET_ROOT})


### Configuration variables

set(PROJECT_COMPILE_DEFINITIONS "")


### Build-type configuration

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    list(APPEND PROJECT_COMPILE_DEFINITIONS
        _DEBUG
        DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    list(APPEND PROJECT_COMPILE_DEFINITIONS
        NDEBUG)
else()
    message(FATAL_ERROR "This project does not support build type '${CMAKE_BUILD_TYPE}'. Only 'Debug' and 'Release' builds are allowed.")
endif()


### Platform configuration

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Enforce minimum target version of Windows
    if(CMAKE_SYSTEM_VERSION VERSION_LESS "10.0.15063.0")
        message(FATAL_ERROR "This project does not support target Windows build ${CMAKE_SYSTEM_VERSION}. You oldest allowed Windows build is 10.0.15063.0 (version 1703, Redstone 2).")
    endif()

    # Warn when not using Ninja to generate build scripts
    if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
        message(WARNING "Warning: CMake generator '${CMAKE_GENERATOR}' is not supported but may work. 'Ninja' is the only supported generator.")
    endif()

    # _WIN32_WINNT_WIN8 = 0x0602
    list(APPEND PROJECT_COMPILE_DEFINITIONS
        WIN32
        _WINDOWS
        WINVER=0x0602
        _WIN32_WINNT=0x0602
        WIN32_LEAN_AND_MEAN
        WINRT_LEAN_AND_MEAN
        NOMINMAX
        _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
#elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
#elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
#elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
else()
    message(FATAL_ERROR "This project does not support the '${CMAKE_SYSTEM_NAME}' platform.")
endif()


### Compiler/linker flags

set(CMAKE_CXX_STANDARD 17)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Enforce required platform toolset
    if(NOT MSVC_TOOLSET_VERSION EQUAL 142)
        message(FATAL_ERROR "This project does not support Visual Studio toolset ${MSVC_TOOLSET_VERSION}. It only supports toolset 142 (Visual Studio 2019).")
    endif()

    set(ARCHITECTURE_NAME X86)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCHITECTURE_NAME X64)
    endif()

    # These are related to packing/alignment and [[nodiscard]], which makes them a little risky, but MSO requires them.
    set(DISABLE_RISKY_WARNINGS_FOR_MSO "/wd4121 /wd4315 /wd4834")

    set(CMAKE_CXX_FLAGS "/nologo /EHsc /GR- /GS /permissive- /sdl /utf-8 /W4 /WX /Zi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4018 /wd4068 /wd4100 /wd4101 /wd4127 /wd4146 /wd4189 /wd4201 /wd4244 /wd4251 /wd4267 /wd4290 /wd4293 /wd4305 /wd4309 /wd4324 /wd4456 /wd4458 /wd4505 /wd4702 /wd4800 /wd4804")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DISABLE_RISKY_WARNINGS_FOR_MSO}")
    set(CMAKE_CXX_FLAGS_DEBUG "/Ob0 /Od /RTC1")
    set(CMAKE_CXX_FLAGS_RELEASE "/GL /guard:cf /Gy /O1 /Oi")

    set(CMAKE_STATIC_LINKER_FLAGS "/nologo /MACHINE:${ARCHITECTURE_NAME}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "/LTCG")

    set(CMAKE_SHARED_LINKER_FLAGS "/nologo /MACHINE:${ARCHITECTURE_NAME} /SUBSYSTEM:console /DEBUG:full /WINMD:no")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/INCREMENTAL /OPT:NOICF,NOREF")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /OPT:ICF,REF /GUARD:cf /LTCG")

    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG ${CMAKE_SHARED_LINKER_FLAGS_DEBUG})
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE ${CMAKE_SHARED_LINKER_FLAGS_RELEASE})
#elseif(CMAKE_CXX_COMPILER_ID IN_LIST "Clang;AppleClang")
#    set(CMAKE_CXX_FLAGS -Wall -Werror -fno-rtti)
else()
    message(FATAL_ERROR "This project does not support the '${CMAKE_CXX_COMPILER_ID}' compiler")
endif()


### External dependencies

include(CTest)
include(NuGet)

# boost
if($ENV{BOOST_ROOT} STREQUAL "")
    nuget(install boost -Version 1.68.0.0 -Framework native -OutputDirectory ${NUGET_ROOT} -NonInteractive)
    set(BOOST_ROOT ${NUGET_ROOT}/boost.1.68.0.0/lib/native)
    list(APPEND PROJECT_COMPILE_DEFINITIONS
        BOOST_ALL_NO_LIB=1
        BOOST_ERROR_CODE_HEADER_ONLY
        BOOST_NO_RTTI
        BOOST_NO_TYPEID
        BOOST_SYSTEM_SOURCE)
else()
    if(EXISTS $ENV{BOOST_ROOT}/lib/native)
        set(BOOST_ROOT $ENV{BOOST_ROOT}/lib/native)
    else()
        set(BOOST_ROOT $ENV{BOOST_ROOT})
    endif()
endif()
file(TO_CMAKE_PATH ${BOOST_ROOT} BOOST_ROOT)
message(STATUS "Boost: ${BOOST_ROOT}")

# Mso
include(FetchContent)
FetchContent_Declare(
    Mso
    GIT_REPOSITORY  https://github.com/microsoft/Mso.git
    GIT_TAG         d1d3cbb9745b9654f3693b001db4a33375d990aa)
message(STATUS "Downloading Mso...")
FetchContent_MakeAvailable(Mso)
list(APPEND PROJECT_COMPILE_DEFINITIONS GTEST_HAS_RTTI=0)


### Project directories

add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
