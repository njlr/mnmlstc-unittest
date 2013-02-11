#ifndef UNITTEST_TEST_HPP
#define UNITTEST_TEST_HPP
#pragma once

#include <unittest/export.hpp>

#include <initializer_list>
#include <functional>
#include <utility>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API test final {
  using task_pair = std::pair<std::string, std::function<void()>>;
  const char* label;

public:
  auto operator = (test const&) noexcept -> test& = delete;
  auto operator = (test&&) noexcept -> test& = delete;

  test (test const&) noexcept = delete;
  test (test&&) noexcept = delete;
  test () noexcept = delete;

  explicit test (const char*) noexcept;
  ~test () noexcept;

  auto operator = (std::initializer_list<task_pair>) noexcept -> void;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_TEST_HPP */
