# Първо занятие

## Преговор на рекурсия

Засегнати теми:

* Пълно изчерпване
* Търсене с връщане назад
* Генериране на комбинаторни конфигурации

[Преговор на материала от курса по УП](https://github.com/fmi-lab/up-kn-2023-2024-group-3-seminar/tree/main/Седмица%2011%20-%20Рекурсия%20с%20връщане%20назад)

Материали и задачи от семинарите:

* [КН, Група 1](https://github.com/peshe/FMI-SDP-2024/tree/main/Семинари/Компютърни%20науки/Група%201/Week%201)
* [КН, Група 3](https://github.com/peshe/FMI-SDP-2024/tree/main/Семинари/Компютърни%20науки/Група%203/Седмица%2001%20-%20Преговор%2C%20двоични%20файлове#преговор---рекурсивни-алгоритми)
* [КН, Група 4](https://github.com/peshe/FMI-SDP-2024/blob/main/Семинари/Компютърни%20науки/Група%204/Week%201%20-%20Recursion%2C%20Backtracking/Presentation.pdf)
* [Информатика, Група 3](https://github.com/peshe/FMI-SDP-2024/blob/main/Семинари/Информатика/Група%203/02_Recursion/tasks.md)

### Задачи

#### Задача 1: Факториел

Напишете рекурсивна функция за изчисление на [факториел](https://en.wikipedia.org/wiki/Factorial) от естествено число `n`.

Пример:

```cpp
Вход: 5
Изход: 120

Вход: 0
Изход: 1
```

---

#### Задача 2: Числа на Фибоначи

Напишете рекурсивна функция, която генерира `n`-тото [число на Фибоначи](https://en.wikipedia.org/wiki/Fibonacci_sequence).

Пример:

```cpp
Вход: 7
Изход: 13

Вход: 10
Изход: 55
```

---

#### Задача 3: Двоично търсене

Напишете рекурсивна функция за [двоично търсене](https://en.wikipedia.org/wiki/Binary_search) в сортиран масив.  Функцията да връща индекса, на който се намира търсеният елемент.  Ако такъв не съществува, да върне `-1`.

Вход:  
*размерът на масива*  
*елементите на масива, разделени с интервали*  
*търсеният елемент*  

Изход: индексът на търсения елемент.

Пример:

```cpp
Вход: 
8
1 3 5 7 9 11 13 15
7

Изход: 3
```

---

#### Задача 4: Генериране на пермутации

Напишете рекурсивна функция за генериране на всички [пермутации](https://en.wikipedia.org/wiki/Permutation) на даден набор от символи.

Вход: низ от символи, които да бъдат пермутирани.

Изход: всички пермутации на дадените символи, разделени с нови редове.

Пример:

```cpp
Вход:
ABC

Изход:
ABC
ACB
BAC
BCA
CAB
CBA
```

---

#### Задача 5: Най-дълга обща подпоследователност

Напишете рекурсивна функция, която намира [най-дългата обща подпоследователност](https://en.wikipedia.org/wiki/Longest_common_subsequence) на два низа.

Вход:  
*низ 1*  
*низ 2*  

Изход: най-дългата обща подпоследователност на двата низа.

Пример:

```cpp
Вход:
ABCDGH
AEDFHR

Изход:
ADH
```

---

#### Задача 6: [Генериране на подмножества](https://leetcode.com/problems/subsets/description/?envType=problem-list-v2&envId=backtracking)

### Задачи за упражнение вкъщи

* [Задача 7](https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/?envType=problem-list-v2&envId=backtracking)
* [Задача 8](https://leetcode.com/problems/binary-watch/description/?envType=problem-list-v2&envId=backtracking)
* [Задача 9](https://leetcode.com/problems/word-search/description/?envType=problem-list-v2&envId=backtracking)
* [Задача 10](https://leetcode.com/problems/generate-parentheses/description/?envType=problem-list-v2&envId=backtracking)
* [Задача 11](https://leetcode.com/problems/restore-ip-addresses/description/?envType=problem-list-v2&envId=backtracking)
* [Задача 12](https://leetcode.com/problems/ambiguous-coordinates/description/?envType=problem-list-v2&envId=backtracking)

## Бинарни файлове

Вижте [binary-files.md](binary-files.md).
