// SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
// SPDX-License-Identifier: MIT

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void showcase_array_using_pointers(int *_a, const size_t _n)
{
    // Initialize array in three different ways.
    int *iter = _a;
    for (size_t i = 0; i < _n; ++i, ++iter) {
        _a[i]     = -1;
        *(_a + i) = -2;
        *iter     = -3;
    }
}

int main()
{
    // Set array size
    const size_t n = 100;

    // Allocation of _n integers stored contagiously in memory
    int *a = malloc(sizeof(int) * n);

    // Call function with pointer (array) operations
    showcase_array_using_pointers(a, n);

    // Print array
    printf("[%d", a[0]);
    for (size_t i = 1; i < n; ++i) {
        printf(", %d", a[i]);
    }
    printf("]\n");

    // Free allocated array.
    free(a);

    return 0;
}