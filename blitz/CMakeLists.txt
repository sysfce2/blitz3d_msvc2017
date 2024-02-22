cmake_minimum_required(VERSION 3.16)

project(blitz)

add_executable(blitz
		libs.cpp
		libs.h
		main.cpp
)

target_link_libraries(blitz compiler)

copy_exe_to_release(blitz bin/blitzcc)
