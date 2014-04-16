#ifndef UNITTEST_UTILITY_HPP
#define UNITTEST_UTILITY_HPP
#pragma once

#include <type_traits>
#include <iostream>
#include <utility>
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

template <class T, class U>
class eq {
  template <class X, class Y>
  static decltype(declval<X>() == declval<Y>(), void()) check (int) noexcept;
  template <class, class> static void check (...) noexcept(false);
public:
  static constexpr auto value = noexcept(check<T, U>(0));
};

template <class T, class U>
class ne {
  template <class X, class Y>
  static decltype(declval<X>() != declval<Y>(), void()) check (int) noexcept;
  template <class, class> static void check (...) noexcept(false);
public:
  static constexpr auto value = noexcept(check<T, U>(0));
};

template <class T, class U>
class ge {
  template <class X, class Y>
  static decltype(declval<X>() >= declval<Y>(), void()) check (int) noexcept;
  template <class, class> static void check (...) noexcept(false);
public:
  static constexpr auto value = noexcept(check<T, U>(0));
};

template <class T, class U>
class le {
  template <class X, class Y>
  static decltype(declval<X>() <= declval<Y>(), void()) check (int) noexcept;
  template <class, class> static void check (...) noexcept(false);
public:
  static constexpr auto value = noexcept(check<T, U>(0));
};

template <class T, class U>
class gt {
  template <class X, class Y>
  static decltype(declval<X>() > declval<Y>(), void()) check (int) noexcept;
  template <class, class> static void check (...) noexcept(false);
public:
  static constexpr auto value = noexcept(check<T, U>(0));
};

template <class T, class U>
class lt {
  template <class X, class Y>
  static decltype(declval<X>() < declval<Y>(), void()) check (int) noexcept;
  template <class, class> static void check (...) noexcept(false);
public:
  static constexpr auto value = noexcept(check<T, U>(0));
};


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
  static decltype(std::end(declval<U>()), void()) check (int) noexcept;
  template <typename> static void check (...) noexcept(false);
public:
  static constexpr bool value = noexcept(check<T>(0));
};

} /* namespace trait */

inline namespace v1 {

class unknown_type {
  intptr_t address;
public:

  unknown_type (unknown_type const&) = delete;
  unknown_type (unknown_type&&) = delete;
  unknown_type () = delete;

  unknown_type& operator = (unknown_type const&) = delete;
  unknown_type& operator = (unknown_type&&) = delete;

  ~unknown_type () = default;

  template <typename T>
  unknown_type (T const& value) :
    address { reinterpret_cast<intptr_t>(std::addressof(value)) }
  { }

  friend ostream& operator << (ostream&, unknown_type const& value);
};

inline ostream& operator << (ostream& os, unknown_type const& value) {
  return os << "<unknown-type @ "
            << reinterpret_cast<void*>(value.address)
            << ">";
}

inline ostream& operator << (ostream& os, std::nullptr_t) {
  return os << "nullptr";
}

}} /* namespace unittest::v1 */

#endif /* UNITTEST_UTILITY_HPP */
