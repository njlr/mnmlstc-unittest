#include <unittest/test.hpp>
#include <unittest/task.hpp>
#include <unittest/safe.hpp>

#include <iostream>
#include <cstdlib>
#include <csignal>

auto sigsegv (int) -> void {
  std::clog << "SIGSEGV signal triggered" << std::endl;
  std::exit(EXIT_FAILURE);
}

/* Tests v1 interface for unittest::test */
auto v1 () -> void {

  unittest::v1::test("my-name") = {
    unittest::v1::task("nothing") = []{ }
  };

  auto name = std::get<0>(*unittest::v1::vault.begin());
  if (name != "my-name") {
    std::clog << "test did not submit proper name: " << name << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

auto main () -> int {
  std::signal(SIGSEGV, sigsegv);
  v1();
  return EXIT_SUCCESS;
}
