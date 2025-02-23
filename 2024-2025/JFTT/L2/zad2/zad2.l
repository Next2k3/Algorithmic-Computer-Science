%{
#include <stdio.h>
int yywrap();
int x=0;
%}

%x STRING
%x QUOTES
%x COMMENT

%%
\(						 { ECHO; BEGIN(STRING); }
<STRING>--.*\)		     { BEGIN(INITIAL); }
<STRING>\".*\"			 { ECHO; }		 	
<STRING>\)				 { ECHO; BEGIN(INITIAL); }
<STRING>.				 { ECHO; }

\"						 { ECHO; BEGIN(QUOTES); }
<QUOTES>\"				 { ECHO; BEGIN(INITIAL); }
<QUOTES>.				 { ECHO; }

^[[:blank:]]*--.*\n     ; 
(^|[[:space:]])--       BEGIN(COMMENT);
([[space]]?)--          BEGIN(COMMENT);

<COMMENT>[^\n]*         ;
<COMMENT>\n             { BEGIN(INITIAL); ECHO; }

%%

int yywrap() {
    return 1;
}

int main() {
    return yylex();
}

