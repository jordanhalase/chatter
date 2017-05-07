cmake_minimum_required (VERSION 3.7)
project (Chatter VERSION 0.1 LANGUAGES CXX)

#enable_testing()

add_executable(chtrDriver src/driver.cpp)
target_link_libraries(chtrDriver Chatter)

find_package(Boost COMPONENTS serialization)

if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(chtrDriver ${Boost_LIBRARIES})
endif(Boost_FOUND)

add_subdirectory(src)
#add_subdirectory(test)
