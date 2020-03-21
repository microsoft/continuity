#include <Continuity/ReactManifest.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace Microsoft::React;
using namespace testing;

const char* c_jsonManifest = R"(
{
    "components": {
        "MyApp.app": {
            "displayName": "MyApp",
            "initialProperties": {
                "a": "string prop",
                "b": true,
                "c": 3.1415925,
                "d": {
                    "nested": 88
                }
            }
        }
    },
    "runtime": {
        "devMode": true,
        "liveReload": true,
        "attachToWebDebugger": true,
        "win32": {
            "container": {
                "type": "dialog",
                "width": 450,
                "height": 400,
                "showOkButton": true,
                "showCancelButton": true
            }
        }
    },
    "assetsPath": "assets",
    "bundle": {
        "fileName": "index.win32",
        "extension": "bundle"
    },
    "packager": {
        "host": "localhost:8081"
    }
}
)";


TEST(ManifestTests, ReadManifestSucceeds)
{
    IManifest* manifest = nullptr;
    auto error = ReadManifest(ManifestSource::Host, c_jsonManifest, &manifest);

    ASSERT_EQ(error, ReactError::Success);
    EXPECT_THAT(manifest, NotNull());

    manifest->Release();
}

TEST(ManifestTests, FindExistingComponentSucceeds)
{
    IManifest* manifest = nullptr;
    auto error = ReadManifest(ManifestSource::Host, c_jsonManifest, &manifest);
    ASSERT_EQ(error, ReactError::Success);

    auto component = manifest->GetComponents().FindComponent("MyApp.app");
    EXPECT_THAT(component, NotNull());

    manifest->Release();
}
