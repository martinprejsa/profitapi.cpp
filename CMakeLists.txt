cmake_minimum_required(VERSION 3.19)
project(profitapi)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(profitapi src/profitapi.cpp)

target_link_libraries(profitapi libcurl)
target_link_libraries(profitapi libfmt)
