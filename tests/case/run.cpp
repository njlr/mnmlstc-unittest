#include <unittest/test.hpp>
#include <unittest/task.hpp>
#include <unittest/safe.hpp>

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <csignal>

auto sigsegv (int) -> void {
  std::clog << "SIGSEGV signal triggered" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto v1 () -> void {
  unittest::v1::test("my-test") = {
    unittest::v1::task("1st-task") = [] {
      throw std::runtime_error("no logic");
    },
    unittest::v1::task("2nd-task") = [] {
      throw std::runtime_error("no logic");
    }
  };

  auto value = 0;
  for (auto item : unittest::v1::vault) {
    try { std::get<2>(item)(); }
    catch (std::runtime_error const& e) {
      value += 1;
      continue;
    }
    std::clog << "task did not throw as expected" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  if (value != 2) {
    std::clog << "test did not submit proper number of tasks" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

auto main () -> int {
  std::signal(SIGSEGV, sigsegv);
  v1();
  return EXIT_SUCCESS;
}
