%{
#include <stdio.h>
int yywrap();
int doc = 0;
int include = 0;
%}

%x INCLUDE
%x QUOTES 
%x STRING
%x COMMENT_SINGLELINE
%x COMMENT_SINGLELINE_DOC
%x COMMENT_MULTILINE
%x COMMENT_MULTILINE_DOC

%%

"#include"				 { ECHO; BEGIN(INCLUDE); }
<INCLUDE>\"				 { ECHO; if(include) {BEGIN(INITIAL);printf("\n");include = 0; } if(!include) {include++;}}
<INCLUDE>\>				 { ECHO; BEGIN(INITIAL); }

\"						 { ECHO; BEGIN(QUOTES); }
<QUOTES>\"				 { ECHO; BEGIN(INITIAL); }
<QUOTES>.				 { ECHO; }

\(						 { ECHO; BEGIN(STRING); }
<STRING>\)				 { ECHO; BEGIN(INITIAL); }
<STRING>.				 { ECHO; }

"//"|"/\\\n/"            				{ BEGIN(COMMENT_SINGLELINE); }
<COMMENT_SINGLELINE>[^\\\n]*\\\n        ;   	
<COMMENT_SINGLELINE>\n   				{ BEGIN(INITIAL); }
<COMMENT_SINGLELINE>.*	 				;

"///"|"//!"              		{ if(doc) { ECHO; } BEGIN(COMMENT_SINGLELINE_DOC); }  
<COMMENT_SINGLELINE_DOC>\n		{ if(doc) { ECHO; } BEGIN(INITIAL); }
<COMMENT_SINGLELINE_DOC>.*		{ if(doc) ECHO; }

"/*"                     	{ BEGIN(COMMENT_MULTILINE); }
<COMMENT_MULTILINE>[^\*]*	;
<COMMENT_MULTILINE>\*+[^/] 	;
<COMMENT_MULTILINE>"*"+"/"	{ BEGIN(INITIAL); }

"/**/"	{ printf(" "); BEGIN(INITIAL); }
  
"/**"|"/*!"				 		{ if(doc) { ECHO;} BEGIN(COMMENT_MULTILINE_DOC); }
<COMMENT_MULTILINE_DOC>[^\*]*	{ if(doc)  ECHO; }
<COMMENT_MULTILINE_DOC>\*+[^/]	{ if(doc)  ECHO; }
<COMMENT_MULTILINE_DOC>"*"+"/"	{ if(doc) { ECHO; } BEGIN(INITIAL);}

.		{ ECHO; } 

%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--doc") == 0) {
        doc = 1; 
    }
    return yylex();
}


