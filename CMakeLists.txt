cmake_minimum_required(VERSION 3.0)
SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_CXX_FLAGS "-I /usr/include/ -l crypt ${CMAKE_CXX_FLAGS}  -std=c++20")
SET(PROGRAM_NAME watcher)
project(watcher)

include_directories(
	include/
)
add_executable(
	${PROGRAM_NAME}

	include/watcherlib.h
	include/watcher.h
	include/server.h
	include/client.h

	watcherlib.cpp
	watcher.cpp
	server.cpp
	client.cpp
	main.cpp
)
