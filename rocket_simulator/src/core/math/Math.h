#pragma once
#include <vector>
#include <array>
#include <cmath>
/**
 * @namespace Core::Math
 * @brief Defines mathematical structures and templates for vectors and matrices.
 */
namespace Core::Math {

    float Q_rsqrt(float number)
    {
        long i;
        float x2, y;
        const float threehalfs = 1.5F;

        x2 = number * 0.5F;
        y = number;
        i = *(long*)&y;                       // evil floating point bit level hacking
        i = 0x5f3759df - (i >> 1);               // what the fuck?
        y = *(float*)&i;
        y = y * (threehalfs - (x2 * y * y));   // 1st iteration
        //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

        return y;
    }
   
    struct Vec2f {
        float x; 
        float y; 
        
        inline float magnitude() const noexcept {
            return sqrtf(x * x + y * y);
        }

        inline Vec2f normalised() {
            float inverseMagnitude = Q_rsqrt(x * x + y * y);
            return Vec2f{ inverseMagnitude * x , inverseMagnitude * y };
        }
        
        inline friend Vec2f operator + (const Vec2f& A, const Vec2f& B) {
            return { A.x + B.x , A.y + B.y };
        }
        inline friend Vec2f operator - (const Vec2f& A, const Vec2f& B) {
            return { A.x - B.x , A.y - B.y };
        }
        inline friend Vec2f operator * (float scalar ,const Vec2f& A) {
            return { A.x * scalar , A.y  * scalar };
        }
        inline friend Vec2f operator * (const Vec2f& A, float scalar) {
            return { A.x * scalar , A.y * scalar };
        }
        inline friend float operator * (const Vec2f& A, const Vec2f& B) {
            return { A.x * B.x +  A.y * B.y};
        }
    };

    struct Vec3f {
        float x; 
        float y; 
        float z; 

        inline float magnitude() const noexcept {
            return sqrtf(x * x + y * y + z * z);
        }

        inline Vec3f normalised() {
            float inverseMagnitude = Q_rsqrt(x * x + y * y  + z*z);
            return Vec3f{ inverseMagnitude * x , inverseMagnitude * y , inverseMagnitude * z };
        }

        inline friend Vec3f operator + (const Vec3f& A, const Vec3f& B) {
            return { A.x + B.x , A.y + B.y  , A.z + B.z};
        }
        inline friend Vec3f operator - (const Vec3f& A, const Vec3f& B) {
            return { A.x - B.x , A.y - B.y  , A.z - B.z};
        }
        inline friend Vec3f operator * (float scalar, const Vec3f& A) {
            return { A.x * scalar , A.y * scalar , A.z * scalar };
        }
        inline friend Vec3f operator * (const Vec3f& A, float scalar) {
            return { A.x * scalar , A.y * scalar , A.z * scalar };
        }
        inline friend float operator * (const Vec3f& A, const Vec3f& B) {
            return { A.x * B.x + A.y * B.y  + A.z * B.z};
        }
    };

    struct Vec4f {
        float x;
        float y;
        float z;
        float w;
        inline float magnitude() const noexcept {
            return sqrtf(x * x + y * y + z * z + w*w);
        }

        inline Vec4f normalised() {
            float inverseMagnitude = Q_rsqrt(x * x + y * y + z * z + w * w);
            return Vec4f{ inverseMagnitude * x , inverseMagnitude * y , inverseMagnitude * z  , inverseMagnitude * w};
        }

        inline friend Vec4f operator + (const Vec4f& A, const Vec4f& B) {
            return { A.x + B.x , A.y + B.y  , A.z + B.z , A.w + B.w };
        }
        inline friend Vec4f operator - (const Vec4f& A, const Vec4f& B) {
            return { A.x - B.x , A.y - B.y  , A.z - B.z , A.w - B.w };
        }
        inline friend Vec4f operator * (float scalar, const Vec4f& A) {
            return { A.x * scalar , A.y * scalar , A.z * scalar , A.w * scalar };
        }
        inline friend Vec4f operator * (const Vec4f& A, float scalar) {
            return { A.x * scalar , A.y * scalar , A.z * scalar  , A.w * scalar};
        }
        inline friend float operator * (const Vec4f& A, const Vec4f& B) {
            return { A.x * B.x + A.y * B.y + A.z * B.z  + A.w * B.w};
        }
    };

    /**
     * @tparam static_alloc A flag indicating whether the matrix uses static memory allocation.
     * @tparam column_major A flag indicating whether the matrix is stored in column-major order.
     * @tparam width The number of columns in the matrix.
     * @tparam height The number of rows in the matrix.
     * @brief A templated base class for a matrix with customizable size and storage format.
     * @details Defines the common interface for all matrix types, with support for accessing and modifying matrix elements.
     */
    template <bool static_alloc, bool column_major, size_t width, size_t height>
    struct Matrix {
       
        virtual const float* getBuffer() const noexcept = 0;
        virtual size_t getCount() const noexcept;
        virtual float constAt(size_t x, size_t y) const = 0;
        virtual float& at(size_t x, size_t y) noexcept = 0;
    };
  
    class Matrix3f : public Matrix<true, true, 3, 3> {
    public:
        explicit Matrix3f();
        Matrix3f(const std::array<float, 9>& buffer);
        virtual const float* getBuffer() const noexcept override;
        virtual float constAt(size_t x, size_t y) const override;
        virtual float& at(size_t x, size_t y) noexcept override;
        virtual inline size_t getCount() const noexcept override {
            return 9;
        }
        friend Matrix3f operator + (const Matrix3f& A, const Matrix3f& B);
        //friend void operator + (Matrix3f& A, const Matrix3f& B);

        friend Matrix3f operator - (const Matrix3f& A, const Matrix3f& B);
        //friend void operator - (Matrix3f& A, const Matrix3f& B);

        friend Matrix3f operator * (const Matrix3f& A, float a);
        //friend void operator * (Matrix3f& A, float a);

        friend Matrix3f operator * (const Matrix3f& A, const Matrix3f& B);
        //friend void operator * (Matrix3f& A, const Matrix3f& B);

        friend Vec3f operator * (const Matrix3f& A, const Vec3f& b);
        //friend void operator * (const Matrix3f& A, Vec3f& b);

        friend Matrix3f operator * (const Vec3f& b, const Matrix3f& A);
        //friend void operator * (const Vec3f& b, Matrix3f& A);

        float determinant() const noexcept;
        
        Matrix3f transpose() const noexcept;
        Matrix3f getInverse() const;
        Vec3f getRow(int index)const;
        Vec3f getCol(int index)const;
    protected:
        std::array<float, 3 * 3> mBuffer;
    };
   
    class Matrix2f : public Matrix<true, true, 2, 2> {
    public:
        explicit Matrix2f();
        Matrix2f(const std::array<float, 4>& buffer);
       
        virtual const float* getBuffer() const noexcept override;
        virtual float constAt(size_t x, size_t y) const override;
        virtual float& at(size_t x, size_t y)  noexcept override;
        virtual inline size_t getCount() const noexcept override {
            return 4;
        }
        friend Matrix2f operator + (const Matrix2f& A, const Matrix2f& B);
        //friend void operator + (Matrix2f& A, const Matrix2f& B);

        friend Matrix2f operator - (const Matrix2f& A, const Matrix2f& B);
        //friend void operator - (Matrix2f& A, const Matrix2f& B);

        friend Matrix2f operator * (const Matrix2f& A, float a);
        //friend void operator * (Matrix2f& A, float a);

        friend Matrix2f operator * (const Matrix2f& A, const Matrix2f& B);
        //friend void operator * (Matrix2f& A, const Matrix2f& B);

        friend Vec2f operator * (const Matrix2f& A, const Vec2f& b);
        //friend void operator * (const Matrix2f& A, Vec2f& b);

        friend Matrix2f operator * (const Vec2f& b, const Matrix2f& A);
        //friend void operator * (const Vec2f& b, Matrix2f& A);

        float determinant() const noexcept;
        Matrix2f transpose() const noexcept;
        Matrix2f getInverse() const;
        Vec2f getRow(int index)const;
        Vec2f getCol(int index)const;
    protected:
        std::array<float, 4> mBuffer;
    };

    class Matrix4f : public Matrix<true, true, 4, 4> {
    public:
        explicit Matrix4f();
        Matrix4f(const std::array<float, 16>& buffer);
       
        virtual const float* getBuffer() const noexcept override;
        virtual float constAt(size_t x, size_t y) const override;
        virtual float& at(size_t x, size_t y) noexcept override;
        virtual inline size_t getCount() const noexcept override {
            return 16;
        }
        friend Matrix4f operator + (const Matrix4f& A, const Matrix4f& B);
        //friend void operator + (Matrix4f& A, const Matrix4f& B);

        friend Matrix4f operator - (const Matrix4f& A, const Matrix4f& B);
       // friend void operator - (Matrix4f& A, const Matrix4f& B);

        friend Matrix4f operator * (const Matrix4f& A, float a);
        //friend void operator * (Matrix4f& A, float a);

        friend Matrix4f operator * (const Matrix4f& A, const Matrix4f& B);
        //friend void operator * (Matrix4f& A, const Matrix4f& B);

        friend Vec4f operator * (const Matrix4f& A, const Vec4f& b);
        //friend void operator * (const Matrix4f& A, Vec4f& b);

        friend Matrix4f operator * (const Vec4f& b, const Matrix4f& A);
        //friend void operator * (const Vec4f& b, Matrix4f& A);

        float determinant() const noexcept;
        Matrix4f transpose() const noexcept;
        Matrix4f getInverse() const;
        Vec4f getRow(int index)const;
        Vec4f getCol(int index)const;
    protected:
        std::array<float, 16> mBuffer;
    };

    class Identity2 : public Matrix2f {
    public:
        Identity2();
    };
    class Identity3 : public Matrix3f {
    public:
        Identity3();
    };
    class Identity4 : public Matrix4f {
    public:
        Identity4();
    };

    class Rotation2D : public Matrix3f {
    public:
        Rotation2D(float angle);
        void   setAngle(float angle) noexcept;
    protected:
        float mAngle;
    };

    class ZAxisRotation3D : public Matrix4f {
    public:
        ZAxisRotation3D(float angle);
        void setAngle(float angle)  noexcept;
        inline float getAngle()const noexcept;
    protected:
        float mAngle;
    };
    class YAxisRotation3D : public Matrix4f {
    public:
        YAxisRotation3D(float angle);
        void setAngle(float angle)  noexcept;
        inline float getAngle()const noexcept;
    protected:
        float mAngle;
    };
    class XAxisRotation3D : public Matrix4f {
    public:
        XAxisRotation3D(float angle);
        void setAngle(float angle)  noexcept;
        inline float getAngle()const noexcept;
    protected:
        float mAngle;
    };

    class Translate2D : public Identity3 {
    public:
        Translate2D(float dx, float dy);
        float& getDx();
        float& getDy();
    };

    class Translate3D : public Identity4 {
    public:
        Translate3D(float dx, float dy, float dz);
        float& getDx();
        float& getDy();
        float& getDz();
    };
}
