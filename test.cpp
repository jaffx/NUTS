#include <iostream>
#include "jsoncpp/include/json/json.h"
#include "nuts_datagram.h"

using namespace std;

int main() {
    uint16_t t;
    t = 1024 & 0x0c00>>2;
    cout << t<< endl;
//    nuts_datagram nd;
//    nd.initialize_request();
//
//    nd.show_info();
//    char buffer[3000];
//    int sz = nd.to_buffer(buffer, sizeof(buffer));
//
////    for(int i =0;i<sz;i++){
////        cout<<int(buffer[i])<<'\t'<<buffer[i]<<endl;
////    }
//    nd.set_format(1);
//    cout << nd.get_format() << endl;
//    sz = nd.parse_from_buffer(buffer, sizeof(buffer));
//    nd.show_info();

}
