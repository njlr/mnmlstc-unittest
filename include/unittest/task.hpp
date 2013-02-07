#ifndef UNITTEST_TASK_HPP
#define UNITTEST_TASK_HPP
#pragma once

#include <unittest/configure.hpp>
#include <unittest/export.hpp>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API task final {
  const char* label;

public:
  auto operator = (task const&) noexcept -> task& = delete;
  auto operator = (task&&) noexcept -> task& = delete;

  task (task const&) noexcept = delete;
  task (task&&) noexcept = delete;
  task () noexcept = delete;

  explicit task (const char*) noexcept;
  ~task () noexcept;

  auto operator = (function&&) const noexcept -> pair<string, function>;
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_TASK_HPP */
