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
#line 1 "parser2.y"

#include "symboltable2.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#define YYSTYPE Symbol_Info

extern FILE *yyin, *yyout;
extern int line_cnt;
std::vector<std::string> variables; 

std::vector<std::string> asm_code[4];

int yylex();

SymbolTable st;

int temp_counter = 1;
void log_error(const char *msg = "") {
    fprintf(yyout, "Line Number: %d\n", line_cnt);
    fprintf(yyout, "%s", msg);
}

void yyerror(const char *str) {
    fprintf(yyout, "%s\n", str);
}

void printASM(std::string str, int i = 2) { 
    asm_code[i].push_back(str);
}

char* newTemp() {
    char* temp;
    temp = (char*) malloc(15 * sizeof(char));
    sprintf(temp, "t%d", temp_counter);
    printASM(("t"+std::to_string(temp_counter)+" DW ?\n"), 1);
    temp_counter++;
    return temp;
}

void printIR(std::string str) {
    std::ofstream op2;
    op2.open("code.ir", std::ios::app);
    if (!op2.is_open()) {
        std::cerr << "Error opening file.\n";
    }
    op2 << str;
    op2.close();
}

void printVar(std::string varName){
    std::string asmCode = "\tMOV AH, 02H\n";
    asmCode += "\tMOV DX, " + varName + "\n";
    asmCode += "\tINT 21H\n";
    printASM(asmCode, 2);
}

void clearOutput() {
    std::ofstream clearout;
    clearout.open("log_error.txt", std::ios::trunc);
    if (!clearout.is_open()) {
        std::cerr << "Error deleting file contents.\n";
    }
    clearout.close();
    clearout.open("table.txt", std::ios::trunc);
    if (!clearout.is_open()) {
        std::cerr << "Error deleting file contents.\n";
    }
    clearout.close();
    clearout.open("code.ir", std::ios::trunc);
    if (!clearout.is_open()) {
        std::cerr << "Error deleting file contents.\n";
    }
    clearout.close();
    clearout.open("code.asm", std::ios::trunc);
    if (!clearout.is_open()) {
        std::cerr << "Error deleting file contents.\n";
    }
    clearout.close();
}


#line 158 "parser2.tab.c"

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

#include "parser2.tab.h"
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
  YYSYMBOL_CONST_FLOAT = 14,               /* CONST_FLOAT  */
  YYSYMBOL_INT = 15,                       /* INT  */
  YYSYMBOL_DIVOP = 16,                     /* DIVOP  */
  YYSYMBOL_MODOP = 17,                     /* MODOP  */
  YYSYMBOL_ASSIGNOP = 18,                  /* ASSIGNOP  */
  YYSYMBOL_SEMICOLON = 19,                 /* SEMICOLON  */
  YYSYMBOL_RELOP = 20,                     /* RELOP  */
  YYSYMBOL_INCOP = 21,                     /* INCOP  */
  YYSYMBOL_DECOP = 22,                     /* DECOP  */
  YYSYMBOL_COLON = 23,                     /* COLON  */
  YYSYMBOL_LOGICOP = 24,                   /* LOGICOP  */
  YYSYMBOL_NOT = 25,                       /* NOT  */
  YYSYMBOL_CONST_INT = 26,                 /* CONST_INT  */
  YYSYMBOL_FLOAT = 27,                     /* FLOAT  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_ELSE = 29,                      /* ELSE  */
  YYSYMBOL_FOR = 30,                       /* FOR  */
  YYSYMBOL_WHILE = 31,                     /* WHILE  */
  YYSYMBOL_RETURN = 32,                    /* RETURN  */
  YYSYMBOL_BREAK = 33,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 34,                  /* CONTINUE  */
  YYSYMBOL_VOID = 35,                      /* VOID  */
  YYSYMBOL_MAIN = 36,                      /* MAIN  */
  YYSYMBOL_SWITCH = 37,                    /* SWITCH  */
  YYSYMBOL_CASE = 38,                      /* CASE  */
  YYSYMBOL_ELIF = 39,                      /* ELIF  */
  YYSYMBOL_DOUBLE = 40,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 41,                      /* CHAR  */
  YYSYMBOL_DEFAULT = 42,                   /* DEFAULT  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_prog = 44,                      /* prog  */
  YYSYMBOL_func_decl_list = 45,            /* func_decl_list  */
  YYSYMBOL_main_func = 46,                 /* main_func  */
  YYSYMBOL_stmt_list = 47,                 /* stmt_list  */
  YYSYMBOL_stmt = 48,                      /* stmt  */
  YYSYMBOL_switch_stmt = 49,               /* switch_stmt  */
  YYSYMBOL_case_list = 50,                 /* case_list  */
  YYSYMBOL_case = 51,                      /* case  */
  YYSYMBOL_default_case_opt = 52,          /* default_case_opt  */
  YYSYMBOL_default_case = 53,              /* default_case  */
  YYSYMBOL_break_stmt = 54,                /* break_stmt  */
  YYSYMBOL_var_decl = 55,                  /* var_decl  */
  YYSYMBOL_type_spec = 56,                 /* type_spec  */
  YYSYMBOL_decl_list = 57,                 /* decl_list  */
  YYSYMBOL_expr_decl = 58,                 /* expr_decl  */
  YYSYMBOL_conditional = 59,               /* conditional  */
  YYSYMBOL_func_decl = 60,                 /* func_decl  */
  YYSYMBOL_param_list = 61,                /* param_list  */
  YYSYMBOL_param = 62,                     /* param  */
  YYSYMBOL_func_call = 63,                 /* func_call  */
  YYSYMBOL_arg_list = 64,                  /* arg_list  */
  YYSYMBOL_expr = 65,                      /* expr  */
  YYSYMBOL_term = 66                       /* term  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   263

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    98,    98,   101,   102,   105,   110,   111,   114,   115,
     116,   117,   118,   119,   120,   123,   131,   134,   139,   149,
     152,   157,   165,   172,   183,   186,   187,   190,   193,   204,
     205,   206,   209,   216,   221,   222,   223,   226,   229,   236,
     237,   238,   241,   242,   243,   259,   274,   288,   304,   323,
     331,   337
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
  "MULOP", "CONST_FLOAT", "INT", "DIVOP", "MODOP", "ASSIGNOP", "SEMICOLON",
  "RELOP", "INCOP", "DECOP", "COLON", "LOGICOP", "NOT", "CONST_INT",
  "FLOAT", "IF", "ELSE", "FOR", "WHILE", "RETURN", "BREAK", "CONTINUE",
  "VOID", "MAIN", "SWITCH", "CASE", "ELIF", "DOUBLE", "CHAR", "DEFAULT",
  "$accept", "prog", "func_decl_list", "main_func", "stmt_list", "stmt",
  "switch_stmt", "case_list", "case", "default_case_opt", "default_case",
  "break_stmt", "var_decl", "type_spec", "decl_list", "expr_decl",
  "conditional", "func_decl", "param_list", "param", "func_call",
  "arg_list", "expr", "term", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-33)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-22)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -33,     9,   -13,   -33,   -33,   -33,    14,   -33,   -33,     1,
     -33,    18,   -33,    -1,    38,   -14,   -33,   180,    15,    11,
     -33,   -33,    43,    44,    32,    47,    87,   -33,   -33,   -33,
     -33,     1,   -33,   -33,   -33,    54,   -33,    55,   -14,     2,
       2,   -33,     2,   -33,   -33,    42,   -33,     2,   180,   -33,
       2,   -33,   -33,    37,    58,   -33,   185,   210,   -33,   239,
     121,   219,    56,     2,     2,     2,     2,     2,     2,    66,
      69,   -33,   -33,   -33,   -33,    58,    16,    16,   -33,   -33,
      23,   180,    45,   129,    59,   -32,   -33,   -24,    68,    70,
     -33,    73,   -33,    85,    91,   180,   180,   -33,   180,     2,
      79,   137,   145,   233,   -33,    97,   180,   178,   -33
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,    24,    25,     0,    26,     2,     0,
       3,     0,    51,     0,     0,    36,    33,     0,     0,     0,
      35,    14,    51,     0,     0,     0,     0,     7,    11,    12,
       8,     0,     9,    10,    13,     0,    37,     0,     0,    41,
       0,    22,     0,     5,     6,     0,    27,     0,     0,    34,
       0,    43,    42,     0,    40,    50,     0,     0,    23,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    32,    49,    38,    39,    46,    47,    44,    45,
      48,     0,     0,     0,     0,    20,    17,    29,     0,     0,
      16,     0,    19,     0,     0,     0,     0,    15,     0,     0,
       0,     0,     0,     0,    30,     0,     0,     0,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -33,   -33,   -33,   -33,     5,   -23,   -33,   -33,    13,   -33,
     -33,   -33,   -33,     6,   -33,   -33,   -33,   -33,   -33,    67,
     -33,   -33,     0,    -9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     8,    26,    27,    28,    85,    86,    91,
      92,    29,    30,    31,    45,    32,    33,    10,    19,    20,
      34,    53,    54,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      13,     4,     4,    44,    15,    93,    84,    50,     9,     3,
      89,    12,    12,     5,     5,    94,    51,    37,    16,    11,
      38,    18,    46,     6,    14,    36,     7,     7,    52,    66,
      55,    55,    67,    55,    64,    65,    66,    44,    55,    67,
      56,    55,    57,    62,    18,    17,    63,    59,    39,    40,
      61,    41,    42,    60,    55,    55,    55,    55,    55,    55,
      44,    58,    48,    75,    76,    77,    78,    79,    80,    64,
      65,    66,    47,    81,    67,    74,    82,    44,    44,    44,
      21,    97,    68,    84,    44,    88,    83,   -18,    21,    22,
      55,    95,    98,    96,     4,    43,    99,    22,    90,   103,
     100,   101,     4,   102,   106,    49,     5,    23,     0,     0,
       0,   107,    24,     0,     5,    23,    25,   -18,     0,     7,
      24,   -18,    21,     0,    25,     0,     0,     7,     0,    72,
      21,    22,     0,     0,     0,     0,     4,    87,    21,    22,
       0,     0,     0,     0,     4,   -21,    21,    22,     5,    23,
       0,     0,     4,   104,    24,    22,     5,    23,    25,     0,
       4,     7,    24,     0,     5,    23,    25,     0,     0,     7,
      24,     0,     5,    23,    25,     0,     0,     7,    24,    21,
       0,    21,    25,     0,     0,     7,   108,     0,    22,     0,
      22,    69,     0,     4,     0,     4,    64,    65,    66,     0,
       0,    67,     0,     0,     0,     5,    23,     5,    23,    68,
       0,    24,     0,    24,     0,    25,    70,    25,     7,     0,
       7,    64,    65,    66,     0,    73,    67,     0,     0,     0,
      64,    65,    66,     0,    68,    67,     0,     0,     0,   105,
       0,     0,     0,    68,    64,    65,    66,     0,     0,    67,
      64,    65,    66,     0,     0,    67,     0,    68,    71,     0,
       0,     0,     0,    68
};

static const yytype_int8 yycheck[] =
{
       9,    15,    15,    26,     5,    29,    38,     5,     2,     0,
      42,    10,    10,    27,    27,    39,    14,     6,    19,     5,
       9,    15,    31,    36,     6,    10,    40,    40,    26,    13,
      39,    40,    16,    42,    11,    12,    13,    60,    47,    16,
      40,    50,    42,     6,    38,     7,     9,    47,     5,     5,
      50,    19,     5,    48,    63,    64,    65,    66,    67,    68,
      83,    19,     7,    63,    64,    65,    66,    67,    68,    11,
      12,    13,    18,     7,    16,    19,     7,   100,   101,   102,
       1,     8,    24,    38,   107,    26,    81,     8,     1,    10,
      99,    23,     7,    23,    15,     8,     5,    10,    85,    99,
      95,    96,    15,    98,     7,    38,    27,    28,    -1,    -1,
      -1,   106,    33,    -1,    27,    28,    37,    38,    -1,    40,
      33,    42,     1,    -1,    37,    -1,    -1,    40,    -1,     8,
       1,    10,    -1,    -1,    -1,    -1,    15,     8,     1,    10,
      -1,    -1,    -1,    -1,    15,     8,     1,    10,    27,    28,
      -1,    -1,    15,     8,    33,    10,    27,    28,    37,    -1,
      15,    40,    33,    -1,    27,    28,    37,    -1,    -1,    40,
      33,    -1,    27,    28,    37,    -1,    -1,    40,    33,     1,
      -1,     1,    37,    -1,    -1,    40,     8,    -1,    10,    -1,
      10,     6,    -1,    15,    -1,    15,    11,    12,    13,    -1,
      -1,    16,    -1,    -1,    -1,    27,    28,    27,    28,    24,
      -1,    33,    -1,    33,    -1,    37,     6,    37,    40,    -1,
      40,    11,    12,    13,    -1,     6,    16,    -1,    -1,    -1,
      11,    12,    13,    -1,    24,    16,    -1,    -1,    -1,     6,
      -1,    -1,    -1,    24,    11,    12,    13,    -1,    -1,    16,
      11,    12,    13,    -1,    -1,    16,    -1,    24,    19,    -1,
      -1,    -1,    -1,    24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    44,    45,     0,    15,    27,    36,    40,    46,    56,
      60,     5,    10,    66,     6,     5,    19,     7,    56,    61,
      62,     1,    10,    28,    33,    37,    47,    48,    49,    54,
      55,    56,    58,    59,    63,    66,    10,     6,     9,     5,
       5,    19,     5,     8,    48,    57,    66,    18,     7,    62,
       5,    14,    26,    64,    65,    66,    65,    65,    19,    65,
      47,    65,     6,     9,    11,    12,    13,    16,    24,     6,
       6,    19,     8,     6,    19,    65,    65,    65,    65,    65,
      65,     7,     7,    47,    38,    50,    51,     8,    26,    42,
      51,    52,    53,    29,    39,    23,    23,     8,     7,     5,
      47,    47,    47,    65,     8,     6,     7,    47,     8
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    47,    47,    48,    48,
      48,    48,    48,    48,    48,    49,    50,    50,    51,    52,
      52,    53,    54,    55,    56,    56,    56,    57,    58,    59,
      59,    59,    60,    60,    61,    61,    61,    62,    63,    64,
      64,    64,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     6,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     8,     2,     1,     4,     1,
       0,     3,     2,     3,     1,     1,     1,     1,     4,     7,
      11,    14,     8,     3,     3,     1,     0,     2,     5,     3,
       1,     0,     1,     1,     3,     3,     3,     3,     3,     3,
       1,     1
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
  case 2: /* prog: func_decl_list main_func  */
#line 98 "parser2.y"
                                { log_error("prog : func_decl_list main_func\n"); }
#line 1311 "parser2.tab.c"
    break;

  case 3: /* func_decl_list: func_decl_list func_decl  */
#line 101 "parser2.y"
                                         { log_error("func_decl_list : func_decl_list func_decl\n"); }
#line 1317 "parser2.tab.c"
    break;

  case 4: /* func_decl_list: %empty  */
#line 102 "parser2.y"
                            { }
#line 1323 "parser2.tab.c"
    break;

  case 5: /* main_func: MAIN LPAREN RPAREN LCURL stmt_list RCURL  */
#line 105 "parser2.y"
                                                    { 
    log_error("main_func : MAIN LPAREN RPAREN LCURL stmt_list RCURL\n"); 
}
#line 1331 "parser2.tab.c"
    break;

  case 6: /* stmt_list: stmt_list stmt  */
#line 110 "parser2.y"
                           { log_error("stmt_list : stmt_list stmt\n"); }
#line 1337 "parser2.tab.c"
    break;

  case 7: /* stmt_list: stmt  */
#line 111 "parser2.y"
                 { log_error("stmt_list : stmt\n"); }
#line 1343 "parser2.tab.c"
    break;

  case 8: /* stmt: var_decl  */
#line 114 "parser2.y"
                { log_error("stmt : var_decl\n"); }
#line 1349 "parser2.tab.c"
    break;

  case 9: /* stmt: expr_decl  */
#line 115 "parser2.y"
                 { log_error("stmt : expr_decl\n"); }
#line 1355 "parser2.tab.c"
    break;

  case 10: /* stmt: conditional  */
#line 116 "parser2.y"
                   { log_error("stmt : conditional\n"); }
#line 1361 "parser2.tab.c"
    break;

  case 11: /* stmt: switch_stmt  */
#line 117 "parser2.y"
                   { log_error("stmt : switch_stmt\n"); }
#line 1367 "parser2.tab.c"
    break;

  case 12: /* stmt: break_stmt  */
#line 118 "parser2.y"
                  { log_error("stmt : break_stmt\n"); }
#line 1373 "parser2.tab.c"
    break;

  case 13: /* stmt: func_call  */
#line 119 "parser2.y"
                 { log_error("stmt : func_call\n"); }
#line 1379 "parser2.tab.c"
    break;

  case 14: /* stmt: error  */
#line 120 "parser2.y"
             { log_error(""); yyerror("syntax error: invalid expression"); }
#line 1385 "parser2.tab.c"
    break;

  case 15: /* switch_stmt: SWITCH LPAREN expr RPAREN LCURL case_list default_case_opt RCURL  */
#line 123 "parser2.y"
                                                                               {
    log_error("switch_stmt : SWITCH LPAREN expr RPAREN LCURL case_list default_case_opt RCURL\n");
    std::string asmCode = "\tMOV AX, " + yyvsp[-5].getSymbol() + "\n";
    asmCode += "\tMOV BX, AX\n";
    printASM(asmCode);
}
#line 1396 "parser2.tab.c"
    break;

  case 16: /* case_list: case_list case  */
#line 131 "parser2.y"
                           {
    log_error("case_list : case_list case\n");
}
#line 1404 "parser2.tab.c"
    break;

  case 17: /* case_list: case  */
#line 134 "parser2.y"
       {
    log_error("case_list : case\n");
}
#line 1412 "parser2.tab.c"
    break;

  case 18: /* case: CASE CONST_INT COLON stmt_list  */
#line 139 "parser2.y"
                                      {
    log_error("case : CASE CONST_INT COLON stmt_list\n");
    std::string asmCode = "\tCMP BX, " + string(yyvsp[-2].getSymbol()) + "\n";
    asmCode += "\tJE CASE_" + string(yyvsp[-2].getSymbol()) + "\n";
    asmCode += "CASE_" + string(yyvsp[-2].getSymbol()) + ":\n";
    asmCode += yyvsp[0].getCode();
    printASM(asmCode);
}
#line 1425 "parser2.tab.c"
    break;

  case 19: /* default_case_opt: default_case  */
#line 149 "parser2.y"
                                {
    log_error("default_case_opt : default_case\n");
}
#line 1433 "parser2.tab.c"
    break;

  case 20: /* default_case_opt: %empty  */
#line 152 "parser2.y"
              {
    log_error("default_case_opt : /* empty */\n");
}
#line 1441 "parser2.tab.c"
    break;

  case 21: /* default_case: DEFAULT COLON stmt_list  */
#line 157 "parser2.y"
                                       {
    log_error("default_case : DEFAULT COLON stmt_list\n");
    std::string asmCode = "DEFAULT:\n";
    asmCode += yyvsp[0].getCode();
    printASM(asmCode);
}
#line 1452 "parser2.tab.c"
    break;

  case 22: /* break_stmt: BREAK SEMICOLON  */
#line 165 "parser2.y"
                             {
    log_error("break_stmt : BREAK SEMICOLON\n");
    std::string asmCode = "\tJMP END_SWITCH\n";
    printASM(asmCode);
}
#line 1462 "parser2.tab.c"
    break;

  case 23: /* var_decl: type_spec decl_list SEMICOLON  */
#line 172 "parser2.y"
                                         {
    log_error("var_decl : type_spec decl_list SEMICOLON\n"); 
    std::string var = yyvsp[-1].getSymbol() + " DW ?\n";
    printASM(var, 1);
    variables.push_back(std::string(yyvsp[-1].getSymbol()));
    std::string asmCode = "\tMOV AX, " + yyvsp[-1].getSymbol() + "\n";
    asmCode += "\tMOV " + yyvsp[-1].getSymbol() + ", AX\n\n";
    yyval.setCode(asmCode);
}
#line 1476 "parser2.tab.c"
    break;

  case 24: /* type_spec: INT  */
#line 183 "parser2.y"
                {
        log_error("type_spec : INT\n");
        }
#line 1484 "parser2.tab.c"
    break;

  case 25: /* type_spec: FLOAT  */
#line 186 "parser2.y"
                  { log_error("type_spec : FLOAT\n"); }
#line 1490 "parser2.tab.c"
    break;

  case 26: /* type_spec: DOUBLE  */
#line 187 "parser2.y"
                   { log_error("type_spec : DOUBLE\n"); }
#line 1496 "parser2.tab.c"
    break;

  case 27: /* decl_list: term  */
#line 190 "parser2.y"
                 { log_error("decl_list : term\n"); }
#line 1502 "parser2.tab.c"
    break;

  case 28: /* expr_decl: term ASSIGNOP expr SEMICOLON  */
#line 193 "parser2.y"
                                          {
    log_error("expr_decl : term ASSIGNOP expr SEMICOLON\n");
    printIR(yyvsp[-3].getSymbol() + " = " + yyvsp[-1].getSymbol() + ";\n");
    std::string asmCode = "\tMOV AX, " + yyvsp[-1].getSymbol() + "\n";
    asmCode += "\tMOV " + yyvsp[-3].getSymbol() + ", AX\n\n";
    
    yyval.setCode(asmCode);
    printASM(asmCode);
    }
#line 1516 "parser2.tab.c"
    break;

  case 29: /* conditional: IF LPAREN expr RPAREN LCURL stmt_list RCURL  */
#line 204 "parser2.y"
                                                         { log_error("conditional : IF LPAREN expr RPAREN LCURL stmt_list RCURL\n"); }
#line 1522 "parser2.tab.c"
    break;

  case 30: /* conditional: IF LPAREN expr RPAREN LCURL stmt_list RCURL ELSE LCURL stmt_list RCURL  */
#line 205 "parser2.y"
                                                                                    { log_error("conditional : IF LPAREN expr RPAREN LCURL stmt_list RCURL ELSE LCURL stmt_list RCURL\n"); }
#line 1528 "parser2.tab.c"
    break;

  case 31: /* conditional: IF LPAREN expr RPAREN LCURL stmt_list RCURL ELIF LPAREN expr RPAREN LCURL stmt_list RCURL  */
#line 206 "parser2.y"
                                                                                                       { log_error("conditional : IF LPAREN expr RPAREN LCURL stmt_list RCURL ELIF LPAREN expr RPAREN LCURL stmt_list RCURL\n"); }
#line 1534 "parser2.tab.c"
    break;

  case 32: /* func_decl: type_spec term LPAREN param_list RPAREN LCURL stmt_list RCURL  */
#line 209 "parser2.y"
                                                                          {
    log_error("func_decl : type_spec ID LPAREN param_list RPAREN LCURL stmt_list RCURL\n");
    std::string asmCode = yyvsp[-6].getSymbol() + " PROC\n";
    asmCode += yyvsp[-1].getCode();
    asmCode += yyvsp[-6].getSymbol() + " ENDP\n";
    printASM(asmCode, 2);
}
#line 1546 "parser2.tab.c"
    break;

  case 33: /* func_decl: type_spec term SEMICOLON  */
#line 216 "parser2.y"
                           {
    log_error("func_decl : type_spec ID SEMICOLON\n");
}
#line 1554 "parser2.tab.c"
    break;

  case 34: /* param_list: param_list COMMA param  */
#line 221 "parser2.y"
                                    { log_error("param_list : param_list COMMA param\n"); }
#line 1560 "parser2.tab.c"
    break;

  case 35: /* param_list: param  */
#line 222 "parser2.y"
                   { log_error("param_list : param\n"); }
#line 1566 "parser2.tab.c"
    break;

  case 36: /* param_list: %empty  */
#line 223 "parser2.y"
                         { log_error("param_list : /* empty */\n"); }
#line 1572 "parser2.tab.c"
    break;

  case 37: /* param: type_spec ID  */
#line 226 "parser2.y"
                     { log_error("param : type_spec ID\n"); }
#line 1578 "parser2.tab.c"
    break;

  case 38: /* func_call: ID LPAREN arg_list RPAREN SEMICOLON  */
#line 229 "parser2.y"
                                                {
    log_error("func_call : ID LPAREN arg_list RPAREN SEMICOLON\n");
    std::string asmCode = "\tCALL " + yyvsp[-4].getSymbol() + "\n";
    printASM(asmCode, 2);
}
#line 1588 "parser2.tab.c"
    break;

  case 39: /* arg_list: arg_list COMMA expr  */
#line 236 "parser2.y"
                               { log_error("arg_list : arg_list COMMA expr\n"); }
#line 1594 "parser2.tab.c"
    break;

  case 40: /* arg_list: expr  */
#line 237 "parser2.y"
                { log_error("arg_list : expr\n"); }
#line 1600 "parser2.tab.c"
    break;

  case 41: /* arg_list: %empty  */
#line 238 "parser2.y"
                       { log_error("arg_list : /* empty */\n"); }
#line 1606 "parser2.tab.c"
    break;

  case 42: /* expr: CONST_INT  */
#line 241 "parser2.y"
                   { log_error("expr : CONST_INT \n"); }
#line 1612 "parser2.tab.c"
    break;

  case 43: /* expr: CONST_FLOAT  */
#line 242 "parser2.y"
                   { log_error("expr : CONST_FLOAT \n"); }
#line 1618 "parser2.tab.c"
    break;

  case 44: /* expr: expr MULOP expr  */
#line 243 "parser2.y"
                       { 
        log_error("expr : expr MULOP expr \n");
        std::string asmCode = "\tXOR DX, DX ;need to clear DX first\n"; 
        asmCode += "\tMOV AX, " + yyvsp[-2].getSymbol() + "\n"; 
        asmCode += "\tMOV BX, " + yyvsp[0].getSymbol() + "\n";
        asmCode += "\tMUL BX\n";
        asmCode += "\tMOV " + yyval.getSymbol() + ", AX\n\n";

        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        obj.setCode(asmCode);
        yyval = obj;  
        printIR(yyval.getSymbol() + " = " + yyvsp[-2].getSymbol() + " * " + yyvsp[0].getSymbol() + "\n");
        
        printASM(asmCode);
     }
#line 1639 "parser2.tab.c"
    break;

  case 45: /* expr: expr DIVOP expr  */
#line 259 "parser2.y"
                       { 
        log_error("expr : expr DIVOP expr \n"); 
        std::string asmCode = "\tXOR DX, DX ;need to clear DX first\n";
        asmCode += "\tMOV AX, " + yyvsp[-2].getSymbol() + "\n";
        asmCode += "\tMOV BX, " + yyvsp[0].getSymbol() + "\n";
        asmCode += "\tDIV BX\n";
        asmCode += "\tMOV " + yyval.getSymbol() + ", AX\n\n";

        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        obj.setCode(asmCode);
        yyval = obj;
        printIR(yyval.getSymbol() + " = " + yyvsp[-2].getSymbol() + " / " + yyvsp[0].getSymbol() + "\n");
        printASM(asmCode);
     }
#line 1659 "parser2.tab.c"
    break;

  case 46: /* expr: expr ADDOP expr  */
#line 274 "parser2.y"
                       { 
        log_error("expr : expr ADDOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        std::string asmCode = "\tMOV AX, " + yyvsp[-2].getSymbol() + "\n";
        asmCode += "\tMOV BX, " + yyvsp[0].getSymbol() + "\n";
        asmCode += "\tADD AX, BX\n";
        asmCode += "\tMOV " + yyval.getSymbol() + ", AX\n\n";

        obj.setCode(asmCode);
        yyval = obj;  
        printIR(yyval.getSymbol() + " = " + yyvsp[-2].getSymbol() + " + " + yyvsp[0].getSymbol() + "\n");
        printASM(asmCode);
     }
#line 1678 "parser2.tab.c"
    break;

  case 47: /* expr: expr SUBOP expr  */
#line 288 "parser2.y"
                       { 
        log_error("expr : expr SUBOP expr \n"); 
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        std::string asmCode = "\tMOV AX, " + yyvsp[-2].getSymbol() + "\n";
        asmCode += "\tMOV BX, " + yyvsp[0].getSymbol() + "\n";
        asmCode += "\tSUB AX, BX\n";
        asmCode += "\tMOV " + yyval.getSymbol() + ", AX\n\n";

        obj.setCode(asmCode);

        yyval = obj;
        
        printIR(yyval.getSymbol() + " = " + yyvsp[-2].getSymbol() + " - " + yyvsp[0].getSymbol() + "\n");
        printASM(asmCode);
     }
#line 1699 "parser2.tab.c"
    break;

  case 48: /* expr: expr LOGICOP expr  */
#line 304 "parser2.y"
                         { 
        log_error("expr : expr LOGICOP expr \n"); 
        std::string asmCode = "\tMOV AX, " + yyvsp[-2].getSymbol() + "\n";
        asmCode += "\tMOV BX, " + yyvsp[0].getSymbol() + "\n";
        if(yyvsp[-1].getSymbol() == "&&") {
            printIR(yyval.getSymbol() + " = " + yyvsp[-2].getSymbol() + " && " + yyvsp[0].getSymbol() + "\n");
            asmCode += "AND AX, BX\n";
        } else if(yyvsp[-1].getSymbol() == "||")  {
            printIR(yyval.getSymbol() + " = " + yyvsp[-2].getSymbol() + " || " + yyvsp[0].getSymbol() + "\n");
            asmCode += "OR AX, BX\n";    
        }
        asmCode += "\tMOV " + yyval.getSymbol() + ", AX\n\n";
        printASM(asmCode);
        char* str = newTemp();
        Symbol_Info obj(str, "TempID");
        obj.setCode(asmCode);
        yyval = obj;
        
     }
#line 1723 "parser2.tab.c"
    break;

  case 49: /* expr: LPAREN expr RPAREN  */
#line 323 "parser2.y"
                          { 
        log_error("expr : LPAREN expr RPAREN  \n");
        printIR(yyval.getSymbol() + " = " + yyvsp[-1].getSymbol() + "\n");
        std::string asmCode = "\tMOV AX, " + yyvsp[-1].getSymbol() + "\n";
        asmCode += "\tMOV " + yyval.getSymbol() + ", AX\n\n";
        yyval.setCode(asmCode);
        printASM(asmCode);
     }
#line 1736 "parser2.tab.c"
    break;

  case 50: /* expr: term  */
#line 331 "parser2.y"
            { 
        log_error("expr : term \n"); 
        printIR(yyval.getSymbol() + " = " + yyvsp[0].getSymbol() + "\n");
     }
#line 1745 "parser2.tab.c"
    break;

  case 51: /* term: ID  */
#line 337 "parser2.y"
          {
    Symbol_Info obj(std::string(yyvsp[0].getSymbol()), "ID");
    if (!(st.insert(obj))) {
        fprintf(yyout, "%s is already declared\n", yyvsp[0].getSymbol().c_str());
    } else {
        log_error("term: ID\n");
    }
}
#line 1758 "parser2.tab.c"
    break;


#line 1762 "parser2.tab.c"

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

#line 347 "parser2.y"


int main() 
{
    st.clear();
    clearOutput();
    std::string asmCode = ".MODEL SMALL\n";
    asmCode += ".STACK 100H\n";
    asmCode += ".DATA\n";
    printASM(asmCode, 0);
    asmCode="";
  
    asmCode += ".CODE\n";
    asmCode += "MAIN PROC\n";
    asmCode += "\tMOV AX, @DATA\n";
    asmCode += "\tMOV DS, AX\n";
    asmCode += "\tXOR AX, AX ;making AX=0\n";
    printASM(asmCode, 2);
    yyin = fopen("input.txt", "r");
    yyout = fopen("log_error.txt", "w");
    yyparse(); 

    st.print();

    asmCode = "\tMOV AH, 4CH\n";
    asmCode += "\tINT 21H\n";
    asmCode += "MAIN ENDP\n";
    asmCode += "END MAIN\n";
    printASM(asmCode, 3);

    for(auto &i: variables){
        printVar(i);
    }

    for(int i = 0; i < 4; ++i) {
        for(auto it: asm_code[i]) {
            std::ofstream op2;
            op2.open("code.asm", std::ios::app);
            if (!op2.is_open()) {
                std::cerr << "Error opening file.\n";
            }
            op2 << it;
            op2.close();
        }
    }

    return 0;
}
