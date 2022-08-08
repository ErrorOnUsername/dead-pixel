cmake_minimum_required( VERSION 3.12 )
project( editor )

set( EDITOR_SOURCES
	editor_layer.cc
	main.cc
	panels.cc
	test_scene.cc
)

add_executable( ${PROJECT_NAME} ${EDITOR_SOURCES} )
target_link_libraries( ${PROJECT_NAME} dead_pixel )

add_custom_command( TARGET ${PROJECT_NAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink
	${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
