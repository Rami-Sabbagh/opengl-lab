cmake_minimum_required (VERSION 3.28)
project(GLAD LANGUAGES C)

add_library(GLAD STATIC src/glad.c)
target_include_directories(GLAD PUBLIC ${PROJECT_SOURCE_DIR}/include)