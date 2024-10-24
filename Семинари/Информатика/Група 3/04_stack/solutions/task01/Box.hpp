#ifndef SDP_20241023_BOX_HPP
#define SDP_20241023_BOX_HPP

template<class T>
struct Box {
    T data;
    Box *next;

    Box *clone() {
        Box *result = new Box{data, nullptr};
        if (this->next) {
            result->next = this->next->clone();
        }
        return result;
    }
};


#endif //SDP_20241023_BOX_HPP
