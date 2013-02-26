#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <memory>
#include <string>

#include <cstdlib>

void v1() {
  using unittest::v1::exception;
  using unittest::v1::self;

  std::unique_ptr<int> ptr { new int };

  try { self.assert_is_null(ptr.release()); }
  catch (exception const& e) {
    if (std::string { "assert_is_null" } != e.type()) {
      std::clog << "unexpected exception '" << e.type() << "' was thrown"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  } catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { self.assert_is_null(ptr.get()); }
  catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
