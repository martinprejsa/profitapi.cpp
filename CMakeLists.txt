cmake_minimum_required(VERSION 3.4)
project(profitapi)
set(CMAKE_CXX_STANDARD 14)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wpedantic)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(profitapi SHARED src/profitapi.cpp)

if(UNIX)
    install(TARGETS profitapi DESTINATION lib)
    install(DIRECTORY include/ DESTINATION include/profitapi)
endif()

target_link_libraries(profitapi PUBLIC curl)
target_link_libraries(profitapi PUBLIC ssl)
target_link_libraries(profitapi PUBLIC crypto)