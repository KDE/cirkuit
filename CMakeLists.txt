PROJECT(cirkuit)
 
cmake_minimum_required(VERSION 2.6)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)

MESSAGE(STATUS "     KDE4 support enabled : ${KDE4_DATA_DIR}")
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake_modules)

SET(CIRKUIT_VERSION "0.4.99")

# configure a header file to pass some of the CMake settings
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
