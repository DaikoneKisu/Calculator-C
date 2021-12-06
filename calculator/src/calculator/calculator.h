#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

typedef struct Calculator Calculator;

Calculator* calculator_create(void);
void calculator_destroy(Calculator* calculator);

void calculator_run_interactive_mode(Calculator* calculator);
void calculator_run_non_interactive_mode(Calculator* calculator, const char* input);

#endif
