list(APPEND GENERATORS "TGZ" "ZIP")

if (BUILD_PACKAGE_MSI)
  list(APPEND GENERATORS "WIX")
endif ()

if (BUILD_PACKAGE_PKG)
# disabled until a replacement is found
#  list(APPEND GENERATORS "PackageMaker")
endif ()

if (BUILD_PACKAGE_DEB)
  list(APPEND GENERATORS "DEB")
endif ()

if (BUILD_PACKAGE_RPM)
  list(APPEND GENERATORS "RPM")
endif ()

#------------------------------------------------------------------------------
# Generic Package
#------------------------------------------------------------------------------
set(CPACK_OUTPUT_FILE_PREFIX ${PACK_BINARY_DIR})

set(CPACK_GENERATOR ${GENERATORS})
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "MNMLSTC")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++11 unit test framework")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/Readme.rst")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/License.rst")

set(CPACK_PACKAGE_VERSION_MAJOR ${UNITTEST_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${UNITTEST_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${UNITTEST_VERSION_PATCH})

# Intended for installers such as NSIS or WIX
set(CPACK_PACKAGE_INSTALL_DIRECTORY "mnmlstc/${PROJECT_NAME}")

#------------------------------------------------------------------------------
# Wix Configuration
#------------------------------------------------------------------------------
set(CPACK_WIX_UPGRADE_GUID "ECDABEC7-0153-42FD-A094-72923031B1EE")
set(CPACK_WIX_PRODUCT_GUID "*")
set(CPACK_WIX_PRODUCT_ICON "${PACK_SOURCE_DIR}/mnmlstc.ico")
set(CPACK_WIX_LICENSE_RTF "${PACK_SOURCE_DIR}/License.rtf")
set(CPACK_WIX_UI_BANNER "${PACK_SOURCE_DIR}/banner.bmp")
set(CPACK_WIX_UI_DIALOG "${PACK_SOURCE_DIR}/dialog.bmp")

#------------------------------------------------------------------------------
# DEB Configuration
#------------------------------------------------------------------------------
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE any)

#------------------------------------------------------------------------------
# RPM Configuration
#------------------------------------------------------------------------------
set(CPACK_RPM_PACKAGE_ARCHITECTURE noarch)
set(CPACK_RPM_PACKAGE_REQUIRES "cmake >= 2.8.11")
set(CPACK_RPM_PACKAGE_RELEASE ${UNITTEST_VERSION})

include(CPack)
