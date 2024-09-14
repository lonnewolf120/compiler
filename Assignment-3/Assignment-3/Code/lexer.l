%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
int line_cnt = 1;

void fcout(string token, string symbol="") {
    ofstream op2;
    op2.open("token.txt", ios::app);
    if (!op2.is_open()) {
        cerr << "Error opening file.\n";
    }
    (symbol=="")?op2<<"<"<<token<<">": op2<<"<"<<token<<", "<<symbol<<">";
    op2.close();
}

void logf(string msg=""){
    ofstream output;
    output.open("log_errpr.txt", ios::app);
    output<<msg;
    output.close();
}
/*explanation for ffcout:
int c is used to say how text will be added into output, 
0 for normal <Token, Lexeme> found
other values for "already exists" type of stuff...
*/
void ffcout(string token, string symbol="", int c=0){
    ofstream output;
    output.open("log_error.txt", ios::app);
    if (!output.is_open()) {
        cerr << "Error opening log_error.txt file.\n";
    }
    
    output << "Line No: " << line_cnt << " ";
    output << "Token <" << token << "> Lexeme " << symbol << " found\n";
    if(c){
        if (token=="ID") {
        output << symbol << " variable already exists\n";
        } else if (token=="CONST_INT" || token=="CONST_FLOAT") {
            output << symbol << " value already exists\n";
        } else if (token=="CONST_CHAR") {
            output << symbol << " character already exists\n";
        }
    } 
    output.close();
}

void yyerror(string msg) {
    error_cnt++;
    ofstream output;
    output.open("log_error.txt", ios::app);
    if (!output.is_open()) {
        cerr << "Error opening file.\n";
    }    
    output << "Error at Line No: " << line_cnt <<" ";
    output << msg << "\n";
    output.close();
}

void clearOutput() {
    ofstream output;
    output.open("log_error.txt", ios::trunc);
    if (!output.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    output.close();
    output.open("token.txt", ios::trunc);
    if (!output.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    output.close();
}



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
    // st.insert(yytext, "CONST_INT"); 
    fcout("CONST_INT", yytext);  
    yylval.cvar = yytext; return ID; 
}
{CHAR}     { 
    string ch = string(1, yytext[1]);
    // st.insert(ch, "CONST_CHAR"); 
    fcout("CONST_CHAR", ch); 
    return yytext[1];
}


\'\'           { yyerror("Empty character constant "+string(yytext)); }
{WID}      { yyerror("Invalid prefix on ID or invalid suffix on Number " + std::string(yytext)); }
{WFLOAT}   { yyerror("Ill formed number " + std::string(yytext)); }
{delim}    { /* Ignore whitespace */ }
.          { yyerror("unrecognized character: " + std::string(yytext)); }
%%
