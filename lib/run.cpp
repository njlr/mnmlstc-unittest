#include <unittest/identity.hpp>
#include <unittest/error.hpp>
#include <unittest/safe.hpp>
#include <unittest/run.hpp>

#include <string>

#include <cstdlib>

namespace unittest {
inline namespace v1 {

auto run () noexcept -> void {
  /* TODO install signal handlers */
  for (auto const& item : vault) {
    auto const& test_name = std::get<0>(item);
    auto const& task_name = std::get<1>(item);
    auto const& task = std::get<2>(item);

    try {
      task();
      std::clog << ".";
    } catch (skipping const& e) {
      std::clog << "S";
    } catch (exception const& e) {
      std::clog << "F";
    } catch (...) {
      std::clog << "F";// << std::endl;
    }
    self.reset();
  }
}

}} /* namespace unittest::v1 */
