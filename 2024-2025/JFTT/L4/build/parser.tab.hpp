/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_PARSER_TAB_HPP_INCLUDED
# define YY_YY_BUILD_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    pidentifier = 258,             /* pidentifier  */
    NUM = 259,                     /* NUM  */
    PROGRAM = 260,                 /* PROGRAM  */
    PROCEDURE = 261,               /* PROCEDURE  */
    PROGRAM_BEGIN = 262,           /* PROGRAM_BEGIN  */
    END = 263,                     /* END  */
    IS = 264,                      /* IS  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    ENDIF = 267,                   /* ENDIF  */
    THEN = 268,                    /* THEN  */
    FROM = 269,                    /* FROM  */
    WHILE = 270,                   /* WHILE  */
    DO = 271,                      /* DO  */
    ENDWHILE = 272,                /* ENDWHILE  */
    REPEAT = 273,                  /* REPEAT  */
    UNTIL = 274,                   /* UNTIL  */
    FOR = 275,                     /* FOR  */
    TO = 276,                      /* TO  */
    DOWNTO = 277,                  /* DOWNTO  */
    ENDFOR = 278,                  /* ENDFOR  */
    READ = 279,                    /* READ  */
    WRITE = 280,                   /* WRITE  */
    EQUAL = 281,                   /* EQUAL  */
    NOTEQUAL = 282,                /* NOTEQUAL  */
    GREATER = 283,                 /* GREATER  */
    LESS = 284,                    /* LESS  */
    GREATEREQUAL = 285,            /* GREATEREQUAL  */
    LESSEQUAL = 286,               /* LESSEQUAL  */
    PLUS = 287,                    /* PLUS  */
    MINUS = 288,                   /* MINUS  */
    MULTIPLY = 289,                /* MULTIPLY  */
    DIVIDE = 290,                  /* DIVIDE  */
    MODULO = 291,                  /* MODULO  */
    ASSIGN = 292,                  /* ASSIGN  */
    COLON = 293,                   /* COLON  */
    SEMICOLON = 294,               /* SEMICOLON  */
    COMMA = 295,                   /* COMMA  */
    LPAREN = 296,                  /* LPAREN  */
    RPAREN = 297,                  /* RPAREN  */
    LBRACKET = 298,                /* LBRACKET  */
    RBRACKET = 299,                /* RBRACKET  */
    T = 300                        /* T  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "source/parser.y"

    char* str;
    int64_t num;
    void* node;

#line 115 "build/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_TAB_HPP_INCLUDED  */
