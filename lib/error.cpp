#include <unittest/error.hpp>

namespace unittest {
namespace v1 {

identity_crisis::identity_crisis (const char* reason) :
  std::runtime_error { reason }
{ }

skip_error::skip_error (const char* reason) :
  std::runtime_error { reason }
{ }

}} /* namespace unittest::v1 */
