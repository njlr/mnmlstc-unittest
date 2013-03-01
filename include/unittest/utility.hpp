#ifndef UNITTEST_UTILITY_HPP
#define UNITTEST_UTILITY_HPP
#pragma once

#include <type_traits>
#include <utility>
#include <sstream>
#include <string>
#include <vector>

namespace unittest {

using std::integral_constant;
using std::is_same;
using std::declval;
using std::ostream;

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

namespace trait {

template <typename T>
struct boolean : integral_constant<bool, is_same<T, bool>::value> { };

template <typename T, typename U> void operator == (T const&, U const&);
template <typename T, typename U> void operator != (T const&, U const&);
template <typename T, typename U> void operator >= (T const&, U const&);
template <typename T, typename U> void operator <= (T const&, U const&);
template <typename T, typename U> void operator > (T const&, U const&);
template <typename T, typename U> void operator < (T const&, U const&);

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
class begin {
  template <typename U>
  static decltype(std::begin(declval<U>()), void()) check (int) noexcept;
  template <typename> static void check (...) noexcept(false);
public:
  static constexpr bool value = noexcept(check<T>(0));
};

template <typename T>
class end {
  template <typename U>
  static decltype(std::begin(declval<U>()), void()) check (int) noexcept;
  template <typename> static void check (...) noexcept(false);
public:
  static constexpr bool value = noexcept(check<T>(0));
};

} /* namespace trait */
class unknown_type {
  intptr_t address;
public:
  template <typename T>
  unknown_type (T const& value) :
    address { reinterpret_cast<intptr_t>(std::addressof(value)) }
  { }
  friend ostream& operator << (ostream&, unknown_type const& value);
};

ostream& operator << (ostream& os, unknown_type const& value);

} /* namespace unittest */

#endif /* UNITTEST_UTILITY_HPP */
