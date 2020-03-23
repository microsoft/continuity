#include "DynamicReader.h"
#include "Manifest/ManifestRuntime.h"

namespace Microsoft::ReactNative
{

constexpr const char* const c_RuntimeDevModeProperty = "devMode";
constexpr bool c_RuntimeDevModeDefault = false;

constexpr const char* const c_RuntimeAttachToWebDebuggerProperty = "attachToWebDebugger";
constexpr bool c_RuntimeAttachToWebDebuggerDefault = false;

constexpr const char* const c_RuntimeLiveReloadProperty = "liveReload";
constexpr bool c_RuntimeLiveReloadDefault = false;

constexpr const char* const c_RuntimeLibrariesProperty = "libraries";

constexpr const char* const c_RuntimeByteCodeCachingProperty = "byteCodeCaching";
constexpr bool c_RuntimeByteCodeCachingDefault = true;

constexpr const char* const c_RuntimeWin32Property = "win32";


ManifestRuntime::ManifestRuntime(bool devMode, bool attachToWebDebugger, bool liveReload,
    Mso::TCntRef<ManifestRuntimeLibraryCollection>&& libraries,
    bool byteCodeCaching, Mso::TCntPtr<ManifestRuntimeWin32>&& win32) noexcept
    : _devMode{devMode}, _attachToWebDebugger{attachToWebDebugger}, _liveReload{liveReload},
    _libraries{std::move(libraries)}, _byteCodeCaching{byteCodeCaching},
    _win32{std::move(win32)}
{
}

bool ManifestRuntime::GetDevMode() const noexcept
{
    return _devMode;
}

bool ManifestRuntime::GetAttachToWebDebugger() const noexcept
{
    return _attachToWebDebugger;
}

bool ManifestRuntime::GetLiveReload() const noexcept
{
    return _liveReload;
}

IManifestRuntimeLibraryCollection& ManifestRuntime::GetLibraries() const noexcept
{
    return _libraries.Get();
}

bool ManifestRuntime::GetByteCodeCaching() const noexcept
{
    return _byteCodeCaching;
}

IManifestRuntimeWin32* ManifestRuntime::GetWin32() const noexcept
{
    return _win32.Get();
}


Mso::TCntRef<ManifestRuntime> ReadManifestRuntime(const folly::dynamic* runtimeData,
    ReactError& error) noexcept
{
    if (runtimeData && runtimeData->isObject())
    {
        auto libraries = ReadManifestRuntimeLibraryCollection(
            FindDynamicChild(*runtimeData, c_RuntimeLibrariesProperty), error);
        if (ReactError::Success != error)
        {
            return {};
        }

        auto win32 = ReadManifestRuntimeWin32(FindDynamicChild(*runtimeData, c_RuntimeWin32Property), error);
        if (ReactError::Success != error)
        {
            return {};
        }

        auto runtime = Mso::Make<ManifestRuntime>(
            GetDynamicBool(*runtimeData, c_RuntimeDevModeProperty, c_RuntimeDevModeDefault),
            GetDynamicBool(*runtimeData, c_RuntimeAttachToWebDebuggerProperty, c_RuntimeAttachToWebDebuggerDefault),
            GetDynamicBool(*runtimeData, c_RuntimeLiveReloadProperty, c_RuntimeLiveReloadDefault),
            std::move(libraries),
            GetDynamicBool(*runtimeData, c_RuntimeByteCodeCachingProperty, c_RuntimeByteCodeCachingDefault),
            std::move(win32));

        error = ReactError::Success;
        return Mso::TCntRef<ManifestRuntime>{*runtime.Detach(), false};
    }

    //	Provide a default runtime configuration.
    auto runtime = Mso::Make<ManifestRuntime>(
        c_RuntimeDevModeDefault, c_RuntimeAttachToWebDebuggerDefault,
        c_RuntimeLiveReloadDefault, Mso::TCntRef<ManifestRuntimeLibraryCollection>{},
        c_RuntimeByteCodeCachingDefault, Mso::TCntPtr<ManifestRuntimeWin32>{});

    error = ReactError::Success;
    return Mso::TCntRef<ManifestRuntime>{*runtime.Detach(), false};
}

}
