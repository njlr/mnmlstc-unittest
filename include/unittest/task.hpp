#ifndef UNITTEST_TASK_HPP
#define UNITTEST_TASK_HPP
#pragma once

#include <unittest/export.hpp>

#include <functional>
#include <string>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API task final {
  using step = std::pair<std::string, std::function<void()>>;
  using function = std::function<void()>;
  const char* label;

public:
  auto operator = (task const&) noexcept -> task& = delete;
  auto operator = (task&&) noexcept -> task& = delete;

  task (task const&) noexcept = delete;
  task (task&&) noexcept = delete;
  task () noexcept = delete;

  explicit task (const char*) noexcept;
  ~task () noexcept;

  auto operator = (function&&) const noexcept -> step;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_TASK_HPP */
