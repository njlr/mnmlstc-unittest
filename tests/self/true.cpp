#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <cstdlib>

auto v1 () -> void {
  using unittest::v1::exception;
  using unittest::v1::self;

  try { self.assert_true(true); }
  catch (exception const&) {
    std::clog << "unexpected assert_true thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { self.assert_true(false); }
  catch (exception const&) { return; }
  catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "assert_true was not thrown" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  v1();
  return EXIT_SUCCESS;
}
