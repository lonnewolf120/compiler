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
#line 1 "parser.y"

#include "symboltable2.h"
#define YYSTYPE Symbol_Info


extern FILE *yyin, *yyout;
extern int line_cnt;
string variables="";
// int line_cnt=1, error_cnt=0;

// ofstream outFile("logerror.txt");  

int yylex();

SymbolTable st;

int temp_counter=1;
char* newTemp(){
    char* temp;
    temp = (char*) malloc(15*sizeof(char));
    sprintf(temp, "t%d", temp_counter);
    temp_counter++;
    return temp;
}


void fcout(string token, string symbol="") {
    ofstream op2;
    op2.open("token.txt", ios::app);
    if (!op2.is_open()) {
        cerr << "Error opening file.\n";
    }
    (symbol=="")?op2<<"<"<<token<<">": op2<<"<"<<token<<", "<<symbol<<">";
    op2.close();
}

void log_error(const char *msg=""){
    fprintf(yyout, "Line Number: %d\n", line_cnt);
    fprintf(yyout, "%s", msg);
}

void yyerror (const char *str) {
    fprintf(yyout, "%s\n", str);
}


void printASM(string str) {
    ofstream op2;
    op2.open("code.asm", ios::app);
    if (!op2.is_open()) {
        cerr << "Error opening file.\n";
    }
    op2<<str;
    op2.close();
}
void initASM(ofstream &op, string variables){
    op << ".MODEL SMALL\n";
    op << ".STACK 100H\n";
    op << ".DATA\n";
    op << variables;
    op << ".CODE\n";
    op << "MAIN PROC\n";
    op << "\tMOV AX, @DATA\n";
    op << "\tMOV DS, AX\n";
}

void printIR(string str) {
    ofstream op2;
    op2.open("code.ir", ios::app);
    if (!op2.is_open()) {
        cerr << "Error opening file.\n";
    }
    op2<<str;
    op2.close();
}

void clearOutput() {
    ofstream clearout;
    clearout.open("log_error.txt", ios::trunc);
    if (!clearout.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    clearout.close();
    clearout.open("table.txt", ios::trunc);
    if (!clearout.is_open()) {
        cerr << "Error delete file contents.\n";
    }
    clearout.close();
}


#line 163 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LTHIRD = 3,                     /* LTHIRD  */
  YYSYMBOL_RTHIRD = 4,                     /* RTHIRD  */
  YYSYMBOL_LPAREN = 5,                     /* LPAREN  */
  YYSYMBOL_RPAREN = 6,                     /* RPAREN  */
  YYSYMBOL_LCURL = 7,                      /* LCURL  */
  YYSYMBOL_RCURL = 8,                      /* RCURL  */
  YYSYMBOL_COMMA = 9,                      /* COMMA  */
  YYSYMBOL_ID = 10,                        /* ID  */
  YYSYMBOL_ADDOP = 11,                     /* ADDOP  */
  YYSYMBOL_SUBOP = 12,                     /* SUBOP  */
  YYSYMBOL_MULOP = 13,                     /* MULOP  */
  YYSYMBOL_DIVOP = 14,                     /* DIVOP  */
  YYSYMBOL_MODOP = 15,                     /* MODOP  */
  YYSYMBOL_ASSIGNOP = 16,                  /* ASSIGNOP  */
  YYSYMBOL_SEMICOLON = 17,                 /* SEMICOLON  */
  YYSYMBOL_RELOP = 18,                     /* RELOP  */
  YYSYMBOL_INCOP = 19,                     /* INCOP  */
  YYSYMBOL_DECOP = 20,                     /* DECOP  */
  YYSYMBOL_LOGICOP = 21,                   /* LOGICOP  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_CONST_INT = 23,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 24,               /* CONST_FLOAT  */
  YYSYMBOL_INT = 25,                       /* INT  */
  YYSYMBOL_FLOAT = 26,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 27,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 28,                      /* CHAR  */
  YYSYMBOL_IF = 29,                        /* IF  */
  YYSYMBOL_ELSE = 30,                      /* ELSE  */
  YYSYMBOL_FOR = 31,                       /* FOR  */
  YYSYMBOL_WHILE = 32,                     /* WHILE  */
  YYSYMBOL_RETURN = 33,                    /* RETURN  */
  YYSYMBOL_BREAK = 34,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 35,                  /* CONTINUE  */
  YYSYMBOL_VOID = 36,                      /* VOID  */
  YYSYMBOL_MAIN = 37,                      /* MAIN  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_line = 39,                      /* line  */
  YYSYMBOL_stmt = 40,                      /* stmt  */
  YYSYMBOL_unit = 41,                      /* unit  */
  YYSYMBOL_func_decl = 42,                 /* func_decl  */
  YYSYMBOL_param_list = 43,                /* param_list  */
  YYSYMBOL_param_decl = 44,                /* param_decl  */
  YYSYMBOL_mul_stmt = 45,                  /* mul_stmt  */
  YYSYMBOL_var_decl = 46,                  /* var_decl  */
  YYSYMBOL_type_spec = 47,                 /* type_spec  */
  YYSYMBOL_decl_list = 48,                 /* decl_list  */
  YYSYMBOL_expr_decl = 49,                 /* expr_decl  */
  YYSYMBOL_ass_list = 50,                  /* ass_list  */
  YYSYMBOL_expr = 51,                      /* expr  */
  YYSYMBOL_term = 52                       /* term  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   115

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  36
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  70

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   106,   106,   107,   110,   111,   114,   115,   116,   119,
     134,   152,   153,   156,   160,   161,   164,   176,   184,   185,
     188,   189,   190,   198,   199,   203,   217,   226,   227,   228,
     240,   252,   264,   276,   293,   303,   314
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
  "\"end of file\"", "error", "\"invalid token\"", "LTHIRD", "RTHIRD",
  "LPAREN", "RPAREN", "LCURL", "RCURL", "COMMA", "ID", "ADDOP", "SUBOP",
  "MULOP", "DIVOP", "MODOP", "ASSIGNOP", "SEMICOLON", "RELOP", "INCOP",
  "DECOP", "LOGICOP", "NOT", "CONST_INT", "CONST_FLOAT", "INT", "FLOAT",
  "DOUBLE", "CHAR", "IF", "ELSE", "FOR", "WHILE", "RETURN", "BREAK",
  "CONTINUE", "VOID", "MAIN", "$accept", "line", "stmt", "unit",
  "func_decl", "param_list", "param_decl", "mul_stmt", "var_decl",
  "type_spec", "decl_list", "expr_decl", "ass_list", "expr", "term", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-26)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-4)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      24,   -26,   -26,   -26,   -26,   -26,     3,     5,   -26,   -26,
      88,   -26,    14,   -26,    -7,   -26,   -26,    14,   -26,    14,
      -1,   -26,    79,    51,    73,     8,    14,   -26,   -13,    -4,
      51,    51,   -26,   -26,    80,   -26,    35,    36,    41,    60,
     -26,    14,    91,    67,    51,    51,    51,    51,   -26,    51,
      31,   -26,    24,    58,    88,   -26,   -26,    46,    46,   -26,
     -26,    95,    63,    10,    24,   -26,   -26,   -26,    45,   -26
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     8,    36,    17,    18,    19,     0,     0,     5,    15,
       2,     6,     0,     7,     0,     1,     4,     0,    14,     0,
       0,    24,    22,     0,    22,     0,     0,    16,     0,     0,
       0,     0,    27,    28,     0,    35,    20,     0,     0,     0,
      11,     0,    26,     0,     0,     0,     0,     0,    25,     0,
       0,    23,     0,     0,     0,    13,    34,    31,    32,    29,
      30,    33,     0,     0,     0,    12,    21,     9,     0,    10
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -26,   -26,   -25,    -6,    75,   -26,    23,   -26,   -26,     4,
     -26,   -26,   -26,    -2,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    39,    40,    10,    11,    17,
      20,    13,    21,    34,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      14,    16,    38,    15,    12,    -3,     1,    14,    26,    23,
      37,     1,    22,    29,    19,     2,    27,    24,    67,    25,
       2,     3,     4,     5,     2,     1,    36,    63,    42,    43,
       3,     4,     5,    41,     2,     3,     4,     5,    50,    68,
      51,    55,    57,    58,    59,    60,     1,    61,    52,     3,
       4,     5,    14,    69,    62,     2,    31,    16,    41,    46,
      47,     2,    16,    14,    14,    64,    53,    66,    14,    54,
       3,     4,     5,    56,    32,    33,    28,    65,    44,    45,
      46,    47,    28,     0,    29,    18,     0,     0,    49,    30,
       0,    44,    45,    46,    47,    30,     0,    48,     0,     0,
       0,    49,    44,    45,    46,    47,    44,    45,    46,    47,
       0,     0,    49,     3,     4,     5
};

static const yytype_int8 yycheck[] =
{
       0,     7,     6,     0,     0,     0,     1,     7,     9,    16,
      23,     1,    12,     5,    10,    10,    17,    17,     8,    19,
      10,    25,    26,    27,    10,     1,    26,    52,    30,    31,
      25,    26,    27,    29,    10,    25,    26,    27,     3,    64,
       4,    41,    44,    45,    46,    47,     1,    49,     7,    25,
      26,    27,    52,     8,    23,    10,     5,    63,    54,    13,
      14,    10,    68,    63,    64,     7,     6,     4,    68,     9,
      25,    26,    27,     6,    23,    24,     3,    54,    11,    12,
      13,    14,     3,    -1,     5,    10,    -1,    -1,    21,    16,
      -1,    11,    12,    13,    14,    16,    -1,    17,    -1,    -1,
      -1,    21,    11,    12,    13,    14,    11,    12,    13,    14,
      -1,    -1,    21,    25,    26,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    10,    25,    26,    27,    39,    40,    41,    42,
      45,    46,    47,    49,    52,     0,    41,    47,    42,    47,
      48,    50,    52,    16,    52,    52,     9,    17,     3,     5,
      16,     5,    23,    24,    51,    52,    52,    23,     6,    43,
      44,    47,    51,    51,    11,    12,    13,    14,    17,    21,
       3,     4,     7,     6,     9,    52,     6,    51,    51,    51,
      51,    51,    23,    40,     7,    44,     4,     8,    40,     8
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    41,    42,
      42,    43,    43,    44,    45,    45,    46,    47,    47,    47,
      48,    48,    48,    48,    48,    49,    50,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     7,
       8,     1,     3,     2,     2,     1,     3,     1,     1,     1,
       3,     6,     1,     4,     1,     4,     3,     1,     1,     3,
       3,     3,     3,     3,     3,     1,     1
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
  case 4: /* stmt: stmt unit  */
#line 110 "parser.y"
                 { log_error("stmt : stmt unit\n");}
#line 1249 "parser.tab.c"
    break;

  case 5: /* stmt: unit  */
#line 111 "parser.y"
            {log_error("stmt : unit\n"); }
#line 1255 "parser.tab.c"
    break;

  case 6: /* unit: var_decl  */
#line 114 "parser.y"
                 { log_error("unit : var_decl\n"); }
#line 1261 "parser.tab.c"
    break;

  case 7: /* unit: expr_decl  */
#line 115 "parser.y"
                  { log_error("unit : expr_decl\n"); }
#line 1267 "parser.tab.c"
    break;

  case 8: /* unit: error  */
#line 116 "parser.y"
             {yyerrok;log_error(""); yyerror("syntax error: invalid expression");}
#line 1273 "parser.tab.c"
    break;

  case 9: /* func_decl: type_spec term LPAREN RPAREN LCURL stmt RCURL  */
#line 119 "parser.y"
                                                          {
    log_error("func_decl : type_spec term LPAREN RPAREN LCURL stmt RCURL\n"); 
    
    string funcName = string(yyvsp[-5].getSymbol());
    string asmCode = funcName + " PROC\n";
    asmCode += "\tPUSH BP\n";
    asmCode += "\tMOV BP, SP\n";
    asmCode += "\t; Function body goes here\n";
    asmCode += "\t"+ string(yyvsp[-1].getSymbol()) +"\n";
    asmCode += "\tPOP BP\n";
    asmCode += "\tRET\n";
    asmCode += funcName + " ENDP\n";
    printASM(asmCode);

    }
#line 1293 "parser.tab.c"
    break;

  case 10: /* func_decl: type_spec term LPAREN param_list RPAREN LCURL stmt RCURL  */
#line 134 "parser.y"
                                                               {
    log_error("func_decl : type_spec term LPAREN param_list RPAREN LCURL stmt RCURL\n"); 
    
    // string funcName = string($2.getSymbol());
    // string asmCode = funcName + " PROC\n";
    // asmCode += "\tPUSH BP\n";
    // asmCode += "\tMOV BP, SP\n";
    // asmCode += "\t; Function body goes here\n";
    // asmCode += "\t"+ string($6.getSymbol()) +"\n";
    // asmCode += "\t"+ string($6.getSymbol()) +"\n";
    // asmCode += "\tPOP BP\n";
    // asmCode += "\tRET\n";
    // asmCode += funcName + " ENDP\n";
    // printASM(asmCode);
    
    }
#line 1314 "parser.tab.c"
    break;

  case 11: /* param_list: param_decl  */
#line 152 "parser.y"
                        { log_error("param_list : param_decl\n"); }
#line 1320 "parser.tab.c"
    break;

  case 12: /* param_list: param_list COMMA param_decl  */
#line 153 "parser.y"
                                         { log_error("param_list : param_list COMMA param_decl\n"); }
#line 1326 "parser.tab.c"
    break;

  case 13: /* param_decl: type_spec term  */
#line 156 "parser.y"
                            { log_error("param_decl : type_spec term\n"); }
#line 1332 "parser.tab.c"
    break;

  case 16: /* var_decl: type_spec decl_list SEMICOLON  */
#line 164 "parser.y"
                                         {
    log_error("vardecl : type_spec dec_list SEMICOLON\n"); 
    printIR(string(yyval.getSymbol())+" = "+string(yyvsp[-1].getSymbol())+";\n");
    
    variables += string(yyvsp[-1].getSymbol()) + " DW ?\n";
    
    string asmCode = "MOV AX, " + string(yyvsp[-1].getSymbol().c_str()) + "\n";
    asmCode += "MOV " + string(yyvsp[-1].getSymbol().c_str()) + ", AX\n\n";
    printASM(asmCode);
}
#line 1347 "parser.tab.c"
    break;

  case 17: /* type_spec: INT  */
#line 176 "parser.y"
                {
        log_error("type_spec : INT\n");
        // printIR(string($$.getSymbol())+" = "+string($1.getSymbol())+" - "+string($3.getSymbol())+"\n");
        
        // printASM("MOV AX, "+string($2.getSymbol().c_str())+"\n");
        // printASM("MOV "+string($$.getSymbol().c_str())+", AX\n\n");
        
        }
#line 1360 "parser.tab.c"
    break;

  case 18: /* type_spec: FLOAT  */
#line 184 "parser.y"
                  {log_error("type_spec : FLOAT\n");}
#line 1366 "parser.tab.c"
    break;

  case 19: /* type_spec: DOUBLE  */
#line 185 "parser.y"
                   {log_error("type_spec : DOUBLE\n");}
#line 1372 "parser.tab.c"
    break;

  case 20: /* decl_list: decl_list COMMA term  */
#line 188 "parser.y"
                                 {log_error("dec_list : dec_list COMMA term\n");}
#line 1378 "parser.tab.c"
    break;

  case 21: /* decl_list: decl_list COMMA term LTHIRD CONST_INT RTHIRD  */
#line 189 "parser.y"
                                               {log_error("dec_list : dec_list COMMA term LTHIRD CONST_INT RTHIRD\n"); }
#line 1384 "parser.tab.c"
    break;

  case 22: /* decl_list: term  */
#line 190 "parser.y"
       {log_error("dec_list : term\n");
// $$ = $1;
printIR(string(yyval.getSymbol()) + " = " + string(yyvsp[0].getSymbol()) + ";\n");
string asmCode = "MOV AX, " + string(yyvsp[0].getSymbol().c_str()) + "\n";
asmCode += "MOV " + string(yyval.getSymbol().c_str()) + ", AX\n\n";
printASM(asmCode);

}
#line 1397 "parser.tab.c"
    break;

  case 23: /* decl_list: term LTHIRD CONST_INT RTHIRD  */
#line 198 "parser.y"
                               { log_error("dec_list : term LTHIRD CONST_INT RTHIRD\n"); }
#line 1403 "parser.tab.c"
    break;

  case 24: /* decl_list: ass_list  */
#line 199 "parser.y"
           {log_error("dec_list : asslist\n");}
#line 1409 "parser.tab.c"
    break;

  case 25: /* expr_decl: term ASSIGNOP expr SEMICOLON  */
#line 203 "parser.y"
                                          {
    log_error("expr_decl : term ASSIGNOP expr SEMICOLON\n");
    // char* str = newTemp();
    // Symbol_Info obj(str, "TempID");
    // $$ = $1 - $3;
    // $$ = obj;
    printIR(string(yyvsp[-3].getSymbol())+" = "+string(yyvsp[-1].getSymbol())+";\n");
    
    string asmCode = "MOV AX, " + string(yyvsp[-1].getSymbol().c_str()) + "\n";
    asmCode += "MOV " + string(yyvsp[-3].getSymbol().c_str()) + ", AX\n\n";
    printASM(asmCode);
    }
#line 1426 "parser.tab.c"
    break;

  case 26: /* ass_list: term ASSIGNOP expr  */
#line 217 "parser.y"
                              {
    log_error(" asslist : term ASSIGNOP expr\n");
    printIR(string(yyvsp[-2].getSymbol()) + " = " + string(yyvsp[0].getSymbol()) + ";\n");
    string asmCode = "MOV AX, " + string(yyvsp[0].getSymbol().c_str()) + "\n";
    asmCode += "MOV " + string(yyvsp[-2].getSymbol().c_str()) + ", AX\n\n";
    printASM(asmCode);
}
#line 1438 "parser.tab.c"
    break;

  case 27: /* expr: CONST_INT  */
#line 226 "parser.y"
                   { log_error("expr : CONST_INT \n"); }
#line 1444 "parser.tab.c"
    break;

  case 28: /* expr: CONST_FLOAT  */
#line 227 "parser.y"
                   { log_error("expr : CONST_FLOAT \n"); }
#line 1450 "parser.tab.c"
    break;

  case 29: /* expr: expr MULOP expr  */
#line 228 "parser.y"
                       { 
        log_error("expr : expr MULOP expr \n");
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        yyval = yyvsp[-2] * yyvsp[0];  
        printIR(string(yyval.getSymbol()) + " = " + string(yyvsp[-2].getSymbol()) + " * " + string(yyvsp[0].getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string(yyvsp[-2].getSymbol().c_str()) + "\n"; 
        asmCode += "MOV BX, " + string(yyvsp[0].getSymbol().c_str()) + "\n";
        asmCode += "MUL AX, BX\n";
        asmCode += "MOV " + string(yyval.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
#line 1467 "parser.tab.c"
    break;

  case 30: /* expr: expr DIVOP expr  */
#line 240 "parser.y"
                       { 
        log_error("expr : expr DIVOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        yyval = yyvsp[-2] / yyvsp[0];  
        printIR(string(yyval.getSymbol()) + " = " + string(yyvsp[-2].getSymbol()) + " / " + string(yyvsp[0].getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string(yyvsp[-2].getSymbol().c_str()) + "\n";
        asmCode += "MOV BX, " + string(yyvsp[0].getSymbol().c_str()) + "\n";
        asmCode += "DIV AX, BX\n";
        asmCode += "MOV " + string(yyval.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
#line 1484 "parser.tab.c"
    break;

  case 31: /* expr: expr ADDOP expr  */
#line 252 "parser.y"
                       { 
        log_error("expr : expr ADDOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        yyval = yyvsp[-2] + yyvsp[0];  
        printIR(string(yyval.getSymbol()) + " = " + string(yyvsp[-2].getSymbol()) + " + " + string(yyvsp[0].getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string(yyvsp[-2].getSymbol().c_str()) + "\n";
        asmCode += "MOV BX, " + string(yyvsp[0].getSymbol().c_str()) + "\n";
        asmCode += "ADD AX, BX\n";
        asmCode += "MOV " + string(yyval.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
#line 1501 "parser.tab.c"
    break;

  case 32: /* expr: expr SUBOP expr  */
#line 264 "parser.y"
                       { 
        log_error("expr : expr SUBOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        yyval = yyvsp[-2] - yyvsp[0]; 
        printIR(string(yyval.getSymbol()) + " = " + string(yyvsp[-2].getSymbol()) + " - " + string(yyvsp[0].getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string(yyvsp[-2].getSymbol().c_str()) + "\n";
        asmCode += "MOV BX, " + string(yyvsp[0].getSymbol().c_str()) + "\n";
        asmCode += "SUB AX, BX\n";
        asmCode += "MOV " + string(yyval.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
#line 1518 "parser.tab.c"
    break;

  case 33: /* expr: expr LOGICOP expr  */
#line 276 "parser.y"
                         { 
        log_error("expr : expr LOGICOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        yyval = obj;
        string asmCode = "MOV AX, " + string(yyvsp[-2].getSymbol().c_str()) + "\n";
        asmCode += "MOV BX, " + string(yyvsp[0].getSymbol().c_str()) + "\n";
        if(yyvsp[-1].getSymbol() == "&&") {
            printIR(string(yyval.getSymbol()) + " = " + string(yyvsp[-2].getSymbol()) + " && " + string(yyvsp[0].getSymbol()) + "\n");
            asmCode += "AND AX, BX\n";
        } else {
            printIR(string(yyval.getSymbol()) + " = " + string(yyvsp[-2].getSymbol()) + " || " + string(yyvsp[0].getSymbol()) + "\n");
            asmCode += "OR AX, BX\n";    
        }
        asmCode += "MOV " + string(yyval.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
#line 1540 "parser.tab.c"
    break;

  case 34: /* expr: LPAREN expr RPAREN  */
#line 293 "parser.y"
                          { 
        log_error("expr : LPAREN expr RPAREN  \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        yyval = obj;
        printIR(string(yyval.getSymbol()) + " = " + string(yyvsp[-1].getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string(yyvsp[-1].getSymbol().c_str()) + "\n";
        asmCode += "MOV " + string(yyval.getSymbol().c_str()) + ", AX\n\n";
        printASM(asmCode);
     }
#line 1555 "parser.tab.c"
    break;

  case 35: /* expr: term  */
#line 303 "parser.y"
            { 
        log_error("expr : term \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        yyval = obj;
        printIR(string(yyval.getSymbol()) + " = " + string(yyvsp[0].getSymbol()) + "\n");
        string asmCode = "MOV AX, " + string(yyvsp[0].getSymbol().c_str()) + "\n";
        printASM(asmCode);
     }
#line 1569 "parser.tab.c"
    break;

  case 36: /* term: ID  */
#line 314 "parser.y"
          {
    
    Symbol_Info obj(string(yyvsp[0].getSymbol()), "ID");

    if (!(st.insert(obj))) {
        fprintf(yyout, "%s is already declared\n", yyvsp[0].getSymbol().c_str());
    }else{
        log_error("term: ID\n");
    }
}
#line 1584 "parser.tab.c"
    break;


#line 1588 "parser.tab.c"

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

#line 326 "parser.y"


int main() 
{
  st.clear();
  clearOutput();
  ofstream opp("code.asm", ios::app);
  initASM(opp, variables);
  yyin=fopen("input.txt","r");
  yyout=fopen("log_error.txt","w");
  yyparse(); 
  st.print();

  string asmCode = "MOV AH, 4CH\n";
  asmCode += "INT 21H\n";
  asmCode += "MAIN ENDP\n";
  asmCode += "END MAIN\n";
  printASM(asmCode);

  return 0;
}
