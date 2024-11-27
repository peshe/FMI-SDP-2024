
# Двочни Дървета

## Дефиниции

**Двоично дърво** 
: Дърво с разклоненост 2

**Наредено дърво** 
: Дърво, при което има някаква зависимост между стойностите във върховете и структурата на дървото. 


Двоичните наредени дървета(BST) са структура от данни, която използваме за да поддържаме някаква подредба на стойностите в дървото. 

## Операции в двоично наредено дърво

Тук `n` е броя елементи в дървото, а `h` е височината на дървото.

|Операция|Сложност по време|
|-|:-:|
|Търсене в дърво|$О(h)$|
|Добавяне на елемент|$О(h)$|
|Премахване на елемент|$О(h)$|
|Извличане на всички елементи в сортиран вид|$О(n)$|

Структурата използва $O(n)$ памет за съхранение.


## Приложения
Основнито приложение на двоичните наредени дървета е търсене и сортиране на данни в динамична колекция.

## Имплементация

```cpp 
class BST{
    struct Node
    {
        DataType val;
        Node* left, * right;

        Node(int el, Node* l = nullptr, Node* r = nullptr)
            : val(el)
            , left(l)
            , right(r)
        {}
    } *root;

    Node* copy(Node* curr){
        if(!curr)return nullptr;
        return new Node(curr->val, copy(curr->left), copy(curr->right));
    }
    void free(Node* curr){
        if(!curr)return;
        free(curr->left);
        free(curr->right);
        delete curr;
    }
    public:

    BST():root(nullptr){};
    BST(const BST& other){
        root = copy(other.root);
    };
    BST(BST&& other){
        swap(root,other.root);
    }
    BST& operator=(const BST& other){
        if(&other != this){
            free(root);
            copy(other.root);
        }
        return *this;
    }
    BST& operator=(BST&& other){
        if(&other != this){
            swap(root, other.root);
        }
        return *this;
    }
    ~BST(){
        free(root);
    }

};
```

## Имплементация на операции
```cpp

class BST{
    private:
    Node* getMin(Node* curr){   
        if(!curr)return curr;
        return curr->left ? getMin(curr->left) : curr;
    }

    Node* extractMin(Node*& curr){
        if(!curr)return curr;
        if(curr->left)return extractMin(curr->left);   
        else{
            Node* detach=curr;
            curr = curr->right;
            return detach;
        }

    }

    void insertRec(Node*& curr, int el){
        if(!curr)curr = new Node(el);
        else insertRec((curr->val < el ? curr->right : curr->left),el); 
    }
    bool searchRec(Node* curr, int el)const{
        if(!curr)return false;
        if(curr->val == el) return true;
        return searchRec( (curr->val < el ? curr->right : curr->left) , el)
    };
    void removeRec(Node*& curr, int el){
        if(!curr)return;
        Node* toDelete; 
        if(curr->val==el){
            if(!curr->left && !curr->right){
                toDelete = curr;
                curr = nullptr;
            }
            else if(!curr->left){
                toDelete = curr;
                curr = curr->right;
            }
            else if(!curr->right){
                toDelete = curr;
                curr = curr->left;
            }
            else{
                Node* newCurr = extractMin(curr->right);
                newCurr -> left = curr->left;
                newCurr -> right = curr->right;
                toDelete = curr;
                curr = newCurr;
            }
            delete toDelete;
        }
        else removeRec((curr->val < el ? curr->right : curr->left),el);
    }

    public:

    void insert(int val){
        insertRec(root,val);
    };
    bool search(int val)const{
        return searchRec(root,val);
    };
    void remove(int val){
        removeRec(root,val);
    };
}
```

## Задачи
1. Да се имаплементира итератор в класа на дървото с възможност за движение в двете посоки.
2. По дадено двоично наредено дърво и цяло число X. Да се отговори на въпросите:
   1.  Съществуват ли два различни върха в дървото, така че тяхната сума да е равна на X.
   2.  Дали дървото е симетрично. Наричаме едно дърво симетрично, когато дървото съвпада със своето огледално дърво. Огледално дърво на дървото T e дърво, при което за всеки връх в T левия наследник е разменен на десния. 
   3.  