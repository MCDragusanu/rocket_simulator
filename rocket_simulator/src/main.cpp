#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <sstream>

#include "win_api/window/Window.h"
#include "utils/logging/ConsoleLogger.h"
#include "math/Math.h"

#include "../include/glad/glad.h"
#include "../include/glfw/glfw3.h"


// Linear transform computation using both Math and FAST_MATH namespaces
template<size_t N>
void run_linear_transform_benchmark() {
    std::wstringstream ss;

    // Dynamically allocate memory for vector, matrix, and result objects
    auto vector =  HeapVector<N>();
    auto matrix =  HeapMatrix<N,N>();
    auto b      =  HeapVector<N>();

    Math::generate_random_vector<N>(b);
    Math::generate_random_matrix<N ,N>(matrix);
    Math::generate_random_vector<N>(vector);

    auto result_math = HeapVector<N>();
    auto result_fast_math = HeapVector<N>();

    // Measure time for Math namespace linear transform
    auto start = std::chrono::high_resolution_clock::now();
    Math::linear_transform(result_math, matrix, vector, b);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_math = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    ss << L"Math namespace time: " << duration_math.count() << L" ms\n";

    // Measure time for FAST_MATH namespace linear transform
    start = std::chrono::high_resolution_clock::now();
    Math::linear_transform(result_fast_math, matrix, vector, b);
    end = std::chrono::high_resolution_clock::now();
    auto duration_fast_math = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    ss << L"FAST_MATH namespace time: " << duration_fast_math.count() << L" ms\n";

    // Compare the results (optionally)
    int is_equal = 0;
    
    for (size_t i = 0; i < N; ++i) {
        if (std::abs((result_math)[i] - (result_fast_math)[i]) > 1e-6) {
            is_equal += 1;
            double v = (vector)[i];
            double b_i = (b)[i];
            double y_1 = (result_math)[i];
            double y_2 = (result_fast_math)[i];
            ss << L"v + b = " << v + b_i << L"   computed =   " << y_1 << L"    fast_computed =    " << y_2 << "\n";
            //break;
        }
    }

    ss << L"Found " << (is_equal)<<  L" diferences" << "\n";

    // Log the results
    Logger::get_instance().logError(ss.str());

   
}
#include <chrono> // Include the chrono library for time measurement

template<size_t N>
void test_lin_system_solver() {
    std::wstringstream ss;

    // Allocate memory for the vector and result objects
    auto x_copy = HeapVector<N>();  // Solution vector for copy solver
    auto A_copy = HeapMatrix<N, N>();  // Identity matrix for copy solver
    auto b_copy = HeapVector<N>();  // Right-hand side vector for copy solver

   
    // Set A as identity matrix for both solvers
    Math::identity(A_copy);
    
    // Generate a random vector b for both solvers
    Math::generate_random_vector<N>(b_copy);
   
    // Measure time for the copy solver
    auto start_time_copy = std::chrono::high_resolution_clock::now();

    // Solve the system A * x = b using lin_sys_solver (copy)
    Math::lin_sys_solver(x_copy, A_copy, b_copy);

    // End measuring time for the copy solver
    auto end_time_copy = std::chrono::high_resolution_clock::now();
    auto duration_copy = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_copy - start_time_copy); // Measure time in milliseconds

    // Log the result of the copy solver
    int differences_copy = 0;
    for (size_t i = 0; i < N; ++i) {
        if (std::abs(x_copy[i] - b_copy[i]) > 1e-6) {  // Allowing for small numerical error
            differences_copy++;
            ss << L"Copy Solver: Difference at index " << i << L": computed x = " << x_copy[i] << L", expected = " << b_copy[i] << "\n";
        }
    }

    if (differences_copy == 0) {
        ss << L"Copy Solver passed the test. No differences found.\n";
    }
    else {
        ss << L"Copy Solver failed the test. " << differences_copy << L" differences found.\n";
    }

    // Measure time for the in-place solver
    auto start_time_inplace = std::chrono::high_resolution_clock::now();

    // Reset the solution vector for in-place solver
    for (int i = 0; i < N; i++) {
        x_copy[i] = 0.0;
    }
    // Solve the system A * x = b using lin_sys_solver (in-place)
    Math::lin_sys_solver_inplace(x_copy, A_copy, b_copy);

    // End measuring time for the in-place solver
    auto end_time_inplace = std::chrono::high_resolution_clock::now();
    auto duration_inplace = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_inplace - start_time_inplace); // Measure time in milliseconds

    // Log the result of the in-place solver
    int differences_inplace = 0;
    for (size_t i = 0; i < N; ++i) {
        if (std::abs(x_copy[i] - b_copy[i]) > 1e-6) {  // Allowing for small numerical error
            differences_inplace++;
            ss << L"In-place Solver: Difference at index " << i << L": computed x = " << x_copy[i] << L", expected = " << b_copy[i] << "\n";
        }
    }

    if (differences_inplace == 0) {
        ss << L"In-place Solver passed the test. No differences found.\n";
    }
    else {
        ss << L"In-place Solver failed the test. " << differences_inplace << L" differences found.\n";
    }

    // Log the duration of both solvers
    ss << L"Time taken for the Copy Solver: " << duration_copy.count() << L" ms\n";
    ss << L"Time taken for the In-place Solver: " << duration_inplace.count() << L" ms\n";

    // Log the results
    Logger::get_instance().logError(ss.str());
}



int main() {
    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); return-1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
        std::cout << "Failed to initialize GLAD" << std::endl; return-1;
    }
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); return 0;
}

   

