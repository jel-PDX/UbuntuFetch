# Dependencies

To build this project, you need:

- cmake 3.30.4 or higher
- catch2
- libcurl
- nlohmann json 3.10.5 or higher

# Build Instructions

This project builds on Linux, macOS, and Windows.

```bash
# Create and enter build directory
mkdir build
cd build

# Generate build files
cmake ..

# Generate executables
make
```

Produces two executables: `ubuntufetch`, the CLI application, and `tests`, the unit tests.

## Note for Windows Users

If you are using vcpkg for cmake, you may have to specify your vcpkg cmake path as a flag in your cmake command, such as below (vcpkg should tell you when you install cmake)
`cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scriopts/buildsystems/vcpkg.cmake`

# Documentation

See the [wiki section](https://github.com/jel-PDX/UbuntuFetch/wiki) of the Github repository for architecture (technologies, implementation) and QA documentation (unit, acceptance, cross-platform testing). Both are living documents that I will update throughout the period of completing this assignment.

The source code of the unit tests, in-line comments across all source code, and the commit history of this repository serve as additional documentation.
