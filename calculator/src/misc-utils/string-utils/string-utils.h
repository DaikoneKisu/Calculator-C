#ifndef MISC_UTILS_STRING_UTILS_STRING_UTILS_H
#define MISC_UTILS_STRING_UTILS_STRING_UTILS_H

#include <string.h>

char* create_empty_string_with_capacity_for_n_chars(int n);
char* clone_string(const char* string);
char* concat_strings(int number_of_strings_to_concat, ...);
int index_of_first_occurrence_of(char char_to_search, const char* string);

#endif
