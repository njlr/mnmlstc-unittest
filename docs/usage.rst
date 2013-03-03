Using Unittest
==============

This section of the documentation goes into detail on how to use the MNMLSTC
Unittest API to its fullest, as well as how to best add functionality to
help MNMLSTC Unittest give better error reports.

Printing Values
---------------

MNMLSTC Unittest's errors utilize the ``std::ostringstream`` type to create
their messages. If a given type does not have a stream insertion operator
overload, it will default to printing ``<unknown-type at [some hex address]>``.
To remove this and print your own values, it is recommended to write a custom
insertion operator for an ``std::ostream``.
