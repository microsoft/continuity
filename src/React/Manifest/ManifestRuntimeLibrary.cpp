#include <React/DynamicReader.h>
#include <ReactNativePlatformSDK/ManifestRuntimeLibrary.h>

namespace Microsoft::React
{

constexpr const char* const c_RuntimeLibraryNameProperty = "name";

constexpr const char* const c_RuntimeLibraryPathProperty = "path";


std::optional<ManifestRuntimeLibrary> ManifestRuntimeLibrary::Create(
    const folly::dynamic& library, Error& error) noexcept
{
    if (library.isString())
    {
        auto name = std::string{library.asString()};
        if (name.empty())
        {
            error.Assign("Runtime library name cannot be empty");
            return std::nullopt;
        }

        return ManifestRuntimeLibrary{std::move(name)};
    }

    if (library.isObject())
    {
        auto name = GetDynamicString(library, c_RuntimeLibraryNameProperty, "");
        if (name.empty())
        {
            error.Assign("Runtime library name cannot be empty");
            return std::nullopt;
        }

        const auto* pathObject = FindDynamicChild(library, c_RuntimeLibraryPathProperty);
        if (pathObject && pathObject->isString())
        {
            if (pathObject->getString().empty())
            {
                error.Assign("Runtime library path cannot be empty");
                return std::nullopt;
            }

            return ManifestRuntimeLibrary{std::move(name), std::string{pathObject->getString()}};
        }

        return ManifestRuntimeLibrary{std::move(name)};
    }

    error.Assign("Invalid runtime library definition");
    return std::nullopt;
}

ManifestRuntimeLibrary::ManifestRuntimeLibrary(std::string&& name) noexcept
    : _name{std::move(name)}
{
}

ManifestRuntimeLibrary::ManifestRuntimeLibrary(std::string&& name, std::string&& path) noexcept
    : _name{std::move(name)}, _path{std::move(path)}
{
}

const std::string& ManifestRuntimeLibrary::GetName() const noexcept
{
    return _name;
}

const std::optional<std::string>& ManifestRuntimeLibrary::GetPath() const noexcept
{
    return _path;
}

}
