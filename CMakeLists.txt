project(nuts)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)

set(LIB_LIST jsoncpp nuts)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# 引入jsoncpp
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

include_directories(nuts/src)
link_directories(nuts/lib)


add_executable(test test.cpp )
add_executable(server server.cpp )
add_executable(server2 server2.cpp )
add_executable(client client.cpp )
add_executable(center center.cpp )
target_link_libraries(test ${LIB_LIST})
target_link_libraries(server2 ${LIB_LIST})
target_link_libraries(server ${LIB_LIST})
target_link_libraries(client ${LIB_LIST})
target_link_libraries(center ${LIB_LIST})
