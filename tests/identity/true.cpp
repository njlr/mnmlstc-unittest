#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <cstdlib>

auto v1 () -> void {

}

auto main () -> int {
  v1();
  return EXIT_FAILURE;
}
