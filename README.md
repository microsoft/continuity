# Continuity

Continuity is a platform for using react-native within a native application.

## Building

Continuity uses [CMake](https://cmake.org) and [Ninja](https://ninja-build.org).

### Windows

_If you already have Visual Studio 2019 installed with C++ tools, skip to step 3._

1. Install Visual Studio 2019 build tools

```
choco install visualstudio2019buildtools
choco install visualstudio2019-workload-vctools
choco install visualstudio2019-workload-universalbuildtools
```

2. Install a [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/sdk-archive). Choose a recent release. Don't go back any farther than `10.0.15063.0` (Spring Creators Update, version 1703).

3. Download [NuGet](https://www.nuget.org/downloads). Choose the command-line version. Add it to your PATH.

4. Generate Ninja build scripts

```
"%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86

cmake -B build\Debug\x86 -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=CMake\toolchain.windows.cmake
cmake -B build\Release\x86 -S . -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=CMake\toolchain.windows.cmake

"%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64

cmake -B build\Debug\x64 -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=CMake\toolchain.windows.cmake
cmake -B build\Release\x64 -S . -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=CMake\toolchain.windows.cmake
```

5. Run the build

```
"%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86

cmake --build build\Debug\x86
cmake --install build\Debug\x86 --prefix dist --component dist

cmake --build build\Release\x86
cmake --install build\Release\x86 --prefix dist --component dist

"%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64

cmake --build build\Debug\x64
cmake --install build\Debug\x64 --prefix dist --component dist

cmake --build build\Release\x64
cmake --install build\Release\x64 --prefix dist --component dist
```

6. Run tests

```
dist\Debug\x86\ManifestTests
dist\Release\x86\ManifestTests
dist\Debug\x64\ManifestTests
dist\Release\x64\ManifestTests
```

## Contributing

This project welcomes contributions and suggestions. Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.opensource.microsoft.com.

When you submit a pull request, a CLA bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., status check, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
