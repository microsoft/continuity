list(APPEND HEADERS
    ${INC_ROOT}/React/DynamicReader.h
    ${INC_ROOT}/React/Error.h
    ${INC_ROOT}/React/Manifest/Manifest.h
    ${INC_ROOT}/React/Manifest/ManifestBundle.h
    ${INC_ROOT}/React/Manifest/ManifestComponent.h
    ${INC_ROOT}/React/Manifest/ManifestPackager.h
    ${INC_ROOT}/React/Manifest/ManifestRuntime.h
    ${INC_ROOT}/React/Manifest/ManifestRuntimeLibrary.h
    ${INC_ROOT}/React/Manifest/ManifestRuntimeWin32.h
    ${INC_ROOT}/React/Manifest/ManifestRuntimeWin32Container.h)

list(APPEND SOURCES
    DynamicReader.cpp
    Error.cpp
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
        ${SOURCES})

target_compile_definitions(Microsoft.React
    PRIVATE
        ${PROJECT_COMPILE_DEFINITIONS}
        _HAS_AUTO_PTR_ETC=1)

target_compile_options(Microsoft.React
    PRIVATE
        $<$<PLATFORM_ID:Windows>:/Gz>)

target_include_directories(Microsoft.React
    PUBLIC
        ${INC_ROOT}
    PRIVATE
        ${PROJECT_INCLUDE_DIRECTORIES})

target_link_libraries(Microsoft.React
    PRIVATE
        folly
        Mso::smartPtr)
