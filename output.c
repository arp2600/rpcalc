#include "output.h"
#include "stdio.h"
#include "string.h"

int _volume = 1; // 1 prints, 0 doesn't

void print_line_start ()
{
	if (!_volume)
		return;

	char *line_start = ":> ";
	printf("%s", COLOR_BLUE); 
	printf("%s", line_start);
	printf("%s", COLOR_RESET);
}

void print_double(double value, const char* color)
{
	if (!_volume)
		return;

	char string[64];
	snprintf(string, 64, "%f", value);
	char *dot = strchr(string, '.');
	if (dot != 0)
	{
		for (int i=strlen(string)-1; i > 0; i--)
		{
			if (string[i] != '0')
			{
				if (string[i] == '.')
					string[i] = '\0';
				break;
			}
			else
				string[i] = '\0';
		}
	}
	printf("%s", color);
	printf("%s", string);
	printf(COLOR_RESET);
}

void print_newline ()
{
	if (!_volume)
		return;

	printf("\n\r");
}

void print_delete ()
{
	if (!_volume)
		return;

	printf("\b \b");
}

void suppress_output (int volume)
{
	_volume = volume;
}

