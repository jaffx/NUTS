#include <iostream>
#include "jsoncpp/include/json/json.h"
#include "nuts_datagram.h"

using namespace std;

int main() {
    nuts_datagram nd;
    nd.flags = 0x1;
    nd.id = 12;
    nd.func_name = "helloworld";
    nd.data = "wulawulawula";
    nd.show_info();
    char buffer[3000];
    int sz = nd.to_buffer(buffer, sizeof(buffer));


    sz = nd.parse_from_buffer(buffer, sizeof(buffer));
    nd.show_info();

}
