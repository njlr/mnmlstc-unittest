#include <unittest/unittest.hpp>

#include <cstdlib>

auto main () -> int {
  using namespace unittest;

  test("first-test") = {
    task("step-one") = []{ self.fail(); },
    task("step-two") = [] { self.assert_is_null((int*)nullptr); },
    task("step-three") = [] {
      self.assert_false(false);
      self.assert_true(true);
    },
    task("step-four") = skip("because we can") = []{}
  };

  run();
}
