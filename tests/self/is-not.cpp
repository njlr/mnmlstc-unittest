#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <cstdlib>

auto v1 () -> void {
  using unittest::v1::self;
  using unittest::v1::exception;

  auto x = 1;
  auto y = x;

  try { self.assert_is_not(x, y); }
  catch (exception const&) {
    std::clog << "unexpected assert_is_not thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  auto a = 1;
  auto const& b = a;

  try { self.assert_is_not(a, b); }
  catch (exception const&) { return; }
  catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "assert_is_not was not thrown" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  v1();
  return EXIT_SUCCESS;
}
