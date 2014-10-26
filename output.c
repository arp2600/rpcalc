#include "output.h"
#include "stdio.h"
#include "string.h"

void print_line_start ()
{
	char *line_start = ":> ";
	printf("%s", COLOR_BLUE); 
	printf("%s", line_start);
	printf("%s", COLOR_RESET);
}

void print_double(double value, const char* color)
{
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
	printf("\n\r");
}

void print_delete ()
{
	printf("\b \b");
}
