#pragma once

#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class LinkedNode {
public:
    T value;

    LinkedNode<T>* next() {
        return next_;
    }

private:
    LinkedNode(T value, LinkedNode<T>* next = nullptr)
        : value(value)
        , next_(next)
    {
    }

    LinkedNode<T>* next_;

    template<typename Elem>
    friend class LinkedList;
};

template <typename Elem>
class LinkedList {
public:
    LinkedNode<Elem>* head() const {
        return head_;
    }

    LinkedNode<Elem>* tail() const {
        return tail_;
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void push_tail(const Elem& elem) {
        if (tail_) {
            assert(tail_->next_ == nullptr);
            LinkedNode<Elem>* newTail = new LinkedNode<Elem>(elem);
            tail_->next_ = newTail;
            tail_ = newTail;
        } else {
            assert(head_ == nullptr);
            LinkedNode<Elem>* newTail = new LinkedNode<Elem>(elem);
            head_ = newTail;
            tail_ = newTail;
        }
        size_++;
    }

    void push_head(const Elem& elem) {
        if (head_) {
            LinkedNode<Elem>* newHead = new LinkedNode<Elem>(elem, head_);
            head_ = newHead;
        } else {
            assert(tail_ == nullptr);
            LinkedNode<Elem>* newNode = new LinkedNode<Elem>(elem);
            head_ = newNode;
            tail_ = newNode;
        }
        size_++;
    }

    void pop_head() {
        assert(head_);
        LinkedNode<Elem>* oldHead = head_;
        head_ = head_->next_;
        if (!head_) {
            assert(tail_ == oldHead);
            tail_ = nullptr;
        }
        delete oldHead;
        size_--;
    }

    /////////
    void insert_after(LinkedNode<Elem>* node, const Elem& elem) {
        assert(node);
        if (!node->next_) {
            assert(node == tail_);
            push_tail(elem);
        } else {
            LinkedNode<Elem>* newNode = new LinkedNode<Elem>(elem, node->next_);
            node->next_ = newNode;
            size_++;
        }
    }

private:
    LinkedNode<Elem>* head_ = nullptr;
    LinkedNode<Elem>* tail_ = nullptr;

    size_t size_ = 0;
};
