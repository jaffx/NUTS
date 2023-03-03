
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
    nuts_server svr("customer");
    svr.set_center("127.0.0.1");
    svr.tree.add_path("customer/info", "客户基本信息接口组");
    svr.tree.add_api("customer/info/get_customer_info", nuts_test_function);
    svr.tree.add_api("customer/info/get_customer_info_by_id", nuts_test_function);
    svr.tree.add_api("customer/info/get_customer_info_by_name", nuts_test_function);
    svr.tree.add_api("customer/info/get_customer_info_by_age", nuts_test_function);
    svr.tree.add_api("customer/info/get_customer_info_by_age", nuts_test_function);
    svr.tree.add_path("customer/info1");
    svr.tree.add_api("customer/info1/get_customer_info", nuts_test_function);
    svr.tree.add_api("customer/info1/get_customer_info_by_id", nuts_test_function);
    svr.tree.add_api("customer/info1/get_customer_info_by_name", nuts_test_function);
    svr.tree.add_api("customer/info1/get_customer_info_by_age", nuts_test_function);
    svr.tree.add_api("customer/info1/get_customer_info_by_age", nuts_test_function);
    svr.tree.add_path("customer/info11");
    svr.tree.add_api("customer/info11/get_customer_info", nuts_test_function);
    svr.tree.add_api("customer/info11/get_customer_info_by_id", nuts_test_function);
    svr.tree.add_api("customer/info11/get_customer_info_by_name", nuts_test_function);
    svr.tree.add_api("customer/info11/get_customer_info_by_age", nuts_test_function);
    svr.tree.add_api("customer/info11/get_customer_info_by_age", nuts_test_function);
    svr.tree.show_tree();

    svr.report_server();
//    int ret = svr.report_server();
//    cout << "发送字节数量" << ret << endl;
//    svr._run_();
}