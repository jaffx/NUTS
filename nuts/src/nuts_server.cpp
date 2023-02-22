//
// Created by lyn on 2023/2/18.
//

#include "nuts_server.h"

nuts_server::nuts_server() {
    this->ip = "0.0.0.0";
    this->port = NUTS_DEFAULT_SERVER_PORT;
    auto bind_ret = this->__socket.bind(this->ip, this->port);
    if (not this->__socket.enable()) {
        cout << "Socket 初始化失败！！" << endl;
        return;
    }
    cout << bind_ret << endl;
    cout << "服务器启动成功：" << ip << ":" << port << endl;
}


nuts_server::~nuts_server() {

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
        int req_len = this->__socket.recvfrom(buffer, sizeof(buffer), req->addr);
        // 报文解析

        parse_len = req->data.parse_from_buffer(buffer, sizeof(buffer));
        cout << "收到RPC请求: " << endl
             << "\tFrom: " << inet_ntoa(req->addr.sin_addr) << ":" << ntohs(req->addr.sin_port) << endl
             << "\tFunc:-> " << req->data.get_func_name() << endl;
//        req->data.show_info();
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
        if (req->data.get_urge()) {
            this->req_que_fast.push(req);
        } else {
            this->req_que.push(req);
        }

    }
}

void nuts_server::_do_nuts_() {
    nuts_request *req;
    nuts_response *rsp;
    nuts_returns ret;
    while (true) {
        req_r_lock.lock();
        if (this->req_que_fast.size()) {
            // 优先处理快速通道请求
            req = this->req_que_fast.front();
            this->req_que_fast.pop();
        } else if (this->req_que.size()) {
            req = this->req_que.front();
            this->req_que.pop();
        } else {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            req_r_lock.unlock();
            continue;
        }
        req_r_lock.unlock();
        // 创建响应
        rsp = new nuts_response;
        rsp->data.initialize_response(req->data);
        rsp->addr = req->addr;
        // 请求内容处理
        string &fn = req->data.func_name;
        auto &&nuts_fp = this->fmaps.find_function(fn);
        if (nuts_fp) {
            // 找到映射函数
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
        rsp_w_lock.lock();
        this->rsp_que.push(rsp);
        rsp_w_lock.unlock();

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
            len = this->__socket.sendto(buffer, len, rsp->addr);
            delete rsp;
        } else {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    }
}

void nuts_function_maps::add_function(std::string r_name, nuts_function h_name) {
    this->fmaps[r_name] = h_name;
}

bool nuts_function_maps::remove_function(std::string r_name) {
    auto &&it = this->fmaps.find(r_name);
    if (it == this->fmaps.end()) {
        return false;
    } else {
        this->fmaps.erase(it);
        return true;
    }
}

bool nuts_function_maps::exist_function(std::string rname) const noexcept {
    return this->fmaps.find(rname) != this->fmaps.end();
}

nuts_function nuts_function_maps::find_function(string r_name) const {
    if (this->exist_function(r_name))
        return this->fmaps.at(r_name);
    else
        return nullptr;
}