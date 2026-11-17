cmake_minimum_required(VERSION 4.2)
project(sald VERSION 0.0.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

add_subdirectory(vendor/glad EXCLUDE_FROM_ALL)
add_subdirectory(vendor/glfw EXCLUDE_FROM_ALL)
add_subdirectory(vendor/glm EXCLUDE_FROM_ALL)
add_subdirectory(vendor/spdlog EXCLUDE_FROM_ALL)

set(ASSIMP_BUILD_STATIC_LIB ON CACHE BOOL "Build library as static (.a)")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Build supplementary tools")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build tests")
add_subdirectory(vendor/assimp EXCLUDE_FROM_ALL)

add_subdirectory(src)

# Only when SALD is built on its own: a project that pulls it in with
# add_subdirectory installs its own files, not SALD's headers and library
if(PROJECT_IS_TOP_LEVEL)
    # `cmake --install` goes to install/ unless a prefix is given (--prefix <dir>)
    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH "Install directory" FORCE)
    endif()

    install(FILES src/sald.h src/saldpch.h
        DESTINATION include
    )

    install(DIRECTORY src/Sald
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
    )

    install(TARGETS ${PROJECT_NAME}
        DESTINATION lib
    )
endif()
