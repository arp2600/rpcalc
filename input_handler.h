#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

void init_input_handler ();
int getch (); // Return the next character from the user
void end_input_handler ();
void read_file (const char *path); // Stop reading stdin and read file at path

#endif
