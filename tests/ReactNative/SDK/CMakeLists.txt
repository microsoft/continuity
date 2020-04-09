
add_rnsdk_test(ManifestTests)

target_sources(ManifestTests PRIVATE ManifestTests.cpp)

target_link_libraries(ManifestTests PUBLIC react-native-sdk)

install(TARGETS ManifestTests
    DESTINATION ${RNSDK_TARGET_TYPE}/${RNSDK_TARGET_PLATFORM}/${RNSDK_TARGET_ARCH}
    COMPONENT dist)
