cmake_minimum_required( VERSION 3.19 )
project( DeadPixel )

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
set( CMAKE_CXX_STANDARD 20 )

if( CMAKE_BUILD_TYPE MATCHES Debug )
	add_compile_definitions( DP_DEBUG )
endif()

include_directories( libs/glfw/include )
include_directories( libs/glad/include )
include_directories( libs/spdlog/include )
include_directories( libs/glm )
include_directories( DeadPixel )

add_subdirectory( libs )
add_subdirectory( DeadPixel )
add_subdirectory( Editor )

add_custom_target( run
	COMMAND ./Editor/editor
	VERBATIM
)
