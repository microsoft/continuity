#pragma once

#include <string>

#include <ReactNative/SDK/ReactManifest.h>

#include "Manifest/ManifestBundle.h"
#include "Manifest/ManifestComponent.h"
#include "Manifest/ManifestPackager.h"
#include "Manifest/ManifestRuntime.h"
#include "stubs/Mso.h"

namespace Microsoft::ReactNative
{

class Manifest final : public Mso::RefCountedObject<IManifest>
{
public:
    Manifest(ManifestSource source, Mso::CntPtr<ManifestComponentCollection>&& components,
        Mso::CntPtr<ManifestRuntime>&& runtime, std::string&& assetsPath,
        Mso::CntPtr<ManifestBundle>&& bundle,
        Mso::CntPtr<ManifestPackager>&& packager, std::string&& webDebugHost) noexcept;

    ManifestSource GetSource() const noexcept override;
    IManifestComponentCollection& GetComponents() const noexcept override;
    IManifestRuntime& GetRuntime() const noexcept override;
    const char* GetAssetsPath() const noexcept override;
    IManifestBundle& GetBundle() const noexcept override;
    IManifestPackager& GetPackager() const noexcept override;
    const char* GetWebDebugHost() const noexcept override;

private:
    ManifestSource _source;
    Mso::CntPtr<ManifestComponentCollection> _components;
    Mso::CntPtr<ManifestRuntime> _runtime;
    std::string _assetsPath;
    Mso::CntPtr<ManifestBundle> _bundle;
    Mso::CntPtr<ManifestPackager> _packager;
    std::string _webDebugHost;
};

}
