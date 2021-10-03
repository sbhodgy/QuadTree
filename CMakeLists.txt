cmake_minimum_required(VERSION 3.0.0)
project(QuadTree VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR})

add_executable(QuadTree main.cpp QuadTree.cpp Particle.cpp)

target_link_libraries(QuadTree sfml-graphics sfml-window sfml-system)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
