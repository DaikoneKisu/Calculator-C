#include "calculator/calculator.h"

#include <stdlib.h>

#include "calculator/evaluator/evaluator.h"
#include "ui/ui.h"
#include "e4c.h"
#include "misc-utils/string-utils/string-utils.h"

struct Calculator {
  Evaluator* evaluator;
};

Calculator* calculator_create(void) {
  Calculator* newly_created_calculator = (Calculator*) malloc(sizeof(Calculator));

  newly_created_calculator->evaluator = evaluator_create();

  return newly_created_calculator;
}

void calculator_destroy(Calculator* calculator) {
  evaluator_destroy(calculator->evaluator);
  free(calculator);
}

void calculator_run_interactive_mode(Calculator* calculator) {
  char* input = ui_read();
  while (strcmp(input, "quit") != 0) {
    calculator_run_non_interactive_mode(calculator, input);
    free(input);
    input = ui_read();
  }
  free(input);
}

void calculator_run_non_interactive_mode(Calculator* calculator, const char* input) {
  try {
    char* result = evaluator_evaluate(calculator->evaluator, input);
    ui_write("%s\n", result);
    free(result);
  } catch (RuntimeException) {
    const e4c_exception* exception = e4c_get_exception();

    ui_write("Error: %s\n", exception->message);
  }
}
