#ifndef UNITTEST_ERROR_HPP
#define UNITTEST_ERROR_HPP
#pragma once

#include <unittest/export.hpp>
#include <string>

#include <cstdint>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API exception {
  std::string message;
  std::string name;
  int64_t value;

protected:
  explicit exception (const char*, std::string&&, int64_t) noexcept;

public:
  exception (const exception&) noexcept;
  virtual ~exception () noexcept;

  auto operator = (exception const&) noexcept -> exception&;

  auto count () const noexcept -> int64_t;
  auto what () const noexcept -> const char*;
  auto type () const noexcept -> const char*;
};

class UNITTEST_EXPORT_API identity_crisis final {
  std::string message;
public:
  explicit identity_crisis (std::string&&);
  auto what () const noexcept -> const char*;
};

class UNITTEST_EXPORT_API skipping final {
  std::string message;
public:
  explicit skipping (std::string&&);
  auto what () const noexcept -> const char*;
};

struct UNITTEST_EXPORT_API failure final : private exception {
  explicit failure (std::string&&, int64_t);
};

struct UNITTEST_EXPORT_API assert_false final : public exception {
  explicit assert_false (std::string&&, int64_t);
};

struct UNITTEST_EXPORT_API assert_true final : public exception {
  explicit assert_true (std::string&&, int64_t);
};

struct UNITTEST_EXPORT_API assert_is_not final : public exception {
  explicit assert_is_not (std::string&&, int64_t);
};

struct UNITTEST_EXPORT_API assert_is final : public exception {
  explicit assert_is (std::string&&, int64_t);
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_ERROR_HPP */
