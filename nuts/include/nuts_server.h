//
// Created by lyn on 2023/2/18.
//

#ifndef NUTS_NUTS_SERVER_H
#define NUTS_NUTS_SERVER_H

#include<iostream>
#include<string>
#include<cstring>
#include<thread>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include "nuts_datagram.h"
#include "jsoncpp/include/json/json.h"
#include <queue>
#include <unordered_map>

#define NUTS_DEFAULT_PORT 1998

using std::string;
using std::cout, std::endl;
using std::queue, std::unordered_map;



struct nuts_request {
    nuts_datagram data;
    sockaddr_in addr;
};

typedef nuts_request nuts_response;

class nuts_server {
public:
    int __socket;
    string ip;
    uint16_t port;
    queue<nuts_request *> req_que, req_que_fast;
    queue<nuts_response *> rsp_que;
    nuts_map fmaps;

    nuts_server();

    void _run_();

    void _recv_();

    void _do_nuts_();

    void _send_();

    ~nuts_server();
};


#endif //NUTS_NUTS_SERVER_H
