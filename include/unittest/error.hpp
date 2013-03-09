#ifndef UNITTEST_ERROR_HPP
#define UNITTEST_ERROR_HPP
#pragma once

#include <stdexcept>
#include <string>

#include <cstdint>

namespace unittest {
inline namespace v1 {

class exception final : public std::logic_error {
  const char* kind;
  int64_t count;

public:
  explicit exception (const char*, std::string&&, int64_t) noexcept;
  exception (const exception&) noexcept;
  virtual ~exception () noexcept;

  exception& operator = (exception const&) noexcept;

  int64_t statement () const noexcept;
  const char* type () const noexcept;
};

class skipping final {
  std::string message;
public:
  explicit skipping (std::string&&);
  const char* what () const noexcept;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_ERROR_HPP */
