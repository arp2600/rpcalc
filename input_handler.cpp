extern "C"
{
#include "input_handler.h"
}
#include "stdlib.h"
#include <string>
#include <vector>

std::vector<std::string> _line_history;
std::string _line_buffer;

void init_input_handler ()
{
	system("/bin/stty raw");
}

// returns -1 once _line_buffer has been read
int purge_buffer ()
{
	if (_line_buffer.length() == 0)
		return -1;
	
	// Read the buffer back character by character
	static int index = 0;
	if (index < _line_buffer.length())
		return _line_buffer.at(index++);

	// Clear the line buffer and return the new line character
	_line_buffer.clear();
	index = 0;
	return '\n';
}

int use_history (int index)
{
	if (_line_history.size() == 0)
		return 0;

	// Delete the characters in the terminal and the line buffer
	for (int i=0; i<_line_buffer.size(); i++)
		printf("\b \b");
	_line_buffer.clear();

	// Bounds check the index
	if (index < 1)
		index = 1;
	else if (index > _line_history.size())
		index = _line_history.size();

	_line_buffer = _line_history[_line_history.size() - index];
	printf("%s", _line_buffer.c_str());

	return index;
}

int read_input ()
{
	static int history_index = 0;

	while (true)
	{
		int c = getchar();
		if (c == 3) // Terminate program ctrl-C
			return 3;
		else if (c == 13) // New line
		{
			printf("\n\r");
			history_index = 0;
			break;
		}
		else if (c == 27) // Arrow keys
		{
			c = getchar();
			if (c == 91)
			{
				c = getchar();
				
				if (c == 65 || c == 66)
				{
					int i = history_index;
					if (c == 65) // Up and Down arrow keys
						i = use_history(++history_index);
					else if (c == 66)
						i = use_history(--history_index);
					history_index = i;
				}
			}
		}
		else if (c == 127) // backspace
		{
			if (_line_buffer.size() > 0)
			{
				printf("\b \b");
				_line_buffer.pop_back();
			}
		}
		else if (c > 31) // Printable character
		{
			_line_buffer.push_back(c);
			printf("%c", c);
		}
	}

	return 0;
}

// Return the next character from the user
int getch ()
{
	while (true)
	{
		// Purge any characters remaining in the buffer from the previous line
		int c = purge_buffer();
		if (c > 0)
			return c;

		// Read the input
		c = read_input();
		switch (c)
		{
			case 3: // End of program
				return -1;
			case 13: // New line
				break;
		}

		_line_history.push_back(_line_buffer);
	}
}

void end_input_handler ()
{
	system("/bin/stty sane");
}
