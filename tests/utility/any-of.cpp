#include <unittest/utility.hpp>
#include <type_traits>
#include <iostream>
#include <cstdlib>

auto main () -> int {
  bool truth = unittest::any_of<
    std::is_floating_point<int>,
    std::is_integral<int>
  >::value;

  if (not truth) {
    std::clog << "truth does not contain expected boolean value" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  bool lies = unittest::any_of<
    std::is_floating_point<int>,
    std::is_integral<float>
  >::value;

  if (lies) {
    std::clog << "2:any_of did not return expected boolean value" << std::endl;
    std::exit(EXIT_FAILURE);
  }
      
  return EXIT_SUCCESS;
}
