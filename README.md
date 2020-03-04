# Continuity

Continuity is a platform for using react-native within a native application.

## Building

Continuity uses CMake, and currently builds for Win32 only.

### Prepare the build

Use CMake to generate Ninja build scripts.

```
mkdir Debug
cmake -B Debug -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug

mkdir Release
cmake -B Release -S . -G Ninja -DCMAKE_BUILD_TYPE=Release
```

### Build

Use CMake again to run the build.

```
cmake --build Debug
cmake --build Release
```

The public headers are under `include/React`, and the Win32 DLL is `{Debug|Release}/src/React/Microsoft.React.dll`.

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
