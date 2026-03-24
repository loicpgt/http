# Simple HTTP Server

## Preface
I am learning to program in C and C++ through this project.
I am discovering a whole new world of programming. Coming from a C# background, I want to understand how computers fundamentally work and how their different parts interact together.

I chose this type of project because I find it easy to iterate through the different levels of difficulty of the language and its ecosystem.
My current goals are:

* To learn the most commonly used patterns in C
* To understand how to work with memory
* To learn how to use CMake
* To understand the differences between C and C++
* To understand threading on Linux
* To understand sockets on Linux


## How to run the project

### Using CMake
```shell
mkdir bin
cd bin
cmake ..
cmake --build .
```

## Project architecture
### lib/http_core
Contains the implementation for the core systems of the software.

### lib/http_sdk
Contains the SDK to develop an HTTP Server using the `http_core` systems.