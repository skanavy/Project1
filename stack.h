#pragma once

#include "linked_list.hpp"

#include <vector>

using namespace std;

// LIFO last in first out -> stack
template <typename T>
class Stack {
public:
    virtual T top() const = 0; // O(1)
    virtual void pushTop(const T& elem) = 0; // O(1)
    virtual T popTop() = 0; // O(1)
    virtual bool empty() const = 0; // O(1)
    virtual size_t size() const = 0; // O(1)
};

template <typename T>
class LinkedListBasedStack: public Stack<T> {
public:
    T top() const override {
        return list_.head()->value;
    }

    void pushTop(const T& elem) override {
        list_.push_head(elem);
    }

    T popTop() override {
        T result = top();
        list_.pop_head();
        return result;
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

template <typename T>
class VectorBasedStack: public Stack<T> {
public:
    T top() const override {
        return vector_[vector_.size() - 1];
    }

    void pushTop(const T& elem) override {
        vector_.push_back(elem);
    }

    T popTop() override {
        T result = top();
        vector_.pop_back();
        return result;
    }

    bool empty() const override {
        return vector_.empty();
    }

    size_t size() const override {
        return vector_.size();
    }

private:
    vector<T> vector_;
};
