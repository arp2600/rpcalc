%option noyywrap
%{
#include "parser.tab.h"
#define RETURN_OP { yylval.string = strdup(yytext); return OPERATION; }

int get_input (char *buf, int max_size);

#define YY_INPUT(buf,result,max_size) result = get_input(buf,max_size)

%}

%%

 /* Operations */
"+"|"-"|"*"|"/"|"%"|"^"				RETURN_OP
(sin|cos|tan)(h)?					RETURN_OP
rnd|sqrt|dup|swap					RETURN_OP
"dump"|"exit" 						RETURN_OP
"."									RETURN_OP

 /* Identifiers */
[a-zA-Z_][a-zA-Z0-9_]*				{ yylval.string = strdup(yytext); return IDENTIFIER; }
 /* Numbers */
[0-9]+("."[0-9]*)?					{ yylval.number = atof(yytext); return NUMBER; }

":"									{ return ':'; }
";"									{ return ';'; }
\n									{ return '\n'; }

 /* Ignore whitespace */
[ \t]								;

 /* Ignore unknown characters */
 .									{ printf("Unrecognized token '%s'\n", yytext); }

%%

int get_input (char *buf, int max_size)
{
	int c = getchar();
	return (c == EOF) ? YY_NULL : (buf[0] = c, 1);
}
