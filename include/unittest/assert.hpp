#ifndef UNITTEST_ASSERT_HPP
#define UNITTEST_ASSERT_HPP

#include <unittest/utility.hpp>
#include <unittest/monitor.hpp>
#include <unittest/error.hpp>

#include <algorithm>
#include <sstream>
#include <utility>
#include <memory>
#include <string>

#include <cstdint>
#include <cmath>

#if defined(assert)
  #undef assert
#endif /* defined(assert) */

namespace unittest {
inline namespace v1 {
namespace assert {
namespace impl {

template <typename T, typename U>
std::string message (T const& first, U const& second, char const* center) {
  std::ostringstream stream;
  stream << first << " " << center << " " << second;
  return stream.str();
}

} /* namespace impl */

/* is_true */
template <typename T>
auto is_true (T const& value) -> typename enable_if<
  std::is_convertible<T, bool>
>::type {
  monitor::increment();
  if (value) { return; }
  throw error { "is-true", impl::message(value, "is not true") };
}

template <typename T>
auto is_true (T const& value) -> typename disable_if<
  std::is_convertible<T, bool>
>::type {
  monitor::increment();
  throw error { "is-true", "Given value is not convertible to bool" };
}

/* is_false */
template <typename T>
auto is_false (T const& value) -> typename enable_if<
  std::is_convertible<T, bool>
>::type {
  monitor::increment();
  if (not value) { return; }
  throw error { "is-false", impl::message(value, "is not false") };
}

template <typename T>
auto is_false (T const& value) -> typename disable_if<
  std::is_convertible<T, bool>
>::type {
  monitor::increment();
  throw error { "is-false", "Given value is not convertible to bool" };
}

/* equal */
template <typename T, typename U>
auto equal (T const& lhs, U const& rhs) -> typename enable_if<
  trait::eq<T, U>
>::type {
  monitor::increment();
  if (lhs == rhs) { return; }
  throw error { "equal", impl::message(lhs, rhs, "is not equal to") };
}

template <typename T, typename U>
auto equal (T const&, U const&) -> typename disable_if<trait::eq<T, U>>::type {
  monitor::increment();
  throw error { "equal", "Given types do not implement operator ==" };
}

/* not-equal */
template <typename T, typename U>
auto not_equal (T const& lhs, U const& rhs) -> typename enable_if<
  trait::ne<T, U>
>::type {
  monitor::increment();
  if (lhs != rhs) { return; }
  throw error { "not-equal", impl::message(lhs, rhs, "is equal to") };
}

template <typename T, typename U>
auto not_equal (T const&, U const&) -> typename disable_if<
  trait::ne<T, U>
>::type {
  monitor::increment();
  throw error { "not-equal", "Given types do not implement operator !=" };
}

/* is */
template <typename T>
void is (T const& lhs, T const& rhs) {
  is(
    reinterpret_cast<intptr_t>(std::addressof(lhs)),
    reinterpret_cast<intptr_t>(std::addressof(rhs))
  );
}

template <typename T>
void is(T const* lhs, T const* rhs) {
  return is(reinterpret_cast<intptr_t>(lhs), reinterpret_cast<intptr_t>(rhs));
}

template<> void is<intptr_t>(intptr_t const& lhs, intptr_t const& rhs) {
  monitor::increment();
  if (lhs == rhs) { return; }
  std::ostringstream stream;
  stream << std::hex << lhs << " is the same as " << rhs;
  throw error { "is", stream.str() };
}

/* is-not */
template <typename T>
void is_not (T const& lhs, T const& rhs) {
  is_not(
    reinterpret_cast<intptr_t>(std::addressof(lhs)),
    reinterpret_cast<intptr_t>(std::addressof(rhs))
  );
}

template <typename T>
void is_not (T* lhs, T* rhs) {
  is_not(reinterpret_cast<intptr_t>(lhs), reinterpret_cast<intptr_t>(rhs));
}

template<> void is_not<intptr_t>(intptr_t const& lhs, intptr_t const& rhs) {
  monitor::increment();
  if (lhs != rhs) { return; }
  std::ostringstream stream;
  stream << std::hex << lhs << " is the same as " << rhs;
  throw error { "is-not", stream.str() };
}

/* is-null */
template <typename T>
void is_null (T const* ptr) {
  monitor::increment();
  if (ptr == nullptr) { return; }
  throw error { "is-null", "Given pointer is not null" };
}

inline void is_null (std::nullptr_t) { monitor::increment(); }

/* is-not-null */
template <typename T>
void is_not_null (T const* ptr) {
  monitor::increment();
  if (ptr) { return; }
  throw error { "is-not-null", "Given pointer is null" };
}

inline void is_not_null (std::nullptr_t) {
  monitor::increment();
  throw error { "is-not-null", "nullptr is always null" };
}

/* in */
template <typename T, typename U>
auto in (T const& lhs, U const& rhs) -> typename enable_if<
  trait::begin<U>,
  trait::end<U>
>::type {
  monitor::increment();
  auto begin = std::begin(rhs);
  auto end = std::end(rhs);
  auto result = std::find(begin, end, lhs);
  if (result != end) { return; }
  throw error { "in", impl::message(lhs, rhs, "is not in") };
}

template <typename T, typename U>
auto in (T const&, U const&) -> typename disable_if<
  trait::begin<U>,
  trait::end<U>
>::type {
  monitor::increment();
  throw error { "in", "Given type is not an iterable range" };
}

/* not-in */
template <typename T, typename U>
auto not_in (T const& lhs, U const& rhs) -> typename enable_if<
  trait::begin<U>,
  trait::end<U>
>::type {
  monitor::increment();
  auto begin = std::begin(rhs);
  auto end = std::end(rhs);
  auto result = std::find(begin, end, lhs);
  if (result == end) { return; }
  throw error { "not-in", impl::message(lhs, rhs, "is in") };
}

template <typename T, typename U>
auto not_in (T const&, U const&) -> typename disable_if<
  trait::begin<U>,
  trait::end<U>
>::type {
  monitor::increment();
  throw error { "not-in", "Given type is not an iterable range" };
}

/* throws */
template <typename T>
void throws (std::function<void()>&& call) {
  monitor::increment();
  try { call(); }
  catch (T const&) { return; }
  catch (...) { }
  throw error { "throws", "Expected exception was not thrown" };
}

/* almost_equal */
void almost_equal (double first, double second, int places=4) {
  monitor::increment();
  if (std::isnan(first)) {
    throw error { "almost-equal", "Cannot compare when 1st value is NaN" };
  }

  if (std::isnan(second)) {
    throw error { "almost-equal", "Cannot compare when 2nd value is NaN" };
  }

  if (std::isinf(first)) {
    throw error { "almost-equal", "Cannot compare when 1st value is infinite" };
  }

  if (std::isinf(second)) {
    throw error { "almost-equal", "Cannot compare when 2nd value is infinite" };
  }

  if (places < 0) {
    throw error { "almost-equal", "Cannot compare less than 0 places" };
  }

  auto tens = static_cast<uint64_t>(std::pow(10, places));
  auto subd = first - second;
  auto compare = std::round(subd * tens) / tens;
  if (compare == 0.0) { return; }

  throw error {
    "almost-equal",
    impl::message(first, second, "is not almost equal to")
  };
}

void almost_equal (float first, float second, int places=4) {
  monitor::increment();
  if (std::isnan(first)) {
    throw error { "almost-equal", "Cannot compare when 1st value is NaN" };
  }

  if (std::isnan(second)) {
    throw error { "almost-equal", "Cannot compare when 2nd value is NaN" };
  }

  if (std::isinf(first)) {
    throw error { "almost-equal", "Cannot compare when 1st value is infinite" };
  }

  if (std::isinf(second)) {
    throw error { "almost-equal", "Cannot compare when 2nd value is infinite" };
  }

  if (places < 0) {
    throw error { "almost-equal", "Cannot compare less than 0 places" };
  }

  auto tens = static_cast<uint64_t>(std::pow(10, places));
  auto subd = first - second;

  auto compare = std::round(subd * tens) / tens;
  if (compare == 0.0f) { return; }

  throw error {
    "almost-equal",
    impl::message(first, second, "is not almost equal to")
  };
}

/* not-almost-equal */
void not_almost_equal (double first, double second, int places=4) {
  monitor::increment();
  if (std::isnan(first)) {
    throw error { "not-almost-equal", "Cannot compare when 1st value is NaN" };
  }

  if (std::isnan(second)) {
    throw error { "not-almost-equal", "Cannot compare when 2nd value is NaN" };
  }

  if (std::isinf(first)) {
    throw error {
      "not-almost-equal",
      "Cannot compare when 1st value is infinite"
    };
  }

  if (std::isinf(second)) {
    throw error {
      "not-almost-equal",
      "Cannot compare when 2nd value is infinite"
    };
  }

  if (places < 0) {
    throw error { "not-almost-equal", "Cannot compare less than 0 places" };
  }

  auto tens = static_cast<uint64_t>(std::pow(10, places));
  auto subd = first - second;
  auto compare = std::round(subd * tens) / tens;
  if (compare != 0.0) { return; }

  throw error {
    "not-almost-equal", impl::message(first, second, "is almost equal to")
  };
}

void not_almost_equal (float first, float second, int places=4) {
  monitor::increment();
  if (std::isnan(first)) {
    throw error { "not-almost-equal", "Cannot compare when 1st value is NaN" };
  }

  if (std::isnan(second)) {
    throw error { "not-almost-equal", "Cannot compare when 2nd value is NaN" };
  }

  if (std::isinf(first)) {
    throw error {
      "not-almost-equal",
      "Cannot compare when 1st value is infinite"
    };
  }

  if (std::isinf(second)) {
    throw error {
      "not-almost-equal",
      "Cannot compare when 2nd value is infinite"
    };
  }

  if (places < 0) {
    throw error { "not-almost-equal", "Cannot compare less than 0 places" };
  }

  auto tens = static_cast<uint64_t>(std::pow(10, places));
  auto subd = first - second;

  auto compare = std::round(subd * tens) / tens;
  if (compare != 0.0f) { return; }

  throw error {
    "not-almost-equal", impl::message(first, second, "is almost equal to")
  };
}

/* greater */
template <typename T, typename U>
auto greater (T const& lhs, U const& rhs) -> typename enable_if<
  trait::gt<T, U>
>::type {
  monitor::increment();
  if (lhs > rhs) { return; }
  throw error { "greater", impl::message(lhs, rhs, "is not greater than") };
}

template <typename T, typename U>
auto greater (T const&, U const&) -> typename disable_if<
  trait::gt<T, U>
>::type {
  monitor::increment();
  throw error { "greater", "Given types do not implement operator >" };
}

/* greater_equal */
template <typename T, typename U>
auto greater_equal (T const& lhs, U const& rhs) -> typename enable_if<
  trait::ge<T, U>
>::type {
  monitor::increment();
  if (lhs >= rhs) { return; }
  throw error {
    "greater-equal",
    impl::message(lhs, rhs, "is not greater or equal to")
  };
}

template <typename T, typename U>
auto greater_equal (T const&, U const&) -> typename disable_if<
  trait::ge<T, U>
>::type {
  monitor::increment();
  throw error { "greater-equal", "Given types do not implement operator >=" };
}

/* less */
template <typename T, typename U>
auto less (T const& lhs, U const& rhs) -> typename enable_if<
  trait::lt<T, U>
>::type {
  monitor::increment();
  if (lhs < rhs) { return; }
  throw error { "less", impl::message(lhs, rhs, "is not less than") };
}

template <typename T, typename U>
auto less (T const&, U const&) -> typename disable_if<
  trait::lt<T, U>
>::type {
  monitor::increment();
  throw error { "less", "Given types do not implement operator <" };
}

/* less-equal */
template <typename T, typename U>
auto less_equal (T const& lhs, U const& rhs) -> typename enable_if<
  trait::le<T, U>
>::type {
  monitor::increment();
  if (lhs <= rhs) { return; }
  throw error {
    "less-equal",
    impl::message(lhs, rhs, "is not less than or equal to")
  };
}

template <typename T, typename U>
auto less_equal (T const&, U const&) -> typename disable_if<
  trait::le<T, U>
>::type {
  monitor::increment();
  throw error { "less-equal", "Given types do not implement operator <=" };
}

/* count-equal */
/* associative-equal */
/* sequence-equal */

/* fail */
inline void fail () {
  monitor::increment();
  throw error { "fail", "Immediate failure requested" };
}

}}} /* namespace unittest::v1::assert */

#endif /* UNITTEST_ASSERT_HPP */
