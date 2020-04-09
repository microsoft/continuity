#pragma once

#include <string>

#include <ReactNative/SDK/ReactManifest.h>
#include <folly/dynamic.h>

#include "stubs/Mso.h"

namespace Microsoft::ReactNative
{

class ManifestPackager final : public Mso::RefCountedObject<IManifestPackager>
{
public:
    ManifestPackager(std::string&& host, std::string&& fileName, std::string&& extension,
        PackagerEnvironment environment, bool minify) noexcept;

    const char* GetHost() const noexcept override;
    const char* GetFileName() const noexcept override;
    const char* GetExtension() const noexcept override;
    PackagerEnvironment GetEnvironment() const noexcept override;
    bool GetMinify() const noexcept override;

private:
    std::string _host;
    std::string _fileName;
    std::string _extension;
    PackagerEnvironment _environment;
    bool _minify;
};


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
Mso::CntPtr<ManifestPackager> ReadManifestPackager(const folly::dynamic* packagerData,
    const std::string& defaultFileName, const std::string& defaultExtension,
    ReactError& error) noexcept;

}
