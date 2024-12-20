
# Видове списъци

## 1. Кръгов Едносвързан Списък 
Кръгов едносвързан списък е тип едносвързан списък, при който последният елемент сочи към първия. 
Този тип структура се използва често за представяне на циклични процеси.

![](https://media.geeksforgeeks.org/wp-content/uploads/20240620113854/circular-linked-list-in-cpp.webp)

#### Задача (Домашно за упражнение)
Да се имплементират следните методи
1. **push_front** - Добавяне на елемент в началото 
2. **push_back** - Добавяне на елемент в края 
3. **pop_front** - Премахване на елемент от началото 
4. **pop_back** - Премахване на елемент от края 
5. **front** - Връщане на първия елемент
6. **back** - Връщане на последния елемент
7. **empty** - Проверка дали списъка е празен 


## 2. Двусвързан Списък (Doubly Linked List)
Двусвързан списък е структура от данни, при която всеки възел съдържа връзка както към следващия, така и към предишния възел.

![](https://www.askpython.com/wp-content/uploads/2021/03/doubly-linked-list-repr-3-1024x439.png.webp)

## Основни операции в двусвързан списък
1. **push_front** - Добавяне на елемент в началото 
2. **push_back** - Добавяне на елемент в края 
3. **push_аt** - Добавяне на елемент на конкретна позиция 
4. **pop_front** - Премахване на елемент от началото 
5. **pop_back** - Премахване на елемент от края 
6. **pop_аt** - Премахване на елемент от конкретна позиция 
7. **front** - Връщане на първия елемент
8. **back** - Връщане на последния елемент
9. **at** - Връщане на елемент на конкретна позиция
10. **empty** - Проверка дали списъка е празен


## Основни операции в едносвързан списък

| №  | Операция      | Име на операция                        | Сложност по време      |
|----|---------------|---------------------------------------|------------------------|
| 1  | push_front    | Добавяне на елемент в началото        | $O(1)$                   |
| 2  | push_back     | Добавяне на елемент в края            | $O(1)$               |
| 3  | push_at       | Добавяне на елемент на конкретна позиция | $O(n)$               |
| 4  | pop_front     | Премахване на елемент от началото     | $O(1)$                   |
| 5  | pop_back      | Премахване на елемент от края         | **$O(1)$**                   |
| 6  | pop_at        | Премахване на елемент от конкретна позиция | $O(n)$             |
| 7  | front         | Връщане на първия елемент             | $O(1)$                   |
| 8  | back          | Връщане на последния елемент          | $O(1)$                  |
| 9  | at            | Връщане на елемент на конкретна позиция | $O(n)$                |
| 10 | empty         | Проверка дали списъкът е празен       | $O(1)$                   |

#### Задача 
Напишете методите pop_at(size_t pos) и push_at(size_t pos)


## 3. Прескачащ Списък (Skip List)
Skip List е структура от данни, която надгражда стандартния свързан списък, като добавя допълнителни нива на връзки (или слоеве), за да ускори достъпа до елементите.

<br>

Skip List представлява йерархия от свързани списъци с няколко нива. В най-долното ниво има традиционен едносвързан списък, в който всички елементи се съдържат в последователен ред. По-горните нива са съкратени версии на долния списък и съдържат подмножества от елементите на нивото под тях.

#### 1. Търсене
>Търсенето започва от най-високото ниво на началния възел и прескача възли, докато не достигне възел с по-висока стойност от търсения елемент. След това алгоритъмът се премества на следващото по-ниско ниво и повтаря процеса, докато намери желания елемент или не достигне до възел, чрез който не можем да слезем на по-ниско ниво.

#### 2. Добавяне на елемент
>Когато нов елемент се добавя в такъв списък, генерираме случайна височина за новия възел. След това новият възел се добавя на всяко ниво до неговата максимална височина.

#### 3. Премахаване на елемент
>При изтриване на възел, той се премахва от всички нива, на които присъства, като отново се актуализират връзките между съседните възли на всяко засегнато ниво.



![](https://upload.wikimedia.org/wikipedia/commons/thumb/8/86/Skip_list.svg/1920px-Skip_list.svg.png)

|Операция| Среден случай (време) |Най-лош случай (време)| Допълнителна памет|
|-|-|-|-|
|Търсене на елемент| $O(log(n))$ | $O(n)$ | $O(1)$ |
|Добавяне на елемент| $O(log(n))$ | $O(n)$ | $O(1)$ |
|Изтриване на елемент| $O(log(n))$ | $O(n)$ | $O(1)$ |


## 4. Самоорганизиращ се Списък (Self-organizing List)
Самоорганизиращият се списък променя подредбата на елементите си въз основа на определени критерии, напр. честота на използване.

### Видове методи за самоорганизация
- **Преместване**:
> При използване елементът се премества в началото в началото на списъка. Елементите, които са достъпвани скоро се достъпват бързо.

- **Броене** : 
> Използването на всеки елемент увеличава брояч за текущия елемент. Списъкът се поддържа сортиран спрямо броя търсения на всеки елемент. Най-търсените са най-отпред.
 
- **Смяна**: 
> При използване елементът бива разменен с предишния си. По този начин след използването му той е на по-предна позиция в списъка.

## 5. Unrolled List
Unrolled list е структура, която разделя елементите в блокове, за да подобри ефективността при използване на паметта и бързината на достъп.

### Характеристики
- Всеки блок съдържа определен брой елементи, което намалява броя на указателите и оптимизира използването на паметта.
- Бързо добавяне и изтриване на елементи в различни блокове.

---

## Задачи за Двусвързан Списък

### Задача 1
Реализирайте метод за обръщане на двусвързан списък.

### Задача 2
Създайте функция, която премахва всички дублирани елементи от двусвързан списък.

### [Задача 3](https://leetcode.com/problems/design-browser-history/description/?envType=problem-list-v2&envId=doubly-linked-list)
Да се имплементира класс описващ история на браузър(да се пазят само адресите) с помощтта на двусвързан списък. Да се имплемнтират методите:
- visit(const string& url) 
- string back(int steps)
- string forward(int steps)

*Забележка: Искаме при посещение на сайт да не можем да се движим напред.* 


### Задача 4
Дадена е матрица с размери N и M. Използвайки структурата Node от двусвързан списък представете матрицата чрез списъци.
```
Пример:
Вход:
4 3 
1 2 3
4 5 6
7 8 9
0 5 3
Изход:
start
|
V
1 -> 2 -> 3 ->
|    |    |
V    V    V
4 -> 5 -> 6 ->
|    |    |
V    V    V
7 -> 8 -> 9 ->
|    |    |
V    V    V
0 -> 5 -> 3 ->
|    |    |
V    V    V
``` 

### [Задача 5](https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/description/?envType=problem-list-v2&envId=doubly-linked-list)
Даден ви двусвързан списък със следната структура на възли:
```cpp
struct Node{
    int val;
    Node* next, *prev, *down;
}
```
Тази структура ни позволява да създаване разклонения в списъка. По този начин възел от списъка може да сочи, както следващия възел, така и възел, който е начало на друг списък. Искаме да изравним списъка, така че той да стане линеен.
Пример:
```
Вход:

1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6
            |
            V
            7 <-> 8 <-> 9 <-> 10
                  |
                  V
                  11 <-> 12
Изход:
1 <-> 2 <-> 3 <-> 7 <-> 8 <-> 11 <-> 12 <-> 9 <-> 10 <-> 4 <-> 5 <-> 6


``` 

