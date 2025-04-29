// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#pragma once
#include <stdexcept>
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

    bool IsEmpty() const { return head_ == nullptr; }

    void Push(const T& value) {
        Node* node = new Node(value);
        if (IsEmpty() || value.prior > head_->data.prior) {
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

    T Pop() {
        if (IsEmpty()) throw std::underflow_error("TPQueue::Pop(): empty");
        Node* tmp = head_;
        T      rv = tmp->data;
        head_ = head_->next;
        delete tmp;
        return rv;
    }

    const T& Top() const {
        if (IsEmpty()) throw std::underflow_error("TPQueue::Top(): empty");
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
#endif  // INCLUDE_TPQUEUE_H_
