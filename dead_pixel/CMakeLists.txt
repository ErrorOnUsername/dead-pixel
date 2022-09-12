cmake_minimum_required( VERSION 3.12 )
project( dead_pixel )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED 1 )

set( PLATFORM_GENERIC_SOURCES
	platform/generic/generic_input.cc
	platform/generic/generic_time.cc
	platform/generic/generic_window.cc
)

set( GL_SOURCES
	gfx/api/opengl/gl_graphics_context.cc
	gfx/api/opengl/gl_renderer.cc
	gfx/api/opengl/gl_buffer.cc
	gfx/api/opengl/gl_framebuffer.cc
	gfx/api/opengl/gl_shader.cc
	gfx/api/opengl/gl_texture.cc
	gfx/api/opengl/gl_vertex_array.cc
	gfx/api/opengl/imgui_build.cc
	gfx/api/opengl/imgui_static.cc
)

set( CORE_SOURCES
	core/application.cc
	core/imgui_layer.cc
	core/json_parser.cc
	core/log.cc
	core/scene.cc
)

set( ENTITY_SYSTEM_SOURCES
	entity_system/entity_context.cc
	entity_system/components/mesh_component.cc
)

set( GFX_SOURCES
	${GL_SOURCES}
	gfx/editor_camera.cc
	gfx/gltf/gltf_parser.cc
)

set( PLATFORM_SOURCES
	${PLATFORM_GENERIC_SOURCES}
)

set( ENGINE_SOURCES
	${CORE_SOURCES}
	${ENTITY_SYSTEM_SOURCES}
	${PLATFORM_SOURCES}
	${GFX_SOURCES}
)

add_library( ${PROJECT_NAME} ${ENGINE_SOURCES} )
target_link_libraries( ${PROJECT_NAME} glfw glad stb_img )

add_custom_command( TARGET ${PROJECT_NAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink
	${CMAKE_CURRENT_SOURCE_DIR}/default_assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/default_assets
)
