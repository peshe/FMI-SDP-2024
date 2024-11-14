#include <iostream>

bool word_search(const char *const *a, unsigned int m, unsigned int n, const std::string &word, size_t word_len_progress, int i, int j)
{
    if (word_len_progress == word.length())
        return true;

    if (i < 0 || i >= m || j < 0 || j >= n)
        return false;

    if (a[i][j] != word[word_len_progress])
        return false;

    return word_search(a, n, m, word, word_len_progress + 1, i + 1, j) ||
           word_search(a, n, m, word, word_len_progress + 1, i, j + 1) ||
           word_search(a, n, m, word, word_len_progress + 1, i - 1, j) ||
           word_search(a, n, m, word, word_len_progress + 1, i, j - 1);
}

bool word_search(const char *const *a, unsigned int m, unsigned int n, const std::string &word)
{
    return word_search(a, m, n, word, 0, 0, 0);
}

template <typename T>
void delete_2d_array(T **a, unsigned int m)
{
    for (unsigned int i = 0; i < m; i++)
        delete[] a[i];
}

int main()
{
    int m;
    std::cin >> m;
    if (!std::cin)
    {
        std::cerr << "error: input of number of array rows failed" << std::endl;
        return 1;
    }
    if (m < 0)
    {
        std::cerr << "error: number of array rows should be a natural number" << std::endl;
        return 2;
    }

    int n;
    std::cin >> n;
    if (!std::cin)
    {
        std::cerr << "error: input of number of array columns failed" << std::endl;
        return 1;
    }
    if (n < 0)
    {
        std::cerr << "error: number of array columns should be a natural number" << std::endl;
        return 2;
    }

    // XXX: вместо ръчна деалокация преди всеки `return`, за предпочитане е да се опакова върнатият указател в `std::unique_ptr` обект, който да гарантира, че паметта, заделена за масива, ще се освободи
    auto a = new char *[m];
    for (unsigned int i = 0; i < m; i++)
    {
        a[i] = new char[n];
        for (unsigned int j = 0; j < n; j++)
        {
            std::cin >> a[i][j];
            if (!std::cin)
            {
                std::cerr << "error: input of array element failed" << std::endl;
                delete_2d_array(a, m);
                return 3;
            }
        }
    }

    std::string word;
    std::cin >> word;
    if (!std::cin)
    {
        std::cerr << "error: input of word for searching in array failed" << std::endl;
        delete_2d_array(a, m);
        return 4;
    }

    std::cout << word_search(a, m, n, word) << std::endl;

    delete_2d_array(a, m);

    return 0;
}