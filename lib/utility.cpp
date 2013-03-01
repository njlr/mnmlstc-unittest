#include <unittest/utility.hpp>

namespace unittest {
inline namespace v1 {

ostream& operator << (ostream& os, unknown_type const& value) {
  return os << "<unknown-type at "
            << reinterpret_cast<void*>(value.address) << ">";
}

}} /* namespace unittest::v1 */
