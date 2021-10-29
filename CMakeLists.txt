cmake_minimum_required( VERSION 3.19 )
project( DeadPixel )

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
set( CMAKE_CXX_STANDARD 20 )

if( CMAKE_BUILD_TYPE MATCHES Debug )
	add_compile_definitions( DP_DEBUG )
endif()

include_directories( ThirdParty/glfw/include )
include_directories( ThirdParty/glad/include )
include_directories( ThirdParty/spdlog/include )
include_directories( ThirdParty/glm )
include_directories( DeadPixel )

add_subdirectory( ThirdParty )
add_subdirectory( DeadPixel )

include_directories( Game )
add_subdirectory( Game )

add_custom_target( run
	COMMAND ./Game/game
	VERBATIM
)
