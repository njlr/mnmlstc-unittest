Unittest API
============

.. default-domain:: cpp

This section of the documentation discusses the publicly available API. If
you are unfamiliar with the concepts of how MNMLSTC Unittest works, it is
recommended that you read the :ref:`concepts <tutorial-concepts>` that
unittest relies on.

.. _api-tests:

Assertions
----------

.. namespace:: unittest

MNMLSTC Unittest provides a set of assertions beyond the basic equality
comparison set that is normally provided. A majority of these are taken from
the python unittest module in name. All of these assertions are located within
the ``assert`` namespace.

+-----------------------------------------------------+------------------+
| Assertions                                          | Checks That      |
+=====================================================+==================+
| :cpp:func:`equal(a, b)<assert::equal>`              | ``a == b``       |
+-----------------------------------------------------+------------------+
| :cpp:func:`not_equal(a, b)<assert::not_equal>`      | ``a != b``       |
+-----------------------------------------------------+------------------+
| :cpp:func:`is_true(a)<assert::is_true>`             | ``a == true``    |
+-----------------------------------------------------+------------------+
| :cpp:func:`is_false(a)<assert::is_false>`           | ``a == false``   |
+-----------------------------------------------------+------------------+
| :cpp:func:`is(a, b)<assert::is>`                    | ``&a == &b``     |
+-----------------------------------------------------+------------------+
| :cpp:func:`is_not(a, b)<assert::is_not>`            | ``&a != &b``     |
+-----------------------------------------------------+------------------+
| :cpp:func:`is_null(a)<assert::is_null>`             | ``a == nullptr`` |
+-----------------------------------------------------+------------------+
| :cpp:func:`is_not_null(a)<assert::is_not_null>`     | ``a != nullptr`` |
+-----------------------------------------------------+------------------+
| :cpp:func:`in(a, b)<assert::in>`                    | ``a in b``       |
+-----------------------------------------------------+------------------+
| :cpp:func:`not_in(a, b)<assert::not_in>`            | ``a not in b``   |
+-----------------------------------------------------+------------------+


.. function:: void assert::equal (first, second)
              void assert::not_equal (first, second)

   Tests that the first and second values are equal/not equal. If no
   operator == or operator != exists for the given types, the function will
   compile, but a runtime error will be thrown immediately. ``first`` and
   ``second`` may be of any type.

   :type first: Any valid type
   :type second: Any valid type

.. function:: void assert::is_true (value)
              void assert::is_false (value)

   Tests that the given value is true or false. This is done explicitly by
   calling ``bool(value)``.

   :type value: Any type that can be converted to a boolean, either implicitly
                or explicitly.

.. function:: void assert::is(first, second)
              void assert::is_not(first, second)

   Tests that first and second either occupy or do not occupy the same
   address of memory. ``first`` and ``second`` may be either const
   references or pointers to some object, but these cannot be interchanged.

.. function:: void assert::is_null(expr)
              void assert::is_not_null(expr)

   Tests that the given expression evaluates or does not evaluate to
   nullptr.

.. function:: void assert::in(first, second)
              void assert::not_in(first, second)

   Tests that the ``first`` is or is not located within ``second``. This
   assertion relies on the ability to call ``std::begin`` and ``std::end``
   on ``second``. If ``second`` cannot have ``std::begin`` and ``std::end``
   called on it, it will fail immediately once reached within the program.

   :type first: ``value_type`` of ``second``
   :type second: Any type that would result in a valid call to ``std::find``


There are also additional assertions to perform more specific checks, such as:

+-------------------------------------------------------------+-------------+
| Member Function                                             | Checks That |
+=============================================================+=============+
| :cpp:func:`almost_equal(a, b)<assert::almost_equal>`        | See Entry   |
+-------------------------------------------------------------+-------------+
| :cpp:func:`not_almost_equal(a, b)<assert::not_almost_equal>`| See Entry   |
+-------------------------------------------------------------+-------------+
| :cpp:func:`greater(a, b)<assert::greater>`                  | ``a > b``   |
+-------------------------------------------------------------+-------------+
| :cpp:func:`greater_equal(a, b)<assert::greater_equal>`      | ``a >= b``  |
+-------------------------------------------------------------+-------------+
| :cpp:func:`less(a, b)<assert::less>`                        | ``a < b``   |
+-------------------------------------------------------------+-------------+
| :cpp:func:`less_equal(a, b)<assert::less_equal>`            | ``a <= b``  |
+-------------------------------------------------------------+-------------+

.. function:: void assert::almost_equal(first, second, places)
              void assert::not_almost_equal(first, second, places)

   Test that *first* and *second* are approximately (or not approximately)
   equal by computing the difference, rounding the given number of decimal
   *places* (default 4), and comparing zero.

   .. note:: These functions round the values to the given number of decimal
             places and not *significant digits*. The operation performed can
             be expressed in python as ``round(first - second, places)``. This
             result is then compared against 0 for (in)equality

   :type first: float or double
   :type second: float or double
   :type places: int

.. function:: void assert::greater(first, second)
              void assert::greater_equal(first, second)
              void assert::less(first, second)
              void assert::less_equal(first, second)

   Test that *first* is respectively >, >=, < or <= than *second* depending
   on the method named. If not the test will fail. If *first* and *second*
   cannot be compared via these operators, the test will still successfully
   compile, but will immediately fail upon the statement being reached.

.. _api-skipping-tests:

Skipping Tests
--------------

.. highlight:: cpp

One can skip tests in unittest by using the various 'skip' types. These types
are constructed in the same manner as tasks. However, they sit in front of
tasks. For example::

    bool value = some_input;
    task("my-task") = skip_if(value, "value given was true") = []{
      assert::fail();
    };

.. class:: skip

   The default skip type simply takes a message. The function it is given will
   not be executed, or even passed along internally to the test runner.

   .. note:: While skip is not marked ``final`` in the API, it is not intended
             to be inherited from by the user.

   .. type:: function

      This type is simply a type alias for :cpp:type:`std::function\<void()>`

   .. function:: skip(const char* msg)

      Creates the skip object with a message to print. It is recommended that
      *msg* be a string literal, rather than stored elsewhere in memory.

   .. function:: function operator = (function&&) const noexcept

.. class:: skip_unless

   ``skip_unless`` takes a boolean and a message. The function it is given
   will not be executed *unless* the given boolean is true.

   ``skip_unless`` inherits from :cpp:class:`skip` privately, treating it
   more as a mixin, than a parent.

   .. function:: skip_unless(bool, const char*)

.. class:: skip_if

   ``skip_if`` takes a boolean and a message. The function it is given will not
   be executed *if* the given boolean is true.

   .. function:: skip_if(bool, const char*)
