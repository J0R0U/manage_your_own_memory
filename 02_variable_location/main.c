// SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
// SPDX-License-Identifier: MIT

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define allocate_integer()       malloc(sizeof(int))
#define deallocate_integer(_int) free(_int)

void run(int *out)
{
    static int call = 0;
    ++call;

    *out = call;
}

int global = 10;
int main()
{
    int  stack = 0;
    int *heap  = allocate_integer();

    run(&stack);
    run(heap);
    run(&global);

    printf("Stack:  %p\n", (void *) &stack);
    printf("Heap:   %p\n", (void *) heap);
    printf("Global: %p\n", (void *) &global);

    deallocate_integer(heap);
}