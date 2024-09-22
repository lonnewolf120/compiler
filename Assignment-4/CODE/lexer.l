%option noyywrap

%{

#include "symboltable2.h"
#define YYSTYPE Symbol_Info
#include "parser2.tab.h"
#include <stdio.h>
#include <stdlib.h>


int line_cnt = 1;
void yyerror (const char *str);

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
delim      [ \t]


%%




"int"      { return INT; }
"float"    { return FLOAT; }
"double"   { return DOUBLE; }
"char"     { return CHAR; }
"gint"      { return INT; }
"gfloat2"    { return FLOAT; }
"gdouble2"   { return DOUBLE; }

"main"     { return MAIN; }
"if"       { return IF; }
"else"     { return ELSE; }
"elif"     { return ELIF; }
"while"    { return WHILE; }
"for"      { return FOR; }
"return"   { return RETURN; }
"break"    { return BREAK; }
"continue" { return CONTINUE; }
"void"     { return VOID; }
"switch"  { return SWITCH; }
"case"    { return CASE; }
"default"  { return DEFAULT; }

"{"         {return LCURL;}
"}"         {return RCURL;}
"("         {return LPAREN;}
")"         {return RPAREN;}
"["         {return LTHIRD;}
"]"         {return RTHIRD;}
","         {return COMMA;}
":"         {return COLON;}
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
      Symbol_Info obj;
      obj.setSymbol(string(yytext));
      obj.setToken("CONST_INT");
      // (string(yytext), "CONST_INT");
      yylval = (YYSTYPE) obj;
      return CONST_INT;
    }
{FLOAT} { 
      Symbol_Info obj;
      obj.setSymbol(string(yytext));
      obj.setToken("CONST_FLOAT");
      yylval = (YYSTYPE) obj;
      return CONST_FLOAT; 
}
{ID} {  
      Symbol_Info obj;
      obj.setSymbol(string(yytext));
      obj.setToken("ID");
      yylval = (YYSTYPE) obj;
      return ID; 
}

{WID} {
      yyerror("Error: Invalid variable name\n");
}
{WFLOAT} {
      yyerror("Error: Invalid decimal number\n");
}

[\n]     { line_cnt++; }
{delim}+ { /* ignore white space */ }

%%
