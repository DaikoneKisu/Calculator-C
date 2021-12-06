#include "ui/ui.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "misc-utils/string-utils/string-utils.h"

void flush_buffer_contents_into(char** dest, const char* buffer, int buffer_size) {
  char* old_state_of_dest = *dest;

  int original_size_of_dest = strlen(*dest);
  *dest = create_empty_string_with_capacity_for_n_chars(original_size_of_dest + buffer_size);
  strcat(*dest, old_state_of_dest);
  strncat(*dest, buffer, buffer_size);

  free(old_state_of_dest);
}

char* ui_read(void) {
  char* input_line = clone_string("");

  ui_write("calculator> ");

  enum { BUFFER_SIZE = 100 };
  char buffer[BUFFER_SIZE] = {};
  int chars_written_in_buffer = 0;
  for (char last_char_read = getchar(); last_char_read != '\n' && last_char_read != EOF; last_char_read = getchar()) {
    buffer[chars_written_in_buffer] = last_char_read;
    ++chars_written_in_buffer;

    if (chars_written_in_buffer == BUFFER_SIZE) {
      flush_buffer_contents_into(&input_line, buffer, BUFFER_SIZE);
    }
  }
  flush_buffer_contents_into(&input_line, buffer, chars_written_in_buffer);

  return input_line;
}

void ui_write(const char* format, ...) {
  va_list extra_arguments;
  va_start(extra_arguments, format);

  vprintf(format, extra_arguments);

  va_end(extra_arguments);
}
