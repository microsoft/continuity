#include "precomp.h"

//  must be first
#include <msoFolly/msoFolly.h>

#include <ReactNativePlatformSDK/Packager.h>

using namespace std::literals::chrono_literals;

namespace Microsoft::React
{

Packager::Packager(const Mso::TCntPtr<INativeHostHttp>& hostHttp, const std::string& host) noexcept
    : _hostHttp{hostHttp}
{
    _rootUrl.assign("http://");
    _rootUrl.append(host);
}

bool Packager::IsRunning() noexcept
{
    if (!_hostHttp)
    {
        return false;
    }

    auto url = _rootUrl + "/status";
    Error error;
    auto response = _hostHttp->HttpGet(url, 30s, error);
    if (error)
    {
        return false;
    }

    return "packager-status:running" == *response;
}

std::optional<std::string> Packager::LoadManifest(Error& error) noexcept
{
    if (!_hostHttp)
    {
        error.Assign("HTTP provider was not given");
        return std::nullopt;
    }

    auto url = _rootUrl + "/app.json";
    auto json = _hostHttp->HttpGet(url, 30s, error);
    if (error)
    {
        return std::nullopt;
    }

    return json;
}

}
