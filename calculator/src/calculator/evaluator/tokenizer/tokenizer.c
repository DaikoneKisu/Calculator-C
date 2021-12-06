#include "calculator/evaluator/tokenizer/tokenizer.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "e4c.h"
#include "misc-utils/string-utils/string-utils.h"

bool only_contains_digits_or_floating_points(const char* string) {
  int string_length = strlen(string);
  for (int i = 0; i < string_length; ++i) {
    if (!isdigit(string[i]) && string[i] != '.') {
      return false;
    }
  }
  return true;
}

bool if_there_is_a_floating_point_it_is_unique(const char* string) {
  int string_length = strlen(string);
  int number_of_floating_points = 0;
  for (int i = 0; i < string_length; ++i) {
    if (string[i] == '.') {
      ++number_of_floating_points;
    }
  }
  return number_of_floating_points < 2;
}

bool if_there_is_a_floating_point_it_is_correctly_placed(const char* string) {
  int floating_point_index = index_of_first_occurrence_of('.', string);
  if (floating_point_index != -1) {
    return 0 < floating_point_index && floating_point_index < (strlen(string) - 1);
  }
  return true;
}

bool is_number(const char* string) {
  if (string[0] == '+' || string[0] == '-') {
    if (strlen(string) > 1) {
      return is_number(&string[1]);
    }
    return false;
  }
  return only_contains_digits_or_floating_points(string) &&
    if_there_is_a_floating_point_it_is_unique(string) &&
    if_there_is_a_floating_point_it_is_correctly_placed(string);
}

bool is_a_valid_identifier(const char* string) {
  int string_length = strlen(string);
  if (!isalpha(string[0])) {
    return false;
  }
  for (int i = 0; i < string_length; ++i) {
    if (!isalnum(string[i]) && string[i] != '_') {
      return false;
    }
  }
  return true;
}

bool is_an_arithmetic_symbol(const char* string) {
  if (strcmp(string, "+") == 0) {
    return true;
  } else if (strcmp(string, "-") == 0) {
    return true;
  } else if (strcmp(string, "*") == 0) {
    return true;
  } else if (strcmp(string, "/") == 0) {
    return true;
  } else if (strcmp(string, "^") == 0) {
    return true;
  } else if (strcmp(string, "!") == 0) {
    return true;
  } else {
    return false;
  }
}

bool is_operation(const char* string) {
  return is_a_valid_identifier(string) || is_an_arithmetic_symbol(string);
}

Token* create_a_token_with_value(const char* value) {
  if (is_number(value)) {
    return token_create(NUMBER_TOKEN, value);
  } else if (is_operation(value)) {
    return token_create(OPERATION_TOKEN, value);
  } else {
    char* error_message = concat_strings(3, "'", value, "' is not a valid token");

    // try...finally needed because error_message is a heap-allocated string and needs to be
    // released, the throw copies error_message so it is safe to free error_message
    try {
      throw(RuntimeException, error_message);
    } finally {
      free(error_message);
    }
  }
}

TokenArray* tokenizer_tokenize(const char* expression_to_tokenize){
  TokenArray* tokens = token_array_create(0);
  char* expression_to_tokenize_clone = clone_string(expression_to_tokenize);

  try {
    char* current_token_value = strtok(expression_to_tokenize_clone, " ");
    while (current_token_value != NULL) {
      Token* current_token = create_a_token_with_value(current_token_value);
      token_array_push_back(tokens, current_token);

      current_token_value = strtok(NULL, " ");
    }
  } catch(RuntimeException) {
    token_array_destroy(tokens);

    // rethrow conserving the original message
    rethrow(e4c_get_exception()->message);
  } finally {
    free(expression_to_tokenize_clone);
  }

  return tokens;
}
