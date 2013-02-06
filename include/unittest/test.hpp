#ifndef UNITTEST_TEST_HPP
#define UNITTEST_TEST_HPP
#pragma once

#include <unittest/configure.hpp>
#include <unittest/export.hpp>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API test final {
  const char* label;

  auto operator = (test const&) noexcept -> test& = delete;
  auto operator = (test&&) noexcept -> test& = delete;

  test (test const&) noexcept = delete;
  test (test&&) noexcept = delete;
  test () noexcept = delete;

public:
  explicit test (const char*) noexcept;
  ~test () noexcept;

  auto operator = (initializer_list<pair<string, function>>) noexcept -> void;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_TEST_HPP */
