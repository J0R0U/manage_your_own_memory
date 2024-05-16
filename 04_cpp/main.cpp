// SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
// SPDX-License-Identifier: MIT

#include <cstring>
#include <iostream>
#include <memory>

// Shows different (de-)allocation procedures
void showcase_allocation()
{
    std::cout << "showcase_allocation()\n";

    // Allocate using new (primitives objects and arrays)
    int         *a = new int;
    int         *b = new int[10];
    std::string *c = new std::string;

    // Deallocate using delete (primitives objects and arrays)
    delete a;
    delete[] b;
    delete c;
}

// A test class to showcase the object life cycle.
class test {
  public:
    // The object constructor
    test()
    {
        // Test output
        std::cout << "  test: constructor called.\n";
    }

    // The object destructor
    ~test()
    {
        // Test output
        std::cout << "  test: destructor called.\n";
    }
};

// Shows different (de-)allocation procedures
void showcase_object_lifecycle()
{
    std::cout << "showcase_object_lifecycle()\n";

    // Explicit constructor/destructor calls
    test *a = new test;
    delete a;

    // Explicit constructor implicit destructor calls
    test b;
}

// A dynamic array without implementing move operators
struct dyn_array {
  public:
    // The array size
    size_t size;

    // The array data
    int *data;

  public:
    // Constructs an array with a given size.
    dyn_array(const size_t &_size);

    // Copies the contents of another dyn_array object.
    dyn_array(const dyn_array &_other);

    // Deletes the allocated memory.
    ~dyn_array();

  public:
    // Assigns this object to the contents of another dyn_array object.
    dyn_array &operator=(const dyn_array &_other);
};

dyn_array::dyn_array(const size_t &_size)
{
    std::cout << "  Constructor\n";

    // Create array of specified size
    size = _size;
    data = new int[size];
}

dyn_array::dyn_array(const dyn_array &_other)
{
    std::cout << "  Copy-Constructor\n";

    // Create array of same size as other
    size = _other.size;
    data = new int[size];

    // Copy contents of previous array
    std::memcpy(data, _other.data, sizeof(int) * size);
}

dyn_array::~dyn_array()
{
    std::cout << "  Destructor\n";

    // Delete dynamically allocated array
    delete[] data;
}

dyn_array &dyn_array::operator=(const dyn_array &_other)
{
    std::cout << "  Assignment-Operator\n";

    // Delete dynamically allocated array of this object before overwriting
    delete[] data;

    // Create array of same size as other
    size = _other.size;
    data = new int[size];

    // Copy contents of previous array
    std::memcpy(data, _other.data, sizeof(int) * size);

    // Return reference to this
    return *this;
}

void showcase_rule_of_three()
{
    std::cout << "showcase_rule_of_three()\n";

    // Create arrays
    dyn_array a{10};
    dyn_array b{20};

    {
        // Call copy constructor
        dyn_array c{b};

        // Call assignment operator
        a = b;

        // Destroy c
    }

    // Destroy a & b
}

// Helper function that returns a dyn_array
dyn_array generate_dyn_array()
{
    // Create two arrays
    dyn_array a{10}, b{20};

    // Choose one randomly
    if ((rand() / (1. * RAND_MAX) > 0.5)) {
        return a;
    } else {
        return b;
    }
}

void showcase_copy_constructor_problems()
{
    std::cout << "showcase_copy_constructor_problems()\n";

    // Initialize pseudo random function
    srand(time(0));

    // Call generate array. Notice how the copy constructor is called (though)
    // technically not necessary
    dyn_array x = generate_dyn_array();

    std::cout << "  x.size: " << x.size << "\n";
}

// A dynamic array
struct dyn_array_move {
  public:
    // The array size
    size_t size;

    // The array data
    int *data;

  public:
    // Constructs an array with a given size.
    dyn_array_move(const size_t &_size);

    // Copies the contents of another dyn_array object.
    dyn_array_move(const dyn_array_move &_other);

    // Move constructor.
    dyn_array_move(dyn_array_move &&_other);

    // Deletes the allocated memory.
    ~dyn_array_move();

  public:
    // Assigns this object to the contents of another dyn_array object.
    dyn_array_move &operator=(const dyn_array_move &_other);

    // Move-Assigns this object to another dyn_array object.
    dyn_array_move &operator=(dyn_array_move &&_other);
};

dyn_array_move::dyn_array_move(const size_t &_size)
{
    std::cout << "  Constructor\n";

    // Create array of specified size
    size = _size;
    data = new int[size];
}

dyn_array_move::dyn_array_move(const dyn_array_move &_other)
{
    std::cout << "  Copy-Constructor\n";

    // Create array of same size as other
    size = _other.size;
    data = new int[size];

    // Copy contents of previous array
    std::memcpy(data, _other.data, sizeof(int) * size);
}

dyn_array_move::dyn_array_move(dyn_array_move &&_other)
{
    std::cout << "  Move-Constructor\n";

    // Move contents of other
    size = _other.size;
    data = _other.data;

    // Invalidate previous object to prevent double deletion
    _other.size = 0;
    _other.data = nullptr;
}

dyn_array_move::~dyn_array_move()
{
    std::cout << "  Destructor\n";

    // Delete dynamically allocated array
    delete[] data;
}

dyn_array_move &dyn_array_move::operator=(const dyn_array_move &_other)
{
    std::cout << "  Assignment-Operator\n";

    // Delete dynamically allocated array of this object before overwriting
    delete[] data;

    // Create array of same size as other
    size = _other.size;
    data = new int[size];

    // Copy contents of previous array
    std::memcpy(data, _other.data, sizeof(int) * size);

    // Return reference to this
    return *this;
}

dyn_array_move &dyn_array_move::operator=(dyn_array_move &&_other)
{
    std::cout << "  Move-Assignment-Operator\n";

    // Delete dynamically allocated array of this object before overwriting
    delete[] data;

    // Move contents of other
    this->size = _other.size;
    data       = _other.data;

    // Invalidate previous object to prevent double deletion
    _other.size = 0;
    _other.data = nullptr;

    // Return reference to this
    return *this;
}

// Helper function that returns a dyn_array
dyn_array_move generate_dyn_array_move()
{
    // Create two arrays
    dyn_array_move a{10}, b{20};

    // Choose one randomly
    if ((rand() / (1. * RAND_MAX) > 0.5)) {
        return a;
    } else {
        return b;
    }
}

void showcase_rule_of_five()
{
    std::cout << "showcase_rule_of_five()\n";

    // Initialize pseudo random function
    srand(time(0));

    // Call generate array. Notice how the copy constructor is not called but
    // instead the move constructor is used.
    dyn_array_move x = generate_dyn_array_move();

    std::cout << "  x.size: " << x.size << "\n";
}

void showcase_unique_ptr()
{
    std::cout << "showcase_unique_ptr()\n";

    // Only one owner
    std::unique_ptr<int>   a{std::make_unique<int>(42)};
    std::unique_ptr<int[]> b{std::make_unique<int[]>(100)};
    // std::unique_ptr<int> c{a};
    std::unique_ptr<int> d{std::move(a)};

    // a = d;
    a = std::move(d);
}

void showcase_shared_and_weak_ptr()
{
    std::cout << "showcase_shared_and_weak_ptr()\n";

    // Reference counted
    std::shared_ptr<int> a{std::make_shared<int>(42)};
    std::shared_ptr<int> b{a};
    std::shared_ptr<int> c{};

    c = a;

    std::weak_ptr<int>   d{c};
    std::shared_ptr<int> e{d.lock()};
}

void run_complex_computation(const std::unique_ptr<int[]> &, const size_t &)
{
    // Choose one randomly
    if ((rand() / (1. * RAND_MAX) > 0.5)) {
        throw "Error";
    }
}

void showcase_smart_pointers()
{
    std::cout << "showcase_smart_pointers()\n";

    try {
        // Allocate array
        std::unique_ptr<int[]> arr{std::make_unique<int[]>(100)};

        // Perform computation with arr that might throw an exception.
        run_complex_computation(arr, 100);

        // arr is automatically deleted as its bound to the scope of the
        // try-block. Even if an exception is thrown the code does not leak.
    } catch (...) {
        std::cerr << "Error occurred.\n";
    }
}

int main()
{
    showcase_allocation();
    showcase_object_lifecycle();
    showcase_rule_of_three();
    showcase_copy_constructor_problems();
    showcase_rule_of_five();
    showcase_unique_ptr();
    showcase_shared_and_weak_ptr();

    return 0;
}