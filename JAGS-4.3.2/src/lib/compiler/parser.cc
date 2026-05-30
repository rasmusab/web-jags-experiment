/* A Bison parser, made by GNU Bison 3.7.6.  */

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
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"

#include <compiler/ParseTree.h>
#include "remap.h"
#include "parser_extra.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <iostream>
#include <vector>
#include <sstream>

using std::malloc;
using std::free;
using jags::ParseTree;

  void yyerror(const char *);
  int yylex();
  int yylex_destroy();
  extern int yylineno;
  typedef struct yy_buffer_state *YY_BUFFER_STATE;
  YY_BUFFER_STATE yy_scan_bytes(char const *bytes, int len);
  void yy_delete_buffer(YY_BUFFER_STATE buffer);
  
#define YYDEBUG 1
  
  static std::vector<ParseTree *> * _pvariables = 0;
  static ParseTree *_pdata = 0;
  static ParseTree *_prelations = 0;
  
  static void setName(ParseTree *p, std::string *name);
  static void setParameters(ParseTree *p, std::vector<ParseTree*> *parameters);
  static void setParameters(ParseTree *p, ParseTree *param1);
  static void setParameters(ParseTree *p, ParseTree *param1, 
			    ParseTree *param2);
  static void setParameters(ParseTree *p, ParseTree *param1, ParseTree *param2,
			    ParseTree *param3);
  static ParseTree *Truncated (ParseTree *left, ParseTree *right);
  static ParseTree *Interval(ParseTree *left, ParseTree *right);
  

#line 110 "parser.cc"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_HH_INCLUDED
# define YY_YY_PARSER_HH_INCLUDED
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
    VAR = 258,                     /* VAR  */
    DATA = 259,                    /* DATA  */
    MODEL = 260,                   /* MODEL  */
    NAME = 261,                    /* NAME  */
    FUNC = 262,                    /* FUNC  */
    SPECIAL = 263,                 /* SPECIAL  */
    BADCHAR = 264,                 /* BADCHAR  */
    IN = 265,                      /* IN  */
    ARROW = 266,                   /* ARROW  */
    FOR = 267,                     /* FOR  */
    GT = 268,                      /* GT  */
    GE = 269,                      /* GE  */
    LT = 270,                      /* LT  */
    LE = 271,                      /* LE  */
    EQ = 272,                      /* EQ  */
    NE = 273,                      /* NE  */
    AND = 274,                     /* AND  */
    OR = 275,                      /* OR  */
    LENGTH = 276,                  /* LENGTH  */
    DIM = 277,                     /* DIM  */
    DOUBLE = 278,                  /* DOUBLE  */
    INT = 279,                     /* INT  */
    NOT = 280,                     /* NOT  */
    NEG = 281,                     /* NEG  */
    ENDL = 282,                    /* ENDL  */
    UREPCHAR = 283                 /* UREPCHAR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define VAR 258
#define DATA 259
#define MODEL 260
#define NAME 261
#define FUNC 262
#define SPECIAL 263
#define BADCHAR 264
#define IN 265
#define ARROW 266
#define FOR 267
#define GT 268
#define GE 269
#define LT 270
#define LE 271
#define EQ 272
#define NE 273
#define AND 274
#define OR 275
#define LENGTH 276
#define DIM 277
#define DOUBLE 278
#define INT 279
#define NOT 280
#define NEG 281
#define ENDL 282
#define UREPCHAR 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 42 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"

  /*
    We can't put any C++ class that requires a constructor in
    union. In particular, we can't have strings.  To get round this
    limitation, we put a pointer to a string in the union, and then
    get the lexical analyzer to return a pointer to a dynamically
    allocated string.  The parser frees the memory when it is done.
    This is tedious, but the alternative is to copy character
    arrays using, e.g. strncpy instead.
  */
  double val;
  std::string *stringptr;
  jags::ParseTree *ptree;
  std::vector<jags::ParseTree*> *pvec;

#line 235 "parser.cc"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HH_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VAR = 3,                        /* VAR  */
  YYSYMBOL_DATA = 4,                       /* DATA  */
  YYSYMBOL_MODEL = 5,                      /* MODEL  */
  YYSYMBOL_NAME = 6,                       /* NAME  */
  YYSYMBOL_FUNC = 7,                       /* FUNC  */
  YYSYMBOL_SPECIAL = 8,                    /* SPECIAL  */
  YYSYMBOL_BADCHAR = 9,                    /* BADCHAR  */
  YYSYMBOL_IN = 10,                        /* IN  */
  YYSYMBOL_ARROW = 11,                     /* ARROW  */
  YYSYMBOL_FOR = 12,                       /* FOR  */
  YYSYMBOL_GT = 13,                        /* GT  */
  YYSYMBOL_GE = 14,                        /* GE  */
  YYSYMBOL_LT = 15,                        /* LT  */
  YYSYMBOL_LE = 16,                        /* LE  */
  YYSYMBOL_EQ = 17,                        /* EQ  */
  YYSYMBOL_NE = 18,                        /* NE  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_LENGTH = 21,                    /* LENGTH  */
  YYSYMBOL_DIM = 22,                       /* DIM  */
  YYSYMBOL_DOUBLE = 23,                    /* DOUBLE  */
  YYSYMBOL_INT = 24,                       /* INT  */
  YYSYMBOL_NOT = 25,                       /* NOT  */
  YYSYMBOL_26_ = 26,                       /* '+'  */
  YYSYMBOL_27_ = 27,                       /* '-'  */
  YYSYMBOL_28_ = 28,                       /* '*'  */
  YYSYMBOL_29_ = 29,                       /* '/'  */
  YYSYMBOL_30_ = 30,                       /* ':'  */
  YYSYMBOL_NEG = 31,                       /* NEG  */
  YYSYMBOL_32_ = 32,                       /* '^'  */
  YYSYMBOL_ENDL = 33,                      /* ENDL  */
  YYSYMBOL_UREPCHAR = 34,                  /* UREPCHAR  */
  YYSYMBOL_35_ = 35,                       /* ';'  */
  YYSYMBOL_36_ = 36,                       /* ','  */
  YYSYMBOL_37_ = 37,                       /* '['  */
  YYSYMBOL_38_ = 38,                       /* ']'  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_41_ = 41,                       /* '('  */
  YYSYMBOL_42_ = 42,                       /* ')'  */
  YYSYMBOL_43_ = 43,                       /* '='  */
  YYSYMBOL_44_ = 44,                       /* '~'  */
  YYSYMBOL_45_T_ = 45,                     /* 'T'  */
  YYSYMBOL_46_I_ = 46,                     /* 'I'  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_input = 48,                     /* input  */
  YYSYMBOL_var_stmt = 49,                  /* var_stmt  */
  YYSYMBOL_dec_list = 50,                  /* dec_list  */
  YYSYMBOL_node_dec = 51,                  /* node_dec  */
  YYSYMBOL_dim_list = 52,                  /* dim_list  */
  YYSYMBOL_data_stmt = 53,                 /* data_stmt  */
  YYSYMBOL_model_stmt = 54,                /* model_stmt  */
  YYSYMBOL_relations = 55,                 /* relations  */
  YYSYMBOL_relation_list = 56,             /* relation_list  */
  YYSYMBOL_relation = 57,                  /* relation  */
  YYSYMBOL_for_loop = 58,                  /* for_loop  */
  YYSYMBOL_counter = 59,                   /* counter  */
  YYSYMBOL_assignment = 60,                /* assignment  */
  YYSYMBOL_determ_relation = 61,           /* determ_relation  */
  YYSYMBOL_stoch_relation = 62,            /* stoch_relation  */
  YYSYMBOL_product = 63,                   /* product  */
  YYSYMBOL_sum = 64,                       /* sum  */
  YYSYMBOL_expression = 65,                /* expression  */
  YYSYMBOL_expression_list = 66,           /* expression_list  */
  YYSYMBOL_range_list = 67,                /* range_list  */
  YYSYMBOL_range_element = 68,             /* range_element  */
  YYSYMBOL_distribution = 69,              /* distribution  */
  YYSYMBOL_truncated = 70,                 /* truncated  */
  YYSYMBOL_interval = 71,                  /* interval  */
  YYSYMBOL_var = 72                        /* var  */
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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   477

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  157

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   283


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
      41,    42,    28,    26,    36,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    30,    35,
       2,    43,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    45,     2,     2,     2,     2,     2,
       2,    37,     2,    38,    32,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,    44,     2,     2,     2,
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
      25,    31,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   105,   105,   106,   107,   108,   109,   112,   113,   116,
     117,   120,   123,   129,   130,   133,   140,   147,   153,   154,
     157,   158,   159,   160,   161,   164,   170,   176,   177,   180,
     184,   200,   204,   208,   214,   219,   229,   234,   243,   244,
     245,   249,   253,   257,   261,   265,   269,   273,   277,   281,
     285,   289,   293,   297,   301,   305,   309,   313,   317,   321,
     324,   325,   328,   329,   332,   333,   339,   344,   354,   355,
     356,   357,   360,   361,   362,   363,   366,   369
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
  "\"end of file\"", "error", "\"invalid token\"", "VAR", "DATA", "MODEL",
  "NAME", "FUNC", "SPECIAL", "BADCHAR", "IN", "ARROW", "FOR", "GT", "GE",
  "LT", "LE", "EQ", "NE", "AND", "OR", "LENGTH", "DIM", "DOUBLE", "INT",
  "NOT", "'+'", "'-'", "'*'", "'/'", "':'", "NEG", "'^'", "ENDL",
  "UREPCHAR", "';'", "','", "'['", "']'", "'{'", "'}'", "'('", "')'",
  "'='", "'~'", "'T'", "'I'", "$accept", "input", "var_stmt", "dec_list",
  "node_dec", "dim_list", "data_stmt", "model_stmt", "relations",
  "relation_list", "relation", "for_loop", "counter", "assignment",
  "determ_relation", "stoch_relation", "product", "sum", "expression",
  "expression_list", "range_list", "range_element", "distribution",
  "truncated", "interval", "var", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    43,    45,    42,    47,
      58,   281,    94,   282,   283,    59,    44,    91,    93,   123,
     125,    40,    41,    61,   126,    84,    73
};
#endif

#define YYPACT_NINF (-109)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      27,    -4,   -26,   -21,    21,    78,    39,  -109,    42,   139,
    -109,   149,   149,  -109,    39,  -109,  -109,   160,  -109,    -4,
      63,    -8,    35,     5,  -109,  -109,    65,    76,    92,    -7,
      28,  -109,    79,    91,    96,  -109,   160,   160,   -22,   120,
     114,   376,  -109,  -109,   160,   156,   163,  -109,  -109,   149,
    -109,  -109,  -109,  -109,  -109,   164,   160,  -109,   160,   156,
     156,   141,   176,   160,  -109,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   376,    85,  -109,   134,   170,    86,   144,   133,
     376,   376,    33,   155,   157,  -109,   376,   117,    -3,   106,
     422,   422,   422,   422,   422,   422,   445,   399,    -3,    -3,
     117,   117,   138,   141,   160,  -109,     4,   160,  -109,     1,
     145,   147,  -109,  -109,   160,  -109,  -109,  -109,  -109,   160,
     158,  -109,    36,    74,   136,   376,   376,  -109,  -109,    64,
     326,    67,   351,  -109,   206,   112,  -109,   236,   123,  -109,
    -109,   266,  -109,  -109,   296,  -109,  -109
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     0,     0,     0,     0,     3,    11,     7,
       9,     0,     0,     1,     0,     4,     5,     0,     8,     0,
      76,     0,     0,     0,    18,    22,     0,    21,    20,     0,
       0,     6,     0,     0,     0,    39,     0,     0,     0,    43,
      45,    13,    38,    10,    64,     0,     0,    15,    19,     0,
      25,    24,    23,    27,    28,     0,     0,    16,     0,     0,
       0,    47,     0,     0,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,     0,    62,     0,     0,     0,     0,    31,
      29,    60,     0,     0,     0,    59,    14,    35,    37,    58,
      49,    50,    51,    52,    53,    54,    55,    56,    36,    46,
      34,    44,    48,    57,    64,    77,     0,    64,    17,     0,
       0,     0,    32,    33,     0,    42,    40,    41,    63,     0,
       0,    67,     0,     0,     0,    61,    30,    26,    66,     0,
       0,     0,     0,    71,     0,     0,    75,     0,     0,    69,
      70,     0,    73,    74,     0,    68,    72
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,  -109,  -109,   179,  -109,   202,   146,  -109,   -11,
     -20,  -109,  -109,    93,  -109,  -109,  -109,  -109,   -17,    94,
    -109,  -108,  -109,  -109,  -109,    54
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     9,    10,    38,     6,     7,    50,    23,
      24,    25,    26,    56,    27,    28,    39,    40,    82,    92,
      83,    84,    89,   122,   123,    42
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,    30,     8,    48,    53,    67,   128,    20,    32,   130,
      48,    20,    21,    11,    63,    53,    64,    22,    12,    61,
      62,    13,    33,    34,    35,    78,    79,    80,    36,    81,
       1,     2,     3,    45,    20,    21,    54,    55,    87,    90,
      22,    91,    37,   131,     3,    47,    96,    54,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    29,    29,    48,    57,   124,
      20,    32,   124,    20,    32,   125,    46,    29,   138,    17,
      20,    32,     2,     3,    29,    33,    34,    35,    33,    34,
      35,    36,    20,    21,    36,    33,    34,    35,    22,    85,
      44,    36,    91,    29,    49,    37,   143,   135,    37,   146,
     139,    51,   136,    93,    94,    37,   140,   142,    20,    32,
      58,   114,   144,   115,   147,    67,   118,    52,   151,    20,
      32,   154,    59,    33,    34,    35,    80,    60,    81,    36,
      66,    29,    20,    32,    33,    34,    35,    80,    65,    81,
      36,    15,    16,    37,   150,    20,    21,    33,    34,    35,
      31,    22,    20,    36,    37,   153,    20,    32,    -1,    86,
      81,    88,   141,    81,    18,    19,   116,    37,   120,   121,
     117,    33,    34,    35,    67,   119,   133,    36,   134,    68,
      69,    70,    71,    72,    73,    74,    75,   126,    43,   127,
     137,    37,    76,    77,    78,    79,    80,    14,    81,   129,
       0,     0,     0,   132,    67,     0,     0,     0,    95,    68,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,     0,    81,     0,
       0,     0,     0,     0,    67,     0,     0,     0,   149,    68,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,     0,    81,     0,
       0,     0,     0,     0,    67,     0,     0,     0,   152,    68,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,     0,    81,     0,
       0,     0,     0,     0,    67,     0,     0,     0,   155,    68,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,     0,    81,     0,
       0,     0,     0,     0,    67,     0,     0,     0,   156,    68,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,     0,    81,    67,
       0,     0,   145,     0,    68,    69,    70,    71,    72,    73,
      74,    75,     0,     0,     0,     0,     0,    76,    77,    78,
      79,    80,     0,    81,    67,     0,     0,   148,     0,    68,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,    67,    81,     0,
       0,     0,    68,    69,    70,    71,    72,    73,    74,     0,
       0,     0,     0,     0,     0,    76,    77,    78,    79,    80,
      67,    81,     0,     0,     0,    -1,    -1,    -1,    -1,    -1,
      -1,     0,     0,     0,     0,     0,     0,     0,    76,    77,
      78,    79,    80,    67,    81,     0,     0,     0,    68,    69,
      70,    71,    72,    73,     0,     0,     0,     0,     0,     0,
       0,    76,    77,    78,    79,    80,     0,    81
};

static const yytype_int16 yycheck[] =
{
      17,    12,     6,    23,    11,     8,   114,     6,     7,   117,
      30,     6,     7,    39,    36,    11,    38,    12,    39,    36,
      37,     0,    21,    22,    23,    28,    29,    30,    27,    32,
       3,     4,     5,    41,     6,     7,    43,    44,    49,    56,
      12,    58,    41,    42,     5,    40,    63,    43,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    11,    12,    87,    40,    36,
       6,     7,    36,     6,     7,    42,    41,    23,    42,    37,
       6,     7,     4,     5,    30,    21,    22,    23,    21,    22,
      23,    27,     6,     7,    27,    21,    22,    23,    12,    45,
      37,    27,   119,    49,    39,    41,    42,   124,    41,    42,
      36,    35,   129,    59,    60,    41,   133,   134,     6,     7,
      41,    36,   139,    38,   141,     8,    40,    35,   145,     6,
       7,   148,    41,    21,    22,    23,    30,    41,    32,    27,
      26,    87,     6,     7,    21,    22,    23,    30,    28,    32,
      27,     5,     6,    41,    42,     6,     7,    21,    22,    23,
      14,    12,     6,    27,    41,    42,     6,     7,    30,     6,
      32,     7,    36,    32,    35,    36,    42,    41,    45,    46,
      10,    21,    22,    23,     8,    41,    41,    27,    41,    13,
      14,    15,    16,    17,    18,    19,    20,    42,    19,    42,
      42,    41,    26,    27,    28,    29,    30,     5,    32,   116,
      -1,    -1,    -1,   119,     8,    -1,    -1,    -1,    42,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    32,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    42,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    32,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    42,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    32,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    42,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    32,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    42,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    -1,    32,     8,
      -1,    -1,    36,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    30,    -1,    32,     8,    -1,    -1,    36,    -1,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,     8,    32,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
       8,    32,    -1,    -1,    -1,    13,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    30,     8,    32,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,    -1,    32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    48,    49,    53,    54,     6,    50,
      51,    39,    39,     0,    53,    54,    54,    37,    35,    36,
       6,     7,    12,    56,    57,    58,    59,    61,    62,    72,
      56,    54,     7,    21,    22,    23,    27,    41,    52,    63,
      64,    65,    72,    51,    37,    41,    41,    40,    57,    39,
      55,    35,    35,    11,    43,    44,    60,    40,    41,    41,
      41,    65,    65,    36,    38,    28,    26,     8,    13,    14,
      15,    16,    17,    18,    19,    20,    26,    27,    28,    29,
      30,    32,    65,    67,    68,    72,     6,    56,     7,    69,
      65,    65,    66,    72,    72,    42,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    36,    38,    42,    10,    40,    41,
      45,    46,    70,    71,    36,    42,    42,    42,    68,    60,
      68,    42,    66,    41,    41,    65,    65,    42,    42,    36,
      65,    36,    65,    42,    65,    36,    42,    65,    36,    42,
      42,    65,    42,    42,    65,    42,    42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    48,    48,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    53,    54,    55,    56,    56,
      57,    57,    57,    57,    57,    58,    59,    60,    60,    61,
      61,    62,    62,    62,    63,    63,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      66,    66,    67,    67,    68,    68,    69,    69,    70,    70,
      70,    70,    71,    71,    71,    71,    72,    72
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     2,     2,     3,     2,     3,     1,
       3,     1,     4,     1,     3,     4,     4,     3,     1,     2,
       1,     1,     1,     2,     2,     2,     6,     1,     1,     3,
       6,     3,     4,     4,     3,     3,     3,     3,     1,     1,
       4,     4,     4,     1,     3,     1,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     1,     3,     0,     1,     4,     3,     6,     5,
       5,     4,     6,     5,     5,     4,     1,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
  case 7: /* var_stmt: VAR dec_list  */
#line 112 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                       { _pvariables = (yyvsp[0].pvec); }
#line 1457 "parser.cc"
    break;

  case 8: /* var_stmt: VAR dec_list ';'  */
#line 113 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                   { _pvariables = (yyvsp[-1].pvec); }
#line 1463 "parser.cc"
    break;

  case 9: /* dec_list: node_dec  */
#line 116 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                   { (yyval.pvec) = new std::vector<ParseTree*>(1, (yyvsp[0].ptree)); }
#line 1469 "parser.cc"
    break;

  case 10: /* dec_list: dec_list ',' node_dec  */
#line 117 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                        { (yyval.pvec) = (yyvsp[-2].pvec); (yyval.pvec)->push_back((yyvsp[0].ptree)); }
#line 1475 "parser.cc"
    break;

  case 11: /* node_dec: NAME  */
#line 120 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
               {
    (yyval.ptree) = new ParseTree(jags::P_VAR, yylineno); setName((yyval.ptree), (yyvsp[0].stringptr)); 
}
#line 1483 "parser.cc"
    break;

  case 12: /* node_dec: NAME '[' dim_list ']'  */
#line 123 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                        {
    (yyval.ptree) = new ParseTree(jags::P_VAR, yylineno); setName((yyval.ptree), (yyvsp[-3].stringptr));
    setParameters((yyval.ptree), (yyvsp[-1].pvec));
}
#line 1492 "parser.cc"
    break;

  case 13: /* dim_list: expression  */
#line 129 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                     { (yyval.pvec) = new std::vector<ParseTree*>(1, (yyvsp[0].ptree)); }
#line 1498 "parser.cc"
    break;

  case 14: /* dim_list: dim_list ',' expression  */
#line 130 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                          { (yyval.pvec)=(yyvsp[-2].pvec); (yyval.pvec)->push_back((yyvsp[0].ptree)); }
#line 1504 "parser.cc"
    break;

  case 15: /* data_stmt: DATA '{' relation_list '}'  */
#line 133 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                      {
    ParseTree *p = new ParseTree(jags::P_RELATIONS, yylineno);
    setParameters(p, (yyvsp[-1].pvec));
    _pdata = p;
}
#line 1514 "parser.cc"
    break;

  case 16: /* model_stmt: MODEL '{' relation_list '}'  */
#line 140 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                        { 
    ParseTree *p = new ParseTree(jags::P_RELATIONS, yylineno);
    setParameters(p, (yyvsp[-1].pvec));
    _prelations = p;
}
#line 1524 "parser.cc"
    break;

  case 17: /* relations: '{' relation_list '}'  */
#line 147 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                 {
    (yyval.ptree) = new ParseTree(jags::P_RELATIONS, yylineno);
    setParameters((yyval.ptree), (yyvsp[-1].pvec));
}
#line 1533 "parser.cc"
    break;

  case 18: /* relation_list: relation  */
#line 153 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                         { (yyval.pvec) = new std::vector<ParseTree*>(1, (yyvsp[0].ptree)); }
#line 1539 "parser.cc"
    break;

  case 19: /* relation_list: relation_list relation  */
#line 154 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                         { (yyval.pvec)=(yyvsp[-1].pvec); (yyval.pvec)->push_back((yyvsp[0].ptree)); }
#line 1545 "parser.cc"
    break;

  case 25: /* for_loop: counter relations  */
#line 164 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                            {
    (yyval.ptree) = new ParseTree(jags::P_FOR, yylineno);
    setParameters((yyval.ptree), (yyvsp[-1].ptree), (yyvsp[0].ptree));
}
#line 1554 "parser.cc"
    break;

  case 26: /* counter: FOR '(' NAME IN range_element ')'  */
#line 170 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                           {
    (yyval.ptree) = new ParseTree(jags::P_COUNTER, yylineno); setName((yyval.ptree), (yyvsp[-3].stringptr));
    setParameters((yyval.ptree), (yyvsp[-1].ptree));
}
#line 1563 "parser.cc"
    break;

  case 29: /* determ_relation: var assignment expression  */
#line 180 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                           {
    (yyval.ptree) = new ParseTree(jags::P_DETRMREL, yylineno);
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
}
#line 1572 "parser.cc"
    break;

  case 30: /* determ_relation: FUNC '(' var ')' assignment expression  */
#line 184 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                         {

  /* 
     The link function is given using an S-style replacement function
     notation.  We need to turn this round so the inverse link
     function is applied to the RHS of the deterministic relation
  */
     
    ParseTree *p = new ParseTree(jags::P_LINK, yylineno); setName(p, (yyvsp[-5].stringptr));
    setParameters(p, (yyvsp[0].ptree));
    
    (yyval.ptree) = new ParseTree(jags::P_DETRMREL, yylineno);
    setParameters((yyval.ptree), (yyvsp[-3].ptree), p);
}
#line 1591 "parser.cc"
    break;

  case 31: /* stoch_relation: var '~' distribution  */
#line 200 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                     {
    (yyval.ptree) = new ParseTree(jags::P_STOCHREL, yylineno); 
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
 }
#line 1600 "parser.cc"
    break;

  case 32: /* stoch_relation: var '~' distribution truncated  */
#line 204 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                 {
    (yyval.ptree) = new ParseTree(jags::P_STOCHREL, yylineno); 
    setParameters((yyval.ptree), (yyvsp[-3].ptree), (yyvsp[-1].ptree), (yyvsp[0].ptree));
}
#line 1609 "parser.cc"
    break;

  case 33: /* stoch_relation: var '~' distribution interval  */
#line 208 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                {
    (yyval.ptree) = new ParseTree(jags::P_STOCHREL, yylineno);
    setParameters((yyval.ptree), (yyvsp[-3].ptree), (yyvsp[-1].ptree), (yyvsp[0].ptree));
}
#line 1618 "parser.cc"
    break;

  case 34: /* product: expression '*' expression  */
#line 214 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                   {
  (yyval.pvec) = new std::vector<ParseTree*>;
  (yyval.pvec)->push_back((yyvsp[-2].ptree));
  (yyval.pvec)->push_back((yyvsp[0].ptree));
}
#line 1628 "parser.cc"
    break;

  case 35: /* product: product '*' expression  */
#line 219 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                         {
  //  This creates a shift-reduce conflict because in the expression
  //  A*B*C, (A*B) is a valid expression. By default, bison shifts,
  //  which is what we want. The warning is suppressed with the %expect
  //  declaration (See also sum: below).
  (yyval.pvec) = (yyvsp[-2].pvec);
  (yyval.pvec)->push_back((yyvsp[0].ptree));
}
#line 1641 "parser.cc"
    break;

  case 36: /* sum: expression '+' expression  */
#line 229 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                               {
  (yyval.pvec) = new std::vector<ParseTree*>;
  (yyval.pvec)->push_back((yyvsp[-2].ptree));
  (yyval.pvec)->push_back((yyvsp[0].ptree));
}
#line 1651 "parser.cc"
    break;

  case 37: /* sum: sum '+' expression  */
#line 234 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                     {
  //  This creates a shift-reduce conflict. By default, bison shifts,
  //  which is what we want. The warning is suppressed with the %expect
  //  declaration (See also product: above).
  (yyval.pvec) = (yyvsp[-2].pvec);
  (yyval.pvec)->push_back((yyvsp[0].ptree));
}
#line 1663 "parser.cc"
    break;

  case 39: /* expression: DOUBLE  */
#line 244 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
         {(yyval.ptree) = new ParseTree(jags::P_VALUE, yylineno); (yyval.ptree)->setValue((yyvsp[0].val));}
#line 1669 "parser.cc"
    break;

  case 40: /* expression: LENGTH '(' var ')'  */
#line 245 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                     {
    (yyval.ptree) = new ParseTree(jags::P_LENGTH, yylineno);
    setParameters((yyval.ptree),(yyvsp[-1].ptree));
}
#line 1678 "parser.cc"
    break;

  case 41: /* expression: DIM '(' var ')'  */
#line 249 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                  {
    (yyval.ptree) = new ParseTree(jags::P_DIM, yylineno);
    setParameters((yyval.ptree),(yyvsp[-1].ptree));
}
#line 1687 "parser.cc"
    break;

  case 42: /* expression: FUNC '(' expression_list ')'  */
#line 253 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                               {
  (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); setName((yyval.ptree), (yyvsp[-3].stringptr));
  setParameters((yyval.ptree), (yyvsp[-1].pvec));
}
#line 1696 "parser.cc"
    break;

  case 43: /* expression: product  */
#line 257 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
          {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("*");
    setParameters((yyval.ptree), (yyvsp[0].pvec));
}
#line 1705 "parser.cc"
    break;

  case 44: /* expression: expression '/' expression  */
#line 261 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                            {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("/");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
}
#line 1714 "parser.cc"
    break;

  case 45: /* expression: sum  */
#line 265 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
      {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("+");
    setParameters((yyval.ptree), (yyvsp[0].pvec));
}
#line 1723 "parser.cc"
    break;

  case 46: /* expression: expression '-' expression  */
#line 269 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                            {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("-");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
}
#line 1732 "parser.cc"
    break;

  case 47: /* expression: '-' expression  */
#line 273 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                           {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("NEG");
    setParameters((yyval.ptree), (yyvsp[0].ptree));
}
#line 1741 "parser.cc"
    break;

  case 48: /* expression: expression ':' expression  */
#line 277 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                            {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName(":");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
}
#line 1750 "parser.cc"
    break;

  case 49: /* expression: expression GT expression  */
#line 281 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                           {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName(">");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
 }
#line 1759 "parser.cc"
    break;

  case 50: /* expression: expression GE expression  */
#line 285 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                           {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName(">=");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
 }
#line 1768 "parser.cc"
    break;

  case 51: /* expression: expression LT expression  */
#line 289 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                           {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("<");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
 }
#line 1777 "parser.cc"
    break;

  case 52: /* expression: expression LE expression  */
#line 293 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                           {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("<=");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
 }
#line 1786 "parser.cc"
    break;

  case 53: /* expression: expression EQ expression  */
#line 297 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                           {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("==");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
 }
#line 1795 "parser.cc"
    break;

  case 54: /* expression: expression NE expression  */
#line 301 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                           {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("!=");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
}
#line 1804 "parser.cc"
    break;

  case 55: /* expression: expression AND expression  */
#line 305 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                            {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("&&");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
 }
#line 1813 "parser.cc"
    break;

  case 56: /* expression: expression OR expression  */
#line 309 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                           {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("||");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
}
#line 1822 "parser.cc"
    break;

  case 57: /* expression: expression '^' expression  */
#line 313 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                            {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); (yyval.ptree)->setName("^");
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
  }
#line 1831 "parser.cc"
    break;

  case 58: /* expression: expression SPECIAL expression  */
#line 317 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                {
    (yyval.ptree) = new ParseTree(jags::P_FUNCTION, yylineno); setName((yyval.ptree), (yyvsp[-1].stringptr));
    setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
 }
#line 1840 "parser.cc"
    break;

  case 59: /* expression: '(' expression ')'  */
#line 321 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                     { (yyval.ptree) = (yyvsp[-1].ptree); }
#line 1846 "parser.cc"
    break;

  case 60: /* expression_list: expression  */
#line 324 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                            { (yyval.pvec) = new std::vector<ParseTree*>(1, (yyvsp[0].ptree)); }
#line 1852 "parser.cc"
    break;

  case 61: /* expression_list: expression_list ',' expression  */
#line 325 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                 { (yyval.pvec)=(yyvsp[-2].pvec); (yyval.pvec)->push_back((yyvsp[0].ptree)); }
#line 1858 "parser.cc"
    break;

  case 62: /* range_list: range_element  */
#line 328 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                          { (yyval.pvec) = new std::vector<ParseTree*>(1, (yyvsp[0].ptree)); }
#line 1864 "parser.cc"
    break;

  case 63: /* range_list: range_list ',' range_element  */
#line 329 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                               { (yyval.pvec)=(yyvsp[-2].pvec); (yyval.pvec)->push_back((yyvsp[0].ptree)); }
#line 1870 "parser.cc"
    break;

  case 64: /* range_element: %empty  */
#line 332 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
               {(yyval.ptree) = new ParseTree(jags::P_RANGE, yylineno);}
#line 1876 "parser.cc"
    break;

  case 65: /* range_element: expression  */
#line 333 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
             {
    (yyval.ptree) = new ParseTree(jags::P_RANGE, yylineno); 
    setParameters((yyval.ptree),(yyvsp[0].ptree));
}
#line 1885 "parser.cc"
    break;

  case 66: /* distribution: FUNC '(' expression_list ')'  */
#line 340 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
{
  (yyval.ptree) = new ParseTree(jags::P_DENSITY, yylineno); setName((yyval.ptree), (yyvsp[-3].stringptr));
  setParameters((yyval.ptree), (yyvsp[-1].pvec));
}
#line 1894 "parser.cc"
    break;

  case 67: /* distribution: FUNC '(' ')'  */
#line 345 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
{
    //BUGS has a dflat() distribution with no parameters
    (yyval.ptree) = new ParseTree(jags::P_DENSITY, yylineno); setName((yyval.ptree), (yyvsp[-2].stringptr));
}
#line 1903 "parser.cc"
    break;

  case 68: /* truncated: 'T' '(' expression ',' expression ')'  */
#line 354 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                                  {(yyval.ptree) = Truncated((yyvsp[-3].ptree),(yyvsp[-1].ptree));}
#line 1909 "parser.cc"
    break;

  case 69: /* truncated: 'T' '(' ',' expression ')'  */
#line 355 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                             {(yyval.ptree) = Truncated(0,(yyvsp[-1].ptree));}
#line 1915 "parser.cc"
    break;

  case 70: /* truncated: 'T' '(' expression ',' ')'  */
#line 356 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                             {(yyval.ptree) = Truncated((yyvsp[-2].ptree),0);}
#line 1921 "parser.cc"
    break;

  case 71: /* truncated: 'T' '(' ',' ')'  */
#line 357 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                  {(yyval.ptree) = Truncated(0,0);}
#line 1927 "parser.cc"
    break;

  case 72: /* interval: 'I' '(' expression ',' expression ')'  */
#line 360 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                                                 {(yyval.ptree) = Interval((yyvsp[-3].ptree),(yyvsp[-1].ptree));}
#line 1933 "parser.cc"
    break;

  case 73: /* interval: 'I' '(' ',' expression ')'  */
#line 361 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                             {(yyval.ptree) = Interval(0,(yyvsp[-1].ptree));}
#line 1939 "parser.cc"
    break;

  case 74: /* interval: 'I' '(' expression ',' ')'  */
#line 362 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                             {(yyval.ptree) = Interval((yyvsp[-2].ptree),0);}
#line 1945 "parser.cc"
    break;

  case 75: /* interval: 'I' '(' ',' ')'  */
#line 363 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                  {(yyval.ptree) = Interval(0,0);}
#line 1951 "parser.cc"
    break;

  case 76: /* var: NAME  */
#line 366 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
          {
  (yyval.ptree) = new ParseTree(jags::P_VAR, yylineno); setName((yyval.ptree), (yyvsp[0].stringptr));
}
#line 1959 "parser.cc"
    break;

  case 77: /* var: NAME '[' range_list ']'  */
#line 369 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"
                          {
  (yyval.ptree) = new ParseTree(jags::P_VAR, yylineno); setName((yyval.ptree), (yyvsp[-3].stringptr));
  setParameters((yyval.ptree), (yyvsp[-1].pvec));
}
#line 1968 "parser.cc"
    break;


#line 1972 "parser.cc"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 375 "../../../../../jags-4-3_patched/src/lib/compiler/parser.yy"


static std::string error_buf;

void yyerror (const char *s)
{
    extern char * yytext;
    extern int yylineno;

    std::ostringstream msg;
    msg << std::string(s) << " on line " << yylineno << " near \"" << 
           std::string(yytext) << "\"";
    error_buf = msg.str();
}

static ParseTree *Truncated (ParseTree *left, ParseTree *right)
{
    //JAGS-Style truncation notation
    ParseTree *p = new ParseTree(jags::P_BOUNDS, yylineno);
    setParameters(p, left, right);
    return p;
}

static ParseTree *Interval (ParseTree *left, ParseTree *right)
{
    //BUGS-Style interval censoring notation
    ParseTree *p = new ParseTree(jags::P_INTERVAL, yylineno);
    setParameters(p, left, right);
    return p;
}

void setName(ParseTree *p, std::string *name)
{
  /* 
     The scanner cannot return a string, because a string cannot be
     part of a union.  So instead the scanner returns a pointer to
     a newly allocated string.  This memory must be freed as soon
     as it is used.
  */
  p->setName(*name);
  delete name;
}
	

void setParameters(ParseTree *p, std::vector<ParseTree*> *parameters)
{
  /* 
     Same as setName (above).  The parser dynamically allocates
     vectors of (pointers to) parameters. These vectors must be
     deleted when we are done with them.
  */
  p->setParameters(*parameters);
  delete parameters; 
}

void setParameters(ParseTree *p, ParseTree *param1)
{
  /*
    Wrapper function that creates a vector containing param1
    to be passed to ParseTree::setParameters.
  */
  std::vector<ParseTree *> parameters(1, param1);
  p->setParameters(parameters);
}

void setParameters(ParseTree *p, ParseTree *param1, ParseTree *param2)
{
  /*
    Wrapper function that creates a vector containing param1
    and param2, to be passed to ParseTree::setParameters
  */
  std::vector<ParseTree *> parameters;
  parameters.push_back(param1);
  parameters.push_back(param2);
  p->setParameters(parameters);
}

void setParameters(ParseTree *p, ParseTree *param1, ParseTree *param2,
		   ParseTree *param3)
{
  /*
    Wrapper function that creates a vector containing param1, param2
    and param3, to be passed to ParseTree::setParameters
  */
  std::vector<ParseTree *> parameters;
  parameters.push_back(param1);
  parameters.push_back(param2);
  parameters.push_back(param3);
  p->setParameters(parameters);
}

static int collect_parse_result(int parse_status,
				std::vector<ParseTree*> * &dec_list,
				ParseTree * &data, ParseTree * &relations,
				std::string &message)
{
    int val = 0;

    if (parse_status == 0) {
	dec_list = _pvariables; 
	data = _pdata; 
	relations = _prelations;
    }
    else {
	message = error_buf;
	delete _pvariables; 
	delete _prelations; 
	delete _pdata;
	val = 1;
    }
    _pvariables = 0;
    _prelations = 0;
    _pdata = 0;

    yylex_destroy();

    return val;
}

int parse_bugs (std::FILE *file, std::vector<ParseTree*> * &dec_list, 
                ParseTree * &data, ParseTree * &relations,
		std::string &message)
{
    extern std::FILE *yyin;
    yyin = file;
    
    error_buf.clear();
    yylineno = 1;

    return collect_parse_result(yyparse(), dec_list, data, relations, message);
}

int parse_bugs_string(char const *text, std::size_t length,
		      std::vector<ParseTree*> * &dec_list,
		      ParseTree * &data, ParseTree * &relations,
		      std::string &message)
{
    if (length > static_cast<std::size_t>(INT_MAX)) {
	message = "Model text is too large to parse";
	return 1;
    }

    error_buf.clear();
    yylineno = 1;

    YY_BUFFER_STATE buffer =
	yy_scan_bytes(text, static_cast<int>(length));
    int parse_status = 1;
    try {
	parse_status = yyparse();
	yy_delete_buffer(buffer);
    }
    catch (...) {
	yy_delete_buffer(buffer);
	yylex_destroy();
	throw;
    }

    return collect_parse_result(parse_status, dec_list, data, relations, message);
}
