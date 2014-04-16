cmake_minimum_required(VERSION 2.8.11)
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
set(DOCS_INSTALL_DIR "share/doc/mnmlstc/unittest" CACHE INTERNAL "")

set(UNITTEST_VERSION_MAJOR 1)
set(UNITTEST_VERSION_MINOR 0)
set(UNITTEST_VERSION_PATCH 4)
set(UNITTEST_VERSION
  ${UNITTEST_VERSION_MAJOR}.${UNITTEST_VERSION_MINOR}.${UNITTEST_VERSION_PATCH}
)

set(TEST_SOURCE_DIR "${PROJECT_SOURCE_DIR}/tests")
set(TEST_BINARY_DIR "${PROJECT_BINARY_DIR}/tests")

set(DOCS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/docs")
set(DOCS_BINARY_DIR "${PROJECT_BINARY_DIR}/docs")

set(PACK_SOURCE_DIR "${PROJECT_SOURCE_DIR}/package")
set(PACK_BINARY_DIR "${PROJECT_BINARY_DIR}/package")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/configure")

# Used by cmake-dependent-option
list(APPEND RPM_DEP "UNIX" "NOT APPLE" "BUILD_PACKAGE")
list(APPEND DEB_DEP "UNIX" "NOT APPLE" "BUILD_PACKAGE")
list(APPEND PKG_DEP "APPLE" "BUILD_PACKAGE")
list(APPEND MSI_DEP "WIN32" "BUILD_PACKAGE")

option(BUILD_UNITTEST_TESTS "Build unittest's personal tests" OFF)
option(BUILD_WITH_LIBCXX "Uses libc++ as stdlib" OFF)
option(BUILD_PACKAGE "Build package information with CPack" OFF)
option(BUILD_DOCS "Build documentation with Sphinx Documentation Generator" OFF)

cmake_dependent_option(BUILD_PACKAGE_MSI "Create an MSI" ON "${MSI_DEP}" OFF)
cmake_dependent_option(BUILD_PACKAGE_RPM "Create an RPM" ON "${RPM_DEP}" OFF)
cmake_dependent_option(BUILD_PACKAGE_DEB "Create a DEB" ON "${DEB_DEP}" OFF)
cmake_dependent_option(BUILD_PACKAGE_PKG "Create a PKG" ON "${PKG_DEP}" OFF)

if (APPLE AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(BUILD_WITH_LIBCXX ON CACHE BOOL "Use libc++ as stdlib" FORCE)
endif ()

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
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  VERSION ${UNITTEST_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/configure/${PROJECT_NAME}-config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_DIR}"
  PATH_VARS
  INCLUDE_INSTALL_DIR
  CMAKE_INSTALL_DIR
)

include_directories("${PROJECT_SOURCE_DIR}/include")

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
  add_subdirectory("${TEST_SOURCE_DIR}" "${TEST_BINARY_DIR}" EXCLUDE_FROM_ALL)
endif ()

if (BUILD_DOCS)
  add_subdirectory("${DOCS_SOURCE_DIR}" "${DOCS_BINARY_DIR}" EXCLUDE_FROM_ALL)
endif ()

if (BUILD_PACKAGE)
  add_subdirectory("${PACK_SOURCE_DIR}" "${PACK_BINARY_DIR}" EXCLUDE_FROM_ALL)
endif ()

#------------------------------------------------------------------------------
# Install
#------------------------------------------------------------------------------
install(FILES
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  DESTINATION ${CMAKE_INSTALL_DIR}
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/unittest"
  DESTINATION ${INCLUDE_INSTALL_DIR}
  FILES_MATCHING PATTERN "*.hpp"
)

if (BUILD_DOCS)
  install(DIRECTORY "${DOCS_BINARY_DIR}/"
    DESTINATION ${DOCS_INSTALL_DIR}
    FILES_MATCHING
    PATTERN ".buildinfo" EXCLUDE
    PATTERN "CMakeFiles" EXCLUDE
    PATTERN ".doctrees" EXCLUDE
    PATTERN "Makefile" EXCLUDE
    PATTERN "*.cmake" EXCLUDE
    PATTERN "*"
  )
endif ()
