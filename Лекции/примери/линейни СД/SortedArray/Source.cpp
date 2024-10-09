/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* A template class for sorted dynamic array.
* Illustrate the proxy design pattern
* and sample unit testing with GoogleTest framework
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/

#include "SortedArray.h"
using fmi::sdp::SortedArray;

// The unit test library
#include "gtest/gtest.h"

// A helper method to check if the array is really sorted
template<class D>
static bool isSorted(const SortedArray<D>& arr)
{
    for (size_t i = 0; i < arr.getSize() - 1; ++i) {
        if (arr[i + 1] < arr[i]) {
            return false;
        }
    }
    return true;
}


TEST(SortedArrayTest, TestAdd)
{
    SortedArray<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(5);

    // 1, 2, 5
    ASSERT_FALSE(arr.isEmpty());
    ASSERT_TRUE(isSorted(arr));
    ASSERT_EQ(arr[0], 1);
    ASSERT_EQ(arr[2], 5);

    arr += 0;
    // 0, 1, 2, 5
    ASSERT_EQ(arr[0], 0);
    ASSERT_TRUE(isSorted(arr));

    arr += 3;
    // 0, 1, 2, 3, 5
    ASSERT_EQ(arr[3], 3);
    ASSERT_TRUE(isSorted(arr));
    ASSERT_EQ(arr.getSize(), 5);
}


TEST(SortedArrayTest, TestFind)
{
    SortedArray<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);
    arr.add(5);
    arr.add(6);

    for (int i = 0; i < 6; ++i)
        ASSERT_EQ(arr.find(i+1), i);

    ASSERT_EQ(arr.find(0), -1);

    ASSERT_EQ(arr.find(8), -1);
    arr.add(8);
    ASSERT_EQ(arr.find(8), 6);

    ASSERT_EQ(arr.find(7), -1);
    arr.add(7);
    ASSERT_EQ(arr.find(7), 6);
    ASSERT_EQ(arr.find(8), 7);
}


TEST(SortedArrayTest, TestRemove)
{
    SortedArray<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);
    arr.add(5);
    arr.add(6);
    
    EXPECT_EQ(arr.find(1), 0);
    arr.remove(0);
    ASSERT_EQ(arr.find(1), -1);
    ASSERT_TRUE(isSorted(arr));
    ASSERT_EQ(arr.getSize(), 5);
    
    arr.remove(arr.find(4));
    ASSERT_EQ(arr.find(1), -1);
    ASSERT_TRUE(isSorted(arr));
    ASSERT_EQ(arr.getSize(), 4);

    arr.remove(arr.getSize() - 1);
    ASSERT_TRUE(isSorted(arr));
    ASSERT_EQ(arr.getSize(), 3);

    ASSERT_THROW(arr.remove(arr.getSize()), std::invalid_argument);
}


TEST(SortedArrayTest, TestEmpty)
{
    SortedArray<int> arr;
    ASSERT_TRUE(arr.isEmpty());

    arr.add(1);
    ASSERT_FALSE(arr.isEmpty());

    arr.remove(0);
    ASSERT_TRUE(arr.isEmpty());
}


TEST(SortedArrayTest, TestClear)
{
    SortedArray<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);

    EXPECT_FALSE(arr.isEmpty());
    EXPECT_NE(arr.getSize(), 0);
    arr.clear();
    ASSERT_TRUE(arr.isEmpty());
    ASSERT_EQ(arr.getSize(), 0);

    arr.add(5);
    ASSERT_FALSE(arr.isEmpty());
    ASSERT_EQ(arr.getSize(), 1);
    ASSERT_EQ(arr[0], 5);
}


TEST(SortedArrayTest, TestProxy)
{
    SortedArray<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);
    arr.add(5);
    arr.add(6);
    EXPECT_TRUE(isSorted(arr));
    
    // 1 2 3 4 5 6
    arr[0] = 0;
    // 0 2 3 4 5 6
    ASSERT_TRUE(isSorted(arr));
    ASSERT_EQ(arr[0], 0);

    arr[3] = 9;
    // 0 2 3 9 5 6 -> // 0 2 3 5 6 9
    ASSERT_TRUE(isSorted(arr));
    ASSERT_EQ(arr[5], 9);
    ASSERT_EQ(arr[3], 5);

    arr[5] = 0;
    ASSERT_TRUE(isSorted(arr));
    ASSERT_EQ(arr[5], 6);
    ASSERT_EQ(arr[0], 0);
    ASSERT_EQ(arr[1], 0);


    ASSERT_THROW((arr[10] == 9), std::invalid_argument);
    ASSERT_THROW((arr[-1] != 0), std::invalid_argument);

}


int main(int argc, char **argv)
{
    // A standard initialization approach
    testing::InitGoogleTest(&argc, argv);

    // Run all registered tests and print the result
    return RUN_ALL_TESTS();
}
