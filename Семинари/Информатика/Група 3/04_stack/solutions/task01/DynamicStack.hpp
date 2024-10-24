#ifndef SDP_20241023_DYNAMICSTACK_HPP
#define SDP_20241023_DYNAMICSTACK_HPP

#include<vector>
#include <stdexcept>

template<class T>
class DynamicStack {
public:
    void push(const T& item) {
        data.push_back(item);
    }

    void pop() {
        if(this->isEmpty()) {
            throw std::out_of_range("Stack is empty!");
        }

        data.pop_back();
    }

    const T& top() const {
        if(this->isEmpty()) {
            throw std::out_of_range("Stack is empty!");
        }

        return data.back();
    }

    bool isEmpty() const {
        return data.empty();
    }

private:
    std::vector<T> data;
};


#endif //SDP_20241023_DYNAMICSTACK_HPP
