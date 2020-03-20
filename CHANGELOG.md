# Change Log - @microsoft/continuity

This log was last generated on Fri, 20 Mar 2020 22:50:05 GMT and should not be manually modified.

## 1.0.11
Fri, 20 Mar 2020 22:50:05 GMT

### Patches

- Set nuget base path so it picks up the right files. (adam@thefoxmans.net)
## 1.0.10
Fri, 20 Mar 2020 22:00:33 GMT

### Patches

- Add GoogleTest and GoogleMock as a project dependency. Add a ReadManifest unit test. Add CMake install to produce a re-distributable collection of headers and binaries. Update build to use cmake install to generate the distributable image. Include Continuity.pdb. Add a testing stage between build and release. (adam@thefoxmans.net)
- Take a fixed drop of Mso which corrects a packing/alignment header bug. Minor fixes to ManifestTests. (adam@thefoxmans.net)
## 1.0.10
Fri, 20 Mar 2020 22:00:07 GMT

### Patches

- Add GoogleTest and GoogleMock as a project dependency. Add a ReadManifest unit test. Add CMake install to produce a re-distributable collection of headers and binaries. Update build to use cmake install to generate the distributable image. Include Continuity.pdb. Add a testing stage between build and release. (adam@thefoxmans.net)
- Take a fixed drop of Mso which corrects a packing/alignment header bug. Minor fixes to ManifestTests. (adam@thefoxmans.net)
## 1.0.9
Tue, 17 Mar 2020 23:08:59 GMT

### Patches

- Add index-based access to the manifest's component collection. (adam@thefoxmans.net)
## 1.0.8
Tue, 17 Mar 2020 22:32:59 GMT

### Patches

- Add missing compile/link directives. Remove test CI pipeline. Fix build CI pipeline to skip nuget publishing when version has not changed. (adam@thefoxmans.net)
## 1.0.7
Mon, 16 Mar 2020 23:31:30 GMT

### Patches

- add empty line to cause a change (adam@thefoxmans.net)
## 1.0.6
Sat, 14 Mar 2020 10:08:43 GMT

### Patches

- Merge both release jobs together so that the package.json file read is done using the bumped version. (adam@thefoxmans.net)
## 1.0.5
Sat, 14 Mar 2020 09:52:54 GMT

### Patches

- Set the Nuget Artifact Id for CI loop builds (adam@thefoxmans.net)
## 1.0.4
Sat, 14 Mar 2020 09:30:49 GMT

### Patches

- switch to rnbot (adam@thefoxmans.net)
## 1.0.3
Thu, 12 Mar 2020 07:28:05 GMT

### Patches

- Add a .def file for x86 and x64. (adam@thefoxmans.net)
## 1.0.2
Wed, 11 Mar 2020 19:12:38 GMT

### Patches

- Update CI loop definitions and correct variable misuse. Align names in CMake scripts with names in CI loops. (adam@thefoxmans.net)
## 1.0.1
Tue, 10 Mar 2020 09:36:00 GMT

### Patches

- Remove /Gz (__stdcall) from the build because it can't be applied to all dependent libs, and it causes unresolved-externals when pulling in dependent headers. (adam@thefoxmans.net)
## 1.0.0
Wed, 04 Mar 2020 09:02:00 GMT

### Major

- === Build
* Refine build error messages. Remove PROJECT_INCLUDE_DIRECTORIES variable (not worth the complexity).
* Microsoft.React: add explicit dependency on Mso::object to mirror what is used in the code.
* Add CMake build dirs to .gitignore.
* Work around an MSO build issue. Debug builds aren't supported. Suppress debug build defines, include Mso headers, and then restore the defines.

=== Versioning
* Fix beachball integration by making the repo public.
* Change publish command to go through the motions without the final step of pushing to the NPM registry.

=== Manifest Library: ABI
* Split each class into a reference-counted public interface and an internal implementation.
* Use only primitive types and interfaces.
* Replace Error objects with error codes.
* Separate publicly headers for inclusion in NuGet package
* Export public library functions. (adam@thefoxmans.net)