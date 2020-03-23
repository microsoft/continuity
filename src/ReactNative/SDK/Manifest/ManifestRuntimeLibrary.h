#pragma once

#include <optional>
#include <string>
#include <vector>

#include <ReactNative/SDK/ReactManifest.h>
#include <folly/dynamic.h>

#include "stubs/Mso.h"

namespace Microsoft::ReactNative
{

class ManifestRuntimeLibrary final : public Mso::RefCountedObject<IManifestRuntimeLibrary>
{
public:
    ManifestRuntimeLibrary(std::string&& name) noexcept;
    ManifestRuntimeLibrary(std::string&& name, std::string&& path) noexcept;

    const char* GetName() const noexcept override;
    const char* GetPath() const noexcept override;

private:
    std::string _name;
    std::optional<std::string> _path;
};


/*
 *  Read a JavaScript bundle library descriptor.
 *
 *  Each library must have a non-empty name, and may also have a path.
 *
 *  Libraries without a path must be "pre-registered" by the host.
 *  Libraries with a path are dynamically loaded, and don't need any registration.
 *
 *          // name only; string
 *          "CryptoJS",
 *
 *          // name only; object
 *          {
 *              "name": "ColorSpace"
 *          }
 *
 *          // name and path
 *          {
 *              "name": "DiscreteCosineTransform",
 *              "path": "libraries/DCT.win32.bundle"
 *          }
 *      ]
 */
Mso::TCntRef<ManifestRuntimeLibrary> ReadManifestRuntimeLibrary(
    const folly::dynamic& libraryData, ReactError& error) noexcept;


class ManifestRuntimeLibraryCollection final : public Mso::RefCountedObject<IManifestRuntimeLibraryCollection>
{
public:
    ManifestRuntimeLibraryCollection(
        std::vector<Mso::TCntRef<ManifestRuntimeLibrary>>&& libraries) noexcept;

    uint32_t GetCount() const noexcept override;
    IManifestRuntimeLibrary* GetLibrary(uint32_t index) const noexcept override;

private:
    std::vector<Mso::TCntRef<ManifestRuntimeLibrary>> _libraries;
};


/*
 *  Read the list of JavaScript bundle libraries.
 *
 *      "libraries": [ ... ]
 */
Mso::TCntRef<ManifestRuntimeLibraryCollection> ReadManifestRuntimeLibraryCollection(
    const folly::dynamic* collectionData, ReactError& error) noexcept;

}
