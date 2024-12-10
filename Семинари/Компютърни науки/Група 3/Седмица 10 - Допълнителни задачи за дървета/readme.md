# Седмица 10 - Допълнителни задачи за дървета

За решаването на следващите задачи използвайте следната структура:

```c++
template <typename T>
struct TreeNode {
  T data;
  TreeNode<T> *left, *right;

  TreeNode(const T& data, TreeNode<T>* const left = nullptr, TreeNode<T>* const right = nullptr)
    : data(data), left(left), right(right) {}
};
```

### Примерно дърво:
```c++
/*
        5
     /    \         
   1       8
  /\      /\     
4   3    0 11
 \      /\   
 13   10  9 
*/

TreeNode<int> *test_tree = 
  new TreeNode<int>(5, 
                    new TreeNode<int>(1, 
                                      new TreeNode<int>(4, 
                                                        nullptr, 
                                                        new TreeNode<int>(13)),
                                      new TreeNode<int>(3)),
                    new TreeNode<int>(8,
                                      new TreeNode<int>(0,
                                                        new TreeNode<int>(10),
                                                        new TreeNode<int>(9)),
                                      new TreeNode<int>(11)));
```

## Задача 01 - Пътища в дърво
```c++
template <typename T>
std::vector<std::vector<T>> paths(const TreeNode<T>* node);
```

Напишете функция, която намира всички пътища от корена на дърво до всяко негово листо.

### Пример:
```c++
for (const std::vector<int>& path : paths(test_tree)) {
  for (int i : path) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

/*
5 1 4 13 
5 1 3 
5 8 0 10 
5 8 0 9 
5 8 11
*/
```

## Задача 02 - Най-близък общ родител
```c++
template <typename T>
const TreeNode<T>* lowest_common_ancestor(const TreeNode<T>* node, const T& lhs, const T& rhs);
```

Напишете функция, която приема двоично дърво и две стойности. Функцията да намира най-близкия общ родител на върховете в дървото, съдържащи дадените стойности.

### Пример:
```c++
const TreeNode<int> *found1 = lowest_common_ancestor(test_tree, 4, 9);
const TreeNode<int> *found2 = lowest_common_ancestor(test_tree, 11, 9);
const TreeNode<int> *not_found = lowest_common_ancestor(test_tree, 7, 8);

if (found1) {
  std::cout << found1->data << '\n'; // -> 5
}
if (found2) {
  std::cout << found2->data << '\n'; // -> 8
}
if (not_found) {
  std::cout << "not found\n";
}
```

## Задача 03 - Огледално дърво
```c++
template <typename T>
bool is_mirror(const TreeNode<T>* node);
```

Напишете функция, която проверява дали двоично дърво е огледално. Огледално дърво наричаме такова дърво, на което дясното поддърво има обратно симетрична структура спрямо лявото.

### Пример:
```c++
/*
        4
       / \         
      1   6
     /\   /\     
    7  2 0  8
    \      / 
     10   11 
*/

TreeNode<int> *mirror = 
  new TreeNode<int>(4, 
                    new TreeNode<int>(1, 
                                      new TreeNode<int>(7, 
                                                        nullptr, 
                                                        new TreeNode<int>(10)),
                                      new TreeNode<int>(2)),
                    new TreeNode<int>(6,
                                      new TreeNode<int>(0),
                                      new TreeNode<int>(8,
                                                        new TreeNode<int>(11))));

std::cout << std::boolalpha << is_mirror(mirror) << '\n'; // -> true
std::cout << std::boolalpha << is_mirror(test_tree) << '\n'; // -> false
```

## Задача 04 - Интервално дърво
```c++
using Interval = std::pair<int, int>;

bool is_interval_tree(const TreeNode<Interval>* node);
```

Интервално дърво наричаме двоично дърво, което има за стойности по възлите интервали, представени като наредени двойки от началото и края на интервала, като за всяко поддърво, интервала в корена трябва да съдържа всеки интервал от неговите възлите. Напишете функция, която по подадено двоично дърво, съдържащо наредени двойки във възлите, проверява дали то е интервално.

### Пример:

```c++
TreeNode<Interval>* interval_tree = 
  new TreeNode<Interval>({1, 20},
                          new TreeNode<Interval>({5, 16},
                                                  new TreeNode<Interval>({6, 13},
                                                                          new TreeNode<Interval>({8, 12}),
                                                                          new TreeNode<Interval>({7, 8})),
                                                  new TreeNode<Interval>({8, 15},
                                                                          new TreeNode<Interval>({10, 11}),
                                                                          new TreeNode<Interval>({9, 13}))),
                          new TreeNode<Interval>({3, 16},
                                                  new TreeNode<Interval>({4, 15},
                                                                          new TreeNode<Interval>({5, 12}),
                                                                          new TreeNode<Interval>({6, 8})),
                                                  new TreeNode<Interval>({8, 11},
                                                                          new TreeNode<Interval>({9, 10}))));

TreeNode<Interval>* not_interval_tree = 
  new TreeNode<Interval>({1, 20},
                          new TreeNode<Interval>({5, 16},
                                                  new TreeNode<Interval>({6, 9},
                                                                          new TreeNode<Interval>({4, 12}),
                                                                          new TreeNode<Interval>({7, 8})),
                                                  new TreeNode<Interval>({8, 11},
                                                                          new TreeNode<Interval>({7, 9}),
                                                                          new TreeNode<Interval>({4, 3}))),
                          new TreeNode<Interval>({3, 16},
                                                  new TreeNode<Interval>({4, 15},
                                                                          new TreeNode<Interval>({5, 12}),
                                                                          new TreeNode<Interval>({6, 8})),
                                                  new TreeNode<Interval>({8, 11},
                                                                          new TreeNode<Interval>({2, 23}),
                                                                          new TreeNode<Interval>({4, 3}))));

std::cout << std::boolalpha << is_interval_tree(interval_tree) << '\n'; // -> true
std::cout << std::boolalpha << is_interval_tree(not_interval_tree) << '\n'; // -> false
```

## Задача 05 - Средна стойност
```c++
void replace_with_average(TreeNode<double>* node);
```

Напишете функция, която приема двоично дърво от реални числа и заменя стойностите във всеки възел със средно-аритметичното на минималната и максималната стойност в поддървото с корен съответния възел. Напишете функцията, така че всеки възел да бъде посетен точно по веднъж.

### Пример:
```c++
// First the tree needs to be converted to double
replace_with_average(test_tree);

// Function that prints the tree left-root-right
print_tree(test_tree); // -> 8.5 13 7 3 6.5 10 5 9 5.5 11
```