CC = gcc
CFLAGS = -std=c11 -Iexternal/exceptions4c-3.0.5/src/ -Isrc/
LDLIBS = -lm

all_objects = $(src_folder_objects) $(external_folder_objects)

src_folder_objects = src/main.o $(calculator_folder_objects) $(ui_folder_objects) $(containers_folder_objects) $(misc_utils_folder)

calculator_folder_objects = src/calculator/calculator.o $(evaluator_folder_objects)
evaluator_folder_objects = src/calculator/evaluator/evaluator.o $(tokenizer_folder_objects)
tokenizer_folder_objects = src/calculator/evaluator/tokenizer/tokenizer.o src/calculator/evaluator/tokenizer/token.o

ui_folder_objects = src/ui/ui.o

containers_folder_objects = $(array_folder_objects) $(stack_folder_objects)
array_folder_objects = src/containers/array/token-array.o src/containers/array/double-array.o
stack_folder_objects = src/containers/stack/double-stack.o

misc_utils_folder = $(string_utils_folder_objects) $(number_converters_folder_objects)
string_utils_folder_objects = src/misc-utils/string-utils/string-utils.o
number_converters_folder_objects = src/misc-utils/number-converters/number-converters.o

external_folder_objects = $(exceptions4c_folder_objects)

exceptions4c_folder_objects = external/exceptions4c-3.0.5/src/e4c.o

build/calculator: $(all_objects)
	$(CC) -o build/calculator $(CFLAGS) $(all_objects) $(LDLIBS)

.PHONY = clean
clean:
	-rm $(all_objects)
