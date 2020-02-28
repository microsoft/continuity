#pragma once

#include <string>

#include <folly/dynamic.h>

#include <React/Error.h>

namespace Microsoft::React
{

enum class PackagerEnvironment
{
    Development,
    Production
};

class ManifestPackager final
{
public:
    /*
     *  Read packager configuration from the manifest.
     *
     *      "packager": {
     *          "host": "localhost:8081",
     *          "fileName": "RNTester.win32",
     *          "extension": "bundle",
     *          "environment": "development",
     *          "minify": false
     *      }
     *
     *  If the packager configuration is invalid or missing, a default configuration
     *  is created. See individual accessors for default values.
     */
    static std::optional<ManifestPackager> Create(const folly::dynamic* const packager,
        const std::string& defaultFileName, const std::string& defaultExtension,
        Error& error) noexcept;

private:
    static std::optional<PackagerEnvironment> StringToPackagerEnvironment(
        const std::string& environment, Error& error) noexcept;

public:
    ManifestPackager(std::string&& host, std::string&& fileName, std::string&& extension,
        PackagerEnvironment environment, bool minify) noexcept;

    //  Host and (optional) port of the packager server
    //
    //  @default 'localhost:8081'
    const std::string& GetHost() const noexcept;

    //  Name and extension of the bundle file  to load from the packager server.
    //  These typically match the on-disk bundle file, and will be set to it by
    //  default if omitted from the manifest.
    //
    //  @default bundle file name/extension
    const std::string& GetFileName() const noexcept;
    const std::string& GetExtension() const noexcept;

    //  Environment in which the bundle runs. Modeled after NODE_ENV.
    //
    //  'Development' uses very little caching, and exhibits much more logging.
    //  This makes the live-reload and debugging experiences better.
    //
    //  'Production' is the opposite. Content is aggressively cached, and logging
    //  is all but disabled.
    //
    //  @default 'Development'
    PackagerEnvironment GetEnvironment() const noexcept;

    //  When true, the packager produces a minified bundle. Code is condensed
    //  using various techniques, including removal of whitespace, variable
    //  name shortening, and inlining.
    //
    //  @default false
    bool GetMinify() const noexcept;

private:
    std::string _host;
    std::string _fileName;
    std::string _extension;
    PackagerEnvironment _environment;
    bool _minify;
};

}
