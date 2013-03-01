#include <unittest/utility.hpp>

namespace unittest {

ostream& operator << (ostream& os, unknown_type const& value) {
  return os << "<unknown-type at "
            << reinterpret_cast<void*>(value.address) << ">";
}

} /* namespace unittest */
