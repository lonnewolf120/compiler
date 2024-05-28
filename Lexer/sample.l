%option noyywrap

%{

#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
int cnt=0;

    SymbolTable st;

%}

start      [a-zA-Z]
ID         {start}[a-zA-Z0-9]*
NUM        [0-9]+
delim      [ \t\n]

%%
print      {st.print();}
\n  	   {cnt++;}
int        { fprintf(yyout, "<KEYWORD, %s, %d>\n", yytext, yyleng); 
    st.insert("KEYWORD", yytext);
}
string     { fprintf(yyout, "<KEYWORD, %s, %d>\n", yytext, yyleng); 
    st.insert("KEYWORD", yytext);}
float      { fprintf(yyout, "<KEYWORD, %s, %d>\n", yytext, yyleng); 
    st.insert("KEYWORD", yytext);}
bool       { fprintf(yyout, "<KEYWORD, %s, %d>\n", yytext, yyleng); 
    st.insert("KEYWORD", yytext);}
struct     { fprintf(yyout, "<KEYWORD, %s, %d>\n", yytext, yyleng); 
    st.insert("KEYWORD", yytext);}

{NUM}      { fprintf(yyout, "<NUMBER, %s, %d>\n", yytext, yyleng); 
    st.insert("NUMBER", yytext);}
{NUM}"."{NUM}      {
             fprintf(yyout, "<FLOAT, %s, %d>\n", yytext, yyleng); 
    st.insert("FLOAT", yytext);}
{ID}       { fprintf(yyout, "<IDENTIFIER, %s, %d>\n", yytext, yyleng); 
    st.insert("IDENTIFIER", yytext);}

{delim}    { /* Ignore whitespace */ }

.          { fprintf(yyout, "OTHER\n"); }

%%

int main() {
    clearOutput();
    yyin = fopen("input.txt", "r");
    yyout = fopen("out.txt", "w");
    yylex();
	fprintf(yyout,"Total lines: %d\n", cnt);
    fclose(yyin);
    fclose(yyout);
    return 0;
}
