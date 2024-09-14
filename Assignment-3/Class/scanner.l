%option noyywrap
%{
#include "parser.tab.h"
#include<stdlib.h>
%}

WS [ \t]
DIGITS [0-9]+
FLOATING_NUM {DIGITS}(\.{DIGITS})?


%%

[\n]			{return NEWLINE;}
{WS}			{}
{FLOATING_NUM}	{
			//sscanf(yytext, "%lf", &yylval);
				yylval.dvar=atof(yytext);
				return NUMBER;}
[+*/]			{return *yytext;}
[-]				{return SUB;}	
[A-Za-z]+		{yylval.cvar=yytext;
				return ID;}

%%