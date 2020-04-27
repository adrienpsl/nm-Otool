cmake_minimum_required(VERSION 3.15)
project(nm_otool C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")


add_subdirectory(libft)
file(GLOB_RECURSE project_files src/*.c)
add_library(${PROJECT_NAME}_lib ${project_files})
target_include_directories(${PROJECT_NAME}_lib PUBLIC includes)
target_include_directories(${PROJECT_NAME}_lib PUBLIC libft/includes)

add_executable(${PROJECT_NAME} "src/ft_nm.c")
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME} libft_lib)
