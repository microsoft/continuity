#include <sstream>

#include <ReactNative/DynamicReader.h>
#include <ReactNative/Manifest/ManifestPackager.h>

namespace ReactNative::Platform
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


std::optional<ManifestPackager> ManifestPackager::Create(
    const folly::dynamic* const packager, const std::string& defaultFileName,
    const std::string& defaultExtension, Error& error) noexcept
{
    if (packager && packager->isObject())
    {
        auto environment = StringToPackagerEnvironment(
            GetDynamicString(*packager, c_PackagerEnvironmentProperty, c_PackagerEnvironmentDefaultString),
            error);
        if (error)
        {
            return std::nullopt;
        }

        return ManifestPackager {
            GetDynamicString(*packager, c_PackagerHostProperty, c_PackagerHostDefault),
            GetDynamicString(*packager, c_PackagerFileNameProperty, defaultFileName.c_str()),
            GetDynamicString(*packager, c_PackagerExtensionProperty, defaultExtension.c_str()),
            *environment,
            GetDynamicBool(*packager, c_PackagerMinifyProperty, c_PackagerMinifyDefault)
        };
    }

    //  Provide a default packager configuration.
    return ManifestPackager {
        std::string{c_PackagerHostDefault},
        std::string{defaultFileName},
        std::string{defaultExtension},
        c_PackagerEnvironmentDefault,
        c_PackagerMinifyDefault
    };
}

std::optional<PackagerEnvironment> ManifestPackager::StringToPackagerEnvironment(
    const std::string& environment, Error& error) noexcept
{
    if (environment == c_PackagerEnvironmentDevelopment)
    {
        return PackagerEnvironment::Development;
    }
    if (environment == c_PackagerEnvironmentProduction)
    {
        return PackagerEnvironment::Production;
    }

    error.Assign("Invalid packager environment type");
    return std::nullopt;
}

ManifestPackager::ManifestPackager(std::string&& host, std::string&& fileName, std::string&& extension,
    PackagerEnvironment environment, bool minify) noexcept
    : _host{std::move(host)}, _fileName{std::move(fileName)}, _extension{std::move(extension)},
    _environment{environment}, _minify{minify}
{
}

const std::string& ManifestPackager::GetHost() const noexcept
{
    return _host;
}

const std::string& ManifestPackager::GetFileName() const noexcept
{
    return _fileName;
}

const std::string& ManifestPackager::GetExtension() const noexcept
{
    return _extension;
}

PackagerEnvironment ManifestPackager::GetEnvironment() const noexcept
{
    return _environment;
}

bool ManifestPackager::GetMinify() const noexcept
{
    return _minify;
}

}
