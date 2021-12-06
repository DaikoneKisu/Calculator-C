#include "containers/array/token-array.h"

#include <stdio.h>
#include <stdlib.h>

#include "misc-utils/string-utils/string-utils.h"

struct TokenArray {
  Token** elements;
  int size;
};

TokenArray* token_array_create(int initial_size) {
  TokenArray* new_array = (TokenArray*) malloc(sizeof(TokenArray));

  if (initial_size != 0) {
    new_array->elements = (Token**) malloc(initial_size * sizeof(Token*));
  } else {
    new_array->elements = NULL;
  }
  new_array->size = initial_size;

  return new_array;
}

TokenArray* token_array_clone(TokenArray* array) {
  TokenArray* clone = token_array_create(array->size);

  memcpy(clone->elements, array->elements, sizeof(Token*) * array->size);

  return clone;
}

void token_array_destroy(TokenArray* array) {
  free(array->elements);
  free(array);
}

int token_array_size(TokenArray* array) {
  return array->size;
}

bool token_array_is_empty(TokenArray* array) {
  return array->size == 0;
}

Token* token_array_get(TokenArray* array, int index) {
  return array->elements[index];
}

void token_array_set(TokenArray* array, int index, Token* new_value) {
  array->elements[index] = new_value;
}

void token_array_push_back(TokenArray* array, Token* new_element) {
  token_array_resize(array, array->size + 1);
  array->elements[array->size - 1] = new_element;
}

void token_array_resize(TokenArray* array, int new_size) {
  if (new_size != 0) {
    array->elements = (Token**) realloc(array->elements, new_size*sizeof(Token*));
  } else {
    free(array->elements);
    array->elements = NULL;
  }
  array->size = new_size;
}

void token_array_clear(TokenArray* array) {
  token_array_resize(array, 0);
}
