cmake_minimum_required(VERSION 2.8.10)
project(unittest CXX)

#------------------------------------------------------------------------------
# Modules, Variables, and Options
#------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)
include(CMakeDependentOption)
include(GenerateExportHeader)
include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)
include(CTest)

set(INCLUDE_INSTALL_DIR "include" CACHE INTERNAL "Header Files")
set(CMAKE_INSTALL_DIR "share/cmake/unittest" CACHE INTERNAL "CMake Files")

set(UNITTEST_VERSION_MAJOR 1)
set(UNITTEST_VERSION_MINOR 0)
set(UNITTEST_VERSION_PATCH 0)
set(UNITTEST_VERSION
  ${UNITTEST_VERSION_MAJOR}.${UNITTEST_VERSION_MINOR}.${UNITTEST_VERSION_PATCH}
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/configure")

cmake_dependent_option(
  BUILD_WITH_LIBCXX "Use libc++ as the standard library" ON
  "USE_STDLIB_LIBCXX" OFF
)
option(BUILD_UNITTEST_TESTS "Build unittest's personal tests" OFF)

#------------------------------------------------------------------------------
# Compiler Environment Check
#------------------------------------------------------------------------------
set(USE_STDLIB_LIBCXX "-stdlib=libc++")
set(USE_STD_CXX11 "-std=c++11")

set(USE_EXCEPTIONS "-fexceptions")
set(USE_PEDANTIC "-pedantic")

set(WARN_EVERYTHING "-Weverything")
set(WARN_NOEXCEPT "-Wnoexcept")
set(WARN_ONE_LINE "-WL")
set(WARN_ERROR "-Werror")
set(WARN_EXTRA "-Wextra")
set(WARN_ALL "-Wall")

if (MSVC)
  set(USE_EXCEPTIONS "/Ehsc")
  set(USE_PEDANTIC "-Za")

  set(WARN_EVERYTHING "-Wall")
  set(WARN_ERROR "-WX")
  set(WARN_ALL "-W4")
endif ()

check_cxx_compiler_flag(${USE_STDLIB_LIBCXX} CAN_USE_STDLIB_LIBCXX)
check_cxx_compiler_flag(${USE_STD_CXX11} CAN_USE_STD_CXX11)

check_cxx_compiler_flag(${USE_EXCEPTIONS} CAN_USE_EXCEPTIONS)
check_cxx_compiler_flag(${USE_PEDANTIC} CAN_USE_PEDANTIC)

check_cxx_compiler_flag(${WARN_EVERYTHING} CAN_WARN_EVERYTHING)
check_cxx_compiler_flag(${WARN_NOEXCEPT} CAN_WARN_NOEXCEPT)
check_cxx_compiler_flag(${WARN_ONE_LINE} CAN_WARN_ONE_LINE)
check_cxx_compiler_flag(${WARN_ERROR} CAN_WARN_ERROR)
check_cxx_compiler_flag(${WARN_EXTRA} CAN_WARN_EXTRA)
check_cxx_compiler_flag(${WARN_ALL} CAN_WARN_ALL)

if (CAN_USE_STDLIB_LIBCXX AND BUILD_WITH_LIBCXX)
  set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${USE_STDLIB_LIBCXX}")
endif ()

if (CAN_USE_STD_CXX11)
  set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${USE_STD_CXX11}")
endif ()

# These headers are currently *required*
check_include_file_cxx(initializer_list HAVE_INITIALIZER_LIST)
check_include_file_cxx(type_traits HAVE_TYPE_TRAITS)
check_include_file_cxx(functional HAVE_FUNCTIONAL)
check_include_file_cxx(tuple HAVE_TUPLE)

check_include_file_cxx(cstdint HAVE_CSTDINT)
check_include_file_cxx(cstddef HAVE_CSTDDEF)

# Handle insane environments
if (NOT HAVE_INITIALIZER_LIST)
  message(FATAL_ERROR "standard header <initializer_list> could not be found")
endif ()

if (NOT HAVE_TYPE_TRAITS)
  message(FATAL_ERROR "standard header <type_traits> could not be found")
endif ()

if (NOT HAVE_FUNCTIONAL)
  message(FATAL_ERROR "standard header <functional> could not be found")
endif ()

if (NOT HAVE_TUPLE)
  message(FATAL_ERROR "standard header <tuple> could not be found")
endif ()

if (NOT HAVE_CSTDINT)
  message(FATAL_ERROR "standard header <cstdint> could not be found")
endif ()

if (NOT HAVE_CSTDDEF)
  message(FATAL_ERROR "standard header <cstddef> could not be found")
endif ()

#------------------------------------------------------------------------------
# Configuration
#------------------------------------------------------------------------------
write_basic_package_version_file(
  ${PROJECT_BINARY_DIR}/unittest-config-version.cmake
  VERSION ${UNITTEST_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/configure/unittest-config.cmake.in
  ${PROJECT_BINARY_DIR}/unittest-config.cmake
  INSTALL_DESTINATION "${CMAKE_INSTALL_DIR}"
  PATH_VARS
  INCLUDE_INSTALL_DIR
  CMAKE_INSTALL_DIR
)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
)

if (CAN_USE_STDLIB_LIBCXX AND BUILD_WITH_LIBCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_STDLIB_LIBCXX}")
endif ()

if (CAN_USE_STD_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_STD_CXX11}")
endif ()

if (CAN_USE_EXCEPTIONS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_EXCEPTIONS}")
endif ()

if (CAN_USE_PEDANTIC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_PEDANTIC}")
endif ()

if (CAN_WARN_NOEXCEPT)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_NOEXCEPT}")
endif ()

if (CAN_WARN_ONE_LINE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_ONE_LINE}")
endif ()

if (CAN_WARN_EXTRA)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_EXTRA}")
endif ()

if (CAN_WARN_ALL)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_ALL}")
endif ()

if (BUILD_TESTING AND BUILD_UNITTEST_TESTS)
  set(CMAKE_TEST_COMMAND ctest)
  set(TEST_SOURCE_DIR "${PROJECT_SOURCE_DIR}/tests")
  set(TEST_BINARY_DIR "${PROJECT_BINARY_DIR}/tests")
  add_subdirectory("${TEST_SOURCE_DIR}" "${TEST_BINARY_DIR}" EXCLUDE_FROM_ALL)
endif ()

#------------------------------------------------------------------------------
# Install
#------------------------------------------------------------------------------
install(FILES
  ${PROJECT_BINARY_DIR}/unittest-config-version.cmake
  ${PROJECT_BINARY_DIR}/unittest-config.cmake
  DESTINATION ${CMAKE_INSTALL_DIR}
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/unittest"
  DESTINATION ${INCLUDE_INSTALL_DIR}
  FILES_MATCHING PATTERN "*.hpp"
)

# TODO: Add BUILD_DOCS option

#------------------------------------------------------------------------------
# Package
#------------------------------------------------------------------------------
set(CPACK_GENERATOR "WIX")
set(CPACK_PACKAGE_NAME "MNMLSTC Unittest")
set(CPACK_PACKAGE_VENDOR "MNMLSTC")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
  "MNMLSTC Unittest - A C++11 unit test framework")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Readme.rst")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.rst")

set(CPACK_PACKAGE_VERSION_MAJOR ${UNITTEST_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${UNITTEST_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${UNITTEST_VERSION_PATCH})
# Intended for installers only, such as NSIS or MSIs
set(CPACK_PACKAGE_INSTALL_DIRECTORY "mnmlstc/${PROJECT_NAME}")

set(CPACK_WIX_UPGRADE_GUID "ECDABEC7-0153-42FD-A094-72923031B1EE")
set(CPACK_WIX_PRODUCT_GUID "*")
set(CPACK_WIX_PRODUCT_ICON "${CMAKE_CURRENT_SOURCE_DIR}/configure/mnmlstc.ico")
set(CPACK_WIX_LICENSE_RTF "${CMAKE_CURRENT_SOURCE_DIR}/configure/License.rtf")
set(CPACK_WIX_UI_BANNER "${CMAKE_CURRENT_SOURCE_DIR}/configure/banner.bmp")

include(CPack)
