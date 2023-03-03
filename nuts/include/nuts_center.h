//
// Created by lyn on 2023/3/1.
//

#ifndef NUTS_NUTS_CENTER_H
#define NUTS_NUTS_CENTER_H
# define NUTS_DEFAULT_CENTER_PORT 1971

#include "basic.h"
#include <string>
#include "order_tree.h"
#include "nuts_datagram.h"
#include <queue>


using std::string;
using std::queue;
struct nuts_center_server_node_info {
    string type;
    string ip;
    string comment;
};

std::iostream &operator<<(std::iostream &, nuts_center_server_node_info &);

typedef order_tree<string, nuts_center_server_node_info> nuts_center_server_tree;


class nuts_center {
    udp_socket __socket;
    string ip;
    uint16_t port;
    nuts_center_server_tree srv_tree;
    queue<nuts_request *> recv_q;
    queue<nuts_response *> send_q;
public:
    nuts_center(uint16_t port = NUTS_DEFAULT_CENTER_PORT);

    void __recv__();

    void __run__();

    void __send__();


};


#endif //NUTS_NUTS_CENTER_H
