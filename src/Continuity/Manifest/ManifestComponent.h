#pragma once

#include <string>
#include <vector>

#include <Continuity/ReactManifest.h>
#include <folly/dynamic.h>

#include "stubs/Mso.h"

namespace Microsoft::React
{

class ManifestComponent final : public Mso::RefCountedObject<IManifestComponent>
{
public:
    ManifestComponent(std::string&& name, std::string&& displayName, std::string&& backgroundColor) noexcept;

    const char* GetName() const noexcept override;
    const char* GetDisplayName() const noexcept override;
    const char* GetBackgroundColor() const noexcept override;

private:
    std::string _name;
    std::string _displayName;
    std::string _backgroundColor;
};


/*
 *  Read a component description from the manifest.
 *
 *  The component name uniquely identifies the react-native experience within
 *  the bundle. At runtime, the react-native runtime looks for the component
 *  in a JavaScript registry (AppRegistry.registerComponent). It renders
 *  whatever it finds as the root react-native element.
 *
 *      "RNTesterApp": {   // Component name
 *          "displayName": "React-Native Tester",
 *          "backgroundColor": "#1E90FF"
 *      }
 */
Mso::TCntRef<ManifestComponent> ReadManifestComponent(const folly::dynamic& componentName,
    const folly::dynamic& componentData, ReactError& error) noexcept;


class ManifestComponentCollection final : public Mso::RefCountedObject<IManifestComponentCollection>
{
public:
    ManifestComponentCollection(std::vector<Mso::TCntRef<ManifestComponent>>&& components) noexcept;

    IManifestComponent* FindComponent(const char* name) const noexcept override;

private:
    std::vector<Mso::TCntRef<ManifestComponent>> _components;
};


/*
 *  Read a collection of component descriptions from the manifest.
 *
 *      "components": [ ... ]
 */
Mso::TCntRef<ManifestComponentCollection> ReadManifestComponentCollection(
    const folly::dynamic* collectionData, ReactError& error) noexcept;

}
