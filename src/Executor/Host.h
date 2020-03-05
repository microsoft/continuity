#pragma once

#include <chrono>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <ReactNativeHost/React.h>
#include <ReactNativePlatformSDK/Error.h>
#include <ReactNativePlatformSDK/Manifest.h>
#include <ReactNativePlatformSDK/ManifestComponent.h>

namespace Microsoft::React
{

using MessageSeverity = Mso::React::LogLevel;

MSO_STRUCT_GUID(INativeHostHttp, "204cbf2a-bc30-4671-9665-c583a9cb7bb2")
struct LIBLET_PUBLICAPI INativeHostHttp : IUnknown
{
    //  Execute an HTTP GET from a URL. On success, return the payload, if any.
    //  On failure, report details using error and return std::nullopt.
    virtual std::optional<std::string> HttpGet(const std::string& url,
        std::chrono::milliseconds timeout, Error& error) noexcept = 0;
};

MSO_STRUCT_GUID(INativeHostLoader, "8cc9f6fc-4f7d-40b2-8b8f-5a1f9a852b20")
struct LIBLET_PUBLICAPI INativeHostLoader : IUnknown
{
    //  Try to get the root directory used by the loader when reading react-native
    //  app files. This is optional. Some loaders may not support it. Providing
    //  access to the filesystem may improve performance.
    virtual std::optional<std::filesystem::path> TryGetRootPath() noexcept = 0;

    //  Load the react-native manifest from the host. On success, return the
    //  manifest content. On failure, report details using error and return
    //  std::nullopt.
    virtual std::optional<std::string> LoadManifest(Error& error) noexcept = 0;

    //  Load a react-native JavaScript bundle from the host. On success, return
    //  the bundle content. On failure, report details using error and return
    //  nullptr.
    virtual Mso::TCntPtr<Mso::React::IJSBundle> LoadJSBundle(
        const std::string& name, const std::filesystem::path& relativePath,
        Error& error) noexcept = 0;
};

MSO_STRUCT_GUID(INativeHost, "8dad7804-5298-4330-aa41-3c2ac953c8e4")
struct LIBLET_PUBLICAPI INativeHost : IUnknown
{
    virtual Mso::TCntPtr<INativeHostHttp> GetHttp() noexcept = 0;
    virtual Mso::TCntPtr<INativeHostLoader> GetLoader() noexcept = 0;

    virtual std::vector<std::string> GetCxxModuleNames() noexcept = 0;

    virtual void OnMessage(MessageSeverity severity, const char* const message) noexcept = 0;
};

MSO_STRUCT_GUID(INativeHostSurface, "173c7f20-4d3f-46c7-9222-6a7251fc42ba")
struct LIBLET_PUBLICAPI INativeHostSurface : IUnknown
{
    virtual void Show(const Mso::TCntPtr<INativeHost>& host, const Manifest& manifest,
        const ManifestComponent& component, Mso::React::IReactHost& reactHost,
        Mso::React::ReactViewOptions&& viewOptions, Error& error) noexcept = 0;
};

LIBLET_PUBLICAPI std::optional<Mso::React::ReactOptions> MakeReactOptions(
    const Manifest& manifest, const Mso::TCntPtr<INativeHost>& host, Error& error) noexcept;

LIBLET_PUBLICAPI void LaunchExperience(const std::string& componentName,
    const std::string& initialProperties, const Mso::TCntPtr<INativeHost>& host,
    const Mso::TCntPtr<INativeHostSurface>& hostSurface, Error& error) noexcept;

}
