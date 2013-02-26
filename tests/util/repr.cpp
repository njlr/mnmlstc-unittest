#include <unittest/utility.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <cstdlib>

int main () {
  using unittest::repr;

  std::vector<int> x { 1, 2, 3 };
  int y = 4;

  if (repr(y) != "4") {
    std::clog << "repr<int> returned unexpected value: " << repr(y)
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::ostringstream stream;
  stream << "<object at " << std::addressof(x) << ">";
  if (repr(x) != stream.str()) {
    std::clog << "repr<std::vector<int>> returned unexpected value: "
              << repr(x)
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
