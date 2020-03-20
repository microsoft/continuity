add_executable(ManifestTests ManifestTests.cpp)

add_test(NAME ManifestTests COMMAND $<TARGET_FILE:ManifestTests>)

target_link_libraries(ManifestTests
    PUBLIC
        Continuity
    PRIVATE
        gmock
        gtest_main)

install(TARGETS ManifestTests
    DESTINATION ${CMAKE_BUILD_TYPE}/${PLATFORM}
    COMPONENT dist)
