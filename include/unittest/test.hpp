#ifndef UNITTEST_TEST_HPP
#define UNITTEST_TEST_HPP
#pragma once

#include <initializer_list>
#include <functional>
#include <utility>
#include <string>

namespace unittest {
inline namespace v1 {

class test final {
  using task_pair = std::pair<std::string, std::function<void()>>;
  const char* label;

public:
  test& operator = (test const&) noexcept = delete;
  test& operator = (test&&) noexcept = delete;

  test (test const&) noexcept = delete;
  test (test&&) noexcept = delete;
  test () noexcept = delete;

  explicit test (const char*) noexcept;
  ~test () noexcept;

  void operator = (std::initializer_list<task_pair>) noexcept;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_TEST_HPP */
