#ifndef CONTAINERS_ARRAY_TOKEN_ARRAY_H
#define CONTAINERS_ARRAY_TOKEN_ARRAY_H

#include <stdbool.h>

#include "calculator/evaluator/tokenizer/token.h"

typedef struct TokenArray TokenArray;

TokenArray* token_array_create(int initial_size);
TokenArray* token_array_clone(TokenArray* array);
void token_array_destroy(TokenArray* array);

int token_array_size(TokenArray* array);
bool token_array_is_empty(TokenArray* array);

Token* token_array_get(TokenArray* array, int index);
void token_array_set(TokenArray* array, int index, Token* new_value);

void token_array_push_back(TokenArray* array, Token* new_element);

void token_array_resize(TokenArray* array, int new_size);

void token_array_clear(TokenArray* array);

#endif
