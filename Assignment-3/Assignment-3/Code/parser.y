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
char *cvar;
}

%type <dvar> expr
%type <cvar> term expr exprdecl
%token <dvar> CONST_FLOAT 
%token NEWLINE
%token CONST_INT
%token <cvar> ID ADDOP MULOP NEWLINE ASSIGNOP SEMICOLON

%left SUB
%left ADDOP
%left DIV
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

expr: CONST_INT  { 
    $$ = $1; 
    st.insert(yytext, "CONST_INT"); 
    fcout("CONST_INT", yytext);  
}
| CONST_FLOAT    { 
    $$ = $1; 
    st.insert(yytext, "CONST_FLOAT"); 
    fcout("CONST_FLOAT", yytext);
}
| expr ADDOP expr {
    $$ = $1 + $2;
    st.insert(yytext, "CONST_FLOAT"); 
    fcout("CONST_FLOAT", yytext);
}
| expr MULOP expr
| expr SUB expr
| expr DIV expr
| term
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

expr : expr '+' expr	{$$=$1+$3;}
| expr SUB expr			{$$=$1-$3;}
| expr '*' expr			{$$=$1*$3;}
| expr '/' expr			{if($3==0) yyerror("Div by 0");
						else $$=$1/$3;}
| NUMBER
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

    yylex();
    //fprintf(yyout,"Total lines: %d\n", line_cnt);
    logf(("\nTotal errors: " + to_string(error_cnt)));
    fclose(yyin);
    //fclose(yyout);
    return 0;
}
