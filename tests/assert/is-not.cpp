#include <iostream>
#include <cstdlib>

#include <unittest/assert.hpp>
#include <unittest/error.hpp>

auto v1 () -> void {
  using unittest::v1::error;
  namespace assert = unittest::v1::assert;

  auto x = 1;
  auto y = x;

  try { assert::is_not(x, y); }
  catch (error const&) {
    std::clog << "unexpected assert_is_not thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (...) {
    std::clog << "unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  auto a = 1;
  auto const& b = a;

  try { assert::is_not(a, b); }
  catch (error const&) { return; }
  catch (...) {
    std::clog << "unexpected error thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "assert_is_not was not thrown" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  v1();
  return EXIT_SUCCESS;
}
