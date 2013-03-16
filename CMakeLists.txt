cmake_minimum_required(VERSION 2.8.10)
project(unittest CXX)

#------------------------------------------------------------------------------
# Modules, Variables, and Options
#------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)
include(CTest)

set(INCLUDE_INSTALL_DIR "include" CACHE INTERNAL "Header Files")
set(LIBRARY_INSTALL_DIR "lib" CACHE INTERNAL "Library Files")

set(CMAKE_INSTALL_DIR "share/cmake/unittest" CACHE INTERNAL "CMake Files")

option(BUILD_UNITTEST_TESTS "Build the unittest's personal tests" OFF)

#------------------------------------------------------------------------------
# Compiler Environment Check
#------------------------------------------------------------------------------
if (NOT MSVC)
  check_cxx_compiler_flag("-stdlib=libc++" CAN_USE_LIBCXX)
  check_cxx_compiler_flag("-std=c++11" CAN_USE_CXX11)
  check_cxx_compiler_flag("-pedantic" CAN_USE_PEDANTIC)

  check_cxx_compiler_flag("-fexceptions" CAN_USE_EXCEPTIONS)
  check_cxx_compiler_flag("-Woverloaded-virtual" CAN_WARN_OVERLOADED_VIRTUAL)
  check_cxx_compiler_flag("-Wuseless-cast" CAN_WARN_USELESS_CAST)
  check_cxx_compiler_flag("-Wnoexcept" CAN_WARN_NOEXCEPT)
  check_cxx_compiler_flag("-Wextra" CAN_WARN_EXTRA)
  check_cxx_compiler_flag("-Wall" CAN_WARN_ALL)
else ()
  check_cxx_compiler_flag("/Ehsc" CAN_USE_EXCEPTIONS)

  check_cxx_compiler_flag("/WL" CAN_WARN_ONE_LINE)
  check_cxx_compiler_flag("/WX" CAN_WARN_ERROR)
  check_cxx_compiler_flag("/W4" CAN_WARN_ALL)
endif ()

if (CAN_USE_CXX11)
  set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -std=c++11")
endif ()

# XXX: This is temporary, and will be removed once a proper option to force
#      the use of libc++ if it is available, or use libstdc++ if available.
#      This will get a bit tricky for certain platforms, like Mac OS X, where
#      a custom build of gcc might exist that is newer than 4.2.1 (the last
#      gcc release on that platform from Apple)
if (CAN_USE_LIBCXX)
  set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -stdlib=libc++")
endif ()

# These headers are currently *required*
check_include_file_cxx(initializer_list HAVE_INITIALIZER_LIST)
check_include_file_cxx(type_traits HAVE_TYPE_TRAITS)
check_include_file_cxx(functional HAVE_FUNCTIONAL)
check_include_file_cxx(regex HAVE_REGEX)
check_include_file_cxx(tuple HAVE_TUPLE)

check_include_file_cxx(cstdint HAVE_CSTDINT)
check_include_file_cxx(cstddef HAVE_CSTDDEF)

# Handle insane environments
if (NOT HAVE_INITIALIZER_LIST)
  message(FATAL_ERROR "Could not locate required header <initializer_list>")
endif ()

if (NOT HAVE_TYPE_TRAITS)
  message(FATAL_ERROR "Could not locate required header <type_traits>")
endif ()

if (NOT HAVE_FUNCTIONAL)
  message(FATAL_ERROR "Could not locate required header <functional>")
endif ()

if (NOT HAVE_REGEX)
  message(FATAL_ERROR "Could not located required header <regex>")
endif ()

if (NOT HAVE_TUPLE)
  message(FATAL_ERROR "Could not locate required header <tuple>")
endif ()

if (NOT HAVE_CSTDINT)
  message(FATAL_ERROR "Could not locate required header <cstdint>")
endif ()

if (NOT HAVE_CSTDDEF)
  message(FATAL_ERROR "Could not locate required header <cstddef>")
endif ()

#------------------------------------------------------------------------------
# Configuration
#------------------------------------------------------------------------------
write_basic_package_version_file(
  ${PROJECT_BINARY_DIR}/unittest-config-version.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/configure/unittest-config.cmake.in
  ${PROJECT_BINARY_DIR}/unittest-config.cmake
  INSTALL_DESTINATION "${CMAKE_INSTALL_DIR}"
  PATH_VARS
  INCLUDE_INSTALL_DIR
  LIBRARY_INSTALL_DIR
)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
)

if (NOT MSVC)
  # TODO: See the note concerning this in the environment check section.
  if (CAN_USE_LIBCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  endif ()

  if (CAN_USE_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  endif ()

  if (CAN_USE_PEDANTIC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
  endif ()

  if (CAN_WARN_EXTRA)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
  endif ()

  if (CAN_WARN_ALL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  endif ()
  
  if (CAN_WARN_NOEXCEPT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnoexcept")
  endif ()

  if (CAN_WARN_USELESS_CAST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuseless-cast")
  endif ()
else ()
  if (CAN_WARN_ALL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif ()

  if (CAN_WARN_ONE_LINE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WL")
  endif ()
endif ()

add_library(unittest STATIC
  ${PROJECT_SOURCE_DIR}/lib/identity.cpp
  ${PROJECT_SOURCE_DIR}/lib/utility.cpp
  ${PROJECT_SOURCE_DIR}/lib/error.cpp
  ${PROJECT_SOURCE_DIR}/lib/test.cpp
  ${PROJECT_SOURCE_DIR}/lib/task.cpp
  ${PROJECT_SOURCE_DIR}/lib/skip.cpp
  ${PROJECT_SOURCE_DIR}/lib/safe.cpp
  ${PROJECT_SOURCE_DIR}/lib/run.cpp
)

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

install(TARGETS unittest
  LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
  ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}
)
