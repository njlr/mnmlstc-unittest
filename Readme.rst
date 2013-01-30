Overview
========

MNMLSTC Unittest is a C++11 unit testing framework. It focuses on being small,
minimal, expressive, and easy to use. Unlike most C++ unit testing frameworks
which rely on the preprocessor macros, unittest tries to take a page from the
python unittest module. However, unittest was written for use with CMake (and
its test runner, CTest) in mind. If this is outside the scope or use of your
project, it would be best to look elsewhere.

Information on installing and using unittest (as well as modifying its
internals) can be found in its documentation.

MNMLSTC Unittest is released under the Apache 2.0 license.

Requirements
------------

There are several requirements to fully use unittest:

 * CMake 2.8.10
 * A C++11 compliant compiler and standard library implementation
 * Sphinx (documentation generation)
