#ifndef UNITTEST_SKIP_HPP
#define UNITTEST_SKIP_HPP

#include <functional>

#include <unittest/error.hpp>

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

  explicit skip (char const* reason) noexcept : reason { reason } { }
  ~skip () noexcept = default;

  function operator = (function&&) const noexcept {
    auto reason = this->reason;
    return [reason] { throw skipping { reason }; };
  }
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

  explicit skip_if (bool condition, char const* reason) noexcept :
    skip { reason },
    condition { condition }
  { }
  ~skip_if () noexcept = default;

  function operator = (function&& call) const noexcept {
    auto condition = this->condition;
    auto reason = this->reason;
    return [condition, reason, call] {
      if (condition) { throw skipping { reason }; }
      call();
    };
  }
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

  explicit skip_unless (bool condition, char const* reason) noexcept :
    skip { reason },
    condition { condition }
  { }
  ~skip_unless () noexcept = default;

  function operator = (function&& call) const noexcept {
    auto condition = this->condition;
    auto reason = this->reason;
    return [condition, reason, call] {
      if (not condition) { throw skipping { reason }; }
      call();
    };
  }
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_SKIP_HPP */
