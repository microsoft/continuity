#pragma once

#include <optional>
#include <string>
#include <vector>

#include <folly/dynamic.h>

#include <React/Error.h>
#include <React/Manifest/ManifestBundle.h>
#include <React/Manifest/ManifestComponent.h>
#include <React/Manifest/ManifestPackager.h>
#include <React/Manifest/ManifestRuntime.h>

namespace Microsoft::React
{

enum class ManifestSource
{
    Host,
    Packager
};

/*
 *  A react-native manifest contains a set of react-native experiences, grouped
 *  together under a single JavaScript bundle. The manifest also describes
 *  runtime configuration and native dependencies.
 */
class Manifest final
{
public:
    /*
     *  Read a react-native manifest.
     *
     *      {
     *          "components": {...},
     *          "runtime": {...},
     *          "bundle": {...},
     *          "packager": {...},
     *          "webDebugHost": "localhost:8081",
     *          "assetsPath": "assets"
     *      }
     */
    static std::optional<Manifest> Create(ManifestSource source,
        const std::string& json, Error& error) noexcept;

private:
    static std::optional<std::vector<ManifestComponent>> CreateComponents(
        const folly::dynamic* const components, Error& error) noexcept;

public:
    Manifest(ManifestSource source, std::vector<ManifestComponent>&& components,
        ManifestRuntime&& runtime, std::string&& assetsPath, ManifestBundle&& bundle,
        ManifestPackager&& packager, std::string&& webDebugHost) noexcept;

    //  Source of the manifest content.
    ManifestSource GetSource() const noexcept;

    //  Collection of named components in the manifest. Each maps to a registered
    //  react-native component (AppRegistry.registerComponent).
    const std::vector<ManifestComponent>& GetComponents() const noexcept;

    //	Get a component by name, or nullptr if it was not found.
    const ManifestComponent* FindComponent(const char* const name) const noexcept;

    //	Runtime configuration for the bundle of react-native experiences
    const ManifestRuntime& GetRuntime() const noexcept;

    //  Path to assets (strings, images, icons, ...) referenced by the bundle
    //
    //  @default 'assets'
    const std::string& GetAssetsPath() const noexcept;

    //  Description of the bundle file
    const ManifestBundle& GetBundle() const noexcept;

    //  Packager configuration for the bundle of react-native experiences
    const ManifestPackager& GetPackager() const noexcept;

    //  Host (and optional port) of the web debug server.
    //
    //  @default packager server host/port
    const std::string& GetWebDebugHost() const noexcept;

private:
    ManifestSource _source;
    std::vector<ManifestComponent> _components;
    ManifestRuntime _runtime;
    std::string _assetsPath;
    ManifestBundle _bundle;
    ManifestPackager _packager;
    std::string _webDebugHost;
};

}
