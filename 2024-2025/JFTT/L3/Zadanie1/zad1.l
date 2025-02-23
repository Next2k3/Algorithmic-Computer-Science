%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "zad1y.hpp"
#define P 1234577

int yylex();
%}


%%
[ \t]  ;
^#(.|\\\n)*\n ;
\\\n   ;
[[:digit:]]+ { 
    yylval = atoi(yytext); 
    return NUM; 
}
\+                          { return PLUS; }
-                           { return MINUS; }
\*                          { return MULT; }
\/                          { return DIV; }
\%                          { return MOD; }
\^                          { return POW; }
\(                          { return BRACKET_OPEN; }
\)                          { return BRACKET_CLOSE; }
\n                          { return END; }
.                           { return ERR; }
%%
