#include <unittest/error.hpp>
#include <unittest/skip.hpp>

#include <iostream>
#include <csignal>

auto v1 () -> void {
  auto skip_if_always = unittest::v1::skip_if(true, "always-skip") = []{};
  auto skip_if_never = unittest::v1::skip_if(false, "never-skip") = []{
    throw 42;
  };

  try {
    skip_if_always();
    std::clog << "skip_if_always did not throw" << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (unittest::v1::skip_error const& e) {
    if (e.what() != std::string { "always-skip" }) {
      std::clog << "skip_if_always did not throw proper error" << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected exception thrown by skip_if_always" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try {
    skip_if_never();
    std::clog << "skip_if_never does not contain proper function" << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (int value) {
    if (value != 42) {
      std::clog << "skip_if_never function threw incorrect value" << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected exception thrown by skip_if_never" << std::endl;
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
