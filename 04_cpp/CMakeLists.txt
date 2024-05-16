# SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
# SPDX-License-Identifier: MIT

# Add example as executable
add_executable(04_cpp main.cpp)

# Add target that executes the executable
add_custom_target(run_04_cpp 04_cpp DEPENDS 04_cpp COMMENT "Run 04_cpp" VERBATIM)