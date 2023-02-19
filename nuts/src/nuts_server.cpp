//
// Created by lyn on 2023/2/18.
//

#include "nuts_server.h"

nuts_server::nuts_server() {
    this->ip = "127.0.0.1";
    this->port = NUTS_DEFAULT_PORT;
    this->__socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->__socket == -1) {
        cout << "Socket 初始化失败！！" << endl;
        return;
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->port);
    addr.sin_addr.s_addr = inet_addr(this->ip.data());
    while (bind(this->__socket, (sockaddr *) (&addr), sizeof(addr))) {
        cout << "Port: " << port << " 绑定失败" << endl;
        this->port++;
        addr.sin_port = htons(this->port);
    }
    cout << "服务器启动成功：" << ip << ":" << port << endl;
}

nuts_server::~nuts_server() {
    close(this->__socket);
}

void nuts_server::_run_() {
    std::thread th(&nuts_server::_recv_, this);
    th.detach();

}

void nuts_server::_recv_() {
    char buffer[65535];
    nuts_request *req;
    socklen_t addr_len;
    while (true) {
        req = new nuts_request;
        memset(buffer, 0, sizeof(buffer));
        recvfrom(this->__socket, buffer, sizeof(buffer), 0, (sockaddr *) &req->addr, &addr_len);
        req->data.parse_from_buffer(buffer, sizeof(buffer));
        this->req_que.push(req);
    }
}

void nuts_server::_do_nuts_() {
    nuts_request *req;
    while (true) {
        if (this->req_que_fast.size()) {
            // 优先处理快速通道请求
            req = this->req_que_fast.front();
            this->req_que_fast.pop();
        } else if (this->req_que.size()) {
            req = this->req_que.front();
            this->req_que.pop();
        } else {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            continue;
        }
        // 请求内容处理

    }
}