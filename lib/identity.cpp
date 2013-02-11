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

auto identity::assert_is_not (intptr_t, intptr_t) -> void {}
auto identity::assert_is (intptr_t, intptr_t) -> void { }

auto identity::fail (const char* m) -> void { }
auto identity::fail () -> void { }

UNITTEST_EXPORT_API identity& self = identity::instance();

}} /* namespace unittest::v1 */
