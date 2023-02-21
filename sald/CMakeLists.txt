# Projects Settings
cmake_minimum_required(VERSION 3.16)
project(sald)

add_library(sald "")

add_subdirectory(src)

file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/src/*/*.h)
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
