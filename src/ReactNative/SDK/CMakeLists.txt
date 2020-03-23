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

add_library(react-native-sdk SHARED)

target_sources(react-native-sdk
    PUBLIC
        ${HEADERS}
    PRIVATE
        ${HEADERS_INTERNAL}
        ${SOURCES})

target_compile_definitions(react-native-sdk
    PRIVATE
        ${PROJECT_COMPILE_DEFINITIONS}
        MICROSOFT_REACT_BUILD)

target_include_directories(react-native-sdk
    PUBLIC
        ${INC_ROOT}
    PRIVATE
        ${BOOST_ROOT}/include
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(react-native-sdk
    PRIVATE
        folly
        Mso::object
        Mso::smartPtr)

target_link_options(react-native-sdk
    PUBLIC
        $<$<PLATFORM_ID:Windows>:/DEF:${CMAKE_CURRENT_SOURCE_DIR}/react-native-sdk.${PLATFORM}.def>)

install(FILES ${HEADERS}
    DESTINATION include/ReactNative/SDK
    COMPONENT dist)

install(TARGETS react-native-sdk
    DESTINATION ${CMAKE_BUILD_TYPE}/${PLATFORM}
    COMPONENT dist)

install(FILES $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/react-native-sdk.${PLATFORM}.def>
    DESTINATION ${CMAKE_BUILD_TYPE}/${PLATFORM}
    RENAME react-native-sdk.def
    COMPONENT dist)

install(FILES $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_BINARY_DIR}/react-native-sdk.pdb>
    DESTINATION ${CMAKE_BUILD_TYPE}/${PLATFORM}
    COMPONENT dist)
