# SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
# SPDX-License-Identifier: MIT

# Add example as executable
add_executable(00_pointer main.cpp)

# Add target that executes the executable
add_custom_target(run_00_pointer 00_pointer DEPENDS 00_pointer COMMENT "Run 00_pointer" VERBATIM)