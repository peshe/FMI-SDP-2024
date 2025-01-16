#include <iostream>
#include <climits>

const int DEFAULT_CAPACITY = 10;
class Heap
{
    private:
        int* arr;
        int size;
        int capacity;

        void free()
        {
            delete[] arr;
        }
        void copy(const Heap& other)
        {
            size = other.size;
            capacity = other.capacity;
            arr = new int[capacity];
            for(int i = 0; i < size; i++)
            {
                arr[i] = other.arr[i];
            }
        }
        int parrent(int index)
        {
            return (index - 1) / 2;
        }
        int left(int index)
        {
            return (index * 2) + 1;
        }
        int right(int index)
        {
            return (index * 2) + 2;
        }
        void heapify(int index)
        {
            int maximum = index;
            if(left(index) < size && arr[left(index)] > arr[maximum])
            {
                maximum = left(index);
            }
            if(right(index) < size && arr[right(index)] > arr[maximum])
            {
                maximum = right(index);
            }
            if(index != maximum)
            {
                std::swap(arr[index], arr[maximum]);
                heapify(maximum);
            }


        }

    public:
        Heap()
        {
            size = 0;
            capacity = DEFAULT_CAPACITY;
            arr = new int[capacity];
        } 
        ~Heap()
        {
            free();
        }
        Heap(const Heap& other)
        {
            copy(other);
        }
        Heap& operator=(const Heap& other)
        {
            if(this != &other)
            {
                free();
                copy(other);
            }
            return *this;
        }
        int getMax()
        {
            return arr[0];
        }
        void deleteMax()
        {
            std::swap(arr[0], arr[size - 1]);
            size--;
            heapify(0);
        }
        void push(int element)
        {
            if(size == capacity)
            {
                capacity *= 2;
                int *tmp = new int[capacity];
                for(int i = 0; i < size; i++)
                {
                    tmp[i] = arr[i];
                }
                delete[] arr;
                arr = tmp;
            }
            arr[size++] = element;
            int i = size - 1;
            while(i != 0 && arr[parrent(i)] < arr[i])
            {
                std::swap(arr[i],arr[parrent(i)]); 
                i = parrent(i);
            }
        }
        void increaseKey(int index, int value)
        {
            if(arr[index] < value)
            {
                arr[index] = value;
                int i = index;
                while(i != 0 && arr[parrent(i)] < arr[i])
                {
                    std::swap(arr[i],arr[parrent(i)]); 
                    i = parrent(i);
                }
            }

        }

        void deleteKey(int index)
        {
            increaseKey(index, INT_MAX);
            deleteMax();
        }

        void printHeap()
        {
            for(int i = 0; i < size; i++)
            {
                std::cout << arr[i] << std::endl;
            }
        }


};

int main()
{
    Heap hp;
    int n;
    int element;
    std::cin >> n;
    for(int i = 0; i < n; i++)
    {
        std::cin >> element;
        hp.push(element);
    }
    hp.printHeap();
}