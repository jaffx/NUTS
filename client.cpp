#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <json/json.h>
#include <cstring>
#include "nuts_datagram.h"
#include "nuts_client.h"

#define PORT 1998
#define IP "127.0.0.1"
using namespace std;

int main() {
    Json::Value v;
    auto ret = nuts_call("test", v, "123.60.150.117");
    if(ret)
        cout<<ret.toStyledString()<<endl;
    else
        cout<<"NULL"<<endl;
}