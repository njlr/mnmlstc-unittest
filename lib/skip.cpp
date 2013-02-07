#include <unittest/skip.hpp>

namespace unittest {
inline namespace v1 {

/* skip_unless */
skip_unless::skip_unless (bool condition, const char* reason) noexcept :
  condition { condition },
  skip { reason }
{ }
skip_unless::~skip_unless () noexcept { this->condition = false; }
auto skip_unless::operator = (function&&) const noexcept -> function {
  bool condition = this->condition;
  return *static_cast<const skip*>(this) = [condition]{};
}

/* skip_if */
skip_if::skip_if (bool condition, const char* reason) noexcept :
  condition { condition },
  skip { reason }
{ }
skip_if::~skip_if () noexcept { this->condition = false; }
auto skip_if::operator = (function&&) const noexcept -> function {
  bool condition = this->condition;
  return *static_cast<const skip*>(this) = [condition]{};
}

/* skip */
skip::skip (const char* reason) noexcept : reason { reason } { }
skip::~skip () noexcept { this->reason = nullptr; }
auto skip::operator = (function&&) const noexcept -> function {
  return []{};
}

}} /* namespace unittest::v1 */
