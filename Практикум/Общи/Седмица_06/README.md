# Общи задачи за практикум -- седмица 05

## Задачи за двусвързан списък

### Задача 0

Модифицирайте дадения [`Node`](../Седмица_05/solutions/Node.h) клас от предходната седмица, така че той да представя възел от двусвързан списък.

### Задача 1

Реализирайте функция `void removeConsecutiveDuplicates(Node* lst)`, която премахва всички последователни повторения на елементи от двусвързания списък lst. Премахнатите елементи да се унищожават с `delete`.

```cpp
Вход:
1, 1, 2, 2, 1, 1, 2, 2, 2, 2, 1, 2, 1, 2
Изход:
1, 2, 1, 2, 1, 2, 1, 2
```

### Задача 2

Да се дефинира функция mirror, която добавя към свързан списък неговото огледално копие

```cpp
Вход:
1<->4<->5
Изход:
1<->4<->5<->5<->4<->1
```

### Задача 3

[LeetCode: 430. Flatten a Multilevel Doubly Linked List](https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/description/)

### Задача 4

Решете [LeetCode: 1472. Design Browser History](https://leetcode.com/problems/design-browser-history/description/), използвайки двусвързан списък.

*Допълнение: Решете същата задача, използвайки други от изучаваните досега структури от данни.*

### Задача 5

[LeetCode: 2296. Design a Text Editor](https://leetcode.com/problems/design-a-text-editor/description/)

## Задачи за цикличен списък

### Задача 6

Да се реализират задачи 1 и 2 от предходната седмица, но за цикличен списък.

### Задача 7

Да се реши [LeetCode: 1823. Find the Winner of the Circular Game](https://leetcode.com/problems/find-the-winner-of-the-circular-game/description/), като се използва цикличен списък.
