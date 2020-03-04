#pragma once

#include <Continuity/ReactManifest.h>
#include <folly/dynamic.h>

#include "Manifest/ManifestRuntimeLibrary.h"
#include "Manifest/ManifestRuntimeWin32.h"
#include "stubs/Mso.h"

namespace Microsoft::React
{

class ManifestRuntime final : public Mso::RefCountedObject<IManifestRuntime>
{
public:
    ManifestRuntime(bool devMode, bool attachToWebDebugger, bool liveReload,
        Mso::TCntRef<ManifestRuntimeLibraryCollection>&& libraries,
        bool byteCodeCaching, Mso::TCntPtr<ManifestRuntimeWin32>&& win32) noexcept;

    bool GetDevMode() const noexcept override;
    bool GetAttachToWebDebugger() const noexcept override;
    bool GetLiveReload() const noexcept override;
    IManifestRuntimeLibraryCollection& GetLibraries() const noexcept override;
    bool GetByteCodeCaching() const noexcept override;
    IManifestRuntimeWin32* GetWin32() const noexcept override;

private:
    bool _devMode;
    bool _attachToWebDebugger;
    bool _liveReload;
    Mso::TCntRef<ManifestRuntimeLibraryCollection> _libraries;
    bool _byteCodeCaching;
    Mso::TCntPtr<ManifestRuntimeWin32> _win32;
};


/*
 *  Read runtime configuration for the bundle of react-native experiences.
 *
 *      "runtime": {
 *          "devMode": true,
 *          "attachToWebDebugger": false,
 *          "liveReload": false,
 *          "libraries": [...],
 *          "byteCodeCaching": true,
 *          "win32": {...}
 *      }
 *
 *  If the runtime configuration is invalid or missing, a default configuration
 *  is created. See individual accessors for default values.
 */
Mso::TCntRef<ManifestRuntime> ReadManifestRuntime(const folly::dynamic* runtimeData,
    ReactError& error) noexcept;

}
