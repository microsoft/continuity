# Change Log - @microsoft/continuity

This log was last generated on Wed, 04 Mar 2020 09:02:00 GMT and should not be manually modified.

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