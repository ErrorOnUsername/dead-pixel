cmake_minimum_required( VERSION 3.19 )
project( dp_sandbox )

add_subdirectory( ../DeadPixel )

add_executable( dp_sandbox main.cpp )
target_link_libraries( dp_sandbox dead_pixel )