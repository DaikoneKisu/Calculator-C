#include "calculator/evaluator/evaluator.h"

#include <stdlib.h>
#include <math.h>

#include "calculator/evaluator/tokenizer/tokenizer.h"
#include "containers/stack/double-stack.h"
#include "e4c.h"
#include "misc-utils/string-utils/string-utils.h"
#include "misc-utils/number-converters/number-converters.h"

struct Evaluator {
  DoubleStack* buffer;
  double stored_number;
  NumberConverter* converter;
};

Evaluator* evaluator_create(void) {
  Evaluator* newly_created_evaluator = (Evaluator*) malloc(sizeof(Evaluator));

  newly_created_evaluator->buffer = double_stack_create();
  newly_created_evaluator->stored_number = 0;
  newly_created_evaluator->converter = decimal_number_converter;

  return newly_created_evaluator;
}

void evaluator_destroy(Evaluator* evaluator) {
  double_stack_destroy(evaluator->buffer);
  free(evaluator);
}

char* evaluate_number(Evaluator* evaluator, const char* number) {
  double value_of_number = number_converter_convert_string_to_number(decimal_number_converter, number);

  double_stack_push(evaluator->buffer, value_of_number);
  return clone_string("");
}

char* pi_operation(Evaluator* evaluator) {
  double_stack_push(evaluator->buffer, acos(-1));
  return clone_string("");
}

char* euler_operation(Evaluator* evaluator) {
  double_stack_push(evaluator->buffer, exp(1));
  return clone_string("");
}

char* addition_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 2) {
    throw(RuntimeException, "the addition needs two operands");
  }

  double second_operand = double_stack_pop(evaluator->buffer);
  double first_operand = double_stack_pop(evaluator->buffer);
  double result = first_operand + second_operand;
  double_stack_push(evaluator->buffer, result);
  
  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* subtraction_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 2) {
    throw(RuntimeException, "the subtraction needs two operands");
  }

  double second_operand = double_stack_pop(evaluator->buffer);
  double first_operand = double_stack_pop(evaluator->buffer);
  double result = first_operand - second_operand;
  double_stack_push(evaluator->buffer, result);
  
  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* multiplication_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 2) {
    throw(RuntimeException, "the multiplication needs two operands");
  }

  double second_operand = double_stack_pop(evaluator->buffer);
  double first_operand = double_stack_pop(evaluator->buffer);
  double result = first_operand * second_operand;
  double_stack_push(evaluator->buffer, result);
  
  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* division_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 2) {
    throw(RuntimeException, "the division needs two operands");
  }

  double divisor = double_stack_pop(evaluator->buffer);
  if (divisor == 0) {
    throw(RuntimeException, "the division divisor can't be zero");
  }
  double dividend = double_stack_pop(evaluator->buffer);
  double result = dividend / divisor;
  double_stack_push(evaluator->buffer, result);
  
  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* exponentiation_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 2) {
    throw(RuntimeException, "the exponentiation needs two operands");
  }

  double exponent = double_stack_pop(evaluator->buffer);
  double base = double_stack_pop(evaluator->buffer);
  if (base == 0 && exponent == 0) {
    throw(RuntimeException, "the exponentiation base and exponent can't be simultaneously zero");
  }
  double result = pow(base, exponent);
  double_stack_push(evaluator->buffer, result);
  
  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* logarithm_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 2) {
    throw(RuntimeException, "the logarithm needs two operands (base and argument)");
  }

  double argument = double_stack_pop(evaluator->buffer);
  if (argument == 0) {
    throw(RuntimeException, "the logarithm argument can't be zero");
  }
  double base = double_stack_pop(evaluator->buffer);
  if (base == 0) {
    throw(RuntimeException, "the logarithm base can't be zero");
  }
  double result = log10(argument)/log10(base);
  double_stack_push(evaluator->buffer, result);
  
  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* root_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 2) {
    throw(RuntimeException, "the root needs two operands (index and radicand)");
  }

  double radicand = double_stack_pop(evaluator->buffer);
  double index = double_stack_pop(evaluator->buffer);
  if (index == 0) {
    throw(RuntimeException, "the root index can't be zero");
  }
  double result = pow(radicand, 1/index);
  double_stack_push(evaluator->buffer, result);
  
  return number_converter_convert_number_to_string(evaluator->converter, result);
}

long factorial_of(long number) {
  long result = 1;
  for (long i = 2; i <= number; ++i) {
    result *= i;
  }
  return result;
}

char* factorial_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    throw(RuntimeException, "the factorial needs one operand");
  }

  double operand = double_stack_pop(evaluator->buffer);
  if (operand < 0) {
    throw(RuntimeException, "the factorial operand can't be lesser than zero");
  }
  double result = factorial_of(lround(operand));
  double_stack_push(evaluator->buffer, result);

  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* sin_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    throw(RuntimeException, "the sine needs one operand");
  }

  double operand = double_stack_pop(evaluator->buffer);
  double result = sin(operand);
  double_stack_push(evaluator->buffer, result);

  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* arcsin_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    throw(RuntimeException, "the arcsine needs one operand");
  }

  double operand = double_stack_pop(evaluator->buffer);
  if (operand < -1 || operand > 1) {
    throw(RuntimeException, "the arcsine operand must be in the range [-1, 1]");
  }
  double result = asin(operand);
  double_stack_push(evaluator->buffer, result);

  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* cos_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    throw(RuntimeException, "the cosine needs one operand");
  }

  double operand = double_stack_pop(evaluator->buffer);
  double result = cos(operand);
  double_stack_push(evaluator->buffer, result);

  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* arccos_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    throw(RuntimeException, "the arccosine needs one operand");
  }

  double operand = double_stack_pop(evaluator->buffer);
  if (operand < -1 || operand > 1) {
    throw(RuntimeException, "the arccosine operand must be in the range [-1, 1]");
  }
  double result = asin(operand);
  double_stack_push(evaluator->buffer, result);

  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* tan_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    throw(RuntimeException, "the tangent needs one operand");
  }

  double operand = double_stack_pop(evaluator->buffer);
  double result = tan(operand);
  double_stack_push(evaluator->buffer, result);

  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* arctan_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    throw(RuntimeException, "the arctangent needs one operand");
  }

  double operand = double_stack_pop(evaluator->buffer);
  double result = atan(operand);
  double_stack_push(evaluator->buffer, result);

  return number_converter_convert_number_to_string(evaluator->converter, result);
}

char* recall_buffer_top_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    throw(RuntimeException, "trying to recall the buffer top when the buffer is empty");
  }

  double buffer_top = double_stack_top(evaluator->buffer);

  return number_converter_convert_number_to_string(evaluator->converter, buffer_top);
}

char* display_buffer_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    return clone_string("empty");
  }

  DoubleStack* buffer_clone = double_stack_clone(evaluator->buffer);
  char* result = number_converter_convert_number_to_string(evaluator->converter, double_stack_pop(buffer_clone));
  while (!double_stack_is_empty(buffer_clone)) {
    char* next_number_to_concat = number_converter_convert_number_to_string(evaluator->converter, double_stack_pop(buffer_clone));

    char* previous_state_of_result = result;
    result = concat_strings(3, result, "\n", next_number_to_concat);

    free(next_number_to_concat);
    free(previous_state_of_result);
  }
  double_stack_destroy(buffer_clone);

  return result;
}

char* clear_buffer_operation(Evaluator* evaluator) {
  double_stack_clear(evaluator->buffer);
  return clone_string("");
}

char* change_base_to_binary_operation(Evaluator* evaluator) {
  evaluator->converter = binary_number_converter;
  return clone_string("");
}

char* change_base_to_octal_operation(Evaluator* evaluator) {
  evaluator->converter = octal_number_converter;
  return clone_string("");
}

char* change_base_to_decimal_operation(Evaluator* evaluator) {
  evaluator->converter = decimal_number_converter;
  return clone_string("");
}

char* change_base_to_hexadecimal_operation(Evaluator* evaluator) {
  evaluator->converter = hexadecimal_number_converter;
  return clone_string("");
}

char* store_number_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    throw(RuntimeException, "the store_number operation needs one operand");
  }

  double number_to_store = double_stack_pop(evaluator->buffer);
  evaluator->stored_number = number_to_store;

  return clone_string("");
}

char* recall_stored_number_operation(Evaluator* evaluator) {
  return number_converter_convert_number_to_string(evaluator->converter, evaluator->stored_number);
}

char* change_stored_number_operation(Evaluator* evaluator) {
  if (double_stack_size(evaluator->buffer) < 1) {
    throw(RuntimeException, "the change_stored_number operation needs one operand");
  }

  double new_number_to_store = double_stack_pop(evaluator->buffer);
  evaluator->stored_number = new_number_to_store;

  return clone_string("");
}

char* evaluate_operation(Evaluator* evaluator, const char* name_of_operation) {
  if (strcmp(name_of_operation, "pi") == 0) {
    return pi_operation(evaluator);
  } else if (strcmp(name_of_operation, "euler") == 0) {
    return euler_operation(evaluator);
  } else if (strcmp(name_of_operation, "+") == 0) {
    return addition_operation(evaluator);
  } else if (strcmp(name_of_operation, "-") == 0) {
    return subtraction_operation(evaluator);
  } else if (strcmp(name_of_operation, "*") == 0) {
    return multiplication_operation(evaluator);
  } else if (strcmp(name_of_operation, "/") == 0) {
    return division_operation(evaluator);
  } else if (strcmp(name_of_operation, "^") == 0) {
    return exponentiation_operation(evaluator);
  } else if (strcmp(name_of_operation, "log") == 0) {
    return logarithm_operation(evaluator);
  } else if (strcmp(name_of_operation, "root") == 0) {
    return root_operation(evaluator);
  } else if (strcmp(name_of_operation, "!") == 0) {
    return factorial_operation(evaluator);
  } else if (strcmp(name_of_operation, "sin") == 0) {
    return sin_operation(evaluator);
  } else if (strcmp(name_of_operation, "arcsin") == 0) {
    return arcsin_operation(evaluator);
  } else if (strcmp(name_of_operation, "cos") == 0) {
    return cos_operation(evaluator);
  } else if (strcmp(name_of_operation, "arccos") == 0) {
    return arccos_operation(evaluator);
  } else if (strcmp(name_of_operation, "tan") == 0) {
    return tan_operation(evaluator);
  } else if (strcmp(name_of_operation, "arctan") == 0) {
    return arctan_operation(evaluator);
  } else if (strcmp(name_of_operation, "recall_buffer_top") == 0) {
    return recall_buffer_top_operation(evaluator);
  } else if (strcmp(name_of_operation, "display_buffer") == 0) {
    return display_buffer_operation(evaluator);
  } else if (strcmp(name_of_operation, "clear_buffer") == 0) {
    return clear_buffer_operation(evaluator);
  } else if (strcmp(name_of_operation, "change_base_to_binary") == 0) {
    return change_base_to_binary_operation(evaluator);
  } else if (strcmp(name_of_operation, "change_base_to_octal") == 0) {
    return change_base_to_octal_operation(evaluator);
  } else if (strcmp(name_of_operation, "change_base_to_decimal") == 0) {
    return change_base_to_decimal_operation(evaluator);
  } else if (strcmp(name_of_operation, "change_base_to_hexadecimal") == 0) {
    return change_base_to_hexadecimal_operation(evaluator);
  } else if (strcmp(name_of_operation, "store_number") == 0) {
    return store_number_operation(evaluator);
  } else if (strcmp(name_of_operation, "recall_stored_number") == 0) {
    return recall_stored_number_operation(evaluator);
  } else if (strcmp(name_of_operation, "change_stored_number") == 0) {
    return change_stored_number_operation(evaluator);
  } else {
    char* error_message = concat_strings(3, "'", name_of_operation, "' is not a supported operation");

    // try...finally needed because error_message is a heap-allocated string and needs to be
    // released, the throw copies error_message so it is safe to free error_message
    try {
      throw(RuntimeException, error_message);
    } finally {
      free(error_message);
    }
  }
}

char* evaluate_token(Evaluator* evaluator, Token* token) {
  switch (token_get_type(token)) {
    case NUMBER_TOKEN:
      return evaluate_number(evaluator, token_get_value(token));
    case OPERATION_TOKEN:
      return evaluate_operation(evaluator, token_get_value(token));
  }
}

char* evaluate_tokens(Evaluator* evaluator, TokenArray* tokens) {
  // result needs to be initially empty in case there are no tokens to evaluate
  char* result = clone_string("");

  int number_of_tokens = token_array_size(tokens);
  for (int i = 0; i < number_of_tokens; ++i) {
    // discard previous results because the result of the total expression will be the
    // result of the evaluation of the last subexpression
    free(result);

    DoubleStack* old_buffer_state = double_stack_clone(evaluator->buffer);
    try {
      result = evaluate_token(evaluator, token_array_get(tokens, i));
    } catch(RuntimeException) {
      double_stack_destroy(evaluator->buffer);
      evaluator->buffer = old_buffer_state;

      // preserve the original reason of the error and propagate it
      rethrow(e4c_get_exception()->message);
    }
    double_stack_destroy(old_buffer_state);
  }

  return result;
}

char* evaluator_evaluate(Evaluator* evaluator, const char* expression_to_evaluate) {
  char* result;

  TokenArray* tokens = tokenizer_tokenize(expression_to_evaluate);
  try {
    result = evaluate_tokens(evaluator, tokens);
  } finally {
    int number_of_tokens = token_array_size(tokens);
    for (int i = 0; i < number_of_tokens; ++i) {
      token_destroy(token_array_get(tokens, i));
    }
    token_array_destroy(tokens);
  }

  return result;
}
