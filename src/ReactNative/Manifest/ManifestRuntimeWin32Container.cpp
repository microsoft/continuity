#include <ReactNative/DynamicReader.h>
#include <ReactNative/Manifest/ManifestRuntimeWin32Container.h>

namespace ReactNative::Platform
{

constexpr const char* const c_RuntimeWin32ContainerTypeProperty = "type";

constexpr const char* const c_ManifestWin32DialogWidthProperty = "width";

constexpr const char* const c_ManifestWin32DialogHeightProperty = "height";

constexpr const char* const c_ManifestWin32DialogShowOkButtonProperty = "showOkButton";
constexpr bool c_ManifestWin32DialogShowOkButtonDefault = false;

constexpr const char* const c_ManifestWin32DialogShowCancelButtonProperty = "showCancelButton";
constexpr bool c_ManifestWin32DialogShowCancelButtonDefault = false;

constexpr const char* const c_Win32TaskPaneMsotbidProperty = "msotbid";
constexpr int64_t c_Win32TaskPaneMsotbidDefault = 1;


ManifestWin32Dialog ManifestWin32Dialog::Create(const folly::dynamic& dialog) noexcept
{
    return ManifestWin32Dialog {
        GetDynamicInt(dialog, c_ManifestWin32DialogWidthProperty),
        GetDynamicInt(dialog, c_ManifestWin32DialogHeightProperty),
        GetDynamicBool(dialog, c_ManifestWin32DialogShowOkButtonProperty, c_ManifestWin32DialogShowOkButtonDefault),
        GetDynamicBool(dialog, c_ManifestWin32DialogShowCancelButtonProperty, c_ManifestWin32DialogShowCancelButtonDefault)
    };
}

ManifestWin32Dialog::ManifestWin32Dialog(std::optional<int64_t>&& width, std::optional<int64_t>&& height,
    bool showOkButton, bool showCancelButton) noexcept
    : _width{std::move(width)}, _height{std::move(height)}, _showOkButton{showOkButton}, _showCancelButton{showCancelButton}
{
}

const std::optional<int64_t>& ManifestWin32Dialog::GetWidth() const noexcept
{
    return _width;
}

const std::optional<int64_t>& ManifestWin32Dialog::GetHeight() const noexcept
{
    return _height;
}

bool ManifestWin32Dialog::GetShowOkButton() const noexcept
{
    return _showOkButton;
}

bool ManifestWin32Dialog::GetShowCancelButton() const noexcept
{
    return _showCancelButton;
}


ManifestWin32TaskPane ManifestWin32TaskPane::Create(const folly::dynamic& taskpane) noexcept
{
    return ManifestWin32TaskPane {
        GetDynamicInt(taskpane, c_Win32TaskPaneMsotbidProperty, c_Win32TaskPaneMsotbidDefault)
    };
}

ManifestWin32TaskPane::ManifestWin32TaskPane(int64_t msotbid) noexcept
    : _msotbid{msotbid}
{
}

int64_t ManifestWin32TaskPane::GetMsotbid() const noexcept
{
    return _msotbid;
}

std::optional<ManifestRuntimeWin32Container> ManifestRuntimeWin32Container::Create(
   const folly::dynamic* const container, Error& error) noexcept
{
    if (container && container->isObject())
    {
        auto type = GetDynamicString(*container, c_RuntimeWin32ContainerTypeProperty, "");
        if (type == "dialog")
        {
            return ManifestRuntimeWin32Container{ManifestWin32Dialog::Create(*container)};
        }
        if (type == "taskpane")
        {
            return ManifestRuntimeWin32Container{ManifestWin32TaskPane::Create(*container)};
        }

        error.Assign("Invalid win32 runtime container type");
    }

    return std::nullopt;
}

ManifestRuntimeWin32Container::ManifestRuntimeWin32Container(ManifestWin32Dialog&& dialog) noexcept
    : _dialog{std::move(dialog)}
{
}

ManifestRuntimeWin32Container::ManifestRuntimeWin32Container(ManifestWin32TaskPane&& taskpane) noexcept
    : _taskpane{std::move(taskpane)}
{
}

ManifestWin32ContainerType ManifestRuntimeWin32Container::GetType() const noexcept
{
    if (_dialog)
    {
        return ManifestWin32ContainerType::Dialog;
    }
    else if (_taskpane)
    {
        return ManifestWin32ContainerType::TaskPane;
    }

    std::terminate();
}

const std::optional<ManifestWin32Dialog>& ManifestRuntimeWin32Container::GetDialog() const noexcept
{
    return _dialog;
}

const std::optional<ManifestWin32TaskPane>& ManifestRuntimeWin32Container::GetTaskPane() const noexcept
{
    return _taskpane;
}
}
