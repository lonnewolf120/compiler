%{
#include "symboltable2.h"
#define YYSTYPE Symbol_Info


extern FILE *yyin, *yyout;
extern int line_cnt;
string variables="";
// int line_cnt=1, error_cnt=0;

// ofstream outFile("logerror.txt");  

int yylex();


SymbolTable st;

int temp_counter=1;
char* newTemp(){
    char* temp;
    temp = (char*) malloc(15*sizeof(char));
    sprintf(temp, "t%d", temp_counter);
    temp_counter++;
    return temp;
}

void log_error(const char *msg=""){
    fprintf(yyout, "Line Number: %d\n", line_cnt);
    fprintf(yyout, "%s", msg);
}

void yyerror (const char *str) {
    fprintf(yyout, "%s\n", str);
}


void printASM(string str) {
    ofstream op2;
    op2.open("code.asm", ios::app);
    if (!op2.is_open()) {
        cerr << "Error opening file.\n";
    }
    op2<<str;
    op2.close();
}
void initASM(ofstream &op, string variables){
    op << ".MODEL SMALL\n";
    op << ".STACK 100H\n";
    op << ".DATA\n";
    op << variables;
    op << ".CODE\n";
    op << "MAIN PROC\n";
    op << "\tMOV AX, @DATA\n";
    op << "\tMOV DS, AX\n";
}

void printIR(string str) {
    ofstream op2;
    op2.open("code.ir", ios::app);
    if (!op2.is_open()) {
        cerr << "Error opening file.\n";
    }
    op2<<str;
    op2.close();
}

void clearOutput() {
    ofstream clearout;
    clearout.open("log_error.txt", ios::trunc);
    if (!clearout.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    clearout.close();
    clearout.open("table.txt", ios::trunc);
    if (!clearout.is_open()) {
        cerr << "Error delete file contents.\n";
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


line: mul_stmt  
    |stmt  
    ;

stmt : stmt unit { log_error("stmt : stmt unit\n");}
     | unit {log_error("stmt : unit\n"); }
     | error {log_error(""); yyerror("syntax error: invalid expression");}
     ;

unit : var_decl  { log_error("unit : var_decl\n"); }
     | expr_decl  { log_error("unit : expr_decl\n"); }
     ;

func_decl : type_spec term LPAREN RPAREN LCURL stmt RCURL {
    log_error("func_decl : type_spec term LPAREN RPAREN LCURL stmt RCURL\n"); 
    
    string funcName = string($2.getSymbol());
    string asmCode = funcName + " PROC\n";
    asmCode += "\tPUSH BP\n";
    asmCode += "\tMOV BP, SP\n";
    asmCode += "\t; Function body goes here\n";
    asmCode += "\t"+ string($6.getSymbol()) +"\n";
    asmCode += "\tPOP BP\n";
    asmCode += "\tRET\n";
    asmCode += funcName + " ENDP\n";
    printASM(asmCode);

    }
    | type_spec term LPAREN param_list RPAREN LCURL stmt RCURL {
    log_error("func_decl : type_spec term LPAREN param_list RPAREN LCURL stmt RCURL\n"); 
    
    }
    ;

param_list : param_decl { log_error("param_list : param_decl\n"); }
           | param_list COMMA param_decl { log_error("param_list : param_list COMMA param_decl\n"); }
           ;

param_decl : type_spec term { log_error("param_decl : type_spec term\n"); }
           ;


mul_stmt : mul_stmt func_decl 
         | func_decl
         ;

var_decl : type_spec decl_list SEMICOLON {
    log_error("vardecl : type_spec dec_list SEMICOLON\n"); 
    printIR(string($$.getSymbol())+" = "+string($2.getSymbol())+";\n");
    
    variables += string($2.getSymbol()) + " DW ?\n";
    
    string asmCode = "MOV AX, " + string($2.getSymbol().c_str()) + "\n";
    asmCode += "MOV " + string($2.getSymbol().c_str()) + ", AX\n\n";
    printASM(asmCode);
}
;

type_spec : INT {
        log_error("type_spec : INT\n");
        // printIR(string($$.getSymbol())+" = "+string($1.getSymbol())+" - "+string($3.getSymbol())+"\n");
        
        // printASM("MOV AX, "+string($2.getSymbol().c_str())+"\n");
        // printASM("MOV "+string($$.getSymbol().c_str())+", AX\n\n");
        
        }
          | FLOAT {log_error("type_spec : FLOAT\n");}
          | DOUBLE {log_error("type_spec : DOUBLE\n");}
          ;

decl_list : decl_list COMMA term {log_error("dec_list : dec_list COMMA term\n");}
        | decl_list COMMA term LTHIRD CONST_INT RTHIRD {log_error("dec_list : dec_list COMMA term LTHIRD CONST_INT RTHIRD\n"); }
        | term {log_error("dec_list : term\n");
        // $$ = $1;
        printIR(string($$.getSymbol()) + " = " + string($1.getSymbol()) + ";\n");
        string asmCode = "MOV AX, " + string($1.getSymbol().c_str()) + "\n";
        asmCode += "MOV " + string($$.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);

        }
        | term LTHIRD CONST_INT RTHIRD { log_error("dec_list : term LTHIRD CONST_INT RTHIRD\n"); }
        | ass_list {log_error("dec_list : asslist\n");}
        ;
 

expr_decl : term ASSIGNOP expr SEMICOLON  {
    log_error("expr_decl : term ASSIGNOP expr SEMICOLON\n");
    // char* str = newTemp();
    // Symbol_Info obj(str, "TempID");
    // $$ = $1 - $3;
    // $$ = obj;
    printIR(string($1.getSymbol())+" = "+string($3.getSymbol())+";\n");
    
    string asmCode = "MOV AX, " + string($3.getSymbol().c_str()) + "\n";
    asmCode += "MOV " + string($1.getSymbol().c_str()) + ", AX\n\n";
    printASM(asmCode);
    }   
;

ass_list : term ASSIGNOP expr {
    log_error(" asslist : term ASSIGNOP expr\n");
    printIR(string($1.getSymbol()) + " = " + string($3.getSymbol()) + ";\n");
    string asmCode = "MOV AX, " + string($3.getSymbol().c_str()) + "\n";
    asmCode += "MOV " + string($1.getSymbol().c_str()) + ", AX\n\n";
    printASM(asmCode);
}
;

expr : CONST_INT   { log_error("expr : CONST_INT \n"); }
     | CONST_FLOAT { log_error("expr : CONST_FLOAT \n"); }
     | expr MULOP expr { 
        log_error("expr : expr MULOP expr \n");
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        // $$ = $1 * $3;
        $$=obj;  
        printIR(string($$.getSymbol()) + " = " + string($1.getSymbol()) + " * " + string($3.getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string($1.getSymbol().c_str()) + "\n"; 
        asmCode += "MOV BX, " + string($3.getSymbol().c_str()) + "\n";
        asmCode += "MUL AX, BX\n";
        asmCode += "MOV " + string($$.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
     | expr DIVOP expr { 
        log_error("expr : expr DIVOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");

        // $$ = $1 / $3;  
        $$=obj;
        printIR(string($$.getSymbol()) + " = " + string($1.getSymbol()) + " / " + string($3.getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string($1.getSymbol().c_str()) + "\n";
        asmCode += "MOV BX, " + string($3.getSymbol().c_str()) + "\n";
        asmCode += "DIV AX, BX\n";
        asmCode += "MOV " + string($$.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
     | expr ADDOP expr { 
        log_error("expr : expr ADDOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        // $$ = $1 + $3;
        $$ = obj;  
        printIR(string($$.getSymbol()) + " = " + string($1.getSymbol()) + " + " + string($3.getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string($1.getSymbol().c_str()) + "\n";
        asmCode += "MOV BX, " + string($3.getSymbol().c_str()) + "\n";
        asmCode += "ADD AX, BX\n";
        asmCode += "MOV " + string($$.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
     | expr SUBOP expr { 
        log_error("expr : expr SUBOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        // $$ = $1 - $3; 
        $$ = obj;
        printIR(string($$.getSymbol()) + " = " + string($1.getSymbol()) + " - " + string($3.getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string($1.getSymbol().c_str()) + "\n";
        asmCode += "MOV BX, " + string($3.getSymbol().c_str()) + "\n";
        asmCode += "SUB AX, BX\n";
        asmCode += "MOV " + string($$.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
     | expr LOGICOP expr { 
        log_error("expr : expr LOGICOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        $$ = obj;
        string asmCode = "MOV AX, " + string($1.getSymbol().c_str()) + "\n";
        asmCode += "MOV BX, " + string($3.getSymbol().c_str()) + "\n";
        if($2.getSymbol() == "&&") {
            printIR(string($$.getSymbol()) + " = " + string($1.getSymbol()) + " && " + string($3.getSymbol()) + "\n");
            asmCode += "AND AX, BX\n";
        } else {
            printIR(string($$.getSymbol()) + " = " + string($1.getSymbol()) + " || " + string($3.getSymbol()) + "\n");
            asmCode += "OR AX, BX\n";    
        }
        asmCode += "MOV " + string($$.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
     | LPAREN expr RPAREN { 
        log_error("expr : LPAREN expr RPAREN  \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        $$ = obj;
        printIR(string($$.getSymbol()) + " = " + string($2.getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string($2.getSymbol().c_str()) + "\n";
        asmCode += "MOV " + string($$.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
     | term { 
        log_error("expr : term \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        $$ = obj;
        printIR(string($$.getSymbol()) + " = " + string($1.getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string($1.getSymbol().c_str()) + "\n";
        printASM(asmCode);
     }
     ;

term : ID {
    
    Symbol_Info obj(string($1.getSymbol()), "ID");

    if (!(st.insert(obj))) {
        fprintf(yyout, "%s is already declared\n", $1.getSymbol().c_str());
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
  ofstream opp("code.asm", ios::app);
  initASM(opp, variables);
  yyin=fopen("input.txt","r");
  yyout=fopen("log_error.txt","w");
  yyparse(); 
  st.print();

  string asmCode = "MOV AH, 4CH\n";
  asmCode += "INT 21H\n";
  asmCode += "MAIN ENDP\n";
  asmCode += "END MAIN\n";
  printASM(asmCode);

  return 0;
}