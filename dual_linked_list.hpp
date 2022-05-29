#pragma once

#include <iostream>

using namespace std;

template <typename T>
class DualLinkedNode {
public:
    T value;

    DualLinkedNode<T>* next() {
        return next_;
    }

    DualLinkedNode<T>* prev() {
        return prev_;
    }

private:
    DualLinkedNode(T value, DualLinkedNode<T>* next = nullptr, DualLinkedNode<T>* prev = nullptr)
        : value(value)
        , next_(next)
        , prev_(prev)
    {
    }

    DualLinkedNode<T>* next_;
    DualLinkedNode<T>* prev_;

    template<typename Elem>
    friend class DualLinkedList;
};

template <typename Elem>
class DualLinkedList {
public:
    DualLinkedNode<Elem>* head() const {
        return head_;
    }

    DualLinkedNode<Elem>* tail() const {
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
            DualLinkedNode<Elem>* newTail = new DualLinkedNode<Elem>(elem, nullptr, tail_);
            tail_->next_ = newTail;
            tail_ = newTail;
        } else {
            assert(head_ == nullptr);
            DualLinkedNode<Elem>* newTail = new DualLinkedNode<Elem>(elem);
            head_ = newTail;
            tail_ = newTail;
        }
        size_++;
    }

    void pop_tail() {
        assert(tail_);
        DualLinkedNode<Elem>* oldTail = tail_;
        tail_ = tail_->prev_;
        if (tail_) {
            assert(tail_->next_ == oldTail);
            tail_->next_ = nullptr;
        } else {
            assert(head_ == oldTail);
            head_ = nullptr;
        }
        delete oldTail;
        size_--;
    }

    void push_head(const Elem& elem) {
        if (head_) {
            assert(head_->prev_ == nullptr);
            DualLinkedNode<Elem>* newHead = new DualLinkedNode<Elem>(elem, head_);
            head_->prev_ = newHead;
            head_ = newHead;
        } else {
            assert(tail_ == nullptr);
            DualLinkedNode<Elem>* newNode = new DualLinkedNode<Elem>(elem);
            head_ = newNode;
            tail_ = newNode;
        }
        size_++;
    }

    void pop_head() {
        assert(head_);
        DualLinkedNode<Elem>* oldHead = head_;
        head_ = head_->next_;
        if (head_) {
            assert(head_->prev_ == oldHead);
            head_->prev_ = nullptr;
        } else {
            assert(tail_ == oldHead);
            tail_ = nullptr;
        }
        delete oldHead;
        size_--;
    }

    void remove(DualLinkedNode<Elem>* node) {
        assert(node);
        if (!node->prev_) {
            assert(node == head_);
            pop_head();
        } else if (!node->next_) {
            assert(node == tail_);
            pop_tail();
        } else {
            assert(node->prev_->next_ == node);
            node->prev_->next_ = node->next_;
            assert(node->next_->prev_ == node);
            node->next_->prev_ = node->prev_;
            delete node;
            size_--;
        }
    }

    /////////
    void insert_after(DualLinkedNode<Elem>* node, const Elem& elem) {
        assert(node);
        if (!node->next_) {
            assert(node == tail_);
            push_tail(elem);
        } else {
            DualLinkedNode<Elem>* newNode = new DualLinkedNode<Elem>(elem, node->next_, node);
            node->next_->prev_ = newNode;
            node->next_ = newNode;
            size_++;
        }
    }

    void insert_before(DualLinkedNode<Elem>* node, const Elem& elem) {
        assert(node);
        if (!node->prev_) {
            assert(node == head_);
            push_head(elem);
        } else {
            DualLinkedNode<Elem>* newNode = new DualLinkedNode<Elem>(elem, node->prev_, node);
            node->prev_->next_ = newNode;
            node->prev_ = newNode;
            size_++;
        }
    }

private:
    DualLinkedNode<Elem>* head_ = nullptr;
    DualLinkedNode<Elem>* tail_ = nullptr;

    size_t size_ = 0;
};
