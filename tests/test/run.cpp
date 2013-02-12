#include <unittest/test.hpp>
#include <iostream>
#include <cstdlib>
#include <csignal>

auto sigsegv (int) -> void {
  std::clog << "SIGSEGV signal triggered" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  std::signal(SIGSEGV, sigsegv);
  return EXIT_FAILURE;
}
