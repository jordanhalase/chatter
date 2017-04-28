include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (AddNode testAddNode.cpp)

target_link_libraries(AddNode Chatter)

add_test (Test AddNode)
