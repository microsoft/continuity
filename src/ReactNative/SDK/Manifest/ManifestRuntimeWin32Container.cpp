#include "DynamicReader.h"
#include "Manifest/ManifestRuntimeWin32Container.h"

namespace Microsoft::ReactNative
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


ManifestWin32Dialog::ManifestWin32Dialog(std::optional<int64_t>&& width, std::optional<int64_t>&& height,
    bool showOkButton, bool showCancelButton) noexcept
    : _width{std::move(width)}, _height{std::move(height)}, _showOkButton{showOkButton}, _showCancelButton{showCancelButton}
{
}

bool ManifestWin32Dialog::GetWidth(int64_t& width) const noexcept
{
    if (_width)
    {
        width = _width.value();
        return true;
    }
    return false;
}

bool ManifestWin32Dialog::GetHeight(int64_t& height) const noexcept
{
    if (_height)
    {
        height = _height.value();
        return true;
    }
    return false;
}

bool ManifestWin32Dialog::GetShowOkButton() const noexcept
{
    return _showOkButton;
}

bool ManifestWin32Dialog::GetShowCancelButton() const noexcept
{
    return _showCancelButton;
}


Mso::CntPtr<ManifestWin32Dialog> ReadManifestWin32Dialog(
    const folly::dynamic& dialogData) noexcept
{
    auto dialog = Mso::Make<ManifestWin32Dialog>(
        GetDynamicInt(dialogData, c_ManifestWin32DialogWidthProperty),
        GetDynamicInt(dialogData, c_ManifestWin32DialogHeightProperty),
        GetDynamicBool(dialogData, c_ManifestWin32DialogShowOkButtonProperty, c_ManifestWin32DialogShowOkButtonDefault),
        GetDynamicBool(dialogData, c_ManifestWin32DialogShowCancelButtonProperty, c_ManifestWin32DialogShowCancelButtonDefault));
    return Mso::CntPtr<ManifestWin32Dialog>{dialog.Detach(), Mso::AttachTag};
}


ManifestWin32TaskPane::ManifestWin32TaskPane(int64_t msotbid) noexcept
    : _msotbid{msotbid}
{
}

int64_t ManifestWin32TaskPane::GetMsotbid() const noexcept
{
    return _msotbid;
}


Mso::CntPtr<ManifestWin32TaskPane> ReadManifestWin32TaskPane(
    const folly::dynamic& taskPaneData) noexcept
{
    auto taskPane = Mso::Make<ManifestWin32TaskPane>(
        GetDynamicInt(taskPaneData, c_Win32TaskPaneMsotbidProperty, c_Win32TaskPaneMsotbidDefault));
    return Mso::CntPtr<ManifestWin32TaskPane>{taskPane.Detach(), Mso::AttachTag};
}


ManifestRuntimeWin32Container::ManifestRuntimeWin32Container(
    Mso::CntPtr<ManifestWin32Dialog>&& dialog) noexcept
    : _dialog{std::move(dialog)}
{
}

ManifestRuntimeWin32Container::ManifestRuntimeWin32Container(
    Mso::CntPtr<ManifestWin32TaskPane>&& taskPane) noexcept
    : _taskPane{std::move(taskPane)}
{
}

ManifestWin32ContainerType ManifestRuntimeWin32Container::GetType() const noexcept
{
    if (_dialog)
    {
        return ManifestWin32ContainerType::Dialog;
    }
    else if (_taskPane)
    {
        return ManifestWin32ContainerType::TaskPane;
    }

    std::terminate();
}

IManifestWin32Dialog* ManifestRuntimeWin32Container::GetDialog() const noexcept
{
    return _dialog.Get();
}

IManifestWin32TaskPane* ManifestRuntimeWin32Container::GetTaskPane() const noexcept
{
    return _taskPane.Get();
}


Mso::CntPtr<ManifestRuntimeWin32Container> ReadManifestRuntimeWin32Container(
    const folly::dynamic* containerData, ReactError& error) noexcept
{
    if (containerData && containerData->isObject())
    {
        auto type = GetDynamicString(*containerData, c_RuntimeWin32ContainerTypeProperty, "");
        if (type == "dialog")
        {
            auto dialog = ReadManifestWin32Dialog(*containerData);
            auto container = Mso::Make<ManifestRuntimeWin32Container>(dialog.Get());

            error = ReactError::Success;
            return container;
        }

        if (type == "taskpane")
        {
            auto taskPane = ReadManifestWin32TaskPane(*containerData);
            auto container = Mso::Make<ManifestRuntimeWin32Container>(taskPane.Get());

            error = ReactError::Success;
            return container;
        }

        error = ReactError::ManifestRuntimeWin32ContainerInvalidType;
        return {};
    }

    error = ReactError::Success;
    return {};
}

}
