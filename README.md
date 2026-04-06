# Song manager

Project for OOP seminar 2026

## Description

This C++ project demonstrates the use of:

- functions
- templates
- iterators
- Standard Template Library

## Requirements

To build and run this application you need to install the followings:

- [CMake](https://cmake.org/)

On macOS, you can use these commands (assuming that [Homebrew](https://brew.sh/) is already installed):

```bash
brew install cmake
```

## Usage

### Build the project

```bash
cmake -S . -B target
cmake --build target
```

### Run the project

```bash
./target/app
```

### Run tests

```bash
ctest --test-dir target --output-on-failure
```
