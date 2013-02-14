#include <unittest/utility.hpp>
#include <type_traits>
#include <iostream>
#include <cstdlib>

auto main () -> int {
  bool truth = unittest::all_of<
    std::is_floating_point<float>,
    std::is_integral<int>
  >::value;

  if (not truth) {
    std::clog << "truth does not contain expected boolean value" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  bool lies = unittest::all_of<
    std::is_integral<int>,
    std::is_floating_point<int>
  >::value;

  if (lies) {
    std::clog << "lies does not contain expected boolean value" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
