#include "calculator/evaluator/tokenizer/token.h"

#include <stdlib.h>

#include "misc-utils/string-utils/string-utils.h"

struct Token {
  TokenType type;
  char* value;
};

Token* token_create(TokenType type, const char* value) {
  Token* newly_created_token = (Token*) malloc(sizeof(Token));

  newly_created_token->type = type;
  newly_created_token->value = clone_string(value);

  return newly_created_token;
}

void token_destroy(Token* token) {
  free(token->value);
  free(token);
}

TokenType token_get_type(Token* token) {
  return token->type;
}

const char* token_get_value(Token* token) {
  return token->value;
}

void token_set_type(Token* token, TokenType new_type) {
  token->type = new_type;
}

void token_set_value(Token* token, const char* new_value) {
  token->value = clone_string(new_value);
}
