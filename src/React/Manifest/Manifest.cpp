#include <sstream>

#include <folly/json.h>

#include <React/DynamicReader.h>
#include <React/Manifest/Manifest.h>

namespace Microsoft::React
{

std::optional<Manifest> Manifest::Create(ManifestSource source,
    const std::string& json, Error& error) noexcept
{
    folly::dynamic manifest;
    try
    {
        manifest = folly::parseJson(json);
    }
    catch (const std::exception& e)
    {
        error.Assign(e.what());
        return std::nullopt;
    }

    auto components = CreateComponents(FindDynamicChild(manifest, "components"), error);
    if (error)
    {
        return std::nullopt;
    }

    auto runtime = ManifestRuntime::Create(FindDynamicChild(manifest, "runtime"), error);
    if (error)
    {
        return std::nullopt;
    }

    auto bundle = ManifestBundle::Create(FindDynamicChild(manifest, "bundle"));

    auto packager = ManifestPackager::Create(FindDynamicChild(manifest, "packager"), bundle.GetFileName(), bundle.GetExtension(), error);
    if (error)
    {
        return std::nullopt;
    }

    auto webDebugHost = GetDynamicString(manifest, "webDebugHost", packager->GetHost().c_str());

    return Manifest {
        source,
        std::move(components.value()),
        std::move(runtime.value()),
        GetDynamicString(manifest, "assetsPath", ""),
        std::move(bundle),
        std::move(packager.value()),
        std::move(webDebugHost)
    };
}

std::optional<std::vector<ManifestComponent>> Manifest::CreateComponents(
    const folly::dynamic* const manifestComponents, Error& error) noexcept
{
    if (!manifestComponents || !manifestComponents->isObject())
    {
        error.Assign("Invalid component list definition");
        return std::nullopt;
    }

    std::vector<ManifestComponent> components;

    for (const auto& manifestComponent : manifestComponents->items())
    {
        auto component = ManifestComponent::Create(manifestComponent.first, manifestComponent.second, error);
        if (error)
        {
            return std::nullopt;
        }
        components.push_back(std::move(component.value()));
    }

    return std::optional<std::vector<ManifestComponent>>{std::move(components)};
}

Manifest::Manifest(ManifestSource source, std::vector<ManifestComponent>&& components,
    ManifestRuntime&& runtime, std::string&& assetsPath, ManifestBundle&& bundle,
    ManifestPackager&& packager, std::string&& webDebugHost) noexcept
    : _source{source}, _components{std::move(components)}, _runtime{std::move(runtime)},
    _assetsPath{std::move(assetsPath)}, _bundle{std::move(bundle)},
    _packager{std::move(packager)}, _webDebugHost{std::move(webDebugHost)}
{
}

ManifestSource Manifest::GetSource() const noexcept
{
    return _source;
}

const std::vector<ManifestComponent>& Manifest::GetComponents() const noexcept
{
    return _components;
}

const ManifestComponent* Manifest::FindComponent(const char* const name) const noexcept
{
    auto iter = std::find_if(_components.begin(), _components.end(),
        [name](const ManifestComponent& component) noexcept
        {
            return component.GetName() == name;
        }
    );

    if (_components.end() == iter)
    {
        return nullptr;
    }

    return &(*iter);
}

const ManifestRuntime& Manifest::GetRuntime() const noexcept
{
    return _runtime;
}

const std::string& Manifest::GetAssetsPath() const noexcept
{
    return _assetsPath;
}

const ManifestBundle& Manifest::GetBundle() const noexcept
{
    return _bundle;
}

const ManifestPackager& Manifest::GetPackager() const noexcept
{
    return _packager;
}

const std::string& Manifest::GetWebDebugHost() const noexcept
{
    return _webDebugHost;
}

}
