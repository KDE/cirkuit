PROJECT(cirkuit)
 
cmake_minimum_required(VERSION 2.6)
SET(CMAKE_BUILD_TYPE Release)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
add_subdirectory(src)
add_subdirectory(icons)
