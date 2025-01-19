#include <stdexcept>  // for std::out_of_range
#include <iostream>    // for debugging
#include "Vector.h"    // for VECTOR class

template <typename __Container, size_t N, size_t M>
class MATRIX {
public:
    MATRIX() {
        if constexpr (std::is_same<__Container, std::vector<double>>::value) {
            this->m_buffer = create_vector(0.0);
        }
        else if constexpr (std::is_same<__Container, std::array<double, M * N>>::value) {
            this->m_buffer = create_array(0.0);
        }
        else {
            throw std::invalid_argument("The provided container type is not supported");
        }
    };
    MATRIX(const double * buffer) {
        if constexpr (std::is_same<__Container, std::vector<double>>::value) {
            this->m_buffer = create_vector(0.0);
            for (int i = 0; i < M * N; i++) {
                m_buffer.at(i) = buffer[i];
            }
        }
        else if constexpr (std::is_same<__Container, std::array<double, M * N>>::value) {
            this->m_buffer = create_array(0.0);
            for (int i = 0; i < M * N; i++) {
                m_buffer.at(i) = buffer[i];
            }
        }
        else {
            throw std::invalid_argument("The provided container type is not supported");
        }
    };
    ~MATRIX() = default;

    double* operator[](size_t row_index) {
        if (row_index >= N) throw std::invalid_argument("Index out of bound");
        else return this->m_buffer.data() + row_index * M;
    }
    const double* operator[](size_t row_index) const {
        if (row_index >= N) throw std::invalid_argument("Index out of bound");
        else return this->m_buffer.data() + row_index * M;
    }
    double* get_data() noexcept{
        
        return this->m_buffer.data();
    }
    const double* get_data() const noexcept {
        return this->m_buffer.data();
    }
protected:
    __Container m_buffer;
private:

    // Helper function for std::vector
    static std::vector<double> create_vector(double default_value) {
        return std::vector<double>(N * M, default_value);
    }

    // Helper function for std::array
    static std::array<double, N * M> create_array(double value) {
        std::array<double, N * M> arr{};
        arr.fill(value);
        return arr;
    }

    MATRIX(const MATRIX< __Container,N, M>&) = delete;
    MATRIX& operator=(const MATRIX<__Container,N, M>&) = delete;
};



template <size_t __Rows , size_t __Columns>
using STATIC_MATRIX = MATRIX<std::array<double, __Rows * __Columns>, __Rows , __Columns>;

template <size_t __Rows, size_t __Columns>
using HEAP_MATRIX = MATRIX<std::vector<double>, __Rows , __Columns>;
