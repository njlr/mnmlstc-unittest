#include <unittest/error.hpp>
#include <unittest/skip.hpp>

namespace unittest {
inline namespace v1 {

/* skip_unless */
skip_unless::skip_unless (bool condition, const char* reason) noexcept :
  skip { reason },
  condition { condition }
{ }
skip_unless::~skip_unless () noexcept { this->condition = false; }
auto skip_unless::operator = (function&& call) const noexcept -> function {
  auto condition = this->condition;
  auto reason = this->reason;
  return [condition, reason, call]{
    if (not condition) { throw skipping { reason }; }
    call();
  };
}

/* skip_if */
skip_if::skip_if (bool condition, const char* reason) noexcept :
  skip { reason },
  condition { condition }
{ }
skip_if::~skip_if () noexcept { this->condition = false; }
auto skip_if::operator = (function&& call) const noexcept -> function {
  auto condition = this->condition;
  auto reason = this->reason;
  return [condition, reason, call]{
    if (condition) { throw skipping { reason }; }
    call();
  };
}

/* skip */
skip::skip (const char* reason) noexcept : reason { reason } { }
skip::~skip () noexcept { this->reason = nullptr; }
auto skip::operator = (function&& call) const noexcept -> function {
  auto reason = this->reason;
  return [reason]{ throw skipping { reason }; };
}

}} /* namespace unittest::v1 */
