#pragma once

#include <string>

#include <folly/dynamic.h>

namespace Microsoft::React
{

class ManifestBundle final
{
public:
    /*
     *  Read bundle file information from the manifest.
     *
     *      "bundle": {
     *          "fileName": "RNTester.win32",
     *          "extension": "bundle"
     *      }
     *
     *  If bundle info is missing, default bundle info is provided.
     *  See individual accessors for default values.
     */
    static ManifestBundle Create(const folly::dynamic* bundle) noexcept;

    ManifestBundle(std::string&& fileName, std::string&& extension) noexcept;

    //  Name of the bundle file, without an extension
    //
    //  @default 'main'
    const std::string& GetFileName() const noexcept;

    //  Extension of the bundle file, without a leading '.'
    //
    //  @default 'bundle' [Windows, Android]
    //  @default 'jsbundle' [Apple]
    const std::string& GetExtension() const noexcept;

private:
    std::string _fileName;
    std::string _extension;
};

}
