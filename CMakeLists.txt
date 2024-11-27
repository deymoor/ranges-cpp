cmake_minimum_required(VERSION 3.12)

project(
        labwork9
        VERSION 1.0
        DESCRIPTION "C++ Year 2024 labword8"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Werror -Wextra -pedantic-errors -fsanitize=address)
add_link_options(-fsanitize=address)
add_subdirectory(libs)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)