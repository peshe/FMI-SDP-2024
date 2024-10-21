#include <iostream>
#include <vector>
#include <string>

class CombinationIterator
{
    bool first;
    size_t n, k;
    size_t count;
    std::vector<size_t> indices;
    const std::string symbols;
    std::string result;

    void moveIndices();
    void updateResult(size_t index);

public:
    
    CombinationIterator(const std::string &characters, size_t combinationLength);
    
    const std::string &next();
    size_t generatedCount()const ;
    bool hasNext() const;
};

void CombinationIterator::moveIndices()
{
    size_t indexToMove = k - 1;
    while (indices[indexToMove] >= n - k + indexToMove)
        indexToMove--;
    indices[indexToMove]++;
    for (size_t i = indexToMove + 1; i < k; i++)
        indices[i] = indices[i - 1] + 1;
    updateResult(indexToMove);
}

void CombinationIterator::updateResult(size_t index)
{
    for (size_t i = index; i < k; i++)
        result[i] = symbols[indices[i]];
}

CombinationIterator::CombinationIterator(const std::string &characters, size_t length)
    : symbols(characters), k(length), n(characters.length()), indices(k, 0), result(k, ' ')
{
    if (k > n)
        throw std::invalid_argument("K can not be larger than N");
    if (!k)
        throw std::invalid_argument("K can not be 0");
    for (size_t i = 0; i < indices.size(); i++)
        indices[i] = i;
    first = true;
    count = 0;
    updateResult(0);
}

const std::string &CombinationIterator::next()
{
    if (!hasNext())
        throw std::out_of_range("There are no more combinations");
    if (first)
        first = false;
    else
        moveIndices();
    count++;
    return result;
}

size_t CombinationIterator::generatedCount()const
{
    return count;
}

bool CombinationIterator::hasNext() const
{
    return first || indices[0] < n - k;
};

int main()
{
    CombinationIterator it("abcdefghijklmnopqrstuvwxyz", 26);
    while (it.hasNext()){
        std::cout<<it.next()<<it.generatedCount()<<std::endl;
    }
}