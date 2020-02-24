#include <React/Error.h>

namespace Microsoft::React
{

void Error::Assign(const char* message) noexcept
{
    _message.emplace(message ? message : "");
}

void Error::Assign(const std::string& message) noexcept
{
    _message.emplace(message);
}

void Error::Assign(std::string&& message) noexcept
{
    _message.emplace(std::move(message));
}

Error::operator bool() const noexcept
{
    return _message.has_value();
}

const std::optional<std::string>& Error::GetMessage() const noexcept
{
    return _message;
}

}
