#include <unittest/error.hpp>

namespace unittest {
namespace v1 {

skip_error::skip_error (const char* reason) : std::runtime_error { reason } { }

}} /* namespace unittest::v1 */
