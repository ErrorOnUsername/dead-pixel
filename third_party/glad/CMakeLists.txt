cmake_minimum_required( VERSION 3.12 )
project( glad )

set( SOURCES
    src/glad.c
)

add_library( glad ${SOURCES} )
