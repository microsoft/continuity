#pragma once

#include <string>

#include <ReactNative/SDK/ReactManifest.h>
#include <folly/dynamic.h>

#include "stubs/Mso.h"

namespace Microsoft::ReactNative
{

class ManifestBundle final : public Mso::RefCountedObject<IManifestBundle>
{
public:
    ManifestBundle(std::string&& fileName, std::string&& extension) noexcept;

    const char* GetFileName() const noexcept override;
    const char* GetExtension() const noexcept override;

private:
    std::string _fileName;
    std::string _extension;
};


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
Mso::CntPtr<ManifestBundle> ReadManifestBundle(const folly::dynamic* bundleData) noexcept;

}
