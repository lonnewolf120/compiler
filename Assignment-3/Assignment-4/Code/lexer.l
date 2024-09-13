%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "symboltable.h"
#include "parser.tab.h"

SymbolTable st;
#define YYSTYPE Symbol_Info 
%}

scmt      "//"([^\n\\]*\\\n)*[^\n]*\n
mcmt      "/*"(.|\n)*?"*/"
start      [a-zA-Z_]
ID         {start}[a-z_A-Z0-9]*
NUM        [0-9]+
WID        {NUM}{ID}
FLOAT      ({NUM})?\.{NUM}(E(-)?)?{NUM}
WFLOAT     {NUM}E{NUM}\.{NUM}
CHAR       \'[^\']\'   
delim      [ \t\n]

%%

{mcmt}    { ffcout("COMMENT", yytext); }
{scmt}    { ffcout("COMMENT", yytext); }
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
"{"         {return LCURL;}
"}"         {return RCURL;}
"("         {return LPAREN;}
")"         {return RPAREN;}
"["         {return LTHIRD;}
"]"         {return RTHIRD;}
","         {return COMMA;}
";"         {return SEMICOLON;}
"++"        {return INCOP;}
"--"        {return INCOP;}
"<"         {return RELOP;}
"<="        {return RELOP;}
">"         {return RELOP;}
">="        {return RELOP;}
"=="        {return RELOP;}
"!="        {return RELOP;}
"="         {return ASSIGNOP;}
"&&"        {return LOGICOP;}
"||"        {return LOGICOP;}
"!"         {return NOT;}
"+"         {return ADDOP;}
"-"         {return SUBOP;}
"*"         {return MULOP;}
"/"         {return DIVOP;}



{NUM}      { 
    //st.insert(yytext, "CONST_INT"); 
    fcout("CONST_INT", yytext);  
    return CONST_INT;
    }
{FLOAT}    { 
    //st.insert(yytext, "CONST_INT"); 
    fcout("CONST_INT", yytext);  
    yylval.dvar = atof(yytext); return CONST_FLOAT; 
}
{ID}       { 
    st.insert(yytext, "CONST_INT"); 
    fcout("CONST_INT", yytext);  
    yylval.cvar = yytext; return ID; 
}
{CHAR}     { 
    string ch = string(1, yytext[1]);
    st.insert(ch, "CONST_CHAR"); fcout("CONST_CHAR", ch); 
    return yytext[1];
}

\'\'           { yyerror("Empty character constant "+string(yytext)); }
{WID}      { yyerror("Invalid prefix on ID or invalid suffix on Number " + std::string(yytext)); }
{WFLOAT}   { yyerror("Ill formed number " + std::string(yytext)); }
{delim}    { /* Ignore whitespace */ }
.          { yyerror("unrecognized character: " + std::string(yytext)); }
%%

