%{
#include <stdio.h>
//#define YYSTYPE double
//instead of this we can have a union which will automatically be for YYSTYPE

int yylex();

void yyerror(const char* str){
    printf("Error");
}

extern FILE *yyin,*yyout;

%}


%union{
    double dvar;
    char  *cvar;
}


%type <dvar>expr
%token NEWLINE <dvar>NUMBER <cvar>ID
%left '+' '-'
%left '*' '/'

%%

stmt : stmt line {printf("multiple statements\n");}
| line 
;

line : expr NEWLINE {printf("res: %lf\n", $1);}
| ID NEWLINE        {printf("res: %s\n", $1);}
| error NEWLINE     {yyerrok;}
;

expr : expr '+' expr    {$$=$1 + $3;}
| expr '-' expr         {$$=$1 - $3;}
| expr '*' expr         {$$=$1 * $3;}
| expr '/' expr         {$$=$1 / $3;}
| NUMBER                
;

%%

int main(){
    yyparse();
}