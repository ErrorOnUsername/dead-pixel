cmake_minimum_required( VERSION 3.19 )
project( dead_pixel )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED 1 )

set( CORE_SOURCES
	core/application.cc
	core/layer.cc
	core/layer_stack.cc
	core/log.cc
)

set( PLATFORM_SOURCES
	platform/generic/generic_window.cc
)

set( GFX_SOURCES
	gfx/camera.cc
	gfx/ui/ui.cc
	gfx/ui/ui_renderer.cc
)

set( GL_GFX_SOURCES
	gfx/open_gl/gl_buffer.cc
	gfx/open_gl/gl_graphics_context.cc
	gfx/open_gl/gl_renderer.cc
	gfx/open_gl/gl_shader.cc
	gfx/open_gl/gl_vertex_array.cc
)

set( DEAD_PIXEL_SOURCES
	${CORE_SOURCES}
	${PLATFORM_SOURCES}
	${GFX_SOURCES}
	${GL_GFX_SOURCES}
)

add_compile_definitions( DP_BUILD )

add_library( dead_pixel ${DEAD_PIXEL_SOURCES} )
target_link_libraries( dead_pixel glfw glad )
