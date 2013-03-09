#ifndef UNITTEST_SAFE_HPP
#define UNITTEST_SAFE_HPP
#pragma once

#include <functional>
#include <utility>
#include <string>
#include <tuple>
#include <list>

namespace unittest {
inline namespace v1 {

class safe final {
  using result = std::function<void()>;
  using string = std::string;

  using item = std::tuple<string, string, result>;
  /* test-name, task-name, function */

  std::list<item> tests;
  safe () noexcept;

public:
  using iterator = decltype(safe::tests)::iterator;

  safe& operator = (safe const&) noexcept = delete;
  safe& operator = (safe&&) noexcept  = delete;

  safe (safe const&) noexcept = delete;
  safe (safe&&) noexcept = delete;

  static safe& instance () noexcept;

  void add (string&&, string&&, result&&) noexcept;

  iterator begin () noexcept;
  iterator end () noexcept;

  size_t size () const noexcept;

  ~safe () noexcept = default;
};

extern safe& vault;

}} /* namespace unittest::v1 */

#endif /* UNITTEST_SAFE_HPP */
