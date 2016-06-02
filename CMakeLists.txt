PROJECT(cirkuit)
 
cmake_minimum_required(VERSION 2.8.12)

# KF5 Port:
# A lot of CMake code that used to be provided by kdelibs is now provided 
# by the extra-cmake-modules package
# find_package(ECM REQUIRED NO_MODULE)
# set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

# include(KDECMakeSettings NO_POLICY_SCOPE)
# include(KDEInstallDirs)
# include(KDECompilerSettings)
# include(FeatureSummary)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)

MESSAGE(STATUS "     KDE4 support enabled : ${KDE4_DATA_DIR}")
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

SET(CIRKUIT_VERSION "0.4.99")

# Configure a header file to pass some CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/cirkuitconfig.h.in"
  "${PROJECT_BINARY_DIR}/cirkuitconfig.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
add_subdirectory(src)
add_subdirectory(icons)
add_subdirectory(doc)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)