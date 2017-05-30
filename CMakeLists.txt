cmake_minimum_required (VERSION 3.1)
project (Chatter VERSION 0.1 LANGUAGES CXX)

# enable_testing()

set(CMAKE_CXX_STANDARD 11)

add_executable(ChatterEdit src/editor/editor.cpp)
add_executable(Driver src/driver.cpp)

target_link_libraries(ChatterEdit Chatter)
target_link_libraries(Driver Chatter)

include_directories("src/chatter")


# add our packages
find_package(Curses)

include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(ChatterEdit ${CURSES_LIBRARIES})

set(CURSES_NEED_NCURSES TRUE)

find_package(Boost COMPONENTS serialization)

if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(ChatterEdit ${Boost_LIBRARIES})
  target_link_libraries(Driver ${Boost_LIBRARIES})
endif(Boost_FOUND)

add_subdirectory(src)
#add_subdirectory(test)
