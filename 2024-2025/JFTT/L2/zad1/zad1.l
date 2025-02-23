%{
#include <stdio.h>
int yywrap();
int yylex();
int lineNumber = 0;
int wordsCount = 0;
int lastLineEmpty = 1;
%}

%%
^[[:blank:]]*\n      { lastLineEmpty = 1; }
[[:blank:]]+         { printf(" "); lastLineEmpty = 0; }
[^ \t\n]+            { printf("%s", yytext); wordsCount++; lastLineEmpty = 0; }
\n                   { ECHO; lineNumber++; lastLineEmpty = 1; }

%%

int yywrap() {}

int main() {
	yylex();
    if (!lastLineEmpty) {
        lineNumber++;
    }
    printf("\nLines: %d\nWords: %d\n", lineNumber, wordsCount);
    return 0;
}
