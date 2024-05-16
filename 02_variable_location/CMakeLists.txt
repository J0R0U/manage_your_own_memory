# SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
# SPDX-License-Identifier: MIT

# Add example as executable
add_executable(02_variable_location main.c)

# Add target that executes the executable
add_custom_target(run_02_variable_location 02_variable_location DEPENDS 02_variable_location COMMENT "Run 02_variable_location" VERBATIM)