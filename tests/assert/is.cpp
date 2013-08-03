#include <iostream>
#include <string>

#include <cstdlib>

#include <unittest/assert.hpp>
#include <unittest/error.hpp>

auto v1 () -> void {
  namespace assert = unittest::v1::assert;
  using unittest::v1::error;

  auto x = 1;
  auto const& y = x;

  try { assert::is(x, y); }
  catch (error const& e) {
    std::clog << "unexpected error thrown: " << e.type() << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (...) {
    std::clog << "unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  auto a = 1;
  auto b = a;

  try { assert::is(a, b); }
  catch (error const& e) {
    if (std::string { "is" } == e.type()) { return; }
    std::clog << "Unexpected error type thrown: " << e.type() << std::endl;
    std::exit(EXIT_FAILURE);
  }
  catch (...) {
    std::clog << "unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::clog << "WORD" << std::endl;

  std::clog << "is was not thrown" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  v1();
  return EXIT_SUCCESS;
}
