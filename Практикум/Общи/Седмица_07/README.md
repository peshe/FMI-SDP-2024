# Общи задачи за практикум -- седмица 07

## Задачи за двоични дървета

### Задача 0

Модифицирайте дадения клас [`Node`](../Седмица_05/solutions/Node.h) от по-предната седмица, така че той да представя възел от двоично дърво. Не е нужно да имплементирате всичките му методи.

### Задача 1

Реализирайте функция `void printLeftParentRight(const Node<T>* btree)`, която по подаден корен на двоично дърво `btree` принтира елементите му в ред ляво дете - родител - дясно дете.

```cpp
Вход:
Node<int> *btree = new Node<int>(1,
                               new Node<int>(2,
                                              new Node<int>(3),
                                              new Node<int>(4)),
                               new Node<int>(5,
                                              new Node<int>(6),
                                              new Node<int>(7)));

Изход:
3 2 4 1 6 5 7
```

### Задача 2

Да се напише функция `std::size_t findNodesNumber(Node<T> *btree)`, която по подаден корен на двоично дърво преброява колко възела има в дървото.

```cpp
Вход:
Node<int> *btree = new Node<int>(1,
                               new Node<int>(2,
                                              new Node<int>(3),
                                              new Node<int>(4)),
                               new Node<int>(5,
                                              new Node<int>(6),
                                              new Node<int>(7)));

Изход:
7
```

### Задача 3

Да се напише функция

```cpp
template <typename Type, typename Result>
Result accumulateBTree(
    const Node<Type> *btree,
    const std::function<Result(const Type&)>& transformValueFunc,
    const std::function<Result(const Result&, const Result&)>& accumulateFunc,
    const Result& initialValue
)
```

, която по подаден корен на двоично дърво, трансформираща стойността на възела функция, акумулираща функция и начална стойност(неутрална спрямо акумулиращата функция) връща получения резултат за цялото дърво.

```cpp
Пример:
Node<int> *btree = new Node<int>(1,
                               new Node<int>(2,
                                              new Node<int>(3),
                                              new Node<int>(4)),
                               new Node<int>(5,
                                              new Node<int>(6),
                                              new Node<int>(7)));
std::function<int(const int&)> squareFn = [] (const int& value) -> int { return value * value; };
std::function<int(const int&, const int&)> sumFn = [] (const int& value1, const int& value2) -> int { return value1 + value2; };

std::cout << accumulateBTree<int, int>(btree, squareFn, sumFn, 0) << std::endl;

Изход:
// 1*1 + 2*2 + 3*3 + 4*4 + 5*5 + 6*6 + 7*7
140
```

### Задача 4

Да се дефинира функция `Node<unsigned int>* generateBTree(unsigned int n)`, която по подадено естествено число `n` връща указател към двоично дърво, съставено от естествените числа от `1` до `n` по възлите. Ако на функцията се подаде аргумент `0`, нека да се върне `nullptr`. За точния начин на генериране вижте следния пример:

```cpp
Вход:
9

Тестване на функцията:
Node<unsigned int> *btree = generateBTree(9);
printLeftParentRight(btree);

Изход:
8 4 9 2 5 1 6 3 7
// т.е. зад btree стои дървото:
//      1
//     / \
//   2     3
//   /\    /\
//  4  5  6  7   
//  /\
// 8  9 

```

### Задача 5

Напишете функция `NodeList<T>* filterBTreeToList(const NodeBTree<T>* btree, const std::function<bool(const T&)>& pred)`, която приема корен на двоично дърво и предикат и връща главата на едносвързан списък, в който са сложени (копирани) всички елементи на дървото, отговарящи на предиката. Редът на елементите в списъка (начинът на обикаляне на дървото) не е от значение.

Забележка: може да зададете `template <typename T> using NodeBTree = Node<T>;`, след което да вземете отново списъка от по-предната седмица [`Node`](../Седмица_05/solutions/Node.h) и да го прекръстите на `NodeList`.

```cpp
Пример:
NodeBTree<int> *btree = new NodeBTree<int>(1,
                               new NodeBTree<int>(2,
                                              new NodeBTree<int>(3),
                                              new NodeBTree<int>(4)),
                               new NodeBTree<int>(5,
                                              new NodeBTree<int>(6),
                                              new NodeBTree<int>(7)));
std::function<bool(const int&)> pred = [] (const int& val) -> bool { return val % 2 == 0; };

NodeList<int> *filtered = filterBTreeToList(btree, pred);
print(filtered);

Изход:
2 4 6
```

### Задача 6

Напишете функция `void printFloors(const NodeBTree<T> *btree)`, която принтира двоично дърво по етажи.  

Допълнение: Помислете и реализирайте функция, която отново получава корен на двоично дърво и му сортира етажите, т.е. подрежда стойностите на всеки етаж, така че да са сортирани (приемете, че има дефиниран оператор `<` за типа `T`).

```cpp
Пример:
NodeBTree<int> *btree = new NodeBTree<int>(1,
                               new NodeBTree<int>(2,
                                              new NodeBTree<int>(3),
                                              new NodeBTree<int>(4)),
                               new NodeBTree<int>(5,
                                              new NodeBTree<int>(6),
                                              new NodeBTree<int>(7)));
printFloors(btree);

Изход:
Floor 1: 1
Floor 2: 2 5
Floor 3: 3 4 6 7
```
