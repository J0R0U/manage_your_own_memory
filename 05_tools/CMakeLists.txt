# SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
# SPDX-License-Identifier: MIT

# Add example as executable (unmodified example)
add_executable(05_tools main.cpp)

# Add example as executable (automatic memory leak detection)
add_executable(05_tools_asan main.cpp)
target_link_libraries(05_tools_asan PRIVATE asan)
target_compile_options(05_tools_asan PRIVATE "-fsanitize=address")

# Add example as executable (manual memory leak detection)
add_executable(05_tools_debug_new debug_new_main.cpp)

# Enable memory leak
set(LEAK ON)

# Set parameters accoringly
if(LEAK)
    set(PARAMETERS "")
else()
    set(PARAMETERS "a")
endif()

# Add custom target to execute custom target
add_custom_target(run_05_tools 05_tools ${PARAMETERS} DEPENDS 05_tools COMMENT "Run 05_tools" VERBATIM)

# Find valgrind
find_program(VALGRIND_EXECUTABLE "valgrind")

# If valgrind was found, add valgrind target
if(VALGRIND_EXECUTABLE)
    add_custom_target(run_05_tools_valgrind
        "${VALGRIND_EXECUTABLE}"
        "--leak-check=full"
        "--show-leak-kinds=all"
        "--track-origins=yes"
        "--verbose"
        "--log-file=${CMAKE_CURRENT_BINARY_DIR}/valgrind.txt"
        "$<TARGET_FILE:05_tools>"
        ${PARAMETERS}
        DEPENDS 05_tools
        BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/valgrind.txt"
    )
else()
    message(WARNING "Valgrind was not found. Skipping.")
endif()

add_custom_target(run_05_tools_asan 05_tools_asan DEPENDS 05_tools_asan COMMENT "Run 05_tools_asan" VERBATIM)
add_custom_target(run_05_tools_debug_new 05_tools_debug_new DEPENDS 05_tools_debug_new COMMENT "Run 05_tools_debug_new" VERBATIM)