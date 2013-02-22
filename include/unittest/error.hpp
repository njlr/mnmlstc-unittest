#ifndef UNITTEST_ERROR_HPP
#define UNITTEST_ERROR_HPP
#pragma once

#include <unittest/export.hpp>
#include <stdexcept>
#include <string>

#include <cstdint>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API exception final : public std::logic_error {
  const char* kind;
  int64_t count;

public:
  explicit exception (const char*, std::string&&, int64_t) noexcept;
  exception (const exception&) noexcept;
  virtual ~exception () noexcept;

  auto operator = (exception const&) noexcept -> exception&;

  auto statement () const noexcept -> int64_t;
  auto type () const noexcept -> const char*;
};

class UNITTEST_EXPORT_API skipping final {
  std::string message;
public:
  explicit skipping (std::string&&);
  auto what () const noexcept -> const char*;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_ERROR_HPP */
