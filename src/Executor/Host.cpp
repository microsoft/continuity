#include "precomp.h"

#include <sstream>

#include <ReactNativeHost/MsoSDXQuirks.h>
#include <ReactNativePlatformSDK/Host.h>
#include <ReactNativePlatformSDK/Packager.h>

namespace Microsoft::React
{

std::optional<Mso::React::ReactOptions> MakeReactOptions(const Manifest& manifest,
    const Mso::TCntPtr<INativeHost>& host, Error& error) noexcept
{
    auto loader = host->GetLoader();
    const auto rootPath = loader->TryGetRootPath();

    std::string packagerHost;
    std::string packagerPort;
    if (!manifest.GetPackager().GetHost().empty())
    {
        const auto& hostAndPort = manifest.GetPackager().GetHost();
        const auto pos = hostAndPort.find(':');

        packagerHost = hostAndPort.substr(0, pos);
        if (std::string::npos != pos && (pos + 1) < hostAndPort.size())
        {
            packagerPort = hostAndPort.substr(pos + 1);
        }
    }

    std::optional<Mso::React::ReactOptions> options{std::in_place};

    //  identity ==> name of the bundle file, without the extension
    options->Identity = manifest.GetBundle().GetFileName();

    options->CxxModuleNames = host->GetCxxModuleNames();

    //  bundle file
    if (rootPath)
    {
        //  give RNH the path to the bundle file, making use of any perf
        //  optimizations built into RNH (e.g. memory-mapping).
        options->SDXBasePath = rootPath.value().u8string();
    }
    else
    {
        //  load the bundle and give it to RNH
        std::filesystem::path bundlePath{manifest.GetBundle().GetFileName()};
        bundlePath += ".";
        bundlePath += manifest.GetBundle().GetExtension();

        auto bundle = loader->LoadJSBundle(manifest.GetBundle().GetFileName(), bundlePath, error);
        if (!bundle)
        {
            return std::nullopt;
        }

        options->JSBundles.push_back(bundle);
    }

    //  library files to load into this host's javascript environment
    for (const auto& library : manifest.GetRuntime().GetLibraries())
    {
        if (library.GetPath())
        {
            if (rootPath)
            {
                //  give RNH the path to the library file, making use of
                //  any perf optimizations built into RNH (e.g. memory-mapping)
                const auto libraryPath = rootPath.value() / library.GetPath().value();
                options->AddFileJSBundle(library.GetName(), libraryPath.u8string());
            }
            else
            {
                //  load the library and give it to RNH
                auto libraryBundle = loader->LoadJSBundle(library.GetName(), library.GetPath().value(), error);
                if (!libraryBundle)
                {
                    return std::nullopt;
                }
                options->JSBundles.push_back(libraryBundle);
            }
        }
        else
        {
            options->AddRegisteredJSBundle(library.GetName().c_str());
        }
    }

    options->OnError = [host](const Mso::ErrorCode& errorcode) noexcept
    {
        host->OnMessage(MessageSeverity::Error, errorcode.ToString());
    };

    options->OnLogging = [host](Mso::React::LogLevel logLevel, const char* message) noexcept
    {
        host->OnMessage(logLevel, message);
    };

    options->OnJSException = [host](Mso::React::JSExceptionInfo&& e) noexcept
    {
        if (e.ExceptionType == Mso::React::JSExceptionType::Fatal)
        {
            std::ostringstream message;
            message
                << std::uppercase << std::setfill('0') << std::hex
                << "JavaScript Exception [id " << std::setw(8) << e.ExceptionId << "]: " << e.ToString();

            host->OnMessage(MessageSeverity::Fatal, message.str().c_str());
        }
    };

    options->EnableBytecode = manifest.GetRuntime().GetByteCodeCaching();
    options->Quirks = {
        Mso::React::MsoSdxQuirks::UsedSetQuirkVersionSet()
    };

#ifdef DEBUG
    options->DeveloperSettings.IsDevModeEnabled = manifest.GetRuntime().GetDevMode();
    options->DeveloperSettings.UseDirectDebugger = false;
    options->DeveloperSettings.UseLiveReload = ManifestSource::Packager == manifest.GetSource() || manifest.GetRuntime().GetLiveReload();
    options->DeveloperSettings.UseWebDebugger = manifest.GetRuntime().GetAttachToWebDebugger();
    options->DeveloperSettings.DebugHost = manifest.GetWebDebugHost();
    options->DeveloperSettings.SourceBundleHost = packagerHost;
    options->DeveloperSettings.SourceBundlePort = packagerPort;
    options->DeveloperSettings.SourceBundlePath = manifest.GetPackager().GetFileName();
    options->DeveloperSettings.SourceBundleExtension = manifest.GetPackager().GetExtension();
#endif  // DEBUG

    options->OnInstanceCreated = [host](const Mso::React::IReactInstance& instance)
    {
        std::ostringstream message;
        message << "Created react-native instance '" << instance.Options().Identity << '\'';
        host->OnMessage(MessageSeverity::Info, message.str().c_str());
    };

    options->OnInstanceLoaded = [host](const Mso::React::IReactInstance& instance, const Mso::ErrorCode& errorcode) noexcept
    {
        if (!errorcode)
        {
            std::ostringstream message;
            message << "Loaded bundles for react-native instance '" << instance.Options().Identity << '\'';
            host->OnMessage(MessageSeverity::Info, message.str().c_str());
        }
        else
        {
            std::ostringstream message;
            message << "Failed to load bundles for react-native instance '" << instance.Options().Identity << '\'';
            host->OnMessage(MessageSeverity::Error, message.str().c_str());

            host->OnMessage(MessageSeverity::Error, errorcode.ToString());
        }
    };

    options->OnInstanceDestroyed = [host](const Mso::React::IReactInstance& instance) noexcept
    {
        std::ostringstream message;
        message << "Destroyed react-native instance '" << instance.Options().Identity << '\'';
        host->OnMessage(MessageSeverity::Info, message.str().c_str());
    };

    return options;
}


void LaunchExperience(const std::string& componentName, const std::string& initialProperties,
    const Mso::TCntPtr<INativeHost>& host, const Mso::TCntPtr<INativeHostSurface>& hostSurface,
    Error& error) noexcept
{
    ManifestSource manifestSource;
    std::optional<std::string> manifestContent;

    Packager packager{host->GetHttp(), "localhost:8081"};
    if (packager.IsRunning())
    {
        manifestSource = ManifestSource::Packager;
        manifestContent = packager.LoadManifest(error);
    }
    else
    {
        manifestSource = ManifestSource::Host;
        manifestContent = host->GetLoader()->LoadManifest(error);
    }
    if (!manifestContent)
    {
        return;
    }

    auto manifest = Manifest::Create(manifestSource, *manifestContent, error);
    if (!manifest)
    {
        return;
    }

    auto component = manifest->FindComponent(componentName.c_str());
    if (!component)
    {
        error.Assign("Manifest component not found");
        return;
    }

    auto options = MakeReactOptions(*manifest, host, error);
    if (!options)
    {
        return;
    }

    auto reactHost = Mso::React::MakeReactHost(std::move(options.value()));

    Mso::React::ReactViewOptions viewOptions;
    viewOptions.ComponentName = component->GetName();
    viewOptions.InitialProps = initialProperties;

    hostSurface->Show(host, *manifest, *component, *reactHost, std::move(viewOptions), error);
}

}
