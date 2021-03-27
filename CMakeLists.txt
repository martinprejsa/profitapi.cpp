cmake_minimum_required(VERSION 3.19)
project(profitapi)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(profitapi SHARED src/profitapi.cpp )

install(TARGETS profitapi DESTINATION lib)
install(FILES include/profitapi/profitapi.hpp DESTINATION include/profitapi)

target_link_libraries(profitapi curl)
target_link_libraries(profitapi ssl)
target_link_libraries(profitapi crypto)