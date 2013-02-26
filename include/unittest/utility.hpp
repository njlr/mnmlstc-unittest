#ifndef UNITTEST_UTILITY_HPP
#define UNITTEST_UTILITY_HPP
#pragma once

#include <type_traits>
#include <utility>
#include <sstream>
#include <string>

namespace unittest {

using std::integral_constant;
using std::is_same;
using std::declval;
using std::ostream;

namespace trait {

template <typename T>
struct boolean : integral_constant<bool, is_same<T, bool>::value> { };

template <typename T, typename U> void operator == (T const&, U const&);
template <typename T, typename U> void operator != (T const&, U const&);
template <typename T, typename U> void operator >= (T const&, U const&);
template <typename T, typename U> void operator <= (T const&, U const&);
template <typename T, typename U> void operator > (T const&, U const&);
template <typename T, typename U> void operator < (T const&, U const&);

template <typename T> void operator << (ostream&, T const&);

template <typename T, typename U>
struct eq : boolean<decltype(declval<T>() == declval<U>())> { };

template <typename T, typename U>
struct ne : boolean<decltype(declval<T>() != declval<U>())> { };

template <typename T, typename U>
struct ge : boolean<decltype(declval<T>() >= declval<U>())> { };

template <typename T, typename U>
struct le : boolean<decltype(declval<T>() <= declval<U>())> { };

template <typename T, typename U>
struct gt : boolean<decltype(declval<T>() > declval<U>())> { };

template <typename T, typename U>
struct lt : boolean<decltype(declval<T>() < declval<U>())> { };

template <typename T>
struct streamable : integral_constant<bool,
  is_same<decltype(declval<ostream>() << declval<T>()), ostream&>::value
> { };

} /* namespace trait */

template <typename T>
auto repr (T const& value) noexcept -> typename std::enable_if<
  trait::streamable<T>::value,
std::string>::type {
  std::ostringstream stream;
  stream << value;
  return stream.str();
}

template <typename T>
auto repr (T const& value) noexcept -> typename std::enable_if<
  not trait::streamable<T>::value,
std::string>::type {
  std::ostringstream stream;
  stream << "<object at " << std::hex << std::addressof(value) << ">";
  return stream.str();
}

template <typename...> struct any_of;
template <typename T, typename... Args>
struct any_of<T, Args...> : integral_constant<bool,
  T::value or any_of<Args...>::value
> { };
template <> struct any_of<> : std::false_type { };

template <typename...> struct all_of;
template <typename T, typename... Args>
struct all_of<T, Args...> : integral_constant<bool,
  T::value and all_of<Args...>::value
> { };
template <> struct all_of<> : std::true_type { };

template <typename... T>
using disable_if = std::enable_if<not all_of<T...>::value>;

template <typename... T>
using enable_if = std::enable_if<all_of<T...>::value>;

} /* namespace unittest */

#endif /* UNITTEST_UTILITY_HPP */
