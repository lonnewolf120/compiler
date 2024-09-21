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
    printASM(("t"+to_string(temp_counter)+" DW ?\n"), 1);
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

void printVar(string varName){
    string asmCode = "\tMOV AH, 02H\n";
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

%token LTHIRD RTHIRD LPAREN RPAREN LCURL RCURL COMMA ID ADDOP SUBOP MULOP DIVOP MODOP ASSIGNOP SEMICOLON RELOP INCOP DECOP LOGICOP NOT CONST_INT CONST_FLOAT INT FLOAT DOUBLE CHAR
%token IF ELSE FOR WHILE RETURN BREAK CONTINUE VOID MAIN

%left LOGICOP
%left ADDOP SUBOP
%left MULOP DIVOP

%right ASSIGNOP 

%%

prog: MAIN LPAREN RPAREN LCURL stmt RCURL { 
    log_error("prog : MAIN LPAREN RPAREN LCURL stmt RCURL\n"); 
    }
    ;

stmt : stmt unit { log_error("stmt : stmt unit\n");}
     | unit {log_error("stmt : unit\n"); }
     | error {log_error(""); yyerror("syntax error: invalid expression");}
     ;

unit : var_decl  { log_error("unit : var_decl\n"); }
     | expr_decl  { log_error("unit : expr_decl\n"); }
     ;

var_decl : type_spec decl_list SEMICOLON {
    log_error("vardecl : type_spec dec_list SEMICOLON\n"); 
    string var = $2.getSymbol() + " DW ?\n";
    printASM(var, 1);
    variables.push_back(string($2.getSymbol()));
    std::string asmCode = "\tMOV AX, " + $2.getSymbol() + "\n";
    asmCode += "\tMOV " + $2.getSymbol() + ", AX\n\n";
}
;

type_spec : INT {
        log_error("type_spec : INT\n");
        }
          | FLOAT {log_error("type_spec : FLOAT\n");}
          | DOUBLE {log_error("type_spec : DOUBLE\n");}
          ;

decl_list : term {log_error("dec_list : term\n");}
        ;

expr_decl : term ASSIGNOP expr SEMICOLON  {
    log_error("expr_decl : term ASSIGNOP expr SEMICOLON\n");
    // char* str = newTemp();
    // Symbol_Info obj(str, "TempID");
    // $$ = obj;
    printIR($1.getSymbol() + " = " + $3.getSymbol() + ";\n");
    std::string asmCode = "\tMOV AX, " + $3.getSymbol() + "\n";
    asmCode += "\tMOV " + $1.getSymbol() + ", AX\n\n";
    printASM(asmCode);
    }   
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
        $$ = obj;
        
     }
     | LPAREN expr RPAREN { 
        log_error("expr : LPAREN expr RPAREN  \n");
        //TODO: UNCOMMENT IF OTHERS ARE DONE 
        // char* str = newTemp();
        // Symbol_Info obj(str, "TempID");
        // $$ = obj;
        printIR($$.getSymbol() + " = " + $2.getSymbol() + "\n");
        std::string asmCode = "\tMOV AX, " + $2.getSymbol() + "\n";
        asmCode += "\tMOV " + $$.getSymbol() + ", AX\n\n";
        printASM(asmCode);
     }
     | term { 
        log_error("expr : term \n"); 
        // std::string asmCode = "\tMOV AX, " + $1.getSymbol() + "\n";
        // printASM(asmCode);
     
        // char* str = newTemp();
        // Symbol_Info obj(str, "TempID");
        // $$ = obj;
        printIR($$.getSymbol() + " = " + $1.getSymbol() + "\n");
     }
     ;

term : ID {
    Symbol_Info obj(string($1.getSymbol()), "ID");
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
    string asmCode = ".MODEL SMALL\n";
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