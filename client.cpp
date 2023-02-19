#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "nuts_datagram.h"
#define PORT 1120
#define IP "127.0.0.1"
using namespace std;

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP);
    socklen_t ssl;
    char buffer[1000] = "11111111";

    nuts_datagram nd ;
    nd.flags = 1;
    nd.data = "HELLO !!";
    nd.func_name = "hello";
    nd.env_number = 20;
    nd.id = 123;
    nd.show_info();
    int length = nd.to_buffer(buffer, sizeof(buffer));
    size_t sl = sendto(sockfd, buffer, length, 0, (sockaddr *) &addr, sizeof(addr));
    cout << "发送字节数: " << sl << endl;
    close(sockfd);
}