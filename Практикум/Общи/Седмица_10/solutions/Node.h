#ifndef _NODE_T_H_
#define _NODE_T_H_

template <typename T>
class Node {
public:
    T value;
    Node* left;
    Node* right;

    Node(T value = T(), Node* left = nullptr, Node* right = nullptr)
      : value(value), left(left), right(right)
    { }

    ~Node() {
      delete left;
      delete right;
    }
};

#endif // _NODE_T_H_
