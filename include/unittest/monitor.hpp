#ifndef UNITTEST_MONITOR_HPP
#define UNITTEST_MONITOR_HPP

#include <functional>
#include <utility>
#include <string>
#include <vector>
#include <tuple>
#include <list>

#include <iostream>
#include <sstream>

#include <cstdlib>
#include <cstdint>
#include <csignal>

#include <unittest/error.hpp>

namespace unittest {
inline namespace v1 {

class monitor {
  std::list<std::tuple<std::string, std::string, std::function<void()>>> tests;
  uint64_t statement;

  monitor (monitor const&) = delete;
  monitor (monitor&&) = delete;

  monitor () noexcept {
    std::signal(SIGSEGV, [] (int) {
      std::clog << "Segmentation Fault Encountered" << std::endl;
      std::exit(EXIT_FAILURE);
    });
  }

  static monitor& ref () noexcept {
    static monitor instance;
    return instance;
  }

public:

  static void increment () noexcept { monitor::ref().statement += 1; }

  static void add (
    std::string&& test_name,
    std::string&& task_name,
    std::function<void()> task_call
  ) noexcept {
    monitor::ref().tests.emplace_back(
      std::move(test_name), std::move(task_name), std::move(task_call)
    );
  }

  static void run () {
    monitor& self = monitor::ref();
    std::vector<std::string> results;
    std::uint64_t failures = 0;

    for (auto const& item : self.tests) {
      std::ostringstream stream;
      auto const& test_name = std::get<0>(item);
      auto const& task_name = std::get<1>(item);
      auto const& task_call = std::get<2>(item);

      try { task_call(); }
      catch (skipping const& e) {
        stream << "[SKIP] " << test_name
               << "." << task_name
               << ": " << e.what();
        results.emplace_back(stream.str());
      } catch (error const& e) {
        stream << "[FAIL] " << test_name
               << "." << task_name
               << ": assert::" << e.type()
               << " on statement " << self.statement
               << " " << e.what();
        results.emplace_back(stream.str());
        failures += 1;
      } catch (...) {
        stream << "[FAIL] " << test_name
               << "." << task_name
               << ": Unhandled and Unknown Exception"
               << "encountered after statement " << self.statement;
        results.emplace_back(stream.str());
        failures += 1;
      }
      self.statement = 0;
    }

    for (auto&& result : results) { std::clog << result << std::endl; }
    std::exit(failures);
  }

};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_MONITOR_HPP */
