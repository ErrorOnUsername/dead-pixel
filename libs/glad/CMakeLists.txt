cmake_minimum_required( VERSION 3.19 )
project( glad )

set( SOURCES
    src/glad.c
)

add_library( glad ${SOURCES} )