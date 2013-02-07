#ifndef UNITTEST_SKIP_HPP
#define UNITTEST_SKIP_HPP
#pragma once

#include <unittest/configure.hpp>
#include <unittest/export.hpp>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API skip {
protected:
  const char* reason;
public:
  auto operator = (skip const&) noexcept -> skip& = delete;
  auto operator = (skip&&) noexcept -> skip& = delete;

  skip (skip const&) noexcept = delete;
  skip (skip&&) noexcept = delete;
  skip () noexcept = delete;

  explicit skip (const char*) noexcept;
  ~skip () noexcept;

  auto operator = (function&&) const noexcept -> function;
};

class UNITTEST_EXPORT_API skip_if final : skip {
  bool condition;
public:
  auto operator = (skip_if const&) noexcept -> skip_if& = delete;
  auto operator = (skip_if&&) noexcept -> skip_if& = delete;

  skip_if (skip const&) noexcept = delete;
  skip_if (skip&&) noexcept = delete;
  skip_if () noexcept = delete;

  explicit skip_if (bool, const char*) noexcept;
  ~skip_if () noexcept;

  auto operator = (function&&) const noexcept -> function;
};

class UNITTEST_EXPORT_API skip_unless final : skip {
  bool condition;
public:
  auto operator = (skip_unless const&) noexcept -> skip_unless& = delete;
  auto operator = (skip_unless&&) noexcept -> skip_unless& = delete;

  skip_unless (skip_unless const&) noexcept = delete;
  skip_unless (skip_unless&&) noexcept = delete;
  skip_unless () noexcept = delete;

  explicit skip_unless (bool, const char*) noexcept;
  ~skip_unless () noexcept;

  auto operator = (function&&) const noexcept -> function;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_SKIP_HPP */
