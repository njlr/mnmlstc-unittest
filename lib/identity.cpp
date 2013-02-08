#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <sstream>

namespace unittest {
namespace v1 {

identity::identity (identity const&) noexcept : statement { 0 } { }
identity::identity () noexcept : statement { -1 } { }
identity::~identity () noexcept { }

auto identity::instance () noexcept -> identity& {
  static identity self;
  return self;
}

auto identity::assert_false (bool c, const char* m) noexcept(false) -> void { }
auto identity::assert_true (bool c, const char* m) noexcept(false) -> void { }

auto identity::assert_false (bool c) noexcept(false) -> void { }
auto identity::assert_true (bool c) noexcept(false) -> void { }

auto identity::assert_is_not (intptr_t, intptr_t, const char*) noexcept(false) -> void { }
auto identity::assert_is (intptr_t, intptr_t, const char*) noexcept(false) -> void { }

auto identity::assert_is_not (intptr_t, intptr_t) noexcept(false) -> void {}
auto identity::assert_is (intptr_t, intptr_t) noexcept(false) -> void { }

auto identity::fail (const char* m) noexcept(false) -> void { }
auto identity::fail () noexcept (false) -> void { }

UNITTEST_EXPORT_API identity& self = identity::instance();

}} /* namespace unittest::v1 */
