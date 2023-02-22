//
// Created by lyn on 2023/2/22.
//

#ifndef TRY_NUT_BASIC_H
#define TRY_NUT_BASIC_H

#include <iostream>
#include <sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
using std::string;
using std::cout, std::endl;
class udp_socket {
public:
    int __socket;
    bool __enable;
    sockaddr_in addr, clnt_addr;
    socklen_t sock_len;

    udp_socket();
    udp_socket(string ip, uint16_t port);

    ~udp_socket();

    int bind();

    int bind(string ip, uint16_t port );

    int recvfrom(void *, size_t);
    int recvfrom(void *, size_t, sockaddr_in&);

    int sendto(void *, size_t );
    int sendto(void *, size_t , sockaddr_in&);

    void set_timeout(int  secs, int  usecs) const ;

    bool enable();
};

#endif //TRY_NUT_BASIC_H
