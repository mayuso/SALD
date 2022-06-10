# Projects Settings
cmake_minimum_required (VERSION 3.16)
project (Sandbox2D)

if (UNIX)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath='$ORIGIN'")
endif()

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME}
	${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../sald/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE sald)

install(TARGETS ${PROJECT_NAME}
	DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}
)

install(DIRECTORY src/Shaders
	DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/../release/sald/${CMAKE_BUILD_TYPE}/lib/"
	DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}
)
