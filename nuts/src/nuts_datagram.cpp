//
// Created by lyn on 2023/2/18.
//


#include "nuts_datagram.h"

uint16_t nuts_datagram::generate_nuts_id() {
    static uint16_t NUTS_ID = 0;
    if (NUTS_ID == 0xffff)
        NUTS_ID = 0;
    NUTS_ID++;
    return NUTS_ID;
}

nuts_datagram::nuts_datagram() {
    this->id = 0;
    this->unset = 0;
    this->unset2 = 0;
    this->data_length = 0;
    this->func_name_length = 0;
    this->flags = 0;
    this->env_number = 0;
}

int nuts_datagram::parse_from_buffer(char *buffer, size_t buf_size) {
    // 成功返回长度，失败返回0
    if (buf_size < 12) {
        return 0;
    }
    char *ptr = (char *) buffer;
//    flags
    this->flags = ntohs(*(uint16_t *) ptr);
    ptr += 2;
//    报文id
    this->id = ntohs(*(uint16_t *) ptr);
    ptr += 2;
//    待定1字节
    ptr++;
//    函数名称长度
    this->func_name_length = *(uint8_t *) ptr;
    ptr++;
//    数据长度
    this->data_length = ntohs(*(uint16_t *) ptr);
    ptr += 2;
    // 判断长度是否正确
    if (buf_size < 12 + this->func_name_length + this->data_length)
        return 0;
//    环境编号
    this->env_number = ntohs(*(uint16_t *) ptr);
    ptr += 2;
//    待定2字节
    ptr += 2;
//    函数名字段
    char *buf = new char[(this->func_name_length + this->data_length) + 1]{}; // 创建一个临时区域用来暂存数据
    strncpy(buf, ptr, this->func_name_length);
    this->func_name = buf;
    ptr += this->func_name_length;
//    数据字段
    strncpy(buf + this->func_name_length, ptr, this->data_length);
    this->data = buf + this->func_name_length;
    ptr += this->data_length;
    delete[] buf;
    return ptr - (char *) buffer;
}

int nuts_datagram::to_buffer(char *buffer, size_t buf_size) {
    memset(buffer, 0, buf_size);
    uint16_t dg_size = 12 + this->func_name.size() + this->data.size();
    if (buf_size < dg_size)
        return 0;
    char *ptr = (char *) buffer;
    // flags
    *(uint16_t *) ptr = htons(this->flags);
    ptr += 2;
    // 报文id
    *(uint16_t *) ptr = htons(this->id);
    ptr += 2;
    // 1字节待定字段
    ptr++;
    // 函数名长度
    this->func_name_length = this->func_name.size();
    strncpy(ptr++, (char *) &this->func_name_length, 2);
    // 数据字段长度
    this->data_length = this->data.size();
    *(uint16_t *) ptr = htons(this->data_length);
    ptr += 2;
    // 环境编号
    *(uint16_t *) ptr = htons(this->env_number);
    ptr += 2;
    // 2字节待定字段
    ptr += 2;
    // 函数名称字段
    strncpy(ptr, this->func_name.data(), this->func_name.size());
    ptr += this->func_name.size();
    // 数据字段
    strncpy(ptr, this->data.data(), this->data.size());
    ptr += this->data.size();
    return ptr - (char *) buffer;
}

void nuts_datagram::show_info() const noexcept {

    int width[2] = {10, 10};
    cout << std::setiosflags(std::ios::left);
    cout << "-------------------------------------------" << endl;
    cout << setw(width[0]) << "FLAG" << std::setw(width[1]) << std::hex << flags << std::dec << endl;
    cout << setw(width[0]) << "ID" << std::setw(width[1]) << id << endl;
    cout << setw(width[0]) << "DATA1_LEN" << std::setw(width[1]) << int(func_name_length) << endl;
    cout << setw(width[0]) << "DATA2_LEN" << std::setw(width[1]) << data_length << endl;
    cout << setw(width[0]) << "ENV_NUMBER" << std::setw(width[1]) << env_number << endl << endl;
    cout << setw(width[0]) << "TYPE" << std::setw(width[1]) << nuts_type_2_text(this->get_type()) << endl;
    cout << setw(width[0]) << "FORMAT" << std::setw(width[1]) << nuts_format_2_text(this->get_format()) << endl;
    cout << setw(width[0]) << "STATUS" << std::setw(width[1]) << nuts_status_code_2_text(this->get_status_code())
         << endl;

    cout << "--------DATA1-------" << endl;
    cout << func_name << endl;
    cout << "--------DATA2-------" << endl;
    cout << data << endl;
    cout << "-------------------------------------------" << endl << endl;

}

nuts_paramters nuts_datagram::get_parameters() {
    Json::Reader r;
    nuts_paramters params;
    if (not r.parse(data, params))
        return Json::nullValue;
    return params;
}

nuts_returns nuts_datagram::get_returns() {
    return get_parameters();
}

void nuts_datagram::set_func_name(std::string func_name) {
    this->data1 = func_name;
}

string nuts_datagram::get_func_name() {
    return this->func_name;
}

void nuts_datagram::set_return(nuts_returns &v) {
    this->data = std::move(v.toStyledString());
}

void nuts_datagram::set_data1(nuts_json_data &v) {
    this->func_name = std::move(v.toStyledString());
}

void nuts_datagram::set_data1(string v) {
    this->data1 = std::move(v);
}

string nuts_datagram::get_data1() {
    return this->data1;
}

void nuts_datagram::set_data2(nuts_json_data &v) {
    this->data = std::move(v.toStyledString());
}

void nuts_datagram::set_data2(string v) {
    this->data2 = std::move(v);
}

string nuts_datagram::get_data2() {
    return this->data2;
}

void nuts_datagram::set_parameters(nuts_paramters &v) {
    set_return(v);
}

void nuts_datagram::initialize_request() noexcept {
    this->set_type(NUTS_TYPE_REQUEST);
    this->set_format(NUTS_FORMAT_JSON);
    this->set_status_code(NUTS_STATUS_CODE_OK);
    this->id = generate_nuts_id();
}

void nuts_datagram::initialize_response() noexcept {
    this->set_type(NUTS_TYPE_RESPONSE);
    this->set_format(NUTS_FORMAT_JSON);
    this->set_status_code(NUTS_STATUS_CODE_OK);
}

void nuts_datagram::initialize_response(nuts_datagram &d) noexcept {
    this->set_type(NUTS_TYPE_RESPONSE);
    this->set_format(NUTS_FORMAT_JSON);
    this->set_status_code(NUTS_STATUS_CODE_OK);
    this->set_urge(d.get_urge());
    this->set_resend(d.get_resend());
    this->id = d.id;
}

void nuts_datagram::set_type(uint16_t type) noexcept {
    if (type > 0x000f)
        return;
    type <<= 12;
    this->flags &= 0x0fff;
    this->flags |= type;
}

uint16_t nuts_datagram::get_type() const noexcept {
    return (this->flags & 0xf000) >> 12;
}

void nuts_datagram::set_format(uint16_t f) noexcept {
    if (f > 0x0003)
        return;
    f <<= 10;
    this->flags &= 0xf3ff;
    this->flags |= f;
}

uint16_t nuts_datagram::get_format() const noexcept {
//    cout<<"flag!" << flags << endl;
    return (this->flags & 0x0c00) >> 10;
}


void nuts_datagram::set_urge(bool urge) {
    if (urge) {
        this->flags |= 0x0200;
    } else {
        this->flags &= 0xfcff;
    }
}

bool nuts_datagram::get_urge() {
    return this->flags & 0x0200;
}

void nuts_datagram::set_resend(bool resend) {
    if (resend) {
        this->flags |= 0x0100;
    } else {
        this->flags &= 0xfeff;
    }
}

bool nuts_datagram::get_resend() {
    return this->flags & 0x0100;
}

void nuts_datagram::set_status_code(uint16_t sc) {
    if (sc > 0x000f) {
        return;
    }
    this->flags &= 0xfff0;
    this->flags |= sc;
}

uint16_t nuts_datagram::get_status_code() const {
    return this->flags & 0x000f;
}

uint16_t nuts_datagram::get_id() const noexcept {
    return this->id;
}

void nuts_datagram::set_id(uint16_t id) {
    this->id = id;
}

void nuts_datagram::format_error() noexcept {
    this->set_type(NUTS_TYPE_RESPONSE);
    this->set_status_code(NUTS_STATUS_CODE_FORMAT_ERROR);
    this->set_format(NUTS_FORMAT_TEXT);
    this->set_data1("NUTS REQUEST FORMAT ERROR!");
    this->set_data2("");
}

void nuts_datagram::refused() noexcept {
    this->set_type(NUTS_TYPE_RESPONSE);
    this->set_status_code(NUTS_STATUS_CODE_REFUSED);
    this->set_format(NUTS_FORMAT_TEXT);
    this->set_data1("Receiver refused!");
    this->set_data2("");
}

void nuts_datagram::not_found() noexcept {
    this->set_type(NUTS_TYPE_RESPONSE);
    this->set_status_code(NUTS_STATUS_CODE_NOT_FOUND);
    this->set_format(NUTS_FORMAT_TEXT);
    this->set_data1("Remote process not found !");
    this->set_data2("");
}

void nuts_datagram::error(std::string v) noexcept {
    this->set_type(NUTS_TYPE_RESPONSE);
    this->set_status_code(NUTS_STATUS_CODE_ERROR);
    this->set_format(NUTS_FORMAT_TEXT);
    if (v.size() == 0)
        this->set_data1("Unknown error");
    else
        this->set_data1(std::move(v));
    this->set_data2("");
}

string nuts_type_2_text(uint16_t type) {
    string ret = "Unknown";
    switch (type) {
        case NUTS_TYPE_REQUEST:
            ret = "Nuts Request";
            break;
        case NUTS_TYPE_RESPONSE:
            ret = "Nuts Response";
            break;
        case NUTS_TYPE_SERVER_REPORT:
            ret = "Server Report";
            break;
        case NUTS_TYPE_SERVER_REPORT_RESPONSE:
            ret = "Server Report Response";
    }
    return ret;

}

string nuts_status_code_2_text(uint16_t code) {
    string ret = "Unknown";
    switch (code) {
        case NUTS_STATUS_CODE_OK:
            ret = "OK";
            break;
        case NUTS_STATUS_CODE_ERROR:
            ret = "ERROR";
            break;
        case NUTS_STATUS_CODE_NOT_FOUND:
            ret = "NOT FOUND";
            break;
        case NUTS_STATUS_CODE_FORMAT_ERROR:
            ret = "FORMAT ERROR";
            break;
        case NUTS_STATUS_CODE_REFUSED:
            ret = "REFUSED";
            break;
    }
    return ret;

}

string nuts_format_2_text(uint16_t f) {
    string ret = "Unknown";
    switch (f) {
        case NUTS_FORMAT_JSON:
            ret = "JSON";
            break;
        case NUTS_FORMAT_TEXT:
            ret = "TEXT";
            break;
    }
    return ret;

}
