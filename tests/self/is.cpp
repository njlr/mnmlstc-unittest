#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <string>

#include <cstdlib>

auto v1 () -> void {
  using unittest::v1::exception;
  using unittest::v1::self;

  auto x = 1;
  auto const& y = x;

  try { self.assert_is(x, y); }
  catch (exception const& e) {
    std::clog << "unexpected exception thrown: " << e.type() << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  auto a = 1;
  auto b = a;

  try { self.assert_is(a, b); }
  catch (exception const& e) {
    if (std::string { "assert_is" } == e.type()) { return; }
    std::clog << "Unexpected exception type thrown: " << e.type() << std::endl;
    std::exit(EXIT_FAILURE);
  }
  catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "assert_is was not thrown" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  v1();
  return EXIT_SUCCESS;
}
