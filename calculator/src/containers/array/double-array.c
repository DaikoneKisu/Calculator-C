#include "containers/array/double-array.h"

#include <stdlib.h>

#include "misc-utils/string-utils/string-utils.h"

struct DoubleArray {
  double* elements;
  int size;
};

DoubleArray* double_array_create(int initial_size) {
  DoubleArray* new_array = (DoubleArray*) malloc(sizeof(DoubleArray));

  if (initial_size != 0) {
    new_array->elements = (double*) malloc(sizeof(double) * initial_size);
  } else {
    new_array->elements = NULL;
  }
  new_array->size = initial_size;

  return new_array;
}

DoubleArray* double_array_clone(DoubleArray* array) {
  DoubleArray* clone = double_array_create(array->size);

  memcpy(clone->elements, array->elements, sizeof(double) * array->size);

  return clone;
}

void double_array_destroy(DoubleArray* array) {
  free(array->elements);
  free(array);
}

int double_array_size(DoubleArray* array) {
  return array->size;
}

bool double_array_is_empty(DoubleArray* array) {
  return array->size == 0;
}

double double_array_get(DoubleArray* array, int index) {
  return array->elements[index];
}

void double_array_set(DoubleArray* array, int index, double new_value) {
  array->elements[index] = new_value;
}

void double_array_push_back(DoubleArray* array, double new_value) {
  double_array_resize(array, array->size + 1);
  array->elements[array->size - 1] = new_value;
}

void double_array_resize(DoubleArray* array, int new_size) {
  if (new_size != 0) {
    array->elements = (double*) realloc(array->elements, sizeof(double) * new_size);
  } else {
    free(array->elements);
    array->elements = NULL;
  }
  array->size = new_size;
}

void double_array_clear(DoubleArray* array) {
  double_array_resize(array, 0);
}
