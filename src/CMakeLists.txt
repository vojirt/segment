cmake_minimum_required(VERSION 2.8)

set(SEGMENT_SRC segment.cpp)

add_library(segmentalg STATIC ${SEGMENT_SRC})
target_link_libraries(segmentalg ${OpenCV_LIBS})