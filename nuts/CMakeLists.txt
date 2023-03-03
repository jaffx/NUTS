project(nuts)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.2)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(lib)
set(INSTALL_LIST src/nuts_server.h src/nuts_datagram.h src/nuts_client.h src/basic.h src/order_tree.h src/nuts_center.h)
set(SRC_LIST src/basic.cpp src/nuts_client.cpp src/nuts_server.cpp src/nuts_datagram.cpp src/nuts_center.cpp src/order_tree.cpp)

install(FILES ${INSTALL_LIST} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)




########## 构建库 ###############


ADD_LIBRARY(nuts_static STATIC ${SRC_LIST})

# 对hello_static的重名为hello
SET_TARGET_PROPERTIES(nuts_static PROPERTIES  OUTPUT_NAME "nuts")
# cmake 在构建一个新的target 时，会尝试清理掉其他使用这个名字的库，如果没有清理还是会只会构建一个动态库，不会构建出静态库
SET_TARGET_PROPERTIES(nuts_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

ADD_LIBRARY(nuts SHARED ${SRC_LIST})

# 对hello_static的重名为hello
SET_TARGET_PROPERTIES(nuts PROPERTIES  OUTPUT_NAME "nuts")
SET_TARGET_PROPERTIES(nuts PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_link_libraries(nuts jsoncpp)
