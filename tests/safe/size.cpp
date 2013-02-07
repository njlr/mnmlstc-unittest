#include <unittest/safe.hpp>

#include <iostream>
#include <cstdlib>
#include <csignal>

auto v1 () -> void {
  if (unittest::v1::vault.size() != 0) {
    std::clog << "vault has elements within it" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  unittest::v1::vault.add("one", "two",
    std::async(std::launch::deferred, [] {
      return std::error_condition { 0, std::generic_category() };
    })
  );

  if (unittest::v1::vault.size() != 1) {
    std::clog << "vault is unable to hold onto new items" << std::endl;
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
  return EXIT_SUCCESS;
}
