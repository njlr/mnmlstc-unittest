#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <sstream>

namespace unittest {
inline namespace v1 {

identity::identity (identity const&) noexcept : statement { 0 } { }
identity::identity () noexcept : statement { -1 } { }
identity::~identity () noexcept { }

auto identity::instance () noexcept -> identity& {
  static identity self;
  return self;
}

auto identity::assert_false (bool c, const char* m) -> void { }
auto identity::assert_true (bool c, const char* m) -> void { }

auto identity::assert_false (bool c) -> void { }
auto identity::assert_true (bool c) -> void { }

auto identity::assert_is_not (intptr_t, intptr_t, const char*) -> void { }
auto identity::assert_is (intptr_t, intptr_t, const char*) -> void { }

//FIXME: does not mention current 'statement' count
auto identity::assert_is_not (intptr_t lhs, intptr_t rhs) -> void {
  if (this->statement < 0) { throw identity_crisis { }; }
  this->statement += 1;
  if (lhs != rhs) { return; }
  throw assert_is_not_error { "" };
}

auto identity::assert_is (intptr_t, intptr_t) -> void { }

//FIXME: does not mention current 'statement' count
auto identity::fail (const char* msg) -> void {
  if (this->statement < 0) { throw identity_crisis { }; }
  this->statement += 1;
  throw failure { msg };
}

//FIXME: does not mention current 'statement' count
auto identity::fail () -> void {
  if (this->statement < 0) { throw identity_crisis { }; }
  this->statement += 1;
  throw failure { "immediate failure requested" };
}

UNITTEST_EXPORT_API identity& self = identity::instance();

}} /* namespace unittest::v1 */
