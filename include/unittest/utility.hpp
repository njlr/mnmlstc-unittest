#ifndef UNITTEST_UTILITY_HPP
#define UNITTEST_UTILITY_HPP
#pragma once

#include <type_traits>

namespace unittest {

template <typename...> struct any_of;
template <typename T, typename... Args>
struct any_of<T, Args...> : std::integral_constant<bool,
  T::value or any_of<Args...>::value
> { };
template <> struct any_of<> : std::false_type { };

template <typename...> struct all_of;
template <typename T, typename... Args>
struct all_of<T, Args...> : std::integral_constant<bool,
  T::value and all_of<Args...>::value
> { };
template <> struct all_of<> : std::true_type { };

template <typename... T>
using enable_if = std::enable_if<all_of<T...>::value>;

} /* namespace unittest */

#endif /* UNITTEST_UTILITY_HPP */
