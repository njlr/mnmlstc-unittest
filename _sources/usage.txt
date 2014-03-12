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

Running Tests
-------------

The very last call in your test executable must absolutely be
``unittest::monitor::run``. MNMLSTC Unittest will exit after running all tests,
and expects that a user will not require additional information once the tests
are run. The return value of the executable will be how many tests passed or
failed.

API Deprecation
---------------

MNMLSTC Unittest takes advantage of inline namespaces to provide a forward
compatible ABI for future version. As of the first release, all parts of the
public API are located within the ``unittest::v1`` namespace. Future versions
will result in this namespace no longer being inline, and to use the older
API, one can simply replace ``using namespace unittest`` with ``using namespace
unittest::v1``. Otherwise, if you wish to use *the latest and greatest*, simply
leaving your code as it is, and updating on major releases is most definitely
an option.

It should be noted that MNMLSTC Unittest follows `Semantic Versioning
<http://semver.org>`_. As such, only when a new feature is added will a minor
release be incremented (such as adding a new assert function to the identity
type in the first release). Changes to the entire API and how it works, will
be reflected in *both* a new inline namespace as the default (e.g., v2) and
a major revision update. For instance adding non-failing versions of each
assertion function (to compete with the GTest)
