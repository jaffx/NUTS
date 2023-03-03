//
// Created by lyn on 2023/2/18.
//

#include "nuts_server.h"

nuts_server::nuts_server(string name, string comments) : psm_name(name), psm_comment(comments) {
    this->tree.tree.root.data.first = name;
    this->tree.tree.root.data.second.type = "psm";
    this->tree.tree.root.data.second.comment = comments;
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

inline void nuts_server::update_comment(std::string comment) noexcept {
    this->psm_comment = comment;
}

nuts_server::~nuts_server() {

}

void nuts_server::_run_() {
    /*
     *
     */
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
        auto &&nuts_fp = this->tree.find_function(fn);
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

string nuts_server::get_server_name() const {
    return this->server_name;
}

void nuts_server::set_server_name(std::string name) noexcept {
    this->server_name = std::move(name);
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

int nuts_server::report_server() {
    /*
     * 向服务中台报告自身服务树信息，进行服务注册
     */
    // 检查是否设置中台位置
    if (this->center_ip.empty()) {
        cout << "中台信息未设置" << endl;
        return -1;
    }
    // 获取注册列表
    auto &&register_infos = this->tree.get_register_infos();
    Json::Value j_rinfos;
    for (auto &kv: register_infos) {
        j_rinfos[kv.first] = kv.second;
    }
//    cout<<j_rinfos.toStyledString()<<endl;
    // 封装注册报文
    nuts_datagram report;
    report.set_type(NUTS_TYPE_SERVER_REPORT);
    report.set_data1(get_local_ip_using_create_socket());
    sockaddr_in center_addr = {};
    center_addr.sin_port = htons(center_port);
    center_addr.sin_family = AF_INET;
    center_addr.sin_addr.s_addr = inet_addr(center_ip.data());
    char outbuffer[NUTS_DATAGRAM_LENGTH_LIMIT] = {};

    report.set_data2(j_rinfos.toStyledString());
    int buffer_len = report.to_buffer(outbuffer, sizeof(outbuffer));
    int ret = this->__socket.sendto(outbuffer, buffer_len, center_addr);

    return 1;
}

vector<pair<string, string>> nuts_function_tree::get_register_infos() const {
    auto *p = &this->tree.root;
    vector<pair<string, string>> rets;
    queue<decltype(p)> nodes;
    queue<string> values;
    string v;
    nodes.push(p), values.push(p->data.first);
    while (not nodes.empty()) {
        p = nodes.front(), v = values.front();
        rets.push_back(std::make_pair(v, p->data.second.type));
        p = p->child;
        while (p) {
            nodes.push(p), values.push(v + "/" + p->data.first);
            p = p->next_brother;
        }
        nodes.pop(), values.pop();
    }
    return rets;
}

vector<string> nuts_function_tree::get_api_list() const {
    auto *p = &this->tree.root;
    vector<string> rets;
    queue<decltype(p)> nodes;
    queue<string> values;
    string v;
    nodes.push(p), values.push(p->data.first);
    while (not nodes.empty()) {
        p = nodes.front(), v = values.front();
        if (p->data.second.type == "api")
            rets.push_back(v);
        p = p->child;
        while (p) {
            nodes.push(p), values.push(v + "/" + p->data.first);
            p = p->next_brother;
        }
        nodes.pop(), values.pop();
    }
    return rets;
}

void nuts_server::set_center(string ip, uint16_t port) noexcept {
    this->center_ip = ip;
    this->center_port = port;
}


int nuts_function_tree::add_path(std::string path, std::string comment) {
    return this->add_node(path, nullptr, "path", comment);
}

int nuts_function_tree::add_api(std::string path, nuts_function func_ptr, std::string comment) {
    return this->add_node(path, func_ptr, "api", comment);
}

int nuts_function_tree::add_node(std::string path, nuts_function func_ptr, string type, std::string comment) {
    /*
     * @return
     *          0   成功
     *          -1  子节点已经注册
     *          -2  父节点没有注册
     *          -3  父节点注册不是路径，无法生成子节点
     *
     */
    vector<string> pths = path_to_vector(path);
    // 检查pths第一个节点是否psm名称相同
    if (pths.empty()) {
        cout << "节点路径不能为空" << endl;
        return -4;
    }
    if (pths[0] != this->tree.root.data.first) {
        cout << "任何路径开头必须以psm名称开始" << endl;
        return -4;
    }
    vector<string> r_pths{pths.begin() + 1, pths.end()};
    auto v = this->tree.find_node(r_pths);
    if (v)// 该节点被注册
    {
        cout << path << "节点被注册" << endl;
        return -1;
    }
    vector<string> father_path{r_pths.begin(), r_pths.end() - 1};

    v = this->tree.find_node(father_path);
    if (father_path.size() > 1) {
        if (not v) {
            cout << vector_to_path(father_path) << "未注册" << endl;
            return -2;
        } else if (v->data.second.type != "path") {
            cout << vector_to_path(father_path) << "节点是非路径节点，无法生成子节点" << endl;
            return -3;
        }
    }

    auto ret = this->tree.insert_node(r_pths, {func_ptr, type, comment});
    if (ret)
        return 0;
    else {
        cout << path << "节点注册失败，错误类型未知" << endl;
        return -4;
    }
}

int nuts_function_tree::delete_path(std::string path) {
    return this->tree.delete_node(std::move(path));

}

nuts_function nuts_function_tree::find_function(std::string path) {
    auto v = this->tree.find_node(path);
    if (not v)
        return nullptr;
    else
        return v->data.second.func_ptr;
}