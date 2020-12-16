# Microsoft React-Native SDK

A platform that makes it easy to blend react-native components into your native application.

## Building

The build is based on [CMake](https://cmake.org) and [Ninja](https://ninja-build.org).

### Windows

_If you already have Visual Studio 2017 installed with C++ tools, skip to step 3._

1. Install Visual Studio 2017 build tools

```
choco install visualstudio2017buildtools
choco install visualstudio2017-workload-vctools
choco install visualstudio2017-workload-universalbuildtools
```

2. Install a [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/sdk-archive). Choose a recent release. Don't go back any farther than `10.0.15063.0` (Spring Creators Update, version 1703).

3. Download [NuGet](https://www.nuget.org/downloads). Choose the command-line version. Add it to your PATH.

4. Run the build

```
scripts\build-windows.cmd
scripts\test-windows.cmd
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

