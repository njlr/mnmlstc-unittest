#include <unittest/unittest.hpp>

int main () {
  using namespace unittest;

  test("first-test") = {
    task("step-two") = [] { assert::is_null(nullptr); },
    task("step-three") = [] {
      assert::not_equal(false, true);
      assert::equal(false, false);
    },
    task("step-four") = skip("because we can") = []{}
  };

  monitor::run();
}
