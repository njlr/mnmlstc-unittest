#include <unittest/safe.hpp>

using std::move;

namespace unittest {
namespace v1 {

safe::safe () noexcept { }

auto safe::instance () noexcept -> safe& {
  static safe vault;
  return vault;
}

auto safe::add (string&& test, string&& task, result&& res) noexcept -> void {
  auto start = this->tests.before_begin();
  this->tests.emplace_after(start, move(test), move(task), move(res));
}

auto safe::begin () noexcept -> iterator { return this->tests.begin(); }
auto safe::end () noexcept -> iterator { return this->tests.end(); }

auto safe::size () const noexcept -> size_t {
  return std::distance(this->tests.begin(), this->tests.end());
}

UNITTEST_EXPORT_API safe& vault = safe::instance();

}} /* namespace unittest::v1 */
