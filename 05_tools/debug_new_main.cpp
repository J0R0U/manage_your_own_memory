// SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
// SPDX-License-Identifier: MIT

#include <iostream>
#include <list>
#include <map>
#include <string>

// Enable bookkeeping by uncommenting the below line.
// #define DEBUG

// Bookkeeping defines
#ifdef DEBUG
// Used to allocate an array of a given type and size. Keeps track of the
// returned pointer.
#    define DEBUG_new_array(_type, _amount) \
        bookkeeper::alloc_array<_type>(__FILE__, __LINE__, _amount)

// Used to deallocate a previous allocated array. Checks if the pointer is
// monitored and removes the corresponding entry.
#    define DEBUG_delete_array(_ptr) \
        bookkeeper::dealloc_array(__FILE__, __LINE__, _ptr)

// Reports memory leaks by iterating over non freed entries.
#    define DEBUG_report_leaks() \
        bookkeeper::report_leaks()
#else
// Used to allocate an array of a given type and size.
#    define DEBUG_new_array(_type, _amount) new _type[_amount]

// Used to deallocate a previous allocated array.
#    define DEBUG_delete_array(_ptr)        delete[] _ptr

// Evaluates to EXIT_SUCCESS. No action performed.
#    define DEBUG_report_leaks()            EXIT_SUCCESS
#endif

// Example for a bookkeeper class.
class bookkeeper {
  private:
    // A struct describing an allocation.
    struct allocation_entry {
        std::string file;
        size_t      line;
        size_t      chars;
    };

    // A struct describing a deallocation error.
    struct deallocation_error {
        std::string file;
        size_t      line;
    };

  private:
    // Information about the currently tracked allocated memory.
    static inline std::map<void *, allocation_entry> s_allocated_memory{};

    // Observed deallocation errors
    static inline std::list<deallocation_error> s_deallocation_error{};

  public:
    /**
     * Allocates an array of type T and size _amount. The pointer is monitored
     * by the bookkeeper and needs to be freed, otherwise a memory leak is
     * reported.
     *
     * @param _file The file the allocation occurred in.
     * @param _line The line the allocation occurred in.
     * @param _amount The size of the array that should be allocated.
     * @tparam T The type of the array that should be allocated.
     * @return The result of new T[_amount].
     */
    template <typename T>
    static T *alloc_array(const std::string &_file, const size_t &_line, const size_t &_amount)
    {
        // Allocate the requested array
        T *alloced_array = new T[_amount];

        // Calculate the number of allocated characters
        const size_t alloced_chars{_amount * sizeof(T)};

        // Keep track of allocated memory
        s_allocated_memory.insert({static_cast<void *>(alloced_array), {_file, _line, alloced_chars}});

        // Return allocated array
        return alloced_array;
    }

    /**
     * Deallocates a given array of type T, removing it from the books.
     *
     * @param _file The file the deallocation occurred in.
     * @param _line The line the deallocation occurred in.
     * @param _array The array that should be deallocated.
     * @tparam T The type of the array that should be deallocated.
     */
    template <typename T>
    static void dealloc_array(const std::string &_file, const size_t &_line, T *_array)
    {
        // Remove entry from books and if it was not present in the book ...
        if (s_allocated_memory.erase(static_cast<void *>(_array)) == 0) {
            // ... report an deallocation error.
            s_deallocation_error.push_back({_file, _line});
        }

        // Free memory occupied by memory
        delete[] _array;
    }

    /**
     * Reports any errors observed while performing allocations.
     *
     * @return EXIT_SUCCESS if no errors where encountered, EXIT_FAILURE
     * otherwise.
     */
    static int report_leaks()
    {
        // Check if there is anything to report
        if (s_allocated_memory.empty() && s_deallocation_error.empty()) {
            return EXIT_SUCCESS;
        }

        // Show memory leaks.
        for (const auto &val : s_allocated_memory) {
            std::cerr << "Leak detected in " << val.second.file << ":" << val.second.line << ". Did not delete " << val.second.chars << " chars.\n";
        }

        // Show unmonitored deallocations.
        for (const auto &val : s_deallocation_error) {
            std::cerr << "Deallocation error detected in " << val.file << ":" << val.line << ".\n";
        }

        return EXIT_FAILURE;
    }
};

// Main function with memory leak
int main(int _argc, char **_argv)
{
    // Allocate array with the size of passed arguments
    std::string *argv_as_strings = DEBUG_new_array(std::string, _argc);

    // Copy all arguments as strings
    for (int i = 0; i < _argc; ++i) {
        argv_as_strings[i] = _argv[i];
    }

    // If the number of passed arguments is even ...
    if (_argc % 2 == 0) {
        // ... deallocate the memory.
        std::cout << "Delete allocated array.\n";
        DEBUG_delete_array(argv_as_strings);
    } else /* If the number of passed arguments is odd */ {
        // ... do not deallocate memory.
        std::cout << "Don't delete allocated array.\n";
    }

    return DEBUG_report_leaks();
}