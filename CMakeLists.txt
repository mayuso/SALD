cmake_minimum_required(VERSION 3.16)
project(Sald VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



if (UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath='$ORIGIN'")
endif()

add_subdirectory(sald/vendor/glad EXCLUDE_FROM_ALL)
add_subdirectory(sald/vendor/glfw EXCLUDE_FROM_ALL)
add_subdirectory(sald/vendor/glm EXCLUDE_FROM_ALL)
add_subdirectory(sald/vendor/assimp EXCLUDE_FROM_ALL)

add_subdirectory(sald)
add_subdirectory(sandbox)
add_subdirectory(sandbox2D)
add_subdirectory(gui)