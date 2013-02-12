#ifndef UNITTEST_SAFE_HPP
#define UNITTEST_SAFE_HPP
#pragma once

#include <unittest/export.hpp>

#include <forward_list>
#include <functional>
#include <utility>
#include <string>
#include <tuple>

namespace unittest {
inline namespace v1 {

class UNITTEST_EXPORT_API safe final {
  using result = std::function<void()>;
  using string = std::string;

  using item = std::tuple<string, string, result>;
  /* test-name, task-name, function */

  std::forward_list<item> tests;
  safe () noexcept;

public:
  using iterator = decltype(safe::tests)::iterator;

  auto operator = (safe const&) noexcept -> safe& = delete;
  auto operator = (safe&&) noexcept -> safe& = delete;

  safe (safe const&) noexcept = delete;
  safe (safe&&) noexcept = delete;

  static auto instance () noexcept -> safe&;

  auto add (string&&, string&&, result&&) noexcept -> void;

  auto begin () noexcept -> iterator;
  auto end () noexcept -> iterator;

  auto size () const noexcept -> size_t;

  ~safe () noexcept = default;
};

extern UNITTEST_EXPORT_API safe& vault;

}} /* namespace unittest::v1 */

#endif /* UNITTEST_SAFE_HPP */
