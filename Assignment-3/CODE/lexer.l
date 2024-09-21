%option noyywrap

%{

#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
int line_cnt = 1;

%}


scmt      "//"([^\n\\]*\\\n)*[^\n]*\n
mcmt      "/*"(.|\n)*?"*/"
start      [a-zA-Z_]
NUM        [0-9]+

ID         {start}[a-z_A-Z0-9]*
WID        {NUM}{ID}
FLOAT  {NUM}"."{NUM}?([eE][-+]?{NUM})?
WFLOAT     {NUM}E{NUM}\.{NUM}
CHAR       \'[^\']\'   
delim      [ \t\n]


%%




"int"      { return INT; }
"float"    { return FLOAT; }
"double"   { return DOUBLE; }
"char"     { return CHAR; }


"if"       { return IF; }
"else"     { return ELSE; }
"while"    { return WHILE; }
"for"      { return FOR; }
"return"   { return RETURN; }
"break"    { return BREAK; }
"continue" { return CONTINUE; }
"void"     { return VOID; }

"{"         {return LCURL;}
"}"         {return RCURL;}
"("         {return LPAREN;}
")"         {return RPAREN;}
"["         {return LTHIRD;}
"]"         {return RTHIRD;}
","         {return COMMA;}
";"         {return SEMICOLON;}
"++"        { return INCOP; }
"--"        { return DECOP; }
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
"%"         {return MULOP;}



{NUM} { 
      yylval.ivar = atoi(yytext);
      return CONST_INT;
    }
{FLOAT} { 
      yylval.dvar = atof(yytext);
      return CONST_FLOAT; 
}
{ID} {  
      yylval.cvar = strdup(yytext); // allocate memory
      return ID; 
}

[\n] { line_cnt++; }

%%
