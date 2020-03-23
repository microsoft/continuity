#include <cstring>

#include "DynamicReader.h"
#include "Manifest/ManifestComponent.h"

namespace Microsoft::ReactNative
{

ManifestComponent::ManifestComponent(std::string&& name, std::string&& displayName,
    std::string&& backgroundColor) noexcept
    : _name{std::move(name)}, _displayName{std::move(displayName)},
    _backgroundColor{std::move(backgroundColor)}
{
}

const char* ManifestComponent::GetName() const noexcept
{
    return _name.c_str();
}

const char* ManifestComponent::GetDisplayName() const noexcept
{
    return _displayName.c_str();
}

const char* ManifestComponent::GetBackgroundColor() const noexcept
{
    return _backgroundColor.c_str();
}


Mso::TCntRef<ManifestComponent> ReadManifestComponent(const folly::dynamic& componentName,
    const folly::dynamic& componentData, ReactError& error) noexcept
{
    if (!componentName.isString() || componentName.getString().empty())
    {
        error = ReactError::ManifestComponentNameEmpty;
        return {};
    }
    auto name = std::string{componentName.getString()};

    if (!componentData.isObject())
    {
        error = ReactError::ManifestComponentInvalid;
        return {};
    }

    auto component = Mso::Make<ManifestComponent>(std::move(name),
        GetDynamicString(componentData, "displayName", componentName.getString().c_str()),
        GetDynamicString(componentData, "backgroundColor", "#ffffff"));

    error = ReactError::Success;
    return Mso::TCntRef<ManifestComponent>{*component.Detach(), false};
}


ManifestComponentCollection::ManifestComponentCollection(
    std::vector<Mso::TCntRef<ManifestComponent>>&& components) noexcept
    : _components{std::move(components)}
{
}

uint32_t ManifestComponentCollection::GetCount() const noexcept
{
    return _components.size();
}

IManifestComponent* ManifestComponentCollection::GetComponent(uint32_t index) const noexcept
{
    if (index < _components.size())
    {
        return _components[index].Ptr();
    }
    return nullptr;
}

IManifestComponent* ManifestComponentCollection::FindComponent(
    const char* name) const noexcept
{
    auto iter = std::find_if(_components.begin(), _components.end(),
        [name](const Mso::TCntRef<ManifestComponent>& component) noexcept
        {
            return 0 == std::strcmp(component->GetName(), name);
        }
    );

    if (_components.end() != iter)
    {
        return iter->Ptr();
    }

    return nullptr;
}


Mso::TCntRef<ManifestComponentCollection> ReadManifestComponentCollection(
    const folly::dynamic* collectionData, ReactError& error) noexcept
{
    if (!collectionData || !collectionData->isObject())
    {
        error = ReactError::ManifestComponentListInvalid;
        return {};
    }

    std::vector<Mso::TCntRef<ManifestComponent>> components;

    for (const auto& componentData : collectionData->items())
    {
        auto component = ReadManifestComponent(componentData.first, componentData.second, error);
        if (ReactError::Success != error)
        {
            return {};
        }
        components.push_back(std::move(component));
    }

    auto collection = Mso::Make<ManifestComponentCollection>(std::move(components));

    error = ReactError::Success;
    return Mso::TCntRef<ManifestComponentCollection>{*collection.Detach(), false};
}

}
