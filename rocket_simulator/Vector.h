#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * VECTOR struct represents a dynamic array for doubles.
 * Fields:
 * - pBuffer: Pointer to the dynamically allocated buffer for storing elements.
 * - size: The current number of elements in the vector.
 * - capacity: The maximum number of elements the vector can store without resizing.
 */
typedef struct VECTOR {
    double* pBuffer;  // Pointer to the dynamically allocated buffer.
    size_t size;      // Current number of elements in the vector.
    size_t capacity;  // Maximum capacity of the vector.
} VECTOR;

// Function prototypes for VECTOR operations:

/**
 * Assigns a specific value to all elements in the vector.
 * @param self: Pointer to the VECTOR struct.
 * @param value: The value to assign.
 */
void vector_assign_value(struct VECTOR* self, double value);

/**
 * Transforms the contents of the vector using a user-defined function.
 * @param self: Pointer to the VECTOR struct.
 * @param transform: Pointer to the transformation function.
 */
void vector_transform_content(struct VECTOR* self, double (*tranform)(double, int));

/**
 * Frees the memory allocated for the vector.
 * @param self: Pointer to the VECTOR struct to free.
 */
void vector_free(struct VECTOR* self);

/**
 * Prints the contents of the vector.
 * @param self: Pointer to the VECTOR struct to print.
 */
void vector_print(const struct VECTOR* self);

/**
 * Normalizes the vector in place, ensuring its magnitude is 1 within a tolerance.
 * @param self: Pointer to the VECTOR struct.
 * @param tolerance: Threshold below which normalization is skipped.
 */
void vector_normalise_in_place(struct VECTOR* self, double tolerance);

/**
 * Adds another vector's elements to the current vector in place.
 * @param self: Pointer to the VECTOR struct.
 * @param other: Pointer to the VECTOR struct to add.
 */
void vector_add_in_place(struct VECTOR* self, const struct VECTOR* other);

/**
 * Subtracts another vector's elements from the current vector in place.
 * @param self: Pointer to the VECTOR struct.
 * @param other: Pointer to the VECTOR struct to subtract.
 */
void vector_substract_in_place(struct VECTOR* self, const struct VECTOR* other);

/**
 * Scales the vector's elements by a scalar value in place.
 * @param self: Pointer to the VECTOR struct.
 * @param scalar: The scalar multiplier.
 */
void vector_scale_in_place(struct VECTOR* self, double scalar);

/**
 * Checks if two vectors are equal within a specified tolerance.
 * @param self: Pointer to the first VECTOR struct.
 * @param other: Pointer to the second VECTOR struct.
 * @param tolerance: The tolerance for element-wise comparison.
 * @return: 1 if equal, 0 otherwise.
 */
int vector_content_equals(const struct VECTOR* self, const struct VECTOR* other, double tolerance);

/**
 * Resizes the vector's capacity.
 * @param self: Pointer to the VECTOR struct.
 * @param capacity: The new capacity.
 * @return: 1 if successful, 0 otherwise.
 */
int vector_resize(struct VECTOR* self, size_t capacity);


/**
 * Calculates the magnitude (Euclidean norm) of the vector.
 * @param self: Pointer to the VECTOR struct.
 * @return: The magnitude of the vector.
 */
double vector_magnitude(const struct VECTOR* self);

/**
 * Computes the dot product of two vectors.
 * @param self: Pointer to the first VECTOR struct.
 * @param other: Pointer to the second VECTOR struct.
 * @return: The dot product of the two vectors.
 */
double vector_dot_product(const struct VECTOR* self, const struct VECTOR* other);

/**
 * Calculates the sum of all elements in the vector.
 * @param self: Pointer to the VECTOR struct.
 * @return: The sum of all elements.
 */
double vector_sum(const struct VECTOR* self);

/**
 * Calculates the mean (average) of the vector's elements.
 * @param self: Pointer to the VECTOR struct.
 * @return: The mean of the elements.
 */
double vector_mean(const struct VECTOR* self);

/**
 * Computes the variance of the vector's elements.
 * @param self: Pointer to the VECTOR struct.
 * @return: The variance of the elements.
 */
double vector_variance(const struct VECTOR* self);

/**
 * Computes the standard deviation of the vector's elements.
 * @param self: Pointer to the VECTOR struct.
 * @return: The standard deviation of the elements.
 */
double vector_standard_dev(const struct VECTOR* self);

/**
 * Creates a new vector with the specified capacity, size, and default value.
 * @param capacity: Initial capacity of the vector.
 * @param size: Initial size of the vector.
 * @param default_value: Value to initialize the elements with.
 * @return: Pointer to the newly created VECTOR struct.
 */
struct VECTOR* vector_create(size_t capacity, size_t size, double default_value);

/**
 * Creates a deep copy of a vector.
 * @param vector: Pointer to the VECTOR struct to copy.
 * @return: Pointer to the copied VECTOR struct.
 */
struct VECTOR* vector_deep_copy(const struct VECTOR* vector);

/**
 * Extracts a subrange of elements from the vector.
 * @param self: Pointer to the VECTOR struct.
 * @param start: Starting index of the subrange.
 * @param end: Ending index of the subrange.
 * @return: Pointer to the new VECTOR struct containing the subrange.
 */
struct VECTOR* vector_sub_range(const struct VECTOR* self, size_t start, size_t end);

/**
 * Creates a vector with a base value, dimension, and index.
 * @param capacity: Initial capacity of the vector.
 * @param dimension: Dimension size.
 * @param index: Index to set a base value.
 * @return: Pointer to the newly created VECTOR struct.
 */
struct VECTOR* vector_base(size_t capacity, size_t dimension, size_t index);

/**
 * Normalizes the vector and returns a new normalized vector.
 * @param self: Pointer to the VECTOR struct.
 * @param tolerance: Threshold below which normalization is skipped.
 * @return: Pointer to the normalized VECTOR struct.
 */
struct VECTOR* vector_normalise(const struct VECTOR* self, double tolerance);

/**
 * Adds two vectors and returns a new vector containing the result.
 * @param lhs: Pointer to the first VECTOR struct.
 * @param rhs: Pointer to the second VECTOR struct.
 * @return: Pointer to the resulting VECTOR struct.
 */
struct VECTOR* vector_add(const struct VECTOR* lhs, const struct VECTOR* rhs);

/**
 * Subtracts one vector from another and returns a new vector containing the result.
 * @param lhs: Pointer to the first VECTOR struct.
 * @param rhs: Pointer to the second VECTOR struct.
 * @return: Pointer to the resulting VECTOR struct.
 */
struct VECTOR* vector_substract(const struct VECTOR* lhs, const struct VECTOR* rhs);

/**
 * Scales a vector by a scalar and returns a new scaled vector.
 * @param lhs: Pointer to the VECTOR struct.
 * @param scalar: The scalar multiplier.
 * @return: Pointer to the resulting VECTOR struct.
 */
struct VECTOR* vector_scale(const struct VECTOR* lhs, double scalar);

