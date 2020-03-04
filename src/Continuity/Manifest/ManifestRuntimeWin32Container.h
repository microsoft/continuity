#pragma once

#include <optional>

#include <Continuity/ReactManifest.h>
#include <folly/dynamic.h>

#include "stubs/Mso.h"

namespace Microsoft::React
{

class ManifestWin32Dialog final : public Mso::RefCountedObject<IManifestWin32Dialog>
{
public:
    ManifestWin32Dialog(std::optional<int64_t>&& width, std::optional<int64_t>&& height,
        bool showOkButton, bool showCancelButton) noexcept;

    bool GetWidth(int64_t& width) const noexcept override;
    bool GetHeight(int64_t& height) const noexcept override;
    bool GetShowOkButton() const noexcept override;
    bool GetShowCancelButton() const noexcept override;

private:
    std::optional<int64_t> _width;
    std::optional<int64_t> _height;
    bool _showOkButton;
    bool _showCancelButton;
};


/*
 *  Read Win32 dialog configuration.
 *
 *      "container": {
 *          "type": "dialog",
 *          "width": 500,
 *          "height": 350,
 *          "showOkButton": true,
 *          "showCancelButton": true
 *      }
 */
Mso::TCntRef<ManifestWin32Dialog> ReadManifestWin32Dialog(
    const folly::dynamic& dialogData) noexcept;


class ManifestWin32TaskPane final : public Mso::RefCountedObject<IManifestWin32TaskPane>
{
public:
    ManifestWin32TaskPane(int64_t msotbid) noexcept;

    int64_t GetMsotbid() const noexcept override;

private:
    int64_t _msotbid;
};


/*
 *  Read Win32 task-pane configuration.
 *
 *      "container": {
 *          "type": "taskpane",
 *          "msotbid": 123
 *      }
 */
Mso::TCntRef<ManifestWin32TaskPane> ReadManifestWin32TaskPane(
    const folly::dynamic& taskPaneData) noexcept;


class ManifestRuntimeWin32Container final : public Mso::RefCountedObject<IManifestRuntimeWin32Container>
{
public:
    ManifestRuntimeWin32Container(Mso::TCntPtr<ManifestWin32Dialog>&& dialog) noexcept;
    ManifestRuntimeWin32Container(Mso::TCntPtr<ManifestWin32TaskPane>&& taskPane) noexcept;

    ManifestWin32ContainerType GetType() const noexcept override;
    IManifestWin32Dialog* GetDialog() const noexcept override;
    IManifestWin32TaskPane* GetTaskPane() const noexcept override;

private:
    Mso::TCntPtr<ManifestWin32Dialog> _dialog;
    Mso::TCntPtr<ManifestWin32TaskPane> _taskPane;
};


/*
 *   Read Win32 runtime container information.
 *
 *       "container": {
 *           "type": "dialog|taskpane"
 *           ... props specific to each type ...
 *       }
 */
Mso::TCntPtr<ManifestRuntimeWin32Container> ReadManifestRuntimeWin32Container(
    const folly::dynamic* containerData, ReactError& error) noexcept;

}
