#include <unittest/assert.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <string>

#include <cstdlib>

void v1 () {
  using unittest::v1::error;
  namespace assert = unittest::v1::assert;

  std::string test { "12334566789" };
  try { assert::in('1', test); }
  catch (...) {
    std::clog << "Unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { assert::in('0', test); }
  catch (error const& e) {
    if (std::string { "in" } != e.type()) {
      std::clog << "unexpected error '" << e.type() << "' was thrown"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { assert::in(1, 2); }
  catch (error const& e) {
    if (std::string { "in" } != e.type()) {
        std::clog << "unexpected error '" << e.type() << "' was thrown"
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
