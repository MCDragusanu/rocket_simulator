#include <stdexcept>  
#include <iostream>    
#include "Vector.h"    

template <typename ContainerType, size_t N, size_t M>
class Matrix {
public:
    explicit Matrix() {
        if constexpr (std::is_same<ContainerType, std::vector<double>>::value) {
            this->mBuffer = create_vector(0.0);
        }
        else if constexpr (std::is_same<ContainerType, std::array<double, M * N>>::value) {
            this->mBuffer = create_array(0.0);
        }
        else {
            throw std::invalid_argument("The provided container type is not supported");
        }
    };
    explicit Matrix(const double * buffer) {
        if constexpr (std::is_same<ContainerType, std::vector<double>>::value) {
            this->mBuffer = create_vector(0.0);
            for (int i = 0; i < M * N; i++) {
                mBuffer.at(i) = buffer[i];
            }
        }
        else if constexpr (std::is_same<ContainerType, std::array<double, M * N>>::value) {
            this->mBuffer = create_array(0.0);
            for (int i = 0; i < M * N; i++) {
                mBuffer.at(i) = buffer[i];
            }
        }
        else {
            throw std::invalid_argument("The provided container type is not supported");
        }
    };
    ~Matrix() = default;

    double* operator[](size_t row_index) {
        if (row_index >= N) throw std::invalid_argument("Index out of bound");
        else return this->mBuffer.data() + row_index * M;
    }
    const double* operator[](size_t row_index) const {
        if (row_index >= N) throw std::invalid_argument("Index out of bound");
        else return this->mBuffer.data() + row_index * M;
    }
    double* get_data() noexcept{
        
        return this->mBuffer.data();
    }
    const double* get_data() const noexcept {
        return this->mBuffer.data();
    }
protected:
    ContainerType mBuffer;
private:

    static std::vector<double> create_vector(double default_value) {
        return std::vector<double>(N * M, default_value);
    }

    static std::array<double, N * M> create_array(double value) {
        std::array<double, N * M> arr{};
        arr.fill(value);
        return arr;
    }

    Matrix(const Matrix< ContainerType,N, M>&) = delete;
    Matrix& operator=(const Matrix<ContainerType,N, M>&) = delete;
};



template <size_t N , size_t M>
using StaticMatrix = Matrix<std::array<double, N * M>, N , M>;

template <size_t N, size_t M>
using HeapMatrix = Matrix<std::vector<double>, N , M>;
