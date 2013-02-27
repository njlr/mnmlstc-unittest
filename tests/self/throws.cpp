#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <string>

#include <cstdlib>

void v1 () {
  using unittest::v1::exception;
  using unittest::v1::self;

  try {
    self.assert_throws<std::logic_error>([]{ throw std::logic_error { "" }; });
  } catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try {
    self.assert_throws<std::logic_error>([]{});
  } catch (exception const& e) {
    if (std::string { "assert_throws" } != e.type()) {
      std::clog << "unexpected exception '" << e.type() << "' was thrown"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "Unexpected exception throw" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
