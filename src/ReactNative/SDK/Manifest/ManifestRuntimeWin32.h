#pragma once

#include <ReactNative/SDK/ReactManifest.h>
#include <folly/dynamic.h>

#include "Manifest/ManifestRuntimeWin32Container.h"
#include "stubs/Mso.h"

namespace Microsoft::ReactNative
{

class ManifestRuntimeWin32 final : public Mso::RefCountedObject<IManifestRuntimeWin32>
{
public:
    ManifestRuntimeWin32(Mso::CntPtr<ManifestRuntimeWin32Container>&& container) noexcept;

    IManifestRuntimeWin32Container* GetContainer() const noexcept override;

private:
    Mso::CntPtr<ManifestRuntimeWin32Container> _container;
};


/*
 *  Read Win32 runtime information.
 *
 *      "win32": {
 *          "container": {...}
 *      }
 */
Mso::CntPtr<ManifestRuntimeWin32> ReadManifestRuntimeWin32(const folly::dynamic* win32Data,
    ReactError& error) noexcept;

}
