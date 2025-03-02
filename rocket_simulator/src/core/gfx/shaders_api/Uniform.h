#pragma once
namespace Core::Gfx::ShaderSystem {
   
    enum class UniformDataType : unsigned char {
        Unknown = 0b0000000,

        // Scalars
        Scalar = 0b0010000,
        Int = 0b0010001,
        Float = 0b0010010,
        Bool = 0b0010011,

        // Vectors
        Vector = 0b0100000,
        Vec2 = 0b0100001,
        Vec3 = 0b0100010,
        Vec4 = 0b0100011,
        IVec2 = 0b0100100,
        IVec3 = 0b0100101,
        IVec4 = 0b0100110,
        BVec2 = 0b0100111,
        BVec3 = 0b0101000,
        BVec4 = 0b0101001,

        // Matrices
        Matrix = 0b1000000,
        Mat2 = 0b1000001,
        Mat3 = 0b1000010,
        Mat4 = 0b1000011,

        // Samplers
        Sampler = 0b1100000,
        Sampler2D = 0b1100001,
        Sampler3D = 0b1100010,
        SamplerCube = 0b1100011
    };
    struct UniformField {
        size_t location;
        size_t size;
        UniformDataType type;
        std::string name;
    };
    
    enum class UniformResult {
        Success,        ///< The uniform was successfully uploaded.
        NotFound,       ///< The specified uniform field was not found.
        TypeMismatch,   ///< The uniform type did not match the expected type.
        InvalidState    ///< The uniform operation cannot be performed due to the current pipeline state.
    };

    template <typename T>
    class Uniform {
    public:
        Uniform<T>(const UniformField& field, const T* data);
        inline const std::string& getUniformName() const noexcept {
            return field.name;
        }
        inline UniformDataType getDataType() const noexcept {
            return field.type
        }
        inline size_t getUniformLocation() const noexcept {
            return field.location;
        }
        inline size_t getUniformSize() const noexcept {
            return field.size;
        }
        inline void setUniform(const T* value) {
            this->pData = value;
        }
     
    protected:
        UniformField field;
        const T* pData;
    };

}