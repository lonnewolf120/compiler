%{
#include<stdlib.h>
#include<stdio.h>
#include <bits/stdc++.h>
using namespace std;
#include "symboltable2.h"

extern FILE *yyin, *yyout;
extern int line_cnt;
// int line_cnt=1, error_cnt=0;

// ofstream outFile("logerror.txt");  

int yylex();

SymbolTable st;

void fcout(string token, string symbol="") {
    ofstream op2;
    op2.open("token.txt", ios::app);
    if (!op2.is_open()) {
        cerr << "Error opening file.\n";
    }
    (symbol=="")?op2<<"<"<<token<<">": op2<<"<"<<token<<", "<<symbol<<">";
    op2.close();
}

// void log_token(string msg=""){
//     ofstream output;
//     output.open("log.txt", ios::app);
//     output<<msg;
//     output.close();
// }
void log_error(const char *msg=""){
    fprintf(yyout, "Line Number: %d\n", line_cnt);
    fprintf(yyout, "%s", msg);
}

void yyerror (const char *str) {
    fprintf(yyout, "%s\n", str);
}


/*explanation for ffcout:
int c is used to say how text will be added into output, 
0 for normal <Token, Lexeme> found
other values for "already exists" type of stuff...
*/
void ffcout(string token, string symbol="", int c=0){
    ofstream output;
    output.open("log_error.txt", ios::app);
    if (!output.is_open()) {
        cerr << "Error opening log_error.txt file.\n";
    }
    
    output << "Line No: " << line_cnt << " ";
    output << "Token <" << token << "> Lexeme " << symbol << " found\n";
    if(c){
        if (token=="ID") {
        output << symbol << " variable already exists\n";
        } else if (token=="CONST_INT" || token=="CONST_FLOAT") {
            output << symbol << " value already exists\n";
        } else if (token=="CONST_CHAR") {
            output << symbol << " character already exists\n";
        }
    } 
    output.close();
}



void clearOutput() {
    ofstream output;
    output.open("log_error.txt", ios::trunc);
    if (!output.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    output.close();
    output.open("log.txt", ios::trunc);
    if (!output.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    output.close();
}

%}

%union{
int ivar;
double dvar;
char *cvar;
}
 
%type <cvar> expr term 
%type <cvar> ID
%token LTHIRD RTHIRD LPAREN RPAREN LCURL RCURL COMMA ID ADDOP SUBOP MULOP DIVOP MODOP ASSIGNOP SEMICOLON RELOP INCOP DECOP LOGICOP NOT CONST_INT CONST_FLOAT INT FLOAT DOUBLE CHAR
%token IF ELSE FOR WHILE RETURN BREAK CONTINUE VOID
%type <dvar> CONST_FLOAT
%type <ivar> CONST_INT 
/* %type <cvar> type_spec decl_list var */

%left LOGICOP
%left ADDOP SUBOP
%left MULOP DIVOP

%right ASSIGNOP 

%%

line: mul_stmt  
    |stmt  
    ;

stmt : stmt unit { log_error("stmt : stmt unit\n");}
     | unit {log_error("stmt : unit\n"); }
     ;

unit : var_decl  { log_error("unit : var_decl\n"); }
     | expr_decl  { log_error("unit : expr_decl\n"); }
     | error {yyerrok;log_error(""); yyerror("syntax error: invalid expression");}
     ;

func_decl : type_spec term LPAREN RPAREN LCURL stmt RCURL {log_error("func_decl : type_spec term LPAREN RPAREN LCURL stmt RCURL\n"); }
          ;



mul_stmt : mul_stmt func_decl 
         | func_decl
         ;

var_decl : type_spec decl_list SEMICOLON {log_error("vardecl : type_spec dec_list SEMICOLON\n"); }
         ;

type_spec : INT {log_error("type_spec : INT\n");}
          | FLOAT {log_error("type_spec : FLOAT\n");}
          | DOUBLE {log_error("type_spec : DOUBLE\n");}
          ;

decl_list : decl_list COMMA term {log_error("dec_list : dec_list COMMA term\n");}
| decl_list COMMA term LTHIRD CONST_INT RTHIRD {log_error("dec_list : dec_list COMMA term LTHIRD CONST_INT RTHIRD\n"); }
| term {log_error("dec_list : term\n");}
| term LTHIRD CONST_INT RTHIRD { log_error("dec_list : term LTHIRD CONST_INT RTHIRD\n"); }
| ass_list {log_error("dec_list : asslist\n");}
;


expr_decl : term ASSIGNOP expr SEMICOLON  {log_error("expr_decl : term ASSIGNOP expr SEMICOLON\n");}   
;

ass_list : term ASSIGNOP expr {log_error(" asslist : term ASSIGNOP expr\n");}
;

expr : CONST_INT   { log_error("expr : CONST_INT \n"); }
     | CONST_FLOAT { log_error("expr : CONST_FLOAT \n"); }
     | expr MULOP expr { log_error("expr : expr MULOP expr \n"); }
     | expr DIVOP expr { log_error("expr : expr DIVOP expr \n"); }
     | expr ADDOP expr { log_error("expr : expr ADDOP expr \n"); }
     | expr SUBOP expr { log_error("expr : expr SUBOP expr \n"); }
     | expr LOGICOP expr { log_error("expr : expr LOGICOP expr \n"); }
     | LPAREN expr RPAREN { log_error("expr : LPAREN expr RPAREN  \n"); }
     | term { log_error("expr : term \n"); }
     ;


term : ID {
    if (!(st.insert(string($1), "identifier", line_cnt))) {
        fprintf(yyout, "%s is already declared\n", (char*)($1));
    }else{
        log_error("term: ID\n");
    }
}  
;

%%

int main() 
{
  st.clear();
  clearOutput();
  yyin=fopen("input.txt","r");
  yyout=fopen("log_error.txt","w");
  yyparse(); 
  st.print();
 
  return 0;
}
