#ifndef MISC_UTILS_NUMBER_CONVERTERS_NUMBER_CONVERTERS_H
#define MISC_UTILS_NUMBER_CONVERTERS_NUMBER_CONVERTERS_H

typedef struct NumberConverter NumberConverter;

char* number_converter_convert_number_to_string(NumberConverter* converter, double number_to_convert);
double number_converter_convert_string_to_number(NumberConverter* converter, const char* string_to_convert);

extern NumberConverter* const binary_number_converter;
extern NumberConverter* const octal_number_converter;
extern NumberConverter* const decimal_number_converter;
extern NumberConverter* const hexadecimal_number_converter;

#endif
