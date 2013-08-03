#ifndef UNITTEST_TASK_HPP
#define UNITTEST_TASK_HPP

#include <functional>
#include <string>

namespace unittest {
inline namespace v1 {

class task final {
  std::string label;

public:
  task& operator = (task const&) noexcept = delete;
  task& operator = (task&&) noexcept = delete;

  task (task const&) noexcept = delete;
  task (task&&) noexcept = delete;
  task () noexcept = delete;

  explicit task (std::string&& label) noexcept : label { std::move(label) } { }
  ~task () noexcept = default;

  std::pair<std::string, std::function<void()>>
  operator = (std::function<void()>&& call) const noexcept {
    return std::make_pair(this->label, std::move(call));
  }
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_TASK_HPP */
