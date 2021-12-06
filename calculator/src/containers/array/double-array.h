#ifndef CONTAINERS_ARRAY_DOUBLE_ARRAY_H
#define CONTAINERS_ARRAY_DOUBLE_ARRAY_H

#include <stdbool.h>

typedef struct DoubleArray DoubleArray;

DoubleArray* double_array_create(int initial_size);
DoubleArray* double_array_clone(DoubleArray* array);
void double_array_destroy(DoubleArray* array);

int double_array_size(DoubleArray* array);
bool double_array_is_empty(DoubleArray* array);

double double_array_get(DoubleArray* array, int index);
void double_array_set(DoubleArray* array, int index, double new_value);

void double_array_push_back(DoubleArray* array, double new_element);

void double_array_resize(DoubleArray* array, int new_size);

void double_array_clear(DoubleArray* array);

#endif
