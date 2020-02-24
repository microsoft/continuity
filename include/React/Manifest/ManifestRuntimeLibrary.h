#pragma once

#include <optional>
#include <string>

#include <folly/dynamic.h>
#include <React/Error.h>

namespace Microsoft::React
{

class ManifestRuntimeLibrary final
{
public:
    /*
     *  Read the list of JavaScript bundle libraries.
     *
     *  Each library must have a non-empty name, and may also have a path.
     *
     *  Libraries without a path must be "pre-registered" by the host.
     *  Libraries with a path are dynamically loaded, and don't need any registration.
     *
     *      "libraries": [
     *          "CryptoJS",
     *          {
     *              "name": "ColorSpace"
     *          },
     *          {
     *              "name": "DiscreteCosineTransform",
     *              "path": "libraries/DCT.win32.bundle"
     *          }
     *      ]
     */
    static std::optional<ManifestRuntimeLibrary> Create(
        const folly::dynamic& library, Error& error) noexcept;

    ManifestRuntimeLibrary(std::string&& name) noexcept;
    ManifestRuntimeLibrary(std::string&& name, std::string&& path) noexcept;

    //  Name of the library
    const std::string& GetName() const noexcept;

    //  Optional path to the library file. Path must be relative, and will be
    //  resolved using the manifest directory.
    //
    //  When missing, the library path is retrieved from a global list.
    //  The host is responsible for pre-registering the library.
    const std::optional<std::string>& GetPath() const noexcept;

private:
    std::string _name;
    std::optional<std::string> _path;
};

}
