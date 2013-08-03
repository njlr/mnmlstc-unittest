#include <iostream>
#include <string>

#include <cstdlib>

#include <unittest/assert.hpp>
#include <unittest/error.hpp>

void v1 () {
  using unittest::v1::error;
  namespace assert = unittest::v1::assert;

  try { assert::not_almost_equal(234.0102f, 234.0101f); }
  catch (...) {
    std::clog << "unexpected error was thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { assert::not_almost_equal(267.000202f, 267.000203f, 5); }
  catch (error const& e) {
    if (std::string { "not-almost-equal" } == e.type()) { return; }
    std::clog << "unexpected error '" << e.type() << "' was thrown"
              << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (...) {
    std::clog << "unexpected error was thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "not-almost-equal error was not thrown as expected!"
            << std::endl;
  std::exit(EXIT_FAILURE);
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
