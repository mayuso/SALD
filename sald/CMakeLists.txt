# Projects Settings
cmake_minimum_required (VERSION 3.16)
project (sald)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*)
add_library(${PROJECT_NAME} SHARED
	${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/vendor/glfw/include
	${PROJECT_SOURCE_DIR}/vendor/glew/include
	${PROJECT_SOURCE_DIR}/vendor/glm
	${PROJECT_SOURCE_DIR}/vendor/stb
    ${PROJECT_SOURCE_DIR}/vendor/assimp/include
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)


# gl, glfw, glew, glm
if (UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC glfw libglew_static glm assimp)
elseif(WIN32)
	target_link_libraries(${PROJECT_NAME} PUBLIC glfw glew_s glm assimp)
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)


install(FILES ${HEADERS}
	DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/include
)
install(TARGETS ${PROJECT_NAME}
	DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/lib
)

if (UNIX)
	install(FILES
		DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/lib
	)
elseif(WIN32)
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		install(FILES	"${CMAKE_BINARY_DIR}/${PROJECT_NAME}/vendor/glfw/src/${CMAKE_BUILD_TYPE}/glfw3d.dll" 
						"${CMAKE_BINARY_DIR}/${PROJECT_NAME}/vendor/assimp/bin/${CMAKE_BUILD_TYPE}/assimp-vc143-mtd.dll"
			DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/lib
		)
	else()
		install(FILES 	"${CMAKE_BINARY_DIR}/${PROJECT_NAME}/vendor/glfw/src/${CMAKE_BUILD_TYPE}/glfw3.dll"
						"${CMAKE_BINARY_DIR}/${PROJECT_NAME}/vendor/assimp/bin/${CMAKE_BUILD_TYPE}/assimp-vc143-mt.dll"
			DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/lib
		)
	endif()
endif()
