project(try_nut)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)

set(LIB_LIST jsoncpp nuts_datagram nuts_server)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# 引入jsoncpp
include_directories(/usr/local/xyq)
link_directories(/usr/local/xyq/jsoncpp/lib)

include_directories(nuts/src)
link_directories(nuts/lib)


add_executable(test test.cpp )
add_executable(server server.cpp )
add_executable(client client.cpp )
target_link_libraries(test ${LIB_LIST})
target_link_libraries(server ${LIB_LIST})
target_link_libraries(client ${LIB_LIST})
