#ifndef UNITTEST_TEST_HPP
#define UNITTEST_TEST_HPP

#include <initializer_list>
#include <functional>
#include <utility>
#include <string>

#include <unittest/monitor.hpp>

namespace unittest {
inline namespace v1 {

class test final {
  using task_pair = std::pair<std::string, std::function<void()>>;
  std::string label;

public:
  test& operator = (test const&) noexcept = delete;
  test& operator = (test&&) noexcept = delete;

  test (test const&) noexcept = delete;
  test (test&&) noexcept = delete;
  test () noexcept = delete;

  explicit test (std::string&& label) noexcept : label { std::move(label) } { }
  ~test () noexcept { }

  void operator = (std::initializer_list<task_pair> tasks) noexcept {
    std::for_each(tasks.begin(), tasks.end(), [this](task_pair item) {
      monitor::add(
        std::move(std::string { this->label }),
        std::move(std::get<0>(item)),
        std::move(std::get<1>(item))
      );
    });
  }
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_TEST_HPP */
