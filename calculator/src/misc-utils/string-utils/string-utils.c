#include "misc-utils/string-utils/string-utils.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char* create_empty_string_with_capacity_for_n_chars(int n) {
  return (char*) calloc(n + 1, sizeof(char));
}

char* clone_string(const char* string) {
  char* clone = (char*) malloc(sizeof(char) * (strlen(string) + 1));
  strcpy(clone, string);
  return clone;
}

char* concat_strings(int number_of_strings_to_concat, ...) {
  va_list strings_to_concat;
  va_start(strings_to_concat, number_of_strings_to_concat);

  va_list copy_of_strings_to_concat;
  va_copy(copy_of_strings_to_concat, strings_to_concat);

  int length_of_resulting_string = 0;
  for (int i = 0; i < number_of_strings_to_concat; ++i) {
    const char* current_string = va_arg(copy_of_strings_to_concat, const char*);
    length_of_resulting_string += strlen(current_string);
  }
  va_end(copy_of_strings_to_concat);

  char* resulting_string = create_empty_string_with_capacity_for_n_chars(length_of_resulting_string + 1);
  for (int i = 0; i < number_of_strings_to_concat; ++i) {
    const char* current_string = va_arg(strings_to_concat, const char*);
    strcat(resulting_string, current_string);
  }
  va_end(strings_to_concat);

  return resulting_string;
}

int index_of_first_occurrence_of(char char_to_search, const char* string) {
  const char* first_occurrence_of_char_to_search_in_string = strchr(string, char_to_search);
  
  if (first_occurrence_of_char_to_search_in_string == NULL) {
    return -1;
  }

  return first_occurrence_of_char_to_search_in_string - string;
}
