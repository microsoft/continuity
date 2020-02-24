#pragma once

#include <optional>
#include <string>

#include <folly/dynamic.h>

namespace Microsoft::React
{

/*
 * Search for a child item in a folly::dynamic container.
 *
 * If the child exists, return a pointer to it. Otherwise, return nullptr.
 */
const folly::dynamic* FindDynamicChild(const folly::dynamic& data, const char* const name) noexcept;

/*
 * Retrieve the named child object from the folly::dynamic container.
 *
 * If the child exists and has type 'object', return a copy of the object.
 * Otherwise, return the default value.
 */
folly::dynamic GetDynamicObject(const folly::dynamic& data, const char* const name, folly::dynamic&& defaultValue) noexcept;

/*
 * Retrieve the named child string from the folly::dynamic container.
 *
 * If the child exists and has type 'string', return a copy of the string.
 * Otherwise, return std::nullopt or the default value.
 */
std::optional<std::string> GetDynamicString(const folly::dynamic& data, const char* const name) noexcept;
std::string GetDynamicString(const folly::dynamic& data, const char* const name, const char* const defaultValue) noexcept;

/*
 * Retrieve the named child double-precision value from the folly::dynamic container.
 *
 * If the child exists and has type 'double', return a copy of the value.
 * Otherwise, return std::nullopt or the default value.
 */
std::optional<double> GetDynamicDouble(const folly::dynamic& data, const char* const name) noexcept;
double GetDynamicDouble(const folly::dynamic& data, const char* const name, double defaultValue) noexcept;

/*
 * Retrieve the named child integer value from the folly::dynamic container.
 *
 * If the child exists and has type 'integer', return a copy of the value.
 * Otherwise, return std::nullopt or the default value.
 */
std::optional<int64_t> GetDynamicInt(const folly::dynamic& data, const char* const name) noexcept;
int64_t GetDynamicInt(const folly::dynamic& data, const char* const name, int64_t defaultValue) noexcept;

/*
 * Retrieve the named child boolean value from the folly::dynamic container.
 *
 * If the child exists and has type 'boolean', return a copy of the value.
 * Otherwise, return the default value.
 */
bool GetDynamicBool(const folly::dynamic& data, const char* const name, bool defaultValue) noexcept;

}
