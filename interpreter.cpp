// Should be written in c++, but given a c interface for compatibility with the parser
//
// The interpreter needs to interpret tokens sent to the parser
// For function definitions, the functions bytecode needs to be stored in a list, and added to a dictionary
// For commands outside of function definitions, the commands need to be executed immediatly
// Commands come in the forms of:
// 		Push:
// 			pushes add new numbers to the stack
// 		Operations:
// 			operations manipulate the stack, such as multiplications and duplications
// 		Definitions:
//			definitions define a function
// 		Functions:
// 			functions are sets of operations to be performed in response to a keyword
// Pushes and Operations diectly translate into rpcalc functions
// Definitions and Functions call back to the interpreter
// When a definition command is interpreted, no other commands are executed until the end definition operator
// is found, and instead, are added to a function body.
// When a function identifier is interpreted, the commands in the function body are executed in the order they were added
