#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <string>

#include <cstdlib>

auto v1 () -> void {
  using unittest::v1::self;

  try { self.fail(); }
  catch (unittest::v1::exception const& e) {
    if (std::string { "fail" } == e.type()) { return; }
    std::clog << "incorrect exception: " << e.type() << " was thrown"
              << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (...) {
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
