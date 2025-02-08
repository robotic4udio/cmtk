# Minimum required CMake version
cmake_minimum_required(VERSION 3.19)

# include_directories(include)
include_directories(src)

# Select Compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set optimization level
# set(CMAKE_CXX_FLAGS "-O3")

# Add your source files here
set(SOURCES
    src/Interval.cpp
    src/Note.cpp
    src/Chord.cpp
    src/Scale.cpp
)

# Add your header files here
set(HEADERS
    src/Interval.h
    src/Note.h
    src/Chord.h
    src/Scale.h
)

# Add a library target
add_library(cmtklib STATIC ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(cmtklib PUBLIC include)

# Project name
project(CMTK)

# Add executable target
add_executable(MyProject src/main.cpp)
target_link_libraries(MyProject cmtklib)

# Add executable target
add_executable(main test/main2.cpp)
target_link_libraries(main cmtklib)

