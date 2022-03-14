cmake_minimum_required( VERSION 3.19 )
project( dp_editor )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED 1 )

set( GAME_SOURCES
	editor_app.cc
	editor_layer.cc
)

add_executable( editor ${GAME_SOURCES} )
target_link_libraries( editor dead_pixel glfw glad )
