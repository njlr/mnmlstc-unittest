#ifndef UNITTEST_SUITE_HPP
#define UNITTEST_SUITE_HPP
#pragma once

#include <initializer_list>
#include <string>

namespace unittest {
inline namespace v1 {

class test;

class UNITTEST_API_EXPORT suite final {
  std::string label;

  auto operator = (suite const&) = delete;
  auto operator = (suite&&) = delete;

  suite () = delete;

public:
  suite (suite const&) noexcept;
  suite (suite&&) noexcept;

  suite (const char*) noexcept;

  auto operator = (std::initializer_list<test>) noexcept -> suite&;
  auto name () const noexcept -> std::string const&;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_SUITE_HPP */
