cmake_minimum_required(VERSION 2.8)

project(segment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3 -Wno-long-long -fno-omit-frame-pointer") ##-g

FIND_PACKAGE( OpenCV REQUIRED )
link_directories ( ${OpenCV_LIB_DIR} )
MESSAGE(STATUS "OpenCV_LIB_DIR: ${OpenCV_LIB_DIR}")

include_directories ( ${OpenCV_INCLUDE_DIRS} )
MESSAGE(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")

include_directories(${CMAKE_SOURCE_DIR}/src/)
add_subdirectory(src)

add_executable(segment main.cpp ${DEMO_MOC_SRCS})
target_link_libraries(segment ${OpenCV_LIBS} segmentalg)
