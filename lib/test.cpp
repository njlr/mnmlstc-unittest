#include <unittest/test.hpp>
#include <unittest/step.hpp>

#include <utility>

using std::initializer_list;
using std::string;
using std::move;

namespace unittest {
inline namespace v1 {

test::test (test const& that) noexcept : label { that.label } { }
test::test (test&& that) noexcept : label { move(that.label) } { }
test::test (std::string&& label) noexcept : label { move(label) } { }

auto test::name () const noexcept -> string const& { return this->label; }
auto test::operator = (initializer_list<step> steps) noexcept -> test& {
  return *this;
}

}} /* namespace unittest::v1 */
