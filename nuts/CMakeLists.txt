project(nuts)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.23)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(lib)
set(INSTALL_LIST src/nuts_server.h src/nuts_datagram.h)
install(FILES ${INSTALL_LIST} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(/usr/local/xyq)
link_directories(/usr/local/xyq/jsoncpp/lib)

add_library(nuts_datagram src/nuts_datagram.cpp)
add_library(nuts_server src/nuts_server.cpp)

target_link_libraries(nuts_server nuts_datagram jsoncpp)