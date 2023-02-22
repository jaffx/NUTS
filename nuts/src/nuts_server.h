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
#include "json/json.h"
#include <queue>
#include <unordered_map>
#include "basic.h"
#include <mutex>

#define NUTS_DEFAULT_SERVER_PORT 1998

using std::string;
using std::cout, std::endl;
using std::queue, std::unordered_map;

class nuts_function_maps {
private:
    unordered_map<string, nuts_function> fmaps;
public:
    void add_function(string, nuts_function);

    bool remove_function(string);

    nuts_function find_function(string) const;

    bool exist_function(string) const noexcept;
};

class nuts_server {
    udp_socket __socket;
    string ip;
    uint16_t port;
    queue<nuts_request *> req_que, req_que_fast;
    queue<nuts_response *> rsp_que;
    std::mutex req_r_lock, rsp_w_lock;

public:
    nuts_function_maps fmaps;

    nuts_server();

    void _run_();

    void _recv_();

    void _do_nuts_();

    void _send_();

    ~nuts_server();
};


#endif //NUTS_NUTS_SERVER_H
