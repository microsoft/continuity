#pragma once

#include <optional>
#include <string>

#include <ReactNativePlatformSDK/Error.h>
#include <ReactNativePlatformSDK/Host.h>

namespace Microsoft::React
{

class LIBLET_PUBLICAPI Packager final
{
public:
    /*
     *  Create a packager which can be used to interact with a running react-native
     *  packager (dev) server.
     *
     *  The HTTP implementation is optional. None of the packager methods work
     *  without it, though, as the packager is controlled using HTTP.
     *
     *  You can use this to conditionally control when the packager is available at
     *  runtime. For example, you can restrict the packager to non-shipping builds
     *  because it is a code injection vulnerability.
     */
    Packager(const Mso::TCntPtr<INativeHostHttp>& http, const std::string& host) noexcept;

    //  Probe the packager to see if it is running.
    bool IsRunning() noexcept;

    //  Try to load a react-native manifest using the packager.
    std::optional<std::string> LoadManifest(Error& error) noexcept;

private:
    Mso::TCntPtr<INativeHostHttp> _hostHttp;
    std::string _rootUrl;
};

}
