#pragma once

#include <Continuity/ReactApi.h>

namespace Microsoft::React
{

struct IManifestBundle : IRefCounted
{
    //  Name of the bundle file, without an extension
    //
    //  @default 'main'
    virtual const char* GetFileName() const noexcept = 0;

    //  Extension of the bundle file, without a leading '.'
    //
    //  @default 'bundle' [Windows, Android]
    //  @default 'jsbundle' [Apple]
    virtual const char* GetExtension() const noexcept = 0;
};


struct IManifestComponent : IRefCounted
{
    //  Name of the registered react-native component (AppRegistry.registerComponent)
    //  which is the root of the react-native experience.
    virtual const char* GetName() const noexcept = 0;

    //  Display name to show when referring to the component
    //
    //  @default component name
    virtual const char* GetDisplayName() const noexcept = 0;

    //  Background color to use when rendering the component, in #rgb or #rrggbb form
    //
    //  @default #ffffff (white)
    virtual const char* GetBackgroundColor() const noexcept = 0;
};


struct IManifestComponentCollection : IRefCounted
{
    //  Get a component by name, or nullptr if it was not found.
    virtual IManifestComponent* FindComponent(const char* name) const noexcept = 0;
};


enum class PackagerEnvironment : uint32_t
{
    Development,
    Production
};


struct IManifestPackager : IRefCounted
{
    //  Host and (optional) port of the packager server
    //
    //  @default 'localhost:8081'
    virtual const char* GetHost() const noexcept = 0;

    //  Name and extension of the bundle file  to load from the packager server.
    //  These typically match the on-disk bundle file, and will be set to it by
    //  default if omitted from the manifest.
    //
    //  @default bundle file name/extension
    virtual const char* GetFileName() const noexcept = 0;
    virtual const char* GetExtension() const noexcept = 0;

    //  Environment in which the bundle runs. Modeled after NODE_ENV.
    //
    //  'Development' uses very little caching, and exhibits much more logging.
    //  This makes the live-reload and debugging experiences better.
    //
    //  'Production' is the opposite. Content is aggressively cached, and logging
    //  is all but disabled.
    //
    //  @default 'Development'
    virtual PackagerEnvironment GetEnvironment() const noexcept = 0;

    //  When true, the packager produces a minified bundle. Code is condensed
    //  using various techniques, including removal of whitespace, variable
    //  name shortening, and inlining.
    //
    //  @default false
    virtual bool GetMinify() const noexcept = 0;
};


struct IManifestRuntimeLibrary : IRefCounted
{
    //  Name of the library
    virtual const char* GetName() const noexcept = 0;

    //  Optional path to the library file. Path must be relative, and will be
    //  resolved using the manifest directory.
    //
    //  When missing, the library path is retrieved from a global list.
    //  The host is responsible for pre-registering the library.
    virtual const char* GetPath() const noexcept = 0;
};


struct IManifestRuntimeLibraryCollection : IRefCounted
{
    //  Get the count of library entries.
    virtual uint32_t GetCount() const noexcept = 0;

    //  Retrieve the library entry at the given 0-based index, or nullptr if the index is out of range.
    virtual IManifestRuntimeLibrary* GetLibrary(uint32_t index) const noexcept = 0;
};


enum class ManifestWin32ContainerType : uint32_t
{
    Dialog,
    TaskPane
};


struct IManifestWin32Dialog : IRefCounted
{
    //  Width of the dialog container in device-independent pixels.
    //  When omitted, width is determined by the layout engine.
    //  Returns true when the width was set, false otherwise.
    virtual bool GetWidth(int64_t& width) const noexcept = 0;

    //  Height of the dialog container in device-independent pixels.
    //  When omitted, height is determined by the layout engine.
    //  Returns true when the height was set, false otherwise.
    virtual bool GetHeight(int64_t& height) const noexcept = 0;

    //  Show an 'OK' button on the dialog surface.
    //
    //  @default false
    virtual bool GetShowOkButton() const noexcept = 0;

    //  Show a 'Cancel' button on the dialog surface.
    //
    //  @default false
    virtual bool GetShowCancelButton() const noexcept = 0;
};


struct IManifestWin32TaskPane : IRefCounted
{
    //  Office toolbar identifier used when displaying a react-native experience
    //  within a task-pane.
    //
    //  @default 1 (msotbidCustom)
    virtual int64_t GetMsotbid() const noexcept = 0;
};


struct IManifestRuntimeWin32Container : IRefCounted
{
    //  Type of container to use when rendering the react-native experience.
    virtual ManifestWin32ContainerType GetType() const noexcept = 0;

    //  Dialog container information. Only valid when type is 'Dialog'.
    virtual IManifestWin32Dialog* GetDialog() const noexcept = 0;

    //  TaskPane container information. Only valid type is 'TaskPane'.
    virtual IManifestWin32TaskPane* GetTaskPane() const noexcept = 0;
};


struct IManifestRuntimeWin32 : IRefCounted
{
    //  Description of the Win32 runtime container which will render the
    //  react-native experience.
    virtual IManifestRuntimeWin32Container* GetContainer() const noexcept = 0;
};


struct IManifestRuntime : IRefCounted
{
    //  Enable developer tools, such as the in-app dev menu and redbox errors.
    //
    //  @default false
    virtual bool GetDevMode() const noexcept = 0;

    //  Attach to a web debugger to load/run react-native experiences.  The debugger
    //  configuration, such as host and port, is in a separate section of the manifest.
    //
    //  @default false
    virtual bool GetAttachToWebDebugger() const noexcept = 0;

    //  Load/run react-native experiences from a packager, rather than a bundle file.
    //  The packager configuration is in a separate section of the manifest.
    //
    //  @default false
    virtual bool GetLiveReload() const noexcept = 0;

    //  List of JavaScript 'library' bundles to load before the main bundle.
    virtual IManifestRuntimeLibraryCollection& GetLibraries() const noexcept = 0;

    //  Use a cache to store compiled JavaScript byte-code. May improve performance
    //  for successive runs of the same bundle content.
    //
    //  @default true
    virtual bool GetByteCodeCaching() const noexcept = 0;

    //  Optional Win32-specific runtime information.
    virtual IManifestRuntimeWin32* GetWin32() const noexcept = 0;
};


enum class ManifestSource : uint32_t
{
    Host,
    Packager
};

/*
 *  A react-native manifest contains a set of react-native apps, grouped
 *  together under a single JavaScript bundle. The manifest also describes
 *  runtime configuration and native dependencies.
 */
struct IManifest : IRefCounted
{
    //  Source of the manifest content.
    virtual ManifestSource GetSource() const noexcept = 0;

    //  Collection of named components in the manifest. Each maps to a registered
    //  react-native component (AppRegistry.registerComponent).
    virtual IManifestComponentCollection& GetComponents() const noexcept = 0;

    //  Runtime configuration for the bundle of react-native apps
    virtual IManifestRuntime& GetRuntime() const noexcept = 0;

    //  Path to assets (strings, images, icons, ...) referenced by the bundle
    //
    //  @default 'assets'
    virtual const char* GetAssetsPath() const noexcept = 0;

    //  Description of the bundle file
    virtual IManifestBundle& GetBundle() const noexcept = 0;

    //  Packager configuration for the bundle of react-native experiences
    virtual IManifestPackager& GetPackager() const noexcept = 0;

    //  Host (and optional port) of the web debug server.
    //
    //  @default packager server host/port
    virtual const char* GetWebDebugHost() const noexcept = 0;
};

/*
 *  Read a react-native manifest.
 *
 *      {
 *          "components": {...},
 *          "runtime": {...},
 *          "bundle": {...},
 *          "packager": {...},
 *          "webDebugHost": "localhost:8081",
 *          "assetsPath": "assets"
 *      }
 */
MICROSOFT_REACT_API(ReactError) ReadManifest(ManifestSource source, const char* json, IManifest** manifest) noexcept;

}
