cmake_minimum_required( VERSION 3.19 )
project( dead_pixel )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED 1 )

set( PLATFORM_GENERIC_SOURCES
	platform/generic/generic_window.cc
	platform/generic/generic_time.cc
)

set( GL_SOURCES
	gfx/api/opengl/gl_graphics_context.cc
)

set( CORE_SOURCES
	core/application.cc
)

set( GFX_SOURCES
	${GL_SOURCES}
)

set( PLATFORM_SOURCES
	${PLATFORM_GENERIC_SOURCES}
)

set( ENGINE_SOURCES
	${CORE_SOURCES}
	${PLATFORM_SOURCES}
	${GFX_SOURCES}
)

add_library( dead_pixel ${ENGINE_SOURCES} )
target_link_libraries( dead_pixel glfw glad )
