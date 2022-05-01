include_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_SOURCE_DIR})

find_package (OpenCV REQUIRED)

add_executable (draw_function draw_function.cpp ../irplotlib.cpp)
add_executable (scatter_plot scatter_plot.cpp ../irplotlib.cpp)
add_executable (draw_line draw_line.cpp ../irplotlib.cpp)
target_link_libraries(draw_function ${OpenCV_LIBRARIES})
target_link_libraries(scatter_plot ${OpenCV_LIBRARIES})
target_link_libraries(draw_line ${OpenCV_LIBRARIES})
