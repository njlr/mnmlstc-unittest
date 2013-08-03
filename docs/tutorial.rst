Getting Started With Unittest
=============================

This tutorial will walk you through the basics of using MNMLSTC Unittest. It
will introduce to you the concepts that MNMLSTC Unittest introduces, as well
as explain *why* MNMLSTC Unittest works in the way it does, and does not take
the same approach to unit tests as many other C++ unit testing frameworks.

It should be noted, MNMLSTC Unittest assumes the following:

 * You are using CMake
 * You are using CTest as the test runner
 * You are using a C++11 compiler
 * Any code that interacts with MNMLSTC Unittest will have exceptions enabled

.. todo:: set a link to the API from here.

Additionally, this tutorial will not teach you everything you need to know to
effectively use MNMLSTC Unittest. It will show the most basic steps that need
to be taken to begin using MNMLSTC Unittest. To get a better idea of how
it works, see the API documentation.

.. _tutorial-concepts:

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
    unnecessary. This is a position that MNMLSTC Unittest takes.

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
it was. As such, MNMLSTC Unittest makes due with what it can.

One might notice, however, the absence of the common setup, teardown and
test fixture concepts. Because of RAII, it is deemed unnecessary for these to
be provided, simply because every other test framework implements them. There
is a way to imitate this kind of consistent setup and teardown via capturing
an object by value within a lambda declaration.

Additionally, initialization of resources can be postponed by simply
initializing them within a lambda, and this should be taken advantage of.

The most important part of MNMLSTC Unittest is that it tries to make you solve
the problem at hand: Do the components you are testing, work?

Your First Unittest Unit Test
-----------------------------

Well, enough about the concepts of Unittest. It's time to write our first
test!

.. highlight:: cpp

Because of how MNMLSTC Unittest works, we can declare any test anywhere within
the program, as long as it is within the scope of *some* function. For the
purposes of this tutorial, we'll simply place everything within main::

    #include <unittest/unittest.hpp>

    int main () {
      using namespace unittest;

      test("my-first-test") = {
        task("first-task") = []{ assert::fail("Not Yet Implemented"); },
        task("second-task") = []{ assert::fail("Not Yet Implemented"); }
      };

      monitor::run();
    }

And now, a brief explanation of just what in tarnation we think we're doing
here. First, we include the unittest amalgamation header. This header is
provided to insure that the proper namespaces and declarations are available
for the user.

Next, we do a ``using namespace unittest``. This is *absolutely* vital, as it
allows unittest to use its automatic value printing fallback without issue.

Now to get to the meat of the program. We declare a test with the name
"my-first-test". All tests (and tasks!) *should* use a string literal. However,
as of right now, their interface is to take a ``std::string&&``.

On the same line, we begin to assign an initialization_list of tasks. Just know
that the only way to submit tasks to a test case is to place them within
this initialization_list.

Tasks work almost like tests in that we assign a value to them after their
declaration. In the case of a task, it *always* takes a
``std::function<void()>`` by rvalue reference. This means anything you pass
into will not be used elsewhere. At that point, MNMLSTC Unittest now *owns*
that object and will do with it as it pleases. While it is possible to
construct a ``std::function<void()>`` with a variety of ways, it is easiest
to simply use a lambda. The lambda will allow for capturing fixtures (declared
with RAII) by value or by reference. Finally, because we really have nothing
to do, *yet*, we call ``assert::fail`` which will immediately make the test
runner stop handling the task.

Finally we call ``monitor::run()``, which is located in the unittest namespace.

.. note:: Make sure that this is the last function call you make. Whether 
          all tests and tasks pass or not is irrelevant, as it will *always*
          call ``std::exit``.

Of course, this only shows how to write a test, not use it with CMake or CTest.
So let's do that!

.. highlight:: cmake

Our CMakeLists.txt file will look like::

    cmake_minimum_required(VERSION 2.8.11)
    project(our-first-unittest-test CXX)

    find_package(unittest REQUIRED)
    include(CTest)

    include_directories(${UNITTEST_INCLUDE_DIR})

    add_executable(my-first-unittest-test ${PROJECT_SOURCE_DIR}/test.cpp)

    add_test(my-first-unittest my-first-unittest-test)

Fairly simple! Go ahead and build then run your tests. If you did everything
right (and let's be honest here, you totally did!), you should see ctest
giving you the 'FAILURE' output. That's fine, because we're going to start
expanding on our test file for the rest of the tutorial.

.. highlight:: cpp

Now that we've got our test building, it's time to get down and dirty with the
assertions. Go ahead and open up your test file. Within the first-task, we're
going to write the test to succeed now. Everybody loves math right? So let's do
some. Place the following within the first-task lambda (make sure to remove the
calls to ``assert::fail``)::

    assert::not_equal(1 + 2, 4);
    assert::equal(2 + 2, 4);

Fairly simple, but we're just trying to show that our assert_equal works!
Compile and run, and we'll still get the failure output. That's fine! We can
modify the second-task to be a bit more complex. Let's create a sequence and
see if it has a value or not. Place the following in the second-task lambda::

    std::vector<int> sequence = { 1, 2, 3, 4, 5, 6 };
    /* Assume you wish to do some work with the sequence here */
    assert::not_in(7, sequence);
    assert::in(4, sequence);

If we were to build and run our test, it should now succeed! Our unittest test
file should now look like this::

    #include <unittest/unittest.hpp>
    #include <vector>

    int main () {
      using namespace unittest;

      test("my-first-test") = {
        task("first-task") = []{
          assert::not_equal(1 + 2, 4);
          assert::equal(2 + 2, 4);
        },
        task("second-task") = []{
          std::vector<int> sequence = { 1, 2, 3, 4, 5, 6 };
          assert::not_in(7, sequence);
          assert::in(4, sequence);
        }
      };

      monitor::run();
    }

Pretty neat!
