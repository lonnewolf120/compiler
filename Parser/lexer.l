%option noyywrap
%{
#include "parser.tab.h"
#include <stdlib.h>
int line_cnt=0;
%}

s-cmt      "//"([^\n\\]*\\\n)*[^\n]*\n
m-cmt      "/*"(.|\n)*?"*/"
start      [a-zA-Z_]
ID         {start}[a-z_A-Z0-9]*
DIGITS     [0-9]+
NUMBER     {DIGITS}(\.{DIGITS})? 
WID        {NUM}{ID}
FLOAT      ({NUM})?\.{NUM}(E(-)?)?{NUM}
WFLOAT     {NUM}E{NUM}\.{NUM}
CHAR       \'[^\']\'   
STRING     [A-Za-z0-9'\-+"%#@!^]
delim      [ \t\n]

%%

\n         { line_cnt++; return NEWLINE; }
[ \t]      {}


{NUMBER}    {
    //sscanf(yytext, "%lf", &yylval.dvar );
    yylval.dvar = atof(yytext);
    return NUMBER;
}



[+*/-]     {return *yytext;}

%%

