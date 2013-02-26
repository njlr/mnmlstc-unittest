#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <string>

#include <cstdlib>

struct custom { };

void v1 () {
  using unittest::v1::exception;
  using unittest::v1::self;

  try { self.assert_equal(1, 1); }
  catch (...) {
    std::clog << "unexpected exception was thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { self.assert_equal(1, 2); }
  catch (exception const& e) {
    if (std::string { "assert_equal" } != e.type()) {
      std::clog << "unexpected exception '" << e.type() << "' was thrown"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { self.assert_equal(custom(), custom()); }
  catch (exception const& e) {
    if (std::string { "assert_equal" } != e.type()) {
      std::clog << "unexpected exception '" << e.type() << "' was thrown"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected exception was thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
