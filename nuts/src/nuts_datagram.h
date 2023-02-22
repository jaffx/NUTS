//
// Created by lyn on 2023/2/18.
//

#ifndef NUTS_NUTS_DATAGRAM_H
#define NUTS_NUTS_DATAGRAM_H

#include <string>
#include <cstring>
#include <iostream>
#include<iomanip>
#include <arpa/inet.h>
# include <jsoncpp/include/json/json.h>
#include <unordered_map>

#define NUTS_TYPE_REQUEST 0
#define NUTS_TYPE_RESPONSE 1
#define NUTS_TYPE_LOG 2
#define NUTS_TYPE_UNKNOWN 3

#define NUTS_FORMAT_TEXT 0
#define NUTS_FORMAT_JSON 1

#define NUTS_STATUS_CODE_OK 0
#define NUTS_STATUS_CODE_ERROR 1
#define NUTS_STATUS_CODE_FORMAT_ERROR 2
#define NUTS_STATUS_CODE_REFUSED 3
#define NUTS_STATUS_CODE_NOT_FOUND 4

using std::string;
using std::cout, std::endl;
using std::setw;
using std::unordered_map;

typedef Json::Value nuts_paramters;
typedef Json::Value nuts_returns;
typedef Json::Value nuts_json_data;

typedef nuts_returns (*nuts_function)(nuts_paramters &);

typedef unordered_map<string, nuts_function> nuts_fmap;

class nuts_datagram {
    uint16_t flags;
    uint16_t id;
    uint16_t unset;
    uint8_t func_name_length;
    uint16_t data_length;
    uint16_t env_number;
    uint16_t unset2;
    string func_name;
    string data;
    string &data1 = func_name;
    string &data2 = data;
public:
    friend class nuts_server;

    static uint16_t generate_nuts_id();

    nuts_datagram();

    int to_buffer(char *buffer, size_t buf_size);

    int parse_from_buffer(char *buffer, size_t buf_size);

    void show_info() const noexcept;

    nuts_paramters get_parameters();

    nuts_returns get_returns();

    void set_func_name(string func_name);

    string get_func_name();

    void set_return(nuts_returns &v);

    void set_parameters(nuts_paramters &v);

    void set_data1(nuts_json_data &v);

    void set_data1(string v);

    void set_data2(string v);

    string get_data1();

    void set_data2(nuts_json_data &v);

    string get_data2();

    void initialize_request() noexcept;

    void initialize_response() noexcept;

    void initialize_response(nuts_datagram &) noexcept;

    void set_type(uint16_t type) noexcept;

    uint16_t get_type() const noexcept;

    void set_format(uint16_t type) noexcept;

    uint16_t get_format() const noexcept;

    void set_urge(bool urge);

    bool get_urge();

    void set_resend(bool resend);

    bool get_resend();

    void set_status_code(uint16_t sc);

    uint16_t get_status_code() const;

    uint16_t get_id() const noexcept;

    void set_id(uint16_t id);

    void format_error() noexcept;

    void refused() noexcept;

    void not_found() noexcept;

    void error(string v = "") noexcept;

};
struct nuts_request {
    nuts_datagram data;
    sockaddr_in addr;
};

typedef nuts_request nuts_response;



string nuts_type_2_text(uint16_t);

string nuts_status_code_2_text(uint16_t);

string nuts_format_2_text(uint16_t);


#endif //NUTS_NUTS_DATAGRAM_H
