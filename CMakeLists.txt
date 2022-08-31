cmake_minimum_required( VERSION 3.12 )
project( dead_pixel )

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
set( CMAKE_CXX_STANDARD 20 )

if( CMAKE_BUILD_TYPE MATCHES Debug )
	add_compile_definitions( DP_DEBUG )
endif()

include_directories( third_party/glfw/include )
include_directories( third_party/glad/include )
include_directories( third_party/spdlog/include )
include_directories( third_party/imgui )
include_directories( third_party/glm )
include_directories( third_party/stb_image )
include_directories( dead_pixel )

add_subdirectory( third_party )
add_subdirectory( dead_pixel )

include_directories( editor )
add_subdirectory( editor )

add_custom_target( run
	COMMAND ./editor/editor
	VERBATIM
	DEPENDS editor
)
