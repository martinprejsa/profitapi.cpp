cmake_minimum_required(VERSION 3.19)
project(libprofitapi)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(libprofitapi src/profitapi.cpp)

target_link_libraries(libprofitapi libcurl)
target_link_libraries(libprofitapi libfmt)
