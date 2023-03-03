//
// Created by lyn on 2023/3/1.
//

#include "nuts_center.h"

nuts_center::nuts_center(uint16_t port) : port(port), ip("0.0.0.0") {
    this->__socket.addr.sin_port = htons(this->port);
    this->__socket.addr.sin_addr.s_addr = inet_addr(this->ip.data());
    if (this->__socket.bind() == -1) {
        cout << this->port << "bind失败" << endl;
        return;
    }

    cout << "中台服务启动成功，工作地址：" << this->ip << ":" << this->port << endl;
}

void nuts_center::__recv__() {
    char buffer[NUTS_DATAGRAM_LENGTH_LIMIT];
    sockaddr_in clnt_addr;
    socklen_t socklen;
    nuts_request *req;
    while (true) {
        req = new nuts_request;
        // 接受报文
        int dg_len = this->__socket.recvfrom(buffer, sizeof(buffer), req->addr);
        cout << "接收到报文长度" << dg_len << endl;
        // 报文解包和格式校验
        if (dg_len < 12) // 排除掉长度错误的报文
            continue;
        auto parse_ret = req->data.parse_from_buffer(buffer, dg_len);
        if (parse_ret == 0) // 报文格式错误
            continue;
        // 报文格式正确，进入处理过程
        req->data.show_info();
        switch (req->data.get_type()) {
            case NUTS_TYPE_SERVER_REPORT:
                deal_report(req);
                break;
            default:
                break;
        }

    }
}


void nuts_center::deal_report(nuts_request *req) {
    string register_ip = req->data.get_data1();
    string register_data = req->data.get_data2();
    Json::Reader reader;
    Json::Value v;
    reader.parse(register_data, v);
    vector<string> members = v.getMemberNames();
    for (auto s: members) {
        this->srv_tree.insert_node(s, v[s].asString(), register_ip);
    }
    this->srv_tree.show_tree();
}

std::ostream &operator<<(std::ostream &io, csrv_node_info &v) {
    io << " ["<<v.type<<"] ";
    if (not v.ip.empty())
        cout << v.ip;
    return io;
}

int csrv_tree::insert_node(std::string path, std::string type, std::string ip) {

    auto pths = path_to_vector(path);
    if (pths.size() == 0) {
        cout << "路径为空，无法插入" << endl;
        return -4;
    }
    string psm_name = pths[0];
    string node_name = *(pths.end() - 1);
    if (pths.size() > 1) {
        vector<string> father_path(pths.begin(), pths.end() - 1);
        auto father_node = this->find_node(father_path);
        if (father_node == nullptr) {
            // 父节点不存在
            cout << path << "插入失败，父路径不存在" << endl;
            return -1;
        } else if (father_node->data.second.type == "api") {
            // 父节点存在但是不支持插入
            cout << path << "插入失败，父路径已经注册为api节点" << endl;
            return -1;
        } else if ((*father_node)[node_name]) {
            // 当前节点已存在，执行覆盖操作
            auto node = (*father_node)[node_name];
            node->data.second.ip = ip;
            node->data.second.type = type;
            node->data.second.t = system_clock::to_time_t(system_clock::now());
            return 0;

        } else {
            csrv_node_info info = {};
            info.type = type;
            info.ip = ip;
            info.t = system_clock::to_time_t(system_clock::now());
            this->tree.insert_node(pths, info);
            return 0;
        }
    } else {
        if (type != "psm") {
            cout << "第一层只能注册为psm" << endl;
            return -1;
        } else {
            this->insert_psm(pths[0], ip);
        }
        return 0;
    }

}

int csrv_tree::insert_psm(std::string psm, std::string ip) {
    auto psm_node = this->tree.root[psm];
    if (nullptr == psm_node) {
        // psm节点不存在，执行注册操作
        csrv_node_info info;
        info.type = "psm";
        info.ip = ip;
        info.t = system_clock::to_time_t(system_clock::now());
        this->tree.insert_node(psm, info);
    } else {
        // psm节点存在，执行更新操作
        psm_node->data.second.type = "psm";
        psm_node->data.second.t = system_clock::to_time_t(system_clock::now());
        psm_node->data.second.ip = ip;
    }
    return 0;
}

int csrv_tree::delete_node(std::string path) {
    return this->tree.delete_node(path);
}

tree_node<string, csrv_node_info> *csrv_tree::find_node(string path) {
    return this->tree.find_node(path);
}

tree_node<string, csrv_node_info> *csrv_tree::find_node(vector<std::string> path) {
    return this->tree.find_node(path);
}

tree_node<string, csrv_node_info> *csrv_tree::find_psm(string psm) {
    return this->tree.root[psm];
}

void csrv_tree::show_tree() {
    this->tree.show_tree();
}