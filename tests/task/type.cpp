#include <unittest/task.hpp>

#include <typeinfo>
#include <iostream>
#include <csignal>
#include <memory>

/* Tests the v1 interface for task's type handling */
auto v1 () -> void {
  auto empty_lambda = []{};
  auto pair = unittest::v1::task("") = empty_lambda;

  if (typeid(pair) != typeid(std::pair<std::string, std::function<void()>>)) {
    std::clog << "pair is not of the expected type" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  if (std::get<1>(pair).target_type() != typeid(empty_lambda)) {
    std::clog << "pair function target is not empty_lambda" << std::endl;
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
