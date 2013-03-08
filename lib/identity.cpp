#include <unittest/identity.hpp>
#include <unittest/error.hpp>

#include <sstream>
#include <string>
#include <limits>
#include <regex>

#include <cmath>

/* Used to solve ambiguity between identity member functions and
 * assertion exceptions
 */

namespace unittest {
inline namespace v1 {

using namespace std::regex_constants;
using std::regex_search;
using std::string;

identity::identity () noexcept : statement { 0 } { }
identity::~identity () noexcept { }

identity& identity::instance () noexcept {
  static identity self;
  return self;
}

void identity::reset () noexcept { this->statement = 0; }

void identity::assert_true (bool cond, cstring msg) {
  this->statement += 1;
  if (cond) { return; }
  throw exception {
    "assert_true",
    msg ? msg : "condition evaluted false",
    this->statement
  };
}

auto identity::assert_false (bool cond, cstring msg) -> void {
  this->statement += 1;
  if (not cond) { return; }
  throw exception {
    "assert_false",
    msg ? msg : "condition evaluated false",
    this->statement
  };
}

void identity::assert_is (intptr_t lhs, intptr_t rhs, cstring msg) {
  this->statement += 1;
  if (lhs == rhs) { return; }
  std::ostringstream stream;
  if (msg) { stream << msg; }
  else { stream << std::hex << lhs << " is not the same as " << rhs; }
  throw exception { "assert_is", stream.str(), this->statement };
}

void identity::assert_is_not (intptr_t lhs, intptr_t rhs, cstring msg) {
  this->statement += 1;
  if (lhs != rhs) { return; }
  std::ostringstream stream;
  if (msg) { stream << msg; }
  else { stream << std::hex << lhs << " is the same as " << rhs; }
  throw exception { "assert_is_not", stream.str(), this->statement };
}

void identity::assert_is_null (intptr_t value, cstring msg) {
  this->statement += 1;
  void* ptr = reinterpret_cast<void*>(value);
  if (ptr == nullptr) { return; }
  throw exception {
    "assert_is_null", 
    msg ? msg : "Given pointer is not null",
    this->statement
  };
}

void identity::assert_is_not_null (intptr_t value, cstring msg) {
  this->statement += 1;
  void* ptr = reinterpret_cast<void*>(value);
  if (ptr != nullptr) { return; }
  throw exception {
    "assert_is_not_null",
    msg ? msg : "Given pointer is not null",
    this->statement
  };
}

void identity::assert_almost_equal (double, double, int, cstring) {
  this->statement += 1;
  throw exception {
    "assert_almost_equal",
    "Not Yet Implemented",
    this->statement
  };
}

void identity::assert_almost_equal (float, float, int, cstring) {
  this->statement += 1;
  throw exception {
    "assert_almost_equal",
    "Not Yet Implemented",
    this->statement
  };
}

void identity::assert_not_almost_equal (double, double, int, cstring) {
  this->statement += 1;
  throw exception {
    "assert_not_almost_equal",
    "Not Yet Implemented",
    this->statement
  };
}

void identity::assert_not_almost_equal (float, float, int, cstring) {
  this->statement += 1;
  throw exception {
    "assert_not_almost_equal",
    "Not Yet Implemented",
    this->statement
  };
}

void identity::assert_regex(
  string const& text,
  string const& regex,
  syntax_option_type syntax,
  match_flag_type flag,
  cstring msg
) {
  this->statement += 1;
  std::regex re;
  try { re = std::regex { regex, syntax }; }
  catch (std::regex_error const& e) {
    std::ostringstream stream;
    stream << "Could not construct regex object: " << e.what();
    throw exception { "assert_regex", stream.str(), this->statement };
  }

  if (regex_search(text, re, flag)) { return; }
  throw exception {
    "assert_regex",
    this->message(regex, text, "not found in", msg),
    this->statement
  };
}

void identity::assert_not_regex(
  string const& text,
  string const& regex,
  syntax_option_type syntax,
  match_flag_type flag,
  cstring msg
) {
  this->statement += 1;
  std::regex re;
  try { re = std::regex { regex, syntax }; }
  catch (std::regex_error const& e) { return; }

  if (regex_search(text, re, flag)) { return; }
  throw exception {
    "assert_not_regex",
    this->message(regex, text, "found in", msg),
    this->statement
  };
}

void identity::fail (cstring msg) {
  this->statement += 1;
  throw exception {
    "fail",
    msg ? msg : "immediate failure requested",
    this->statement
  };
}

UNITTEST_EXPORT_API identity& self = identity::instance();

}} /* namespace unittest::v1 */
