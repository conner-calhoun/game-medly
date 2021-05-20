cmake_minimum_required(VERSION 3.10)
project(Roame VERSION 0.0.1)

# Note, dependencies must be extracted into the lib folder
set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/SDL2-2.0.14)
set(SDL2_image_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/SDL2_image-2.0.5)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

## Library
set(SRCS
    src/roame/src/game.cpp)

add_library(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME}
PUBLIC
    src/roame/inc
    src/roame/components

    ${SDL2_INCLUDE_DIRS}
    ${SDL2_image_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2_image_LIBRARIES}
)

## Test
set(TEST_SRCS
    src/test/main.cpp)

add_executable(test_${PROJECT_NAME} ${TEST_SRCS})

target_include_directories(test_${PROJECT_NAME}
PUBLIC
    src/roame/inc
    src/roame/components
    src/test/components/
)

target_link_libraries(test_${PROJECT_NAME}
    Roame
)