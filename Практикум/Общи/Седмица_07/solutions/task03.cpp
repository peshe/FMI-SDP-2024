#include "Node.h"

#include <functional>
#include <iostream>


template <typename Type, typename Result>
Result accumulateBTree(
    const Node<Type> *btree,
    const std::function<Result(const Type&)>& transformValueFunc,
    const std::function<Result(const Result&, const Result&)>& accumulateFunc,
    const Result& initialValue
) {
    if (btree == nullptr) return initialValue;

    Result transformedValue = transformValueFunc(btree->value);
    Result accumulatedLeft = accumulateBTree(
        btree->left, transformValueFunc, accumulateFunc, initialValue
    );
    Result accumulatedRight = accumulateBTree(
        btree->right, transformValueFunc, accumulateFunc, initialValue
    );

    return accumulateFunc(
        accumulateFunc(transformedValue, accumulatedLeft),
        accumulatedRight
    );
}

int main () {
    Node<int> *btree = new Node<int>(1,
                               new Node<int>(2,
                                              new Node<int>(3),
                                              new Node<int>(4)),
                               new Node<int>(5,
                                              new Node<int>(6),
                                              new Node<int>(7)));
    std::function<int(const int&)> squareFn = [] (const int& value) -> int {
        return value * value;
    };
    std::function<int(const int&, const int&)> sumFn = [] (
        const int& value1, const int& value2
    ) -> int {
        return value1 + value2;
    };

    std::cout << accumulateBTree(btree, squareFn, sumFn, 0) << std::endl;

    delete btree;
    return 0;
}
