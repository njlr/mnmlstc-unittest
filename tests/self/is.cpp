#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <cstdlib>

auto v1 () -> void {
  using unittest::v1::exception;
  using unittest::v1::self;

  auto x = 1;
  auto const& y = x;

  try { self.assert_is(x, y); }
  catch (exception const&) {
    std::clog << "unexpected assert_is_error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  auto a = 1;
  auto b = a;

  try { self.assert_is(a, b); }
  catch (exception const&) { return; }
  catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "assert_is_error was not thrown" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  v1();
  return EXIT_SUCCESS;
}
