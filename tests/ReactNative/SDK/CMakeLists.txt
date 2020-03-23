add_executable(ManifestTests ManifestTests.cpp)

target_compile_definitions(ManifestTests
    PRIVATE
        ${PROJECT_COMPILE_DEFINITIONS})

target_link_libraries(ManifestTests
    PUBLIC
        react-native-sdk
    PRIVATE
        gmock
        gtest_main)

add_test(NAME ManifestTests COMMAND $<TARGET_FILE:ManifestTests>)

install(TARGETS ManifestTests
    DESTINATION ${CMAKE_BUILD_TYPE}/${PLATFORM}
    COMPONENT dist)
