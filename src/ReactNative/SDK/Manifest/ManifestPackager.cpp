#include "DynamicReader.h"
#include "Manifest/ManifestPackager.h"

namespace Microsoft::ReactNative
{

constexpr const char* const c_PackagerEnvironmentDevelopment = "development";
constexpr const char* const c_PackagerEnvironmentProduction = "production";

constexpr const char* const c_PackagerHostProperty = "host";
constexpr const char* const c_PackagerHostDefault = "localhost:8081";

constexpr const char* const c_PackagerFileNameProperty = "fileName";

constexpr const char* const c_PackagerExtensionProperty = "extension";

constexpr const char* const c_PackagerEnvironmentProperty = "environment";
constexpr PackagerEnvironment c_PackagerEnvironmentDefault = PackagerEnvironment::Development;
constexpr const char* const c_PackagerEnvironmentDefaultString = c_PackagerEnvironmentDevelopment;

constexpr const char* const c_PackagerMinifyProperty = "minify";
constexpr bool c_PackagerMinifyDefault = false;


ManifestPackager::ManifestPackager(std::string&& host, std::string&& fileName,
    std::string&& extension, PackagerEnvironment environment, bool minify) noexcept
    : _host{std::move(host)}, _fileName{std::move(fileName)},
    _extension{std::move(extension)}, _environment{environment}, _minify{minify}
{
}

const char* ManifestPackager::GetHost() const noexcept
{
    return _host.c_str();
}

const char* ManifestPackager::GetFileName() const noexcept
{
    return _fileName.c_str();
}

const char* ManifestPackager::GetExtension() const noexcept
{
    return _extension.c_str();
}

PackagerEnvironment ManifestPackager::GetEnvironment() const noexcept
{
    return _environment;
}

bool ManifestPackager::GetMinify() const noexcept
{
    return _minify;
}


Mso::TCntRef<ManifestPackager> ReadManifestPackager(const folly::dynamic* packagerData,
    const std::string& defaultFileName, const std::string& defaultExtension,
    ReactError& error) noexcept
{
    if (packagerData && packagerData->isObject())
    {
        PackagerEnvironment environment;
        auto environmentValue = GetDynamicString(*packagerData, c_PackagerEnvironmentProperty,
            c_PackagerEnvironmentDefaultString);
        if (environmentValue == c_PackagerEnvironmentDevelopment)
        {
            environment = PackagerEnvironment::Development;
        }
        else if (environmentValue == c_PackagerEnvironmentProduction)
        {
            environment = PackagerEnvironment::Production;
        }
        else
        {
            error = ReactError::ManifestPackagerEnvironmentInvalid;
            return {};
        }

        auto packager = Mso::Make<ManifestPackager>(
            GetDynamicString(*packagerData, c_PackagerHostProperty, c_PackagerHostDefault),
            GetDynamicString(*packagerData, c_PackagerFileNameProperty, defaultFileName.c_str()),
            GetDynamicString(*packagerData, c_PackagerExtensionProperty, defaultExtension.c_str()),
            environment,
            GetDynamicBool(*packagerData, c_PackagerMinifyProperty, c_PackagerMinifyDefault));

        error = ReactError::Success;
        return Mso::TCntRef<ManifestPackager>{*packager.Detach(), false};
    }

    //  Provide a default packager configuration.
    auto packager = Mso::Make<ManifestPackager>(std::string{c_PackagerHostDefault},
        std::string{defaultFileName}, std::string{defaultExtension}, c_PackagerEnvironmentDefault,
        c_PackagerMinifyDefault);

    error = ReactError::Success;
    return Mso::TCntRef<ManifestPackager>{*packager.Detach(), false};
}

}
