PROJECT(dpic)
cmake_minimum_required(VERSION 2.6)

SET(dpic_SRCS dpic2.c dpic.c p2clib.c)
 
ADD_EXECUTABLE(dpic ${dpic_SRCS})
 
TARGET_LINK_LIBRARIES(dpic -lm)
 
install(TARGETS dpic RUNTIME DESTINATION bin)
