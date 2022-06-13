# Projects Settings
cmake_minimum_required (VERSION 3.16)
project (gui)

if (UNIX)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath='$ORIGIN'")
endif()

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME}
	${SOURCES}
	${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.cpp
	${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
	${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
	${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
	${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
	${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
	${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/../sald/src

	${PROJECT_SOURCE_DIR}/vendor/imgui
	${PROJECT_SOURCE_DIR}/vendor/imgui/backends
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

target_link_libraries(${PROJECT_NAME} PRIVATE sald)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

install(TARGETS ${PROJECT_NAME}
	DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/../release/sald/${CMAKE_BUILD_TYPE}/lib/"
	DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}
)
