#pragma once
#include <vector>
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
   

    /**
     * @struct Vec2f
     * @brief A 2D vector with `float` components.
     * @details Represents a 2D vector with `x` and `y` components, typically used for 2D geometry, positions, or directions.
     */
    
    struct Vec2f {
        float x; ///< The x-component of the vector.
        float y; ///< The y-component of the vector.
        
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
        inline friend float operator * (const Vec2f& A, float scalar) {
            return { A.x * scalar , A.y * scalar };
        }
    };

    /**
     * @struct Vec3f
     * @brief A 3D vector with `float` components.
     * @details Represents a 3D vector with `x`, `y`, and `z` components, commonly used for 3D geometry, positions, or directions.
     */
    struct Vec3f {
        float x; ///< The x-component of the vector.
        float y; ///< The y-component of the vector.
        float z; ///< The z-component of the vector.
    };

    /**
     * @struct Vec4f
     * @brief A 4D vector with `float` components.
     * @details Represents a 4D vector with `x`, `y`, `z`, and `w` components, often used for homogeneous coordinates, transformations, or color representations.
     */
    struct Vec4f {
        float x; ///< The x-component of the vector.
        float y; ///< The y-component of the vector.
        float z; ///< The z-component of the vector.
        float w; ///< The w-component of the vector.
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
        /**
         * @brief Gets a pointer to the constant matrix data.
         * @return A pointer to the constant matrix buffer.
         * @details Provides access to the raw matrix data buffer for read-only operations.
         */
        virtual const float* getConstBuffer() const noexcept = 0;

        /**
         * @brief Gets a pointer to the matrix data.
         * @return A pointer to the matrix buffer.
         * @details Provides access to the raw matrix data buffer for both read and write operations.
         */
        virtual float* getBuffer() const noexcept = 0;

        /**
         * @brief Accesses an element in the matrix by its row and column indices.
         * @param x The column index.
         * @param y The row index.
         * @return The matrix element at the specified position.
         */
        virtual float at(size_t x, size_t y) const = 0;

        /**
         * @brief Accesses an element in the matrix by its row and column indices (constant reference).
         * @param x The column index.
         * @param y The row index.
         * @return A constant reference to the matrix element at the specified position.
         */
        virtual float& constAt(size_t x, size_t y) const noexcept = 0;
    };

    /**
     * @class Matrix3f
     * @brief A 3x3 matrix of `float` values.
     * @details Implements the matrix interface for a 3x3 matrix, typically used for 2D transformations like rotation and scaling.
     */
    class Matrix3f : public Matrix<true, true, 3, 3> {
    public:
        virtual const float* getConstBuffer() const noexcept override;
        virtual float* getBuffer() const noexcept override;
        virtual float at(size_t x, size_t y) const override;
        virtual float& constAt(size_t x, size_t y) const noexcept override;
    };

    /**
     * @class Matrix2f
     * @brief A 2x2 matrix of `float` values.
     * @details Implements the matrix interface for a 2x2 matrix, often used in 2D geometric transformations.
     */
    class Matrix2f : public Matrix<true, true, 2, 2> {
    public:
        virtual const float* getConstBuffer() const noexcept override;
        virtual float* getBuffer() const noexcept override;
        virtual float at(size_t x, size_t y) const override;
        virtual float& constAt(size_t x, size_t y) const noexcept override;
    };

    /**
     * @class Matrix4f
     * @brief A 4x4 matrix of `float` values.
     * @details Implements the matrix interface for a 4x4 matrix, commonly used for 3D transformations, including scaling, translation, and rotation.
     */
    class Matrix4f : public Matrix<true, true, 4, 4> {
    public:
        virtual const float* getConstBuffer() const noexcept override;
        virtual float* getBuffer() const noexcept override;
        virtual float at(size_t x, size_t y) const override;
        virtual float& constAt(size_t x, size_t y) const noexcept override;
    };
}
