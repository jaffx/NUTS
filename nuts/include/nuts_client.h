//
// Created by lyn on 2023/2/21.
//

#ifndef TRY_NUT_NUTS_CLIENT_H
#define TRY_NUT_NUTS_CLIENT_H

#include <iostream>
#include "nuts_datagram.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <vector>
#include <queue>
#include <unordered_map>
#include<unistd.h>

using std::shared_ptr;
using std::queue, std::vector, std::unordered_map;

class nuts_client {
    int __socket;
    uint16_t port;

public:
    nuts_client();

    queue<shared_ptr<nuts_request> > req_que;
    unordered_map<uint16_t, shared_ptr<nuts_response>> rsp_poll;

    void _send_();

    void _recv_();

    void _run_();

};

nuts_returns nuts_call(string fname, nuts_paramters &p);

shared_ptr<nuts_datagram> send_nuts_call(nuts_datagram &);

#endif //TRY_NUT_NUTS_CLIENT_H
