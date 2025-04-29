// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

struct SYM {
    char ch;
    int prior;
};

template<typename T>
class TPQueue {
private:
    struct Node {
        T      data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* head_{ nullptr };

public:
    TPQueue() = default;
    ~TPQueue() { clear(); }

    bool empty() const { return head_ == nullptr; }

    void push(const T& value) {
        Node* node = new Node(value);
        if (empty() || value.prior > head_->data.prior) {
            node->next = head_;
            head_ = node;
        }
        else {
            Node* cur = head_;
            while (cur->next && cur->next->data.prior >= value.prior) {
                cur = cur->next;
            }
            node->next = cur->next;
            cur->next = node;
        }
    }

    T pop() {
        if (empty()) throw std::underflow_error("TPQueue::pop(): empty");
        Node* tmp = head_;
        T      rv = tmp->data;
        head_ = head_->next;
        delete tmp;
        return rv;
    }

    const T& top() const {
        if (empty()) throw std::underflow_error("TPQueue::top(): empty");
        return head_->data;
    }

    void clear() {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
    }
};

#endif 
