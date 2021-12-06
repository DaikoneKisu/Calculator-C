#ifndef CONTAINERS_STACK_DOUBLE_STACK_H
#define CONTAINERS_STACK_DOUBLE_STACK_H

#include <stdbool.h>

typedef struct DoubleStack DoubleStack;

DoubleStack* double_stack_create(void);
DoubleStack* double_stack_clone(DoubleStack* stack);
void double_stack_destroy(DoubleStack* stack);

int double_stack_size(DoubleStack* stack);
bool double_stack_is_empty(DoubleStack* stack);

double double_stack_top(DoubleStack* stack);

void double_stack_push(DoubleStack* stack, double new_element);
double double_stack_pop(DoubleStack* stack);
void double_stack_swap(DoubleStack* stack);

void double_stack_clear(DoubleStack* stack);

#endif
