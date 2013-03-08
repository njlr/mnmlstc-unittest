Overview
========

MNMLSTC Unittest is a C++11 unit testing framework. It focuses on being small,
minimal, expressive, and easy to use. Unlike most C++ unit testing frameworks
which rely on preprocessor macros, unittest tries to take a page from the
python unittest module, and as such it has *no preprocessor macros*.

Information on installing and using unittest (as well as modifying its
internals) can be found in its
`documentation <https://unittest.readthedocs.org/>`_.

MNMLSTC Unittest is released under the Apache 2.0 license.

Basic Example
--------------

Below is a basic example of how unittest can be used::

    #include <unittest/unittest.hpp>

    auto main () -> int {
      using namespace unittest;

      test("my-test") = {
        task("assert-equal") = [] {
          self.assert_equal(1, 2, "optional message");
          self.assert_throws<my_exception_type>([]{throw my_exception_type;});
        },
        task("fails") = [] { self.fail(); },
        task("skip") = skip("always-skip") = [] { self.fail(); }
      };

      run();
    }

Requirements
------------

There are several requirements to fully use unittest:

 * `CMake 2.8.10 <http://cmake.org>`_
 * A C++11 compliant compiler and standard library implementation
 * `Sphinx <http://sphinx-doc.org>`_
 * `Cloud Sphinx Theme <https://pypi.python.org/pypi/cloud_sptheme>`_

Sphinx and the Cloud Sphinx Theme are only necessary if generating the
documentation manually.
