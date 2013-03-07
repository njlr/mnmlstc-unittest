#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <iostream>
#include <cstdlib>

void v1 () {
  using unittest::v1::exception;
  using unittest::v1::self;

  try { self.assert_not_regex("abcdefg", "[0-9]"); }
  catch (...) {
    std::clog << "unexpected exception was thrown: " << std::endl;
    std::exit(EXIT_FAILURE);
  }

  try { self.assert_regex("abcdefg", "[a-z]"); }
  catch (exception const& e) {
    if (std::string { "assert_not_regex" } == e.type()) { return; }
    std::clog << "unexpected exception '" << e.type() << "' was thrown"
              << std::endl;
  } catch (...) {
    std::clog << "unexpected exception thrown" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::clog << "expected behavior has not occurred" << std::endl;
  std::exit(EXIT_FAILURE);
}

int main () {
  v1();
  return EXIT_SUCCESS;
}
