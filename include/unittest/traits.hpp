#ifndef UNITTEST_TRAITS_HPP
#define UNITTEST_TRAITS_HPP
#pragma once

#include <type_traits>

namespace unittest {
namespace trait {

using std::integral_constant;
using std::is_same;
using std::declval;

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

template <typename... T> struct is_printable : std::true_type { };

}} /* namespace unittest::trait */

#endif /* UNITTEST_TRAITS_HPP */
