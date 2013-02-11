#include <unittest/task.hpp>

namespace unittest {
inline namespace v1 {

task::task (const char* str) noexcept : label { str } { }
task::~task () noexcept { }

auto task::operator = (function&& call) const noexcept -> step {
  return std::make_pair(this->label, std::move(call));
}

}} /* namespace unittest::v1 */
