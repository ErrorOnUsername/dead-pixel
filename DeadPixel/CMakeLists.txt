cmake_minimum_required( VERSION 3.19 )
project( dead_pixel )

set( CMAKE_CXX_STANDARD 20 )

set( CORE_SOURCES
	Core/Application.cpp
	Core/Layer.cpp
	Core/LayerStack.cpp
	Core/Log.cpp
)

set( PLATFORM_SOURCES
	Platform/Generic/GenericWindow.cpp
)

set( RENDERER_SOURCES )

set( DEAD_PIXEL_SOURCES ${CORE_SOURCES} ${PLATFORM_SOURCES} ${RENDERER_SOURCES} )

add_definitions(-DDP_BUILD)
add_library( dead_pixel ${DEAD_PIXEL_SOURCES} )
target_precompile_headers( dead_pixel PRIVATE dppch.h )
target_link_libraries( dead_pixel glfw glad )
