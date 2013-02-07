#include <unittest/test.hpp>

namespace unittest {
namespace v1 {

using task = pair<string, function>;

test::test (const char* str) noexcept : label { str } { }
test::~test () noexcept { }
auto test::operator = (initializer_list<task> tasks) noexcept -> void {
  // TODO: Submit this->label, task<0>, and task<1> to internal registry
}

}} /* namespace unittest::v1 */
