#include <iostream>
#include <vector>
#include <stdexcept>

typedef const std::vector<std::vector<int>> &VecMatrixConst;
typedef std::vector<std::vector<int>> VecMatrix;
typedef std::vector<int> MatrixRow;

class Matrix
{
private:
    int N, M;
    VecMatrix data;

    void validateMatrix(VecMatrixConst v)
    {
        if (v.empty()){
            throw std::invalid_argument("Empty matrix");
        }

        size_t size = v[0].size();
        if (size == 0){
            throw std::invalid_argument("Empty matrix row");
        }

        for (size_t i = 1; i < v.size(); i++){
            if (v[i].size() != size){
                throw std::invalid_argument("Inconsistent row sizes");
            }
        }

        N = v.size();
        M = size;
    }

    void allocate(size_t n, size_t m)
    {
        data.resize(n, MatrixRow(m));
    }

    void copy(VecMatrixConst other)
    {
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < M; j++)
                data[i][j] = other[i][j];
    }

    Matrix(size_t n, size_t m) : N(n), M(m)
    {
        allocate(N, M);
    }

public:
    Matrix(VecMatrixConst v)
    {
        validateMatrix(v);
        allocate(N, M);
        copy(v);
    }

    Matrix(const Matrix &other) : N(other.N), M(other.M)
    {
        allocate(N, M);
        copy(other.data);
    }

    Matrix operator+(const Matrix &other) const
    {
        if (N != other.N || M != other.M)
        {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }

        Matrix result(N, M);
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < M; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix &operator+=(const Matrix &other)
    {
        if (N != other.N || M != other.M){
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }

        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < M; j++)
                data[i][j] += other.data[i][j];
        
        return *this;
    }

    Matrix operator*(const Matrix &other) const
    {
        if (M != other.N){
            throw std::invalid_argument("Invalid dimensions for matrix multiplication");
        }

        Matrix result(N, other.M);
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < other.M; j++)
            {
                int sum = 0;
                for (size_t k = 0; k < M; k++)
                {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    Matrix operator*(int scalar) const
    {
        Matrix result(*this);
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < M; j++)
            {
                result.data[i][j] *= scalar;
            }
        }
        return result;
    }

    Matrix &operator*=(int scalar)
    {
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < M; j++)
            {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }

    void print() const
    {
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < M; j++)
            {
                std::cout << data[i][j] << ' ';
            }
            std::cout << "\n";
        }
        std::cout<<"\n";
    }


    friend Matrix operator*(int scalar, const Matrix &rhs);
};

Matrix operator*(int scalar, const Matrix &rhs)
{
    return rhs * scalar;
}

int main()
{
    Matrix m1({{1, 2, 3, 5},
               {4, 5, 6, 7},
               {7, 8, 9, 15}});
    Matrix m2({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10,11,12}
        });
    (m2*m1).print();
    m1.print();
    m1+=m1;
    m1.print();
}