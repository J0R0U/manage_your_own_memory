# SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
# SPDX-License-Identifier: MIT

# Add example as executable
add_executable(03_c main.c)

# Add target that executes the executable
add_custom_target(run_03_c 03_c DEPENDS 03_c COMMENT "Run 03_c" VERBATIM)