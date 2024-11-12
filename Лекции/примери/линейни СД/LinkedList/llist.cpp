#include "llist.hpp"
#include <cassert>

/////////////////////////////////////////////////
// Simple tests for the list implementatio

void testPush()
{
     LList<int> test {1, 2};

     test.push_end(5);
     test.push_atPos(2, 3);
     test.push_atPos(3, 4);
     for (int i = 1;  i <= 5; i++) {
         assert(test.at(unsigned(i - 1)) == i);
     }

     bool flag = false;
     try {
         test.push_atPos(unsigned(-1), 0);
     } catch (const std::invalid_argument&) {
         flag = true;
     }
     assert(flag);

     LList<int>::iterator it = test.begin();
     ++it;
     test.push_after(it, 10);
     assert(test.size() == 6);
     assert(test.at(0) == 1 && test.at(1) == 2 && test.at(2) == 10 && test.at(3) == 3);

     test.push_after(test.begin(), 0);
     assert(test.front() == 1 && *(++test.begin()) == 0 && test.at(1) == 0);
}

void testPop(unsigned seed = 1)
{
    LList<int> test;
    bool flag = false;
    try {
        test.pop_atPos(0);
    } catch (const std::invalid_argument&) {
        flag = true;
    }

    assert(flag);

    flag = false;
    try {
        test.pop_atPos(1);
    } catch (const std::invalid_argument&) {
        flag = true;
    }

    assert(flag);

    srand(seed);
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++) {
        test.push_atPos(i, (int)i);
    }

    flag = false;
    try {
        for (size_t i = 0; i < testSz; i++) {
            test.pop_atPos(rand() % (testSz - i));
        }
    } catch (const std::invalid_argument&) {
        flag = true;
    }

    assert(flag || test.empty());
}

void testPos(unsigned seed = 1)
{
    LList<int> test;

    srand(seed);
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++) {
        test.push_atPos(i, rand() % testSz);
    }

    srand(seed);
    for (size_t i = 0; i < testSz; i++) {
        assert(rand() % testSz == (size_t)test.at(i));
    }

    bool flag = false;
    try {
        test.at(unsigned(-1));
    } catch (const std::invalid_argument&) {
        flag = true;
    }

    assert(flag);
}

void testCpy(unsigned seed = 1)
{
    LList<int> test;

    srand(seed);
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++) {
        test.push_atPos(i, rand() % testSz);
    }

    LList<int> testCpy(test);
    for (size_t i = 0; i < testSz; i++) {
        assert(testCpy.at(i) == test.at(i));
    }

    assert(testCpy.size() == test.size());

    LList<int> testOp = test;
    for (size_t i = 0; i < testSz; i++) {
        assert(testCpy.at(i) == test.at(i));
    }

    assert(testOp.size() == testOp.size());
}

void testReverse()
{
    LList<int> test;
    const size_t testSz = 100;
    for (size_t i = 0; i < testSz; i++) {
        test.push_front((int)i);
    }

    test.reverse();
    for (size_t i = 0; i < testSz; i++) {
        assert(test.at(0) == (int)i);
        test.pop_front();
    }
}

template <class DataType>
const DataType& print(const DataType& elem)
{
    std::cout << elem << " ";
    return elem;
}

void testSet(unsigned seed = 1)
{
    LList<int> test;
    const size_t testSz = 100;
    const size_t set_sz = 5;
    srand(seed);

    for (size_t i = 0; i < testSz; i++) {
        test.push_front(rand() % set_sz);
    }

    test.toSet();
    assert(test.size() <= 5);
    test.map(print<int>);
}

void testIsSorted(unsigned seed = 1)
{
    const size_t testSz = 100;
    const size_t set_sz = 5;
    srand(seed);

{
    LList<int> test1;
    for (size_t i = 0; i < testSz; ++i)
        test1.push_front((int)i);
    assert(test1.isSorted());
}

{
    LList<int> test2;
    for (size_t i = testSz; i > 0; --i)
        test2.push_front((int)i);
    assert(test2.isSorted());
}

{
    LList<int> test3;
    for (size_t i = set_sz; i > 0; --i)
        test3.push_front(0);

    for (size_t i = 0; i < testSz; ++i)
        test3.push_front((int)i);
    assert(test3.isSorted());
}

{
    LList<int> test4;
    for (size_t i = set_sz; i > 0; --i)
        test4.push_front(0);

    for (size_t i = testSz; i > 0; --i)
        test4.push_front((int)i);
    assert(!test4.isSorted());
}

{
    LList<int> test5;
    for (size_t i = 0; i < testSz; ++i)
        test5.push_front((int)i/4);
    assert(test5.isSorted());
}

{
    LList<int> test6;
    for (size_t i = 0; i < testSz; i++) {
        test6.push_front(rand() % set_sz);
    }
    assert(!test6.isSorted());
}
}

void testSort(unsigned seed = 1)
{
    const size_t testSz = 500;
    const size_t moduleSz = 2000;
    srand(seed);

{
    LList<int> test;

    for (size_t i = 0; i < testSz; i++) {
        test.push_front(rand() % moduleSz);
    }

    test.sort();
    assert(test.isSorted());

    test.reverse();
    assert(test.isSorted());
}

}

void testIterator()
{
    LList<int>test {1, 2, 3, 4, 5};

    int i = 1, sum = 0;
    for (const int & val : test) {
        assert (val == i);
        ++i;
        sum += val;
    }


    for (LList<int>::iterator it1 = test.begin(); it1 != test.end(); ++it1) {
        int innerSum = 0;

        LList<int>::iterator it2 = it1;
        while (it2) innerSum += *it2++;

        assert (innerSum == sum);
        sum -= *it1;
    }
}

void testMap()
{
    LList<int> test;
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++) {
        test.push_end((int)i);
    }

    test.map([](int& x){x *= 2;});

    for (size_t i = 0; i < testSz; i++) {
        assert(test.at(i) == (int)(2*i));
    }
    assert(test.back() == 198);

    test.push_front(0);
    test.push_end(200);
    assert(test.front() == 0);
    assert(test.back() == 200);
}

void testFilter()
{
    LList<int> test;
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++) {
        test.push_front((int)i);
    }

    test.filter([](int x){return x % 3;});

    assert(test.size() == 66);
    for (size_t i = 0; i < test.size(); i++) {
        assert(test.at(i)%3);
    }
    assert(test.back() == 1);

    test.push_front(0);
    test.push_end(200);
    assert(test.front() == 0);
    assert(test.back() == 200);
}

void testAppend()
{
    LList<int> list1{ 1, 2, 3, 4 };
    LList<int> list2{ 5, 6, 7, 8 };

    list1.append(list2);
    assert(list1.size() == 8);
    int pos = 0;
    for (int i : list1) {
        assert(i == pos + 1);
        ++pos;
    }

    list1.append({ 9, 10, 11, 12 });
    list1.map([](int el) {std::cout << el << " "; });
}


void makeTests()
{
    testPush();
    testPos();
    testPop();
    testCpy();
    testReverse();
    testSet();
    testIsSorted();
    testSort();
    testIterator();

    testAppend();

    testMap();
    testFilter();
}

int main ()
{
    makeTests();
    return 0;
}
