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

#option(BUILD_SHARED "Build unittest as a DLL" OFF)

set(INCLUDE_INSTALL_DIR "include" CACHE INTERNAL "Header Files")
set(LIBRARY_INSTALL_DIR "lib" CACHE INTERNAL "Library Files")

set(CMAKE_INSTALL_DIR "share/cmake/unittest" CACHE INTERNAL "CMake Files")

#------------------------------------------------------------------------------
# Compiler Environment Check
#------------------------------------------------------------------------------
if (NOT MSVC)
  check_cxx_compiler_flag("-stdlib=libc++" CAN_USE_LIBCXX)
  check_cxx_compiler_flag("-std=c++11" CAN_USE_CXX11)

  check_cxx_compiler_flag("-fno-omit-frame-pointer" CAN_USE_NO_OMIT_FRAME_PTR)
  check_cxx_compiler_flag("-fvisibility=hidden" CAN_USE_VISIBILITY_HIDDEN)
  check_cxx_compiler_flag("-fexceptions" CAN_USE_EXCEPTIONS)
  check_cxx_compiler_flag("-flto" CAN_USE_LTO)

  check_cxx_compiler_flag("-Wnoexcept" CAN_WARN_NOEXCEPT)
  check_cxx_compiler_flag("-Wall" CAN_WARN_ALL)
else ()
  check_cxx_compiler_flag("/Ehsc" CAN_USE_EXCEPTIONS)
  check_cxx_compiler_flag("/sdl" CAN_USE_SECURITY)
  check_cxx_compiler_flag("/GL" CAN_USE_LTO)

  check_cxx_compiler_flag("/WL" CAN_WARN_ONE_LINE)
  check_cxx_compiler_flag("/WX" CAN_WARN_ERROR)
  check_cxx_compiler_flag("/W4" CAN_WARN_ALL)
endif ()

check_include_file_cxx(initializer_list HAVE_INITIALIZER_LIST)
check_include_file_cxx(unordered_map HAVE_UNORDERED_MAP)
check_include_file_cxx(system_error HAVE_SYSTEM_ERROR)
check_include_file_cxx(type_traits HAVE_TYPE_TRAITS)
check_include_file_cxx(functional HAVE_FUNCTIONAL)
check_include_file_cxx(tuple HAVE_TUPLE)

check_include_file_cxx(cstdint HAVE_CSTDINT)
check_include_file_cxx(cstddef HAVE_CSTDDEF)

#------------------------------------------------------------------------------
# Configuration
#------------------------------------------------------------------------------
write_basic_package_version_file(
  ${PROJECT_BINARY_DIR}/unittest-config-version.cmake
  VERSION 0.1.0
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

if (CAN_USE_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

if (CAN_USE_WALL)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif ()

add_compiler_export_flags()
add_library(unittest STATIC
  ${PROJECT_SOURCE_DIR}/lib/suite.cpp
  ${PROJECT_SOURCE_DIR}/lib/test.cpp
  ${PROJECT_SOURCE_DIR}/lib/step.cpp
)

generate_export_header(unittest
  EXPORT_MACRO_NAME UNITTEST_EXPORT_API
  EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/unittest/export.hpp
  DEPRECATED_MACRO_NAME UNITTEST_DEPRECATED
)

#------------------------------------------------------------------------------
# Install
#------------------------------------------------------------------------------
install(FILES
  ${PROJECT_BINARY_DIR}/unittest-config-version.cmake
  ${PROJECT_BINARY_DIR}/unittest-config.cmake
  DESTINATION ${CMAKE_INSTALL_DIR}
)

install(FILES
  ${PROJECT_BINARY_DIR}/include/unittest/export.hpp
  DESTINATION ${INCLUDE_INSTALL_DIR}
)
