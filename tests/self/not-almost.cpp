#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <string>

#include <cstdlib>

void v1 () {
  using unittest::v1::exception;
  using unittest::v1::self;

  try { self.assert_not_almost_equal(234.0102f, 234.0101f); }
  catch (...) {
    std::clog << "unexpected exception was thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { self.assert_not_almost_equal(267.000202f, 267.000203f, 5); }
  catch (exception const& e) {
    if (std::string { "assert_not_almost_equal" } == e.type()) { return; }
    std::clog << "unexpected exception '" << e.type() << "' was thrown"
              << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (...) {
    std::clog << "unexpected exception was thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "assert_not_almost_equal exception was not thrown as expected!"
            << std::endl;
  std::exit(EXIT_FAILURE);
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
