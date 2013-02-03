#ifndef UNITTEST_TEST_HPP
#define UNITTEST_TEST_HPP
#pragma once

#include <initializer_list>
#include <string>

#include <unittest/export.hpp>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API test final {
  std::string label;

  auto operator = (test const&) noexcept -> test& = delete;
  auto operator = (test&&) noexcept -> test& = delete;

  test () noexcept = delete;

public:
  test (test const&) noexcept;
  test (test&&) noexcept;

  explicit test (std::string&&) noexcept;

  auto operator = (std::initializer_list<class step>) noexcept -> test&;
  auto name () const noexcept -> std::string const&;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_TEST_HPP */
