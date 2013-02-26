#include <unittest/safe.hpp>
#include <unittest/test.hpp>

namespace unittest {
inline namespace v1 {

using std::initializer_list;
using std::move;

test::test (const char* str) noexcept : label { str } { }
test::~test () noexcept { }

void test::operator = (initializer_list<task_pair> tasks) noexcept {
  for (auto item : tasks) {
    vault.add(this->label, move(std::get<0>(item)), move(std::get<1>(item)));
  }
}

}} /* namespace unittest::v1 */
