<!--
SPDX-FileCopyrightText: 2024 J0R0U <https://github.com/J0R0U>
SPDX-License-Identifier: MIT
-->

![Project Logo: Introducing "Manage Your Own Memory" by J0R0U](./images/logo.svg)

## Scope

This projects gives a small introduction into memory management in C and C++.
The general ideas also apply to other self-managed languages. The examples are
part of a presentation where they are used to showcase basic behavior and ideas.

The project currently includes

1. a small recap of pointers,
2. an overview about memory management in C,
3. an overview about memory management in C++ and
4. an introduction to tools that can be used to detect leaks.

## Usage

The project uses cmake[^1] to setup the build process. The different programs are
added as executables, so the following steps can be used to build all
executables:

```bash
# Create build folder
mkdir .build

# Step into newly created folder
cd .build

# Configure cmake
cmake ..

# Build using make
make
```

The commands are executed within the project folder.

To run the programs the executables can be found in their respective subfolder
in `.build`. It is also possible to run the commands using make. Use the custom
targets `run_XX_YYY` to execute the example `XX_YYY`. Below is an example:

```bash
 make run_00_pointer
```

## License

This project uses reuse[^2] to provide license information for the supplied
files. Currently everything is licensed under the terms and conditions of the
MIT license. However, the logo is also available under the terms and conditions
of the CC-BY-4.0 license. For more information see the licenses text supplied in
`LICENSES` folder.  

[^1]: https://cmake.org/
[^2]: https://reuse.software/