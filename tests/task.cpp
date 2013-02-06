#include <unittest/task.hpp>

#include <iostream>
#include <csignal>
#include <memory>

auto v1 () -> void {
  auto empty_lambda = []{};
  auto pair = unittest::task("alpha") = empty_lambda;

  std::string name = std::get<0>(pair);
  if (name.compare("alpha") != 0) {
    std::clog << "name != 'alpha'" << ": " << name << std::endl;
    std::exit(EXIT_FAILURE);
  }

  if (std::get<1>(pair).target_type() != typeid(empty_lambda)) {
    std::clog << "std::get<1>(pair) is not empty_lambda" << std::endl;
    std::exit(EXIT_FAILURE);
  }

}

auto main () -> int {
  std::signal(SIGSEGV, [](int){
    std::clog << "SIGSEGV signal triggered" << std::endl;
    std::exit(EXIT_FAILURE);
  });

  v1();

  return EXIT_SUCCESS;
}
