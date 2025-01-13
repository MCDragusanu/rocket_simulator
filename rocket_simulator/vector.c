#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define VECTOR_LOG(level, fmt, ...) \
    fprintf(stderr, "[%s][%s:%d] " level ": " fmt "\n", __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)


void vector_assign_value(struct VECTOR* self, double value) {
    if (self == NULL) {
        printf("[vector_assign_value] Vector is Null!\n");
        return;
    }
    if (self->pBuffer == NULL) {
        printf("[vector_assign_value] Vector buffer is Null!\n");
        return;
    }

    for (size_t i = 0; i < self->size; i++) {
        self->pBuffer[i] = value;
    }
}

void vector_transform_content(struct VECTOR* self, double (*tranform)(double, int)) {
    if (self == NULL || self->pBuffer == NULL) {
        printf("[vector_transform_content] Vector is Null!\n");
        return;
    }
    for (size_t i = 0; i < self->size; i++) {
        self->pBuffer[i] = tranform(self->pBuffer[i], i);
    }
}

void vector_free(struct VECTOR* self) {
    if (self != NULL) {
        free(self->pBuffer);
        free(self);
    }
}

void vector_print(const struct VECTOR* self) {
    if (self == NULL) {
        printf("\n[ NULL ]\n");
        return;
    }

    if (self->size == 0) {
        printf("\n[ ]\n");
        return;
    }

    printf("\n[");
    for (size_t i = 0; i < self->size; i++) {
        printf("%f", self->pBuffer[i]);
        if (i < self->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


int vector_content_equals(const struct VECTOR* lhs, const struct VECTOR* rhs , double tolerance) {
    if (lhs == NULL || rhs == NULL) {
        printf("[vector_content_equals] Invalid argument: One of the input vectors is null!\n");
        return 0;
    }

    if (lhs->pBuffer == NULL || rhs->pBuffer == NULL) {
        printf("[vector_content_equals] Invalid argument: One of the input vectors has a null buffer!\n");
        return 0;
    }

    if (lhs->size != rhs->size) {
        return 0;
    }

    for (int i = 0; i < lhs->size; i++) {
        if (fabs(lhs->pBuffer[i] - rhs->pBuffer[i]) > tolerance) return 0;
    }

    return 1;
}

int vector_resize(struct VECTOR* self, size_t new_capacity) {
    if (self == NULL) {
        printf("[vector_resize] Invalid argument: self is null!\n");
        return 0;
    }

    if (self->pBuffer == NULL) {
        printf("[vector_resize] Invalid argument: self buffer is null!\n");
        return 0;
    }

    if (new_capacity == 0) {
        printf("[vector_resize] Cannot resize to zero capacity!\n");
        return 0;
    }

    double* new_buffer = (double*)realloc(self->pBuffer, new_capacity * sizeof(double));
    if (new_buffer == NULL) {
        printf("[vector_resize] Runtime exception: Buffer resize failed!\n");
        return 0;
    }

    self->capacity = new_capacity;

    if (new_buffer != self->pBuffer) {
        self->pBuffer = new_buffer;
    }

    if (self->size > new_capacity) {
        self->size = new_capacity;
    }

    return 1;
}

struct VECTOR* vector_deep_copy(const struct VECTOR* self) {
    if (self == NULL || self->pBuffer == NULL) {
        printf("[vector_set_buffer] Invalid argument: Input self is not initialised correctly!\n");
        return NULL;
    }

    struct VECTOR* result = (struct VECTOR*)malloc(sizeof(struct VECTOR));
    if (result == NULL) {
        printf("[vector_set_buffer] Runtime error: Failed to allocate VECTOR inst!\n");
        return NULL;
    }

    result->pBuffer = (double*)calloc(self->capacity, sizeof(double));
    if (result->pBuffer == NULL) {
        printf("[vector_set_buffer] Runtime error: Failed to allocate VECTOR  buffer!\n");
        vector_free(result);
        return NULL;
    }

    memcpy(result->pBuffer, self->pBuffer, self->capacity * sizeof(double));
    result->capacity = self->capacity;
    result->size = self->size;

    return result;
    
}

struct VECTOR* vector_create(size_t capacity, size_t size, double default_value) {
    if (capacity < size) {
        printf("ERROR [vector_create]: Destination capacity (%zu) is smaller than size (%zu).\n", capacity, size);
        return NULL;
    }

    struct VECTOR* result = malloc(sizeof(struct VECTOR));
    if (result == NULL) {
        printf("[vector_create] Failed to allocate VECTOR object!\n");
        return NULL;
    }

   result->pBuffer = (double*)calloc(capacity, sizeof(double));
    if (result->pBuffer == NULL) {
        printf("[vector_create] Failed to allocate VECTOR buffer!\n");
        free(result);
        return NULL;
    }
  
    result->capacity = capacity;
    result->size = size;
    vector_assign_value(result, default_value);

    return result;
}

struct VECTOR* vector_sub_range(const struct VECTOR* src, size_t startInclusive, size_t endExclusive) {
    if (src == NULL || src->pBuffer == NULL) {
        printf("[vector_sub_range] Source self or buffer is null!\n");
        return NULL;
    }

    if (startInclusive >= src->size || startInclusive >= endExclusive || endExclusive > src->size) {
        printf("ERROR [vector_sub_range]: Invalid range. Start index (%zu) and end index (%zu) are out of bounds.\n", startInclusive, endExclusive);
        return NULL;
    }

    struct VECTOR* result = malloc(sizeof(struct VECTOR));
    if (result == NULL) {
        printf("[vector_sub_range] Failed to allocate Destination self!\n");
        return NULL;
    }

    size_t item_count = endExclusive - startInclusive;
    result->pBuffer = (double*)calloc(item_count, sizeof(double));
    if (result->pBuffer == NULL) {
        printf("Error [vector_sub_range] : Failed to allocate VECTOR buffer!\n");
        free(result);
        return NULL;
    }

    memcpy(result->pBuffer, src->pBuffer + startInclusive, item_count * sizeof(double));
    result->capacity = item_count;
    result->size = item_count;

    return result;
}

struct VECTOR* vector_base(size_t capacity, size_t dimension, size_t index) {
    if (dimension > capacity || index >= dimension) {
        printf("ERROR [vector_base]: Invalid dimension or index.\n");
        return NULL;
    }

    struct VECTOR* result = vector_create(capacity, dimension, 0);
    if (result == NULL) {
        printf("Error [vector_base] : Failed to allocate Base self!\n");
        return NULL;
    }

    result->pBuffer[index] = 1.0;
    return result;
}

void vector_normalise_in_place(struct VECTOR* self , double tolerance) {

    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_normalise_in_place] : Vector or buffer is null!\n");
        return;
    }
    double magnitude = vector_magnitude(self);
    if (fabs(magnitude) < tolerance) {
        printf("Warning [vector_normalise_in_place] : the magnitude is below tolerance %f", tolerance);
        return;
    }

    for (size_t i = 0; i < self->size; i++) {
        self->pBuffer[i] /= magnitude;
    }
}
void vector_add_in_place(struct VECTOR* self, const struct VECTOR* other) {
    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_add_in_place] : Source Vector ptr or buffer is null!\n");
        return;
    }
    if (other == NULL || other->pBuffer == NULL) {
        printf("Error [vector_add_in_place] : Other Vector ptr or buffer is null!\n");
        return;
    }
   
    if (self->size != other->size) {
        printf("Error [vector_add_in_place] : The vectors are of different sizes!\n");
        return;
    }

    for (size_t i = 0; i < self->size; i++) {
        self->pBuffer[i] += other->pBuffer[i];
    }
}

void vector_substract_in_place(struct VECTOR* self, const struct VECTOR* other) {
    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_substract_in_place] : Source Vector ptr or buffer is null!\n");
        return;
    }
    if (other == NULL || other->pBuffer == NULL) {
        printf("Error [vector_substract_in_place] : Other Vector ptr or buffer is null!\n");
        return;
    }

    if (self->size != other->size) {
        printf("Error [vector_substract_in_place] : The vectors are of different sizes!\n");
        return;
    }

    for (size_t i = 0; i < self->size; i++) {
        self->pBuffer[i] -= other->pBuffer[i];
    }
}

void vector_scale_in_place(struct VECTOR* self, double scalar) {
    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_substract_in_place] : Source Vector ptr or buffer is null!\n");
        return;
    }
    for (size_t i = 0; i < self->size; i++) {
        self->pBuffer[i] *= scalar;
    }
}


double vector_magnitude(const struct VECTOR* self) {
   
    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_magnitude] : Vector or buffer is null!\n");
        return;
    }

    double squared_sum = 0.0;
    for (size_t i = 0; i < self->size; i++) {
        squared_sum += (self->pBuffer[i] * self->pBuffer[i]);
    }

    return sqrt(squared_sum);
}

double vector_dot_product(const struct VECTOR* self, const struct VECTOR* other) {
    
    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_dot_product] : Source Vector ptr or buffer is null!\n");
        return 0.0;
    }
    if (other == NULL || other->pBuffer == NULL) {
        printf("Error [vector_dot_product] : Other Vector ptr or buffer is null!\n");
        return 0.0;
    }

    if (self->size != other->size) {
        printf("Error [vector_dot_product] : The vectors are of different sizes!\n");
        return 0.0;
    }

    double dot_product = 0.0;

    for (size_t i = 0; i < self->size; i++) {
        dot_product += (self->pBuffer[i] * other->pBuffer[i]);
    }

    return dot_product;
}

double vector_sum(const struct VECTOR* self) {
    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_sum] : Source Vector ptr or buffer is null!\n");
        return 0.0;
    }

    double sum = 0.0;

    for (size_t i = 0; i < self->size; i++) {
        sum += self->pBuffer[i];
    }

    return sum;
}

double vector_mean(const struct VECTOR* self) {
    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_mean] : Source Vector ptr or buffer is null!\n");
        return 0.0;
    }
    if (self->size == 0) {
        printf("Error [vector_mean] : Source Vector has size 0!\n");
        return 0.0;
    }
    double sum = vector_sum(self);
    return sum / self->size;
}

double vector_variance(const struct VECTOR* self) {
    
    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_variance] : Source Vector ptr or buffer is null!\n");
        return 0.0;
    }

    if (self->size == 0) {
        printf("Error [vector_variance] : Source Vector has size 0!\n");
        return 0.0;
    }

    double mean = vector_mean(self);

    double variance = 0.0;

    for (int i = 0; i < self->size; i++) {
        variance += (self->pBuffer[i] - mean) * (self->pBuffer[i] - mean);
    }

    return variance / self->size;
}


double vector_standard_dev(const struct VECTOR* self) {
    
    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_standard_dev] : Source Vector ptr or buffer is null!\n");
        return 0.0;
    }

    return sqrt(vector_variance(self));
}


struct VECTOR* vector_normalise(const struct VECTOR* self , double tolerance) {
    if (self == NULL || self->pBuffer == NULL) {
        printf("Error [vector_normalise] : Source Vector ptr or buffer is null!\n");
        return;
    }

    double magnitude = vector_magnitude(self);
    if (fabs(magnitude) < tolerance) {
        printf("Warning [vector_normalise] : the magnitude is below tolerance %f", tolerance);
        return self;
    }

    struct VECTOR* result = vector_deep_copy(self);
    if (result == NULL || result->pBuffer == NULL) {
        printf("Error [vector_normalise] : Result Vector failed to create!\n");
        return;
    }

    for (size_t i = 0; i < self->size; i++) {
        result->pBuffer[i] /= magnitude;
    }
    return result;
}


struct VECTOR* vector_add(const struct VECTOR* lhs, const struct VECTOR* rhs) {
    if (lhs == NULL || lhs->pBuffer == NULL) {
        printf("Error [vector_add] : Source Vector ptr or buffer is null!\n");
        return;
    }
    if (rhs == NULL || rhs->pBuffer == NULL) {
        printf("Error [vector_add] : Source Vector ptr or buffer is null!\n");
        return;
    }

   
    if (lhs->size != rhs->size) {
        printf("Warning [vector_add] : the self sizes are different");
        return NULL;
    }

    struct VECTOR* result = vector_deep_copy(lhs);
    if (result == NULL || result->pBuffer == NULL) {
        printf("Error [vector_add] : Result Vector failed to create!\n");
        return;
    }

    for (size_t i = 0; i < lhs->size; i++) {
        result->pBuffer[i] += rhs->pBuffer[i];
    }
    return result;
}

struct VECTOR* vector_substract(const struct VECTOR* lhs, const struct VECTOR* rhs) {
    if (lhs == NULL || lhs->pBuffer == NULL) {
        printf("Error [vector_substract] : Source Vector ptr or buffer is null!\n");
        return;
    }
    if (rhs == NULL || rhs->pBuffer == NULL) {
        printf("Error [vector_substract] : Source Vector ptr or buffer is null!\n");
        return;
    }


    if (lhs->size != rhs->size) {
        printf("Warning [vector_substract] : the vector sizes are different");
        return NULL;
    }

    struct VECTOR* result = vector_deep_copy(lhs);
    if (result == NULL || result->pBuffer == NULL) {
        printf("Error [vector_substract] : Result Vector failed to create!\n");
        return;
    }

    for (size_t i = 0; i < lhs->size; i++) {
        result->pBuffer[i] -= rhs->pBuffer[i];
    }
    return result;
}

struct VECTOR* vector_scale(const struct VECTOR* lhs, double scalar) {
    if (lhs == NULL || lhs->pBuffer == NULL) {
        printf("Error [vector_substract] : Source Vector ptr or buffer is null!\n");
        return;
    }

    struct VECTOR* result = vector_deep_copy(lhs);
    if (result == NULL || result->pBuffer == NULL) {
        printf("Error [vector_substract] : Result Vector failed to create!\n");
        return;
    }

    for (size_t i = 0; i < lhs->size; i++) {
        result->pBuffer[i] *= scalar;
    }
    return result;
}

