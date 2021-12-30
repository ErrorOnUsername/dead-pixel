cmake_minimum_required( VERSION 3.19 )
project( game )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED 1 )

set( GAME_SOURCES
	GameApp.cpp
	GameLayer.cpp
)

add_executable( game ${GAME_SOURCES} )
target_link_libraries( game dead_pixel glfw glad )
