project(nuts)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.23)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(lib)
set(INSTALL_LIST src/nuts_server.h src/nuts_datagram.h src/nuts_client.h )

install(FILES ${INSTALL_LIST} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(../libs/)
link_directories(../libs/jsoncpp/lib)

add_library(basic src/basic.cpp)
add_library(nuts_datagram SHARED src/nuts_datagram.cpp)
add_library(nuts_server SHARED src/nuts_server.cpp)
add_library(nuts_client SHARED src/nuts_client.cpp)


target_link_libraries(nuts_datagram jsoncpp basic)
target_link_libraries(nuts_server nuts_datagram jsoncpp basic)
target_link_libraries(nuts_client nuts_datagram jsoncpp basic)