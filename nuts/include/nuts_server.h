//
// Created by lyn on 2023/2/18.
//

#ifndef NUTS_NUTS_SERVER_H
#define NUTS_NUTS_SERVER_H

#include<iostream>
#include<string>
#include<cstring>
#include<thread>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include "nuts_datagram.h"
#include "json/json.h"
#include <queue>
#include <unordered_map>
#include "basic.h"
#include <mutex>
#include "order_tree.h"
#include "nuts_server_register.h"

#define NUTS_DEFAULT_SERVER_PORT 1998

using std::string;
using std::cout, std::endl;
using std::queue, std::unordered_map;

class nuts_function_maps {
private:
    unordered_map<string, nuts_function> fmaps;
public:
    friend class nuts_server;

    void add_function(string, nuts_function);

    bool remove_function(string);

    nuts_function find_function(string) const;

    bool exist_function(string) const noexcept;
};

struct nuts_function_info {
    /*
     * 本地服务树注册信息
     * type：
     */
    nuts_function func_ptr;
    string type;
    string comment;
};


std::ostream &operator<<(std::ostream &io, nuts_function_info &v) {
    cout << "[" << v.type << ']' << v.comment;
    return io;
}

class nuts_function_tree {
private:
    order_tree<string, nuts_function_info> tree;
public:
    friend class nuts_server;


    int add_path(string, string comment = "");
    int add_api(string, nuts_function, string comment = "");

    int add_node(string, nuts_function, string type, string comment = "");

    int delete_path(string);

    nuts_function find_function(string);

    void show_tree() {
        cout<<"*"<< this->tree.root.data.first<<" : "<< this->tree.root.data.second<<endl;
        this->tree.show_tree();
    };

    vector<pair<string, string>> get_register_infos() const;
    vector<string> get_api_list()const ;

};


class nuts_server {
    /*
     *
     * */
    udp_socket __socket;
    string server_name;
    string ip;
    uint16_t port;
    queue<nuts_request *> req_que, req_que_fast;
    queue<nuts_response *> rsp_que;
    std::mutex req_r_lock, rsp_w_lock;
    string psm_name, psm_comment; // 服务名称及描述
    string center_ip;
    uint16_t center_port;
public:
    nuts_function_tree tree;


    nuts_server(string name, string commnet = "");

    inline void update_comment(string) noexcept;

    void _run_();

    void _recv_();

    void _do_nuts_();

    void _send_();

    void set_server_name(string name) noexcept;

    string get_server_name() const;




    void set_center(string ip, uint16_t port = 1971) noexcept;

    int report_server();

    int report_psm();

    ~nuts_server();
};


#endif //NUTS_NUTS_SERVER_H
