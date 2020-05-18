
### Configuration variables

set(RNSDK_INC_ROOT ${RNSDK_SRC_ROOT}/include)
set(RNSDK_NUGET_ROOT ${RNSDK_BIN_ROOT}/nuget)
file(MAKE_DIRECTORY ${RNSDK_NUGET_ROOT})

set(RNSDK_COMPILE_DEFINITIONS "")

set(RNSDK_COMPILE_FLAGS_MSVC /nologo /EHsc /GR- /GS /permissive- /sdl /utf-8 /W4 /WX /Zi /wd4018 /wd4068 /wd4100 /wd4101 /wd4127 /wd4146 /wd4189 /wd4201 /wd4244 /wd4251 /wd4267 /wd4290 /wd4293 /wd4305 /wd4309 /wd4324 /wd4456 /wd4458 /wd4505 /wd4702 /wd4800 /wd4804)
set(RNSDK_COMPILE_FLAGS_CLANG "")
set(RNSDK_COMPILE_FLAGS_GCC "")

set(RNSDK_COMPILE_FLAGS_MSVC_DEBUG /Ob0 /Od /RTC1)
set(RNSDK_COMPILE_FLAGS_CLANG_DEBUG "")
set(RNSDK_COMPILE_FLAGS_GCC_DEBUG "")

set(RNSDK_COMPILE_FLAGS_MSVC_RELEASE /GL /guard:cf /Gy /O1 /Oi)
set(RNSDK_COMPILE_FLAGS_CLANG_RELEASE "")
set(RNSDK_COMPILE_FLAGS_GCC_RELEASE "")

set(RNSDK_LINK_STATIC_LIBRARY_FLAGS_MSVC /nologo)
set(RNSDK_LINK_STATIC_LIBRARY_FLAGS_CLANG "")
set(RNSDK_LINK_STATIC_LIBRARY_FLAGS_GCC "")

set(RNSDK_LINK_STATIC_LIBRARY_FLAGS_MSVC_DEBUG "")
set(RNSDK_LINK_STATIC_LIBRARY_FLAGS_CLANG_DEBUG "")
set(RNSDK_LINK_STATIC_LIBRARY_FLAGS_GCC_DEBUG "")

set(RNSDK_LINK_STATIC_LIBRARY_FLAGS_MSVC_RELEASE /LTCG)
set(RNSDK_LINK_STATIC_LIBRARY_FLAGS_CLANG_RELEASE "")
set(RNSDK_LINK_STATIC_LIBRARY_FLAGS_GCC_RELEASE "")

set(RNSDK_LINK_SHARED_LIBRARY_FLAGS_MSVC /nologo /SUBSYSTEM:console /DEBUG:full /WINMD:no /minpdbpathlen:256)
set(RNSDK_LINK_SHARED_LIBRARY_FLAGS_CLANG "")
set(RNSDK_LINK_SHARED_LIBRARY_FLAGS_GCC "")

set(RNSDK_LINK_SHARED_LIBRARY_FLAGS_MSVC_DEBUG /INCREMENTAL /OPT:NOICF,NOREF)
set(RNSDK_LINK_SHARED_LIBRARY_FLAGS_CLANG_DEBUG "")
set(RNSDK_LINK_SHARED_LIBRARY_FLAGS_GCC_DEBUG "")

set(RNSDK_LINK_SHARED_LIBRARY_FLAGS_MSVC_RELEASE /INCREMENTAL:NO /OPT:ICF,REF /GUARD:cf /LTCG)
set(RNSDK_LINK_SHARED_LIBRARY_FLAGS_CLANG_RELEASE "")
set(RNSDK_LINK_SHARED_LIBRARY_FLAGS_GCC_RELEASE "")

# Debug, Release
set(RNSDK_TARGET_TYPE "")

# Win32, macOS, iOS, Android
set(RNSDK_TARGET_PLATFORM "")

# x86, x64, arm
set(RNSDK_TARGET_ARCH "")


### Build-type configuration

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    list(APPEND RNSDK_COMPILE_DEFINITIONS
        _DEBUG
        DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    list(APPEND RNSDK_COMPILE_DEFINITIONS
        NDEBUG)
else()
    message(FATAL_ERROR "This project does not support build type '${CMAKE_BUILD_TYPE}'. Only 'Debug' and 'Release' builds are allowed.")
endif()
set(RNSDK_TARGET_TYPE ${CMAKE_BUILD_TYPE})


### System configuration

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(RNSDK_TARGET_PLATFORM Win32)

    # Enforce minimum target version of Windows
    if(CMAKE_SYSTEM_VERSION VERSION_LESS "10.0.15063.0")
        message(FATAL_ERROR "This project does not support target Windows build ${CMAKE_SYSTEM_VERSION}. The oldest allowed Windows build is 10.0.15063.0 (version 1703, Redstone 2).")
    endif()

    # Warn when not using Ninja to generate build scripts
    if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
        message(WARNING "Warning: CMake generator '${CMAKE_GENERATOR}' is not supported for Windows builds, but may work. 'Ninja' is the recommended generator.")
    endif()

    # _WIN32_WINNT_WIN8 = 0x0602
    list(APPEND RNSDK_COMPILE_DEFINITIONS
        WIN32
        _WINDOWS
        WINVER=0x0602
        _WIN32_WINNT=0x0602
        WIN32_LEAN_AND_MEAN
        WINRT_LEAN_AND_MEAN
        NOMINMAX
        _HAS_AUTO_PTR_ETC=1
        GLOG_NO_ABBREVIATED_SEVERITIES
        RN_EXPORT=
        _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
#elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
#    set(RNSDK_TARGET_PLATFORM macOS)
#elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
#    set(RNSDK_TARGET_PLATFORM iOS)
#elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
#    set(RNSDK_TARGET_PLATFORM Android)
else()
    message(FATAL_ERROR "This project does not support the '${CMAKE_SYSTEM_NAME}' system.")
endif()


### Compiler/linker configuration

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Read the target machine architecture for Windows
    if($ENV{VSCMD_ARG_TGT_ARCH} STREQUAL "")
        message(FATAL_ERROR "Error: environment variable VSCMD_ARG_TGT_ARCH is not set (required for Windows builds). Are you using a Visual Studio Tools Command Prompt?")
    endif()
    set(RNSDK_TARGET_ARCH $ENV{VSCMD_ARG_TGT_ARCH})

    # Enforce required platform toolset
    if(NOT MSVC_TOOLSET_VERSION EQUAL 141)
        message(FATAL_ERROR "This project does not support Visual Studio toolset ${MSVC_TOOLSET_VERSION}. It only supports toolset 141 (Visual Studio 2017).")
    endif()

#elseif(CMAKE_CXX_COMPILER_ID IN_LIST "Clang;AppleClang")
#    set(RNSDK_TARGET_ARCH x64)
#elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    set(RNSDK_TARGET_ARCH ???)
else()
    message(FATAL_ERROR "This project does not support the '${CMAKE_CXX_COMPILER_ID}' compiler")
endif()


### Target creation functions

function(_rnsdk_target_compile_options TARGET_NAME)
    target_compile_definitions(${TARGET_NAME}
        PRIVATE
            ${RNSDK_COMPILE_DEFINITIONS})

    target_compile_options(${TARGET_NAME}
        PRIVATE
            $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:
                ${RNSDK_COMPILE_FLAGS_MSVC}
                $<$<CONFIG:Debug>:${RNSDK_COMPILE_FLAGS_MSVC_DEBUG}>
                $<$<CONFIG:Release>:${RNSDK_COMPILE_FLAGS_MSVC_RELEASE}>>
            $<$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang>:
                ${RNSDK_COMPILE_FLAGS_CLANG}
                $<$<CONFIG:Debug>:${RNSDK_COMPILE_FLAGS_CLANG_DEBUG}>
                $<$<CONFIG:Release>:${RNSDK_COMPILE_FLAGS_CLANG_RELEASE}>>
            $<$<COMPILE_LANG_AND_ID:CXX,GNU>:
                ${RNSDK_COMPILE_FLAGS_GCC}
                $<$<CONFIG:Debug>:${RNSDK_COMPILE_FLAGS_GCC_DEBUG}>
                $<$<CONFIG:Release>:${RNSDK_COMPILE_FLAGS_GCC_RELEASE}>>
    )
endfunction()

function(add_rnsdk_static_library LIBRARY_NAME)
    message(STATUS "Adding static library target ${LIBRARY_NAME}")
    add_library(${LIBRARY_NAME} STATIC)

    _rnsdk_target_compile_options(${LIBRARY_NAME})

    target_link_options(${LIBRARY_NAME}
        PRIVATE
            $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:
                ${RNSDK_LINK_STATIC_LIBRARY_FLAGS_MSVC} /MACHINE:${RNSDK_TARGET_ARCH}
                $<$<CONFIG:Debug>:${RNSDK_LINK_STATIC_LIBRARY_FLAGS_MSVC_DEBUG}>
                $<$<CONFIG:Release>:${RNSDK_LINK_STATIC_LIBRARY_FLAGS_MSVC_RELEASE}>>
            $<$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang>:
                ${RNSDK_LINK_STATIC_LIBRARY_FLAGS_CLANG}
                $<$<CONFIG:Debug>:${RNSDK_LINK_STATIC_LIBRARY_FLAGS_CLANG_DEBUG}>
                $<$<CONFIG:Release>:${RNSDK_LINK_STATIC_LIBRARY_FLAGS_CLANG_RELEASE}>>
            $<$<COMPILE_LANG_AND_ID:CXX,GNU>:
                ${RNSDK_LINK_STATIC_LIBRARY_FLAGS_GCC}
                $<$<CONFIG:Debug>:${RNSDK_LINK_STATIC_LIBRARY_FLAGS_GCC_DEBUG}>
                $<$<CONFIG:Release>:${RNSDK_LINK_STATIC_LIBRARY_FLAGS_GCC_RELEASE}>>
    )
endfunction()

function(add_rnsdk_shared_library LIBRARY_NAME)
    message(STATUS "Adding shared library target ${LIBRARY_NAME}")
    add_library(${LIBRARY_NAME} SHARED)

    _rnsdk_target_compile_options(${LIBRARY_NAME})

    target_link_options(${LIBRARY_NAME}
        PRIVATE
            $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:
                ${RNSDK_LINK_SHARED_LIBRARY_FLAGS_MSVC} /MACHINE:${RNSDK_TARGET_ARCH}
                $<$<CONFIG:Debug>:${RNSDK_LINK_SHARED_LIBRARY_FLAGS_MSVC_DEBUG}>
                $<$<CONFIG:Release>:${RNSDK_LINK_SHARED_LIBRARY_FLAGS_MSVC_RELEASE}>>
            $<$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang>:
                ${RNSDK_LINK_SHARED_LIBRARY_FLAGS_CLANG}
                $<$<CONFIG:Debug>:${RNSDK_LINK_SHARED_LIBRARY_FLAGS_CLANG_DEBUG}>
                $<$<CONFIG:Release>:${RNSDK_LINK_SHARED_LIBRARY_FLAGS_CLANG_RELEASE}>>
            $<$<COMPILE_LANG_AND_ID:CXX,GNU>:
                ${RNSDK_LINK_SHARED_LIBRARY_FLAGS_GCC}
                $<$<CONFIG:Debug>:${RNSDK_LINK_SHARED_LIBRARY_FLAGS_GCC_DEBUG}>
                $<$<CONFIG:Release>:${RNSDK_LINK_SHARED_LIBRARY_FLAGS_GCC_RELEASE}>>
    )
endfunction()

function(add_rnsdk_test TEST_NAME)
    message(STATUS "Adding test target ${TEST_NAME}")
    add_executable(${TEST_NAME})

    _rnsdk_target_compile_options(${TEST_NAME})

    target_link_libraries(${TEST_NAME}
        PRIVATE
            gmock
            gtest_main)

    add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)
endfunction()
