#include <unittest/suite.hpp>
#include <unittest/test.hpp>

#include <utility>

using std::initializer_list;
using std::string;
using std::move;

namespace unittest {
inline namespace v1 {

suite::suite (suite const& that) noexcept : label { that.label } { }
suite::suite (suite&& that) noexcept : label { move(that.label) } { }
suite::suite (const char* label) noexcept : label { label } { }

auto suite::name () const noexcept -> string const& { return this->label; }

auto suite::operator = (initializer_list<test>) noexcept -> suite& {
  return *this;
};

}} /* namespace unittest::v1 */
