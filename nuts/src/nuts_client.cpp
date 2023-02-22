//
// Created by lyn on 2023/2/21.
//

#include "nuts_client.h"

nuts_returns nuts_call(string fname, nuts_paramters &p) {
    nuts_datagram req;
    req.initialize_request();
    req.set_func_name(fname);
    req.set_parameters(p);
    auto rsp = send_nuts_call(req);
    if (rsp)
        rsp->show_info();
    else
        cout << "NULL" << endl;
    return false;
}

shared_ptr<nuts_datagram> send_nuts_call(nuts_datagram &data) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr = {};
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1998);
    addr.sin_family = AF_INET;
    socklen_t sklen = sizeof(addr);
    timeval tv = {5, 0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    char buffer[65535] = {};
    int req_len = data.to_buffer(buffer, sizeof(buffer));
    int send_len = sendto(sockfd, buffer, req_len, 0, (sockaddr *) &addr, sklen);
    memset(buffer, 0, req_len);
    int rsp_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (sockaddr *) &addr, &sklen);
    if (rsp_len == -1) {
        return nullptr;
    }
    shared_ptr<nuts_datagram> rsp(new nuts_datagram);
    close(sockfd);
    rsp->parse_from_buffer(buffer, rsp_len);
    return rsp;
    //    sendto(sockfd, &addr);
}