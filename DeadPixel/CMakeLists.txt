cmake_minimum_required( VERSION 3.19 )
project( dead_pixel )

set( CMAKE_CXX_STANDARD 20 )

set( CORE_SOURCES
	Core/Application.cpp
	Core/Layer.cpp
	Core/Log.cpp
	Core/Window.cpp
)

set( RENDERER_SOURCES
	Renderer/Buffer.cpp
	Renderer/Renderer.cpp
	Renderer/Shader.cpp
	Renderer/VertexArray.cpp
	Renderer/API/GraphicsAPI.cpp
	Renderer/API/OpenGL/GLContext.cpp
	Renderer/API/OpenGL/GLGraphicsAPI.cpp
	Renderer/API/OpenGL/GLBuffer.cpp
	Renderer/API/OpenGL/GLShader.cpp
	Renderer/API/OpenGL/GLVertexArray.cpp
)

set( DEAD_PIXEL_SOURCES ${CORE_SOURCES} ${RENDERER_SOURCES} )

add_library( dead_pixel ${DEAD_PIXEL_SOURCES} )
target_link_libraries( dead_pixel glfw glad )
