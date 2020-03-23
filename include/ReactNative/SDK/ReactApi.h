#pragma once

#include <cstdint>


//  Library export

#ifndef MICROSOFT_REACT_EXPORT
#if defined(WIN32)
#if defined(MICROSOFT_REACT_BUILD)
#define MICROSOFT_REACT_EXPORT __declspec(dllexport)
#else // !MICROSOFT_REACT_BUILD
#define MICROSOFT_REACT_EXPORT __declspec(dllimport)
#endif // MICROSOFT_REACT_BUILD
#else // !WIN32
#define MICROSOFT_REACT_EXPORT
#endif // WIN32
#endif // !MICROSOFT_REACT_EXPORT

//  vtable optimization (MSVC++ only)

#ifndef DECLSPEC_NOVTABLE
#if defined(__clang__) || !defined(__cplusplus) || defined(__GNUC__)
#define DECLSPEC_NOVTABLE
#else
#define DECLSPEC_NOVTABLE  __declspec(novtable)
#endif
#endif


//  Error codes

namespace Microsoft::ReactNative
{

enum class ReactError : uint32_t
{
    Success = 0,
    ManifestParse = 1,
    ManifestComponentNameEmpty = 2,
    ManifestComponentInvalid = 3,
    ManifestComponentListInvalid = 4,
    ManifestPackagerEnvironmentInvalid = 5,
    ManifestLibraryNameEmpty = 6,
    ManifestLibraryPathEmpty = 7,
    ManifestLibraryInvalid = 8,
    ManifestRuntimeWin32ContainerInvalidType = 9
};

}


//  API (function) definition

#define MICROSOFT_REACT_API(returnType) extern "C" [[nodiscard]] MICROSOFT_REACT_EXPORT returnType __stdcall


//  reference counted interface

namespace Microsoft::ReactNative
{

struct DECLSPEC_NOVTABLE IRefCounted
{
    virtual void AddRef() const noexcept = 0;
    virtual void Release() const noexcept = 0;
};

}
