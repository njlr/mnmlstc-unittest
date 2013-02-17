#include <unittest/identity.hpp>
#include <unittest/error.hpp>
#include <unittest/safe.hpp>
#include <unittest/run.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <cstdlib>
#include <cstdint>
#include <csignal>

namespace {

auto install_handlers () noexcept -> void {
  std::signal(SIGSEGV, [](int) {
    std::clog << "Segmentation Fault Encountered." << std::endl;
    std::exit(EXIT_FAILURE);
  });
}

}

namespace unittest {
inline namespace v1 {

auto run () noexcept -> void {
  std::vector<std::string> results;
  std::uint64_t failures;
  ::install_handlers();

  for (auto const& item : vault) {
    std::ostringstream stream;
    auto const& test_name = std::get<0>(item);
    auto const& task_name = std::get<1>(item);
    auto const& task = std::get<2>(item);

    try { task(); }
    catch (skipping const& e) {
      stream << "[SKIP] " << test_name << "." << task_name << ": " << e.what();
      results.emplace_back(stream.str());
    } catch (exception const& e) {
      stream << "[FAIL] " << test_name << "." << task_name << ": "
             << "Assertion " << e.type() << " in statement " << e.count()
             << " " << e.what();
      results.emplace_back(stream.str());
      failures += 1;
    } catch (...) {
      stream << "[FAIL] " << test_name << "." << task_name << ":"
             << "Unhandled and Unknown Exception";
      results.emplace_back(stream.str());
      failures += 1;
    }
    self.reset();
  }

  for (auto&& result : results) { std::clog << result << std::endl; }
  std::exit(failures ? EXIT_FAILURE : EXIT_SUCCESS);
}

}} /* namespace unittest::v1 */
