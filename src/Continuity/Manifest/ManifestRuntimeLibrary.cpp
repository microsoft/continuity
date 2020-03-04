#include "DynamicReader.h"
#include "ManifestRuntimeLibrary.h"

namespace Microsoft::React
{

constexpr const char* const c_RuntimeLibraryNameProperty = "name";

constexpr const char* const c_RuntimeLibraryPathProperty = "path";


ManifestRuntimeLibrary::ManifestRuntimeLibrary(std::string&& name) noexcept
    : _name{std::move(name)}
{
}

ManifestRuntimeLibrary::ManifestRuntimeLibrary(std::string&& name, std::string&& path) noexcept
    : _name{std::move(name)}, _path{std::move(path)}
{
}

const char* ManifestRuntimeLibrary::GetName() const noexcept
{
    return _name.c_str();
}

const char* ManifestRuntimeLibrary::GetPath() const noexcept
{
    if (_path)
    {
        return _path->c_str();
    }
    return nullptr;
}


Mso::TCntRef<ManifestRuntimeLibrary> ReadManifestRuntimeLibrary(
    const folly::dynamic& libraryData, ReactError& error) noexcept
{
    if (libraryData.isString())
    {
        auto name = std::string{libraryData.asString()};
        if (name.empty())
        {
            error = ReactError::ManifestLibraryNameEmpty;
            return {};
        }

        auto library = Mso::Make<ManifestRuntimeLibrary>(std::move(name));

        error = ReactError::Success;
        return Mso::TCntRef<ManifestRuntimeLibrary>{*library.Detach(), false};
    }

    if (libraryData.isObject())
    {
        auto name = GetDynamicString(libraryData, c_RuntimeLibraryNameProperty, "");
        if (name.empty())
        {
            error = ReactError::ManifestLibraryNameEmpty;
            return {};
        }

        const auto* pathObject = FindDynamicChild(libraryData, c_RuntimeLibraryPathProperty);
        if (pathObject && pathObject->isString())
        {
            if (pathObject->getString().empty())
            {
                error = ReactError::ManifestLibraryPathEmpty;
                return {};
            }

            auto library = Mso::Make<ManifestRuntimeLibrary>(std::move(name),
                std::string{pathObject->getString()});

            error = ReactError::Success;
            return Mso::TCntRef<ManifestRuntimeLibrary>{*library.Detach(), false};
        }

        auto library = Mso::Make<ManifestRuntimeLibrary>(std::move(name));

        error = ReactError::Success;
        return Mso::TCntRef<ManifestRuntimeLibrary>{*library.Detach(), false};
    }

    error = ReactError::ManifestLibraryInvalid;
    return {};
}


ManifestRuntimeLibraryCollection::ManifestRuntimeLibraryCollection(
    std::vector<Mso::TCntRef<ManifestRuntimeLibrary>>&& libraries) noexcept
    : _libraries{std::move(libraries)}
{
}

uint32_t ManifestRuntimeLibraryCollection::GetCount() const noexcept
{
    return _libraries.size();
}

IManifestRuntimeLibrary* ManifestRuntimeLibraryCollection::GetLibrary(
    uint32_t index) const noexcept
{
    if (index < _libraries.size())
    {
        return _libraries[index].Ptr();
    }
    return nullptr;
}


Mso::TCntRef<ManifestRuntimeLibraryCollection> ReadManifestRuntimeLibraryCollection(
    const folly::dynamic* collectionData, ReactError& error) noexcept
{
    std::vector<Mso::TCntRef<ManifestRuntimeLibrary>> libraries;

    if (collectionData && collectionData->isArray())
    {
        for (const auto& libraryData : *collectionData)
        {
            auto library = ReadManifestRuntimeLibrary(libraryData, error);
            if (ReactError::Success != error)
            {
                return {};
            }
            libraries.push_back(std::move(library));
        }
    }

    auto collection = Mso::Make<ManifestRuntimeLibraryCollection>(std::move(libraries));

    error = ReactError::Success;
    return Mso::TCntRef<ManifestRuntimeLibraryCollection>{*collection.Detach(), false};
}

}
