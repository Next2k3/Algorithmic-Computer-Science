%option noyywrap

%{
#include "../build/parser.tab.hpp"
#include <iostream>
#include <cerrno>
#include <cstdint>

extern int yylineno;
std::string currentLine;

int yylex();
void yyerror(const char *s);
%}

NUM         [0-9]+ 
ID          [_a-z]+
COMMENT     \#[^\n]*

%%
"PROGRAM"       { currentLine += yytext; return PROGRAM; }
"PROCEDURE"     { currentLine += yytext; return PROCEDURE; }
"BEGIN"         { currentLine += yytext; return PROGRAM_BEGIN; }
"END"           { currentLine += yytext; return END; }
"IS"            { currentLine += yytext; return IS; }
"IF"            { currentLine += yytext; return IF; }
"THEN"          { currentLine += yytext; return THEN; }
"ELSE"          { currentLine += yytext; return ELSE; }
"ENDIF"         { currentLine += yytext; return ENDIF; }
"FROM"          { currentLine += yytext; return FROM; }
"WHILE"         { currentLine += yytext; return WHILE; }
"DO"            { currentLine += yytext; return DO; }
"ENDWHILE"      { currentLine += yytext; return ENDWHILE; }
"REPEAT"        { currentLine += yytext; return REPEAT; }
"UNTIL"         { currentLine += yytext; return UNTIL; } 
"FOR"           { currentLine += yytext; return FOR; }
"TO"            { currentLine += yytext; return TO; }
"DOWNTO"        { currentLine += yytext; return DOWNTO; }
"ENDFOR"        { currentLine += yytext; return ENDFOR; }
"READ"          { currentLine += yytext; return READ; }
"WRITE"         { currentLine += yytext; return WRITE; }
"T"		        { currentLine += yytext; return T; }
"="             { currentLine += yytext; return EQUAL; }
"!="            { currentLine += yytext; return NOTEQUAL; }
">"             { currentLine += yytext; return GREATER; }
"<"             { currentLine += yytext; return LESS; }
">="            { currentLine += yytext; return GREATEREQUAL; }
"<="            { currentLine += yytext; return LESSEQUAL; }
"+"             { currentLine += yytext; return PLUS; }
"-"             { currentLine += yytext; return MINUS; }
"*"             { currentLine += yytext; return MULTIPLY; }
"/"             { currentLine += yytext; return DIVIDE; }
"%"             { currentLine += yytext; return MODULO; }
":="            { currentLine += yytext; return ASSIGN; }
":"             { currentLine += yytext; return COLON; }
";"             { currentLine += yytext; return SEMICOLON; }
","             { currentLine += yytext; return COMMA; }
"("             { currentLine += yytext; return LPAREN; }
")"             { currentLine += yytext; return RPAREN; }
"["             { currentLine += yytext; return LBRACKET; }
"]"             { currentLine += yytext; return RBRACKET; }
{COMMENT}       { currentLine += yytext; } // Ignoruj komentarze
{NUM}           {
                    currentLine += yytext;
                    errno = 0;
                    long long num = strtoll(yytext, NULL, 10);
                    if (errno == ERANGE || num > INT64_MAX || num < 0) {
                        std::cerr << "Error: number out of range at line "<< yylineno<<": " << yytext << std::endl;
                        std::exit(1);
                    }
                    yylval.num = num;
                    return NUM;
}
{ID}            { currentLine += yytext; yylval.str = strdup(yytext); return pidentifier; }
[ \t]+          { currentLine += yytext; };
\n              {
                    currentLine = "";
                    yylineno++;
                }
.               { 
                    currentLine += yytext; 
                    std::cerr << "Error:  " << yytext << " was not declared " << std::endl;
                    std::cerr << yylineno <<" | "<< currentLine << std::endl;
                    std::exit(1); 
                }

%%

