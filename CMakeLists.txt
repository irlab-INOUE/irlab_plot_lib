cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(irplotlib)

find_package (OpenCV REQUIRED)

add_executable (main main.cpp irplotlib.cpp)
target_link_libraries(main ${OpenCV_LIBRARIES})

add_subdirectory(samples)
