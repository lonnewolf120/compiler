%option noyywrap
%{

#include <stdio.h>

#include "SymbolTable.h"
#define YYSTYPE SymbolInfo
#include "generator.tab.h"
void yyerror(const char* str);

%}

%%
[ \t\n]+ 	{}
[0-9]+   	{
				SymbolInfo obj(yytext, "NUM");
				yylval = obj;
				return NUM;}
[_A-Za-z]+ 	{
				SymbolInfo obj(yytext, "ID");
				yylval = obj;	
				return ID;
			}
[-+=;()]	{return *yytext;}
. 			{
				yyerror("error\n");
			}


%%