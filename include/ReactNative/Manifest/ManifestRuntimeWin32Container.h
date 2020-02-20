#pragma once

#include <optional>
#include <variant>

#include <folly/dynamic.h>
#include <ReactNative/Error.h>
#include <ReactNative/Manifest/ManifestRuntimeWin32Container.h>

namespace ReactNative::Platform 
{

class ManifestWin32Dialog final
{
public:
    /*
     *  Read Win32 dialog configuration.
     *
     *      "container": {
     *         "type": "dialog",
     *         "width": 500,
     *         "height": 350,
     *         "showOkButton": true,
     *         "showCancelButton": true
     *      }
     */
    static ManifestWin32Dialog Create(const folly::dynamic& dialog) noexcept;

    ManifestWin32Dialog(std::optional<int64_t>&& width, std::optional<int64_t>&& height,
       bool showOkButton, bool showCancelButton) noexcept;

    //  Width of the dialog container in device-independent pixels.
    //  When omitted, width is determined by the layout engine.
    const std::optional<int64_t>& GetWidth() const noexcept;

    //  Height of the dialog container in device-independent pixels.
    //  When omitted, height is determined by the layout engine.
    const std::optional<int64_t>& GetHeight() const noexcept;

    //  Show an 'OK' button on the dialog surface.
    //
    //  @default false
    bool GetShowOkButton() const noexcept;

    //  Show a 'Cancel' button on the dialog surface.
    //
    //  @default false
    bool GetShowCancelButton() const noexcept;

private:
   std::optional<int64_t> _width;
   std::optional<int64_t> _height;
   bool _showOkButton;
   bool _showCancelButton;
};


class ManifestWin32TaskPane final
{
public:
    /*
     *  Read Win32 task-pane configuration.
     *
     *      "container": {
     *         "type": "taskpane",
     *         "msotbid": 123
     *      }
     */
    static ManifestWin32TaskPane Create(const folly::dynamic& taskpane) noexcept;

    ManifestWin32TaskPane(int64_t msotbid) noexcept;

    //  Office toolbar identifier used when displaying a react-native experience
    //  within a task-pane.
    //
    //  @default 1 (msotbidCustom)
    int64_t GetMsotbid() const noexcept;

private:
   int64_t _msotbid;
};


enum class ManifestWin32ContainerType
{
    Dialog,
    TaskPane
};

class ManifestRuntimeWin32Container final
{
public:
    /*
     *  Read Win32 runtime container information.
     *
     *      "container": {
     *          "type": "dialog|taskpane"
     *          ... props specific to each type ...
     *      }
     */
    static std::optional<ManifestRuntimeWin32Container> Create(
        const folly::dynamic* const container, Error& error) noexcept;

    ManifestRuntimeWin32Container(ManifestWin32Dialog&& dialog) noexcept;
    ManifestRuntimeWin32Container(ManifestWin32TaskPane&& taskpane) noexcept;

    //  Type of container to use when rendering the react-native experience.
    ManifestWin32ContainerType GetType() const noexcept;

    //  Dialog container information. Only valid when type is 'Dialog'.
    const std::optional<ManifestWin32Dialog>& GetDialog() const noexcept;

    //  TaskPane container information. Only valid type is 'TaskPane'.
    const std::optional<ManifestWin32TaskPane>& GetTaskPane() const noexcept;

private:
    std::optional<ManifestWin32Dialog> _dialog;
    std::optional<ManifestWin32TaskPane> _taskpane;
};

}
