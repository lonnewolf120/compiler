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
FLOAT      {NUM}.{NUM}(E(-)?)?{NUM}
delim      [ \t\n]
%%
print      { st.print(); }

\n         { cnt++; }
"if"       { fprintf(yyout, "<IF, %s>\n", yytext); 
             st.insert("IF", yytext); }
"else"     { fprintf(yyout, "<ELSE, %s>\n", yytext); 
             st.insert("ELSE", yytext); }
"for"      { fprintf(yyout, "<FOR, %s>\n", yytext); 
             st.insert("FOR", yytext); }
"while"    { fprintf(yyout, "<WHILE, %s>\n", yytext); 
             st.insert("WHILE", yytext); }
"do"       { fprintf(yyout, "<DO, %s>\n", yytext); 
             st.insert("DO", yytext); }
"break"    { fprintf(yyout, "<BREAK, %s>\n", yytext); 
             st.insert("BREAK", yytext); }
"int"      { fprintf(yyout, "<INT, %s>\n", yytext); 
             st.insert("INT", yytext); }
"char"     { fprintf(yyout, "<CHAR, %s>\n", yytext); 
             st.insert("CHAR", yytext); }
"float"    { fprintf(yyout, "<FLOAT, %s>\n", yytext); 
             st.insert("FLOAT", yytext); }
"double"   { fprintf(yyout, "<DOUBLE, %s>\n", yytext); 
             st.insert("DOUBLE", yytext); }
"void"     { fprintf(yyout, "<VOID, %s>\n", yytext); 
             st.insert("VOID", yytext); }
"return"   { fprintf(yyout, "<RETURN, %s>\n", yytext); 
             st.insert("RETURN", yytext); }
"switch"   { fprintf(yyout, "<SWITCH, %s>\n", yytext); 
             st.insert("SWITCH", yytext); }
"case"     { fprintf(yyout, "<CASE, %s>\n", yytext); 
             st.insert("CASE", yytext); }
"default"  { fprintf(yyout, "<DEFAULT, %s>\n", yytext); 
             st.insert("DEFAULT", yytext); }
"continue" { fprintf(yyout, "<CONTINUE, %s>\n", yytext); 
             st.insert("CONTINUE", yytext); }


{NUM}      { fprintf(yyout, "<CONST_INT, %s>\n", yytext); 
             st.insert("CONST_INT", yytext); }
{FLOAT}    { fprintf(yyout, "<CONST_FLOAT, %s>\n", yytext); 
                st.insert("CONST_FLOAT", yytext); }
{ID}       { fprintf(yyout, "<IDENTIFIER, %s>\n", yytext); 
             st.insert("IDENTIFIER", yytext); }

"+"        { fprintf(yyout, "<ADDOP, %s>\n", yytext); 
             st.insert("ADDOP", yytext); }
"*"        { fprintf(yyout, "<MULOP, %s>\n", yytext); 
             st.insert("MULOP", yytext); }
"/"        { fprintf(yyout, "<MULOP, %s>\n", yytext); 
             st.insert("MULOP", yytext); }
"%"        { fprintf(yyout, "<MULOP, %s>\n", yytext); 
             st.insert("MULOP", yytext); }
"++"       { fprintf(yyout, "<INCOP, %s>\n", yytext); 
             st.insert("INCOP", yytext); }
"--"       { fprintf(yyout, "<INCOP, %s>\n", yytext); 
             st.insert("INCOP", yytext); }
"<"        { fprintf(yyout, "<RELOP, %s>\n", yytext); 
             st.insert("RELOP", yytext); }
"<="       { fprintf(yyout, "<RELOP, %s>\n", yytext); 
             st.insert("RELOP", yytext); }
">"        { fprintf(yyout, "<RELOP, %s>\n", yytext); 
             st.insert("RELOP", yytext); }
">="       { fprintf(yyout, "<RELOP, %s>\n", yytext); 
             st.insert("RELOP", yytext); }
"=="       { fprintf(yyout, "<RELOP, %s>\n", yytext); 
             st.insert("RELOP", yytext); }
"!="       { fprintf(yyout, "<RELOP, %s>\n", yytext); 
             st.insert("RELOP", yytext); }
"="        { fprintf(yyout, "<ASSIGNOP, %s>\n", yytext); 
             st.insert("ASSIGNOP", yytext); }
"&&"       { fprintf(yyout, "<LOGICOP, %s>\n", yytext); 
             st.insert("LOGICOP", yytext); }
"||"       { fprintf(yyout, "<LOGICOP, %s>\n", yytext); 
             st.insert("LOGICOP", yytext); }
"!"        { fprintf(yyout, "<NOT, %s>\n", yytext); 
             st.insert("NOT", yytext); }
"("        { fprintf(yyout, "<LPAREN, %s>\n", yytext); 
             st.insert("LPAREN", yytext); }
")"        { fprintf(yyout, "<RPAREN, %s>\n", yytext); 
             st.insert("RPAREN", yytext); }
"{"        { fprintf(yyout, "<LCURL, %s>\n", yytext); 
             st.insert("LCURL", yytext); }
"}"        { fprintf(yyout, "<RCURL, %s>\n", yytext); 
             st.insert("RCURL", yytext); }
"["        { fprintf(yyout, "<LTHIRD, %s>\n", yytext); 
             st.insert("LTHIRD", yytext); }
"]"        { fprintf(yyout, "<RTHIRD, %s>\n", yytext); 
             st.insert("RTHIRD", yytext); }
","        { fprintf(yyout, "<COMMA, %s>\n", yytext); 
             st.insert("COMMA", yytext); }
";"        { fprintf(yyout, "<SEMICOLON, %s>\n", yytext); 
             st.insert("SEMICOLON", yytext); }

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
