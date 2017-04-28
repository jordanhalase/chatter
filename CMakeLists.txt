cmake_minimum_required (VERSION 3.7)
project (Chatter VERSION 0.1 LANGUAGES CXX)

#enable_testing()

add_executable(chtrDriver src/driver.cpp)
target_link_libraries(chtrDriver Chatter)

add_subdirectory(src)
#add_subdirectory(test)
