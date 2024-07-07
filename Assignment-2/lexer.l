%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "symboltable.h"

SymbolTable st;

%}

s-cmt      "//"([^\n\\]*\\\n)*[^\n]*\n
m-cmt      "/*"(.|\n)*?"*/"
start      [a-zA-Z_]
ID         {start}[a-z_A-Z0-9]*
NUM        [0-9]+
WID        {NUM}{ID}
FLOAT      ({NUM})?\.{NUM}(E(-)?)?{NUM}
WFLOAT     {NUM}E{NUM}\.{NUM}
CHAR       \'[^\']\'   
delim      [ \t\n]

%%

{m-cmt}    { ffcout("COMMENT", yytext); }
{s-cmt}    { ffcout("COMMENT", yytext); }
\n         { line_cnt++; }
"if"       { ffcout("IF", "if"); fcout("IF"); }
"else"     { ffcout("ELSE", "else"); fcout("ELSE"); }
"for"      { ffcout("FOR", "for"); fcout("FOR"); }
"while"    { ffcout("WHILE", "while"); fcout("WHILE"); }
"do"       { ffcout("DO", "do"); fcout("DO"); }
"break"    { ffcout("BREAK", "break"); fcout("BREAK"); }
"int"      { ffcout("INT", "int"); fcout("INT"); }
"char"     { ffcout("CHAR", "char"); fcout("CHAR"); }
"float"    { ffcout("FLOAT", "float"); fcout("FLOAT"); }
"double"   { ffcout("DOUBLE", "double"); fcout("DOUBLE"); }
"void"     { ffcout("VOID", "void"); fcout("VOID"); }
"return"   { ffcout("RETURN", "return"); fcout("RETURN"); }
"switch"   { ffcout("SWITCH", "switch"); fcout("SWITCH"); }
"case"     { ffcout("CASE", "case"); fcout("CASE"); }
"default"  { ffcout("DEFAULT", "default"); fcout("DEFAULT"); }
"continue" { ffcout("CONTINUE", "continue"); fcout("CONTINUE"); }

{NUM}      { st.insert(yytext, "CONST_INT"); fcout("CONST_INT", yytext); }
{FLOAT}    { st.insert(yytext, "CONST_FLOAT"); fcout("CONST_FLOAT", yytext); }
{ID}       { st.insert(yytext, "ID"); fcout("ID", yytext); }
{CHAR}     { 
    string ch = string(1, yytext[1]);
    st.insert(ch, "CONST_CHAR"); fcout("CONST_CHAR", ch); }

"+"        { ffcout("ADDOP", yytext); fcout("ADDOP", yytext); }
"*"        { ffcout("MULOP", yytext); fcout("MULOP", yytext); }
"/"        { ffcout("MULOP", yytext); fcout("MULOP", yytext); }
"%"        { ffcout("MULOP", yytext); fcout("MULOP", yytext); }
"++"       { ffcout("INCOP", yytext); fcout("INCOP", yytext); }
"--"       { ffcout("INCOP", yytext); fcout("INCOP", yytext); }
"<"        { ffcout("RELOP", yytext); fcout("RELOP", yytext); }
"<="       { ffcout("RELOP", yytext); fcout("RELOP", yytext); }
">"        { ffcout("RELOP", yytext); fcout("RELOP", yytext); }
">="       { ffcout("RELOP", yytext); fcout("RELOP", yytext); }
"=="       { ffcout("RELOP", yytext); fcout("RELOP", yytext); }
"!="       { ffcout("RELOP", yytext); fcout("RELOP", yytext); }
"="        { ffcout("ASSIGNOP", yytext); fcout("ASSIGNOP", yytext); }
"&&"       { ffcout("LOGICOP", yytext); fcout("LOGICOP", yytext); }
"||"       { ffcout("LOGICOP", yytext); fcout("LOGICOP", yytext); }
"!"        { ffcout("NOT", yytext); fcout("NOT", yytext); }
"("        { ffcout("LPAREN", yytext); fcout("LPAREN", yytext); }
")"        { ffcout("RPAREN", yytext); fcout("RPAREN", yytext); }
"{"        { ffcout("LCURL", yytext); fcout("LCURL", yytext); }
"}"        { ffcout("RCURL", yytext); fcout("RCURL", yytext); }
"["        { ffcout("LTHIRD", yytext); fcout("LTHIRD", yytext); }
"]"        { ffcout("RTHIRD", yytext); fcout("RTHIRD", yytext); }
","        { ffcout("COMMA", yytext); fcout("COMMA", yytext); }
";"        { ffcout("SEMICOLON", yytext); fcout("SEMICOLON", yytext); }


\'\'           { yyerror("Empty character constant "+string(yytext)); }
{WID}      { yyerror("Invalid prefix on ID or invalid suffix on Number " + std::string(yytext)); }
{WFLOAT}   { yyerror("Ill formed number " + std::string(yytext)); }
{delim}    { /* Ignore whitespace */ }
.          { yyerror("unrecognized character: " + std::string(yytext)); }
%%


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
