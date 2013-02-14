#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <cstdlib>

auto v1 () -> void {
  using namespace unittest::v1;

  try { self.fail(); }
  catch (identity_crisis const&) { return; }
  catch (...) {
    std::clog << "identity crisis did not occur" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "identity crisis did not occur" << std::endl;
  std::exit(EXIT_FAILURE);
}

auto main () -> int {
  v1();
  return EXIT_SUCCESS;
}
