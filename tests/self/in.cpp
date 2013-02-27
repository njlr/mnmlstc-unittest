#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <string>

#include <cstdlib>

void v1 () {
  using unittest::v1::exception;
  using unittest::v1::self;

  std::string test { "12334566789" };
  try { self.assert_in('1', test); }
  catch (...) {
    std::clog << "Unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { self.assert_in('0', test); }
  catch (exception const& e) {
    if (std::string { "assert_in" } != e.type()) {
      std::clog << "unexpected exception '" << e.type() << "' was thrown"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
