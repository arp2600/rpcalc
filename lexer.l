%option noyywrap
%{
#include "parser.tab.h"

int line_num = 0;
%}

%%

 /* The binary operators of the language */
"+"|"-"|"*"|"/"|"%"|"^" 			{ yylval.v_string = strdup(yytext); return BINOP; }
sin|cos|tan							{ yylval.v_string = strdup(yytext); return UNOP; }
"dump"|"exit" 						{ yylval.v_string = strdup(yytext); return ACTION; }

kilo								{ yylval.v_float = 1000; return NUM; }
mill								{ yylval.v_float = 1000000; return NUM; }
bill 								{ yylval.v_float = 1000000000; return NUM; }

miles2km							{ yylval.v_float = 1.609344; return NUM; }
pi									{ yylval.v_float = 3.14159265359; return NUM; }
phi									{ yylval.v_float = 1.61803398875; return NUM; }

 /* Ignore whitespace but count new lines */
[ \t]								;
[\n]								{ ++line_num; return '\n'; }

 /* Identifiers and Integers */
 /* [a-zA-Z_][a-zA-Z0-9_]*	{ yylval.v_string = strdup(yytext); return IDENTIFIER; } */
[0-9]+("."[0-9]*)?					{ yylval.v_float = atof(yytext); return NUM; }

 /* .                       { printf("Unknown token!\n"); yyterminate(); } */

%%
