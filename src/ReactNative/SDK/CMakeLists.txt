list(APPEND HEADERS
    ${RNSDK_INC_ROOT}/ReactNative/SDK/ReactApi.h
    ${RNSDK_INC_ROOT}/ReactNative/SDK/ReactManifest.h)

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

add_rnsdk_shared_library(react-native-sdk)

target_sources(react-native-sdk
    PUBLIC
        ${HEADERS}
    PRIVATE
        ${HEADERS_INTERNAL}
        ${SOURCES})

target_include_directories(react-native-sdk
    PUBLIC
        ${RNSDK_INC_ROOT}
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
        $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/DEF:${CMAKE_CURRENT_SOURCE_DIR}/react-native-sdk.${RNSDK_TARGET_ARCH}.def>)

install(FILES ${HEADERS}
    DESTINATION include/ReactNative/SDK
    COMPONENT dist)

install(TARGETS react-native-sdk
    DESTINATION ${RNSDK_TARGET_TYPE}/${RNSDK_TARGET_PLATFORM}/${RNSDK_TARGET_ARCH}
    COMPONENT dist)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/react-native-sdk.${RNSDK_TARGET_ARCH}.def
        DESTINATION ${RNSDK_TARGET_TYPE}/${RNSDK_TARGET_PLATFORM}/${RNSDK_TARGET_ARCH}
        RENAME react-native-sdk.def
        COMPONENT dist)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/react-native-sdk.pdb
        DESTINATION ${RNSDK_TARGET_TYPE}/${RNSDK_TARGET_PLATFORM}/${RNSDK_TARGET_ARCH}
        COMPONENT dist)
endif()
