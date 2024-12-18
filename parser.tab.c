/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include "hashtable.h"
    #include "garbagecollection.h"
    #include "lexer.h"

    int array_size;
    int twod_array_size_row;
    int twod_array_size_col;

    extern int yylineno;
    extern char current_token_text[];

    void yyerror(const char *s) {
        fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
        fprintf(stderr, "Current token: %s\n", current_token_text);
    }

    void enter_scope();
    void exit_scope();

    int evaluate_condition(int condition) {
        return condition;
    }

    int condvalue;
    int temp;
    int condition_met;


/* Line 371 of yacc.c  */
#line 102 "parser.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     FLOAT_NUMBER = 259,
     STRING_LITERAL = 260,
     EQUALS = 261,
     SEMICOLON = 262,
     PLUS = 263,
     MINUS = 264,
     MULTIPLY = 265,
     DIVIDE = 266,
     LPAR = 267,
     RPAR = 268,
     LCB = 269,
     RCB = 270,
     MAIN = 271,
     LIBDEF = 272,
     CALL = 273,
     VAR = 274,
     FILENAME = 275,
     IDENT = 276,
     LSB = 277,
     RSB = 278,
     USER_INPUT = 279,
     COMMA = 280,
     IMPORT = 281,
     IF = 282,
     ELSE = 283,
     EQ = 284,
     NEQ = 285,
     LT = 286,
     GT = 287,
     LEQ = 288,
     GEQ = 289,
     OR = 290,
     AND = 291,
     ELSEIF = 292
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 35 "parser.y"

    int num;
    float fnum;
    char *str;
    struct {
        int type;
        union {
            int intValue;
            float floatValue;
            char *strValue;
        } value;
    } exprval;


/* Line 387 of yacc.c  */
#line 197 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 225 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   205

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNRULES -- Number of states.  */
#define YYNSTATES  131

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    13,    20,    22,
      23,    26,    28,    31,    37,    38,    42,    43,    47,    49,
      51,    53,    55,    57,    59,    61,    63,    65,    67,    72,
      77,    82,    87,    91,    95,    99,   103,   106,   109,   110,
     121,   122,   123,   133,   134,   135,   141,   142,   153,   156,
     159,   161,   163,   165,   169,   173,   177,   181,   185,   189,
     193,   197,   201,   205,   209,   213,   217,   219,   221
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    45,    41,    -1,    41,    -1,
      45,    -1,    -1,    42,    16,    14,    46,    15,     7,    -1,
      43,    -1,    -1,    43,    44,    -1,    44,    -1,    26,    20,
      -1,    17,    14,    46,    15,     7,    -1,    -1,    46,    48,
       7,    -1,    -1,    47,    49,     7,    -1,    50,    -1,    52,
      -1,    54,    -1,    56,    -1,    64,    -1,    51,    -1,    53,
      -1,    55,    -1,    62,    -1,    65,    -1,    19,    21,     6,
      66,    -1,    19,    21,     6,    67,    -1,    19,    21,     6,
      66,    -1,    19,    21,     6,    67,    -1,    21,     6,    66,
      -1,    21,     6,    67,    -1,    21,     6,    66,    -1,    21,
       6,    67,    -1,    18,    21,    -1,    18,    21,    -1,    -1,
      27,    12,    66,    13,    57,    14,    47,    15,    58,    60,
      -1,    -1,    -1,    58,    37,    12,    66,    13,    59,    14,
      47,    15,    -1,    -1,    -1,    28,    61,    14,    47,    15,
      -1,    -1,    27,    12,    66,    13,    63,    14,    47,    15,
      58,    60,    -1,    24,    21,    -1,    24,    21,    -1,     3,
      -1,     4,    -1,    21,    -1,    66,     8,    66,    -1,    66,
       9,    66,    -1,    66,    10,    66,    -1,    66,    11,    66,
      -1,    66,    29,    66,    -1,    66,    30,    66,    -1,    66,
      31,    66,    -1,    66,    32,    66,    -1,    66,    33,    66,
      -1,    66,    34,    66,    -1,    66,    35,    66,    -1,    66,
      36,    66,    -1,    12,    66,    13,    -1,     5,    -1,    21,
      -1,    67,     8,    67,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   102,   102,   105,   106,   107,   108,   111,   114,   115,
     118,   119,   122,   124,   126,   127,   130,   131,   134,   135,
     136,   137,   138,   141,   142,   143,   144,   145,   148,   161,
     164,   179,   188,   225,   238,   277,   292,   295,   298,   298,
     301,   302,   302,   312,   313,   313,   323,   323,   326,   367,
     411,   412,   413,   427,   438,   448,   458,   473,   477,   481,
     484,   493,   496,   499,   510,   521,   525,   526,   527
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "FLOAT_NUMBER",
  "STRING_LITERAL", "EQUALS", "SEMICOLON", "PLUS", "MINUS", "MULTIPLY",
  "DIVIDE", "LPAR", "RPAR", "LCB", "RCB", "MAIN", "LIBDEF", "CALL", "VAR",
  "FILENAME", "IDENT", "LSB", "RSB", "USER_INPUT", "COMMA", "IMPORT", "IF",
  "ELSE", "EQ", "NEQ", "LT", "GT", "LEQ", "GEQ", "OR", "AND", "ELSEIF",
  "$accept", "program", "start_stmt", "mainprog", "import_list_opt",
  "import_list", "IMPORT_stmt", "libprogstart", "statement_list",
  "conditional_statement_list", "statement", "conditional_statement",
  "var_declaration", "conditional_var_declaration", "assignment",
  "conditional_assignment", "display", "conditional_display",
  "if_statement", "$@1", "elseif_statements", "$@2", "else_statement",
  "$@3", "conditional_if_statement", "$@4", "input_statement",
  "conditional_input_statement", "expr", "sexpr", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    40,    40,    41,    42,    42,
      43,    43,    44,    45,    46,    46,    47,    47,    48,    48,
      48,    48,    48,    49,    49,    49,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    55,    57,    56,
      58,    59,    58,    60,    61,    60,    63,    62,    64,    65,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    67,    67,    67
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     0,     6,     1,     0,
       2,     1,     2,     5,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       4,     4,     3,     3,     3,     3,     2,     2,     0,    10,
       0,     0,     9,     0,     0,     5,     0,    10,     2,     2,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     0,     2,     4,     0,     8,    11,     5,
      14,    12,     1,     0,    10,     3,     0,    14,     0,     0,
       0,     0,     0,     0,     0,    18,    19,    20,    21,    22,
       0,    13,    36,     0,     0,    48,     0,    15,     0,     0,
      50,    51,    66,     0,    52,    32,    33,    52,     0,     7,
      28,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    65,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      67,    68,     0,    16,     0,    40,     0,     0,     0,     0,
       0,     0,    23,    24,    25,    26,    27,    43,    37,     0,
       0,    49,     0,    17,    44,     0,    39,     0,    34,    35,
       0,     0,     0,    30,    31,    46,    16,     0,     0,     0,
      41,    16,    45,     0,     0,    16,    40,     0,    43,    42,
      47
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,     9,    16,    84,
      24,    91,    25,    92,    26,    93,    27,    94,    28,    82,
      97,   123,   106,   111,    95,   118,    29,    96,    45,    46
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -37
static const yytype_int16 yypact[] =
{
      24,   -13,   -18,     8,   -37,   -37,    -7,     3,   -37,   -10,
     -37,   -37,   -37,    33,   -37,   -37,   117,   -37,    41,    28,
      31,    47,    46,    50,    61,   -37,   -37,   -37,   -37,   -37,
     142,   -37,   -37,    63,    39,   -37,    42,   -37,    66,    39,
     -37,   -37,   -37,    42,   -37,    93,    62,   -37,     2,   -37,
      93,    62,    48,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    34,   -37,   -37,   120,   120,
     169,   169,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,    60,   -37,   149,   -37,    54,    68,    86,    70,
      87,    90,   -37,   -37,   -37,   -37,   -37,   -23,   -37,    94,
      39,   -37,    42,   -37,   -37,   121,   -37,    39,    93,    62,
      77,    91,    42,    93,    62,   -37,   -37,    85,   123,   156,
     -37,   -37,   -37,   126,   163,   -37,   -37,   170,   -23,   -37,
     -37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -37,   -37,   -37,   133,   -37,   -37,   138,   -37,   129,    18,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
      21,   -37,    20,   -37,   -37,   -37,   -37,   -37,   -36,   -35
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -10
static const yytype_int16 yytable[] =
{
      48,    10,    11,    50,    51,   104,    -9,    52,    12,    13,
      53,    54,    55,    56,   105,    66,     2,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,     2,
      81,    57,    58,    59,    60,    61,    62,    63,    64,    42,
      -9,     1,    40,    41,    42,    40,    41,    17,    31,    32,
       2,    43,    33,    34,    43,    80,    53,    54,    55,    56,
      44,    67,    36,    47,   108,   109,   110,    35,    37,    39,
      65,   113,   114,    49,    83,    98,   117,    57,    58,    59,
      60,    61,    62,    63,    64,    53,    54,    55,    56,    99,
     115,   101,   100,    53,    54,    55,    56,   103,   120,   102,
     107,    53,    54,    55,    56,   116,    57,    58,    59,    60,
      61,    62,    63,    64,    57,    58,    59,    60,    61,    62,
      63,    64,    57,    58,    59,    60,    61,    62,    63,    64,
      55,    56,    18,   112,   119,    19,    20,   121,    21,   124,
     125,    22,    15,   127,    23,    14,    30,   128,   130,    57,
      58,    59,    60,    61,    62,    63,    64,    38,     0,     0,
      19,    20,     0,    21,    85,     0,    22,    86,    87,    23,
      88,   122,     0,    89,    86,    87,    90,    88,   126,     0,
      89,    86,    87,    90,    88,   129,     0,    89,    86,    87,
      90,    88,     0,     0,    89,     0,     0,    90,    57,    58,
      59,    60,    61,    62,    63,    64
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-37)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      36,    14,    20,    39,    39,    28,    16,    43,     0,    16,
       8,     9,    10,    11,    37,    13,    26,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    26,
      65,    29,    30,    31,    32,    33,    34,    35,    36,     5,
      16,    17,     3,     4,     5,     3,     4,    14,     7,    21,
      26,    12,    21,     6,    12,    21,     8,     9,    10,    11,
      21,    13,    12,    21,   100,   100,   102,    21,     7,     6,
       8,   107,   107,     7,    14,    21,   112,    29,    30,    31,
      32,    33,    34,    35,    36,     8,     9,    10,    11,    21,
      13,    21,     6,     8,     9,    10,    11,     7,    13,    12,
       6,     8,     9,    10,    11,    14,    29,    30,    31,    32,
      33,    34,    35,    36,    29,    30,    31,    32,    33,    34,
      35,    36,    29,    30,    31,    32,    33,    34,    35,    36,
      10,    11,    15,    12,   116,    18,    19,    14,    21,   121,
      14,    24,     9,   125,    27,     7,    17,   126,   128,    29,
      30,    31,    32,    33,    34,    35,    36,    15,    -1,    -1,
      18,    19,    -1,    21,    15,    -1,    24,    18,    19,    27,
      21,    15,    -1,    24,    18,    19,    27,    21,    15,    -1,
      24,    18,    19,    27,    21,    15,    -1,    24,    18,    19,
      27,    21,    -1,    -1,    24,    -1,    -1,    27,    29,    30,
      31,    32,    33,    34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    26,    39,    40,    41,    42,    43,    44,    45,
      14,    20,     0,    16,    44,    41,    46,    14,    15,    18,
      19,    21,    24,    27,    48,    50,    52,    54,    56,    64,
      46,     7,    21,    21,     6,    21,    12,     7,    15,     6,
       3,     4,     5,    12,    21,    66,    67,    21,    66,     7,
      66,    67,    66,     8,     9,    10,    11,    29,    30,    31,
      32,    33,    34,    35,    36,     8,    13,    13,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      21,    67,    57,    14,    47,    15,    18,    19,    21,    24,
      27,    49,    51,    53,    55,    62,    65,    58,    21,    21,
       6,    21,    12,     7,    28,    37,    60,     6,    66,    67,
      66,    61,    12,    66,    67,    13,    14,    66,    63,    47,
      13,    14,    15,    59,    47,    14,    15,    47,    58,    15,
      60
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 14:
/* Line 1792 of yacc.c  */
#line 126 "parser.y"
    { (yyval.str) = ""; }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 127 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (3)].str); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 130 "parser.y"
    { (yyval.str) = ""; }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 131 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (3)].str); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 134 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 135 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 136 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 137 "parser.y"
    { (yyval.str) = ""; }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 138 "parser.y"
    {(yyval.str) ="";}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 141 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 142 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 143 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 144 "parser.y"
    { (yyval.str) = ""; }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 145 "parser.y"
    {(yyval.str) ="";}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 148 "parser.y"
    { 
                   if ((yyvsp[(4) - (4)].exprval).type == TYPE_INT) {
                       insert_variable((yyvsp[(2) - (4)].str));
                       update_variable((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].exprval).value.intValue);
                   } else if ((yyvsp[(4) - (4)].exprval).type == TYPE_FLOAT) {
                       insert_float_variable((yyvsp[(2) - (4)].str));
                       update_float_variable((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].exprval).value.floatValue);
                   } else {
                       insert_string_variable((yyvsp[(2) - (4)].str));
                       update_string_variable((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].exprval).value.strValue);
                   }
                   (yyval.str) = (yyvsp[(2) - (4)].str);
                 }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 161 "parser.y"
    { insert_string_variable((yyvsp[(2) - (4)].str)); update_string_variable((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].str)); (yyval.str) = (yyvsp[(2) - (4)].str); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 164 "parser.y"
    { 
                               if (evaluate_condition(condvalue)) {
                                   if ((yyvsp[(4) - (4)].exprval).type == TYPE_INT) {
                                       insert_variable((yyvsp[(2) - (4)].str));
                                       update_variable((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].exprval).value.intValue);
                                   } else if ((yyvsp[(4) - (4)].exprval).type == TYPE_FLOAT) {
                                       insert_float_variable((yyvsp[(2) - (4)].str));
                                       update_float_variable((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].exprval).value.floatValue);
                                   } else {
                                       insert_string_variable((yyvsp[(2) - (4)].str));
                                       update_string_variable((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].exprval).value.strValue);
                                   }
                               }
                               (yyval.str) = (yyvsp[(2) - (4)].str);
                             }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 179 "parser.y"
    { 
                               if (evaluate_condition(condvalue)) {  // Assuming string literals are always true
                                   insert_string_variable((yyvsp[(2) - (4)].str));
                                   update_string_variable((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].str));
                               }
                               (yyval.str) = (yyvsp[(2) - (4)].str);
                             }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 188 "parser.y"
    { 
                int old_type = get_variable_type((yyvsp[(1) - (3)].str));
                if (old_type == -1) {
                    if ((yyvsp[(3) - (3)].exprval).type == TYPE_INT) {
                        insert_variable((yyvsp[(1) - (3)].str));
                        update_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.intValue);
                    } else if ((yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) {
                        insert_float_variable((yyvsp[(1) - (3)].str));
                        update_float_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.floatValue);
                    } else {
                        insert_string_variable((yyvsp[(1) - (3)].str));
                        update_string_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.strValue);
                    }
                } else {
                    if ((yyvsp[(3) - (3)].exprval).type == TYPE_INT && old_type != TYPE_INT) {
                        delete_variable((yyvsp[(1) - (3)].str));
                        insert_variable((yyvsp[(1) - (3)].str));
                        update_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.intValue);
                    } else if ((yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT && old_type != TYPE_FLOAT) {
                        delete_variable((yyvsp[(1) - (3)].str));
                        insert_float_variable((yyvsp[(1) - (3)].str));
                        update_float_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.floatValue);
                    } else if ((yyvsp[(3) - (3)].exprval).type == TYPE_STRING && old_type != TYPE_STRING) {
                        delete_variable((yyvsp[(1) - (3)].str));
                        insert_string_variable((yyvsp[(1) - (3)].str));
                        update_string_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.strValue);
                    } else {
                        if ((yyvsp[(3) - (3)].exprval).type == TYPE_INT) 
                            update_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.intValue); 
                        else if ((yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) 
                            update_float_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.floatValue);
                        else 
                            update_string_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.strValue);
                    }
                }
                (yyval.str) = (yyvsp[(1) - (3)].str);
            }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 225 "parser.y"
    { 
                int old_type = get_variable_type((yyvsp[(1) - (3)].str));
                if (old_type == -1) {
                    insert_string_variable((yyvsp[(1) - (3)].str));
                } else if (old_type != TYPE_STRING) {
                    delete_variable((yyvsp[(1) - (3)].str));
                    insert_string_variable((yyvsp[(1) - (3)].str));
                }
                update_string_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str)); 
                (yyval.str) = (yyvsp[(1) - (3)].str);
            }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 238 "parser.y"
    { 
                            if (evaluate_condition(condvalue)) {
                                int old_type = get_variable_type((yyvsp[(1) - (3)].str));
                                if (old_type == -1) {
                                    if ((yyvsp[(3) - (3)].exprval).type == TYPE_INT) {
                                        insert_variable((yyvsp[(1) - (3)].str));
                                        update_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.intValue);
                                    } else if ((yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) {
                                        insert_float_variable((yyvsp[(1) - (3)].str));
                                        update_float_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.floatValue);
                                    } else {
                                        insert_string_variable((yyvsp[(1) - (3)].str));
                                        update_string_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.strValue);
                                    }
                                } else {
                                    if ((yyvsp[(3) - (3)].exprval).type == TYPE_INT && old_type != TYPE_INT) {
                                        delete_variable((yyvsp[(1) - (3)].str));
                                        insert_variable((yyvsp[(1) - (3)].str));
                                        update_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.intValue);
                                    } else if ((yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT && old_type != TYPE_FLOAT) {
                                        delete_variable((yyvsp[(1) - (3)].str));
                                        insert_float_variable((yyvsp[(1) - (3)].str));
                                        update_float_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.floatValue);
                                    } else if ((yyvsp[(3) - (3)].exprval).type == TYPE_STRING && old_type != TYPE_STRING) {
                                        delete_variable((yyvsp[(1) - (3)].str));
                                        insert_string_variable((yyvsp[(1) - (3)].str));
                                        update_string_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.strValue);
                                    } else {
                                        if ((yyvsp[(3) - (3)].exprval).type == TYPE_INT) 
                                            update_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.intValue); 
                                        else if ((yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) 
                                            update_float_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.floatValue);
                                        else 
                                            update_string_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].exprval).value.strValue);
                                    }
                                }
                            }
                            (yyval.str) = (yyvsp[(1) - (3)].str);
                        }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 277 "parser.y"
    { 
                            if (evaluate_condition(condvalue)) {  // Assuming string literals are always true
                                int old_type = get_variable_type((yyvsp[(1) - (3)].str));
                                if (old_type == -1) {
                                    insert_string_variable((yyvsp[(1) - (3)].str));
                                } else if (old_type != TYPE_STRING) {
                                    delete_variable((yyvsp[(1) - (3)].str));
                                    insert_string_variable((yyvsp[(1) - (3)].str));
                                }
                                update_string_variable((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str)); 
                            }
                            (yyval.str) = (yyvsp[(1) - (3)].str);
                        }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 292 "parser.y"
    { display_variable((yyvsp[(2) - (2)].str)); (yyval.str) = (yyvsp[(2) - (2)].str); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 295 "parser.y"
    { if (evaluate_condition(condvalue)) { display_variable((yyvsp[(2) - (2)].str)); } (yyval.str) = (yyvsp[(2) - (2)].str); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 298 "parser.y"
    { condvalue = (yyvsp[(3) - (4)].exprval).value.intValue; condition_met = condvalue; }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 302 "parser.y"
    { 
                     if (!condition_met) {
                         condvalue = (yyvsp[(4) - (5)].exprval).value.intValue;
                         condition_met = condvalue;
                     } else {
                         condvalue = 0;
                     }
                   }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 313 "parser.y"
    { 
                  if (!condition_met) { // Only evaluate if no previous condition was met
                      condvalue = 1; 
                      condition_met = 1; 
                  } else {
                      condvalue = 0; // Prevent the else block from executing
                  }
                }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 323 "parser.y"
    { condvalue = (yyvsp[(3) - (4)].exprval).value.intValue; }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 326 "parser.y"
    {
    char input_buffer[256];
    printf("Enter value for %s: ", (yyvsp[(2) - (2)].str));
    fgets(input_buffer, sizeof(input_buffer), stdin);
    // Remove newline character from input if present
    input_buffer[strcspn(input_buffer, "\n")] = '\0';

    int var_type = get_variable_type((yyvsp[(2) - (2)].str));
    
    // If the variable is not declared, determine its type from the input
    if (var_type == -1) {
        if (is_number(input_buffer)) {
            int value = atoi(input_buffer);
            insert_variable((yyvsp[(2) - (2)].str));  // Declare as an integer variable
            update_variable((yyvsp[(2) - (2)].str), value);  // Update with input value
        } else if (is_float(input_buffer)) {
            float value = atof(input_buffer);
            insert_float_variable((yyvsp[(2) - (2)].str));  // Declare as a float variable
            update_float_variable((yyvsp[(2) - (2)].str), value);  // Update with input value
        } else {
            insert_string_variable((yyvsp[(2) - (2)].str));  // Declare as a string variable
            update_string_variable((yyvsp[(2) - (2)].str), input_buffer);  // Update with input value
        }
    } else {
        // If the variable is already declared, update it based on its existing type
        if (var_type == TYPE_INT && is_number(input_buffer)) {
            int value = atoi(input_buffer);
            update_variable((yyvsp[(2) - (2)].str), value);
        } else if (var_type == TYPE_FLOAT && is_float(input_buffer)) {
            float value = atof(input_buffer);
            update_float_variable((yyvsp[(2) - (2)].str), value);
        } else if (var_type == TYPE_STRING) {
            update_string_variable((yyvsp[(2) - (2)].str), input_buffer);
        } else {
            fprintf(stderr, "Error: Type mismatch for variable %s\n", (yyvsp[(2) - (2)].str));
        }
    }

    (yyval.str) = (yyvsp[(2) - (2)].str);
}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 367 "parser.y"
    {
    if (evaluate_condition(condvalue)) {
        char input_buffer[256];
        printf("Enter value for %s: ", (yyvsp[(2) - (2)].str));
        fgets(input_buffer, sizeof(input_buffer), stdin);
        // Remove newline character from input if present
        input_buffer[strcspn(input_buffer, "\n")] = '\0';

        int var_type = get_variable_type((yyvsp[(2) - (2)].str));
        
        // If the variable is not declared, determine its type from the input
        if (var_type == -1) {
            if (is_number(input_buffer)) {
                int value = atoi(input_buffer);
                insert_variable((yyvsp[(2) - (2)].str));  // Declare as an integer variable
                update_variable((yyvsp[(2) - (2)].str), value);  // Update with input value
            } else if (is_float(input_buffer)) {
                float value = atof(input_buffer);
                insert_float_variable((yyvsp[(2) - (2)].str));  // Declare as a float variable
                update_float_variable((yyvsp[(2) - (2)].str), value);  // Update with input value
            } else {
                insert_string_variable((yyvsp[(2) - (2)].str));  // Declare as a string variable
                update_string_variable((yyvsp[(2) - (2)].str), input_buffer);  // Update with input value
            }
        } else {
            // If the variable is already declared, update it based on its existing type
            if (var_type == TYPE_INT && is_number(input_buffer)) {
                int value = atoi(input_buffer);
                update_variable((yyvsp[(2) - (2)].str), value);
            } else if (var_type == TYPE_FLOAT && is_float(input_buffer)) {
                float value = atof(input_buffer);
                update_float_variable((yyvsp[(2) - (2)].str), value);
            } else if (var_type == TYPE_STRING) {
                update_string_variable((yyvsp[(2) - (2)].str), input_buffer);
            } else {
                fprintf(stderr, "Error: Type mismatch for variable %s\n", (yyvsp[(2) - (2)].str));
            }
        }
    }
    (yyval.str) = (yyvsp[(2) - (2)].str);
}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 411 "parser.y"
    { (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = (yyvsp[(1) - (1)].num) }; }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 412 "parser.y"
    { (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = (yyvsp[(1) - (1)].fnum) }; }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 413 "parser.y"
    { 
        int intValue = get_variable_value((yyvsp[(1) - (1)].str)); 
        if (intValue != -1) {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = intValue };
        } else {
            float floatValue = get_float_variable_value((yyvsp[(1) - (1)].str));
            if (floatValue != -1.0) {
                (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = floatValue };
            } else {
                char *strValue = get_string_variable_value((yyvsp[(1) - (1)].str));
                (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_STRING, .value.strValue = strValue };
            }
        }
    }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 427 "parser.y"
    { 
        if ((yyvsp[(1) - (3)].exprval).type == TYPE_STRING || (yyvsp[(3) - (3)].exprval).type == TYPE_STRING) {
            char *str1 = ((yyvsp[(1) - (3)].exprval).type == TYPE_STRING) ? (yyvsp[(1) - (3)].exprval).value.strValue : ((yyvsp[(1) - (3)].exprval).type == TYPE_INT) ? int_to_string((yyvsp[(1) - (3)].exprval).value.intValue) : float_to_string((yyvsp[(1) - (3)].exprval).value.floatValue);
            char *str2 = ((yyvsp[(3) - (3)].exprval).type == TYPE_STRING) ? (yyvsp[(3) - (3)].exprval).value.strValue : ((yyvsp[(3) - (3)].exprval).type == TYPE_INT) ? int_to_string((yyvsp[(3) - (3)].exprval).value.intValue) : float_to_string((yyvsp[(3) - (3)].exprval).value.floatValue);
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_STRING, .value.strValue = concatStrings(str1, str2) };
        } else if ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT || (yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = ((yyvsp[(1) - (3)].exprval).type == TYPE_INT ? (yyvsp[(1) - (3)].exprval).value.intValue : (yyvsp[(1) - (3)].exprval).value.floatValue) + ((yyvsp[(3) - (3)].exprval).type == TYPE_INT ? (yyvsp[(3) - (3)].exprval).value.intValue : (yyvsp[(3) - (3)].exprval).value.floatValue) };
        } else {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = (yyvsp[(1) - (3)].exprval).value.intValue + (yyvsp[(3) - (3)].exprval).value.intValue };
        }
    }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 438 "parser.y"
    { 
        if ((yyvsp[(1) - (3)].exprval).type == TYPE_STRING || (yyvsp[(3) - (3)].exprval).type == TYPE_STRING) {
            fprintf(stderr, "Error: Cannot subtract strings\n");
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = NAN };
        } else if ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT || (yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = ((yyvsp[(1) - (3)].exprval).type == TYPE_INT ? (yyvsp[(1) - (3)].exprval).value.intValue : (yyvsp[(1) - (3)].exprval).value.floatValue) - ((yyvsp[(3) - (3)].exprval).type == TYPE_INT ? (yyvsp[(3) - (3)].exprval).value.intValue : (yyvsp[(3) - (3)].exprval).value.floatValue) };
        } else {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = (yyvsp[(1) - (3)].exprval).value.intValue - (yyvsp[(3) - (3)].exprval).value.intValue };
        }
    }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 448 "parser.y"
    { 
        if ((yyvsp[(1) - (3)].exprval).type == TYPE_STRING || (yyvsp[(3) - (3)].exprval).type == TYPE_STRING) {
            fprintf(stderr, "Error: Cannot multiply strings\n");
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = NAN };
        } else if ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT || (yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = ((yyvsp[(1) - (3)].exprval).type == TYPE_INT ? (yyvsp[(1) - (3)].exprval).value.intValue : (yyvsp[(1) - (3)].exprval).value.floatValue) * ((yyvsp[(3) - (3)].exprval).type == TYPE_INT ? (yyvsp[(3) - (3)].exprval).value.intValue : (yyvsp[(3) - (3)].exprval).value.floatValue) };
        } else {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = (yyvsp[(1) - (3)].exprval).value.intValue * (yyvsp[(3) - (3)].exprval).value.intValue };
        }
    }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 458 "parser.y"
    {
        if ((yyvsp[(1) - (3)].exprval).type == TYPE_STRING || (yyvsp[(3) - (3)].exprval).type == TYPE_STRING) {
            fprintf(stderr, "Error: Cannot divide strings\n");
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = NAN };
        } else if (((yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT && (yyvsp[(3) - (3)].exprval).value.floatValue != 0) || ((yyvsp[(3) - (3)].exprval).type == TYPE_INT && (yyvsp[(3) - (3)].exprval).value.intValue != 0)) {
            if ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT || (yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) {
                (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = ((yyvsp[(1) - (3)].exprval).type == TYPE_INT ? (yyvsp[(1) - (3)].exprval).value.intValue : (yyvsp[(1) - (3)].exprval).value.floatValue) / ((yyvsp[(3) - (3)].exprval).type == TYPE_INT ? (yyvsp[(3) - (3)].exprval).value.intValue : (yyvsp[(3) - (3)].exprval).value.floatValue) };
            } else {
                (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = (yyvsp[(1) - (3)].exprval).value.intValue / (yyvsp[(3) - (3)].exprval).value.intValue };
            }
        } else {
            fprintf(stderr, "Error: Division by zero\n");
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = 0 };
        }
    }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 473 "parser.y"
    { (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = ((yyvsp[(1) - (3)].exprval).type == (yyvsp[(3) - (3)].exprval).type) && 
                                                (((yyvsp[(1) - (3)].exprval).type == TYPE_INT && (yyvsp[(1) - (3)].exprval).value.intValue == (yyvsp[(3) - (3)].exprval).value.intValue) || 
                                                 ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT && (yyvsp[(1) - (3)].exprval).value.floatValue == (yyvsp[(3) - (3)].exprval).value.floatValue) || 
                                                 ((yyvsp[(1) - (3)].exprval).type == TYPE_STRING && strcmp((yyvsp[(1) - (3)].exprval).value.strValue, (yyvsp[(3) - (3)].exprval).value.strValue) == 0)) }; }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 477 "parser.y"
    { (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = !((yyvsp[(1) - (3)].exprval).type == (yyvsp[(3) - (3)].exprval).type) || 
                                                 (((yyvsp[(1) - (3)].exprval).type == TYPE_INT && (yyvsp[(1) - (3)].exprval).value.intValue != (yyvsp[(3) - (3)].exprval).value.intValue) || 
                                                  ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT && (yyvsp[(1) - (3)].exprval).value.floatValue != (yyvsp[(3) - (3)].exprval).value.floatValue) || 
                                                  ((yyvsp[(1) - (3)].exprval).type == TYPE_STRING && strcmp((yyvsp[(1) - (3)].exprval).value.strValue, (yyvsp[(3) - (3)].exprval).value.strValue) != 0)) }; }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 481 "parser.y"
    { (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = ((yyvsp[(1) - (3)].exprval).type == (yyvsp[(3) - (3)].exprval).type) && 
                                               (((yyvsp[(1) - (3)].exprval).type == TYPE_INT && (yyvsp[(1) - (3)].exprval).value.intValue < (yyvsp[(3) - (3)].exprval).value.intValue) || 
                                                ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT && (yyvsp[(1) - (3)].exprval).value.floatValue < (yyvsp[(3) - (3)].exprval).value.floatValue)) }; }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 484 "parser.y"
    { 
        if ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT || (yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = 
                ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT ? (yyvsp[(1) - (3)].exprval).value.floatValue : (yyvsp[(1) - (3)].exprval).value.intValue) > 
                ((yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT ? (yyvsp[(3) - (3)].exprval).value.floatValue : (yyvsp[(3) - (3)].exprval).value.intValue) };
        } else {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = (yyvsp[(1) - (3)].exprval).value.intValue > (yyvsp[(3) - (3)].exprval).value.intValue };
        }
    }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 493 "parser.y"
    { (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = ((yyvsp[(1) - (3)].exprval).type == (yyvsp[(3) - (3)].exprval).type) && 
                                                (((yyvsp[(1) - (3)].exprval).type == TYPE_INT && (yyvsp[(1) - (3)].exprval).value.intValue <= (yyvsp[(3) - (3)].exprval).value.intValue) || 
                                                 ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT && (yyvsp[(1) - (3)].exprval).value.floatValue <= (yyvsp[(3) - (3)].exprval).value.floatValue)) }; }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 496 "parser.y"
    { (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = ((yyvsp[(1) - (3)].exprval).type == (yyvsp[(3) - (3)].exprval).type) && 
                                                (((yyvsp[(1) - (3)].exprval).type == TYPE_INT && (yyvsp[(1) - (3)].exprval).value.intValue >= (yyvsp[(3) - (3)].exprval).value.intValue) || 
                                                 ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT && (yyvsp[(1) - (3)].exprval).value.floatValue >= (yyvsp[(3) - (3)].exprval).value.floatValue)) }; }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 499 "parser.y"
    {
        if ((yyvsp[(1) - (3)].exprval).type == TYPE_STRING || (yyvsp[(3) - (3)].exprval).type == TYPE_STRING) {
            fprintf(stderr, "Error: Cannot apply '||' on strings\n");
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = NAN };
        } else if ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT || (yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = (((yyvsp[(1) - (3)].exprval).type == TYPE_INT ? (yyvsp[(1) - (3)].exprval).value.intValue : (yyvsp[(1) - (3)].exprval).value.floatValue) != 0) ||
                                                         (((yyvsp[(3) - (3)].exprval).type == TYPE_INT ? (yyvsp[(3) - (3)].exprval).value.intValue : (yyvsp[(3) - (3)].exprval).value.floatValue) != 0) };
        } else {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = (yyvsp[(1) - (3)].exprval).value.intValue || (yyvsp[(3) - (3)].exprval).value.intValue };
        }
    }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 510 "parser.y"
    {
        if ((yyvsp[(1) - (3)].exprval).type == TYPE_STRING || (yyvsp[(3) - (3)].exprval).type == TYPE_STRING) {
            fprintf(stderr, "Error: Cannot apply '&&' on strings\n");
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_FLOAT, .value.floatValue = NAN };
        } else if ((yyvsp[(1) - (3)].exprval).type == TYPE_FLOAT || (yyvsp[(3) - (3)].exprval).type == TYPE_FLOAT) {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = (((yyvsp[(1) - (3)].exprval).type == TYPE_INT ? (yyvsp[(1) - (3)].exprval).value.intValue : (yyvsp[(1) - (3)].exprval).value.floatValue) != 0) &&
                                                         (((yyvsp[(3) - (3)].exprval).type == TYPE_INT ? (yyvsp[(3) - (3)].exprval).value.intValue : (yyvsp[(3) - (3)].exprval).value.floatValue) != 0) };
        } else {
            (yyval.exprval) = (typeof((yyval.exprval))){ .type = TYPE_INT, .value.intValue = (yyvsp[(1) - (3)].exprval).value.intValue && (yyvsp[(3) - (3)].exprval).value.intValue };
        }
    }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 521 "parser.y"
    { (yyval.exprval) = (yyvsp[(2) - (3)].exprval); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 525 "parser.y"
    { (yyval.str) = strdup((yyvsp[(1) - (1)].str)); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 526 "parser.y"
    { (yyval.str) = get_string_variable_value((yyvsp[(1) - (1)].str)); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 527 "parser.y"
    {
         char *temp = concatStrings((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
         free((yyvsp[(1) - (3)].str));
         free((yyvsp[(3) - (3)].str));
         (yyval.str) = temp;
       }
    break;


/* Line 1792 of yacc.c  */
#line 2162 "parser.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 535 "parser.y"


int is_number(const char* str) {
    char* endptr;
    strtol(str, &endptr, 10);
    return *endptr == '\0';
}

int is_float(const char* str) {
    char* endptr;
    strtof(str, &endptr);
    return *endptr == '\0';
}
