#include "DynamicReader.h"
#include "ManifestBundle.h"

namespace Microsoft::ReactNative
{

constexpr const char* const c_BundleFileNameProperty = "fileName";
constexpr const char* const c_BundleFileNameDefault = "main";

constexpr const char* const c_BundleExtensionProperty = "extension";
constexpr const char* const c_BundleExtensionDefault = "bundle";

ManifestBundle::ManifestBundle(std::string&& fileName, std::string&& extension) noexcept
    : _fileName{std::move(fileName)}, _extension{std::move(extension)}
{
}

const char* ManifestBundle::GetFileName() const noexcept
{
    return _fileName.c_str();
}

const char* ManifestBundle::GetExtension() const noexcept
{
    return _extension.c_str();
}

Mso::TCntRef<ManifestBundle> ReadManifestBundle(const folly::dynamic* bundleData) noexcept
{
    if (bundleData && bundleData->isObject())
    {
        auto bundle = Mso::Make<ManifestBundle>(
            GetDynamicString(*bundleData, c_BundleFileNameProperty, c_BundleFileNameDefault),
            GetDynamicString(*bundleData, c_BundleExtensionProperty, c_BundleExtensionDefault));
        return Mso::TCntRef<ManifestBundle>{*bundle.Detach(), false};
    }

    //  Provide a default bundle configuration.
    auto bundle = Mso::Make<ManifestBundle>(std::string{c_BundleFileNameDefault},
        std::string{c_BundleExtensionDefault});
    return Mso::TCntRef<ManifestBundle>{*bundle.Detach(), false};
}

}
