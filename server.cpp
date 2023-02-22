
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
//    std::this_thread::sleep_for(std::chrono::seconds(10));
    if (p["test"].isNull()) {
        cout << "No" << endl;
        return "no";
    } else {
        cout << "ok" << endl;
        return "ok";
    }
}

int main() {
    nuts_server svr;
    svr.fmaps.add_function("test", nuts_test_function);
    svr._run_();
}