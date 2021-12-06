#include "calculator/calculator.h"
#include "ui/ui.h"
#include "e4c.h"

int main(int argc, char* argv[]) {
  // initializes the data needed to use exceptions
  e4c_using_context(E4C_TRUE) {
    Calculator* calculator = calculator_create();

    if (argc == 1) {
      calculator_run_interactive_mode(calculator);
    } else if (argc == 2) {
      calculator_run_non_interactive_mode(calculator, argv[1]);
    } else {
      ui_write("Error: the calculator only accepts zero or one arguments\n");
    }

    calculator_destroy(calculator);
  }
  return 0;
}
