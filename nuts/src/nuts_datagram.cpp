//
// Created by lyn on 2023/2/18.
//


#include "nuts_datagram.h"

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
    cout << "-------------------------------------------" << endl;
    cout << setw(width[0]) << "FLAG" << std::setw(width[1]) << std::hex << flags << std::dec << endl;
    cout << setw(width[0]) << "ID" << std::setw(width[1]) << id << endl;
    cout << setw(width[0]) << "FUN_LEN" << std::setw(width[1]) << int(func_name_length) << endl;
    cout << setw(width[0]) << "DATA_LEN" << std::setw(width[1]) << data_length << endl;
    cout << setw(width[0]) << "ENV_NUMBER" << std::setw(width[1]) << env_number << endl;
    cout << "--------FUNC_NAME-------" << endl;
    cout << func_name << endl;
    cout << "--------DATA-------" << endl;
    cout << data << endl;
    cout << "-------------------------------------------" << endl << endl;

}