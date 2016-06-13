project(cirkuit)

set(CIRKUIT_VERSION "0.4.99")

cmake_minimum_required(VERSION 3.0)

# KF5 Port:
# A lot of CMake code that used to be provided by kdelibs is now provided 
# by the extra-cmake-modules package
find_package(ECM 5.18 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(Qt5 5.2 REQUIRED COMPONENTS Quick)
find_package(KF5 REQUIRED COMPONENTS I18n ConfigWidgets DBusAddons DocTools KIO NewStuff TextEditor TextWidgets KDELibs4Support)
find_package(Poppler REQUIRED COMPONENTS Qt5)

include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMInstallIcons)
include(GenerateExportHeader)

# Configure a header file to pass some CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/cirkuitconfig.h.in"
  "${PROJECT_BINARY_DIR}/cirkuitconfig.h"
)

add_subdirectory(src)
add_subdirectory(icons)
add_subdirectory(doc)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
