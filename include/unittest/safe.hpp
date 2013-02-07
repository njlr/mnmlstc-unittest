#ifndef UNITTEST_SAFE_HPP
#define UNITTEST_SAFE_HPP
#pragma once

#include <unittest/export.hpp>

#include <forward_list>
#include <system_error>
#include <utility>
#include <string>
#include <future>
#include <tuple>

namespace unittest {
inline namespace v1 {

using std::forward_list;
using std::string;
using std::tuple;

using result = std::future<std::error_condition>;

class UNITTEST_EXPORT_API safe final {
  /* test-name, task-name, deferred function */
  forward_list<tuple<string, string, result>> tests;
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
