#include "order_tree.h"
vector<string> path_to_vector(string path) {
    string value;
    vector<string> ret;
    for (auto &c: path) {
        if (c == '/') {
            if (value.size()) {
                ret.push_back(value);
                value.resize(0);
            }
        } else {
            value += c;
        }
    }
    if (value.size()) {
        ret.push_back(value);
        value.resize(0);
    }
    return ret;
}

string vector_to_path(vector<string> path) {
    if (path.empty())
        return "";
    string ret = path[0];
    for (int i = 1; i < path.size(); i++) {
        ret += "/";
        ret += path[i];
    }
    return ret;
}