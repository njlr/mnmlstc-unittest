#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <cstdlib>

auto v1 () -> void {
  using unittest::v1::self;

  try { self.fail(); }
  catch (unittest::v1::failure const&) { return; }
  catch (...) {
    std::clog << "expected exception was not thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "self.fail did not throw exception" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  v1();
  return EXIT_SUCCESS;
}
