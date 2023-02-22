//
// Created by lyn on 2023/2/18.
//

#include "nuts_server.h"

nuts_server::nuts_server() {
    this->ip = "127.0.0.1";
    this->port = NUTS_DEFAULT_SERVER_PORT;
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
        cout << "Port: " << port << " 绑定失败" << endl; // 服务端不接受绑定失败
        return;
//        this->port++;
//        addr.sin_port = htons(this->port);
    }
    cout << "服务器启动成功：" << ip << ":" << port << endl;
}


nuts_server::~nuts_server() {
    close(this->__socket);
}

void nuts_server::_run_() {
    std::thread th(&nuts_server::_recv_, this);
    th.detach();
    std::thread th2(&nuts_server::_send_, this);
    th2.detach();
    this->_do_nuts_();

}


void nuts_server::_recv_() {
    char buffer[65535];
    int parse_len;
    nuts_request *req;
    nuts_response *rsp;
    socklen_t addr_len = sizeof(sockaddr);
    while (true) {
        req = new nuts_request;
        memset(buffer, 0, sizeof(buffer));
        // 接受请求
        recvfrom(this->__socket, buffer, sizeof(buffer), 0, (sockaddr *) &req->addr, &addr_len);
        // 报文解析
        parse_len = req->data.parse_from_buffer(buffer, sizeof(buffer));

        req->data.show_info();
        if (parse_len == 0) {
            // 解析失败，丢弃
            delete req;
            continue;
        }
        // 格式校验
        if (not(req->data.get_type() == NUTS_TYPE_REQUEST and req->data.get_format() == NUTS_FORMAT_JSON)) {
            rsp = req;
            rsp->data.format_error();
            this->rsp_que.push(rsp);
            continue;
        }
        // 鉴权

        // 入队
        if (req->data.get_urge())
            this->req_que_fast.push(req);
        else
            this->req_que.push(req);
    }
}

void nuts_server::_do_nuts_() {
    nuts_request *req;
    nuts_response *rsp;
    nuts_returns ret;
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
        // 创建响应
        rsp = new nuts_response;
        rsp->data.initialize_response(req->data);
        rsp->addr = req->addr;
        // 请求内容处理
        string &fn = req->data.func_name;
        auto &&it = this->fmaps.find(fn);
        if (it != fmaps.end()) {
            // 找到映射函数
            nuts_function &nuts_fp = (*it).second;
            auto &&param = req->data.get_parameters();
            try {
                ret = std::move(nuts_fp(param));
                rsp->data.set_return(ret);
            }
            catch (std::exception e) {
                rsp->data.error(e.what());
            }
            catch (string e) {
                rsp->data.error(e);
            }
            catch (...) {
                rsp->data.error();
            }
        } else {
            // 未找到映射函数
            rsp->data.not_found();
        }
        this->rsp_que.push(rsp);
    }
}

void nuts_server::_send_() {
    char buffer[65535];
    nuts_response *rsp;
    size_t len;
    while (true) {
        if (not this->rsp_que.empty()) {
            rsp = rsp_que.front();
            rsp_que.pop();
            len = rsp->data.to_buffer(buffer, sizeof(buffer));
            len = sendto(this->__socket, buffer, len, 0, (sockaddr *) &rsp->addr, sizeof(sockaddr));
            cout << inet_ntoa(rsp->addr.sin_addr) << endl;
            rsp->data.show_info();
            delete rsp;
        } else {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    }
}