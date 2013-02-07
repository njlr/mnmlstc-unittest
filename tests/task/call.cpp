#include <unittest/task.hpp>

#include <iostream>
#include <csignal>

/* Tests the v1 interface for task's handling of a function */
auto v1 () -> void {
  int value = 0;
  auto pair = unittest::v1::task("") = [&value] { value += 2; };

  if (not std::get<1>(pair)) {
    std::clog << "pair contains a null function" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::get<1>(pair)();
  if (value != 2) {
    std::clog << "pair called incorrect function" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

auto sigsegv (int) -> void {
  std::clog << "SIGSEGV signal triggered" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  std::signal(SIGSEGV, sigsegv);
  v1();
  return EXIT_SUCCESS; /* This should never be reached */
}
