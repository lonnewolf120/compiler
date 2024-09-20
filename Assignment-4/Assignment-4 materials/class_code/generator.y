%{
#include<stdio.h>
#include<stdlib.h>
#include "SymbolTable.h"
#define YYSTYPE SymbolInfo

int yylex();
extern FILE* yyout; 

int temp_counter=1;
void yyerror(const char* str){
		printf("Error: %s\n", str);
	}
	
char* newTemp(){
	char* temp;
	temp = (char*) malloc(15*sizeof(char));
	sprintf(temp, "t%d", temp_counter);
	temp_counter++;
	return temp;
}

%}

%token ID NUM '(' ')' ';'
%left '+' '-'
%right '='

%%

stmt: line				{}
| stmt line				{}

;

line: ID '=' expr ';'	{
	printf("%s = %s\n", $1.getSymbol().c_str(), $3.getSymbol().c_str() );
	temp_counter=1;
}
;

expr: expr '+' expr		{
	char* str = newTemp();
	SymbolInfo obj(str, "TempID");
	$$ = obj;
	cout<<$$.getSymbol()<<" = " << $1.getSymbol() << "+" << $3.getSymbol()<<endl;

	// ASM Code
	fprintf(yyout, "MOV AX, %s\n", $1.getSymbol().c_str());
	fprintf(yyout, "MOV BX, %s\n", $3.getSymbol().c_str());
	fprintf(yyout, "ADD AX, BX\n");
	fprintf(yyout, "MOV %s, AX\n\n", $$.getSymbol().c_str());
}

| expr '-' expr			{
	char* str = newTemp();
	SymbolInfo obj(str, "TempID");
	$$ = obj;
	cout<<$$.getSymbol()<<" = " << $1.getSymbol() << "-" << $3.getSymbol()<<endl;
	
	// ASM Code
	fprintf(yyout, "MOV AX, %s\n", $1.getSymbol().c_str());
	fprintf(yyout, "MOV BX, %s\n", $3.getSymbol().c_str());
	fprintf(yyout, "SUB AX, BX\n");
	fprintf(yyout, "MOV %s, AX\n\n", $$.getSymbol().c_str());
}
| '(' expr ')'			{ $$ = $2; }
| ID					{}
| NUM					{}
;

%%

int main(){
	yyout = fopen("asm.txt", "w");
	yyparse();
}
