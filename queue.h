#pragma once

#include "linked_list.hpp"

// FIFO first in first out -> queue
template <typename T>
class Queue {
public:
    virtual T front() const = 0; // O(1)
    virtual T dequeue() = 0; // O(1)
    virtual void enqueue(const T& elem) = 0; // O(1)
    virtual bool empty() const = 0; // O(1)
    virtual size_t size() const = 0; // O(1)
};

template <typename T>
class LinkedListBasedQueue: public Queue<T> {
public:
    T front() const override {
        assert(!list_.empty());
        return list_.head()->value;
    }

    T dequeue() override {
        assert(!list_.empty());
        T result = front();
        list_.pop_head();
        return result;
    }

    void enqueue(const T& elem) override {
        list_.push_tail(elem);
    }

    bool empty() const override {
        return list_.empty();
    }

    size_t size() const override {
        return list_.size();
    }

private:
    LinkedList<T> list_;
};
