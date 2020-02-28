
## Download Mso

include(FetchContent)
FetchContent_Declare(
    Mso
    GIT_REPOSITORY  https://github.com/microsoft/Mso.git
    GIT_TAG         d1d3cbb9745b9654f3693b001db4a33375d990aa)
message(STATUS "Downloading Mso...")
FetchContent_MakeAvailable(Mso)

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
    ${INC_ROOT}/React/Manifest/ManifestRuntimeWin32Container.h
)

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
    Manifest/ManifestRuntimeWin32Container.cpp
)

add_library(Microsoft.React SHARED ${HEADERS} ${SOURCES})

target_include_directories(Microsoft.React PUBLIC ${INC_ROOT})

target_link_libraries(Microsoft.React
    PRIVATE
        folly
        Mso::crash
        Mso::smartPtr)
