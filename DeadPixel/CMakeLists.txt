cmake_minimum_required( VERSION 3.19 )
project( dead_pixel )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED 1 )

set( CORE_SOURCES
	Core/Application.cpp
	Core/Layer.cpp
	Core/LayerStack.cpp
	Core/Log.cpp
)

set( PLATFORM_SOURCES
	Platform/Generic/GenericWindow.cpp
)

set( GFX_SOURCES
	GFX/Camera.cpp
)

set( GL_GFX_SOURCES
	GFX/OpenGL/GLBuffer.cpp
	GFX/OpenGL/GLGraphicsContext.cpp
	GFX/OpenGL/GLRenderer.cpp
	GFX/OpenGL/GLShader.cpp
	GFX/OpenGL/GLVertexArray.cpp
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
