//
// Created by lyn on 2023/2/22.
//

#include "basic.h"

udp_socket::udp_socket() {
    this->__socket = socket(AF_INET, SOCK_DGRAM, 0);
    this->addr = {};
    this->sock_len = sizeof(addr);
}

udp_socket::udp_socket(string ip, uint16_t port) {
    this->__socket = socket(AF_INET, SOCK_DGRAM, 0);
    this->sock_len = sizeof(addr);
    this->addr = {};
    this->addr.sin_addr.s_addr = inet_addr(ip.data());
    this->addr.sin_port = htons(port);
    this->addr.sin_family = AF_INET;
}

udp_socket::~udp_socket() {
    close(this->__socket);
}

int udp_socket::recvfrom(void *buffer, size_t buf_size) {
    int recv_len = ::recvfrom(this->__socket, buffer, buf_size, 0, (sockaddr *) &clnt_addr, &this->sock_len);
    return recv_len;
}

int udp_socket::sendto(void *buffer, size_t buf_size) {
    int send_len = ::sendto(this->__socket, buffer, buf_size, 0, (sockaddr *) &addr, sock_len);
    return send_len;
}

void udp_socket::set_timeout(int secs, int usecs) const {
    timeval tv{secs, usecs};
    setsockopt(this->__socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
}

int udp_socket::bind() {
    return ::bind(this->__socket, (sockaddr *) &addr, this->sock_len);

}

int udp_socket::bind(string ip, uint16_t port) {
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = inet_addr(ip.data());
    return this->bind();
}