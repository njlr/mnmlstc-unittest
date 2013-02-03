#ifndef MNMLSTC_UNITTEST_STEP_HPP
#define MNMLSTC_UNITTEST_STEP_HPP
#pragma once

#include <functional>
#include <string>

#include <unittest/export.hpp>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API step final {
  std::function<void(void)> function;
  std::string label;

  auto operator = (step const&) noexcept -> step& = delete;
  auto operator = (step&&) noexcept -> step& = delete;

  step () noexcept = delete;

public:
  step (step const&) noexcept;
  step (step&&) noexcept;

  explicit step (std::string&&) noexcept;

  auto operator = (std::function<void(void)>&&) noexcept -> step&;
  auto operator () () const noexcept -> void;

  auto name () const noexcept -> std::string const&;
};

}} /* namespace unittest::v1 */

#endif /* MNMLSTC_UNITTEST_STEP_HPP */
