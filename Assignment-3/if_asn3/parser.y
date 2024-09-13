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
SymbolTable st;


int yylex();

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
void log_error(string msg=""){
    ofstream output;
    output.open("log_error.txt", ios::app);
    output<<"Line Number: "<< line_cnt <<"\n";
    output<<msg;
    output.close();
}


void yyerror (const char *str) {
    ofstream output;
    output.open("log_error.txt", ios::app);
    output << str << "\n";
    output.close();
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
%token NEWLINE LTHIRD RTHIRD LPAREN RPAREN LCURL RCURL COMMA ID ADDOP SUBOP MULOP DIVOP ASSIGNOP SEMICOLON RELOP INCOP DECOP LOGICOP NOT CONST_INT CONST_FLOAT INT FLOAT DOUBLE
%type <dvar> CONST_FLOAT
%type <ivar> CONST_INT 
/* %type <cvar> type_spec decl_list var */
%left SUBOP
%left ADDOP
%left DIVOP
%left MULOP

%right ASSIGNOP 

%%

line: mul_stmt NEWLINE 
    |stmt NEWLINE 
    ;

stmt : stmt unit { log_error("stmt : stmt unit\n");}
     | unit {log_error("stmt : unit\n"); }
     ;

unit : var_decl NEWLINE { log_error("unit : var_decl\n"); }
     | expr_decl NEWLINE { log_error("unit : expr_decl\n"); }
     | error NEWLINE { yyerror("syntax error"); yyerrok; }
     ;



mul_stmt : mul_stmt func_decl 
         | func_decl
         ;

func_decl : type_spec term LPAREN RPAREN LCURL stmt RCURL {log_error("func_decl : type_spec term LPAREN RPAREN LCURL stmt RCURL\n"); }
          | type_spec term LPAREN RPAREN NEWLINE LCURL NEWLINE stmt RCURL {log_error("func_decl : type_spec term LPAREN RPAREN LCURL stmt RCURL\n"); }
          ;

var_decl : type_spec decl_list SEMICOLON {log_error("vardecl : typespec declist SEMICOLON\n"); }
         ;

type_spec : INT {log_error("typespec : INT\n");}
          | FLOAT {log_error("typespec : FLOAT\n");}
          | DOUBLE {log_error("typespec : DOUBLE\n");}
          ;

decl_list : decl_list COMMA term {log_error("declist : declist COMMA term\n");}
| decl_list COMMA term LTHIRD CONST_INT RTHIRD {log_error("declist : declist COMMA term LTHIRD CONST_INT RTHIRD\n"); }
| term {log_error("declist : term\n");}
| term LTHIRD CONST_INT RTHIRD { log_error("declist : term LTHIRD CONST_INT RTHIRD\n"); }
| ass_list {log_error("declist : asslist\n");}
;


expr_decl : term ASSIGNOP expr SEMICOLON  {log_error("exprdecl : term ASSIGNOP expr SEMICOLON\n");}   
;

ass_list : term ASSIGNOP expr {log_error(" asslist : term ASSIGNOP expr\n");}
;

expr : CONST_INT   { log_error("expr : CONST_INT \n"); }
     | CONST_FLOAT { log_error("expr : CONST_FLOAT \n"); }
     | expr MULOP expr { log_error("expr : expr MULOP expr \n"); }
     | expr DIVOP expr { log_error("expr : expr DIVOP expr \n"); }
     | expr ADDOP expr { log_error("expr : expr ADDOP expr \n"); }
     | expr SUBOP expr { log_error("expr : expr SUBOP expr \n"); }
     | term { log_error("expr : term \n"); }
     ;


term : ID {
    log_error("term: ID\n");
    st.insert(string($1), "identifier"); 
    // st.print();
}   
;
%%

int main() 
{
  st.clear();
  clearOutput();
  yyin=fopen("sample_input.txt","r");
  /* yyout=fopen("log.txt","w"); */
  yyparse(); 
  st.print();
 
  return 0;
}
