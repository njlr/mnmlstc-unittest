#ifndef UNITTEST_ERROR_HPP
#define UNITTEST_ERROR_HPP
#pragma once

#include <unittest/configure.hpp>
#include <unittest/export.hpp>

#include <stdexcept>

namespace unittest {
inline namespace v1 {

struct UNITTEST_EXPORT_API skip_error final : public std::runtime_error {
  explicit skip_error(const char*);
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_ERROR_HPP */
