#include <stdexcept>  // for std::out_of_range
#include <vector>     // for std::vector
#include <array>      // for std::array
#include <type_traits> // for std::is_same

template<typename __Container, size_t __Dimension>
class VECTOR {
public:
    
    VECTOR() {
        if constexpr (std::is_same<__Container, std::vector<double>>::value) {
            this->m_buffer = create_vector(0.0);

        }
        else if constexpr (std::is_same<__Container, std::array<double, __Dimension>>::value) {
            this->m_buffer = create_array(0.0);
        }
        else {
            throw std::invalid_argument("The provided container type is not supported");
        }
    };

    VECTOR(const double * buffer) {
        if constexpr (std::is_same<__Container, std::vector<double>>::value) {
            this->m_buffer = create_vector(0.0);
            for (int i = 0; i < __Dimension; i++) {
                m_buffer.at(i) = buffer[i];
            }
        }
        else if constexpr (std::is_same<__Container, std::array<double, __Dimension>>::value) {
            this->m_buffer = create_array(0.0);
            for (int i = 0; i < __Dimension; i++) {
                m_buffer.at(i) = buffer[i];
            }
        }
        else {
            throw std::invalid_argument("The provided container type is not supported");
        }
    };
    explicit VECTOR(double default_value ) {
        if constexpr (std::is_same<__Container, std::vector<double>>::value) {
            this->m_buffer = create_vector(default_value);
            
        }
        else if constexpr (std::is_same<__Container, std::array<double, __Dimension>>::value) {
            this->m_buffer = create_array(default_value);
        }
        else {
            throw std::invalid_argument("The provided container type is not supported");
        }
    }

    ~VECTOR() = default;

    double& operator[](size_t index) {
        return this->m_buffer.at(index); 
    }

    const double& operator[](size_t index) const {
        return this->m_buffer.at(index);
    }

    const double* get_data() const noexcept {
        return this->m_buffer.data();
    }

    double* get_data() noexcept {
        return this->m_buffer.data();
    }

protected:
    __Container m_buffer;

private:
    // Helper functions
    static std::array<double, __Dimension> create_array(double value) {
        std::array<double, __Dimension> arr{};
        arr.fill(value); 
        return arr;
    }

    static std::vector<double> create_vector(double value) {
        return std::vector<double>(__Dimension, value); 
    }

    VECTOR(const VECTOR<__Container, __Dimension>&) = delete;
    VECTOR& operator=(const VECTOR<__Container, __Dimension>&) = delete;
};

template <size_t __Dimension>
using STATIC_VECTOR = VECTOR<std::array<double, __Dimension>, __Dimension>;

template <size_t __Dimension>
using HEAP_VECTOR = VECTOR<std::vector<double>, __Dimension>;
