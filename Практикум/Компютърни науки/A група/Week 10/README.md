# Задачи

# Задача 1

Напишете програма, която проверява дали дадено дърво е:

- Двоично наредено
- Балансирано
  - почти идеално балансирано
  - идеално балансирано(перфектно)

Mожете да използвате дефиницията от следния [семинар](https://github.com/peshe/FMI-SDP-2024/tree/main/%D0%A1%D0%B5%D0%BC%D0%B8%D0%BD%D0%B0%D1%80%D0%B8/%D0%9A%D0%BE%D0%BC%D0%BF%D1%8E%D1%82%D1%8A%D1%80%D0%BD%D0%B8%20%D0%BD%D0%B0%D1%83%D0%BA%D0%B8/%D0%93%D1%80%D1%83%D0%BF%D0%B0%201/%D0%A1%D0%B5%D0%B4%D0%BC%D0%B8%D1%86%D0%B0%2011#%D0%B4%D0%B5%D1%84%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B8)

```
Вход:
         ┌──6
      ┌──7
      │  └──8
   ┌──10
   │  │  ┌──12
   │  └──13
   │     └──18
┌──19
│  │  ┌──25
│  └──37
│     └──39
48
│     ┌──53
│  ┌──54
│  │  └──59
└──65
   │  ┌──70
   └──71
      └──72
```

```
Изход:
BST: true
Perfect: false
Almost perfect: true
```

---

# Задача 2

Напишете програма, която намира **сумата на всички леви листа** в двоично дърво.

**Листов възел** е възел без деца. **Ляв листов възел** е възел, който е ляво дете на друг възел.

**Пример 1:**

```
Вход: root = [3,9,20,null,null,15,7]
Изход: 24
Обяснение: В дървото има два леви листови възла със стойности 9 и 15.
```

**Пример 2:**

```
Вход: root = [1]
Изход: 0
```

---

# Задача 3

Напишете програма, която намира **минималната дълбочина** на двоично дърво.

**Минималната дълбочина** е броят на възлите по най-краткия път от кореновия възел до най-близкия листов възел.

**Забележка:** Листов възел е възел без деца.

**Пример 1:**

```
Вход: root = [3,9,20,null,null,15,7]
Изход: 2
```

**Пример 2:**

```
Вход: root = [2,null,3,null,4,null,5,null,6]
Изход: 5
```

---

# Задача 4

Напишете програма, която по сортиран масив от числа създава балансирано двоично наредено дърво.

```
Вход:
7
6 7 8 10 12 13 18
```

```
Изход:
   ┌──6
┌──7
│  └──8
10
│  ┌──12
└──13
   └──18
```

---

# Задача 5

Напишете програма, която **създава и връща двоично дърво** по дадени два масива:

- `preorder`
- `inorder`

Програмата трябва да използва двата масива, за да реконструира оригиналното дърво.

**Пример 1:**

```
Вход: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Изход: [3,9,20,null,null,15,7]
```

**Пример 2:**

```
Вход: preorder = [-1], inorder = [-1]
Изход: [-1]
```

---

# Задача 6

Да се напише програма, която сериализира двоично наредено дърво във вектор и след това го десериализира от същия вектор.

Десериализираното дърво балансирано ли е?
Може ли да се имплементира такава десериализация, която да връща балансирано дърво?

---
