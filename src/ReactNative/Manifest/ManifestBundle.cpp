#include <ReactNative/DynamicReader.h>
#include <ReactNative/Manifest/ManifestBundle.h>

namespace ReactNative::Platform 
{

constexpr const char* const c_BundleFileNameProperty = "fileName";
constexpr const char* const c_BundleFileNameDefault = "main";

constexpr const char* const c_BundleExtensionProperty = "extension";
constexpr const char* const c_BundleExtensionDefault = "bundle";

ManifestBundle ManifestBundle::Create(const folly::dynamic* bundle) noexcept
{
    if (bundle && bundle->isObject())
    {
        return ManifestBundle {
            GetDynamicString(*bundle, c_BundleFileNameProperty, c_BundleFileNameDefault),
            GetDynamicString(*bundle, c_BundleExtensionProperty, c_BundleExtensionDefault)
        };
    }

    //  Provide a default bundle configuration.
    return ManifestBundle{std::string{c_BundleFileNameDefault}, std::string{c_BundleExtensionDefault}};
}

ManifestBundle::ManifestBundle(std::string&& fileName, std::string&& extension) noexcept
    : _fileName{std::move(fileName)}, _extension{std::move(extension)}
{
}

const std::string& ManifestBundle::GetFileName() const noexcept
{
    return _fileName;
}

const std::string& ManifestBundle::GetExtension() const noexcept
{
    return _extension;
}

}
