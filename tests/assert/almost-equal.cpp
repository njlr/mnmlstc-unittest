#include <iostream>
#include <string>

#include <cstdlib>

#include <unittest/assert.hpp>
#include <unittest/error.hpp>

void v1 () {
  using unittest::v1::error;
  namespace assert = unittest::v1::assert;

  try { assert::almost_equal(234.01012f, 234.01010f); }
  catch (...) {
    std::clog << "unexpected error was thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { assert::almost_equal(267.0002f, 267.000167f, 5); }
  catch (error const& e) {
    if (std::string { "almost-equal" } != e.type()) {
      std::clog << "unexpected error '" << e.type() << "' was thrown"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
    return;
  } catch (...) {
    std::clog << "unexpected error was thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "almost-equal error was not thrown as expected!"
            << std::endl;
  std::exit(EXIT_FAILURE);
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
