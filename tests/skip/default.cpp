#include <unittest/error.hpp>
#include <unittest/skip.hpp>

#include <iostream>
#include <csignal>

auto v1 () -> void {
  auto skip = unittest::v1::skip("success") = []{};
  try {
    skip();
    std::clog << "skip did not throw" << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (unittest::v1::skip_error const& e) {
    if (e.what() != std::string { "success" }) {
      std::clog << "skip did not throw proper skip_error" << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected exception thrown by skip" << std::endl;
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
