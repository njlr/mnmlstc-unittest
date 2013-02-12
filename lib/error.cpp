#include <unittest/error.hpp>

namespace unittest {
inline namespace v1 {

skip_error::skip_error (const char* reason) :
  runtime_error { reason }
{ }

identity_crisis::identity_crisis () :
  runtime_error { "self was not captured by value or copied" }
{ }

failure::failure (const char* reason) :
  runtime_error { reason }
{ }

assert_false_error::assert_false_error (const char* reason) :
  runtime_error { reason }
{ }

assert_true_error::assert_true_error (const char* reason) :
  runtime_error { reason }
{ }

assert_is_not_error::assert_is_not_error (const char* reason) :
  runtime_error { reason }
{ }

assert_is_error::assert_is_error (const char* reason) :
  runtime_error { reason }
{ }

}} /* namespace unittest::v1 */
