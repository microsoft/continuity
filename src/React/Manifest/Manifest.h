#pragma once

#include <string>

#include <React/ReactManifest.h>

#include "Manifest/ManifestBundle.h"
#include "Manifest/ManifestComponent.h"
#include "Manifest/ManifestPackager.h"
#include "Manifest/ManifestRuntime.h"
#include "stubs/Mso.h"

namespace Microsoft::React
{

class Manifest final : public Mso::RefCountedObject<IManifest>
{
public:
    Manifest(ManifestSource source, Mso::TCntRef<ManifestComponentCollection>&& components,
        Mso::TCntRef<ManifestRuntime>&& runtime, std::string&& assetsPath,
        Mso::TCntRef<ManifestBundle>&& bundle,
        Mso::TCntRef<ManifestPackager>&& packager, std::string&& webDebugHost) noexcept;

    ManifestSource GetSource() const noexcept override;
    IManifestComponentCollection& GetComponents() const noexcept override;
    IManifestRuntime& GetRuntime() const noexcept override;
    const char* GetAssetsPath() const noexcept override;
    IManifestBundle& GetBundle() const noexcept override;
    IManifestPackager& GetPackager() const noexcept override;
    const char* GetWebDebugHost() const noexcept override;

private:
    ManifestSource _source;
    Mso::TCntRef<ManifestComponentCollection> _components;
    Mso::TCntRef<ManifestRuntime> _runtime;
    std::string _assetsPath;
    Mso::TCntRef<ManifestBundle> _bundle;
    Mso::TCntRef<ManifestPackager> _packager;
    std::string _webDebugHost;
};

}
