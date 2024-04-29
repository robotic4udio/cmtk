# Minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# include_directories(include)
include_directories(libraries/midifile/include)
include_directories(libraries/SimpleJSON)
include_directories(libraries/oscpkt)
include_directories(src)

# Select Compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Set optimization level
# set(CMAKE_CXX_FLAGS "-O3")

# Add your source files here
set(SOURCES
    src/InterfaceGPT.cpp
    src/Interval.cpp
    src/Note.cpp
    src/Chord.cpp
    src/Scale.cpp
    # Midfile library:
    libraries/midifile/src/Binasc.cpp
    libraries/midifile/src/MidiEvent.cpp
    libraries/midifile/src/MidiEventList.cpp
    libraries/midifile/src/MidiFile.cpp
    libraries/midifile/src/MidiMessage.cpp
)

# Add your header files here
set(HEADERS
    src/Interval.h
    src/Note.h
    src/Chord.h
    src/Scale.h
    src/InterfaceGPT.h
    libraries/SimpleJSON/json.hpp
    # Midfile library:
    libraries/midifile/include/Binasc.h
    libraries/midifile/include/MidiEvent.h
    libraries/midifile/include/MidiEventList.h
    libraries/midifile/include/MidiFile.h
    libraries/midifile/include/MidiMessage.h
    libraries/midifile/include/Options.h    
    # Oscpkt library:
    libraries/oscpkt/oscpkt.hh
)

# Compile the mififile library
# add_subdirectory(libraries/midifile)

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

