// SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
// SPDX-License-Identifier: MIT

#include <iostream>
#include <string>

// Main function with memory leak
int main(int _argc, char **_argv)
{
    // Allocate array with the size of passed arguments
    std::string *argv_as_strings = new std::string[_argc];

    // Copy all arguments as strings
    for (int i = 0; i < _argc; ++i) {
        argv_as_strings[i] = _argv[i];
    }

    // If the number of passed arguments is even ...
    if (_argc % 2 == 0) {
        // ... deallocate the memory.
        std::cout << "Delete allocated array.\n";
        delete[] argv_as_strings;
    } else /* If the number of passed arguments is odd */ {
        // ... do not deallocate memory.
        std::cout << "Don't delete allocated array.\n";
    }

    return 0;
}