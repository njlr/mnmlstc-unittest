#include <unittest/error.hpp>

using std::string;

namespace unittest {
inline namespace v1 {

exception::exception (const char* kind, string&& msg, int64_t count) noexcept :
  std::logic_error { msg },
  kind { kind },
  count { count }
{ }

exception::exception (exception const& that) noexcept :
  std::logic_error { that },
  kind { that.kind },
  count { that.count }
{ }

exception::~exception () noexcept { }

auto exception::statement () const noexcept -> int64_t { return this->count; }
auto exception::type () const noexcept -> const char* { return this->kind; }

skipping::skipping (string&& msg) : message { std::move(msg) } { }
auto skipping::what () const noexcept -> const char* {
  return this->message.c_str();
}

}} /* namespace unittest::v1 */
