%{
#include<stdio.h>
//#define YYSTYPE double
extern FILE *yyin, *yyout;

int yylex();

void yyerror (const char *str)
{
printf("Error. %s \n", str);
}

%}

%union{
double dvar;
char *cvar;}

%type <dvar>expr
%token <dvar>NUMBER 
%token NEWLINE
%token <cvar>ID
%left '+' SUB
%left '*' '/'

%%
stmt: stmt line
| line
;

line: expr NEWLINE		{printf("Correct Syntax. %lf \n", $1);}
|ID NEWLINE 			{printf("Correct Syntax. %s \n", $1);}
|error NEWLINE			{yyerrok;}
;

expr : expr '+' expr	{$$=$1+$3;}
| expr SUB expr			{$$=$1-$3;}
| expr '*' expr			{$$=$1*$3;}
| expr '/' expr			{if($3==0) yyerror("Div by 0");
						else $$=$1/$3;}
| NUMBER
;

%%

main()
{
yyparse();
}