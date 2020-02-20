#include <ReactNative/DynamicReader.h>
#include <ReactNative/Manifest/ManifestRuntimeWin32.h>

namespace ReactNative::Platform 
{

constexpr const char* const c_RuntimeWin32ContainerProperty = "container";

std::optional<ManifestRuntimeWin32> ManifestRuntimeWin32::Create(
    const folly::dynamic* const win32, Error& error) noexcept
{
    if (win32 && win32->isObject())
    {
        auto container = ManifestRuntimeWin32Container::Create(FindDynamicChild(*win32, c_RuntimeWin32ContainerProperty), error);
        if (error)
        {
            return std::nullopt;
        }

        return ManifestRuntimeWin32{std::move(container)};
    }

    return std::nullopt;
}

ManifestRuntimeWin32::ManifestRuntimeWin32(
    std::optional<ManifestRuntimeWin32Container>&& container) noexcept
    : _container{std::move(container)}
{
}

const std::optional<ManifestRuntimeWin32Container>& ManifestRuntimeWin32::GetContainer() const noexcept
{
    return _container;
}

}
