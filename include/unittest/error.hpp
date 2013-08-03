#ifndef UNITTEST_ERROR_HPP
#define UNITTEST_ERROR_HPP
#pragma once

#include <stdexcept>
#include <string>

#include <cstdint>

namespace unittest {
inline namespace v1 {

class error final : public std::logic_error {
  char const* kind;

public:
  explicit error (char const* kind, std::string&& msg) noexcept :
    std::logic_error { msg },
    kind { kind }
  { }

  error (error const& that) noexcept :
    std::logic_error { that },
    kind { that.kind }
  { }

  virtual ~error () noexcept { }

  error& operator = (error const& that) noexcept {
    static_cast<std::logic_error&>(*this) = that;
    this->kind = that.kind;
    return *this;
  }

  char const* type () const noexcept { return this->kind; }
};

class skipping final {
  std::string message;
public:
  explicit skipping (std::string&& message) : message { std::move(message) } { }
  const char* what () const noexcept { return this->message.c_str(); }
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_ERROR_HPP */
