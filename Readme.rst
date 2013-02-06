Overview
========

MNMLSTC Unittest is a C++11 unit testing framework. It focuses on being small,
minimal, expressive, and easy to use. Unlike most C++ unit testing frameworks
which rely on the preprocessor macros, unittest tries to take a page from the
python unittest module, and as such it has *no preprocessor macros*.

Information on installing and using unittest (as well as modifying its
internals) can be found in its documentation.

MNMLSTC Unittest is released under the Apache 2.0 license.

Basic Example
--------------

Below is a basic example of how unittest can be used::

    auto main () -> int {
      using namespace unittest;

      test("my-test") = {
        task("assert-equal") = [self] {
          self.assert_equal(1, 2, "optional message");
          self.assert_raises<my_exception_type>([]{throw my_exception_type;});
        },
        task("fails") = [self] { self.fail(); },
        task("skip") = skip("always-skip") = [self] { self.fail(); }
      };
    }

Requirements
------------

There are several requirements to fully use unittest:

 * CMake 2.8.10
 * A C++11 compliant compiler and standard library implementation
 * Sphinx (documentation generation)
