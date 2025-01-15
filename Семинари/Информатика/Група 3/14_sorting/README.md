# СДП Семинар 14 -- Сортирания. Двоично и троично търсене

[Статия в Уикипедия за сортиращи алгоритми](https://en.wikipedia.org/wiki/Sorting_algorithm)

## Сортиращи алгоритми на базата на сравнение

### „Бавни“ алгоритми за сортиране

- Bubble Sort
- Insertion Sort
- Selection Sort

#### Задача 1

Имплеметирайте метода на мехурчето за сортиране на `std::vector`.

### „Бързи“ алгоритми за сортиране

- Quick Sort
- Merge Sort
- Heap Sort

#### Задача 2

Напишете шаблон за *quick sort* за сортиране на `std::vector` в C++.

#### Задача 3

Имплементирайте *merge sort* за свързан списък.

### Долна граница за броя на сравненията

Доказва се (следващия семестър по ДАА), че алгоритъм, който използва сравнения за сортиране, прави не по-малко от *nlog(n)* сравнения.

## Сортиране в линейно време

### Сортиране чрез броене

Counting Sort се използва когато имаме краен брой възможни стойности за елементите, които сортираме.

#### Задача 4

Решете [1051. Height Checker](https://leetcode.com/problems/height-checker/description/).

#### Задача 5

Решете [1122. Relative Sort Array](https://leetcode.com/problems/relative-sort-array/description/).

## Двоично и троично търсене

### Двоично търсене

Решете задачата [Скала](https://www.hackerrank.com/contests/daa-2021-2022-winter-1/challenges/challenge-2593/problem).

### Троично търсене

Използва се за намиране на екстремум на унимодални функции.

#### Задача 7

Решете [Спасителят на плажа](https://judge.openfmi.net/practice/get_problem_description?contest_id=198&problem_id=589).
