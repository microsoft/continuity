list(APPEND HEADERS
    ${INC_ROOT}/ReactNative/SDK/ReactApi.h
    ${INC_ROOT}/ReactNative/SDK/ReactManifest.h)

list(APPEND HEADERS_INTERNAL
    DynamicReader.h
    Manifest/Manifest.h
    Manifest/ManifestBundle.h
    Manifest/ManifestComponent.h
    Manifest/ManifestPackager.h
    Manifest/ManifestRuntime.h
    Manifest/ManifestRuntimeLibrary.h
    Manifest/ManifestRuntimeWin32.h
    Manifest/ManifestRuntimeWin32Container.h
    stubs/Mso.h)

list(APPEND SOURCES
    DynamicReader.cpp
    Manifest/Manifest.cpp
    Manifest/ManifestBundle.cpp
    Manifest/ManifestComponent.cpp
    Manifest/ManifestPackager.cpp
    Manifest/ManifestRuntime.cpp
    Manifest/ManifestRuntimeLibrary.cpp
    Manifest/ManifestRuntimeWin32.cpp
    Manifest/ManifestRuntimeWin32Container.cpp)

add_library(Microsoft.ReactNative.SDK SHARED)

target_sources(Microsoft.ReactNative.SDK
    PUBLIC
        ${HEADERS}
    PRIVATE
        ${HEADERS_INTERNAL}
        ${SOURCES})

target_compile_definitions(Microsoft.ReactNative.SDK
    PRIVATE
        ${PROJECT_COMPILE_DEFINITIONS}
        MICROSOFT_REACT_BUILD)

target_include_directories(Microsoft.ReactNative.SDK
    PUBLIC
        ${INC_ROOT}
    PRIVATE
        ${BOOST_ROOT}/include
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Microsoft.ReactNative.SDK
    PRIVATE
        folly
        Mso::object
        Mso::smartPtr)

target_link_options(Microsoft.ReactNative.SDK
    PUBLIC
        $<$<PLATFORM_ID:Windows>:/DEF:${CMAKE_CURRENT_SOURCE_DIR}/Microsoft.ReactNative.SDK.${PLATFORM}.def>)

install(FILES ${HEADERS}
    DESTINATION include/ReactNative/SDK
    COMPONENT dist)

install(TARGETS Microsoft.ReactNative.SDK
    DESTINATION ${CMAKE_BUILD_TYPE}/${PLATFORM}
    COMPONENT dist)

install(FILES $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/Microsoft.ReactNative.SDK.${PLATFORM}.def>
    DESTINATION ${CMAKE_BUILD_TYPE}/${PLATFORM}
    RENAME Microsoft.ReactNative.SDK.def
    COMPONENT dist)

install(FILES $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_BINARY_DIR}/Microsoft.ReactNative.SDK.pdb>
    DESTINATION ${CMAKE_BUILD_TYPE}/${PLATFORM}
    COMPONENT dist)
