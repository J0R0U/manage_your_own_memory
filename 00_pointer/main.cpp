// SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
// SPDX-License-Identifier: MIT

#include <iostream>

// Mark a variable as unused (to suppress compiler warnings)
#define UNUSED(variable) ((void) variable)

void showcase_pointer_syntax(int &_x)
{
    // Declaring a pointer use an asterisks after the type you want to point to.
    int *a, *b;

    // To read/write the address use the pointer like an integer. To get the
    // address of a variable use the ampersand operator.
    a = &_x;
    b = a;

    // Typically a pointer is modified using plus and minus operators.
    ++b;

    // To load/store data the pointer is dereferenced using the asterisk
    // operator.
    *b      = 10;
    int var = *b;

    // Suppress unused warning
    UNUSED(var);
}

int main()
{
    // Array x with two elements
    int x[2] = {0, 0};

    // Call function with pointer operations
    showcase_pointer_syntax(x[0]);

    // Output x
    std::cout << "int x[2] = {" << x[0] << ", " << x[1] << "};\n";

    return 0;
}