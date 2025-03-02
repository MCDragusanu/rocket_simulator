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

    
    enum class UniformResult {
        Success,        ///< The uniform was successfully uploaded.
        NotFound,       ///< The specified uniform field was not found.
        TypeMismatch,   ///< The uniform type did not match the expected type.
        InvalidState    ///< The uniform operation cannot be performed due to the current pipeline state.
    };

    template <typename T>
    class Uniform {
        virtual const std::string& getUniformName() const noexcept;
        virtual UniformDataType getDataType() const noexcept;
        virtual size_t getUniformLocation() const noexcept;
        virtual size_t getUniformSize() const noexcept;
        virtual void setUniform(const T* value) = 0;
        virtual void uploadUniform() = 0; // abstract this to be platform independend 
    protected:
        std::string mName;
        size_t uniformLocation;
        size_t uniformSize;
        const T* pData;
    };


    class FloatUniform : public Uniform<float> {
    public:
        FloatUniform(const std::string& uniformName, size_t uniformLocation, float value);
        virtual void setUniform(const float* ptrFloat) override;
        virtual void uploadUniform() override;
    };

    class Matrix4fUniform : public Uniform<Core::Math::Matrix4f> {
        Matrix4fUniform(const std::string& uniformName, size_t uniformLocation, const Core::Math::Matrix4f* ptrMatrix);
        virtual void setUniform(const Core::Math::Matrix4f* ptrFloat) override;
        virtual void uploadUniform() override;
    };

    class Matrix3fUniform : public Uniform<Core::Math::Matrix3f> {
        Matrix3fUniform(const std::string& uniformName, size_t uniformLocation, const Core::Math::Matrix3f* ptrMatrix);
        virtual void setUniform(const Core::Math::Matrix3f* ptrFloat) override;
        virtual void uploadUniform() override;
    };
}