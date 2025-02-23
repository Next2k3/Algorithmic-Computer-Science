/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "source/parser.y"

#include <iostream>
#include <memory>
#include "AST.hpp"
#include <cstdint>

extern int yylex();
extern void yyerror(const char *s);
extern int yylineno;
extern std::string currentLine;
extern char* yytext;

std::unique_ptr<ASTNode> root;

inline ASTNode* cast(void* ptr) { return static_cast<ASTNode*>(ptr); }
inline void* to_void(ASTNode* node) { return static_cast<void*>(node); }


#line 90 "build/parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_pidentifier = 3,                /* pidentifier  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_PROGRAM = 5,                    /* PROGRAM  */
  YYSYMBOL_PROCEDURE = 6,                  /* PROCEDURE  */
  YYSYMBOL_PROGRAM_BEGIN = 7,              /* PROGRAM_BEGIN  */
  YYSYMBOL_END = 8,                        /* END  */
  YYSYMBOL_IS = 9,                         /* IS  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_ENDIF = 12,                     /* ENDIF  */
  YYSYMBOL_THEN = 13,                      /* THEN  */
  YYSYMBOL_FROM = 14,                      /* FROM  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_DO = 16,                        /* DO  */
  YYSYMBOL_ENDWHILE = 17,                  /* ENDWHILE  */
  YYSYMBOL_REPEAT = 18,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 19,                     /* UNTIL  */
  YYSYMBOL_FOR = 20,                       /* FOR  */
  YYSYMBOL_TO = 21,                        /* TO  */
  YYSYMBOL_DOWNTO = 22,                    /* DOWNTO  */
  YYSYMBOL_ENDFOR = 23,                    /* ENDFOR  */
  YYSYMBOL_READ = 24,                      /* READ  */
  YYSYMBOL_WRITE = 25,                     /* WRITE  */
  YYSYMBOL_EQUAL = 26,                     /* EQUAL  */
  YYSYMBOL_NOTEQUAL = 27,                  /* NOTEQUAL  */
  YYSYMBOL_GREATER = 28,                   /* GREATER  */
  YYSYMBOL_LESS = 29,                      /* LESS  */
  YYSYMBOL_GREATEREQUAL = 30,              /* GREATEREQUAL  */
  YYSYMBOL_LESSEQUAL = 31,                 /* LESSEQUAL  */
  YYSYMBOL_PLUS = 32,                      /* PLUS  */
  YYSYMBOL_MINUS = 33,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 34,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 35,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 36,                    /* MODULO  */
  YYSYMBOL_ASSIGN = 37,                    /* ASSIGN  */
  YYSYMBOL_COLON = 38,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 39,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 40,                     /* COMMA  */
  YYSYMBOL_LPAREN = 41,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 42,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 43,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 44,                  /* RBRACKET  */
  YYSYMBOL_T = 45,                         /* T  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_program_all = 47,               /* program_all  */
  YYSYMBOL_procedures = 48,                /* procedures  */
  YYSYMBOL_main = 49,                      /* main  */
  YYSYMBOL_commands = 50,                  /* commands  */
  YYSYMBOL_command = 51,                   /* command  */
  YYSYMBOL_proc_head = 52,                 /* proc_head  */
  YYSYMBOL_proc_call = 53,                 /* proc_call  */
  YYSYMBOL_declarations = 54,              /* declarations  */
  YYSYMBOL_args_decl = 55,                 /* args_decl  */
  YYSYMBOL_args = 56,                      /* args  */
  YYSYMBOL_expression = 57,                /* expression  */
  YYSYMBOL_condition = 58,                 /* condition  */
  YYSYMBOL_value = 59,                     /* value  */
  YYSYMBOL_identifier = 60,                /* identifier  */
  YYSYMBOL_NUM_T = 61                      /* NUM_T  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   280

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   300


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    43,    43,    53,    62,    71,    77,    84,    94,   103,
     111,   118,   126,   134,   141,   148,   157,   166,   172,   178,
     187,   197,   207,   214,   221,   225,   232,   239,   246,   250,
     257,   264,   271,   274,   282,   290,   298,   306,   318,   326,
     334,   342,   350,   358,   369,   373,   380,   384,   388,   395,
     398
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "pidentifier", "NUM",
  "PROGRAM", "PROCEDURE", "PROGRAM_BEGIN", "END", "IS", "IF", "ELSE",
  "ENDIF", "THEN", "FROM", "WHILE", "DO", "ENDWHILE", "REPEAT", "UNTIL",
  "FOR", "TO", "DOWNTO", "ENDFOR", "READ", "WRITE", "EQUAL", "NOTEQUAL",
  "GREATER", "LESS", "GREATEREQUAL", "LESSEQUAL", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "MODULO", "ASSIGN", "COLON", "SEMICOLON", "COMMA",
  "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "T", "$accept",
  "program_all", "procedures", "main", "commands", "command", "proc_head",
  "proc_call", "declarations", "args_decl", "args", "expression",
  "condition", "value", "identifier", "NUM_T", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-25)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -25,     5,    22,   -25,    -7,    31,   -25,    23,   -24,     9,
       7,   248,     2,     1,    48,    15,    -4,     8,     8,   248,
      50,    66,     8,   133,   -25,    36,    39,   248,    74,   -25,
      76,    16,   248,     3,   -25,    83,    42,    87,    12,    49,
      78,   249,   -25,   -25,    84,   146,    85,    62,    63,   -25,
     -25,   -25,     8,   159,    60,   -25,     4,   -25,   170,   248,
     -25,    15,   -25,    28,    61,    71,   248,     8,     8,     8,
       8,     8,     8,   248,     8,     8,   -25,   -25,    67,   -12,
     -25,    15,   -25,   104,   -25,   183,    77,   119,   -25,   -25,
     -25,   122,   -25,   -25,   -25,   -25,   -25,   -25,   194,    88,
      52,   -25,     8,     8,     8,     8,     8,    86,   -25,   -25,
     -25,   -25,   248,   -25,   -25,   -25,     8,     8,   -25,   -25,
     -25,   -25,   -25,    15,   210,   107,   110,    91,   -25,   248,
     248,   -25,   221,   237,   -25,   -25
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     1,     0,     0,     2,     0,     0,     0,
      24,     0,     0,     0,     0,     0,    46,     0,     0,     0,
       0,     0,     0,     0,     9,     0,     0,     0,     0,    28,
       0,     0,     0,     0,    49,     0,     0,     0,     0,    46,
       0,     0,    45,    44,     0,     0,     0,     0,     0,     7,
       8,    17,     0,     0,    22,    29,     0,    20,     0,     0,
      50,     0,    31,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,    19,     0,    32,
       6,     0,    26,     0,     4,     0,     0,     0,    21,    47,
      48,     0,    38,    39,    40,    41,    42,    43,     0,     0,
       0,    10,     0,     0,     0,     0,     0,     0,    27,     3,
      25,    30,     0,    12,    13,    14,     0,     0,    33,    34,
      35,    36,    37,     0,     0,     0,     0,     0,    11,     0,
       0,    23,     0,     0,    15,    16
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -25,   -25,   -25,   -25,   -19,   -20,   -25,   -25,   114,   -25,
     -25,   -25,   -17,    -8,    14,    -9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     6,    23,    24,     9,    25,    12,    31,
      63,    78,    40,    41,    26,    43
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      45,    44,     7,    50,    29,     3,    36,    82,    53,    27,
      59,    39,    34,    58,    48,    64,    34,    13,    14,    34,
     102,   103,   104,   105,   106,    50,    10,     4,     5,    65,
      11,    42,    42,    50,     8,    47,    42,    37,    50,    38,
      85,    35,    28,    28,    79,    35,    30,    91,    35,    83,
      15,    10,    86,    46,    98,    32,    56,    99,    57,    92,
      93,    94,    95,    96,    97,    50,    42,   100,    87,    39,
      88,    50,   107,   116,   117,    51,    52,    54,    50,    55,
      61,    42,    42,    42,    42,    42,    42,    60,    42,    42,
      62,    66,    38,   124,   118,   119,   120,   121,   122,    75,
      73,    76,    77,    81,    50,    89,   101,   108,   125,   126,
     132,   133,    50,    50,   127,    90,    42,    42,    42,    42,
      42,   110,   111,   129,   123,    16,   130,   115,    33,     0,
      42,    42,    17,   112,   113,   131,    16,    18,     0,     0,
      19,    49,    20,    17,     0,     0,    21,    22,    18,    16,
       0,    19,     0,    20,     0,     0,    17,    21,    22,     0,
       0,    18,    16,     0,    19,    74,    20,    80,     0,    17,
      21,    22,     0,    16,    18,     0,     0,    19,    84,    20,
      17,     0,     0,    21,    22,    18,    16,     0,    19,     0,
      20,   109,     0,    17,    21,    22,     0,    16,    18,     0,
       0,    19,     0,    20,    17,     0,     0,    21,    22,    18,
       0,   114,    19,    16,    20,     0,     0,     0,    21,    22,
      17,     0,   128,     0,    16,    18,     0,     0,    19,     0,
      20,    17,     0,     0,    21,    22,    18,     0,     0,    19,
      16,    20,     0,     0,   134,    21,    22,    17,     0,     0,
       0,    16,    18,     0,     0,    19,     0,    20,    17,     0,
     135,    21,    22,    18,     0,     0,    19,     0,    20,     0,
       0,     0,    21,    22,     0,    67,    68,    69,    70,    71,
      72
};

static const yytype_int16 yycheck[] =
{
      19,    18,     9,    23,     3,     0,    15,     3,    27,     7,
       7,     3,     4,    32,    22,     3,     4,    41,     9,     4,
      32,    33,    34,    35,    36,    45,     3,     5,     6,    38,
       7,    17,    18,    53,     3,    21,    22,    41,    58,    43,
      59,    33,    40,    40,    52,    33,    45,    66,    33,    45,
      43,     3,    61,     3,    73,     7,    40,    74,    42,    67,
      68,    69,    70,    71,    72,    85,    52,    75,    40,     3,
      42,    91,    81,    21,    22,    39,    37,     3,    98,     3,
      38,    67,    68,    69,    70,    71,    72,     4,    74,    75,
       3,    13,    43,   112,   102,   103,   104,   105,   106,    14,
      16,    39,    39,    43,   124,    44,    39,     3,   116,   117,
     129,   130,   132,   133,   123,    44,   102,   103,   104,   105,
     106,    44,     3,    16,    38,     3,    16,    39,    14,    -1,
     116,   117,    10,    11,    12,    44,     3,    15,    -1,    -1,
      18,     8,    20,    10,    -1,    -1,    24,    25,    15,     3,
      -1,    18,    -1,    20,    -1,    -1,    10,    24,    25,    -1,
      -1,    15,     3,    -1,    18,    19,    20,     8,    -1,    10,
      24,    25,    -1,     3,    15,    -1,    -1,    18,     8,    20,
      10,    -1,    -1,    24,    25,    15,     3,    -1,    18,    -1,
      20,     8,    -1,    10,    24,    25,    -1,     3,    15,    -1,
      -1,    18,    -1,    20,    10,    -1,    -1,    24,    25,    15,
      -1,    17,    18,     3,    20,    -1,    -1,    -1,    24,    25,
      10,    -1,    12,    -1,     3,    15,    -1,    -1,    18,    -1,
      20,    10,    -1,    -1,    24,    25,    15,    -1,    -1,    18,
       3,    20,    -1,    -1,    23,    24,    25,    10,    -1,    -1,
      -1,     3,    15,    -1,    -1,    18,    -1,    20,    10,    -1,
      23,    24,    25,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    -1,    24,    25,    -1,    26,    27,    28,    29,    30,
      31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    47,    48,     0,     5,     6,    49,     9,     3,    52,
       3,     7,    54,    41,     9,    43,     3,    10,    15,    18,
      20,    24,    25,    50,    51,    53,    60,     7,    40,     3,
      45,    55,     7,    54,     4,    33,    61,    41,    43,     3,
      58,    59,    60,    61,    58,    50,     3,    60,    59,     8,
      51,    39,    37,    50,     3,     3,    40,    42,    50,     7,
       4,    38,     3,    56,     3,    61,    13,    26,    27,    28,
      29,    30,    31,    16,    19,    14,    39,    39,    57,    59,
       8,    43,     3,    45,     8,    50,    61,    40,    42,    44,
      44,    50,    59,    59,    59,    59,    59,    59,    50,    58,
      59,    39,    32,    33,    34,    35,    36,    61,     3,     8,
      44,     3,    11,    12,    17,    39,    21,    22,    59,    59,
      59,    59,    59,    38,    50,    59,    59,    61,    12,    16,
      16,    44,    50,    50,    23,    23
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    48,    49,    49,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      52,    53,    54,    54,    54,    54,    55,    55,    55,    55,
      56,    56,    57,    57,    57,    57,    57,    57,    58,    58,
      58,    58,    58,    58,    59,    59,    60,    60,    60,    61,
      61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     8,     7,     0,     6,     5,     2,     1,
       4,     7,     5,     5,     5,     9,     9,     2,     3,     3,
       4,     4,     3,     8,     1,     6,     3,     4,     1,     2,
       3,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     4,     4,     1,
       2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program_all: procedures main  */
#line 43 "source/parser.y"
                    {
        auto programNode = new ProgramNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        root = std::unique_ptr<ASTNode>(programNode);
    }
#line 1255 "build/parser.tab.cpp"
    break;

  case 3: /* procedures: procedures PROCEDURE proc_head IS declarations PROGRAM_BEGIN commands END  */
#line 53 "source/parser.y"
                                                                              {
        auto procedureNode = new ProcedureNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-7].node))),
            std::unique_ptr<ProcHeadNode>(static_cast<ProcHeadNode*>((yyvsp[-5].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-3].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(procedureNode);
    }
#line 1269 "build/parser.tab.cpp"
    break;

  case 4: /* procedures: procedures PROCEDURE proc_head IS PROGRAM_BEGIN commands END  */
#line 62 "source/parser.y"
                                                                   {
        auto procedureNode = new ProcedureNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-6].node))),
            std::unique_ptr<ProcHeadNode>(static_cast<ProcHeadNode*>((yyvsp[-4].node))),
            nullptr,
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(procedureNode);
    }
#line 1283 "build/parser.tab.cpp"
    break;

  case 5: /* procedures: %empty  */
#line 71 "source/parser.y"
                  {
        (yyval.node) = to_void(nullptr);
    }
#line 1291 "build/parser.tab.cpp"
    break;

  case 6: /* main: PROGRAM IS declarations PROGRAM_BEGIN commands END  */
#line 77 "source/parser.y"
                                                       { 
        auto mainNode = new MainNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-3].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(mainNode);
    }
#line 1303 "build/parser.tab.cpp"
    break;

  case 7: /* main: PROGRAM IS PROGRAM_BEGIN commands END  */
#line 84 "source/parser.y"
                                            {
        auto mainNode = new MainNode(
            std::unique_ptr<ASTNode>(cast(nullptr)),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(mainNode);
    }
#line 1315 "build/parser.tab.cpp"
    break;

  case 8: /* commands: commands command  */
#line 94 "source/parser.y"
                     {
        auto commandsNode = dynamic_cast<CommandsNode*>(cast((yyvsp[-1].node)));
        if (!commandsNode) {
            yyerror("Invalid cast to CommandsNode");
            YYABORT;
        }
        commandsNode->addCommand(std::unique_ptr<ASTNode>(cast((yyvsp[0].node))));
        (yyval.node) = to_void(commandsNode);
    }
#line 1329 "build/parser.tab.cpp"
    break;

  case 9: /* commands: command  */
#line 103 "source/parser.y"
              {
        auto commandsNode = new CommandsNode();
        commandsNode->addCommand(std::unique_ptr<ASTNode>(cast((yyvsp[0].node))));
        (yyval.node) = to_void(commandsNode);
    }
#line 1339 "build/parser.tab.cpp"
    break;

  case 10: /* command: identifier ASSIGN expression SEMICOLON  */
#line 111 "source/parser.y"
                                           {
        auto assignmentNode = new AssignmentNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-3].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(assignmentNode);
    }
#line 1351 "build/parser.tab.cpp"
    break;

  case 11: /* command: IF condition THEN commands ELSE commands ENDIF  */
#line 118 "source/parser.y"
                                                     {
        auto ifNode = new IfNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-5].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-3].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(ifNode);
    }
#line 1364 "build/parser.tab.cpp"
    break;

  case 12: /* command: IF condition THEN commands ENDIF  */
#line 126 "source/parser.y"
                                       {
        auto ifNode = new IfNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-3].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node))),
            std::unique_ptr<ASTNode>(cast(nullptr))
        );
        (yyval.node) = to_void(ifNode);
    }
#line 1377 "build/parser.tab.cpp"
    break;

  case 13: /* command: WHILE condition DO commands ENDWHILE  */
#line 134 "source/parser.y"
                                           {
        auto whileNode = new WhileNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-3].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(whileNode);
    }
#line 1389 "build/parser.tab.cpp"
    break;

  case 14: /* command: REPEAT commands UNTIL condition SEMICOLON  */
#line 141 "source/parser.y"
                                                {
        auto repeatNode = new RepeatNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-3].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(repeatNode);
    }
#line 1401 "build/parser.tab.cpp"
    break;

  case 15: /* command: FOR pidentifier FROM value TO value DO commands ENDFOR  */
#line 148 "source/parser.y"
                                                             {
        auto forToNode = new ForToNode(
            (yyvsp[-7].str),
            std::unique_ptr<ASTNode>(cast((yyvsp[-5].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-3].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(forToNode);
    }
#line 1415 "build/parser.tab.cpp"
    break;

  case 16: /* command: FOR pidentifier FROM value DOWNTO value DO commands ENDFOR  */
#line 157 "source/parser.y"
                                                                 {
        auto forDownToNode = new ForDownToNode(
            (yyvsp[-7].str),
            std::unique_ptr<ASTNode>(cast((yyvsp[-5].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-3].node))),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(forDownToNode);
    }
#line 1429 "build/parser.tab.cpp"
    break;

  case 17: /* command: proc_call SEMICOLON  */
#line 166 "source/parser.y"
                          {
        auto procallCommandNode = new ProcallCommandNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(procallCommandNode);
    }
#line 1440 "build/parser.tab.cpp"
    break;

  case 18: /* command: READ identifier SEMICOLON  */
#line 172 "source/parser.y"
                                {
        auto readNode = new ReadNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(readNode);
    }
#line 1451 "build/parser.tab.cpp"
    break;

  case 19: /* command: WRITE value SEMICOLON  */
#line 178 "source/parser.y"
                            {
        auto writeNode = new WriteNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(writeNode);  
    }
#line 1462 "build/parser.tab.cpp"
    break;

  case 20: /* proc_head: pidentifier LPAREN args_decl RPAREN  */
#line 187 "source/parser.y"
                                        {
        auto procHeadNode = new ProcHeadNode(
            (yyvsp[-3].str),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))
        );
        (yyval.node) = to_void(procHeadNode);  
    }
#line 1474 "build/parser.tab.cpp"
    break;

  case 21: /* proc_call: pidentifier LPAREN args RPAREN  */
#line 197 "source/parser.y"
                                   {
        auto procCallNode  = new ProcCallNode (
            (yyvsp[-3].str),
            std::unique_ptr<ASTNode>(cast((yyvsp[-1].node)))       
        );
        (yyval.node) = to_void(procCallNode );  
    }
#line 1486 "build/parser.tab.cpp"
    break;

  case 22: /* declarations: declarations COMMA pidentifier  */
#line 207 "source/parser.y"
                                   {
        auto declarationsNode = new DeclarationsNode();
        auto declarationNode = new DeclarationNode((yyvsp[0].str));
        declarationsNode->addDeclaration(std::unique_ptr<ASTNode>(cast(declarationNode)));
        declarationsNode->addDeclaration(std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))));
        (yyval.node) = to_void(declarationsNode);
    }
#line 1498 "build/parser.tab.cpp"
    break;

  case 23: /* declarations: declarations COMMA pidentifier LBRACKET NUM_T COLON NUM_T RBRACKET  */
#line 214 "source/parser.y"
                                                                         {
        auto declarationsNode = new DeclarationsNode();
        auto declarationNode = new DeclarationNode((yyvsp[-5].str), (yyvsp[-3].num), (yyvsp[-1].num));
        declarationsNode->addDeclaration(std::unique_ptr<ASTNode>(cast(declarationNode)));
        declarationsNode->addDeclaration(std::unique_ptr<ASTNode>(cast((yyvsp[-7].node))));
        (yyval.node) = to_void(declarationsNode);
    }
#line 1510 "build/parser.tab.cpp"
    break;

  case 24: /* declarations: pidentifier  */
#line 221 "source/parser.y"
                  {
        auto declarationNode = new DeclarationNode((yyvsp[0].str));
        (yyval.node) = to_void(declarationNode);
    }
#line 1519 "build/parser.tab.cpp"
    break;

  case 25: /* declarations: pidentifier LBRACKET NUM_T COLON NUM_T RBRACKET  */
#line 225 "source/parser.y"
                                                      {
        auto declarationNode = new DeclarationNode((yyvsp[-5].str), (yyvsp[-3].num), (yyvsp[-1].num));
        (yyval.node) = to_void(declarationNode);
    }
#line 1528 "build/parser.tab.cpp"
    break;

  case 26: /* args_decl: args_decl COMMA pidentifier  */
#line 232 "source/parser.y"
                                {
        auto argsdeclsNode = new ArgsdeclsNode();
        auto argsdeclNode = new ArgsdeclNode((yyvsp[0].str));
        argsdeclsNode->addArgsdecl(std::unique_ptr<ASTNode>(cast(argsdeclNode)));
        argsdeclsNode->addArgsdecl(std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))));
        (yyval.node) = to_void(argsdeclsNode);
    }
#line 1540 "build/parser.tab.cpp"
    break;

  case 27: /* args_decl: args_decl COMMA T pidentifier  */
#line 239 "source/parser.y"
                                    {
        auto argsdeclsNode = new ArgsdeclsNode();
        auto argsdeclNode = new ArgsdeclNode((yyvsp[0].str), true);
        argsdeclsNode->addArgsdecl(std::unique_ptr<ASTNode>(cast(argsdeclNode)));
        argsdeclsNode->addArgsdecl(std::unique_ptr<ASTNode>(cast((yyvsp[-3].node))));
        (yyval.node) = to_void(argsdeclsNode);
    }
#line 1552 "build/parser.tab.cpp"
    break;

  case 28: /* args_decl: pidentifier  */
#line 246 "source/parser.y"
                  {
        auto argsdeclNode = new ArgsdeclNode((yyvsp[0].str));
        (yyval.node) = to_void(argsdeclNode);
    }
#line 1561 "build/parser.tab.cpp"
    break;

  case 29: /* args_decl: T pidentifier  */
#line 250 "source/parser.y"
                    {
        auto argsdeclNode = new ArgsdeclNode((yyvsp[0].str), true);
        (yyval.node) = to_void(argsdeclNode);
    }
#line 1570 "build/parser.tab.cpp"
    break;

  case 30: /* args: args COMMA pidentifier  */
#line 257 "source/parser.y"
                          {
        auto argsNode = new ArgsNode();
        auto argNode = new ArgNode((yyvsp[0].str));
        argsNode->addArg(std::unique_ptr<ASTNode>(cast(argNode)));
        argsNode->addArg(std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))));
        (yyval.node) = to_void(argsNode);
    }
#line 1582 "build/parser.tab.cpp"
    break;

  case 31: /* args: pidentifier  */
#line 264 "source/parser.y"
                  {
        auto argNode = new ArgNode((yyvsp[0].str));
        (yyval.node) = to_void(argNode);
    }
#line 1591 "build/parser.tab.cpp"
    break;

  case 32: /* expression: value  */
#line 271 "source/parser.y"
          {
        (yyval.node) = (yyvsp[0].node); 
    }
#line 1599 "build/parser.tab.cpp"
    break;

  case 33: /* expression: value PLUS value  */
#line 274 "source/parser.y"
                       {
        auto expressionNode = new ExpressionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            "+", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(expressionNode);  // Dodajemy poprawnie węzeł
    }
#line 1612 "build/parser.tab.cpp"
    break;

  case 34: /* expression: value MINUS value  */
#line 282 "source/parser.y"
                        {
        auto expressionNode = new ExpressionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            "-", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(expressionNode);  // Dodajemy poprawnie węzeł
    }
#line 1625 "build/parser.tab.cpp"
    break;

  case 35: /* expression: value MULTIPLY value  */
#line 290 "source/parser.y"
                           {
        auto expressionNode = new ExpressionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            "*", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(expressionNode);  // Dodajemy poprawnie węzeł
    }
#line 1638 "build/parser.tab.cpp"
    break;

  case 36: /* expression: value DIVIDE value  */
#line 298 "source/parser.y"
                         {
        auto expressionNode = new ExpressionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            "/", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(expressionNode);  // Dodajemy poprawnie węzeł
    }
#line 1651 "build/parser.tab.cpp"
    break;

  case 37: /* expression: value MODULO value  */
#line 306 "source/parser.y"
                         {
        auto expressionNode = new ExpressionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            "%", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(expressionNode);  // Dodajemy poprawnie węzeł
    }
#line 1664 "build/parser.tab.cpp"
    break;

  case 38: /* condition: value EQUAL value  */
#line 318 "source/parser.y"
                      {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            "=", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
#line 1677 "build/parser.tab.cpp"
    break;

  case 39: /* condition: value NOTEQUAL value  */
#line 326 "source/parser.y"
                           {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            "!=", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
#line 1690 "build/parser.tab.cpp"
    break;

  case 40: /* condition: value GREATER value  */
#line 334 "source/parser.y"
                          {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            ">", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
#line 1703 "build/parser.tab.cpp"
    break;

  case 41: /* condition: value LESS value  */
#line 342 "source/parser.y"
                       {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            "<", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
#line 1716 "build/parser.tab.cpp"
    break;

  case 42: /* condition: value GREATEREQUAL value  */
#line 350 "source/parser.y"
                               {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            ">=", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
#line 1729 "build/parser.tab.cpp"
    break;

  case 43: /* condition: value LESSEQUAL value  */
#line 358 "source/parser.y"
                            {
    	auto conditionNode = new ConditionNode(
            std::unique_ptr<ASTNode>(cast((yyvsp[-2].node))), 
            "<=", 
            std::unique_ptr<ASTNode>(cast((yyvsp[0].node)))
        );
        (yyval.node) = to_void(conditionNode);  // Dodajemy poprawnie węzeł
    }
#line 1742 "build/parser.tab.cpp"
    break;

  case 44: /* value: NUM_T  */
#line 369 "source/parser.y"
          {
        auto valueNode = new ValueNode((yyvsp[0].num));
        (yyval.node) = to_void(valueNode);
    }
#line 1751 "build/parser.tab.cpp"
    break;

  case 45: /* value: identifier  */
#line 373 "source/parser.y"
                 {
        auto valueNode = new ValueNode(std::unique_ptr<ASTNode>(cast((yyvsp[0].node))));
        (yyval.node) = to_void(valueNode);
    }
#line 1760 "build/parser.tab.cpp"
    break;

  case 46: /* identifier: pidentifier  */
#line 380 "source/parser.y"
                {
        auto identifierNode = new IdentifierNode((yyvsp[0].str));
        (yyval.node) = to_void(identifierNode);
    }
#line 1769 "build/parser.tab.cpp"
    break;

  case 47: /* identifier: pidentifier LBRACKET pidentifier RBRACKET  */
#line 384 "source/parser.y"
                                                {
        auto identifierNode = new IdentifierNode((yyvsp[-3].str), (yyvsp[-1].str));
        (yyval.node) = to_void(identifierNode);
    }
#line 1778 "build/parser.tab.cpp"
    break;

  case 48: /* identifier: pidentifier LBRACKET NUM_T RBRACKET  */
#line 388 "source/parser.y"
                                          {
        auto identifierNode = new IdentifierNode((yyvsp[-3].str), (yyvsp[-1].num));
        (yyval.node) = to_void(identifierNode);
    }
#line 1787 "build/parser.tab.cpp"
    break;

  case 49: /* NUM_T: NUM  */
#line 395 "source/parser.y"
        {
        (yyval.num) = (yyvsp[0].num);
    }
#line 1795 "build/parser.tab.cpp"
    break;

  case 50: /* NUM_T: MINUS NUM  */
#line 398 "source/parser.y"
                {
        (yyval.num) = -(yyvsp[0].num);
    }
#line 1803 "build/parser.tab.cpp"
    break;


#line 1807 "build/parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 403 "source/parser.y"


void yyerror(const char *s) {
    std::cerr << "Syntax error: "<< yytext << std::endl;
    std::cerr << yylineno <<"  | "<< currentLine << std::endl;
}

