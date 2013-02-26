#ifndef UNITTEST_IDENTITY_HPP
#define UNITTEST_IDENTITY_HPP
#pragma once

#include <unittest/utility.hpp>
#include <unittest/export.hpp>
#include <unittest/error.hpp>

#include <sstream>
#include <utility>
#include <memory>

#include <cstdint>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API identity final {
  using cstring = const char*;

  std::int64_t statement;

  identity () noexcept;

  void assert_is_not_null(intptr_t, cstring=nullptr);
  void assert_is_null (intptr_t, cstring=nullptr);

  void assert_is_not (intptr_t, intptr_t, cstring=nullptr);
  void assert_is (intptr_t, intptr_t, cstring=nullptr);

public:

  identity& operator = (identity const&) noexcept = delete;
  identity& operator = (identity&&) noexcept = delete;
  identity (identity const&) noexcept = delete;
  identity (identity&&) noexcept = delete;

  ~identity () noexcept;

  static identity& instance () noexcept;
  void reset () noexcept;

  /* assert_greater_equal */
  template <typename T, typename U>
  auto assert_greater_equal (T const& lhs, U const& rhs, cstring msg=nullptr)
  -> typename enable_if<trait::ge<T, U>>::type {
    this->statement += 1;
    if (lhs >= rhs) { return; }
    std::ostringstream stream;
    if (msg) {
      stream << msg;
    } else {
      stream << repr(lhs) << " not greater than or equal to " << repr(rhs);
    }
    throw exception { "assert_greater_equal", stream.str(), this->statement };
  }

  template <typename T, typename U>
  auto assert_greater_equal (T const&, U const&, cstring=nullptr)
  -> typename disable_if<trait::ge<T, U>>::type {
    this->statement += 1;
    throw exception {
      "assert_greater_equal",
      "Given types do not implement operator >=",
      this->statement
    };
  }

  /* assert_less_equal */
  template <typename T, typename U>
  auto assert_less_equal (T const& lhs, U const& rhs, cstring msg=nullptr)
  -> typename enable_if<trait::le<T, U>>::type {
    this->statement += 1;
    throw exception {
      "assert_less_equal",
      "Not yet implemented",
      this->statement
    };
  }

  template <typename T, typename U>
  auto assert_less_equal (T const&, U const&, cstring=nullptr)
  -> typename disable_if<trait::le<T, U>>::type {
    this->statement += 1;
    throw exception {
      "assert_less_equal",
      "Given types do not implement operator <=",
      this->statement
    };
  }

  /* assert_not_equal */
  template <typename T, typename U>
  auto assert_not_equal (T const& lhs, U const& rhs, cstring msg=nullptr)
  -> typename enable_if<trait::ne<T, U>>::type {
    this->statement += 1;
    if (lhs != rhs) { return; }
    std::ostringstream stream;
    if (msg) { stream << msg; }
    else { stream << repr(lhs) << " is equal to " << repr(rhs); }
    throw exception { "assert_not_equal", stream.str(), this->statement };
  }

  template <typename T, typename U>
  auto assert_not_equal (T const&, U const&, cstring=nullptr)
  -> typename disable_if<trait::ne<T, U>>::type {
    this->statement += 1;
    throw exception {
      "assert_not_equal",
      "Given types do not implement operator !=",
      this->statement
    };
  }

  /* assert_equal */
  template <typename T, typename U>
  auto assert_equal (T const& lhs, U const& rhs, cstring msg=nullptr)
  -> typename enable_if<trait::eq<T, U>>::type {
    this->statement += 1;
    if (lhs == rhs) { return; }
    std::ostringstream stream;
    if (msg) { stream << msg; }
    else { stream << repr(lhs) << " is not equal to " << repr(rhs); }
    throw exception { "assert_equal", stream.str(), this->statement };
  }

  template <typename T, typename U>
  auto assert_equal (T const&, U const&, cstring=nullptr)
  -> typename disable_if<trait::eq<T, U>>::type {
    this->statement += 1;
    throw exception {
      "assert_equal",
      "Given types do not implement operator ==", 
      this->statement
    };
  }

  /* assert_is_not */
  template <typename T>
  void assert_is_not (T const& lhs, T const& rhs, cstring msg=nullptr) {
    auto one = std::addressof(lhs);
    auto two = std::addressof(rhs);
    this->assert_is_not(one, two, msg);
  }

  template <typename T>
  void assert_is_not (T* lhs, T* rhs, cstring msg=nullptr) {
    auto lhs_ = reinterpret_cast<intptr_t>(lhs);
    auto rhs_ = reinterpret_cast<intptr_t>(rhs);
    this->assert_is_not(lhs_, rhs_, msg);
  }

  /* assert_is */
  template <typename T>
  void assert_is (T const& lhs, T const& rhs, cstring msg=nullptr) {
    this->assert_is(std::addressof(lhs), std::addressof(rhs), msg);
  }

  template <typename T>
  void assert_is (T* lhs, T* rhs, cstring msg=nullptr) {
    auto lhs_ = reinterpret_cast<intptr_t>(lhs);
    auto rhs_ = reinterpret_cast<intptr_t>(rhs);
    this->assert_is(lhs_, rhs_, msg);
  }

  template <typename T>
  void assert_is_not_null (T* ptr, cstring msg=nullptr) {
    this->assert_is_not_null(reinterpret_cast<intptr_t>(ptr), msg);
  }

  template <typename T>
  void assert_is_null (T* ptr, cstring msg=nullptr) {
    this->assert_is_null(reinterpret_cast<intptr_t>(ptr), msg);
  }

  void assert_false (bool, cstring=nullptr);
  void assert_true (bool, cstring=nullptr);
  void fail (cstring=nullptr);
};

extern UNITTEST_EXPORT_API identity& self;

}} /* namespace unittest::v1 */

#endif /* UNITTEST_IDENTITY_HPP */
