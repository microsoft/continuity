#pragma once

#include <optional>
#include <string>

namespace ReactNative::Platform
{

class Error final
{
public:
    //	Assign a value to this error, causing it to be "set". This indicates
    //	that a failure has occurred.
    void Assign(const char* message) noexcept;
    void Assign(const std::string& message) noexcept;
    void Assign(std::string&& message) noexcept;

    //	Test to see if a value has been assigned to this error object.
    //	The presence of a value indicates that a failure has occurred.
    explicit operator bool() const noexcept;

    //	Get the message assigned to this error, if any.
    const std::optional<std::string>& GetMessage() const noexcept;

private:
    std::optional<std::string> _message;
};

}
