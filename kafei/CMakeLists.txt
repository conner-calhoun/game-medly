cmake_minimum_required(VERSION 3.10)
project(Kafei VERSION 0.0.1)

find_package(OpenGL REQUIRED)

# GLFW STUFF
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/deps/glfw)


set(SRCS
    src/kafei/src/renderer.cpp)

set(DEP_SRCS
    deps/glad/src/glad.c)

add_library(${PROJECT_NAME} ${SRCS} ${DEP_SRCS})

target_include_directories(${PROJECT_NAME}
PUBLIC
    src/kafei/inc

    # GLAD Includes
    deps/glad/include
)

target_link_libraries(${PROJECT_NAME}
    glfw
    OpenGL::GL
)


# Test
set(TEST_SRCS
    src/test/main.cpp)

add_executable(test_${PROJECT_NAME} ${TEST_SRCS})

target_include_directories(test_${PROJECT_NAME}
PUBLIC
    src/test
    src/kafei/inc
)

target_link_libraries(test_${PROJECT_NAME}
    Kafei
)