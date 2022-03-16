cmake_minimum_required( VERSION 3.19)
project( editor )

set( EDITOR_SOURCES
	editor_layer.cc
	imgui_layer.cc
	main.cc
)

add_executable( editor ${EDITOR_SOURCES} )
target_link_libraries( editor dead_pixel imgui )
