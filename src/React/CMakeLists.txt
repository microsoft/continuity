list(APPEND HEADERS
    ${INC_ROOT}/React/ReactApi.h
    ${INC_ROOT}/React/ReactManifest.h)

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

add_library(Microsoft.React SHARED)

target_sources(Microsoft.React
    PUBLIC
        ${HEADERS}
    PRIVATE
        ${HEADERS_INTERNAL}
        ${SOURCES})

target_compile_definitions(Microsoft.React
    PRIVATE
        ${PROJECT_COMPILE_DEFINITIONS}
        MICROSOFT_REACT_BUILD
        _HAS_AUTO_PTR_ETC=1)

target_compile_options(Microsoft.React
    PRIVATE
        $<$<PLATFORM_ID:Windows>:/Gz>)

target_include_directories(Microsoft.React
    PUBLIC
        ${INC_ROOT}
    PRIVATE
        ${boost_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Microsoft.React
    PRIVATE
        folly
        Mso::object
        Mso::smartPtr)
