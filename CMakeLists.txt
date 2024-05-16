# SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.22.1)

project(manage_your_own_memory
    VERSION 1.0.0
    LANGUAGES C CXX
)

# Warn about everything
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Werror")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Weverything" "-Werror")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options("/W4" "/WX")
endif()

# Check if current project is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Disable extensions, only the standart should be allowed
    set(CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Add examples
add_subdirectory(00_pointer)
add_subdirectory(01_array)
add_subdirectory(02_variable_location)
add_subdirectory(03_c)
add_subdirectory(04_cpp)
add_subdirectory(05_tools)