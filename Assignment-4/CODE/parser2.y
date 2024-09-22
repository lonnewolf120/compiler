%{
#include "symboltable2.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#define YYSTYPE Symbol_Info

extern FILE *yyin, *yyout;
extern int line_cnt;
std::vector<std::string> variables; 

std::vector<std::string> asm_code[4];

int yylex();

SymbolTable st;

int temp_counter = 1;
void log_error(const char *msg = "") {
    fprintf(yyout, "Line Number: %d\n", line_cnt);
    fprintf(yyout, "%s", msg);
}

void yyerror(const char *str) {
    fprintf(yyout, "%s\n", str);
}

void printASM(std::string str, int i = 2) { 
    asm_code[i].push_back(str);
}

char* newTemp() {
    char* temp;
    temp = (char*) malloc(15 * sizeof(char));
    sprintf(temp, "t%d", temp_counter);
    printASM(("t"+std::to_string(temp_counter)+" DW ?\n"), 1);
    temp_counter++;
    return temp;
}

void printIR(std::string str) {
    std::ofstream op2;
    op2.open("code.ir", std::ios::app);
    if (!op2.is_open()) {
        std::cerr << "Error opening file.\n";
    }
    op2 << str;
    op2.close();
}

void printVar(std::string varName){
    std::string asmCode = "\tMOV AH, 02H\n";
    asmCode += "\tMOV DX, " + varName + "\n";
    asmCode += "\tINT 21H\n";
    printASM(asmCode, 2);
}

void clearOutput() {
    std::ofstream clearout;
    clearout.open("log_error.txt", std::ios::trunc);
    if (!clearout.is_open()) {
        std::cerr << "Error deleting file contents.\n";
    }
    clearout.close();
    clearout.open("table.txt", std::ios::trunc);
    if (!clearout.is_open()) {
        std::cerr << "Error deleting file contents.\n";
    }
    clearout.close();
    clearout.open("code.ir", std::ios::trunc);
    if (!clearout.is_open()) {
        std::cerr << "Error deleting file contents.\n";
    }
    clearout.close();
    clearout.open("code.asm", std::ios::trunc);
    if (!clearout.is_open()) {
        std::cerr << "Error deleting file contents.\n";
    }
    clearout.close();
}

%}

%token LTHIRD RTHIRD LPAREN RPAREN LCURL RCURL COMMA ID ADDOP SUBOP MULOP CONST_FLOAT INT 
%token DIVOP MODOP ASSIGNOP SEMICOLON RELOP INCOP DECOP COLON LOGICOP NOT CONST_INT FLOAT 
%token IF ELSE FOR WHILE RETURN BREAK CONTINUE VOID MAIN SWITCH CASE ELIF DOUBLE CHAR DEFAULT

%left LOGICOP
%left ADDOP SUBOP
%left MULOP DIVOP
%right ASSIGNOP 

%%
prog:  func_decl_list main_func { log_error("prog : func_decl_list main_func\n"); }
       ;

func_decl_list: func_decl_list func_decl { log_error("func_decl_list : func_decl_list func_decl\n"); }
              | /* empty */ { }
              ;

main_func: MAIN LPAREN RPAREN LCURL stmt_list RCURL { 
    log_error("main_func : MAIN LPAREN RPAREN LCURL stmt_list RCURL\n"); 
}
;

stmt_list : stmt_list stmt { log_error("stmt_list : stmt_list stmt\n"); }
          | stmt { log_error("stmt_list : stmt\n"); }
          ;

stmt : var_decl { log_error("stmt : var_decl\n"); }
     | expr_decl { log_error("stmt : expr_decl\n"); }
     | conditional { log_error("stmt : conditional\n"); }
     | switch_stmt { log_error("stmt : switch_stmt\n"); }
     | break_stmt { log_error("stmt : break_stmt\n"); }
     | func_call { log_error("stmt : func_call\n"); }
     | error { log_error(""); yyerror("syntax error: invalid expression"); }
     ;

switch_stmt : SWITCH LPAREN expr RPAREN LCURL case_list default_case_opt RCURL {
    log_error("switch_stmt : SWITCH LPAREN expr RPAREN LCURL case_list default_case_opt RCURL\n");
    std::string asmCode = "\tMOV AX, " + $3.getSymbol() + "\n";
    asmCode += "\tMOV BX, AX\n";
    printASM(asmCode);
}
;

case_list : case_list case {
    log_error("case_list : case_list case\n");
}
| case {
    log_error("case_list : case\n");
}
;

case : CASE CONST_INT COLON stmt_list {
    log_error("case : CASE CONST_INT COLON stmt_list\n");
    std::string asmCode = "\tCMP BX, " + string($2.getSymbol()) + "\n";
    asmCode += "\tJE CASE_" + string($2.getSymbol()) + "\n";
    asmCode += "CASE_" + string($2.getSymbol()) + ":\n";
    asmCode += $4.getCode();
    printASM(asmCode);
}
;

default_case_opt : default_case {
    log_error("default_case_opt : default_case\n");
}
| /* empty */ {
    log_error("default_case_opt : /* empty */\n");
}
;

default_case : DEFAULT COLON stmt_list {
    log_error("default_case : DEFAULT COLON stmt_list\n");
    std::string asmCode = "DEFAULT:\n";
    asmCode += $3.getCode();
    printASM(asmCode);
}
;

break_stmt : BREAK SEMICOLON {
    log_error("break_stmt : BREAK SEMICOLON\n");
    std::string asmCode = "\tJMP END_SWITCH\n";
    printASM(asmCode);
}
;

var_decl : type_spec decl_list SEMICOLON {
    log_error("var_decl : type_spec decl_list SEMICOLON\n"); 
    std::string var = $2.getSymbol() + " DW ?\n";
    printASM(var, 1);
    variables.push_back(std::string($2.getSymbol()));
    std::string asmCode = "\tMOV AX, " + $2.getSymbol() + "\n";
    asmCode += "\tMOV " + $2.getSymbol() + ", AX\n\n";
    $$.setCode(asmCode);
}
;

type_spec : INT {
        log_error("type_spec : INT\n");
        }
          | FLOAT { log_error("type_spec : FLOAT\n"); }
          | DOUBLE { log_error("type_spec : DOUBLE\n"); }
          ;

decl_list : term { log_error("decl_list : term\n"); }
        ;

expr_decl : term ASSIGNOP expr SEMICOLON  {
    log_error("expr_decl : term ASSIGNOP expr SEMICOLON\n");
    printIR($1.getSymbol() + " = " + $3.getSymbol() + ";\n");
    std::string asmCode = "\tMOV AX, " + $3.getSymbol() + "\n";
    asmCode += "\tMOV " + $1.getSymbol() + ", AX\n\n";
    
    $$.setCode(asmCode);
    printASM(asmCode);
    }   
;

conditional: IF LPAREN expr RPAREN LCURL stmt_list RCURL { log_error("conditional : IF LPAREN expr RPAREN LCURL stmt_list RCURL\n"); }
            | IF LPAREN expr RPAREN LCURL stmt_list RCURL ELSE LCURL stmt_list RCURL { log_error("conditional : IF LPAREN expr RPAREN LCURL stmt_list RCURL ELSE LCURL stmt_list RCURL\n"); }
           | IF LPAREN expr RPAREN LCURL stmt_list RCURL ELIF LPAREN expr RPAREN LCURL stmt_list RCURL { log_error("conditional : IF LPAREN expr RPAREN LCURL stmt_list RCURL ELIF LPAREN expr RPAREN LCURL stmt_list RCURL\n"); }
           ;

func_decl : type_spec term LPAREN param_list RPAREN LCURL stmt_list RCURL {
    log_error("func_decl : type_spec ID LPAREN param_list RPAREN LCURL stmt_list RCURL\n");
    std::string asmCode = $2.getSymbol() + " PROC\n";
    asmCode += $7.getCode();
    asmCode += $2.getSymbol() + " ENDP\n";
    printASM(asmCode, 2);
}
| type_spec term SEMICOLON {
    log_error("func_decl : type_spec ID SEMICOLON\n");
}
;

param_list : param_list COMMA param { log_error("param_list : param_list COMMA param\n"); }
           | param { log_error("param_list : param\n"); }
           | /* empty */ { log_error("param_list : /* empty */\n"); }
           ;

param : type_spec ID { log_error("param : type_spec ID\n"); }
      ;

func_call : ID LPAREN arg_list RPAREN SEMICOLON {
    log_error("func_call : ID LPAREN arg_list RPAREN SEMICOLON\n");
    std::string asmCode = "\tCALL " + $1.getSymbol() + "\n";
    printASM(asmCode, 2);
}
;

arg_list : arg_list COMMA expr { log_error("arg_list : arg_list COMMA expr\n"); }
         | expr { log_error("arg_list : expr\n"); }
         | /* empty */ { log_error("arg_list : /* empty */\n"); }
         ;

expr : CONST_INT   { log_error("expr : CONST_INT \n"); }
     | CONST_FLOAT { log_error("expr : CONST_FLOAT \n"); }
     | expr MULOP expr { 
        log_error("expr : expr MULOP expr \n");
        std::string asmCode = "\tXOR DX, DX ;need to clear DX first\n"; 
        asmCode += "\tMOV AX, " + $1.getSymbol() + "\n"; 
        asmCode += "\tMOV BX, " + $3.getSymbol() + "\n";
        asmCode += "\tMUL BX\n";
        asmCode += "\tMOV " + $$.getSymbol() + ", AX\n\n";

        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        obj.setCode(asmCode);
        $$ = obj;  
        printIR($$.getSymbol() + " = " + $1.getSymbol() + " * " + $3.getSymbol() + "\n");
        
        printASM(asmCode);
     }
     | expr DIVOP expr { 
        log_error("expr : expr DIVOP expr \n"); 
        std::string asmCode = "\tXOR DX, DX ;need to clear DX first\n";
        asmCode += "\tMOV AX, " + $1.getSymbol() + "\n";
        asmCode += "\tMOV BX, " + $3.getSymbol() + "\n";
        asmCode += "\tDIV BX\n";
        asmCode += "\tMOV " + $$.getSymbol() + ", AX\n\n";

        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        obj.setCode(asmCode);
        $$ = obj;
        printIR($$.getSymbol() + " = " + $1.getSymbol() + " / " + $3.getSymbol() + "\n");
        printASM(asmCode);
     }
     | expr ADDOP expr { 
        log_error("expr : expr ADDOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        std::string asmCode = "\tMOV AX, " + $1.getSymbol() + "\n";
        asmCode += "\tMOV BX, " + $3.getSymbol() + "\n";
        asmCode += "\tADD AX, BX\n";
        asmCode += "\tMOV " + $$.getSymbol() + ", AX\n\n";

        obj.setCode(asmCode);
        $$ = obj;  
        printIR($$.getSymbol() + " = " + $1.getSymbol() + " + " + $3.getSymbol() + "\n");
        printASM(asmCode);
     }
     | expr SUBOP expr { 
        log_error("expr : expr SUBOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        std::string asmCode = "\tMOV AX, " + $1.getSymbol() + "\n";
        asmCode += "\tMOV BX, " + $3.getSymbol() + "\n";
        asmCode += "\tSUB AX, BX\n";
        asmCode += "\tMOV " + $$.getSymbol() + ", AX\n\n";

        obj.setCode(asmCode);

        $$ = obj;
        
        printIR($$.getSymbol() + " = " + $1.getSymbol() + " - " + $3.getSymbol() + "\n");
        printASM(asmCode);
     }
     | expr LOGICOP expr { 
        log_error("expr : expr LOGICOP expr \n"); 
        std::string asmCode = "\tMOV AX, " + $1.getSymbol() + "\n";
        asmCode += "\tMOV BX, " + $3.getSymbol() + "\n";
        if($2.getSymbol() == "&&") {
            printIR($$.getSymbol() + " = " + $1.getSymbol() + " && " + $3.getSymbol() + "\n");
            asmCode += "AND AX, BX\n";
        } else if($2.getSymbol() == "||")  {
            printIR($$.getSymbol() + " = " + $1.getSymbol() + " || " + $3.getSymbol() + "\n");
            asmCode += "OR AX, BX\n";    
        }
        asmCode += "\tMOV " + $$.getSymbol() + ", AX\n\n";
        printASM(asmCode);
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        obj.setCode(asmCode);
        $$ = obj;
        
     }
     | LPAREN expr RPAREN { 
        log_error("expr : LPAREN expr RPAREN  \n");
        printIR($$.getSymbol() + " = " + $2.getSymbol() + "\n");
        std::string asmCode = "\tMOV AX, " + $2.getSymbol() + "\n";
        asmCode += "\tMOV " + $$.getSymbol() + ", AX\n\n";
        $$.setCode(asmCode);
        printASM(asmCode);
     }
     | term { 
        log_error("expr : term \n"); 
        printIR($$.getSymbol() + " = " + $1.getSymbol() + "\n");
     }
     ;

term : ID {
    Symbol_Info obj(std::string($1.getSymbol()), "ID");
    if (!(st.insert(obj))) {
        fprintf(yyout, "%s is already declared\n", $1.getSymbol().c_str());
    } else {
        log_error("term: ID\n");
    }
}  
;

%%

int main() 
{
    st.clear();
    clearOutput();
    std::string asmCode = ".MODEL SMALL\n";
    asmCode += ".STACK 100H\n";
    asmCode += ".DATA\n";
    printASM(asmCode, 0);
    asmCode="";
  
    asmCode += ".CODE\n";
    asmCode += "MAIN PROC\n";
    asmCode += "\tMOV AX, @DATA\n";
    asmCode += "\tMOV DS, AX\n";
    asmCode += "\tXOR AX, AX ;making AX=0\n";
    printASM(asmCode, 2);
    yyin = fopen("input.txt", "r");
    yyout = fopen("log_error.txt", "w");
    yyparse(); 

    st.print();

    asmCode = "\tMOV AH, 4CH\n";
    asmCode += "\tINT 21H\n";
    asmCode += "MAIN ENDP\n";
    asmCode += "END MAIN\n";
    printASM(asmCode, 3);

    for(auto &i: variables){
        printVar(i);
    }

    for(int i = 0; i < 4; ++i) {
        for(auto it: asm_code[i]) {
            std::ofstream op2;
            op2.open("code.asm", std::ios::app);
            if (!op2.is_open()) {
                std::cerr << "Error opening file.\n";
            }
            op2 << it;
            op2.close();
        }
    }

    return 0;
}