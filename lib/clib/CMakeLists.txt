cmake_minimum_required(VERSION 3.10)
project(cwary C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS -lpthread)
add_executable(tcp-server-test tcp-server.c listbuff.c tcp-server.h listbuff.h tcp-server-test.c)

add_library(web SHARED tcp-server.c tcp-server.h listbuff.c listbuff.h tools.c tools.h)
add_library(c-extra SHARED c-extra.c c-extra.h listbuff.c listbuff.h)

add_executable(c-extra-test c-extra-test.c c-extra.c c-extra.h listbuff.c listbuff.h)

add_library(cwary SHARED
        # list buffer
        listbuff.c listbuff.h
        # tools
        tools.c tools.h
        # web
        tcp-server.c tcp-server.h
        # C's extras functions
        c-extra.c c-extra.h
        )
