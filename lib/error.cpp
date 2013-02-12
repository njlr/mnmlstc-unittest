#include <unittest/error.hpp>

namespace unittest {
inline namespace v1 {

exception::exception (std::string&& message, int64_t value) noexcept :
  message { std::move(message) },
  value { value }
{ }

exception::exception (exception const& that) noexcept :
  message { that.message },
  value { that.value }
{ }

exception::~exception () noexcept { }

auto exception::count  () const noexcept -> int64_t { return this->value; }
auto exception::what () const noexcept -> const char* {
  return this->message.c_str();
}

skipping::skipping (std::string&& msg) : exception { std::move(msg), -1 } { }

identity_crisis::identity_crisis (std::string&& msg) :
  exception { "self not copied by value before: " + msg, -1 }
{ }

failure::failure (std::string&& msg, int64_t val) :
  exception { std::move(msg), val }
{ }

assert_false::assert_false (std::string&& msg, int64_t val) :
  exception { std::move(msg), val }
{ }

assert_true::assert_true (std::string&& msg, int64_t val) :
  exception { std::move(msg), val }
{ }

assert_is_not::assert_is_not (std::string&& msg, int64_t val) :
  exception { std::move(msg), val }
{ }

assert_is::assert_is (std::string&& msg, int64_t val) :
  exception { std::move(msg), val }
{ }

}} /* namespace unittest::v1 */
