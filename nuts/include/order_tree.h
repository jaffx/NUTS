//
// Created by lyn on 2023/2/24.
//

#ifndef XSTL_ORDER_TREE_H
#define XSTL_ORDER_TREE_H

#include <exception>
#include <stdexcept>
#include <stack>
#include <vector>
#include <utility>
#include <iostream>
#include <stack>


using std::stack, std::vector;
using std::initializer_list;
using std::cout, std::endl;
using std::pair;
using std::string;


 vector<string> path_to_vector(string);
 string vector_to_path(vector<string>);


template<typename KT, typename VT>
class tree_node {
public:
    pair<KT, VT> data;
    tree_node<KT, VT> *child = nullptr;
    tree_node<KT, VT> *next_brother = nullptr, *last_brother = nullptr;
    tree_node<KT, VT> *father = nullptr;

    tree_node() {};

    tree_node(KT, VT);

    tree_node(pair<KT, VT>);


    tree_node<KT, VT> *insert_into_child(KT, VT);

    tree_node<KT, VT> *insert_into_child(pair<KT, VT>);

    void show(int deep);

    void delete_cb();

    tree_node *operator[](KT k);

    ~tree_node();
};

template<typename KT, typename VT>
class order_tree {
public:
    tree_node<KT, VT> root;

    tree_node<KT, VT> &operator[](VT &);

//    tree_node<KT, VT> *insert_node(KT, VT);

//    tree_node<KT, VT> *insert_node(vector<std::pair<KT, VT>> &);


//    tree_node<KT, VT> *insert_node(vector<std::pair<KT, VT>> &&);


    tree_node<KT, VT> *insert_node(vector<KT>, VT v);
    tree_node<KT, VT> *insert_node(string , VT v);

    int delete_node(vector<KT> &);

    int delete_node(vector<KT> &&);

    int delete_node(string path);


    VT *find_node(vector<KT> &);

    VT *find_node(vector<KT> &&);

    VT *find_node(string path);


    void show_tree();

    order_tree() {};

    ~order_tree();
};

//
// Created by lyn on 2023/2/24.
//

#include "order_tree.h"


template<typename KT, typename VT>
tree_node<KT, VT>::tree_node(KT k, VT v) {
    this->data = std::move(std::make_pair(k, v));
}

template<typename KT, typename VT>
tree_node<KT, VT>::tree_node(pair<KT, VT> kv) {
    this->data = std::move(kv);
}

template<typename KT, typename VT>
void tree_node<KT, VT>::delete_cb() {
    if (this->child) {
        this->child->delete_cb();
        delete this->child;
        this->child = nullptr;
    }
    if (this->next_brother) {
        this->next_brother->delete_cb();
        delete this->next_brother;
        this->next_brother = nullptr;
    }
}

template<typename KT, typename VT>
tree_node<KT, VT>::~tree_node() {
//    if (this->last_brother) {
//        this->last_brother->
//                next_brother = nullptr;
//    } else if (this->father) {
//        this->father->child = nullptr;
//    }
////    std::cout << "Delete:--> " << this->data.first << std::endl;
}

template<typename KT, typename VT>
tree_node<KT, VT> *tree_node<KT, VT>::insert_into_child(pair<KT, VT> kv) {

    if (this->child == nullptr) {
        this->child = new tree_node<KT, VT>(kv);
        this->child->father = this;
        return this->child;
    }
    tree_node<KT, VT> *p = this->child, *q = this, *n;
    while (p and p->data.first < kv.first) {
        // 每一个节点只能注册一个服务
        q = p;
        p = p->next_brother;
    }
    if (p and p->data.first == kv.first) {
        // key相同，执行覆盖操作
        p->data.second = kv.second;
        return p;
    }
    if (q == this) {
        // q没动，说明插到头上
        q = new tree_node<KT, VT>(kv);
        q->next_brother = this->child;
        q->father = this;
        if (q->next_brother)
            q->next_brother->last_brother = q;
        this->child = q;
        return this->child;
    } else {
        // 插到q的后面
        n = new tree_node<KT, VT>(kv);
        n->father = this;
        n->next_brother = q->next_brother;
        if (q->next_brother)
            q->next_brother = n;
        n->last_brother = q;
        q->next_brother = n;
        return n;
    }
}

template<typename KT, typename VT>
tree_node<KT, VT> *tree_node<KT, VT>::insert_into_child(KT k, VT v) {
    return this->insert_into_child(std::make_pair(k, v));
}


template<typename KT, typename VT>
order_tree<KT, VT>::~order_tree() {
    if (root.child) {
        root.child->delete_cb();
        delete root.child;
    }

}

template<typename KT, typename VT>
tree_node<KT, VT> *tree_node<KT, VT>::operator[](KT key) {
    auto p = this->child;
    while (p) {
        if (p->data.first == key)
            return p;
        p = p->next_brother;
    }
    return p;
}

//template<typename KT, typename VT>
//tree_node<KT, VT> *order_tree<KT, VT>::insert_node(vector<std::pair<KT, VT>> &values) {
//    if (values.empty())
//        return nullptr;
//
//    auto next_ptr = this->root.insert_into_child(values[0]);
//    for (int idx = 1; idx < values.size(); idx++) {
//        next_ptr = next_ptr->insert_into_child(values[idx]);
//    }
//    return next_ptr;
//}



template<typename KT, typename VT>
tree_node<KT, VT> *order_tree<KT, VT>::insert_node(vector<KT> values, VT v) {
    if (values.empty())
        return nullptr;
    if (values.size() == 1) {
        if (root[values[0]]) {
            // 插入失败
            cout << "插入失败" << endl;
            return nullptr;
        } else
            return root.insert_into_child(values[0], v);
    }

    auto next_ptr = this->root[values[0]];
    for (
            int idx = 1;
            idx < values.

                    size()

                  - 1 and
            next_ptr;
            idx++) {
        next_ptr = (*next_ptr)[values[idx]];
    }
    if (next_ptr == nullptr) {
        cout << "插入失败" << endl;
        return nullptr;
    }

    auto &new_key = values.at(values.size() - 1);
    return next_ptr->insert_into_child(new_key, v);

}

template<typename KT, typename VT>
tree_node<KT, VT> *order_tree<KT, VT>::insert_node(string path, VT v) {
    return this->insert_node(path_to_vector(std::move(path)), std::move(v));
}
template<typename KT, typename VT>
int order_tree<KT, VT>::delete_node(string path) {
   return  this->delete_node(path_to_vector(std::move(path)));
}
template<typename KT, typename VT>
VT* order_tree<KT, VT>::find_node(string path) {
    return this->find_node(path_to_vector(std::move(path)));
}

//template<typename KT, typename VT>
//tree_node<KT, VT> *order_tree<KT, VT>::insert_node(vector<std::pair<KT, VT>> &&values) {
//    if (values.empty())
//        return nullptr;
//    auto next_ptr = this->root.insert_into_child(values[0]);
//    for (int idx = 1; idx < values.size(); idx++) {
//        next_ptr = next_ptr->insert_into_child(values[idx]);
//    }
//    return next_ptr;
//}


//template<typename KT, typename VT>
//tree_node<KT, VT> *order_tree<KT, VT>::insert_node(KT k, VT v) {
//    return this->root.insert_into_child(std::make_pair(k, v));
//}


template<typename KT, typename VT>
void order_tree<KT, VT>::show_tree() {
    if (this->root.child)
        this->root.child->show(0);
}

template<typename KT, typename VT>
tree_node<KT, VT> &order_tree<KT, VT>::operator[](VT &v) {
    if (this->root == nullptr)
        throw std::out_of_range("The value is out of range");
    return *(this->root)[v];
}

template<typename KT, typename VT>
void tree_node<KT, VT>::show(int deep) {
    for (int i = 0; i < deep; i++)
        cout << "|   ";

    cout << "|-- " << this->data.first << " : " << this->data.second << endl;
    if (this->child)
        this->child->show(deep + 1);
    if (this->next_brother)
        this->next_brother->show(deep);
}

template<typename KT, typename VT>
int order_tree<KT, VT>::delete_node(vector<KT> &values) {
    // 0 失败
    // 1 成功
    auto *p = &root;

    for (auto it = values.begin(); it != values.end(); it++) {
        // 尝试找到节点
        p = (*p)[*it];
        if (not p)  // 未找到节点，失败
            return 0;
    }
    // 找到节点，执行删除操作
    if (p->child) { // 节点存在子节点，对子节点进行递归删除
        p->child->delete_cb();
        delete p->child;
    }
    if (p->last_brother) {
        // 如果不是第一个子节点，相当于对链表进行删除操作，只需要修改前一个节点和后一个节点的连接关系即可
        p->last_brother->next_brother = p->next_brother;
        if (p->next_brother)
            p->next_brother->last_brother = p->last_brother;

    } else if (p->father) {
        // 需要修改与父节点之间的连接关系
        p->father->child = p->next_brother;
        if (p->next_brother)
            p->next_brother->last_brother = nullptr;
    }
    delete p;
    return 1;
}

template<typename KT, typename VT>
VT *order_tree<KT, VT>::find_node(vector<KT> &values) {
    // 找到某个路径上的节点
    auto *p = &root;

    for (auto it = values.begin(); it != values.end(); it++) {
        // 尝试找到节点
        p = (*p)[*it];
        if (not p)  // 未找到节点，失败
            return nullptr;
    }
    return &(p->data.second);

}

template<typename KT, typename VT>
VT *order_tree<KT, VT>::find_node(vector<KT> &&values) {
    return this->find_node(values);
}


template<typename KT, typename VT>
int order_tree<KT, VT>::delete_node(vector<KT> &&values) {
    return this->delete_node(values);
}


#endif //XSTL_ORDER_TREE_H
