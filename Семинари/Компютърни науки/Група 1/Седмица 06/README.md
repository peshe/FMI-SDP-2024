# Едносвързан списък, имплементация, итератор и задачи.


Линейна структура от данни, състояща се от възли(node-ове), които са свързани помежду си чрез указатели. Както при масивите, имаме достъп до всички елементи, но разликата е, че този достъп ни е доста по-скъп.

## Основни операции в едносвързан списък
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
| 1  | push_front    | Добавяне на елемент в началото        | O(1)                   |
| 2  | push_back     | Добавяне на елемент в края            | O(1)               |
| 3  | push_at       | Добавяне на елемент на конкретна позиция | O(n)               |
| 4  | pop_front     | Премахване на елемент от началото     | O(1)                   |
| 5  | pop_back      | Премахване на елемент от края         | O(n)                   |
| 6  | pop_at        | Премахване на елемент от конкретна позиция | O(n)             |
| 7  | front         | Връщане на първия елемент             | O(1)                   |
| 8  | back          | Връщане на последния елемент          | O(1)                  |
| 9  | at            | Връщане на елемент на конкретна позиция | O(n)                |
| 10 | empty         | Проверка дали списъкът е празен       | O(1)                   |


## Примерна имплементация

```cpp
class List{
    struct Node{
        Node* next;
        int val;
        Node(int v,Node* n=nullptr):val(v), next(n){};
    };
    Node* head, tail;
    size_t size;
}
```

#### 1. push_front
```cpp
void push_front(int el){
    head = new Node(el, head);
    if(!tail)tail = head;
    size++;
}
```

#### 2. push_back
```cpp
void push_back(int el){
    if(!tail){
        push_front(ел);
        return;
    }
    tail->next = new Node(el, tail->next);
    tail = tail->next;
    size++;
}
```

#### 3. push_at
```cpp
void push_at(size_t index, int el){

    if(index > size)
        throw std::invalid_argument("Index out of range");

    if(index == 0)
        push_front(el);
    else if(index == size)
        push_back(el);
    else{
        Node* curr= head;
        for(int i = 0 ; i < index - 1; i++, curr = curr->next);
        curr->next = new Node(el, curr->next);
        size++;
    }
}
```

#### 4. pop_front
```cpp
    void pop_front(){
        pop_at(0);
    }
```


#### 5. pop_back
```cpp
void pop_back(){
    pop_at(size-1);
}
```

#### 6. pop_at
```cpp
void pop_at(size_t pos){
    if(empty())
        throw std::underflow_error("There are no elements in the list");
    if(pos >= size)
        throw std::underflow_error("Index out of range");

    Node* temp;
    if(pos == 0){
        temp = head;
        head = head->next;

        if(!head)
            tail = head;
        
    }
    else if(pos == size-1){
        Node* curr = head;
        while( curr->next != tail )
            curr = curr->next;

        curr->next = nullptr;
        temp = tail;
        tail = curr;
    }
    else{
        Node* curr = head;
        for(int i = 0; i < pos-1; i++)
            curr = curr->next;

        temp = curr->next;
        curr->next = curr->next->next;
    }

    delete temp;
    size--;
}
```

#### 7. front
```cpp
int front(){
    if(empty())
        throw std::invalid_argument("The list is empty");
    return head->val;
}
```

#### 8. back
```cpp
int back(){
    if(empty())
        throw std::invalid_argument("The list is empty");
    return tail->val;
}
```
 
#### 9. at
```cpp
int at(size_t pos){
    if(empty())
        throw std::invalid_argument("The list is empty");
    if(pos >= size)
        throw std::invalid_argument("Index out of range");
    
    if(pos == 0)return front(); 
    if(pos == size-1)return back(); 

    Node* curr = head;
    for(int i=0;i<pos;i++)
        curr = curr->next;
    return curr->val;
}
```

#### 10.  empty
```cpp
bool empty(){
    return !size;
}
```

## Итератор

Итератора в едносвързан списък няма как да бъде двупосочен, тъй като имаме достъп само напред. За разлика от другите структури досега итератора ни носи предимство при добваяне и махане на елементи от списъка, тъй като операциите с него стават константи, докато без него са линейни. Нека разгледаме примерна имплементация:


```cpp
class Iterator{
    Node* ptr;
    List& owner;
}

Iterator begin(){
    return Iterator(head, *this)
};
Iterator end(){
    return Iterator(nullptr, *this)
}

void push_After(int el, Iterator it){
    if(&it.owner != this)
        throw std::invalid_argument("Iterator is not from this list");
    if(it == end())
        throw std::invalid_argument("Cannot push elements past the end");
    it.ptr->next = new Node(el, it.ptr->next);
    if(tail == it.ptr)
        tail = it.ptr->next;
    size++;
}

void pop_After(int el, Iterator it){
    if(&it.owner != this)
        throw std::invalid_argument("Iterator is not from this list");
    if(it == end() || it.ptr == tail)
        throw std::invalid_argument("Cannot pop past the end");
    Node* temp = it.ptr->next;
    it.ptr->next = temp->next;
    if(temp == tail)
        tail = it.ptr;
    
    delete temp;
    size--;
}

```

*Забележка: Ако искаме методи PushAt или PopAt в итератора ще ни се наложи да пазим предишния елемент и винаги да достъпваме следващия. Това създава и проблем с имплементацията на списъка, тъй като по този начин няма да имаме достъп до първия елемент.*



## Задачи:

#### 1. Да се обърне едно свързан списък. На изход очакване указател към новото начало. 

*Забележка: на вход получавате само указател за началото*

Сложност по време: О(n)

Пример:
```
Вход:

head
 |
 V
 1 -> 2 -> 3 -> 4 -> 5

Изход:
                  head
                    |
                    V
1 <- 2 <- 3 <- 4 <- 5

```
*Може ли задачата да се реши чрез модифициране на първия списък за константна допълнителна памет?*

---

#### 2. Да се напише функция която получава начало на едносвързан списък и число k, и връща стойността на възела, който се намира на k-та позиция отзад напред.

Сложност по време : О(n)

Сложност по памет : О(1)

Пример:
```
Вход:
head
 |
 V
 1 -> 2 -> 3 -> 4 -> 5

 2 // k

 Изход:
 4

```

---

#### 3. Да се напише функция, която по дадено начало на списък и число k. Прави k ротации на списъка. Една ротация в списък премества последния елемент на първо място.

Сложност по време: O(n)

Сложност по памет: О(1)

Пример:

```
Вход:

head
 |
 V
 1 -> 2 -> 3 -> 4 -> 5

 3 // ротации

Изход:

head
 |
 V
 3 -> 4 -> 5 -> 1 -> 2
```   

---

#### 4. По подаденo начало на списък определете дали има цикъл в него.

Пример:

```
Вход:
head
 |
 v
 5 -> 1 -> 2
      ^    |
      |    v
      4 <- 3

Изход:
true

```

**Допълнение**

Как можем да намерим началото на този цикъл.

---

 #### 5. Напишете програма, която получава на вход 2 начала на списъци. Вашата програма трябва да върне указател към възела, в който се пресичат двата списъка. Ако такъв не съществува, да се върне nullptr. 

Сложност по време: О(n1 + n2)

Сложност по памет: O(1)

Пример:

```
Вход:

head1
  |
  v
  1 -> 2 -> 3
            |
            v
            4 -> 5 -> 6
            ^
            |
  7 -> 8 -> 9
  ^
  |
head2

Изход:
  1 -> 2 -> 3
            |
            v
  result -> 4 -> 5 -> 6
            ^
            |
  7 -> 8 -> 9

```
