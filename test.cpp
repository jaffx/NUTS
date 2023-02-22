#include <iostream>
#include "jsoncpp/include/json/json.h"
#include "nuts_datagram.h"

using namespace std;

int main() {
    int sk = socket(AF_INET, SOCK_DGRAM, 0);
    timeval tv{3, 0};
    setsockopt(sk, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    char buffer[100];
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1120);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t len = sizeof(addr);
    int v = recvfrom(sk, buffer, sizeof(buffer), 0, (sockaddr *) &addr, &len);
    cout << "ok" << endl;
    cout << v << endl;
}
