#ifndef UNITTEST_ERROR_HPP
#define UNITTEST_ERROR_HPP
#pragma once

#include <unittest/export.hpp>

#include <stdexcept>

namespace unittest {
inline namespace v1 {

using std::runtime_error;

struct UNITTEST_EXPORT_API skip_error final : public runtime_error {
  explicit skip_error (const char*);
};

struct UNITTEST_EXPORT_API identity_crisis final : public runtime_error {
  explicit identity_crisis (const char*);
};

struct UNITTEST_EXPORT_API failure final : public runtime_error {
  explicit failure (const char*);
};

struct UNITTEST_EXPORT_API assert_false_error final : public runtime_error {
  explicit assert_false_error (const char*);
};

struct UNITTEST_EXPORT_API assert_true_error final : public runtime_error {
  explicit assert_true_error (const char*);
};

struct UNITTEST_EXPORT_API assert_is_not_error final : public runtime_error {
  explicit assert_is_not_error (const char*);
};

struct UNITTEST_EXPORT_API assert_is_error final : public runtime_error {
  explicit assert_is_error (const char*);
};

}} /* namespace unittest::v1 */

#endif /* UNITTEST_ERROR_HPP */
