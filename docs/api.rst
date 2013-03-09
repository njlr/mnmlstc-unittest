Unittest API
============

.. default-domain:: cpp

This section of the documentation discusses the publicly available API. If
you are unfamiliar with the concepts of how MNMLSTC Unittest works, it is
recommended that you read the :ref:`concepts <tutorial-concepts>` that
unittest relies on.

.. _api-tests:

Tests and Tasks
---------------

.. namespace:: unittest

.. class:: unittest::identity

   The identity type is available as a global variable under the name ``self``.
   It provides a number of member functions to check for and report failures,
   such as:

   +-----------------------------------+------------------+
   | Member Function                   | Checks That      |
   +===================================+==================+
   | :cpp:func:`assert_equal(a, b)     | ``a == b``       |
   | <identity::assert_equal>`         |                  |
   +-----------------------------------+------------------+
   | :cpp:func:`assert_not_equal(a, b) | ``a != b``       |
   | <identity::assert_not_equal>`     |                  |
   +-----------------------------------+------------------+
   | :cpp:func:`assert_true(a)         | ``a == true``    |
   | <identity::assert_true>`          |                  |
   +-----------------------------------+------------------+
   | :cpp:func:`assert_false(a)        | ``a == false``   |
   | <identity::assert_false>`         |                  |
   +-----------------------------------+------------------+
   | :cpp:func:`assert_is(a, b)        | ``&a == &b``     |
   | <identity::assert_is>`            |                  |
   +-----------------------------------+------------------+
   | :cpp:func:`assert_is_not(a, b)    | ``&a != &b``     |
   | <identity::assert_is_not>`        |                  |
   +-----------------------------------+------------------+
   | :cpp:func:`assert_is_null(a)      | ``a == nullptr`` |
   | <identity::assert_is_null>`       |                  |
   +-----------------------------------+------------------+
   | :cpp:func:`assert_is_not_null(a)  | ``a != nullptr`` |
   | <identity::assert_is_not_null>`   |                  |
   +-----------------------------------+------------------+
   | :cpp:func:`assert_in(a, b)        | ``a in b``       |
   | <identity::assert_in>`            |                  |
   +-----------------------------------+------------------+
   | :cpp:func:`assert_not_in(a, b)    | ``a not in b``   |
   | <identity::assert_not_in>`        |                  |
   +-----------------------------------+------------------+

   .. function:: void assert_equal (T const& first, U const& second)

      Asserts that first and second are equal by way of ``operator ==``. If
      no ``operator ==`` exists for the given types, the function will still
      take them as arguments and compile without issue. It will however,
      immediately fail upon being reached. ``first`` and ``second`` may be of
      any type.

      :raises: exception if first is not equal to second

   .. function:: void assert_not_equal (T const& first, U const& second)

      Asserts that first and second are not equal by way of ``operator !=``.
      If no ``operator !=`` exists for the given types, the function will
      still take them and compile without issue. It will result in an immediate
      failure however.

      :raises: exception if first is not equal to second

   .. function:: void assert_true(bool)

      Asserts that the given boolean value is true. Any type that is implicitly
      convertible to bool may be passed in (such as smart pointers). Those
      types that require explicit boolean conversion must do so themselves.

      :raises: exception if the given boolean value does not evaluate to true.

   .. function:: void assert_false(bool)

      Asserts that the given boolean value is false. Any type that is
      implicitly convertible to bool may be passed in (such as smart pointers).
      Those types that require explicit boolean conversion must do so
      themselves.

      :raises: exception if the given boolean value does not evaluate to false.

.. _api-skipping-tests:

Skipping Tests
--------------
