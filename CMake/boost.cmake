# Boost is special because it doesn't use CMake as its build system.
#
# CMake has special handling for finding a boost build (FindBoost module).
# CMake assumes that when it finds boost, everything will already be built.
#
# Using what it finds (or doesn't find), CMake will set vars indicating how 
# much of boost is available. Other libraries, like Folly, depend on these 
# vars during CMake's build-script generation.
#
# To make this all work, Boost must be downloaded, unpacked, and built before
# allowing CMake to proceed. This is done using a separate, blocking run of CMake.

set(BOOST_PROJECT_VERSION 1.71.0)
set(BOOST_PROJECT_FILE_EXT .tar.gz)
set(BOOST_PROJECT_FILE_SHA256 96b34f7468f26a141f6020efb813f1a2f3dfb9797ecf76a7d7cbd843cc95f5bd)

## ------------------------

string(REPLACE "." "_" BOOST_PROJECT_FILE_STEM "boost_${BOOST_PROJECT_VERSION}")
set(BOOST_PROJECT_FILE "${BOOST_PROJECT_FILE_STEM}.tar.gz")
string(TOLOWER ${BOOST_PROJECT_FILE_SHA256} BOOST_PROJECT_FILE_SHA256)
set(BOOST_PROJECT_URL "https://dl.bintray.com/boostorg/release/${BOOST_PROJECT_VERSION}/source/${BOOST_PROJECT_FILE}")

file(TO_CMAKE_PATH "${CMAKE_BINARY_DIR}/boost" BOOST_PROJECT_BINARY_DIR)
file(MAKE_DIRECTORY ${BOOST_PROJECT_BINARY_DIR})

set(BOOST_PROJECT_DOWNLOAD_FILE ${BOOST_PROJECT_BINARY_DIR}/${BOOST_PROJECT_FILE})

file(TO_CMAKE_PATH "${CMAKE_SOURCE_DIR}/extern" BOOST_PROJECT_EXTERN_DIR)
set(BOOST_PROJECT_SOURCE_DIR ${BOOST_PROJECT_EXTERN_DIR}/${BOOST_PROJECT_FILE_STEM})

file(TO_NATIVE_PATH "${BOOST_PROJECT_BINARY_DIR}" BOOST_PROJECT_B2_OUTPUT_DIR)

## Download & Verify

if(NOT BOOST_PROJECT_DOWNLOADED)
    if(EXISTS ${BOOST_PROJECT_DOWNLOAD_FILE})
        message(VERBOSE "Found previously downloaded Boost archive")
        message(VERBOSE "   path=${BOOST_PROJECT_DOWNLOAD_FILE}")

        file(SHA256 ${BOOST_PROJECT_DOWNLOAD_FILE} BOOST_PROJECT_FILE_SHA256_ACTUAL)
        string(TOLOWER ${BOOST_PROJECT_FILE_SHA256_ACTUAL} BOOST_PROJECT_FILE_SHA256_ACTUAL)
        if(NOT BOOST_PROJECT_FILE_SHA256 STREQUAL BOOST_PROJECT_FILE_SHA256_ACTUAL)
            message(VERBOSE "Boost archive hash did not match the expected value")
            message(VERBOSE "   expected=${BOOST_PROJECT_FILE_SHA256}")
            message(VERBOSE "     actual=${BOOST_PROJECT_FILE_SHA256_ACTUAL}")

            message(VERBOSE "Removing untrusted archive file")
            file(REMOVE ${BOOST_PROJECT_DOWNLOAD_FILE})
        else()
            message(VERBOSE "Boost archive hash successfully verified")
        endif()
    endif()

    if(NOT EXISTS ${BOOST_PROJECT_DOWNLOAD_FILE})
        message(STATUS "Downloading Boost ${BOOST_PROJECT_VERSION}...")
        file(DOWNLOAD ${BOOST_PROJECT_URL} ${BOOST_PROJECT_DOWNLOAD_FILE}
            INACTIVITY_TIMEOUT 30
            STATUS BOOST_PROJECT_DOWNLOAD_STATUS
            TIMEOUT 300
            EXPECTED_HASH SHA256=${BOOST_PROJECT_FILE_SHA256}
            TLS_VERIFY ON)
        list(POP_FRONT ${BOOST_PROJECT_DOWNLOAD_STATUS} 
            BOOST_PROJECT_DOWNLOAD_STATUS_CODE 
            BOOST_PROJECT_DOWNLOAD_STATUS_MESSAGE)
        if(NOT ${BOOST_PROJECT_DOWNLOAD_STATUS_CODE} EQUAL 0)
            message(FATAL_ERROR "Failed with error ${BOOST_PROJECT_DOWNLOAD_STATUS_CODE}: ${BOOST_PROJECT_DOWNLOAD_STATUS_MESSAGE}")
        endif()
    endif()

    message(VERBOSE "Marking Boost archive as downloaded and verified")
    set(BOOST_PROJECT_DOWNLOADED TRUE CACHE BOOL "Has the Boost archive been downloaded and verified?" FORCE)
endif()

## Unpack

if(NOT BOOST_PROJECT_UNPACKED)
    if (EXISTS ${BOOST_PROJECT_SOURCE_DIR})
        message(STATUS "Cleaning up from a previous unpack operation...")
        message(VERBOSE "   removing path ${BOOST_PROJECT_SOURCE_DIR}")
        file(REMOVE_RECURSE "${BOOST_PROJECT_SOURCE_DIR}")
    endif()

    message(STATUS "Unpacking Boost (this may take a few minutes)...")
    file(MAKE_DIRECTORY ${BOOST_PROJECT_SOURCE_DIR})
    execute_process(COMMAND "${CMAKE_COMMAND}" -E tar xfz "${BOOST_PROJECT_DOWNLOAD_FILE}" "${BOOST_PROJECT_FILE_STEM}"
        WORKING_DIRECTORY "${BOOST_PROJECT_EXTERN_DIR}"
        RESULT_VARIABLE BOOST_PROJECT_UNPACK_STATUS_CODE
        COMMAND_ECHO STDOUT)
    if(NOT BOOST_PROJECT_UNPACK_STATUS_CODE EQUAL 0)
        message(FATAL_ERROR "Boost unpack failed with error ${BOOST_PROJECT_UNPACK_STATUS_CODE}")
    endif()

    message(VERBOSE "Marking Boost as unpacked")
    set(BOOST_PROJECT_UNPACKED TRUE CACHE BOOL "Has the Boost archive been unpacked?" FORCE)
endif()

## Build

set(BOOST_PROJECT_ADDRESS_MODEL 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BOOST_PROJECT_ADDRESS_MODEL 64)
endif()

if(WIN32)
    set(BOOST_PROJECT_SHELL_COMMAND cmd /c)
    set(BOOST_PROJECT_BOOTSTRAP_APP .\\bootstrap.bat)
    set(BOOST_PROJECT_BUILD_APP .\\b2.exe)
elseif(UNIX)
    set(BOOST_PROJECT_SHELL_COMMAND sh -c)
    set(BOOST_PROJECT_BOOTSTRAP_APP ./bootstrap.sh)
    set(BOOST_PROJECT_BUILD_APP ./b2)
endif()

if(NOT BOOST_PROJECT_BOOTSTRAPPED)
    message(STATUS "Boost: bootstrapping the build...")
    execute_process(COMMAND ${BOOST_PROJECT_SHELL_COMMAND} ${BOOST_PROJECT_BOOTSTRAP_APP}
        WORKING_DIRECTORY ${BOOST_PROJECT_SOURCE_DIR}
        RESULT_VARIABLE BOOST_PROJECT_BOOTSTRAP_RESULT
        COMMAND_ECHO STDOUT)
    if(NOT BOOST_PROJECT_BOOTSTRAP_RESULT EQUAL 0)
        message(FATAL_ERROR "Boost bootstrap failed with error ${BOOST_PROJECT_BOOTSTRAP_RESULT}")
    endif()

    message(VERBOSE "Marking Boost as bootstrapped")
    set(BOOST_PROJECT_BOOTSTRAPPED TRUE CACHE BOOL "Has the Boost build been bootstrapped?" FORCE)
endif()

if(NOT BOOST_PROJECT_BUILT)
    message(STATUS "Boost: building debug ${BOOST_PROJECT_ADDRESS_MODEL}-bit...")
    execute_process(COMMAND ${BOOST_PROJECT_SHELL_COMMAND} ${BOOST_PROJECT_BUILD_APP} --without-test --build-dir=${BOOST_PROJECT_B2_OUTPUT_DIR} variant=debug address-model=${BOOST_PROJECT_ADDRESS_MODEL} stage
        WORKING_DIRECTORY ${BOOST_PROJECT_SOURCE_DIR}
        RESULT_VARIABLE BOOST_PROJECT_BUILD_RESULT
        COMMAND_ECHO STDOUT)
    if(NOT BOOST_PROJECT_BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "Boost build failed with error ${BOOST_PROJECT_BUILD_RESULT}")
    endif()

    message(VERBOSE "Marking Boost as built")
    set(BOOST_PROJECT_BUILT TRUE CACHE BOOL "Has Boost been built?" FORCE)
endif()

## Configure CMake for importing boost

set(BOOST_ROOT ${BOOST_PROJECT_SOURCE_DIR})
set(Boost_NO_SYSTEM_PATHS ON)
