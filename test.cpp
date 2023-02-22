
#include <iostream>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <nuts_datagram.h>
#include "nuts_datagram.h"
#include "nuts_server.h"
#define SRV_IP "127.0.0.1"
#define SRV_PORT 1120
using std::cout, std::endl;

nuts_returns nuts_test_function(nuts_paramters &p) {
    if (p["test"].isNull()) {
        cout << "No" << endl;
        return "no";
    } else {
        cout << "ok" << endl;
        return "ok";
    }
}

int main() {

}