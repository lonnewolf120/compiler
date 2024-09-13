%{
#include<stdio.h>
#include <bits/stdc++.h>

using namespace std;
//#define YYSTYPE double
#include "symboltable.h"
SymbolTable st;
extern FILE *yyin, *yyout;
extern int line_cnt;

int yylex();

void yyerror (const char *str)
{
printf("Error. %s \n", str);
}

%}

%union{
double dvar;
char *cvar;
}
 
%type <cvar>  CONST_INT CONST_FLOAT term expr_decl
%token NEWLINE LTHIRD RTHIRD LPAREN RPAREN LCURL RCURL COMMA
%token CONST_INT CONST_FLOAT INT FLOAT DOUBLE
%token <cvar> ID ADDOP SUBOP MULOP DIVOP ASSIGNOP SEMICOLON RELOP INCOP LOGICOP NOT


%left SUBOP
%left ADDOP
%left DIVOP
%left MULOP

%%

mul_stmt : mul_stmt func_decl
         | func_decl
         ;

func_decl : type_spec term LPAREN RPAREN LCURL stmt RCURL
          ;

stmt : stmt unit
     | unit
     ;

unit : var_decl NEWLINE 
     | expr_decl NEWLINE
     ;

var_decl : type_spec decl_list SEMICOLON
         ;

type_spec : INT 
          | FLOAT 
          | DOUBLE
          ;

term : ID    {
    st.insert($1, "ID");
    std::cout<< "ID" <<  $1 << std::endl;  
}
     ;

ass_list : term ASSIGNOP expr

expr: CONST_INT   {  }
    | CONST_FLOAT     {  }
    | expr MULOP expr {  }
    | expr DIVOP expr   {  }
    | expr ADDOP expr {  }
    | expr SUBOP expr   { }
    | term            
    ;

expr_decl : term ASSIGNOP expr SEMICOLON     
          ;

decl_list : decl_list COMMA term
          | decl_list COMMA term LTHIRD CONST_INT RTHIRD
          | term
          | term LTHIRD CONST_INT RTHIRD
          | ass_list
          ;

%%

int main(int argc, char *argv[]) {
    yyparse();
    clearOutput();
//    if(argc!=2){cerr<<"error taking input from file";}
    std::cout<<"Enter the input file name: ";
    char msg[20]; cin>>msg;
    std::cout<<"\nThe output will show in 202214024_log.txt & 202214024_token.txt\n\n";
    yyin = fopen(msg,"r");
    st.print();

    yylex();
    //fprintf(yyout,"Total lines: %d\n", line_cnt);
    logf(("\nTotal errors: " + to_string(error_cnt)));
    fclose(yyin);
    //fclose(yyout);
    return 0;
}
