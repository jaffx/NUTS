
#include <iostream>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <nuts_datagram.h>

#define SRV_IP "127.0.0.1"
#define SRV_PORT 1120
using std::cout, std::endl;

int main() {
    int srv_sock = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in srv_addr{0};

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SRV_PORT);
    srv_addr.sin_addr.s_addr = inet_addr(SRV_IP);

    if (bind(srv_sock, (struct sockaddr *) (&srv_addr), sizeof(srv_addr)) == 0) {
        cout << "绑定成功" << endl;
    } else {
        cout << "绑定失败" << endl;
    }


    sockaddr_in clnt_addr = {};
    socklen_t sklen = sizeof(clnt_addr);
    size_t dl;
    char buffer[2048] = {};

    memset(buffer, 0, sizeof(buffer));
    dl = recvfrom(srv_sock, buffer, sizeof(buffer), 0, (sockaddr *) &clnt_addr, &sklen);
    cout << "接收字节数：" << dl << endl;
    cout << "IP:" << inet_ntoa(clnt_addr.sin_addr) << ":" << ntohs(clnt_addr.sin_port) << endl;
    nuts_datagram nd;
    nd.parse_from_buffer(buffer, sizeof(buffer));
    nd.show_info();

}