#include <unittest/step.hpp>

#include <utility>

using std::string;
using std::move;

namespace unittest {
inline namespace v1 {

step::step (step const& that) noexcept : label { that.label } { }
step::step (step&& that) noexcept : label { move(that.label) } { }

step::step (string&& label) noexcept : label { move(label) } { }

auto step::name () const noexcept -> std::string const& { return this->label; }

auto step::operator = (std::function<void(void)>&& call) noexcept -> step& {
  this->function = move(call);
  return *this;
}

auto step::operator () () const noexcept -> void {
  if (not this->function) { return; }
  this->function();
}

}} /* namespace unittest::v1 */
