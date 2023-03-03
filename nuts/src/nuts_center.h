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
#include  <chrono>


using std::string;
using std::queue;
using std::chrono::system_clock;
struct csrv_node_info {
    // 中台服务树节点信息
    string type;
    string ip;
    time_t t;
};

std::ostream &operator<<(std::ostream &, csrv_node_info &);

class csrv_tree {
public:
    uint16_t env_number;
    order_tree<string, csrv_node_info> tree;

    int insert_node(string, string, string);

    int delete_node(string);

    tree_node<string, csrv_node_info> *find_node(string);

    tree_node<string, csrv_node_info> *find_node(vector<string> path);

    tree_node<string, csrv_node_info> *find_psm(string);

    int insert_psm(string psm, string ip);

    void show_tree();
};


class nuts_center {
    udp_socket __socket;
    string ip;
    uint16_t port;
    csrv_tree srv_tree;
    queue<nuts_request *> recv_q;
    queue<nuts_response *> send_q;
public:
    nuts_center(uint16_t port = NUTS_DEFAULT_CENTER_PORT);

    void __recv__();

    void __run__();

    void __send__();

    void deal_report(nuts_request *);


};


#endif //NUTS_NUTS_CENTER_H
