#pragma once

#include <optional>
#include <variant>

#include <folly/dynamic.h>
#include <ReactNative/Error.h>
#include <ReactNative/Manifest/ManifestRuntimeWin32Container.h>

namespace ReactNative::Platform 
{

class ManifestRuntimeWin32 final
{
public:
    /*
     *  Read Win32 runtime information.
     *
     *      "win32": {
     *          "container": {...}
     *      }
     */
    static std::optional<ManifestRuntimeWin32> Create(
        const folly::dynamic* const win32, Error& error) noexcept;

    ManifestRuntimeWin32(std::optional<ManifestRuntimeWin32Container>&& container) noexcept;

    //  Description of the Win32 runtime container which will render the
    //  react-native experience.
    const std::optional<ManifestRuntimeWin32Container>& GetContainer() const noexcept;

private:
    std::optional<ManifestRuntimeWin32Container> _container;
};

}
