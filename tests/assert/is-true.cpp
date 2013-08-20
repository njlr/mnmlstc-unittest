#include <iostream>
#include <memory>
#include <string>

#include <cstdlib>

#include <unittest/assert.hpp>
#include <unittest/error.hpp>

void v1() {
  using unittest::v1::error;
  namespace assert = unittest::v1::assert;

  bool value = false;
  try { assert::is_true(value); }
  catch (error const& e) {
    if (std::string { "is-true" } != e.type()) {
      std::clog << "unxpected error '" << e.type() << "' was thrown"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  value = true;
  try { assert::is_true(true); }
  catch (...) {
    std::clog << "unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
