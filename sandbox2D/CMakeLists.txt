# Projects Settings
cmake_minimum_required (VERSION 3.16)
project (Sandbox2D)

if (UNIX)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath='$ORIGIN'")
endif()

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
        src/Sandbox2DApp.cpp
        src/Sandbox2DLayer.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/../sald/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE sald)

install(TARGETS ${PROJECT_NAME}
	DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}
)

install(DIRECTORY src/Shaders
	DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}
)

install(DIRECTORY src/Textures
	DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}
)
