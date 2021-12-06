#include "misc-utils/number-converters/number-converters.h"

#include <math.h>
#include <stdlib.h>

#include "misc-utils/string-utils/string-utils.h"

enum {
  MAX_NUMBER_OF_FRACTIONAL_PLACES_IN_BINARY_CONVERSIONS = 6,
  MAX_NUMBER_OF_FRACTIONAL_PLACES_IN_OCTAL_CONVERSIONS = 6,
  MAX_NUMBER_OF_FRACTIONAL_PLACES_IN_DECIMAL_CONVERSIONS = 6,
  MAX_NUMBER_OF_FRACTIONAL_PLACES_IN_HEXADECIMAL_CONVERSIONS = 6
};

struct NumberConverter {
  char* (*convert_number_to_string) (double number);
  double (*convert_string_to_number) (const char* string);
};

char binary_values_mappings(int decimal_value_of_digit_in_binary) {
  switch (decimal_value_of_digit_in_binary) {
    case 0: return '0';
    case 1: return '1';
  }
}

char octal_values_mappings(int decimal_value_of_digit_in_octal) {
  switch (decimal_value_of_digit_in_octal) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
  }
}

char decimal_values_mappings(int decimal_value_of_digit_in_decimal) {
  switch (decimal_value_of_digit_in_decimal) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
  }
}

char hexadecimal_values_mappings(int decimal_value_of_digit_in_hexadecimal) {
  switch (decimal_value_of_digit_in_hexadecimal) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 10: return 'A';
    case 11: return 'B';
    case 12: return 'C';
    case 13: return 'D';
    case 14: return 'E';
    case 15: return 'F';
  }
}

char* convert_integer_part_to_string(double number, int destination_base, char (*destination_base_values_mappings)(int)) {
  if (number < 0) {
    char* result_without_sign = convert_integer_part_to_string(-number, destination_base, destination_base_values_mappings);
    char* result = concat_strings(2, "-", result_without_sign);
    free(result_without_sign);
    return result;
  }

  long long integer_part = trunc(number);
  if (integer_part == 0) {
    return clone_string("0");
  }
  int number_of_integer_digits_of_number_in_destination_base = ((int) (log10(number)/log10(destination_base))) + 1;

  char* result = create_empty_string_with_capacity_for_n_chars(number_of_integer_digits_of_number_in_destination_base);

  for (int i = number_of_integer_digits_of_number_in_destination_base - 1; i >= 0; --i) {
    int decimal_value_of_next_digit = integer_part % destination_base;
    char next_digit = destination_base_values_mappings(decimal_value_of_next_digit);
    result[i] = next_digit;
    integer_part /= destination_base;
  }

  return result;
}

char* convert_fractional_part_to_string(double number, int destination_base, int max_number_of_fractional_places, char (*destination_base_values_mappings)(int)) {
  if (max_number_of_fractional_places == 0) {
    return clone_string("");
  }

  char* result = create_empty_string_with_capacity_for_n_chars(max_number_of_fractional_places);

  double dummy;
  double fractional_part = fabs(modf(number, &dummy));
  int index_of_last_non_redundant_digit = -1;
  for (int i = 0; i < max_number_of_fractional_places; ++i) {
    int decimal_value_of_next_digit = trunc(fractional_part * destination_base);
    if (decimal_value_of_next_digit > 0) {
      index_of_last_non_redundant_digit = i;
    }

    char next_digit = destination_base_values_mappings(decimal_value_of_next_digit);
    result[i] = next_digit;

    fractional_part = modf(fractional_part * destination_base, &dummy);
  }
  result[index_of_last_non_redundant_digit + 1] = '\0';

  return result;
}

char* convert_number_to_binary_string(double number) {
  char* integer_part = convert_integer_part_to_string(number, 2, &binary_values_mappings);
  char* fractional_part = convert_fractional_part_to_string(number, 2, MAX_NUMBER_OF_FRACTIONAL_PLACES_IN_BINARY_CONVERSIONS, &binary_values_mappings);
  char* result;
  if (strlen(fractional_part) == 0) {
    result = integer_part;
    integer_part = NULL;
  } else {
    result = concat_strings(3, integer_part, ".", fractional_part);
  }

  free(integer_part);
  free(fractional_part);
  return result;
}

char* convert_number_to_octal_string(double number) {
  char* integer_part = convert_integer_part_to_string(number, 8, &octal_values_mappings);
  char* fractional_part = convert_fractional_part_to_string(number, 8, MAX_NUMBER_OF_FRACTIONAL_PLACES_IN_OCTAL_CONVERSIONS, &octal_values_mappings);
  char* result;
  if (strlen(fractional_part) == 0) {
    result = integer_part;
    integer_part = NULL;
  } else {
    result = concat_strings(3, integer_part, ".", fractional_part);
  }

  free(integer_part);
  free(fractional_part);
  return result;
}

char* convert_number_to_decimal_string(double number) {
  char* integer_part = convert_integer_part_to_string(number, 10, &decimal_values_mappings);
  char* fractional_part = convert_fractional_part_to_string(number, 10, MAX_NUMBER_OF_FRACTIONAL_PLACES_IN_DECIMAL_CONVERSIONS, &decimal_values_mappings);
  char* result;
  if (strlen(fractional_part) == 0) {
    result = integer_part;
    integer_part = NULL;
  } else {
    result = concat_strings(3, integer_part, ".", fractional_part);
  }

  free(integer_part);
  free(fractional_part);
  return result;
}

char* convert_number_to_hexadecimal_string(double number) {
  char* integer_part = convert_integer_part_to_string(number, 16, &hexadecimal_values_mappings);
  char* fractional_part = convert_fractional_part_to_string(number, 16, MAX_NUMBER_OF_FRACTIONAL_PLACES_IN_HEXADECIMAL_CONVERSIONS, &hexadecimal_values_mappings);
  char* result;
  if (strlen(fractional_part) == 0) {
    result = integer_part;
    integer_part = NULL;
  } else {
    result = concat_strings(3, integer_part, ".", fractional_part);
  }

  free(integer_part);
  free(fractional_part);
  return result;
}

char* number_converter_convert_number_to_string(NumberConverter* converter, double number) {
  return converter->convert_number_to_string(number);
}

int binary_digits_mappings(char binary_digit) {
  switch (binary_digit) {
    case '0': return 0;
    case '1': return 1;
  }
}

int octal_digits_mappings(char octal_digit) {
  switch (octal_digit) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
  }
}

int decimal_digits_mappings(char decimal_digit) {
  switch (decimal_digit) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
  }
}

int hexadecimal_digits_mappings(char hexadecimal_digit) {
  switch (hexadecimal_digit) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a':
    case 'A': return 10;
    case 'b':
    case 'B': return 11;
    case 'c':
    case 'C': return 12;
    case 'd':
    case 'D': return 13;
    case 'e':
    case 'E': return 14;
    case 'f':
    case 'F': return 15;
  }
}

double convert_integer_part_of_string_to_number(const char* string, int original_base, int (*original_base_digits_mappings)(char)) {
  if (string[0] == '-') {
    double result_without_sign = convert_integer_part_of_string_to_number(&string[1], original_base, original_base_digits_mappings);
    return -result_without_sign;
  } else if (string[0] == '+') {
    return convert_integer_part_of_string_to_number(&string[1], original_base, original_base_digits_mappings);
  }

  int floating_point_index = index_of_first_occurrence_of('.', string);

  double result = 0.0;
  int starting_index = floating_point_index == -1 ? strlen(string) - 1 : floating_point_index - 1;
  int integer_places_processed = 0;
  for (int i = starting_index; i >= 0; --i) {
    int decimal_value_of_next_digit = original_base_digits_mappings(string[i]);
    result += decimal_value_of_next_digit * pow(original_base, integer_places_processed);
    ++integer_places_processed;
  }

  return result;
}

double convert_fractional_part_of_string_to_number(const char* string, int original_base, int (*original_base_digits_mappings)(char)) {
  if (string[0] == '-') {
    double result_without_sign = convert_fractional_part_of_string_to_number(&string[1], original_base, original_base_digits_mappings);
    return -result_without_sign;
  }

  int floating_point_position = index_of_first_occurrence_of('.', string);

  if (floating_point_position == -1) {
    return 0.0;
  }

  double result = 0.0;
  int fractional_places_processed = 0;
  for (int i = floating_point_position + 1; i < strlen(string); ++i) {
    int decimal_value_of_next_digit = original_base_digits_mappings(string[i]);
    result += decimal_value_of_next_digit / pow(original_base, fractional_places_processed + 1);
    ++fractional_places_processed;
  }

  return result;
}

double convert_binary_string_to_number(const char* string) {
  double integer_part = convert_integer_part_of_string_to_number(string, 2, &binary_digits_mappings);
  double fractional_part = convert_fractional_part_of_string_to_number(string, 2, &binary_digits_mappings);
  return integer_part + fractional_part;
}

double convert_octal_string_to_number(const char* string) {
  double integer_part = convert_integer_part_of_string_to_number(string, 8, &octal_digits_mappings);
  double fractional_part = convert_fractional_part_of_string_to_number(string, 8, &octal_digits_mappings);
  return integer_part + fractional_part;
}

double convert_decimal_string_to_number(const char* string) {
  double integer_part = convert_integer_part_of_string_to_number(string, 10, &decimal_digits_mappings);
  double fractional_part = convert_fractional_part_of_string_to_number(string, 10, &decimal_digits_mappings);
  return integer_part + fractional_part;
}

double convert_hexadecimal_string_to_number(const char* string) {
  double integer_part = convert_integer_part_of_string_to_number(string, 16, &hexadecimal_digits_mappings);
  double fractional_part = convert_fractional_part_of_string_to_number(string, 16, &hexadecimal_digits_mappings);
  return integer_part + fractional_part;
}

double number_converter_convert_string_to_number(NumberConverter* converter, const char* string) {
  return converter->convert_string_to_number(string);
}

NumberConverter internal_binary_number_converter = {
  .convert_number_to_string = &convert_number_to_binary_string,
  .convert_string_to_number = &convert_binary_string_to_number
};
NumberConverter* const binary_number_converter = &internal_binary_number_converter;

NumberConverter internal_octal_number_converter = {
  .convert_number_to_string = &convert_number_to_octal_string,
  .convert_string_to_number = &convert_octal_string_to_number
};
NumberConverter* const octal_number_converter = &internal_octal_number_converter;

NumberConverter internal_decimal_number_converter = {
  .convert_number_to_string = &convert_number_to_decimal_string,
  .convert_string_to_number = &convert_decimal_string_to_number
};
NumberConverter* const decimal_number_converter = &internal_decimal_number_converter;

NumberConverter internal_hexadecimal_number_converter = {
  .convert_number_to_string = &convert_number_to_hexadecimal_string,
  .convert_string_to_number = &convert_hexadecimal_string_to_number
};
NumberConverter* const hexadecimal_number_converter = &internal_hexadecimal_number_converter;
