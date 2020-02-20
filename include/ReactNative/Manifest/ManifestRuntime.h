#pragma once

#include <optional>
#include <vector>

#include <folly/dynamic.h>

#include <ReactNative/Error.h>
#include <ReactNative/Manifest/ManifestRuntimeLibrary.h>
#include <ReactNative/Manifest/ManifestRuntimeWin32.h>

namespace ReactNative::Platform
{

class ManifestRuntime final
{
public:
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
    static std::optional<ManifestRuntime> Create(
        const folly::dynamic* const runtime, Error& error) noexcept;

private:
    static std::vector<ManifestRuntimeLibrary> CreateLibraries(
        const folly::dynamic* const manifestLibraries, Error& error) noexcept;

public:
    ManifestRuntime(bool devMode, bool attachToWebDebugger, bool liveReload,
        std::vector<ManifestRuntimeLibrary>&& libraries, bool byteCodeCaching,
        std::optional<ManifestRuntimeWin32>&& win32) noexcept;

    //  Enable developer tools, such as the in-app dev menu and redbox errors.
    //
    //  @default false
    bool GetDevMode() const noexcept;

    //  Attach to a web debugger to load/run react-native experiences.  The debugger
    //  configuration, such as host and port, is in a separate section of the manifest.
    //
    //  @default false
    bool GetAttachToWebDebugger() const noexcept;

    //  Load/run react-native experiences from a packager, rather than a bundle file.
    //  The packager configuration is in a separate section of the manifest.
    //
    //  @default false
    bool GetLiveReload() const noexcept;

    //  List of JavaScript 'library' bundles to load before the main bundle.
    const std::vector<ManifestRuntimeLibrary>& GetLibraries() const noexcept;

    //  Use a cache to store compiled JavaScript byte-code. May improve performance
    //  for successive runs of the same bundle content.
    //
    //  @default true
    bool GetByteCodeCaching() const noexcept;

    //  Optional Win32-specific runtime information.
    const std::optional<ManifestRuntimeWin32>& GetWin32() const noexcept;

private:
    bool _devMode;
    bool _attachToWebDebugger;
    bool _liveReload;
    std::vector<ManifestRuntimeLibrary> _libraries;
    bool _byteCodeCaching;
    std::optional<ManifestRuntimeWin32> _win32;
};

}
