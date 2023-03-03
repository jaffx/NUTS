//
// Created by lyn on 2023/2/22.
//

#include "basic.h"

udp_socket::udp_socket() {
    this->__socket = socket(AF_INET, SOCK_DGRAM, 0);
    this->addr = {};
    this->addr.sin_family = AF_INET;
    this->sock_len = sizeof(addr);
    this->__enable = this->__socket != -1;
}

udp_socket::udp_socket(string ip, uint16_t port) {
    this->__socket = socket(AF_INET, SOCK_DGRAM, 0);
    this->sock_len = sizeof(addr);
    this->addr = {};
    this->addr.sin_addr.s_addr = inet_addr(ip.data());
    this->addr.sin_port = htons(port);
    this->addr.sin_family = AF_INET;
    this->__enable = this->__socket != -1;
    this->sock_len = sizeof(sockaddr);
}

int udp_socket::listen() {
    return ::listen(this->__socket, 10);
}

udp_socket::~udp_socket() {
    close(this->__socket);
}

int udp_socket::recvfrom(void *buffer, size_t buf_size) {
    int recv_len = ::recvfrom(this->__socket, buffer, buf_size, 0, (sockaddr *) &clnt_addr, &this->sock_len);
    return recv_len;
}

int udp_socket::recvfrom(void *buffer, size_t buf_size, sockaddr_in &_clnt_addr) {
    int recv_len = ::recvfrom(this->__socket, buffer, buf_size, 0, (sockaddr *) &_clnt_addr, &this->sock_len);
    return recv_len;
}

int udp_socket::sendto(void *buffer, size_t buf_size) {
    int send_len = ::sendto(this->__socket, buffer, buf_size, 0, (sockaddr *) &clnt_addr, sock_len);
    return send_len;
}

int udp_socket::sendto(void *buffer, size_t buf_size, sockaddr_in &_clnt_addr) {
    int send_len = ::sendto(this->__socket, buffer, buf_size, 0, (sockaddr *) &_clnt_addr, sock_len);
    return send_len;
}

void udp_socket::set_timeout(int secs, int usecs) const {
    timeval tv{secs, usecs};
    setsockopt(this->__socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
}

int udp_socket::bind() {
    int ret = ::bind(this->__socket, (sockaddr *) &addr, this->sock_len);
    if (ret == -1)
        this->__enable = false;
    return ret;
}

int udp_socket::bind(string ip, uint16_t port) {
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = inet_addr(ip.data());
    this->addr.sin_family = AF_INET;
    return this->bind();
}

bool udp_socket::enable() {
    return __enable;
}

string get_local_ip_using_create_socket() {
    static string local_ip = "";
    if (not local_ip.empty())
        return local_ip;
    int status = 0;
    int af = AF_INET;
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in remote_addr;
    struct sockaddr_in local_addr;
    socklen_t len = 0;

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(53);
    remote_addr.sin_addr.s_addr = inet_addr("1.1.1.1");

    len = sizeof(struct sockaddr_in);
    status = connect(sock_fd, (struct sockaddr *) &remote_addr, len);
    if (status != 0) {
        printf("connect err \n");
    }

    len = sizeof(struct sockaddr_in);
    getsockname(sock_fd, (struct sockaddr *) &local_addr, &len);

    local_ip = inet_ntoa(local_addr.sin_addr);
    return local_ip;
}