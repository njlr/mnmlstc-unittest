#ifndef UNITTEST_SKIP_HPP
#define UNITTEST_SKIP_HPP
#pragma once

#include <functional>

namespace unittest {
inline namespace v1 {

class skip {
  using function = std::function<void()>;
protected:
  const char* reason;
public:
  skip& operator = (skip const&) noexcept = delete;
  skip& operator = (skip&&) noexcept = delete;

  skip (skip const&) noexcept = delete;
  skip (skip&&) noexcept = delete;
  skip () noexcept = delete;

  explicit skip (const char*) noexcept;
  ~skip () noexcept;

  function operator = (function&&) const noexcept;
};

class skip_if final : skip {
  using function = std::function<void()>;
  bool condition;
public:
  skip_if& operator = (skip_if const&) noexcept = delete;
  skip_if& operator = (skip_if&&) noexcept = delete;

  skip_if (skip const&) noexcept = delete;
  skip_if (skip&&) noexcept = delete;
  skip_if () noexcept = delete;

  explicit skip_if (bool, const char*) noexcept;
  ~skip_if () noexcept;

  function operator = (function&&) const noexcept;
};

class skip_unless final : skip {
  using function = std::function<void()>;
  bool condition;
public:
  skip_unless& operator = (skip_unless const&) noexcept = delete;
  skip_unless& operator = (skip_unless&&) noexcept = delete;

  skip_unless (skip_unless const&) noexcept = delete;
  skip_unless (skip_unless&&) noexcept = delete;
  skip_unless () noexcept = delete;

  explicit skip_unless (bool, const char*) noexcept;
  ~skip_unless () noexcept;

  function operator = (function&&) const noexcept;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_SKIP_HPP */
