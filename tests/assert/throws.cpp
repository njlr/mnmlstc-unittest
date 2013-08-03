#include <iostream>
#include <string>

#include <cstdlib>

#include <unittest/assert.hpp>
#include <unittest/error.hpp>

void v1 () {
  using unittest::v1::error;
  namespace assert = unittest::v1::assert;

  try {
    assert::throws<std::logic_error>([]{ throw std::logic_error { "" }; });
  } catch (...) {
    std::clog << "unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try {
    assert::throws<std::logic_error>([]{});
  } catch (error const& e) {
    if (std::string { "throws" } != e.type()) {
      std::clog << "unexpected error '" << e.type() << "' was thrown"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "Unexpected error throw" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
