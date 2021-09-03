cmake_minimum_required( VERSION 3.19 )
project( dp_editor )

set( EDITOR_SOURCES
	main.cpp
)

add_executable( editor ${EDITOR_SOURCES} )
target_link_libraries( editor dead_pixel glfw glad )
