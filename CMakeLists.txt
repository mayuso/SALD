cmake_minimum_required(VERSION 3.16)

project(Sald VERSION 0.0.1 LANGUAGES CXX)

include(CTest)

if (UNIX)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath='$ORIGIN'")
	# libglew_static fails without -fPIC (Position Independent Code) on linux. Should probably learn more about this and find a better solution.
	add_compile_options (-fPIC)
endif()

add_subdirectory(sald/vendor/glad EXCLUDE_FROM_ALL)
add_subdirectory(sald/vendor/glfw EXCLUDE_FROM_ALL)
add_subdirectory(sald/vendor/glm EXCLUDE_FROM_ALL)
add_subdirectory(sald/vendor/assimp EXCLUDE_FROM_ALL)

add_subdirectory(sald)
add_subdirectory(sandbox)
add_subdirectory(sandbox2D)
add_subdirectory(gui)