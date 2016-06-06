project(cirkuit)

cmake_minimum_required(VERSION 3.0)

find_package(ECM 1.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_SOURCE_DIR}/cmake_modules)

find_package(Qt5 5.2 REQUIRED COMPONENTS Quick)
find_package(KF5 REQUIRED COMPONENTS I18n ConfigWidgets DBusAddons DocTools KIO NewStuff TextEditor TextWidgets KDELibs4Support)
find_package(Poppler REQUIRED)

include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMInstallIcons)
include(GenerateExportHeader)

SET(CIRKUIT_VERSION "0.4.2")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/cirkuitconfig.h.in"
  "${PROJECT_BINARY_DIR}/cirkuitconfig.h"
)

add_subdirectory(src)
add_subdirectory(icons)
add_subdirectory(doc)
