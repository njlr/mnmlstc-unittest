Getting Started With Unittest
=============================

This tutorial will walk you through the basics of using MNMLSTC Unittest. It
will introduce to you the concepts that MNMLSTC Unittest introduces, as well
as explain *why* MNMLSTC Unittest works in the way it does.

It should be noted, MNMLSTC Unittest assumes the following:

 * You are using CMake
 * You are using CTest as the test runner
 * You are using a C++11 compiler
 * Any code that interacts with MNMLSTC Unittest will have exceptions enabled

Concepts
--------

Unittest differs from most unit testing libraries in their naming conventions.
This section will discuss how these naming conventions result in a few
*technical* conceptual differences. At the end of the day, however, they are
all the same. You have cases, suites, tests, and fixtures. When explaining the
differences, similarities to other frameworks (such as GTest, Unity, or
python's unittest module) will be made.

.. glossary::

   test suite
    For unittest, the resulting executable produced from CMake is your test
    suite. One could argue that organizing suites within suites ad infinitum is
    unnecessary. This is an argument that MNMLSTC Unittest makes.

   test case
    Unlike python's unittest or GTest, the 'test case' in MNMLSTC Unittest is
    just a 'test'. Tests are made up of steps, or tasks. A case, technically
    speaking, is a collection of steps taken to ensure that your code is
    sane. So, while other systems refer to a collection of tasks as a test
    case, MNMLSTC Unittest calls these a test.

   test step
    A step is placed within a test. They can fail, pass, or skip. They are,
    outside of a single assertion statement, the smallest unit of execution
    within MNMLSTC Unittest, and where most of your work will go.

As you can see from the *very* brief explanations, MNMLSTC Unittest doesn't
differ much from other unit testing libraries. However, in the realm of C++,
it does differ in one major way: *There are absolutely no preprocessor macros*.
But why would MNMLSTC Unittest have none of these?

When it comes to the preprocessor macros, one has to understand what these
macros actually do to understand any potential compiler errors. And at runtime,
we aren't given an idea of *why* the assertion failed (e.g., what are the
values inside of the tested variables, rather than what their names are/what
line it all happens on?). Python's unittest does this well (and it comes as a
result of its ability to perform runtime reflection on variables, as well as
know the current line), but C++ is not python, no matter how hard one wished
it was. As such, MNMLSTC makes due with what it can.
