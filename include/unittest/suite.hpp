#ifndef UNITTEST_SUITE_HPP
#define UNITTEST_SUITE_HPP
#pragma once

#include <initializer_list>
#include <string>

#include <unittest/export.hpp>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API suite final {
  std::string label;

  auto operator = (suite const&) noexcept -> suite& = delete;
  auto operator = (suite&&) noexcept -> suite& = delete;

  suite () = delete;

public:
  suite (suite const&) noexcept;
  suite (suite&&) noexcept;

  explicit suite (std::string&&) noexcept;

  auto operator = (std::initializer_list<class test>) noexcept -> suite&;
  auto name () const noexcept -> std::string const&;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_SUITE_HPP */
