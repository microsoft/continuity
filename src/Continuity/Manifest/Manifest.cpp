#include <folly/dynamic.h>
#include <folly/json.h>

#include "DynamicReader.h"
#include "Manifest/Manifest.h"

namespace Microsoft::React
{

Manifest::Manifest(ManifestSource source, Mso::TCntRef<ManifestComponentCollection>&& components,
    Mso::TCntRef<ManifestRuntime>&& runtime, std::string&& assetsPath,
    Mso::TCntRef<ManifestBundle>&& bundle,
    Mso::TCntRef<ManifestPackager>&& packager, std::string&& webDebugHost) noexcept
    :   _source{source}, _components{std::move(components)}, _runtime{std::move(runtime)},
        _assetsPath{std::move(assetsPath)}, _bundle{std::move(bundle)}, _packager{std::move(packager)},
        _webDebugHost{std::move(webDebugHost)}
{
}

ManifestSource Manifest::GetSource() const noexcept
{
    return _source;
}

IManifestComponentCollection& Manifest::GetComponents() const noexcept
{
    return _components.Get();
}

IManifestRuntime& Manifest::GetRuntime() const noexcept
{
    return _runtime.Get();
}

const char* Manifest::GetAssetsPath() const noexcept
{
    return _assetsPath.c_str();
}

IManifestBundle& Manifest::GetBundle() const noexcept
{
    return _bundle.Get();
}

IManifestPackager& Manifest::GetPackager() const noexcept
{
    return _packager.Get();
}

const char* Manifest::GetWebDebugHost() const noexcept
{
    return _webDebugHost.c_str();
}

MICROSOFT_REACT_API(ReactError) ReadManifest(ManifestSource source, const char* json, IManifest** manifest) noexcept
{
    *manifest = nullptr;

    folly::dynamic manifestData;
    try
    {
        manifestData = folly::parseJson(json);
    }
    catch (const std::exception&)
    {
        return ReactError::ManifestParse;
    }

    ReactError error;

    auto components = ReadManifestComponentCollection(FindDynamicChild(manifestData, "components"), error);
    if (ReactError::Success != error)
    {
        return error;
    }

    auto runtime = ReadManifestRuntime(FindDynamicChild(manifestData, "runtime"), error);
    if (ReactError::Success != error)
    {
        return error;
    }

    auto bundle = ReadManifestBundle(FindDynamicChild(manifestData, "bundle"));

    auto packager = ReadManifestPackager(FindDynamicChild(manifestData, "packager"),
        bundle->GetFileName(), bundle->GetExtension(), error);
    if (ReactError::Success != error)
    {
        return error;
    }

    auto webDebugHost = GetDynamicString(manifestData, "webDebugHost", packager->GetHost());

    auto manifestObject = Mso::Make<Manifest, IManifest>(source, std::move(components),
        std::move(runtime), GetDynamicString(manifestData, "assetsPath", ""),
        std::move(bundle), std::move(packager), std::move(webDebugHost));

    *manifest = manifestObject.Detach();
    return ReactError::Success;
}

}
