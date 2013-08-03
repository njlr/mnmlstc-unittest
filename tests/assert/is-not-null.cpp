#include <iostream>
#include <memory>
#include <string>

#include <cstdlib>

#include <unittest/assert.hpp>
#include <unittest/error.hpp>

void v1() {
  using unittest::v1::error;
  namespace assert = unittest::v1::assert;

  std::unique_ptr<int> ptr { new int };

  try { assert::is_not_null(ptr.release()); }
  catch (...) {
    std::clog << "Unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { assert::is_not_null(ptr.get()); }
  catch (error const& e) {
    if (std::string { "is-not-null" } != e.type()) {
      std::clog << "Unexpected error '" << e.type() << "' thrown"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "Unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
