// SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
// SPDX-License-Identifier: MIT

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Helper to determine max possible array size, i.e. a very large unreasonable
// number
#define MAX_INT_ARRAY_SIZE (SIZE_MAX / sizeof(int))

// Common (de-)allocation functions are given below:
//   void *malloc(size_t _how_much);
//   void *calloc(size_t _element_size, size_t _how_many);
//   void *realloc(void *_previous_location, size_t _new_size);
//   void  free(void *_memory_to_deallocate);

void showcase_allocation()
{
    // Header
    puts("showcase_allocation:");

    // Use malloc to allocate an integer
    int *a = (int *) malloc(sizeof(int));
    printf("  a: %p\n", (void *) a);

    int *b = (int *) malloc(sizeof(int) * 10);
    printf("  b: %p\n", (void *) b);

    int *c = (int *) calloc(sizeof(int), 10);
    printf("  c: %p\n", (void *) c);

    int *d = (int *) realloc(c, sizeof(int) * 5);
    printf("  d: %p\n", (void *) d);

    // Free the memory occupied by the variables. Notice that only the pointer
    // is passed, the runtime has to keep track of the actual memory block size.
    free(a);
    free(b);
    free(d);
}

void showcase_allocation_typical()
{
    // Header
    puts("showcase_allocation_typical:");

    // Allocation code:
    //  - Use sizeof(type) to allocate memory (int is not always 4 Bytes)
    int *a = (int *) malloc(sizeof(int));

    // Always check if the return value is valid.
    if (a == NULL) {
        // Return or perform some other error handling. Caveat: Make sure to
        // free memory that was allocated successfully.
        return;
    }

    // Use the allocated objects:
    //  - Don't use your memory uninitialized
    //  - Don't transfer ownership without noticing (read documentation of the
    //    functions you call)
    //  - Don't loose your pointer; if you dont have a reference to the pointer
    //    you cannot retrieve it.
    printf("  a: %p\n", (void *) a);

    // Deallocation:
    //  - For contained allocation; write this as soon as you write the
    //    allocation code.
    free(a);
}

/**
 * This function allocates memory and transfers ownership to the caller. To free
 * the memory use free().
 *
 * @return NULL if the allocation failed, otherwise pointer to an int array of
 * size 100
 */
int *allocate_array()
{
    // Allocate array of size 100;
    return (int *) malloc(sizeof(int) * 100);
}

// This function shows the usage of a self written source function.
void showcase_own_source_function()
{
    // Header
    puts("showcase_own_source_function:");

    // Allocate array
    int *a = allocate_array();

    // Check if allocation was successful
    if (a == NULL) {
        return; // return if not
    }

    // Do something with the allocated array
    printf("  a: %p\n", (void *) a);

    // Free the allocated memory as described in the description of
    // allocate_array
    free(a);
}

// A node struct with an id
struct node {
    int id;
};

// An edge struct pointing from one element to another
struct edge {
    size_t from;
    size_t to;
};

// A graph struct with nodes and edges
struct graph {
    size_t       nodes_size;
    struct node *nodes;
    size_t       edges_size;
    struct edge *edges;
};

/**
 * This function allocates memory and transfers ownership to the caller. To free
 * the memory use destroy_graph().
 *
 * @param _nodes The number of nodes.
 * @param _edges The number of edges.
 * @return A new graph with edge and node arrays. Both arrays can be null if the
 * allocation failed. In those cases the size will be set to 0.
 */
struct graph create_graph(size_t _nodes, size_t _edges)
{
    // Initialize graph struct
    struct graph ret = {
        .nodes_size = _nodes,
        .nodes      = malloc(sizeof(struct node) * _nodes),
        .edges_size = _edges,
        .edges      = malloc(sizeof(struct edge) * _edges),
    };

    // Check if nodes where allocated successfully
    if (ret.nodes == NULL) {
        ret.nodes_size = 0;
    }

    // Check if edges where allocated successfully
    if (ret.edges == NULL) {
        ret.edges_size = 0;
    }

    // Return result
    return ret;
}

/**
 * This function deallocates memory associated with a graph object obtained by
 * calling create_graph().
 *
 * @param _graph The graph that will be destroyed.
 */
void destroy_graph(struct graph _graph)
{
    free(_graph.nodes);
    free(_graph.edges);
}

// This function show cases the usage of a self written source and drain
// function.
void showcase_own_source_drain_function()
{
    // Header
    puts("showcase_own_source_drain_function:");

    // Allocate array
    struct graph a = create_graph(10, 20);

    // No check required, necessary changes already performed in function

    // Do something with the allocated array
    printf("  nodes: %p\n", (void *) a.nodes);
    printf("  edges: %p\n", (void *) a.edges);

    // Free the allocated memory as described in the description of
    // create_graph, i.e., with the fitting drain function
    destroy_graph(a);
}

// Some global data. Call initialize_global before first use and teardown_global
// when finished.
int *global;

// Initializes global. Allocates dynamic memory, use teardown_global to free it.
void initialize_global()
{
    global  = (int *) malloc(sizeof(int));
    *global = 42;
}

// Destroys the dynamic memory associated with global. Make sure to call
// initialize_global before attempting to call this function.
void teardown_global()
{
    free(global);
}

// This function show cases the usage of a self written source and drain
// function.
void showcase_global_lifecycle()
{
    // Header
    puts("showcase_global_lifecycle:");

    // Initialize global array
    initialize_global();

    // Do something with the global resource
    printf("  global: %p\n", (void *) global);

    // Free resources allocated in global.
    teardown_global();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Walloc-size-larger-than="

// This function showcases how easy it is to create a memory leak.
void showcase_realloc_pitfall()
{
    // Header
    puts("showcase_realloc_pitfall:");

    // Initialize value
    int *a = NULL;
    printf("  a: %p\n", (void *) a);

    // Extend size
    a = realloc(a, sizeof(int));
    printf("  a: %p\n", (void *) a);

    // Extend size (by a lot)
    // If this call to realloc fails, we leaked a since we dont have any
    // reference to the previous value of a that we need to call free.
    a = realloc(a, sizeof(int) * MAX_INT_ARRAY_SIZE);
    printf("  a: %p\n", (void *) a);
}

#pragma GCC diagnostic pop

// Main function
int main()
{
    showcase_allocation();
    showcase_allocation_typical();
    showcase_own_source_function();
    showcase_own_source_drain_function();
    showcase_global_lifecycle();
    showcase_realloc_pitfall();

    return 0;
}