#ifndef CALCULATOR_EVALUATOR_TOKENIZER_TOKEN_H
#define CALCULATOR_EVALUATOR_TOKENIZER_TOKEN_H

typedef struct Token Token;

typedef enum {
  NUMBER_TOKEN, OPERATION_TOKEN
} TokenType;

Token* token_create(TokenType type, const char* value);
void token_destroy(Token* token);

TokenType token_get_type(Token* token);
const char* token_get_value(Token* token);

void token_set_type(Token* token, TokenType new_type);
void token_set_value(Token* token, const char* new_value);

#endif
