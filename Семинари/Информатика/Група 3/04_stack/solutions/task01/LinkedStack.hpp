#ifndef SDP_20241023_LINKEDSTACK_HPP
#define SDP_20241023_LINKEDSTACK_HPP


#include <cstddef>
#include <stdexcept>
#include "Box.hpp"

template<class T>
class LinkedStack {
public:
    LinkedStack() : head(nullptr), size(0) {}

    LinkedStack(const LinkedStack &other) : head(nullptr), size(0) {
        this->head = other.head->clone();
    }

    LinkedStack &operator=(const LinkedStack &other) {
        if (this != &other) {
            Box<T> *newHead;
            try {
                newHead = other.head->clone();
            }
            catch (...) {
                clear(newHead);
                throw;
            }
            clear(this->head);
            this->head = newHead;
            this->size = other.size;
        }
        return *this;
    }

    ~LinkedStack() {
        clear(this->head);
    }

    void push(const T &item) {
        Box<T> *newBox;
        try {
            newBox = new Box<T>{item, nullptr};
        }
        catch (...) {
            clear(newBox);
            throw;
        }
        newBox->next = this->head;
        this->head = newBox;
    }

    void pop() {
        if (!this->head) {
            throw std::out_of_range("Stack is empty!");
        }

        Box<T> *tmp = this->head;
        this->head = this->head->next;
        delete tmp;
        this->size--;
    }

    const T &top() const {
        if (!this->head) {
            throw std::out_of_range("Stack is empty!");
        }

        return this->head->data;
    }

    bool isEmpty() const {
        return this->size == 0;
    }

private:
    static void clear(Box<T> *box) {
        if (box && box->next) {
            clear(box->next);
        }
        delete box;
    }

private:
    Box<T> *head;
    std::size_t size;
};


#endif //SDP_20241023_LINKEDSTACK_HPP
