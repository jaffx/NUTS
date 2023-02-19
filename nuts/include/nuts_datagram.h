//
// Created by lyn on 2023/2/18.
//

#ifndef NUTS_NUTS_DATAGRAM_H
#define NUTS_NUTS_DATAGRAM_H

#include <string>
#include <cstring>
#include <iostream>
#include<iomanip>
#define NUT_TYPE_REQUEST 0
#define NUT_TYPE_UNKNOWN 1
#define NUT_TYPE_LOG 2
#define NUT_TYPE_RESPONSE 3

#define NUT_FORMAT_TEXT 0
#define NUT_FORMAT_JSON 1

#define NUT_STATUS_CODE_OK 0
#define NUT_STATUS_CODE_ERROR 1
#define NUT_STATUS_CODE_FORMAT_ERROR 2
#define NUT_STATUS_CODE_REFUSED 3
#define NUT_STATUS_CODE_NOT_ABLE 4

using std::string;
using std::cout, std::endl;
using std::setw;

class nuts_datagram {
public:
    uint16_t flags;
    uint16_t id;
    uint16_t unset;
    uint8_t func_name_length;
    uint16_t data_length;
    uint16_t env_number;
    uint16_t unset2;
    string func_name;
    string data;


    nuts_datagram();
    int to_buffer(char *buffer, size_t buf_size);

    int parse_from_buffer(char *buffer, size_t buf_size);

    void show_info() const noexcept;
};


#endif //NUTS_NUTS_DATAGRAM_H
