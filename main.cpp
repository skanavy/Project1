#include "pasha_lib.hpp"

#include <iostream>
#include <list>
#include <cassert>

using namespace pasha_lib;
using namespace std;

template <typename T>
class Node {
public:
    T value;

    Node<T>* next() {
        return next_;
    }

    Node<T>* prev() {
        return prev_;
    }

private:
    Node(T value, Node<T>* next = nullptr, Node<T>* prev = nullptr)
        : value(value)
        , next_(next)
        , prev_(prev)
    {
    }

    Node<T>* next_;
    Node<T>* prev_;

    template<typename Elem>
    friend class List;
};

template <typename Elem>
class List {
public:
    Node<Elem>* head() const {
        return head_;
    }

    Node<Elem>* tail() const {
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
            Node<Elem>* newTail = new Node<Elem>(elem, nullptr, tail_);
            tail_->next_ = newTail;
            tail_ = newTail;
        } else {
            assert(head_ == nullptr);
            Node<Elem>* newTail = new Node<Elem>(elem);
            head_ = newTail;
            tail_ = newTail;
        }
        size_++;
    }

    void pop_tail() {
        assert(tail_);
        Node<Elem>* oldTail = tail_;
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
            Node<Elem>* newHead = new Node<Elem>(elem, head_);
            head_->prev_ = newHead;
            head_ = newHead;
        } else {
            assert(tail_ == nullptr);
            Node<Elem>* newNode = new Node<Elem>(elem);
            head_ = newNode;
            tail_ = newNode;
        }
        size_++;
    }

    void pop_head() {
        assert(head_);
        Node<Elem>* oldHead = head_;
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

    void remove(Node<Elem>* node) {
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

    void insert_after(Node<Elem>* node, const Elem& elem) {
        assert(node);
        if (!node->next_) {
            assert(node == tail_);
            push_tail(elem);
        } else {
            Node<Elem>* newNode = new Node<Elem>(elem, node->next_, node);
            node->next_->prev_ = newNode;
            node->next_ = newNode;
            size_++;
        }
    }

    void insert_before(Node<Elem>* node, const Elem& elem) {
        assert(node);
        if (!node->prev_) {
            assert(node == head_);
            push_head(elem);
        } else {
            Node<Elem>* newNode = new Node<Elem>(elem, node->prev_, node);
            node->prev_->next_ = newNode;
            node->prev_ = newNode;
            size_++;
        }
    }

private:
    Node<Elem>* head_ = nullptr;
    Node<Elem>* tail_ = nullptr;

    size_t size_ = 0;
};

//class Queue()...

int main() {
    const size_t SIZE = 10000000;
    executeAndPrintTime("vector: ", TimeMeasureUnit::milliseconds, [&] {
        vector<int> v;
        size_t max_size = 0;
        for (size_t i = 0; i < SIZE; ++i) {
            if (randInt(0, 2) != 0) {
                v.push_back(randInt(0, 10000));
                if (v.size() > max_size) {
                    max_size = v.size();
                }
            } else {
                if (v.empty()) continue;
                v.erase(v.begin());
            }
        }
        cout << max_size << endl;
    });

    executeAndPrintTime("list: ", TimeMeasureUnit::milliseconds, [&] {
        List<int> l;
        for (size_t i = 0; i < SIZE; ++i) {
            if (randInt(0, 2) != 0) {
                l.push_tail(randInt(0, 10000));
            } else {
                if (l.empty()) continue;
                l.pop_head();
            }
        }
    });

    return 0;
}
