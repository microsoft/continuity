
list(APPEND HEADERS
    ../include/React/DynamicReader.h
    ../include/React/Error.h
    ../include/React/Manifest/Manifest.h
    ../include/React/Manifest/ManifestBundle.h
    ../include/React/Manifest/ManifestComponent.h
    ../include/React/Manifest/ManifestPackager.h
    ../include/React/Manifest/ManifestRuntime.h
    ../include/React/Manifest/ManifestRuntimeLibrary.h
    ../include/React/Manifest/ManifestRuntimeWin32.h
    ../include/React/Manifest/ManifestRuntimeWin32Container.h
)

list(APPEND SOURCES
    React/DynamicReader.cpp
    React/Error.cpp
    React/Manifest/Manifest.cpp
    React/Manifest/ManifestBundle.cpp
    React/Manifest/ManifestComponent.cpp
    React/Manifest/ManifestPackager.cpp
    React/Manifest/ManifestRuntime.cpp
    React/Manifest/ManifestRuntimeLibrary.cpp
    React/Manifest/ManifestRuntimeWin32.cpp
    React/Manifest/ManifestRuntimeWin32Container.cpp
)

add_library(Microsoft.React SHARED ${HEADERS} ${SOURCES})

target_include_directories(Microsoft.React PUBLIC ../include)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADERS})
