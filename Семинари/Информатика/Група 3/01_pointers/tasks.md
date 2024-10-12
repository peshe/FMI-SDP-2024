# Семинар СДП - седмица 1

## Указатели

Променлива, която съдържа в себеси адрес към друга променлива.

**Пример 1:** Да се напише функция, която пренасочва даден указател да сочи към подадена променлива. За улеснение, работете с цели числа.

Грешно решение:

```c++
#include<iostream>

// Грешката е тук: Подаваме указателя по стойност и се прави негово копие,
// което се променя локално, вместо да се промени самата стойност.
void redirect(int* ptr, int dest) {
    ptr = &dest;
}

int main() {
    int a = 10;
    int b = 12;
    int* ptr = &a;

    redirect(ptr, b);
    std::cout << *ptr << std::endl;
}
```

Ако подадем укателя по референция, копие няма да бъде направено. В случая искаме указател към указател:

```c++
void redirect(int** ptr, int& dest) {
    *ptr = &dest;
}
```

### Референции

Разлики спрямо указателите:

- Не могат да се пренасочват;
- Винаги сочат към нещо: За указателите имаме тип `nullptr`, който сочи към нищото;
- Имплицитно дереференциране.

```c++
void redirect(int*& ptr, int& dest) {
    ptr = &dest;
}
```

### Указатели и константи

- `const int*` -- Указател, който сочи към const int. Можем да пренасочваме, но не можем да променяме стойността; 
- `int const*` -- Еквивалентно на горното;
- `int * const` -- Константен указател: не можем да го пренасочваме, но можем да променяме стойността;
- `const int* const` -- Константен указател към константен int. Нито можем да пренасочваме нито да променяме стойността.

### Указатели към функции. Функции от по-висок ред

```c++
void myIntFunc(int x)
{
    std::cout << x << std::endl;
}
 
int main()
{
    void (*foo)(int);
    foo = &my_int_func;

    foo(2); // Можем да извикаме функцията нормално
    (*foo)(2); // Може и така, но не изглежда много добре
}
```

#### Подаване като параметър

```c++
int applyOperation(int (*op)(int, int),
                        int x, int y)
{
    return (*op)(x, y);
}

int add(int a, int b)
{
    return a + b;
}

int mult(int a, int b)
{
    return a * b;
}

int main()
{
    int (*addPtr)(int, int);
    addPtr = &add;

    int sum = applyOperation(addPtr, 1, 2) 
    int prod = applyOperation(mult, 1, 2)
}
```

## Темплейти

- Дават ни възможност да преизползваме код;
- Те са вид полиморфизъм;
- Да се внимава с разделната компилация.

### Примери

#### Функция

```cpp
template <typename Type>
Type add(Type lhs, Type rhs) {
    return lhs + rhs;
}

int main() {
    std::cout << add(5, 6) << std::endl;
    std::cout << add(5.8, 10) << std::endl;

    return 0;
}
```

#### Клас

```cpp
const size_t MAX_SIZE = 256;
template <typename Type>
class Container {
private:
    Type data[MAX_SIZE];
    size_t size;

public:
    Container() : size(0) {}

    Type get_at(size_t index) const {
        if(index < size)
            return data[index];
        throw std::out_of_range("Index is too large...");
    }

    void add(const Type&);
};

template <typename Type>
void Container<Type>::add(const Type& new_elem) {
    if(size == MAX_SIZE)
        throw std::out_of_range("There is not enough space!");
    data[size++] = new_elem;
}
```

### Конкретизиране на поведение

#### Функция

```cpp
template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

// Explicit specialization
template <>
int max(int a, int b) {
    return a + b;
}

// Partial specialization
template <typename T>
T* max(T* a, T* b) {
    return a > b ? a : b;
}
```

#### Клас

```cpp
template <>
class Container {
private:
    int data[MAX_SIZE];
    size_t size;

public:
    Container() : size(0) {}

    //int get_at(size_t index) - махаме функционалност
    //добавяме нова
    void display_at(size_t index) const
    {
        if(index < size)
            std::cout << data[index];
        throw std::out_of_range("Index is too large...");
    }

    void add(const Type&)
    {
        if(size == MAX_SIZE)
            throw std::out_of_range("There is not enough space!");
        data[size++] = new_elem;
    }
}
```

## Още задачи

### Задача 1

Да се напише функция, която приема като аргумент масив от цели числа, броя на
елементите и друга функция – `next(i)` (тя приема едно число и връща числото, което е с 3 по-
голямо от подаденото) и връща сумата на елементите, които се намират на индекси, които се получават чрез прилагане на `next` върху предишните индекси (в примера кратни
на `3`, индексите започват от `0`).

Реализирайте сами функцията next и я използвайте в другата функция!

$\sum_{i=0, next(i)}^{n} arr[i]$

### Задача 2

Имплементирайте функция `map`, която прилага подадена като аргумент функция върху всеки елемент на даден масив от цели числа;.

*Допълнение:*
Да се реализира и втори път като функция, която връща нов масив, вместо да променя елементите на стария.

### Задача 3

Да се напише функция `filter`, която приема като аргументи масив от цели числа, неговата
размерност и едноаргументен предикат, и връща нов масив с елементите от масива, отговарящи на предиката.
