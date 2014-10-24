#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

void interpret_operation (char *op_name, int perform);	// Handling operations
void interpret_number (double number, int perform);	// Handling numbers
void interpret_func_definition (char *func_name);	// Function definitios
void interpret_func_call (char *func_name, int perform);	// Function calls
void interpret_end_of_func ();	// Function end

#endif
