cmake_minimum_required(VERSION 3.16.3)

project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPPFILES src/main.cpp src/game.cpp src/platform.cpp src/projectile.cpp src/block.cpp src/player.cpp src/entity.cpp src/camera.cpp src/collisions.cpp)

set(SFML_LINKS -lsfml-graphics -lsfml-window -lsfml-system)

add_executable(${PROJECT_NAME}_main ${CPPFILES})

target_compile_options(${PROJECT_NAME}_main PRIVATE -Wall -g -fpic)
target_link_libraries(${PROJECT_NAME}_main ${SFML_LINKS})
