#include <React/DynamicReader.h>
#include <React/Manifest/ManifestComponent.h>

namespace Microsoft::React
{

std::optional<ManifestComponent> ManifestComponent::Create(
    const folly::dynamic& componentName, const folly::dynamic& component, Error& error) noexcept
{
    if (!componentName.isString() || componentName.getString().empty())
    {
        error.Assign("Component name must be a non-empty string");
        return std::nullopt;
    }
    auto name = std::string{componentName.getString()};

    if (!component.isObject())
    {
        error.Assign("Invalid component definition");
        return std::nullopt;
    }

    return ManifestComponent{
        std::move(name),
        GetDynamicString(component, "displayName", componentName.getString().c_str()),
        GetDynamicString(component, "backgroundColor", "#ffffff")};
}

ManifestComponent::ManifestComponent(std::string&& name, std::string&& displayName, std::string&& backgroundColor) noexcept
    : _name{std::move(name)}, _displayName{std::move(displayName)}, _backgroundColor{std::move(backgroundColor)}
{
}

const std::string& ManifestComponent::GetName() const noexcept
{
    return _name;
}

const std::string& ManifestComponent::GetDisplayName() const noexcept
{
    return _displayName;
}

const std::string& ManifestComponent::GetBackgroundColor() const noexcept
{
    return _backgroundColor;
}

}
