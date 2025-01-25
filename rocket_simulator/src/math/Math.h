#pragma once
#include <array>
#include <cmath>
#include <immintrin.h>
#include <random>
#include "Matrix.h"


#define E_CONST 2.718281828459045 
#define PI_CONST 3.141592653589793 
#define EPS_CONST 1e-6

#define to_radians(angle) ((angle / 360.0) * PI_CONST) 
#define to_angle(radian) (radian * (180.0 / PI_CONST))

namespace Math {

    // Adds two static vectors(left += right)
    template <size_t N>
    void add_vector_to_left(StaticVector<N>&left, const StaticVector<N>&right) {
        for (size_t i = 0; i < N; ++i) {
            left[i] += right[i];
        }
    }

    // Subtracts two static vectors (left -= right)
    template <size_t N>
    void subtract_vector_from_left(StaticVector<N>& left, const StaticVector<N>& right) {
        for (size_t i = 0; i < N; ++i) {
            left[i] -= right[i];
        }
    }

    // Computes the dot product of two static vectors.
    template <size_t N>
    double dot_product(const StaticVector<N>& left, const StaticVector<N>& right) {
        double result = 0.0;
        for (size_t i = 0; i < N; ++i) {
            result += left[i] * right[i];
        }
        return result;
    }

    // Multiplies two static matrices (result = left * right)
    template <size_t N, size_t M>
    void multiply_matrix(StaticMatrix<N, M>& result, const StaticMatrix<N, M>& left, const StaticMatrix<N, M>& right) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result[i][j] = 0.0;
                for (size_t k = 0; k < M; ++k) {
                    result[i][j] += left[i][k] * right[k][j];
                }
            }
        }
    }

    // Adds two static matrices (left += right)
    template <size_t N, size_t M>
    void add_matrix_to_left(StaticMatrix<N, M>& left, const StaticMatrix<N, M>& right) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                left[i][j] += right[i][j];
            }
        }
    }

    // Subtracts two static matrices (left -= right)
    template <size_t N, size_t M>
    void subtract_matrix_from_left(StaticMatrix<N, M>& left, const StaticMatrix<N, M>& right) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                left[i][j] -= right[i][j];
            }
        }
    }

    // Adds two heap vectors (left += right)
    template <size_t N>
    void add_vector_to_left(HeapVector<N>& left, const HeapVector<N>& right) {
        for (size_t i = 0; i < N; ++i) {
            left[i] += right[i];
        }
    }

    // Subtracts two heap vectors (left -= right)
    template <size_t N>
    void subtract_vector_from_left(HeapVector<N>& left, const HeapVector<N>& right) {
        for (size_t i = 0; i < N; ++i) {
            left[i] -= right[i];
        }
    }

    // Computes the dot product of two heap vectors.
    template <size_t N>
    double dot_product(const HeapVector<N>& left, const HeapVector<N>& right) {
        double result = 0.0;
        for (size_t i = 0; i < N; ++i) {
            result += left[i] * right[i];
        }
        return result;
    }

    // Multiplies two heap matrices (result = left * right)
    template <size_t N, size_t M>
    void mul(HeapMatrix<N, M>& result, const HeapMatrix<N, M>& left, const HeapMatrix<N, M>& right) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result[i][j] = 0.0;
                for (size_t k = 0; k < M; ++k) {
                    result[i][j] += left[i][k] * right[k][j];
                }
            }
        }
    }
    template <size_t N, size_t M>
    void mul(StaticMatrix<N, M>& result, const StaticMatrix<N, M>& left, const StaticMatrix<N, M>& right) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                result[i][j] = 0.0;
                for (size_t k = 0; k < M; ++k) {
                    result[i][j] += left[i][k] * right[k][j];
                }
            }
        }
    }
    // Multiplies a matrix by a vector (M × v).
    template< size_t M, size_t N>
    void mul(StaticVector<M>& result, const StaticMatrix<M, N>& mat, const StaticVector<N>& vec) {
        for (size_t i = 0; i < M; ++i) {
            result[i] = 0.0;
            for (size_t j = 0; j < N; ++j) {
                result[i] += mat[i][j] * vec[j];
            }
        }
    }

    // Multiplies a matrix by a vector (M × v).
    template< size_t M, size_t N>
    void mul(HeapVector<M>& result, const HeapMatrix<M, N>& mat, const HeapVector<N>& vec) {
        for (size_t i = 0; i < M; ++i) {
            result[i] = 0.0;
            for (size_t j = 0; j < N; ++j) {
                result[i] += mat[i][j] * vec[j];
            }
        }
    }

    // Computes the outer product of two vectors (v × vT).
    template<typename ContainerType, size_t N>
    void outer_product(Matrix<ContainerType, N, N>& result, const Vector<ContainerType, N>& vec1, const Vector<ContainerType, N>& vec2) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                result[i][j] = vec1[i] * vec2[j];
            }
        }
    }

    // Adds two heap matrices (left += right)
    template <size_t N, size_t M>
    void add_matrix_to_left(HeapMatrix<N, M>& left, const HeapMatrix<N, M>& right) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                left[i][j] += right[i][j];
            }
        }
    }

    // Subtracts two heap matrices (left -= right)
    template <size_t N, size_t M>
    void subtract_matrix_from_left(HeapMatrix<N, M>& left, const HeapMatrix<N, M>& right) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                left[i][j] -= right[i][j];
            }
        }
    }

    

    // Linear transformation (y = A * x + b)
    template<size_t N, size_t M>
    void linear_transform(StaticVector< N>& y, const StaticMatrix<N, M>& A, const StaticVector< M>& x, const StaticVector<N>& b) {
        mul(y, A, x);
        add_vector_to_left(y, b);
    }
    // Linear transformation (y = A * x + b)
    template<size_t N, size_t M>
    void linear_transform(HeapVector< N>& y, const HeapMatrix<N, M>& A, const HeapVector< M>& x, const HeapVector<N>& b){
        mul(y, A, x);
        add_vector_to_left(y, b);
    }

    // Creates an orthographic projection matrix
    void orthographic(StaticMatrix<4, 4>& result, double left, double right, double bottom, double top, double near_v, double far_v) {
        result[0][0] = 2.0 / (right - left);
        result[1][1] = 2.0 / (top - bottom);
        result[2][2] = -2.0 / (far_v - near_v);
        result[3][3] = 1.0;
        result[3][0] = -(right + left) / (right - left);
        result[3][1] = -(top + bottom) / (top - bottom);
        result[3][2] = -(far_v + near_v) / (far_v - near_v);
    }

    void orthographic(HeapMatrix< 4, 4>& result, double left, double right, double bottom, double top, double near_v, double far_v) {
        result[0][0] = 2.0 / (right - left);
        result[1][1] = 2.0 / (top - bottom);
        result[2][2] = -2.0 / (far_v - near_v);
        result[3][3] = 1.0;
        result[3][0] = -(right + left) / (right - left);
        result[3][1] = -(top + bottom) / (top - bottom);
        result[3][2] = -(far_v + near_v) / (far_v - near_v);
    }

    // Creates a perspective projection matrix
    void perspective(StaticMatrix< 4, 4>& result, double fov, double aspect_ratio, double n, double f) {
        double tan_half_fov = std::tan(to_radians(fov) / 2.0);
        result[0][0] = 1.0 / (aspect_ratio * tan_half_fov);
        result[1][1] = 1.0 / tan_half_fov;
        result[2][2] = -(n + f) / (f - n);
        result[2][3] = -1.0;
        result[3][2] = -(2.0 * f * n) / (f - n);
    }

    // Creates a perspective projection matrix
    
    void perspective(HeapMatrix<4, 4>& result, double fov, double aspect_ratio, double n, double f) {
        double tan_half_fov = std::tan(to_radians(fov) / 2.0);
        result[0][0] = 1.0 / (aspect_ratio * tan_half_fov);
        result[1][1] = 1.0 / tan_half_fov;
        result[2][2] = -(n + f) / (f - n);
        result[2][3] = -1.0;
        result[3][2] = -(2.0 * f * n) / (f - n);
    }

    // Generates an identity matrix
    template<size_t N>
    void identity(StaticMatrix<N, N>& result) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                result[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }
    template<size_t N>
    void identity(HeapMatrix<N, N>& result) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                result[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }

    // Generates a random vector
    template<size_t N>
    void generate_random_vector(StaticVector<N>& vec) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-100.0, 100.0);
        for (size_t i = 0; i < N; ++i) {
            vec[i] = dis(gen);
        }
    }
    template<size_t N>
    void generate_random_vector(HeapVector<N>& vec) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-100.0, 100.0);
        for (size_t i = 0; i < N; ++i) {
            vec[i] = dis(gen);
        }
    }

    // Generates a random matrix
    template<size_t N, size_t M>
    void generate_random_matrix(StaticMatrix<M, N>& mat) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-100.0, 100.0);
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] = dis(gen);
            }
        }
    }
    
    template<size_t N, size_t M>
    void generate_random_matrix(HeapMatrix<M, N>& mat) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-100.0, 100.0);
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] = dis(gen);
            }
        }
    }

    template<size_t N , size_t M>
    void lin_sys_solver(StaticVector<M>& x, const StaticMatrix<N, M>& A, const StaticVector<N>& y) {
        
        size_t row_index = 0;
        auto copy_x = StaticVector<M>(x.get_data());
        auto copy_A = StaticMatrix<N, M>(A.get_data());
        auto copy_y = StaticVector<N>(y.get_data());

        //triunghiularizare sup matrice A
        for (; row_index < N; row_index++) {
             //impart linia y la A[i][i] daca A[i][i] != 1
            double Aii= A[row_index][row_index];

            if (std::fabs(Aii - 0.0) < EPS_CONST) {
                for (int i = 0; i < N; i++) {
                    x[i] = copy_x[i];
                }
                Logger::get_instance().logError("SYSTEM Has no-unique solution");
                return;
            }

            if (std::fabs(Aii -1.0) > EPS_CONST) {
                for (int i = row_index; i < N; ++i) {
                    copy_A[row_index][i] /= Aii;
                }
                copy_y[row_index] /= Aii;
            }

            //formez 0 sub elementul de pe diagonala principala
            for (size_t i = row_index + 1; i < N; i++) {
                
                double coeff = -1.0 / (A[i][row_index]); // -1/Aij

                for (size_t j = row_index + 1; j < M; j++) {
                    copy_A[i][j] += (A[row_index][j] * coeff);
                }

                copy_y[i] += (y[row_index] * coeff);  // Calculez Yi
            }
        }

        x[N-1] = copy_y[N - 1] / copy_A[N - 1][M - 1];

        for (int k = N - 2; k >= 0; k--) {
            double sum = 0;
            
            //            M
            //Xk = (Yk - E  Aki * Xi ) * 1 / Akk
            //            i = k

            for (int i = k +1; i < M; i++) {
                sum += copy_A[k][i] * x[i];
            }
            x[k] = (y[k] - sum) * (1 / copy_A[k][k]);
        }


    }
    
    template<size_t N, size_t M>
    void lin_sys_solver(HeapVector<M>& x, const HeapMatrix<N, M>& A, const HeapVector<N>& y) {

        size_t row_index = 0;
        auto copy_x = HeapVector<M>(x.get_data());
        auto copy_A = HeapMatrix<N , M>(A.get_data());
        auto copy_y = HeapVector<N>(y.get_data());
       
        //triunghiularizare sup matrice A
        for (; row_index < N; row_index++) {
            //impart linia y la A[i][i] daca A[i][i] != 1
            double Aii = A[row_index][row_index];

            if (std::fabs(Aii - 0.0) < EPS_CONST) {
                for (int i = 0; i < N; i++) {
                    x[i] = copy_x[i];
                }
                Logger::get_instance().logError(L"SYSTEM Has no-unique solution");
                return;
            }

            if (std::fabs(Aii - 1.0) > EPS_CONST) {
                for (int i = row_index; i < N; ++i) {
                    copy_A[row_index][i] /= Aii;
                }
                copy_y[row_index] /= Aii;
            }
            //formez 0 sub elementul de pe diagonala principala
            for (size_t i = row_index + 1; i < N; i++) {

                double coeff = -1.0 / (A[i][row_index]); // -1/Aij

                for (size_t j = row_index + 1; j < M; j++) {
                    copy_A[i][j] += (A[row_index][j] * coeff);
                }

                copy_y[i] += (y[row_index] * coeff);  // Calculez Yi
            }
        }

        x[N - 1] = copy_y[N - 1] / copy_A[N - 1][M - 1];

        for (int k = N - 2; k >= 0; k--) {
            double sum = 0;

            //            M
            //Xk = (Yk - E  Aki * Xi ) * 1 / Akk
            //            i = k

            for (int i = k + 1; i < M; i++) {
                sum += copy_A[k][i] * x[i];
            }
            x[k] = (y[k] - sum) * (1 / copy_A[k][k]);
        }


    }
    
    template<size_t N, size_t M>
    void lin_sys_solver_inplace(StaticVector<M>& x, StaticMatrix<N, M>& A, StaticVector<N>& y) {
        size_t row_index = 0;

        //triunghiularizare sup matrice A
        for (; row_index < N; row_index++) {
            
            
            double Aii = A[row_index][row_index];

            if (std::fabs(Aii - 0.0) < EPS_CONST) {
                Logger::get_instance().logError(L"SYSTEM Has no-unique solution");
                return;
            }
            //impart linia y la A[i][i] daca A[i][i] != 1
            if (std::fabs(Aii - 1.0) > EPS_CONST) {
                for (size_t i = row_index; i < N; ++i) {
                    A[row_index][i] /= Aii;
                }
                y[row_index] /= Aii;
            }

            //formez 0 sub elementul de pe diagonala principala
            for (size_t i = row_index + 1; i < N; i++) {
                double coeff = -1.0 / A[i][row_index]; 

                for (size_t j = row_index + 1; j < M; j++) {
                    A[i][j] += A[row_index][j] * coeff;
                }

                y[i] += y[row_index] * coeff;
            }
        }
       
       
        x[N - 1] = y[N - 1] / A[N - 1][M - 1];

        for (int k = N - 2; k >= 0; k--) {
            double sum = 0;

            
            for (int i = k + 1; i < M; i++) {
                sum += A[k][i] * x[i];
            }
          
        //            M
        //Xk = (Yk - E  Aki * Xi ) * 1 / Akk
        //            i = k
        // 
         x[k] = (y[k] - sum) * (1 / A[k][k]); 
        }
    }
   
    template<size_t N, size_t M>
    void lin_sys_solver_inplace(HeapVector<M>& x, HeapMatrix<N, M>& A, HeapVector<N>& y) {
        size_t row_index = 0;

        //triunghiularizare sup matrice A
        for (; row_index < N; row_index++) {


            double Aii = A[row_index][row_index];

            if (std::fabs(Aii - 0.0) < EPS_CONST) {
                Logger::get_instance().logError(L"SYSTEM Has no-unique solution");
                return;
            }
            //impart linia y la A[i][i] daca A[i][i] != 1
            if (std::fabs(Aii - 1.0) > EPS_CONST) {
                for (size_t i = row_index; i < N; ++i) {
                    A[row_index][i] /= Aii;
                }
                y[row_index] /= Aii;
            }

            //formez 0 sub elementul de pe diagonala principala
            for (size_t i = row_index + 1; i < N; i++) {
                double coeff = -1.0 / A[i][row_index]; // -1/A[i][row_index]

                for (size_t j = row_index + 1; j < M; j++) {
                    A[i][j] += A[row_index][j] * coeff;
                }

                y[i] += y[row_index] * coeff;
            }
        }


        x[N - 1] = y[N - 1] / A[N - 1][M - 1];

        for (int k = N - 2; k >= 0; k--) {
            double sum = 0;

           
            for (int i = k + 1; i < M; i++) {
                sum += A[k][i] * x[i];
            }

            //            M
            //Xk = (Yk - E  Aki * Xi ) * 1 / Akk
            //            i = k
            // 
            x[k] = (y[k] - sum) * (1 / A[k][k]);

        }
    }

}



/*namespace FAST_MATH {

    // Type aliases for specific VECTOR sizes
    using VECTOR3D = VECTOR_STACK<3>;
    using VECTOR4D = VECTOR_STACK<4>;
    using VECTOR5D = VECTOR_STACK<5>;
    using VECTOR6D = VECTOR_STACK<6>;

    using MATRIX3D = MATRIX_STACK<3, 3>;
    using MATRIX4D = MATRIX_STACK<4, 4>;
    using MATRIX5D = MATRIX_STACK<5, 5>;
    using MATRIX6D = MATRIX_STACK<6, 6>;

    // Function to add two vectors (left += right)
    // Loop unrolled
    template<size_t S>
    void add_vector_to_left(VECTOR<S>* left, const VECTOR<S>* right) {
        double* left_data = left->get_data();  // Get the data pointer from 'left'
        const double* right_data = right->get_data(); // Get the data pointer from 'right'

        size_t i = 0;

        // Unrolling loop to add 4 elements at a time
        for (; i + 4 <= S; i += 4) {
            left_data[i] += right_data[i];
            left_data[i + 1] += right_data[i + 1];
            left_data[i + 2] += right_data[i + 2];
            left_data[i + 3] += right_data[i + 3];
        }

        // Process the remaining elements
        for (; i < S; ++i) {
            left_data[i] += right_data[i];
        }
    }

    // Function to add two vectors (right += left)
    // Loop unrolled
    template<size_t S>
    void add_vector_to_right(const VECTOR<S>* left, VECTOR<S>* right) {
        const double* left_data = left->get_data();  // Get the data pointer from 'left'
        double* right_data = right->get_data();      // Get the data pointer from 'right'

        size_t i = 0;

        // Unrolling loop to add 4 elements at a time
        for (; i + 4 <= S; i += 4) {
            right_data[i] += left_data[i];
            right_data[i + 1] += left_data[i + 1];
            right_data[i + 2] += left_data[i + 2];
            right_data[i + 3] += left_data[i + 3];
        }

        // Process the remaining elements
        for (; i < S; ++i) {
            right_data[i] += left_data[i];
        }
    }

    // Function to compute the dot product of two vectors
    // Loop unrolled
    template<size_t S>
    double dot_product(const VECTOR<S>* left, const VECTOR<S>* right) {
        const double* left_data = left->get_data();  // Get the data pointer from 'left'
        const double* right_data = right->get_data(); // Get the data pointer from 'right'

        double dot_product_result = 0.0;
        size_t i = 0;

        // Unrolling loop to process 4 elements at a time
        for (; i + 4 <= S; i += 4) {
            dot_product_result += left_data[i] * right_data[i];
            dot_product_result += left_data[i + 1] * right_data[i + 1];
            dot_product_result += left_data[i + 2] * right_data[i + 2];
            dot_product_result += left_data[i + 3] * right_data[i + 3];
        }

        // Process the remaining elements
        for (; i < S; ++i) {
            dot_product_result += left_data[i] * right_data[i];
        }

        return dot_product_result;
    }

    // Multiplies two matrices and stores the result in the given matrix
    // Loop unrolled
    template<size_t M, size_t N, size_t P>
    void multiply_matrix(Matrix<M, P>* result, const Matrix<M, N>* left, const Matrix<N, P>* right) {
        const double* left_data = left->get_data();  // Get the data pointer from 'left'
        const double* right_data = right->get_data(); // Get the data pointer from 'right'
        double* result_data = result->get_data();    // Get the data pointer from 'result'

        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < P; ++j) {
                result_data[i * P + j] = 0.0;
                size_t k = 0;

                // Unroll the loop to process 4 elements at a time
                for (; k + 4 <= N; k += 4) {
                    result_data[i * P + j] += left_data[i * M + k] * right_data[k * P + j];
                    result_data[i * P + j] += left_data[i * M + k + 1] * right_data[(k + 1) * P + j];
                    result_data[i * P + j] += left_data[i * M + k + 2] * right_data[(k + 2) * P + j];
                    result_data[i * P + j] += left_data[i * M + k + 3] * right_data[(k + 3) * P + j];
                }

                // Process the remaining elements
                for (; k < N; ++k) {
                    result_data[i * P + j] += left_data[i * N + k] * right_data[k * P + j];
                }
            }
        }
    }

    // Matrix-vector multiplication (M × N)
    // Loop unrolled
    template<size_t M, size_t N>
    void mul(VECTOR<M>* result, const Matrix<M, N>* mat, const VECTOR<N>* vec) {
        const double* mat_data = mat->get_data();  // Get the data pointer from 'mat'
        const double* vec_data = vec->get_data();  // Get the data pointer from 'vec'
        double* result_data = result->get_data();  // Get the data pointer from 'result'

        for (size_t i = 0; i < M; ++i) {
            result_data[i] = 0.0;
            size_t j = 0;

            // Unroll the loop to process 4 elements at a time
            for (; j + 4 <= N; j += 4) {
                result_data[i] += mat_data[i * N + j] * vec_data[j];
                result_data[i] += mat_data[i * N + j + 1] * vec_data[j + 1];
                result_data[i] += mat_data[i * N + j + 2] * vec_data[j + 2];
                result_data[i] += mat_data[i * N + j + 3] * vec_data[j + 3];
            }

            // Process the remaining elements
            for (; j < N; ++j) {
                result_data[i] += mat_data[i * N + j] * vec_data[j];
            }
        }
    }

    // Linear transformation (y = A * x + b)
    template<size_t N, size_t M>
    void linear_transform(VECTOR<N>* y, const Matrix<N, M>* A, const VECTOR<M>* x, const VECTOR<N>* b) {
        mul(y, A, x);  // Matrix-vector multiplication

        // Add the bias vector (unrolled loop)
        double* y_data = y->get_data();
        const double* b_data = b->get_data();

        size_t i = 0;

        // Unrolling loop to process 4 elements at a time
        for (; i + 4 <= N; i += 4) {
            y_data[i] += b_data[i];
            y_data[i + 1] += b_data[i + 1];
            y_data[i + 2] += b_data[i + 2];
            y_data[i + 3] += b_data[i + 3];
        }

        // Process the remaining elements
        for (; i < N; ++i) {
            y_data[i] += b_data[i];
        }
    }

    // Creates an orthographic projection matrix
    void orthographic(MATRIX4D* result, double left, double right, double bottom, double top, double near_v, double far_v) {
        ((*result)[0])[0] = 2.0 / (right - left);
        ((*result)[1])[1] = 2.0 / (top - bottom);
        ((*result)[2])[2] = -2.0 / (far_v - near_v);
        ((*result)[3])[3] = 1.0;

        ((*result)[3])[0] = -(right + left) / (right - left);
        ((*result)[3])[1] = -(top + bottom) / (top - bottom);
        ((*result)[3])[2] = -(far_v + near_v) / (far_v - near_v);
    }

    // Creates a perspective projection matrix
    void perspective(MATRIX4D* result, double fov, double aspect_ratio, double n, double f) {
        double tan_half_fov = std::tan(to_radians(fov) / 2.0);

        ((*result)[0])[0] = 1.0 / (aspect_ratio * tan_half_fov);
        ((*result)[1])[1] = 1.0 / tan_half_fov;
        ((*result)[2])[2] = -(n + f) / (f - n);
        ((*result)[2])[3] = -1.0;
        ((*result)[3])[2] = -(2.0 * f * n) / (f - n);
    }

    // Generates an identity matrix
    template<size_t N>
    void identity(Matrix<N, N>* result) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                ((*result)[i])[j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }
    template<size_t N>
    void generate_random_vector(VECTOR<N>* vec) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-100.0, 100.0);
        for (size_t i = 0; i < N; ++i) {
            (*vec)[i] = dis(gen);
        }
    }

    // Function to generate a random matrix
    template<size_t M, size_t N>
    void generate_random_matrix(Matrix<M, N>* mat) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-100.0, 100.0);
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                ((*mat)[i])[j] = dis(gen);
            }
        }
    }
}
*/