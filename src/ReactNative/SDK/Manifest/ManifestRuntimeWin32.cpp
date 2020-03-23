#include "DynamicReader.h"
#include "Manifest/ManifestRuntimeWin32.h"

namespace Microsoft::ReactNative
{

constexpr const char* const c_RuntimeWin32ContainerProperty = "container";

ManifestRuntimeWin32::ManifestRuntimeWin32(
    Mso::TCntPtr<ManifestRuntimeWin32Container>&& container) noexcept
    : _container{std::move(container)}
{
}

IManifestRuntimeWin32Container* ManifestRuntimeWin32::GetContainer() const noexcept
{
    return _container.Get();
}


Mso::TCntPtr<ManifestRuntimeWin32> ReadManifestRuntimeWin32(const folly::dynamic* win32Data,
    ReactError& error) noexcept
{
    if (win32Data && win32Data->isObject())
    {
        auto container = ReadManifestRuntimeWin32Container(
            FindDynamicChild(*win32Data, c_RuntimeWin32ContainerProperty), error);
        if (ReactError::Success != error)
        {
            return {};
        }

        auto win32 = Mso::Make<ManifestRuntimeWin32>(std::move(container));

        error = ReactError::Success;
        return win32.Get();
    }

    error = ReactError::Success;
    return {};
}

}
