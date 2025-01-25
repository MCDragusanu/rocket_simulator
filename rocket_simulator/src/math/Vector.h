#include <stdexcept>  
#include <vector>     
#include <array>      
#include <type_traits> 

template<typename ContainerType, size_t width>
class Vector {
public:
    
   explicit Vector() {
        if constexpr (std::is_same<ContainerType, std::vector<double>>::value) {
            this->mBuffer = create_vector(0.0);

        }
        else if constexpr (std::is_same<ContainerType, std::array<double, width>>::value) {
            this->mBuffer = create_array(0.0);
        }
        else {
            throw std::invalid_argument("The provided container type is not supported");
        }
    };

   explicit Vector(const double * buffer) {
        if constexpr (std::is_same<ContainerType, std::vector<double>>::value) {
            this->mBuffer = create_vector(0.0);
            for (int i = 0; i < width; i++) {
                mBuffer.at(i) = buffer[i];
            }
        }
        else if constexpr (std::is_same<ContainerType, std::array<double, width>>::value) {
            this->mBuffer = create_array(0.0);
            for (int i = 0; i < width; i++) {
                mBuffer.at(i) = buffer[i];
            }
        }
        else {
            throw std::invalid_argument("The provided container type is not supported");
        }
    };
    explicit Vector(double default_value ) {
        if constexpr (std::is_same<ContainerType, std::vector<double>>::value) {
            this->mBuffer = create_vector(default_value);
            
        }
        else if constexpr (std::is_same<ContainerType, std::array<double, width>>::value) {
            this->mBuffer = create_array(default_value);
        }
        else {
            throw std::invalid_argument("The provided container type is not supported");
        }
    }

    ~Vector() = default;

    double& operator[](size_t index) {
        return this->mBuffer.at(index); 
    }

    const double& operator[](size_t index) const {
        return this->mBuffer.at(index);
    }

    const double* get_data() const noexcept {
        return this->mBuffer.data();
    }

    double* get_data() noexcept {
        return this->mBuffer.data();
    }

protected:
    ContainerType mBuffer;

private:
    // Helper functions
    static std::array<double, width> create_array(double value) {
        std::array<double, width> arr{};
        arr.fill(value); 
        return arr;
    }

    static std::vector<double> create_vector(double value) {
        return std::vector<double>(width, value);
    }

    Vector(const Vector<ContainerType, width>&) = delete;
    Vector& operator=(const Vector<ContainerType, width>&) = delete;
};

template <size_t width>
using StaticVector = Vector<std::array<double, width>, width>;

template <size_t width>
using HeapVector = Vector<std::vector<double>, width>;
