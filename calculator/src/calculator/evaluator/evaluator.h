#ifndef CALCULATOR_EVALUATOR_EVALUATOR_H
#define CALCULATOR_EVALUATOR_EVALUATOR_H

typedef struct Evaluator Evaluator;

Evaluator* evaluator_create(void);
void evaluator_destroy(Evaluator* evaluator);

char* evaluator_evaluate(Evaluator* evaluator, const char* expression_to_evaluate);

#endif
