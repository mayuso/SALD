# Projects Settings
cmake_minimum_required(VERSION 3.16)
project(sald)

file(GLOB SOURCES src/Sald/*.cpp)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/src/Sald/*.h)
add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/vendor/glfw/include
    ${PROJECT_SOURCE_DIR}/vendor/glad/include
    ${PROJECT_SOURCE_DIR}/vendor/glm
    ${PROJECT_SOURCE_DIR}/vendor/stb
    ${PROJECT_SOURCE_DIR}/vendor/assimp/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw glm assimp)

install(FILES ${HEADERS}
    DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/include/Sald
)
install(TARGETS ${PROJECT_NAME}
    DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/lib
)

if(UNIX)
    install(FILES
        DESTINATION ${PROJECT_SOURCE_DIR}/../release/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/lib
    )
endif()
