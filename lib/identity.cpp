#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <sstream>

/* Used to solve ambiguity between identity member functions and
 * assertion exceptions
 */
namespace {
  using unittest::v1::assert_false;
  using unittest::v1::assert_true;

  using unittest::v1::assert_is_not;
  using unittest::v1::assert_is;
}

namespace unittest {
inline namespace v1 {

identity::identity (identity const&) noexcept : statement { 0 } { }
identity::identity () noexcept : statement { -1 } { }
identity::~identity () noexcept { }

auto identity::instance () noexcept -> identity& {
  static identity self;
  return self;
}

/* TODO: Implement */
auto identity::assert_false (bool cond, const char* msg) -> void { }
auto identity::assert_true (bool cond, const char* msg) -> void { }

auto identity::assert_is_not (intptr_t, intptr_t, const char*) -> void { }
auto identity::assert_is (intptr_t, intptr_t, const char*) -> void { }

auto identity::assert_false (bool cond) -> void {
  if (this->statement < 0) { throw identity_crisis { "assert_false" }; }
  this->statement += 1;
  if (not cond) { return; }
  throw ::assert_false { "condition evaluated true", this->statement };
}

auto identity::assert_true (bool cond) -> void {
  if (this->statement < 0) { throw identity_crisis { "assert_true" }; }
  this->statement += 1;
  if (cond) { return; }
  throw ::assert_true { "condition evaluted false", this->statement };
}

auto identity::assert_is_not (intptr_t lhs, intptr_t rhs) -> void {
  if (this->statement < 0) { throw identity_crisis { "assert_is_not" }; }
  this->statement += 1;
  if (lhs != rhs) { return; }
  std::ostringstream stream;
  stream << lhs <<  " is the same as " << rhs;
  throw ::assert_is_not { stream.str(), this->statement };
}

auto identity::assert_is (intptr_t lhs, intptr_t rhs) -> void {
  if (this->statement < 0) { throw identity_crisis { "assert_is" }; }
  this->statement += 1;
  if (lhs == rhs) { return; }
  std::ostringstream stream;
  stream << lhs << " is not the same as " << rhs;
  throw ::assert_is { stream.str(), this->statement };
}

auto identity::fail (const char* msg) -> void {
  if (this->statement < 0) { throw identity_crisis { "fail" }; }
  this->statement += 1;
  throw failure { msg, this->statement };
}

auto identity::fail () -> void {
  if (this->statement < 0) { throw identity_crisis { "fail" }; }
  this->statement += 1;
  throw failure { "immediate failure requested", this->statement };
}

UNITTEST_EXPORT_API identity& self = identity::instance();

}} /* namespace unittest::v1 */
