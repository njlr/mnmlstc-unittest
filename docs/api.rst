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

   .. function:: void assert_equal (first, second, msg=nullptr)
                 void assert_not_equal (first, second, msg=nullptr)

      Tests that first and second are equal/not equal. If no
      ``operator ==`` or ``operator !=`` exists for the given types, the
      function will accept it, but fail immediately once reached. ``first``
      and ``second`` may be of any type.

      :type first: Any valid type
      :type second: Any valid type
      :type msg: const char*

   .. function:: void assert_true(exp, msg=nullptr)
                 void assert_false(exp, msg=nullptr)

      Tests that the given expression implicitly evaluates to true or
      false. Any types that require explicit boolean conversion must do
      so before being passed in as parameters.

   .. function:: void assert_is(first, second, msg=nullptr)
                 void assert_is_not(first, second, msg=nullptr)

      Tests that first and second either occupy or do not occupy the same
      address of memory. ``first`` and ``second`` may be either const
      references or pointers to some object, but these cannot be interchanged.

   .. function:: void assert_is_null(expr, msg=nullptr)
                 void assert_is_not_null(expr, msg=nullptr)

      Tests that the given expression evaluates or does not evaluate to
      nullptr.

   .. function:: void assert_in(first, second, msg=nullptr)
                 void assert_not_in(first, second, msg=nullptr)

      Tests that the ``first`` is or is not located within ``second``. This
      assertion relies on the ability to call ``std::begin`` and ``std::end``
      on ``second``. If ``second`` cannot have ``std::begin`` and ``std::end``
      called on it, it will fail immediately once reached within the program.

      :type first: ``value_type`` of ``second``
      :type second: Any container type that can have ``std::begin`` and
                    ``std::end`` called on it.

   There are also additional member functions to perform more specific checks
   such as:

   +------------------------------------------+------------------------+
   | Member Function                          | Checks That            |
   +==========================================+========================+
   | :cpp:func:`assert_almost_equal(a, b)     | ``round(a-b, 7) == 0`` |
   | <identity::assert_almost_equal>`         |                        |
   +------------------------------------------+------------------------+
   | :cpp:func:`assert_not_almost_equal(a, b) | ``round(a-b, 7) != 0`` |
   | <identity::assert_not_almost_equal>`     |                        |
   +------------------------------------------+------------------------+
   | :cpp:func:`assert_greater(a, b)          | ``a > b``              |
   | <identity::assert_greater>`              |                        |
   +------------------------------------------+------------------------+
   | :cpp:func:`assert_greater_equal(a, b)    | ``a >= b``             |
   | <identity::assert_greater_equal>`        |                        |
   +------------------------------------------+------------------------+
   | :cpp:func:`assert_less(a, b)             | ``a < b``              |
   | <identity::assert_less>`                 |                        |
   +------------------------------------------+------------------------+
   | :cpp:func:`assert_less_equal(a, b)       | ``a <= b``             |
   | <identity::assert_less_equal>`           |                        |
   +------------------------------------------+------------------------+
   | :cpp:func:`assert_regex(s, re)           | ``regex_search(s, re)``|
   | <identity::assert_regex>`                |                        |
   +------------------------------------------+------------------------+
   | :cpp:func:`assert_not_regex(s, re)       | ``not                  |
   | <identity::assert_not_regex>`            | regex_search(s, re)``  |
   +------------------------------------------+------------------------+

.. _api-skipping-tests:

Skipping Tests
--------------
