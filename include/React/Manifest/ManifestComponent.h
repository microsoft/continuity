#pragma once

#include <string>

#include <folly/dynamic.h>

#include <React/Error.h>

namespace Microsoft::React
{

class ManifestComponent final
{
public:
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
    static std::optional<ManifestComponent> Create(
        const folly::dynamic& componentName, const folly::dynamic& component, Error& error) noexcept;

    ManifestComponent(std::string&& name, std::string&& displayName, std::string&& backgroundColor) noexcept;

    //  Name of the registered react-native component (AppRegistry.registerComponent)
    //  which is the root of the react-native experience.
    const std::string& GetName() const noexcept;

    //  Display name to show when referring to the component
    //
    //  @default component name
    const std::string& GetDisplayName() const noexcept;

    //  Background color to use when rendering the component, in #rgb or #rrggbb form
    //
    //  @default #ffffff (white)
    const std::string& GetBackgroundColor() const noexcept;

private:
    std::string _name;
    std::string _displayName;
    std::string _backgroundColor;
};

}
