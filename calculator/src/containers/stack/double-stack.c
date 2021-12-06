#include "containers/stack/double-stack.h"

#include <stdlib.h>

#include "containers/array/double-array.h"

struct DoubleStack {
  DoubleArray* elements;
};

DoubleStack* double_stack_create(void) {
  DoubleStack* stack = malloc(sizeof(DoubleStack));

  stack->elements = double_array_create(0);

  return stack;
}

void double_stack_destroy(DoubleStack* stack) {
  double_array_destroy(stack->elements);
  free(stack);
}

bool double_stack_is_empty(DoubleStack* stack) {
  return double_array_is_empty(stack->elements);
}

void double_stack_push(DoubleStack* stack, double new_element) {
  double_array_push_back(stack->elements, new_element);
}

double double_stack_pop(DoubleStack* stack) {
  int number_of_elements = double_array_size(stack->elements);

  double popped_element = double_array_get(stack->elements, number_of_elements - 1);
  double_array_resize(stack->elements, number_of_elements - 1);

  return popped_element;
}

double double_stack_top(DoubleStack* stack) {
  return double_array_get(stack->elements, double_array_size(stack->elements) - 1);
}

void double_stack_swap(DoubleStack* stack) {
  int number_of_elements = double_array_size(stack->elements);

  double element_at_top = double_array_get(stack->elements, number_of_elements - 1);
  double element_behind_top = double_array_get(stack->elements, number_of_elements - 2);
  double_array_set(stack->elements, number_of_elements - 1, element_behind_top);
  double_array_set(stack->elements, number_of_elements - 2, element_at_top);
}

int double_stack_size(DoubleStack* stack) {
  return double_array_size(stack->elements);
}

DoubleStack* double_stack_clone(DoubleStack* stack) {
  DoubleStack* clone = (DoubleStack*) malloc(sizeof(DoubleStack));

  clone->elements = double_array_clone(stack->elements);

  return clone;
}

void double_stack_clear(DoubleStack* stack) {
  double_array_clear(stack->elements);
}
