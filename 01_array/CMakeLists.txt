# SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
# SPDX-License-Identifier: MIT

# Add example as executable
add_executable(01_array main.c)

# Add target that executes the executable
add_custom_target(run_01_array 01_array DEPENDS 01_array COMMENT "Run 01_array" VERBATIM)