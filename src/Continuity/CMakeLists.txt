list(APPEND HEADERS
    ${INC_ROOT}/Continuity/ReactApi.h
    ${INC_ROOT}/Continuity/ReactManifest.h)

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

add_library(Continuity SHARED)

target_sources(Continuity
    PUBLIC
        ${HEADERS}
    PRIVATE
        ${HEADERS_INTERNAL}
        ${SOURCES})

target_compile_definitions(Continuity
    PRIVATE
        ${PROJECT_COMPILE_DEFINITIONS}
        MICROSOFT_REACT_BUILD)

target_include_directories(Continuity
    PUBLIC
        ${INC_ROOT}
    PRIVATE
        ${BOOST_ROOT}/include
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Continuity
    PRIVATE
        folly
        Mso::object
        Mso::smartPtr)

target_link_options(Continuity
    PUBLIC
        $<$<PLATFORM_ID:Windows>:/DEF:${CMAKE_CURRENT_SOURCE_DIR}/Continuity.${PLATFORM}.def>)
