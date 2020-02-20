#include <ReactNative/DynamicReader.h>
#include <ReactNative/Manifest/ManifestRuntime.h>

namespace ReactNative::Platform
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


std::optional<ManifestRuntime> ManifestRuntime::Create(
    const folly::dynamic* const runtime, Error& error) noexcept
{
    if (runtime && runtime->isObject())
    {
        auto libraries = CreateLibraries(FindDynamicChild(*runtime, c_RuntimeLibrariesProperty), error);
        if (error)
        {
            return std::nullopt;
        }

        auto win32 = ManifestRuntimeWin32::Create(FindDynamicChild(*runtime, c_RuntimeWin32Property), error);
        if (error)
        {
            return std::nullopt;
        }

        return ManifestRuntime {
            GetDynamicBool(*runtime, c_RuntimeDevModeProperty, c_RuntimeDevModeDefault),
            GetDynamicBool(*runtime, c_RuntimeAttachToWebDebuggerProperty, c_RuntimeAttachToWebDebuggerDefault),
            GetDynamicBool(*runtime, c_RuntimeLiveReloadProperty, c_RuntimeLiveReloadDefault),
            std::move(libraries),
            GetDynamicBool(*runtime, c_RuntimeByteCodeCachingProperty, c_RuntimeByteCodeCachingDefault),
            std::move(win32)
        };
    }

    //  Provide a default runtime configuration.
    return ManifestRuntime {
        c_RuntimeDevModeDefault,
        c_RuntimeAttachToWebDebuggerDefault,
        c_RuntimeLiveReloadDefault,
        {},
        c_RuntimeByteCodeCachingDefault,
        {}
    };
}

std::vector<ManifestRuntimeLibrary> ManifestRuntime::CreateLibraries(
    const folly::dynamic* const manifestLibraries, Error& error) noexcept
{
    if (manifestLibraries && manifestLibraries->isArray())
    {
        std::vector<ManifestRuntimeLibrary> libraries;

        for (const auto& manifestLibrary : *manifestLibraries)
        {
            auto library = ManifestRuntimeLibrary::Create(manifestLibrary, error);
            if (error)
            {
                return {};
            }
            libraries.push_back(std::move(library.value()));
        }

        return libraries;
    }

    return {};
}

ManifestRuntime::ManifestRuntime(bool devMode, bool attachToWebDebugger, bool liveReload,
    std::vector<ManifestRuntimeLibrary>&& libraries, bool byteCodeCaching,
    std::optional<ManifestRuntimeWin32>&& win32) noexcept
    : _devMode{devMode}, _attachToWebDebugger{attachToWebDebugger}, _liveReload{liveReload},
    _libraries{std::move(libraries)}, _byteCodeCaching{byteCodeCaching}, _win32{std::move(win32)}
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

const std::vector<ManifestRuntimeLibrary>& ManifestRuntime::GetLibraries() const noexcept
{
    return _libraries;
}

bool ManifestRuntime::GetByteCodeCaching() const noexcept
{
    return _byteCodeCaching;
}

const std::optional<ManifestRuntimeWin32>& ManifestRuntime::GetWin32() const noexcept
{
    return _win32;
}

}
