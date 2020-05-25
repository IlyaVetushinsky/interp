%option noyywrap
%option c++
%{
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Calc4.h"
#include "Calc4.tab.hpp"
void yyerror(char *);
%}
%%
[a-z] {
 yylval.sIndex = *yytext - 'a';
 return VARIABLE;
 }
[0-9]+ {
 yylval.iValue = atoi(yytext);
 return INTEGER;
 }
[-()<>=+*/;:{}.] {
 return *yytext;
 }
">=" return GE;
"<=" return LE;
"==" return EQ;
"!=" return NE;
"while" return WHILE;
"if" return IF;
"else" return ELSE;
"print" return PRINT;
"goto" return GOTO;
[ \t\n]+ ; /* ignore whitespace */
. yyerror("Unknown character");
%%
int yywrap(void) {
 return 1;
}