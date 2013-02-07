#include <unittest/error.hpp>
#include <unittest/skip.hpp>

namespace unittest {
namespace v1 {

/* skip_unless */
skip_unless::skip_unless (bool condition, const char* reason) noexcept :
  condition { condition },
  skip { reason }
{ }
skip_unless::~skip_unless () noexcept { this->condition = false; }
auto skip_unless::operator = (function&& call) const noexcept -> function {
  bool condition = this->condition;
  return [condition]{};
}

/* skip_if */
skip_if::skip_if (bool condition, const char* reason) noexcept :
  condition { condition },
  skip { reason }
{ }
skip_if::~skip_if () noexcept { this->condition = false; }
auto skip_if::operator = (function&& call) const noexcept -> function {
  auto condition = this->condition;
  auto reason = this->reason;
  return [condition, reason, call]{
    if (condition) { throw skip_error(reason); }
    call();
  };
}

/* skip */
skip::skip (const char* reason) noexcept : reason { reason } { }
skip::~skip () noexcept { this->reason = nullptr; }
auto skip::operator = (function&&) const noexcept -> function {
  return []{};
}

}} /* namespace unittest::v1 */
