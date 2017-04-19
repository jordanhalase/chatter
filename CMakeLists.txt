cmake_minimum_required (VERSION 3.7)
project (Chatter VERSION 0.1 LANGUAGES CXX)

# Sets all .cpp files in /src for building
file(GLOB SOURCES src/*.cpp)

add_executable(chatter ${SOURCES})

