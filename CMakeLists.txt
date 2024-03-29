cmake_minimum_required(VERSION 3.16)
project(Sald VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath='$ORIGIN'")
endif()

add_subdirectory(sald/vendor/glad EXCLUDE_FROM_ALL)
add_subdirectory(sald/vendor/glfw EXCLUDE_FROM_ALL)
add_subdirectory(sald/vendor/glm EXCLUDE_FROM_ALL)
add_subdirectory(sald/vendor/spdlog EXCLUDE_FROM_ALL)

set(ASSIMP_BUILD_STATIC_LIB ON CACHE BOOL "Build library as static (.a)")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Build supplementary tools")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build tests")
add_subdirectory(sald/vendor/assimp EXCLUDE_FROM_ALL)

add_subdirectory(sald)
add_subdirectory(sald-breakout)
add_subdirectory(sandbox)
add_subdirectory(sandbox2D)
