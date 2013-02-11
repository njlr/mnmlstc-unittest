#include <unittest/task.hpp>

#include <iostream>
#include <csignal>
#include <cstdlib>

/* Tests the v1 interface for a task's name */
auto v1 () -> void {
  auto pair = unittest::v1::task("task-name") = []{};
  std::string name = std::get<0>(pair);

  if (name.compare("task-name") != 0) {
    std::clog << "task-name not in pair" << ": " << name << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

auto sigsegv (int) -> void {
  std::clog << "SIGSEGV signal triggered" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  std::ignore = std::signal(SIGSEGV, sigsegv);
  v1();
  return EXIT_SUCCESS;
}
