include(CPack)

message(STATUS "CPACK_PACKAGE_CONTACT: ${CPACK_PACKAGE_CONTACT}")
message(STATUS "CPACK_DEBIAN_PACKAGE_MAINTAINER: ${CPACK_DEBIAN_PACKAGE_MAINTAINER}")

set(CPACK_PACKAGE_NAME "forge")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VENDOR "FeatherNest")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Modern C++ package manager")
set(CPACK_PACKAGE_DESCRIPTION "A modern package manager for C++ projects")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/120MF/forge")
set(CPACK_PACKAGE_CONTACT "moonfeather120@outlook.com")

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")

set(CPACK_GENERATOR "DEB;TGZ;ZIP")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "MoonFeather <moonfeather120@outlook.com>")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.34), libstdc++6 (>= 12)")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

if (NOT CPACK_PACKAGE_CONTACT)
    message(FATAL_ERROR "CPACK_PACKAGE_CONTACT is not set")
endif ()

if (NOT CPACK_DEBIAN_PACKAGE_MAINTAINER)
    message(FATAL_ERROR "CPACK_DEBIAN_PACKAGE_MAINTAINER is not set")
endif ()

set(CPACK_RPM_PACKAGE_GROUP "Development/Tools")
set(CPACK_RPM_PACKAGE_LICENSE "ISC")
set(CPACK_RPM_PACKAGE_REQUIRES "glibc >= 2.34, libstdc++ >= 12")

set(CPACK_NSIS_DISPLAY_NAME "Forge Build System")
set(CPACK_NSIS_PACKAGE_NAME "Forge")
set(CPACK_NSIS_HELP_LINK "https://github.com/120MF/forge")
set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/120MF/forge")
set(CPACK_NSIS_CONTACT "moonfeather120@outlook.com")

set(CPACK_COMPONENTS_ALL Runtime Development)
set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime")
set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "Forge executable")
set(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "Development")
set(CPACK_COMPONENT_DEVELOPMENT_DESCRIPTION "Headers and libraries")