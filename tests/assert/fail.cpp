#include <iostream>
#include <string>

#include <cstdlib>

#include <unittest/assert.hpp>
#include <unittest/error.hpp>

auto v1 () -> void {
  namespace assert = unittest::v1::assert;
  using unittest::v1::error;

  try { assert::fail(); }
  catch (error const& e) {
    if (std::string { "fail" } == e.type()) { return; }
    std::clog << "incorrect exception: " << e.type() << " was thrown"
              << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (...) {
    std::clog << "expected exception was not thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "assert::fail did not throw exception" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  v1();
  return EXIT_SUCCESS;
}
