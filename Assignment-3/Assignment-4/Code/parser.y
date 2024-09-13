%{
#include<stdio.h>
//#define YYSTYPE double
extern FILE *yyin, *yyout;

int yylex();
int tcnt = 0;

void yyerror (const char *str)
{
printf("Error. %s \n", str);
}

char* CTemp(){
    char* temp = (char*)malloc(10);
    sprintf(temp, "t%d", tcnt++);
    return temp;
}



%}

%union{
double dvar;
double CONST_FLOAT;
char *cvar;
}
 
%type <cvar> expr CONST_INT CONST_FLOAT term expr_decl
%token NEWLINE LTHIRD RTHIRD LPAREN RPAREN LCURL RCURL COMMA
%token CONST_INT CONST_FLOAT INT FLOAT DOUBLE
%token <cvar> ID ADDOP SUBOP MULOP DIVOP ASSIGNOP SEMICOLON RELOP INCOP LOGICOP NOT


%left SUBOP
%left ADDOP
%left DIVOP
%left MULOP


%%
mul_stmt: mul_stmt func_decl
| func_decl
;

func_decl: type_spec term LPAREN RPAREN LCURL stmt RCURL
;

stmt: stmt unit | unit
;

unit: var_decl NEWLINE 
| expr_decl NEWLINE
;

var_decl: type_spec decl_list SEMICOLON
;

type_spec: INT 
| FLOAT 
| DOUBLE
;

term: ID    {
    st.insert(yytext, "Identifier"); 
    fcout("ID", yytext);  
}
;

ass_list: term ASSIGNOP expr

expr: CONST_INT  
| CONST_FLOAT     
| expr MULOP expr { $$ = $1 * $2; }
| expr DIVOP expr   { $$ = $1 / $2; }
| expr ADDOP expr { 
    char *str = Ctemp();
    Symbol_Info si(str, "Temp");
    $$ = si;
    cout<< $$.getSymbol().c_str() << " = " << $1.getSymbol().c_str() << " + " << $2.getSymbol().c_str();
    str = $1 + $3;

    //ASM  code
    cout<< "MOV ax, " $1.getSymbol().c_str() <<"\n";
    cout<< "MOV bx, " $3.getSymbol().c_str() <<"\n";
    cout<< "ADD ax, bx" <<"\n";
    cout<< 'MOV '<< $$.getSymbol().c_str() <<", ax\n";

    tcnt = 1;
}
| expr SUBOP expr   { $$ = $1 - $2; }
| term            {
    
    cout<< 'MOV '<< $$.getSymbol().c_str() <<", ax\n";
}
;

expr_decl: term ASSIGNOP expr SEMICOLON     
;

decl_list: decl_list COMMA term
| decl_list COMMA term LTHIRD CONST_INT RTHIRD
| term
| term LTHIRD CONST_INT RTHIRD
| ass_list

line: expr NEWLINE		{printf("Correct Syntax. %lf \n", $1);}
|ID NEWLINE 			{printf("Correct Syntax. %s \n", $1);}
|error NEWLINE			{yyerrok;}
;

%%

int main()
{
yyparse();
}


int main(int argc, char *argv[]) {
    clearOutput();
//    if(argc!=2){cerr<<"error taking input from file";}
    cout<<"Enter the input file name: ";
    char msg[20]; cin>>msg;
    cout<<"\nThe output will show in 202214024_log.txt & 202214024_token.txt\n\n";
    yyin = fopen(msg,"r");
    yyin = fopen(asm.txt, "w")

    yylex();
    //fprintf(yyout,"Total lines: %d\n", line_cnt);
    logf(("\nTotal errors: " + to_string(error_cnt)));
    fclose(yyin);
    //fclose(yyout);
    return 0;
}
