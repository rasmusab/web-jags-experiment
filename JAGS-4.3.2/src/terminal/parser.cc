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

/* Substitute the type names.  */
#define YYSTYPE         ZZSTYPE
/* Substitute the variable and function names.  */
#define yyparse         zzparse
#define yylex           zzlex
#define yyerror         zzerror
#define yydebug         zzdebug
#define yynerrs         zznerrs
#define yylval          zzlval
#define yychar          zzchar

/* First part of user prologue.  */
#line 2 "../../../../jags-4-3_patched/src/terminal/parser.yy"

#include <config.h>

#ifdef Win32
#include <windows.h>   /* For getCurrentDirectory */
#include <io.h>        /* For chdir */
#else
#include <unistd.h>    /* For getcwd, chdir */
#endif

//#include <limits.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <fstream>
#include <list>
#include <iterator>
#include <string>
#include <utility>

#include <dirent.h>
#include <time.h>
#include <errno.h>

#include <Console.h>
#include <module/Module.h>
#include <compiler/ParseTree.h>
#include <util/nainf.h>
#include <cstring>
#include <ltdl.h>

//Required for warning about masked distributions after module loading
#include <deque>
#include <distribution/Distribution.h>
#include <compiler/Compiler.h>

#include "ReadData.h"

    typedef void(*pt2Func)();

    int zzerror(const char *);
    int zzlex();
    int zzlex_destroy();
#define YYERROR_VERBOSE 0
    static jags::Console *console;
    bool interactive;
    extern int command_buffer_count;
    void setName(jags::ParseTree *p, std::string *name);
    std::map<std::string, jags::SArray> _data_table;
    std::deque<lt_dlhandle> _dyn_lib;
    bool open_data_buffer(std::string const *name);
    bool open_command_buffer(std::string const *name);
    void return_to_main_buffer();
    void setMonitor(jags::ParseTree const *var, int thin, std::string const &type);
    void clearMonitor(jags::ParseTree const *var, std::string const &type);
    void doCoda (jags::ParseTree const *var, std::string const &stem);
    void doAllCoda (std::string const &stem);
    void doDump (std::string const &file, jags::DumpType type, unsigned int chain);
    void dumpMonitors(std::string const &file, std::string const &type);
    void doSystem(std::string const *command);
    std::string ExpandFileName(char const *s);

    static bool getWorkingDirectory(std::string &name);
    static void errordump();
    static void updatestar(long niter, long refresh, int width);
	// Run adaptation phase until adapted, regardless of iterations:
    static void autoadaptstar(long maxiter, long refresh, int width);
    static void adaptstar(long niter, long refresh, int width, bool force);
    static void setParameters(jags::ParseTree *p, jags::ParseTree *param1);
    static void setParameters(jags::ParseTree *p, std::vector<jags::ParseTree*> *parameters);
    static void setParameters(jags::ParseTree *p, jags::ParseTree *param1, jags::ParseTree *param2);
    static void loadModule(std::string const &name);
    static void unloadModule(std::string const &name);
    static void dumpSamplers(std::string const &file);
    static void delete_pvec(std::vector<jags::ParseTree*> *);
    static void print_unused_variables(std::map<std::string, jags::SArray> const &table, bool data);
    static void listFactories(jags::FactoryType type);
	static void listModules();
    static void setFactory(std::string const &name, jags::FactoryType type,
                           std::string const &status);
    static void setSeed(unsigned int seed);
    static bool Jtry(bool ok);
	// Needed for update (and adapt) functions to dump variable states:
    static bool Jtry_dump(bool ok);
	// Note: on !ok, Jtry(_dump) only exits if !interactive and otherwise returns ok, 
	// so the parent function should evaluate the value and return; if appriopriate
    

#line 174 "parser.cc"

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
#ifndef YY_ZZ_PARSER_HH_INCLUDED
# define YY_ZZ_PARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef ZZDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define ZZDEBUG 1
#  else
#   define ZZDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define ZZDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined ZZDEBUG */
#if ZZDEBUG
extern int zzdebug;
#endif

/* Token kinds.  */
#ifndef ZZTOKENTYPE
# define ZZTOKENTYPE
  enum zztokentype
  {
    ZZEMPTY = -2,
    ZZEOF = 0,                     /* "end of file"  */
    ZZerror = 256,                 /* error  */
    ZZUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    DOUBLE = 259,                  /* DOUBLE  */
    NAME = 260,                    /* NAME  */
    STRING = 261,                  /* STRING  */
    SYSCMD = 262,                  /* SYSCMD  */
    ENDCMD = 263,                  /* ENDCMD  */
    MODEL = 264,                   /* MODEL  */
    DATA = 265,                    /* DATA  */
    IN = 266,                      /* IN  */
    TO = 267,                      /* TO  */
    INITS = 268,                   /* INITS  */
    PARAMETERS = 269,              /* PARAMETERS  */
    COMPILE = 270,                 /* COMPILE  */
    INITIALIZE = 271,              /* INITIALIZE  */
    ADAPT = 272,                   /* ADAPT  */
    AUTOADAPT = 273,               /* AUTOADAPT  */
    FORCEADAPT = 274,              /* FORCEADAPT  */
    UPDATE = 275,                  /* UPDATE  */
    BY = 276,                      /* BY  */
    MONITORS = 277,                /* MONITORS  */
    MONITOR = 278,                 /* MONITOR  */
    TYPE = 279,                    /* TYPE  */
    SET = 280,                     /* SET  */
    CLEAR = 281,                   /* CLEAR  */
    THIN = 282,                    /* THIN  */
    CODA = 283,                    /* CODA  */
    STEM = 284,                    /* STEM  */
    EXIT = 285,                    /* EXIT  */
    NCHAINS = 286,                 /* NCHAINS  */
    CHAIN = 287,                   /* CHAIN  */
    LOAD = 288,                    /* LOAD  */
    UNLOAD = 289,                  /* UNLOAD  */
    SAMPLER = 290,                 /* SAMPLER  */
    SAMPLERS = 291,                /* SAMPLERS  */
    RNGTOK = 292,                  /* RNGTOK  */
    FACTORY = 293,                 /* FACTORY  */
    FACTORIES = 294,               /* FACTORIES  */
    MODULES = 295,                 /* MODULES  */
    SEED = 296,                    /* SEED  */
    LIST = 297,                    /* LIST  */
    STRUCTURE = 298,               /* STRUCTURE  */
    DIM = 299,                     /* DIM  */
    NA = 300,                      /* NA  */
    R_NULL = 301,                  /* R_NULL  */
    DIMNAMES = 302,                /* DIMNAMES  */
    ITER = 303,                    /* ITER  */
    ARROW = 304,                   /* ARROW  */
    ENDDATA = 305,                 /* ENDDATA  */
    ASINTEGER = 306,               /* ASINTEGER  */
    DOTDATA = 307,                 /* DOTDATA  */
    DIRECTORY = 308,               /* DIRECTORY  */
    CD = 309,                      /* CD  */
    PWD = 310,                     /* PWD  */
    RUN = 311,                     /* RUN  */
    ENDSCRIPT = 312                /* ENDSCRIPT  */
  };
  typedef enum zztokentype zztoken_kind_t;
#endif
/* Token kinds.  */
#define ZZEMPTY -2
#define ZZEOF 0
#define ZZerror 256
#define ZZUNDEF 257
#define INT 258
#define DOUBLE 259
#define NAME 260
#define STRING 261
#define SYSCMD 262
#define ENDCMD 263
#define MODEL 264
#define DATA 265
#define IN 266
#define TO 267
#define INITS 268
#define PARAMETERS 269
#define COMPILE 270
#define INITIALIZE 271
#define ADAPT 272
#define AUTOADAPT 273
#define FORCEADAPT 274
#define UPDATE 275
#define BY 276
#define MONITORS 277
#define MONITOR 278
#define TYPE 279
#define SET 280
#define CLEAR 281
#define THIN 282
#define CODA 283
#define STEM 284
#define EXIT 285
#define NCHAINS 286
#define CHAIN 287
#define LOAD 288
#define UNLOAD 289
#define SAMPLER 290
#define SAMPLERS 291
#define RNGTOK 292
#define FACTORY 293
#define FACTORIES 294
#define MODULES 295
#define SEED 296
#define LIST 297
#define STRUCTURE 298
#define DIM 299
#define NA 300
#define R_NULL 301
#define DIMNAMES 302
#define ITER 303
#define ARROW 304
#define ENDDATA 305
#define ASINTEGER 306
#define DOTDATA 307
#define DIRECTORY 308
#define CD 309
#define PWD 310
#define RUN 311
#define ENDSCRIPT 312

/* Value type.  */
#if ! defined ZZSTYPE && ! defined ZZSTYPE_IS_DECLARED
union ZZSTYPE
{
#line 99 "../../../../jags-4-3_patched/src/terminal/parser.yy"

  int intval;
  double val;
  std::string *stringptr;
  jags::ParseTree *ptree;
  std::vector<jags::ParseTree*> *pvec;
  std::vector<double> *vec;
  std::vector<long> *ivec;

#line 359 "parser.cc"

};
typedef union ZZSTYPE ZZSTYPE;
# define ZZSTYPE_IS_TRIVIAL 1
# define ZZSTYPE_IS_DECLARED 1
#endif


extern ZZSTYPE zzlval;


int zzparse (void);


#endif /* !YY_ZZ_PARSER_HH_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_DOUBLE = 4,                     /* DOUBLE  */
  YYSYMBOL_NAME = 5,                       /* NAME  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_SYSCMD = 7,                     /* SYSCMD  */
  YYSYMBOL_ENDCMD = 8,                     /* ENDCMD  */
  YYSYMBOL_MODEL = 9,                      /* MODEL  */
  YYSYMBOL_DATA = 10,                      /* DATA  */
  YYSYMBOL_IN = 11,                        /* IN  */
  YYSYMBOL_TO = 12,                        /* TO  */
  YYSYMBOL_INITS = 13,                     /* INITS  */
  YYSYMBOL_PARAMETERS = 14,                /* PARAMETERS  */
  YYSYMBOL_COMPILE = 15,                   /* COMPILE  */
  YYSYMBOL_INITIALIZE = 16,                /* INITIALIZE  */
  YYSYMBOL_ADAPT = 17,                     /* ADAPT  */
  YYSYMBOL_AUTOADAPT = 18,                 /* AUTOADAPT  */
  YYSYMBOL_FORCEADAPT = 19,                /* FORCEADAPT  */
  YYSYMBOL_UPDATE = 20,                    /* UPDATE  */
  YYSYMBOL_BY = 21,                        /* BY  */
  YYSYMBOL_MONITORS = 22,                  /* MONITORS  */
  YYSYMBOL_MONITOR = 23,                   /* MONITOR  */
  YYSYMBOL_TYPE = 24,                      /* TYPE  */
  YYSYMBOL_SET = 25,                       /* SET  */
  YYSYMBOL_CLEAR = 26,                     /* CLEAR  */
  YYSYMBOL_THIN = 27,                      /* THIN  */
  YYSYMBOL_CODA = 28,                      /* CODA  */
  YYSYMBOL_STEM = 29,                      /* STEM  */
  YYSYMBOL_EXIT = 30,                      /* EXIT  */
  YYSYMBOL_NCHAINS = 31,                   /* NCHAINS  */
  YYSYMBOL_CHAIN = 32,                     /* CHAIN  */
  YYSYMBOL_LOAD = 33,                      /* LOAD  */
  YYSYMBOL_UNLOAD = 34,                    /* UNLOAD  */
  YYSYMBOL_SAMPLER = 35,                   /* SAMPLER  */
  YYSYMBOL_SAMPLERS = 36,                  /* SAMPLERS  */
  YYSYMBOL_RNGTOK = 37,                    /* RNGTOK  */
  YYSYMBOL_FACTORY = 38,                   /* FACTORY  */
  YYSYMBOL_FACTORIES = 39,                 /* FACTORIES  */
  YYSYMBOL_MODULES = 40,                   /* MODULES  */
  YYSYMBOL_SEED = 41,                      /* SEED  */
  YYSYMBOL_LIST = 42,                      /* LIST  */
  YYSYMBOL_STRUCTURE = 43,                 /* STRUCTURE  */
  YYSYMBOL_DIM = 44,                       /* DIM  */
  YYSYMBOL_NA = 45,                        /* NA  */
  YYSYMBOL_R_NULL = 46,                    /* R_NULL  */
  YYSYMBOL_DIMNAMES = 47,                  /* DIMNAMES  */
  YYSYMBOL_ITER = 48,                      /* ITER  */
  YYSYMBOL_ARROW = 49,                     /* ARROW  */
  YYSYMBOL_ENDDATA = 50,                   /* ENDDATA  */
  YYSYMBOL_ASINTEGER = 51,                 /* ASINTEGER  */
  YYSYMBOL_DOTDATA = 52,                   /* DOTDATA  */
  YYSYMBOL_DIRECTORY = 53,                 /* DIRECTORY  */
  YYSYMBOL_CD = 54,                        /* CD  */
  YYSYMBOL_PWD = 55,                       /* PWD  */
  YYSYMBOL_RUN = 56,                       /* RUN  */
  YYSYMBOL_ENDSCRIPT = 57,                 /* ENDSCRIPT  */
  YYSYMBOL_58_ = 58,                       /* ','  */
  YYSYMBOL_59_ = 59,                       /* '('  */
  YYSYMBOL_60_ = 60,                       /* ')'  */
  YYSYMBOL_61_ = 61,                       /* '['  */
  YYSYMBOL_62_ = 62,                       /* ']'  */
  YYSYMBOL_63_ = 63,                       /* ':'  */
  YYSYMBOL_64_ = 64,                       /* '*'  */
  YYSYMBOL_65_ = 65,                       /* ';'  */
  YYSYMBOL_66_ = 66,                       /* '`'  */
  YYSYMBOL_67_ = 67,                       /* '='  */
  YYSYMBOL_68_c_ = 68,                     /* 'c'  */
  YYSYMBOL_YYACCEPT = 69,                  /* $accept  */
  YYSYMBOL_input = 70,                     /* input  */
  YYSYMBOL_line = 71,                      /* line  */
  YYSYMBOL_command = 72,                   /* command  */
  YYSYMBOL_model = 73,                     /* model  */
  YYSYMBOL_data_in = 74,                   /* data_in  */
  YYSYMBOL_data_to = 75,                   /* data_to  */
  YYSYMBOL_data = 76,                      /* data  */
  YYSYMBOL_data_clear = 77,                /* data_clear  */
  YYSYMBOL_parameters_in = 78,             /* parameters_in  */
  YYSYMBOL_parameters_to = 79,             /* parameters_to  */
  YYSYMBOL_parameters = 80,                /* parameters  */
  YYSYMBOL_compile = 81,                   /* compile  */
  YYSYMBOL_initialize = 82,                /* initialize  */
  YYSYMBOL_autoadapt = 83,                 /* autoadapt  */
  YYSYMBOL_forceadapt = 84,                /* forceadapt  */
  YYSYMBOL_adapt = 85,                     /* adapt  */
  YYSYMBOL_update = 86,                    /* update  */
  YYSYMBOL_exit = 87,                      /* exit  */
  YYSYMBOL_var = 88,                       /* var  */
  YYSYMBOL_range_list = 89,                /* range_list  */
  YYSYMBOL_range_element = 90,             /* range_element  */
  YYSYMBOL_index = 91,                     /* index  */
  YYSYMBOL_monitor = 92,                   /* monitor  */
  YYSYMBOL_monitor_set = 93,               /* monitor_set  */
  YYSYMBOL_monitor_clear = 94,             /* monitor_clear  */
  YYSYMBOL_monitors_to = 95,               /* monitors_to  */
  YYSYMBOL_file_name = 96,                 /* file_name  */
  YYSYMBOL_coda = 97,                      /* coda  */
  YYSYMBOL_load = 98,                      /* load  */
  YYSYMBOL_unload = 99,                    /* unload  */
  YYSYMBOL_samplers_to = 100,              /* samplers_to  */
  YYSYMBOL_list_factories = 101,           /* list_factories  */
  YYSYMBOL_list_modules = 102,             /* list_modules  */
  YYSYMBOL_set_factory = 103,              /* set_factory  */
  YYSYMBOL_set_seed = 104,                 /* set_seed  */
  YYSYMBOL_r_assignment_list = 105,        /* r_assignment_list  */
  YYSYMBOL_r_assignment = 106,             /* r_assignment  */
  YYSYMBOL_r_name = 107,                   /* r_name  */
  YYSYMBOL_r_data = 108,                   /* r_data  */
  YYSYMBOL_r_structure = 109,              /* r_structure  */
  YYSYMBOL_r_attribute_list = 110,         /* r_attribute_list  */
  YYSYMBOL_r_dim = 111,                    /* r_dim  */
  YYSYMBOL_r_collection = 112,             /* r_collection  */
  YYSYMBOL_r_integer_collection = 113,     /* r_integer_collection  */
  YYSYMBOL_r_value_collection = 114,       /* r_value_collection  */
  YYSYMBOL_r_value_list = 115,             /* r_value_list  */
  YYSYMBOL_r_value = 116,                  /* r_value  */
  YYSYMBOL_r_generic_attribute = 117,      /* r_generic_attribute  */
  YYSYMBOL_r_generic_list = 118,           /* r_generic_list  */
  YYSYMBOL_r_generic_list_element = 119,   /* r_generic_list_element  */
  YYSYMBOL_r_generic_vector = 120,         /* r_generic_vector  */
  YYSYMBOL_r_numeric_vector = 121,         /* r_numeric_vector  */
  YYSYMBOL_r_double_list = 122,            /* r_double_list  */
  YYSYMBOL_r_character_vector = 123,       /* r_character_vector  */
  YYSYMBOL_r_string_list = 124,            /* r_string_list  */
  YYSYMBOL_get_working_dir = 125,          /* get_working_dir  */
  YYSYMBOL_set_working_dir = 126,          /* set_working_dir  */
  YYSYMBOL_read_dir = 127,                 /* read_dir  */
  YYSYMBOL_run_script = 128                /* run_script  */
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
typedef yytype_int16 yy_state_t;

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
         || (defined ZZSTYPE_IS_TRIVIAL && ZZSTYPE_IS_TRIVIAL)))

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   306

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  315

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


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
      59,    60,    64,     2,    58,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    65,
       2,    67,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    61,     2,    62,     2,     2,    66,     2,     2,    68,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if ZZDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   181,   181,   185,   191,   192,   193,   194,   195,   196,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   227,   239,   244,   252,
     258,   264,   276,   282,   308,   322,   325,   329,   335,   344,
     356,   360,   366,   373,   377,   382,   386,   391,   395,   400,
     404,   409,   412,   415,   421,   424,   429,   432,   438,   441,
     442,   445,   448,   451,   454,   457,   461,   465,   471,   474,
     480,   486,   498,   499,   502,   505,   508,   511,   516,   519,
     522,   529,   534,   539,   545,   551,   558,   565,   573,   581,
     584,   587,   592,   595,   600,   608,   609,   610,   615,   616,
     620,   627,   635,   636,   637,   638,   641,   644,   649,   650,
     653,   656,   660,   666,   667,   670,   671,   677,   680,   681,
     684,   685,   688,   689,   690,   691,   692,   693,   696,   697,
     700,   701,   704,   705,   708,   709,   714,   725,   733,   757
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if ZZDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "DOUBLE",
  "NAME", "STRING", "SYSCMD", "ENDCMD", "MODEL", "DATA", "IN", "TO",
  "INITS", "PARAMETERS", "COMPILE", "INITIALIZE", "ADAPT", "AUTOADAPT",
  "FORCEADAPT", "UPDATE", "BY", "MONITORS", "MONITOR", "TYPE", "SET",
  "CLEAR", "THIN", "CODA", "STEM", "EXIT", "NCHAINS", "CHAIN", "LOAD",
  "UNLOAD", "SAMPLER", "SAMPLERS", "RNGTOK", "FACTORY", "FACTORIES",
  "MODULES", "SEED", "LIST", "STRUCTURE", "DIM", "NA", "R_NULL",
  "DIMNAMES", "ITER", "ARROW", "ENDDATA", "ASINTEGER", "DOTDATA",
  "DIRECTORY", "CD", "PWD", "RUN", "ENDSCRIPT", "','", "'('", "')'", "'['",
  "']'", "':'", "'*'", "';'", "'`'", "'='", "'c'", "$accept", "input",
  "line", "command", "model", "data_in", "data_to", "data", "data_clear",
  "parameters_in", "parameters_to", "parameters", "compile", "initialize",
  "autoadapt", "forceadapt", "adapt", "update", "exit", "var",
  "range_list", "range_element", "index", "monitor", "monitor_set",
  "monitor_clear", "monitors_to", "file_name", "coda", "load", "unload",
  "samplers_to", "list_factories", "list_modules", "set_factory",
  "set_seed", "r_assignment_list", "r_assignment", "r_name", "r_data",
  "r_structure", "r_attribute_list", "r_dim", "r_collection",
  "r_integer_collection", "r_value_collection", "r_value_list", "r_value",
  "r_generic_attribute", "r_generic_list", "r_generic_list_element",
  "r_generic_vector", "r_numeric_vector", "r_double_list",
  "r_character_vector", "r_string_list", "get_working_dir",
  "set_working_dir", "read_dir", "run_script", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-206)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -206,   100,  -206,    97,   104,  -206,    -7,    77,    29,   140,
     -45,  -206,    20,    80,   121,   129,    81,     7,   -13,    15,
    -206,   158,   130,   149,   126,  -206,   158,  -206,   158,   133,
    -206,   161,  -206,  -206,  -206,    21,  -206,  -206,  -206,    21,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,   158,  -206,   158,   158,  -206,
     158,   158,   158,   139,   113,   114,   115,   116,   158,   117,
     170,   170,   118,   162,   174,   122,   123,  -206,  -206,  -206,
    -206,   158,   124,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
     178,    32,  -206,   135,    61,  -206,  -206,  -206,  -206,  -206,
     127,   120,   165,   166,   167,   168,   132,   188,   136,   137,
      75,   187,   191,  -206,   164,   169,  -206,   173,   138,  -206,
      21,  -206,     5,   141,   171,   197,   142,   143,   146,   147,
     183,  -206,   -27,  -206,   145,   182,   186,   152,   153,   155,
     156,   157,   159,   160,  -206,  -206,  -206,  -206,   163,  -206,
     172,   175,  -206,  -206,  -206,  -206,  -206,   185,   176,   177,
     212,   217,   218,   220,   179,   188,  -206,   188,   180,   181,
     219,   222,   202,   203,   158,   158,   108,    26,     4,    39,
     184,   225,  -206,   189,   190,   192,   193,   224,  -206,  -206,
     227,   228,   194,   195,   198,   199,   196,   200,   201,   204,
     205,   206,   -24,  -206,   207,    46,  -206,   229,   208,  -206,
    -206,  -206,  -206,   209,   210,   211,   214,   221,    -8,   213,
    -206,  -206,  -206,  -206,  -206,    17,    85,  -206,  -206,    39,
    -206,   215,  -206,  -206,  -206,  -206,   223,   226,   216,   230,
     231,  -206,   232,   233,    79,  -206,  -206,  -206,  -206,   239,
     241,  -206,  -206,  -206,    18,     2,    85,  -206,   234,   235,
    -206,  -206,   237,   238,  -206,   242,   243,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,    12,    12,     6,   134,
     236,    86,  -206,  -206,    89,   245,   246,  -206,  -206,    90,
     102,    18,    12,  -206,  -206,   240,  -206,   247,  -206,   253,
    -206,  -206,  -206,  -206,  -206
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     4,     0,     0,     0,     0,
      50,    52,     0,     0,     0,     0,     0,     0,     0,     0,
      61,     0,     0,     0,     0,   148,     0,   146,     0,     0,
       3,     0,    10,    11,    12,    39,    13,    14,    15,    45,
      16,    17,    19,    20,    18,    21,    27,    22,    69,    70,
      23,    24,    25,    26,    31,    32,    33,    34,    35,    29,
      30,    28,     7,     6,     9,     0,    37,     0,     0,    42,
       0,     0,     0,     0,    57,    53,    55,    59,     0,    62,
       0,     0,    73,     0,     0,    86,    84,    82,    83,    88,
      89,     0,     0,    94,   147,   149,     8,     5,   106,   105,
       0,     0,    99,     0,     0,    36,    41,    40,    49,    48,
      46,     0,     0,     0,     0,     0,    80,     0,    71,    78,
       0,     0,     0,    98,     0,     0,    90,     0,     0,    38,
       0,   100,     0,    43,     0,     0,     0,     0,     0,     0,
       0,    68,     0,    64,    66,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   107,   101,   125,   104,     0,   126,
       0,     0,   102,   103,   118,   119,   121,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,     0,     0,     0,     0,     0,    65,    67,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,     0,   123,     0,     0,    58,
      54,    56,    60,     0,     0,     0,    75,    74,     0,     0,
      87,    85,    93,    91,    92,     0,     0,   111,   120,     0,
     122,     0,    47,    81,    72,    79,     0,     0,     0,     0,
       0,   109,     0,     0,     0,   112,   113,   124,    44,     0,
       0,    97,    96,    95,     0,     0,     0,   110,     0,     0,
     138,   142,     0,     0,   137,     0,     0,   127,   132,   134,
     117,   116,   115,   114,    76,    77,     0,     0,     0,     0,
       0,     0,   128,   130,     0,     0,     0,   140,   144,     0,
       0,     0,     0,   135,   136,     0,   133,     0,   139,     0,
     143,   131,   129,   141,   145
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,    -5,
    -206,  -174,    59,  -206,  -206,  -206,  -206,   -26,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,   244,    -9,  -206,  -206,
    -206,  -206,   -19,  -184,  -206,    74,  -206,  -182,    -3,   -21,
     -30,  -205,   -14,  -206,  -206,  -206,  -206,  -206,  -206,  -206
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    82,
     142,   143,   144,    47,    48,    49,    50,    89,    51,    52,
      53,    54,    55,    56,    57,    58,   101,   102,   103,   212,
     162,   254,   255,   163,   164,   165,   215,   166,   256,   291,
     292,   293,   278,   299,   279,   300,    59,    60,    61,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      94,   198,    95,   213,    65,   141,   156,   216,   156,   156,
     270,   157,    79,    73,    86,   248,   270,   290,   271,    66,
      79,   156,   270,    74,   271,    83,    98,    99,    84,   249,
     156,   175,    80,    81,   236,   176,   237,    98,    99,   105,
      70,   106,   107,   156,   108,   109,   110,   159,   158,   159,
     159,   251,   116,   160,   272,   273,   160,   257,   274,   277,
     272,   273,   159,   275,   274,   126,    98,    99,   160,   275,
     161,   159,   161,   161,   295,   118,   119,   160,   211,    85,
     276,   281,   129,    75,   159,   161,   276,   100,    67,    68,
     252,   280,   131,    78,   161,   131,   311,   130,   100,   147,
       2,     3,   148,    69,   239,    63,   240,     4,     5,     6,
       7,   133,    64,     8,     9,    10,    11,    12,    13,    14,
      15,   155,    16,    17,    76,    18,   130,   100,    19,   253,
      20,   208,    77,    21,    22,    90,    23,   266,   297,   267,
     298,    96,    24,   209,   302,   210,   303,   302,   307,   304,
     308,    71,    72,    25,    26,    27,    28,    29,   206,   207,
     309,    91,   310,    87,    88,    92,    93,   121,   122,    97,
     111,   112,   113,   114,   115,    79,   120,   123,   117,   135,
     124,   125,   127,   128,   132,   134,   136,   137,   138,   139,
     140,   141,   149,   151,   145,   146,   150,   153,   152,   167,
     169,   170,   171,   168,   154,   172,   173,   174,   177,   178,
     179,   180,   181,   182,   183,   193,   184,   190,   185,   186,
     194,   195,   187,   196,   202,   203,   204,   205,   218,   223,
     224,   188,   241,   225,   189,   191,   199,   192,   197,   200,
     201,   246,   268,   217,   297,   247,   269,   282,   250,   219,
     220,   313,   221,   222,   226,   227,   230,   228,   229,   314,
     231,   232,   214,   283,   233,   234,   294,   238,   242,   243,
     244,   245,   312,   235,   296,   258,   261,     0,     0,     0,
       0,     0,   259,   104,     0,   260,     0,     0,     0,     0,
     262,   263,     0,     0,   284,   285,   286,   287,     0,   264,
     265,   288,   289,   301,   305,     0,   306
};

static const yytype_int16 yycheck[] =
{
      26,   175,    28,   187,    11,     3,     4,   189,     4,     4,
       4,     6,     5,    58,    19,    23,     4,     5,     6,    26,
       5,     4,     4,     3,     6,    38,     5,     6,    41,    37,
       4,    58,    25,    26,    58,    62,    60,     5,     6,    65,
      11,    67,    68,     4,    70,    71,    72,    45,    43,    45,
      45,   235,    78,    51,    42,    43,    51,   239,    46,   264,
      42,    43,    45,    51,    46,    91,     5,     6,    51,    51,
      68,    45,    68,    68,    68,    80,    81,    51,    52,    64,
      68,   265,    50,     3,    45,    68,    68,    66,    11,    12,
       5,   265,   101,    12,    68,   104,   301,    65,    66,    24,
       0,     1,    27,    26,    58,     8,    60,     7,     8,     9,
      10,    50,     8,    13,    14,    15,    16,    17,    18,    19,
      20,   130,    22,    23,     3,    25,    65,    66,    28,    44,
      30,    23,     3,    33,    34,     5,    36,    58,     4,    60,
       6,     8,    42,    35,    58,    37,    60,    58,    58,    60,
      60,    11,    12,    53,    54,    55,    56,    57,   184,   185,
      58,    12,    60,     5,     6,    39,    40,     5,     6,     8,
      31,    58,    58,    58,    58,     5,    58,     3,    61,    59,
      58,    58,    58,     5,    49,    58,    21,    21,    21,    21,
      58,     3,     5,    29,    58,    58,     5,    24,    29,    58,
       3,    59,    59,    32,    66,    59,    59,    24,    63,    27,
      24,    59,    59,    58,    58,     3,    59,    32,    59,    59,
       3,     3,    59,     3,     5,     3,    24,    24,     3,     5,
       3,    59,     3,     5,    59,    59,   177,    60,    59,    59,
      59,    27,     3,    59,     4,    24,     5,   266,    35,    60,
      60,     4,    60,    60,    60,    60,    60,    59,    59,     6,
      60,    60,   188,   266,    60,    60,   287,    60,    60,    60,
      60,    60,   302,    67,   288,    60,    60,    -1,    -1,    -1,
      -1,    -1,    59,    39,    -1,    59,    -1,    -1,    -1,    -1,
      60,    60,    -1,    -1,    60,    60,    59,    59,    -1,    67,
      67,    59,    59,    67,    59,    -1,    60
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    70,     0,     1,     7,     8,     9,    10,    13,    14,
      15,    16,    17,    18,    19,    20,    22,    23,    25,    28,
      30,    33,    34,    36,    42,    53,    54,    55,    56,    57,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    92,    93,    94,
      95,    97,    98,    99,   100,   101,   102,   103,   104,   125,
     126,   127,   128,     8,     8,    11,    26,    11,    12,    26,
      11,    11,    12,    58,     3,     3,     3,     3,    12,     5,
      25,    26,    88,    38,    41,    64,    88,     5,     6,    96,
       5,    12,    39,    40,    96,    96,     8,     8,     5,     6,
      66,   105,   106,   107,   105,    96,    96,    96,    96,    96,
      96,    31,    58,    58,    58,    58,    96,    61,    88,    88,
      58,     5,     6,     3,    58,    58,    96,    58,     5,    50,
      65,   106,    49,    50,    58,    59,    21,    21,    21,    21,
      58,     3,    89,    90,    91,    58,    58,    24,    27,     5,
       5,    29,    29,    24,    66,   106,     4,     6,    43,    45,
      51,    68,   109,   112,   113,   114,   116,    58,    32,     3,
      59,    59,    59,    59,    24,    58,    62,    63,    27,    24,
      59,    59,    58,    58,    59,    59,    59,    59,    59,    59,
      32,    59,    60,     3,     3,     3,     3,    59,    90,    91,
      59,    59,     5,     3,    24,    24,    96,    96,    23,    35,
      37,    52,   108,   112,   114,   115,   116,    59,     3,    60,
      60,    60,    60,     5,     3,     5,    60,    60,    59,    59,
      60,    60,    60,    60,    60,    67,    58,    60,    60,    58,
      60,     3,    60,    60,    60,    60,    27,    24,    23,    37,
      35,   112,     5,    44,   110,   111,   117,   116,    60,    59,
      59,    60,    60,    60,    67,    67,    58,    60,     3,     5,
       4,     6,    42,    43,    46,    51,    68,   120,   121,   123,
      90,   112,   111,   117,    60,    60,    59,    59,    59,    59,
       5,   118,   119,   120,   118,    68,   121,     4,     6,   122,
     124,    67,    58,    60,    60,    59,    60,    58,    60,    58,
      60,   120,   119,     4,     6
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    73,    73,    74,    74,
      75,    76,    77,    78,    78,    78,    79,    79,    80,    80,
      81,    81,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    88,    88,    89,    89,    90,    90,    91,    92,
      92,    93,    93,    93,    93,    93,    93,    93,    94,    94,
      95,    95,    96,    96,    97,    97,    97,    97,    98,    99,
     100,   101,   101,   101,   102,   103,   103,   103,   104,   105,
     105,   105,   106,   106,   106,   107,   107,   107,   108,   108,
     109,   109,   110,   110,   110,   110,   111,   111,   112,   112,
     113,   114,   114,   115,   115,   116,   116,   117,   118,   118,
     119,   119,   120,   120,   120,   120,   120,   120,   121,   121,
     122,   122,   123,   123,   124,   124,   125,   126,   127,   128
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     2,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     3,     1,
       3,     3,     2,     3,     8,     1,     3,     8,     3,     3,
       1,     6,     1,     2,     7,     2,     7,     2,     7,     2,
       7,     1,     1,     4,     1,     3,     1,     3,     1,     1,
       1,     3,     8,     2,     7,     7,    11,    11,     3,     8,
       3,     8,     1,     1,     2,     7,     2,     7,     2,     2,
       3,     7,     7,     7,     2,     9,     9,     9,     3,     1,
       2,     3,     3,     3,     3,     1,     1,     3,     1,     3,
       6,     4,     1,     1,     3,     3,     3,     3,     1,     1,
       4,     1,     4,     1,     3,     1,     1,     3,     1,     3,
       1,     3,     1,     4,     1,     4,     4,     1,     1,     4,
       1,     3,     1,     4,     1,     3,     1,     2,     1,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = ZZEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == ZZEMPTY)                                        \
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
   Use ZZerror or ZZUNDEF. */
#define YYERRCODE ZZUNDEF


/* Enable debugging if requested.  */
#if ZZDEBUG

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
#else /* !ZZDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !ZZDEBUG */


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

  yychar = ZZEMPTY; /* Cause a token to be read.  */

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
  if (yychar == ZZEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= ZZEOF)
    {
      yychar = ZZEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == ZZerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = ZZUNDEF;
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
  yychar = ZZEMPTY;
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
  case 2: /* input: %empty  */
#line 181 "../../../../jags-4-3_patched/src/terminal/parser.yy"
       {
    if (interactive && command_buffer_count == 0) 
	std::cout << ". " << std::flush;
}
#line 1687 "parser.cc"
    break;

  case 3: /* input: input line  */
#line 185 "../../../../jags-4-3_patched/src/terminal/parser.yy"
             {
    if (interactive && command_buffer_count == 0) 
	std::cout << ". " << std::flush;
}
#line 1696 "parser.cc"
    break;

  case 4: /* line: ENDCMD  */
#line 191 "../../../../jags-4-3_patched/src/terminal/parser.yy"
             {}
#line 1702 "parser.cc"
    break;

  case 5: /* line: command ENDCMD  */
#line 192 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                 {}
#line 1708 "parser.cc"
    break;

  case 6: /* line: error ENDCMD  */
#line 193 "../../../../jags-4-3_patched/src/terminal/parser.yy"
               {if(interactive) yyerrok; else exit(1); }
#line 1714 "parser.cc"
    break;

  case 7: /* line: run_script  */
#line 194 "../../../../jags-4-3_patched/src/terminal/parser.yy"
             {}
#line 1720 "parser.cc"
    break;

  case 8: /* line: ENDSCRIPT ENDCMD  */
#line 195 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                   {}
#line 1726 "parser.cc"
    break;

  case 9: /* line: SYSCMD ENDCMD  */
#line 196 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                { doSystem((yyvsp[-1].stringptr)); delete (yyvsp[-1].stringptr);}
#line 1732 "parser.cc"
    break;

  case 36: /* model: MODEL IN file_name  */
#line 227 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                          {
    std::FILE *file = std::fopen(ExpandFileName(((yyvsp[0].stringptr))->c_str()).c_str(), "r");
    if (!file) {
	std::cerr << "Failed to open file " << *((yyvsp[0].stringptr)) << std::endl;
	if (!interactive) exit(1);
    }
    else {
	Jtry(console->checkModel(file));
	std::fclose(file);
    }
    delete (yyvsp[0].stringptr);
 }
#line 1749 "parser.cc"
    break;

  case 37: /* model: MODEL CLEAR  */
#line 239 "../../../../jags-4-3_patched/src/terminal/parser.yy"
              {
    console->clearModel();
 }
#line 1757 "parser.cc"
    break;

  case 38: /* data_in: data r_assignment_list ENDDATA  */
#line 244 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                        {
    std::string rngname;
    readRData((yyvsp[-1].pvec), _data_table, rngname);
    if (rngname.size() != 0) {
	std::cerr << "WARNING: .RNG.name assignment ignored" << std::endl;
    }
    delete_pvec((yyvsp[-1].pvec));
 }
#line 1770 "parser.cc"
    break;

  case 39: /* data_in: data  */
#line 252 "../../../../jags-4-3_patched/src/terminal/parser.yy"
       {
    // Failed to open the data file 
    if (!interactive) exit(1);
  }
#line 1779 "parser.cc"
    break;

  case 40: /* data_to: DATA TO file_name  */
#line 258 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                           {
    doDump(*(yyvsp[0].stringptr), jags::DUMP_DATA, 1);
    delete (yyvsp[0].stringptr);
}
#line 1788 "parser.cc"
    break;

  case 41: /* data: DATA IN file_name  */
#line 264 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                        {
    if(open_data_buffer((yyvsp[0].stringptr))) {
	std::cout << "Reading data file " << *(yyvsp[0].stringptr) << std::endl;
    }
    else {
	std::cerr << "Unable to open file " << *(yyvsp[0].stringptr) << std::endl << std::flush;
	if (!interactive) exit(1);
    }
    delete (yyvsp[0].stringptr);
 }
#line 1803 "parser.cc"
    break;

  case 42: /* data_clear: DATA CLEAR  */
#line 276 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                       {
    std::cout << "Clearing data table " << std::endl;
    _data_table.clear();
}
#line 1812 "parser.cc"
    break;

  case 43: /* parameters_in: parameters r_assignment_list ENDDATA  */
#line 283 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    std::map<std::string, jags::SArray> parameter_table;
    std::string rngname;
    readRData((yyvsp[-1].pvec), parameter_table, rngname);
    delete_pvec((yyvsp[-1].pvec));
    /* Set all chains to the same state. If the user sets the
       RNG state in addition to the parameter values then all
       chains will be identical!
    */
    if (console->model() == 0) {
	std::cout << "ERROR: Initial values ignored. "
		  <<  "(You must compile the model first)" << std::endl;
	if (!interactive) exit(1);
    }
    for (unsigned int i = 1; i <= console->nchain(); ++i) {
	/* We have to set the name first, because the state or seed
	   might be embedded in the parameter_table */
	if (rngname.size() != 0) {
	    Jtry(console->setRNGname(rngname, i));
	}
	Jtry(console->setParameters(parameter_table, i));
    }
    print_unused_variables(parameter_table, false);

}
#line 1842 "parser.cc"
    break;

  case 44: /* parameters_in: parameters r_assignment_list ENDDATA ',' CHAIN '(' INT ')'  */
#line 309 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    std::map<std::string, jags::SArray> parameter_table;
    std::string rngname;
    readRData((yyvsp[-6].pvec), parameter_table, rngname);
    delete (yyvsp[-6].pvec);
    /* We have to set the name first, because the state or seed
       might be embedded in the parameter_table */
    if (rngname.size() != 0) {
        Jtry(console->setRNGname(rngname, (yyvsp[-1].intval)));
    }
    Jtry(console->setParameters(parameter_table, (yyvsp[-1].intval)));
    print_unused_variables(parameter_table, false);
}
#line 1860 "parser.cc"
    break;

  case 45: /* parameters_in: parameters  */
#line 322 "../../../../jags-4-3_patched/src/terminal/parser.yy"
             {}
#line 1866 "parser.cc"
    break;

  case 46: /* parameters_to: PARAMETERS TO file_name  */
#line 325 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                       {
    doDump(*(yyvsp[0].stringptr), jags::DUMP_PARAMETERS, 1);
    delete (yyvsp[0].stringptr);
}
#line 1875 "parser.cc"
    break;

  case 47: /* parameters_to: PARAMETERS TO file_name ',' CHAIN '(' INT ')'  */
#line 329 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                                {
    doDump(*(yyvsp[-5].stringptr), jags::DUMP_PARAMETERS, (yyvsp[-1].intval));
    delete (yyvsp[-5].stringptr);
}
#line 1884 "parser.cc"
    break;

  case 48: /* parameters: PARAMETERS IN file_name  */
#line 335 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                    {
  if(open_data_buffer((yyvsp[0].stringptr))) {
    std::cout << "Reading parameter file " << *(yyvsp[0].stringptr) << std::endl;
  }
  else {
    std::cerr << "Unable to open file " << *(yyvsp[0].stringptr) << std::endl << std::flush;
  }
  delete (yyvsp[0].stringptr);
}
#line 1898 "parser.cc"
    break;

  case 49: /* parameters: INITS IN file_name  */
#line 344 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                     {
  /* Legacy option to not break existing scripts */
  if(open_data_buffer((yyvsp[0].stringptr))) {
    std::cout << "Reading initial values file " << *(yyvsp[0].stringptr) << std::endl;
  }
  else {
    std::cerr << "Unable to open file " << *(yyvsp[0].stringptr) << std::endl << std::flush;
  }
  delete (yyvsp[0].stringptr);
}
#line 1913 "parser.cc"
    break;

  case 50: /* compile: COMPILE  */
#line 356 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                 {
    Jtry(console->compile(_data_table, 1, true));
    print_unused_variables(_data_table, true);
 }
#line 1922 "parser.cc"
    break;

  case 51: /* compile: COMPILE ',' NCHAINS '(' INT ')'  */
#line 360 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                  {
    Jtry(console->compile(_data_table, (yyvsp[-1].intval), true));
    print_unused_variables(_data_table, true);
}
#line 1931 "parser.cc"
    break;

  case 52: /* initialize: INITIALIZE  */
#line 366 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                       {
    if (!console->initialize()) {
	errordump();
    }
}
#line 1941 "parser.cc"
    break;

  case 53: /* autoadapt: AUTOADAPT INT  */
#line 373 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                         {
    long refresh = interactive ? (yyvsp[0].intval)/50 : 0;
    autoadaptstar((yyvsp[0].intval), refresh, 50);
}
#line 1950 "parser.cc"
    break;

  case 54: /* autoadapt: AUTOADAPT INT ',' BY '(' INT ')'  */
#line 377 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                   {
    autoadaptstar((yyvsp[-5].intval),(yyvsp[-1].intval), 50);
}
#line 1958 "parser.cc"
    break;

  case 55: /* forceadapt: FORCEADAPT INT  */
#line 382 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                           {
    long refresh = interactive ? (yyvsp[0].intval)/50 : 0;
    adaptstar((yyvsp[0].intval), refresh, 50, true);
}
#line 1967 "parser.cc"
    break;

  case 56: /* forceadapt: FORCEADAPT INT ',' BY '(' INT ')'  */
#line 386 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                    {
    adaptstar((yyvsp[-5].intval),(yyvsp[-1].intval), 50, true);
}
#line 1975 "parser.cc"
    break;

  case 57: /* adapt: ADAPT INT  */
#line 391 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                 {
    long refresh = interactive ? (yyvsp[0].intval)/50 : 0;
    adaptstar((yyvsp[0].intval), refresh, 50, false);
}
#line 1984 "parser.cc"
    break;

  case 58: /* adapt: ADAPT INT ',' BY '(' INT ')'  */
#line 395 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                               {
    adaptstar((yyvsp[-5].intval),(yyvsp[-1].intval), 50, false);
}
#line 1992 "parser.cc"
    break;

  case 59: /* update: UPDATE INT  */
#line 400 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                   {
    long refresh = interactive ? (yyvsp[0].intval)/50 : 0;
    updatestar((yyvsp[0].intval), refresh, 50);
}
#line 2001 "parser.cc"
    break;

  case 60: /* update: UPDATE INT ',' BY '(' INT ')'  */
#line 404 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                {
  updatestar((yyvsp[-5].intval),(yyvsp[-1].intval), 50);
}
#line 2009 "parser.cc"
    break;

  case 61: /* exit: EXIT  */
#line 409 "../../../../jags-4-3_patched/src/terminal/parser.yy"
           { return 0; }
#line 2015 "parser.cc"
    break;

  case 62: /* var: NAME  */
#line 412 "../../../../jags-4-3_patched/src/terminal/parser.yy"
          {
  (yyval.ptree) = new jags::ParseTree(jags::P_VAR); setName((yyval.ptree), (yyvsp[0].stringptr));
}
#line 2023 "parser.cc"
    break;

  case 63: /* var: NAME '[' range_list ']'  */
#line 415 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                          {
  (yyval.ptree) = new jags::ParseTree(jags::P_VAR); setName((yyval.ptree), (yyvsp[-3].stringptr));
  setParameters((yyval.ptree), (yyvsp[-1].pvec));
}
#line 2032 "parser.cc"
    break;

  case 64: /* range_list: range_element  */
#line 421 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                          {
  (yyval.pvec) = new std::vector<jags::ParseTree*>(1, (yyvsp[0].ptree)); 
}
#line 2040 "parser.cc"
    break;

  case 65: /* range_list: range_list ',' range_element  */
#line 424 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                               {
  (yyval.pvec)=(yyvsp[-2].pvec); (yyval.pvec)->push_back((yyvsp[0].ptree));
}
#line 2048 "parser.cc"
    break;

  case 66: /* range_element: index  */
#line 429 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                     {
  (yyval.ptree) = new jags::ParseTree(jags::P_RANGE); setParameters((yyval.ptree), (yyvsp[0].ptree));
}
#line 2056 "parser.cc"
    break;

  case 67: /* range_element: index ':' index  */
#line 432 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                  {
  (yyval.ptree) = new jags::ParseTree(jags::P_RANGE); setParameters((yyval.ptree), (yyvsp[-2].ptree), (yyvsp[0].ptree));
}
#line 2064 "parser.cc"
    break;

  case 68: /* index: INT  */
#line 438 "../../../../jags-4-3_patched/src/terminal/parser.yy"
           {(yyval.ptree) = new jags::ParseTree(jags::P_VALUE); (yyval.ptree)->setValue((yyvsp[0].intval));}
#line 2070 "parser.cc"
    break;

  case 71: /* monitor_set: MONITOR SET var  */
#line 445 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                              { 
    setMonitor((yyvsp[0].ptree), 1, "trace"); delete (yyvsp[0].ptree);
}
#line 2078 "parser.cc"
    break;

  case 72: /* monitor_set: MONITOR SET var ',' THIN '(' INT ')'  */
#line 448 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                       { 
    setMonitor((yyvsp[-5].ptree), (yyvsp[-1].intval), "trace"); delete (yyvsp[-5].ptree);
}
#line 2086 "parser.cc"
    break;

  case 73: /* monitor_set: MONITOR var  */
#line 451 "../../../../jags-4-3_patched/src/terminal/parser.yy"
              {
    setMonitor((yyvsp[0].ptree), 1, "trace"); delete (yyvsp[0].ptree);
}
#line 2094 "parser.cc"
    break;

  case 74: /* monitor_set: MONITOR var ',' THIN '(' INT ')'  */
#line 454 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                   { 
    setMonitor((yyvsp[-5].ptree), (yyvsp[-1].intval), "trace"); delete (yyvsp[-5].ptree);
}
#line 2102 "parser.cc"
    break;

  case 75: /* monitor_set: MONITOR var ',' TYPE '(' NAME ')'  */
#line 457 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                    {
    setMonitor((yyvsp[-5].ptree), 1, *(yyvsp[-1].stringptr));
    delete (yyvsp[-1].stringptr);
}
#line 2111 "parser.cc"
    break;

  case 76: /* monitor_set: MONITOR var ',' TYPE '(' NAME ')' THIN '(' INT ')'  */
#line 461 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                                     {
    setMonitor((yyvsp[-9].ptree), (yyvsp[-1].intval), *(yyvsp[-5].stringptr)); 
    delete (yyvsp[-5].stringptr);
}
#line 2120 "parser.cc"
    break;

  case 77: /* monitor_set: MONITOR var ',' THIN '(' INT ')' TYPE '(' NAME ')'  */
#line 465 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                                     {
    setMonitor((yyvsp[-9].ptree), (yyvsp[-5].intval), *(yyvsp[-1].stringptr)); 
    delete (yyvsp[-1].stringptr);
}
#line 2129 "parser.cc"
    break;

  case 78: /* monitor_clear: MONITOR CLEAR var  */
#line 471 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                 {
    clearMonitor((yyvsp[0].ptree), "trace"); delete (yyvsp[0].ptree);
}
#line 2137 "parser.cc"
    break;

  case 79: /* monitor_clear: MONITOR CLEAR var ',' TYPE '(' NAME ')'  */
#line 474 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                          {
    clearMonitor((yyvsp[-5].ptree), *(yyvsp[-1].stringptr));
    delete (yyvsp[-1].stringptr);
}
#line 2146 "parser.cc"
    break;

  case 80: /* monitors_to: MONITORS TO file_name  */
#line 481 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    dumpMonitors(*(yyvsp[0].stringptr), "trace");
    delete (yyvsp[0].stringptr);
}
#line 2155 "parser.cc"
    break;

  case 81: /* monitors_to: MONITORS TO file_name ',' TYPE '(' NAME ')'  */
#line 486 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                            {
    dumpMonitors(*(yyvsp[-5].stringptr), *(yyvsp[-1].stringptr));
    delete (yyvsp[-5].stringptr);
    delete (yyvsp[-1].stringptr); 
}
#line 2165 "parser.cc"
    break;

  case 82: /* file_name: NAME  */
#line 498 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                { (yyval.stringptr) = (yyvsp[0].stringptr);}
#line 2171 "parser.cc"
    break;

  case 83: /* file_name: STRING  */
#line 499 "../../../../jags-4-3_patched/src/terminal/parser.yy"
         { (yyval.stringptr) = (yyvsp[0].stringptr); }
#line 2177 "parser.cc"
    break;

  case 84: /* coda: CODA var  */
#line 502 "../../../../jags-4-3_patched/src/terminal/parser.yy"
               {
  doCoda ((yyvsp[0].ptree), "CODA"); delete (yyvsp[0].ptree);
}
#line 2185 "parser.cc"
    break;

  case 85: /* coda: CODA var ',' STEM '(' file_name ')'  */
#line 505 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                      {
  doCoda ((yyvsp[-5].ptree), *(yyvsp[-1].stringptr)); delete (yyvsp[-5].ptree); delete (yyvsp[-1].stringptr);
}
#line 2193 "parser.cc"
    break;

  case 86: /* coda: CODA '*'  */
#line 508 "../../../../jags-4-3_patched/src/terminal/parser.yy"
           {
  doAllCoda ("CODA"); 
}
#line 2201 "parser.cc"
    break;

  case 87: /* coda: CODA '*' ',' STEM '(' file_name ')'  */
#line 511 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                      {
  doAllCoda (*(yyvsp[-1].stringptr)); delete (yyvsp[-1].stringptr); 
}
#line 2209 "parser.cc"
    break;

  case 88: /* load: LOAD file_name  */
#line 516 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                     { loadModule(*(yyvsp[0].stringptr)); }
#line 2215 "parser.cc"
    break;

  case 89: /* unload: UNLOAD NAME  */
#line 519 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                    { unloadModule(*(yyvsp[0].stringptr)); }
#line 2221 "parser.cc"
    break;

  case 90: /* samplers_to: SAMPLERS TO file_name  */
#line 523 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    dumpSamplers(*(yyvsp[0].stringptr));
    delete (yyvsp[0].stringptr);
}
#line 2230 "parser.cc"
    break;

  case 91: /* list_factories: LIST FACTORIES ',' TYPE '(' SAMPLER ')'  */
#line 530 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    listFactories(jags::SAMPLER_FACTORY);
}
#line 2238 "parser.cc"
    break;

  case 92: /* list_factories: LIST FACTORIES ',' TYPE '(' RNGTOK ')'  */
#line 535 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    listFactories(jags::RNG_FACTORY);
}
#line 2246 "parser.cc"
    break;

  case 93: /* list_factories: LIST FACTORIES ',' TYPE '(' MONITOR ')'  */
#line 540 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    listFactories(jags::MONITOR_FACTORY);
}
#line 2254 "parser.cc"
    break;

  case 94: /* list_modules: LIST MODULES  */
#line 546 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    listModules();
}
#line 2262 "parser.cc"
    break;

  case 95: /* set_factory: SET FACTORY STRING NAME ',' TYPE '(' SAMPLER ')'  */
#line 552 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    setFactory(*(yyvsp[-6].stringptr), jags::SAMPLER_FACTORY, *(yyvsp[-5].stringptr));
    delete (yyvsp[-6].stringptr);
    delete (yyvsp[-5].stringptr);
}
#line 2272 "parser.cc"
    break;

  case 96: /* set_factory: SET FACTORY NAME NAME ',' TYPE '(' RNGTOK ')'  */
#line 559 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    setFactory(*(yyvsp[-6].stringptr), jags::RNG_FACTORY, *(yyvsp[-5].stringptr));
    delete (yyvsp[-6].stringptr);
    delete (yyvsp[-5].stringptr);
}
#line 2282 "parser.cc"
    break;

  case 97: /* set_factory: SET FACTORY NAME NAME ',' TYPE '(' MONITOR ')'  */
#line 566 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    setFactory(*(yyvsp[-6].stringptr), jags::MONITOR_FACTORY, *(yyvsp[-5].stringptr));
    delete (yyvsp[-6].stringptr);
    delete (yyvsp[-5].stringptr);
}
#line 2292 "parser.cc"
    break;

  case 98: /* set_seed: SET SEED INT  */
#line 574 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    setSeed((yyvsp[0].intval));
}
#line 2300 "parser.cc"
    break;

  case 99: /* r_assignment_list: r_assignment  */
#line 581 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                {
  (yyval.pvec) = new std::vector<jags::ParseTree*>(1, (yyvsp[0].ptree));
}
#line 2308 "parser.cc"
    break;

  case 100: /* r_assignment_list: r_assignment_list r_assignment  */
#line 584 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                 {
  (yyval.pvec) = (yyvsp[-1].pvec); (yyval.pvec)->push_back((yyvsp[0].ptree));
}
#line 2316 "parser.cc"
    break;

  case 101: /* r_assignment_list: r_assignment_list ';' r_assignment  */
#line 587 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                     {
  (yyval.pvec) = (yyvsp[-2].pvec); (yyval.pvec)->push_back((yyvsp[0].ptree));
}
#line 2324 "parser.cc"
    break;

  case 102: /* r_assignment: r_name ARROW r_structure  */
#line 592 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                       {
  (yyval.ptree) = (yyvsp[0].ptree); setName((yyval.ptree), (yyvsp[-2].stringptr));
}
#line 2332 "parser.cc"
    break;

  case 103: /* r_assignment: r_name ARROW r_collection  */
#line 595 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                            {
  (yyval.ptree) = new jags::ParseTree(jags::P_ARRAY);
  setName((yyval.ptree), (yyvsp[-2].stringptr));
  setParameters((yyval.ptree), (yyvsp[0].ptree));
}
#line 2342 "parser.cc"
    break;

  case 104: /* r_assignment: r_name ARROW STRING  */
#line 600 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                      {
  /* Allow this for setting the NAME of the random number generator */
  (yyval.ptree) = new jags::ParseTree(jags::P_VAR); setName((yyval.ptree), (yyvsp[-2].stringptr));
  jags::ParseTree *p = new jags::ParseTree(jags::P_VAR); setName(p, (yyvsp[0].stringptr));
  setParameters((yyval.ptree), p);
}
#line 2353 "parser.cc"
    break;

  case 107: /* r_name: '`' NAME '`'  */
#line 610 "../../../../jags-4-3_patched/src/terminal/parser.yy"
               {
    /* R >= 2.4.0 uses backticks for quoted names */
    (yyval.stringptr) = (yyvsp[-1].stringptr);
}
#line 2362 "parser.cc"
    break;

  case 109: /* r_data: DOTDATA '=' r_collection  */
#line 616 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                           {
    (yyval.ptree) = (yyvsp[0].ptree);
}
#line 2370 "parser.cc"
    break;

  case 110: /* r_structure: STRUCTURE '(' r_data ',' r_attribute_list ')'  */
#line 620 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                                           {
  (yyval.ptree) = new jags::ParseTree(jags::P_ARRAY); 
  if ((yyvsp[-1].ptree)) 
    setParameters((yyval.ptree), (yyvsp[-3].ptree), (yyvsp[-1].ptree));
  else
    setParameters((yyval.ptree), (yyvsp[-3].ptree));
}
#line 2382 "parser.cc"
    break;

  case 111: /* r_structure: STRUCTURE '(' r_data ')'  */
#line 627 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                           {
    (yyval.ptree) = new jags::ParseTree(jags::P_ARRAY);
    setParameters((yyval.ptree), (yyvsp[-1].ptree));
}
#line 2391 "parser.cc"
    break;

  case 113: /* r_attribute_list: r_generic_attribute  */
#line 636 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                      {(yyval.ptree)=0;}
#line 2397 "parser.cc"
    break;

  case 115: /* r_attribute_list: r_attribute_list ',' r_dim  */
#line 638 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                             {(yyval.ptree)=(yyvsp[0].ptree);}
#line 2403 "parser.cc"
    break;

  case 116: /* r_dim: DIM '=' r_collection  */
#line 641 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                            {
  (yyval.ptree) = (yyvsp[0].ptree);
}
#line 2411 "parser.cc"
    break;

  case 117: /* r_dim: DIM '=' range_element  */
#line 644 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                        {
  (yyval.ptree) = (yyvsp[0].ptree);
}
#line 2419 "parser.cc"
    break;

  case 120: /* r_integer_collection: ASINTEGER '(' r_value_collection ')'  */
#line 653 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                                           {(yyval.ptree) = (yyvsp[-1].ptree);}
#line 2425 "parser.cc"
    break;

  case 121: /* r_value_collection: r_value  */
#line 656 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                            { 
  (yyval.ptree) = new jags::ParseTree(jags::P_VECTOR); 
  setParameters((yyval.ptree), (yyvsp[0].ptree));
}
#line 2434 "parser.cc"
    break;

  case 122: /* r_value_collection: 'c' '(' r_value_list ')'  */
#line 660 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                           {
  (yyval.ptree) = new jags::ParseTree(jags::P_VECTOR);
  setParameters((yyval.ptree), (yyvsp[-1].pvec));
}
#line 2443 "parser.cc"
    break;

  case 123: /* r_value_list: r_value  */
#line 666 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                      {(yyval.pvec) = new std::vector<jags::ParseTree*>(1, (yyvsp[0].ptree)); }
#line 2449 "parser.cc"
    break;

  case 124: /* r_value_list: r_value_list ',' r_value  */
#line 667 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                           {(yyval.pvec) = (yyvsp[-2].pvec); (yyval.pvec)->push_back((yyvsp[0].ptree));}
#line 2455 "parser.cc"
    break;

  case 125: /* r_value: DOUBLE  */
#line 670 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                {(yyval.ptree) = new jags::ParseTree(jags::P_VALUE); (yyval.ptree)->setValue((yyvsp[0].val));}
#line 2461 "parser.cc"
    break;

  case 126: /* r_value: NA  */
#line 671 "../../../../jags-4-3_patched/src/terminal/parser.yy"
     {(yyval.ptree) = new jags::ParseTree(jags::P_VALUE); (yyval.ptree)->setValue(JAGS_NA);}
#line 2467 "parser.cc"
    break;

  case 127: /* r_generic_attribute: NAME '=' r_generic_vector  */
#line 677 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                               {;}
#line 2473 "parser.cc"
    break;

  case 128: /* r_generic_list: r_generic_list_element  */
#line 680 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                       {;}
#line 2479 "parser.cc"
    break;

  case 129: /* r_generic_list: r_generic_list ',' r_generic_list_element  */
#line 681 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                            {;}
#line 2485 "parser.cc"
    break;

  case 130: /* r_generic_list_element: r_generic_vector  */
#line 684 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                         {;}
#line 2491 "parser.cc"
    break;

  case 131: /* r_generic_list_element: NAME '=' r_generic_vector  */
#line 685 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                            {;}
#line 2497 "parser.cc"
    break;

  case 132: /* r_generic_vector: r_numeric_vector  */
#line 688 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                   {;}
#line 2503 "parser.cc"
    break;

  case 133: /* r_generic_vector: ASINTEGER '(' r_numeric_vector ')'  */
#line 689 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                     {;}
#line 2509 "parser.cc"
    break;

  case 134: /* r_generic_vector: r_character_vector  */
#line 690 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                     {;}
#line 2515 "parser.cc"
    break;

  case 135: /* r_generic_vector: LIST '(' r_generic_list ')'  */
#line 691 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                              {;}
#line 2521 "parser.cc"
    break;

  case 136: /* r_generic_vector: STRUCTURE '(' r_generic_list ')'  */
#line 692 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                                   {;}
#line 2527 "parser.cc"
    break;

  case 137: /* r_generic_vector: R_NULL  */
#line 693 "../../../../jags-4-3_patched/src/terminal/parser.yy"
         {;}
#line 2533 "parser.cc"
    break;

  case 138: /* r_numeric_vector: DOUBLE  */
#line 696 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                         {;}
#line 2539 "parser.cc"
    break;

  case 140: /* r_double_list: DOUBLE  */
#line 700 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                      {;}
#line 2545 "parser.cc"
    break;

  case 141: /* r_double_list: r_double_list ',' DOUBLE  */
#line 701 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                           {;}
#line 2551 "parser.cc"
    break;

  case 142: /* r_character_vector: STRING  */
#line 704 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                           {;}
#line 2557 "parser.cc"
    break;

  case 143: /* r_character_vector: 'c' '(' r_string_list ')'  */
#line 705 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                            {;}
#line 2563 "parser.cc"
    break;

  case 144: /* r_string_list: STRING  */
#line 708 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                      {;}
#line 2569 "parser.cc"
    break;

  case 145: /* r_string_list: r_string_list ',' STRING  */
#line 709 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                           {;}
#line 2575 "parser.cc"
    break;

  case 146: /* get_working_dir: PWD  */
#line 715 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    std::string name;
    if (getWorkingDirectory(name)) {
	std::cout << name << std::endl;
    }
    else {
	std::cout << "ERROR: " << name << std::endl;
    }
}
#line 2589 "parser.cc"
    break;

  case 147: /* set_working_dir: CD file_name  */
#line 726 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    if (chdir(((yyvsp[0].stringptr))->c_str()) == -1) {
	std::cout << "ERROR: Cannot change working directory" << std::endl;
    }
    delete (yyvsp[0].stringptr);
}
#line 2600 "parser.cc"
    break;

  case 148: /* read_dir: DIRECTORY  */
#line 734 "../../../../jags-4-3_patched/src/terminal/parser.yy"
{
    std::string name;
    if (!getWorkingDirectory(name)) {
	std::cerr << "ERROR: Unable to get working directory name\n"
		  << name << std::endl;
	return 0;
    }
	
    DIR *dir;
    struct dirent *de;
    if ((dir = opendir(name.c_str())) != 0) {
	while ((de = readdir(dir)) != 0) {
	    if (std::strcmp(de->d_name, ".") && std::strcmp(de->d_name, "..")) {
		std::cout << de->d_name << "\n";
	    }
	}
	closedir(dir);
    }
    else {
	std::cerr << "Unable to open working directory" << std::endl;
    }
}
#line 2627 "parser.cc"
    break;

  case 149: /* run_script: RUN file_name  */
#line 757 "../../../../jags-4-3_patched/src/terminal/parser.yy"
                          {
    if(open_command_buffer((yyvsp[0].stringptr))) {
	std::cout << "Running script file " << *(yyvsp[0].stringptr) << std::endl;
    }
    else {
	std::cerr << "Unable to open script file " << *(yyvsp[0].stringptr) << std::endl;
    }
    delete (yyvsp[0].stringptr);
 }
#line 2641 "parser.cc"
    break;


#line 2645 "parser.cc"

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
  yytoken = yychar == ZZEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
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

      if (yychar <= ZZEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == ZZEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = ZZEMPTY;
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
  if (yychar != ZZEMPTY)
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

#line 768 "../../../../jags-4-3_patched/src/terminal/parser.yy"


int zzerror (const char *s)
{
    return_to_main_buffer();
    std::cerr << s << std::endl;
    return 0;
}

static jags::Range getRange(jags::ParseTree const *var)
{
  /* 
     Blank arguments, e.g. foo[] or bar[,1]  are not allowed.
  */
  unsigned int size = var->parameters().size();

  std::vector<int>  ind_lower(size), ind_upper(size);
  for (unsigned int i = 0; i < size; ++i) {
    jags::ParseTree const *range_element = var->parameters()[i];
    switch(range_element->parameters().size()) {
    case 1:
      ind_lower[i] = (int) (range_element->parameters()[0]->value() + 1.0E-6);
      ind_upper[i] = ind_lower[i];
      break;
    case 2:
      ind_lower[i] = (int) (range_element->parameters()[0]->value() + 1.0E-6);  
      ind_upper[i] = (int) (range_element->parameters()[1]->value() + 1.0E-6);
      break;
    default:
      //Error! FIXME
      break;
    }
  }
  return jags::SimpleRange(ind_lower, ind_upper);
}

void setMonitor(jags::ParseTree const *var, int thin, std::string const &type)
{
    std::string const &name = var->name();
    if (var->parameters().empty()) {
	/* Requesting the whole node */
	console->setMonitor(name, jags::Range(), thin, type);
    }
    else {
	/* Requesting subset of a multivariate node */
	console->setMonitor(name, getRange(var), thin, type);
    }
}

void clearMonitor(jags::ParseTree const *var, std::string const &type)
{
    std::string const &name = var->name();
    if (var->parameters().empty()) {
	/* Requesting the whole node */
	console->clearMonitor(name, jags::Range(), type);
    }
    else {
	/* Requesting subset of a multivariate node */
	console->clearMonitor(name, getRange(var), type);
    }
}

void doAllCoda (std::string const &stem)
{
    console->coda(stem);
}

void doCoda (jags::ParseTree const *var, std::string const &stem)
{
    //FIXME: Allow list of several nodes

    std::vector<std::pair<std::string, jags::Range> > dmp;
    if (var->parameters().empty()) {
	/* Requesting the whole node */
	dmp.push_back(std::pair<std::string,jags::Range>(var->name(), jags::Range()));
    }
    else {
	/* Requesting subset of a multivariate node */
	dmp.push_back(std::pair<std::string,jags::Range>(var->name(), getRange(var)));
    }
    console->coda(dmp, stem);
}

/* Helper function for doDump that handles all the special cases
   (missing values etc) when writing a double value */
static void writeValue(double x, std::ostream &out, bool isdiscrete)
{
  using namespace std;

  if (x == JAGS_NA) {
    out << "NA";
  }
  else if (jags_isnan(x)) {
    out << "NaN";
  }
  else if (!jags_finite(x)) {
    if (x > 0)
      out << "Inf";
    else
      out << "-Inf";
  }
  else if (isdiscrete) {
      out << static_cast<int>(x) << "L";
  }
  else {
    out << x;
  }
}

void doDump(std::string const &file, jags::DumpType type, unsigned int chain)
{
    std::map<std::string,jags::SArray> data_table;
    std::string rng_name;
    if (!console->dumpState(data_table, rng_name, type, chain)) {
	return;
    }

    /* Open output file */
    std::ofstream out(file.c_str());
    if (!out) {
	std::cerr << "Failed to open file " << file << std::endl;
	return;
    }
  
    if (rng_name.size() != 0) {
	out << "`.RNG.name` <- \"" << rng_name << "\"\n";
    }

    for (std::map<std::string, jags::SArray>::const_iterator p = data_table.begin();
	 p != data_table.end(); ++p) {
	std::string const &name = p->first;
	jags::SArray const &sarray = p->second;
	std::vector<double> const &value = sarray.value();
	long length = sarray.length();
	out << "`" << name << "` <- " << std::endl;
	std::vector<unsigned int> const &dim = sarray.dim(false);
	bool discrete = sarray.isDiscreteValued();

	if (dim.size() == 1) {
	    // Vector 
	    if (dim[0] == 1) {
		// Scalar
		writeValue(value[0], out, discrete);
	    }
	    else {
		// Vector of length > 1
		out << "c(";
		for (int i = 0; i < length; ++i) {
		    if (i > 0) {
			out << ",";
		    }
		    writeValue(value[i], out, discrete);
		}
		out << ")";
	    }
	}
	else {
	    // Array 
	    out << "structure(c(";
	    for (int i = 0; i < length; ++i) {
		if (i > 0) {
		    out << ",";
		}
		writeValue(value[i], out, discrete);
	    }
	    out << "), .Dim = c(";
	    for (unsigned int j = 0; j < dim.size(); ++j) {
		if (j > 0) {
		    out << ",";
		}
		out << dim[j] << "L";
	    }
	    out << "))";
	}
	out << "\n";
    }
    out.close();
}  

void dumpMonitors(std::string const &file, std::string const &type)
{
    std::map<std::string,jags::SArray> data_table;

    if (!console->dumpMonitors(data_table, type, false)) {
	return;
    }

    /* Open output file */
    std::ofstream out(file.c_str());
    if (!out) {
	std::cerr << "Failed to open file " << file << std::endl;
	return;
    }

    out << "`" << type << "` <-\nstructure(list(";

    std::map<std::string, jags::SArray>::const_iterator p;
    for (p = data_table.begin(); p != data_table.end(); ++p) {
	std::string const &name = p->first;
	jags::SArray const &sarray = p->second;
	std::vector<double> const &value = sarray.value();
	long length = sarray.length();

	if (p != data_table.begin()) {
	    out << ", \n";
	}
	out << "\"" << name << "\" = ";
	std::vector<unsigned int> const &dim = sarray.dim(false);
	bool discrete = sarray.isDiscreteValued();
	bool named = !sarray.dimNames().empty();

	if (dim.size() == 1 && !named) {
	    // Vector 
	    if (dim[0] == 1) {
		// Scalar
		writeValue(value[0], out, discrete);
	    }
	    else {
		// Vector of length > 1
		out << "c(";
		for (int i = 0; i < length; ++i) {
		    if (i > 0) {
			out << ",";
		    }
		    writeValue(value[i], out, discrete);
		}
		out << ")";
	    }
	}
	else {
	    // Array 
	    out << "structure(c(";
	    for (int i = 0; i < length; ++i) {
		if (i > 0) {
		    out << ",";
		}
		writeValue(value[i], out, discrete);
	    }
	    out << "), .Dim = ";
	    if (named) {
		out << "structure(";
	    }
	    out << "c(";
	    for (unsigned int j = 0; j < dim.size(); ++j) {
		if (j > 0) {
		    out << ",";
		}
		out << dim[j] << "L";
	    }
	    out << ")";
	    if (named) {
		std::vector<std::string> const &dnames = sarray.dimNames();
		out << ", .Names = c(";
		for (unsigned int k = 0; k < dnames.size(); ++k) {
		    if (k > 0) {
			out << ",";
		    }
		    out << "\"" << dnames[k] << "\"";
		}
		out << "))";
	    }
	    out << ")";
	}
    }

    out << "), \n.Names = c(";
    for (p = data_table.begin(); p != data_table.end(); ++p) {
	if (p != data_table.begin()) {
	    out << ", ";
	}
	std::string const &name = p->first;
	out << "\"" << name << "\"";
    }
    out << "))";
    out.close();
}

void setParameters(jags::ParseTree *p, std::vector<jags::ParseTree*> *parameters)
{
  /* 
     The parser dynamically allocates vectors of (pointers to)
     parameters. These vectors must be deleted when we are done with
     them.
  */
  p->setParameters(*parameters);
  delete parameters; 
}

void setParameters(jags::ParseTree *p, jags::ParseTree *param1)
{
  /*
    Wrapper function that creates a vector containing param1
    to be passed to jags::ParseTree::setParameters.
  */
  std::vector<jags::ParseTree *> parameters(1, param1);
  p->setParameters(parameters);
}

void setParameters(jags::ParseTree *p, jags::ParseTree *param1, jags::ParseTree *param2)
{
  /*
    Wrapper function that creates a vector containing param1
    and param2, to be passed to jags::ParseTree::setParameters
  */
  std::vector<jags::ParseTree *> parameters;
  parameters.push_back(param1);
  parameters.push_back(param2);
  p->setParameters(parameters);
}

void setName(jags::ParseTree *p, std::string *name)
{
  p->setName(*name);
  delete name;
}

static void errordump()
{
    if (console->model()) {
	std::ostringstream fname;
	for (unsigned int i = 1; i <= console->nchain(); ++i) {
	    fname << "jags.dump" << i << ".R";
	    std::cout << "Dumping chain " << i << " at iteration " 
		      << console->iter() << " to file " << fname.str() 
		      << std::endl;
	    doDump(fname.str(), jags::DUMP_ALL, i);
	    fname.str("");
	}
	// Moved clearModel from Console.cc CATCH_ERRORS to here
	// to allow doDump to work as described in the manual:
	console->clearModel();
    }
    if (!interactive) exit(1);
}

static void updatestar(long niter, long refresh, int width)
{
    std::cout << "Updating " << niter << std::endl;

    bool adapt = console->isAdapting();
    if (adapt && console->iter() > 0) {
	//Turn off iteration immediately if we have some burn-in
	if (console->adaptOff()) {
	    adapt = false;
	}
	else {
	    std::cout << std::endl;
	    errordump();
	    return;
	}
    }

    if (refresh == 0) {
	if( !Jtry_dump(console->update(niter/2)) ) return;
	bool status = true;
	if (adapt) {
	    if (!console->checkAdaptation(status)) {
		errordump();
		return;
	    }
	    if (!console->adaptOff()) {
		errordump();
		return;
	    }
	}
	if( !Jtry_dump(console->update(niter - niter/2)) ) return;
	if (!status) {
	    std::cerr << "WARNING: Adaptation incomplete\n";
	}
	return;
    }

    if (width > niter / refresh + 1)
	width = niter / refresh + 1;

    for (int i = 0; i < width - 1; ++i) {
	std::cout << "-";
    }
    std::cout << "| " << std::min(width * refresh, niter) << std::endl 
	      << std::flush;

    int col = 0;
    bool status = true;
    for (long n = niter; n > 0; n -= refresh) {
	if (adapt && n <= niter/2) {
	    // Turn off adaptive mode half way through burnin
	    if (!console->checkAdaptation(status)) {
		std::cout << std::endl;
		errordump();
		return;
	    }
	    if (console->adaptOff()) {
		adapt = false;
	    }
	    else {
		std::cout << std::endl;
		errordump();
		return;
	    }
	}
	long nupdate = std::min(n, refresh);
	if(Jtry_dump(console->update(nupdate))) {
	    std::cout << "*" << std::flush;
	}
	else {
	    std::cout << std::endl;
	    return;
	}
	col++;
	if (col == width || n <= nupdate) {
	    int percent = 100 - (n-nupdate) * 100/niter;
	    std::cout << " " << percent << "%" << std::endl;
	    if (n > nupdate) {
		col = 0;
	    }
	}
    }
    if (!status) {
	std::cerr << "WARNING: Adaptation incomplete\n";
    }
}

static void autoadaptstar(long maxiter, long refresh, int width)
{
    if (!console->isAdapting()) {
        std::cout << "Adaptation skipped: model is not in adaptive mode.\n";
		return;
    }
    std::cout << "Autoadapting up to " << maxiter << " iterations" << std::endl;
	
    if (width > maxiter / refresh + 1)
		width = maxiter / refresh + 1;
	
	long i = 0;
	bool status = false;
	
	if ( refresh == 0 ) {
		for (i = 0; i < maxiter; i++) {
			if (!console->checkAdaptation(status)) {
			    errordump();
			    return;
			}
			if(status)
				break;

			if( !Jtry_dump(console->update(1)) ) {
				std::cout << std::endl;
				return;
			}
		}
	}
	else {
	    for (int j = 0; j < width - 1; ++j) {
			std::cout << "-";
	    }
	    std::cout << "| " << std::min(width * refresh, maxiter) << std::endl 
		      << std::flush;

		int col = 0;
	    for (long n = maxiter; n > 0; n -= refresh) {
		    long nupdate = std::min(n, refresh);
			for (long j = 0; j < nupdate; j++) {
				if (!console->checkAdaptation(status)) {
				    errordump();
				    return;
				}
				if(status)
					break;

				if( !Jtry_dump(console->update(1)) ) {
					std::cout << std::endl;
					return;
				}
				i++;
			}
			if(status){
		    	std::cout << std::endl;
				break;
			}

	        std::cout << "+" << std::flush;
	    	col++;
	    	if (col == width || n <= nupdate) {
	    	    int percent = 100 - (n-nupdate) * 100/maxiter;
	    	    std::cout << " " << percent << "%" << std::endl;
	    	    if (n > nupdate) {
	        		col = 0;
		        }
		    }
	    }
	}
		
	if (!console->checkAdaptation(status)) {
	    errordump();
	    return;
	}
	
	if (!status) {
	    std::cerr << "Adaptation incomplete\n";
	}
	else {
		std::cout << "Adaptation completed in " << i << " iterations" << std::endl;
		if (!console->adaptOff()) {
			std::cout << std::endl;
			errordump();
			return;
	    }
	}
    return;
}

static void adaptstar(long niter, long refresh, int width, bool force)
{
    if (!console->isAdapting()) {
	    if( force ) {
			// Missing endl is deliberate - updatestar will write to the same line:
		    std::cout << "Model not in adaptive mode: ";
			updatestar(niter, refresh, width);			
		}
		else {
	        std::cerr << "Adaptation skipped: model is not in adaptive mode.\n";
		}
		return;
    }
    std::cout << "Adapting " << niter << std::endl;
    
    bool status = true;
    if (refresh == 0) {
	if( !Jtry_dump(console->update(niter)) ) return;
	if (!console->checkAdaptation(status)) {
	    errordump();
	    return;
	}
	if (!status) {
	    std::cerr << "Adaptation incomplete\n";
	    return;
	}
	else {
	    std::cerr << "Adaptation successful\n";
	    return;
	}
    }

    if (width > niter / refresh + 1)
	width = niter / refresh + 1;

    for (int i = 0; i < width - 1; ++i) {
	std::cout << "-";
    }
    std::cout << "| " << std::min(width * refresh, niter) << std::endl 
	      << std::flush;

    int col = 0;
    for (long n = niter; n > 0; n -= refresh) {
	long nupdate = std::min(n, refresh);
	if(Jtry_dump(console->update(nupdate)))
	    std::cout << "+" << std::flush;
	else {
	    std::cout << std::endl;
	    return;
	}
	col++;
	if (col == width || n <= nupdate) {
	    int percent = 100 - (n-nupdate) * 100/niter;
	    std::cout << " " << percent << "%" << std::endl;
	    if (n > nupdate) {
		col = 0;
	    }
	}
    }
    if (!console->checkAdaptation(status)) {
	std::cout << std::endl;
	errordump();
	return;
    }
    if (!status) {
	std::cerr << "Adaptation incomplete.\n";
    }
    else {
	std::cerr << "Adaptation successful\n";
    }
}

static void loadModule(std::string const &name)
{
    std::cout << "Loading module: " << name;
    lt_dlhandle mod = lt_dlopenext(name.c_str());
    if (mod == NULL) {
	std::cout << ": " << lt_dlerror() << std::endl;
    }
    else {
	std::cout << ": ok" << std::endl;
	_dyn_lib.push_front(mod);
	jags::Console::loadModule(name);
    }
}

static void unloadModule(std::string const &name)
{
    std::cout << "Unloading module: " << name << std::endl;
    jags::Console::unloadModule(name);
}

int main (int argc, char **argv)
{
  extern std::FILE *zzin;

  std::FILE *cmdfile = 0;
  if (argc > 2) {
    std::cerr << "Too many arguments" << std::endl;
  }
  else if (argc == 2) {
    interactive = false;
    cmdfile = std::fopen(ExpandFileName(argv[1]).c_str(),"r");
    if (cmdfile) {
      zzin = cmdfile;
    }
    else {
      std::cerr << "Unable to open command file " << argv[1] << std::endl;
      return 1;
    }
  }
  else {
    interactive = true;
  }

#ifndef _WIN32
  /* 
     - Allows emulation of dynamic loading on platforms that do not
     support it by preloading modules. 
     - Causes build failures on mingw-w64 (as at 21 April 2010) so
     not used on Windows platform.
  */
  LTDL_SET_PRELOADED_SYMBOLS();
#endif

  if(lt_dlinit()) {
      std::cerr << lt_dlerror() << std::endl;
      return 1;
  }

  /*
  pt2Func load_base = (pt2Func)(lt_dlsym(base, "load"));
  if (load_base == NULL) {
      std::cout << lt_dlerror() << std::endl;
      return 1;
  }
  else{
      (*load_base)();
  }
  */
  
  time_t t;
  time(&t);
  std::cout << "Welcome to " << PACKAGE_STRING << " on " << ctime(&t);
  std::cout << "JAGS is free software and comes with ABSOLUTELY NO WARRANTY" 
            << std::endl;
  loadModule("basemod");
  loadModule("bugs");

  console = new jags::Console(std::cout, std::cerr);

  zzparse();
  zzlex_destroy();

  if (argc==2) {
      std::fclose(cmdfile);
  }
  
  //Unload modules
  std::vector<std::string> mods = jags::Console::listModules();
  for (unsigned int i = 0; i < mods.size(); ++i) {
      jags::Console::unloadModule(mods[i]);
  }
  delete console;
  //Release dynamic libraries. 
  for (unsigned int i = 0; i < _dyn_lib.size(); ++i) {
      lt_dlclose(_dyn_lib[i]);
  }
  lt_dlexit();
}

static bool getWorkingDirectory(std::string &name)
{
    char buf[FILENAME_MAX];
#ifdef Win32
    if (getCurrentDirectory(FILENAME_MAX, buf)) {
	name = buf;
	return true;
    }
    else {
	name = "Error in getCurrentDirectory";
	return false;
    }
#else
    if (getcwd(buf, FILENAME_MAX)) {
	name = buf;
	return true;
    }
    else {
	switch(errno) {
	case EACCES:
	    name = "Access denied";
	    break;
	case ENOENT:
	    name = "Not found";
	    break;
	case ERANGE:
	    name = "Directory name too long";
	    break;
	default:
	    name = "Error in getcwd";
	    break;
	}
	return false;
    }
#endif
}

static void dumpSamplers(std::string const &file)
{
    std::ofstream out(file.c_str());
    if (!out) {
	std::cerr << "Failed to open file " << file << std::endl;
	return;
    }

    std::vector<std::vector<std::string> > sampler_list;
    console->dumpSamplers(sampler_list);
    for (unsigned int i = 0; i < sampler_list.size(); ++i) {
	for (unsigned int j = 1; j < sampler_list[i].size(); ++j) {
	    out << i + 1 << "\t" 
		<< sampler_list[i][0] << "\t" //First element is sampler name
		<< sampler_list[i][j] << "\n"; //Rest are node names
	}
    }

    out.close();
}

static void delete_pvec(std::vector<jags::ParseTree*> *pv)
{
    for (unsigned int i = 0; i < pv->size(); ++i) {
	delete (*pv)[i];
    }
    delete pv;
}

static void print_unused_variables(std::map<std::string, jags::SArray> const &table,
				   bool data)
{
    std::vector<std::string> supplied_vars;
    for (std::map<std::string, jags::SArray>::const_iterator p = table.begin();
	 p != table.end(); ++p)
    {
	supplied_vars.push_back(p->first);
    }
    
    std::vector<std::string> unused_vars;
    std::vector<std::string> model_vars = console->variableNames();
    if (!data) {
	// Initial values table may legitimately contain these names
	model_vars.push_back(".RNG.name");
	model_vars.push_back(".RNG.seed");
	model_vars.push_back(".RNG.state");
    }
	
	// Make sure both vectors are sorted to avoid false positive WARNINGs:
	std::sort(model_vars.begin(), model_vars.end());
	std::sort(supplied_vars.begin(), supplied_vars.end());
	
	/*  Test code to check vectors:
	if(data){
		std::cout << "Variables in model:\n";
		std::copy(model_vars.begin(), model_vars.end(),
			  std::ostream_iterator<std::string>(std::cout, ", "));
		std::cout << "\n";

		std::cout << "Supplied vars:\n";
		std::copy(supplied_vars.begin(), supplied_vars.end(),
			  std::ostream_iterator<std::string>(std::cout, ", "));
		std::cout << "\n";
	}  
	*/
	
    std::set_difference(supplied_vars.begin(), supplied_vars.end(),
			model_vars.begin(), model_vars.end(),
			std::inserter(unused_vars, unused_vars.begin()));

    if (!unused_vars.empty()) {
	std::cerr << "\nWARNING: Unused variable(s) in ";
	if (data) {
	    std::cerr << "data table:\n";
	}
	else {
	    std::cerr << "initial value table:\n";
	}
	std::copy(unused_vars.begin(), unused_vars.end(),
		  std::ostream_iterator<std::string>(std::cerr, "\n"));
	std::cerr << "\n";
    }

}

std::string ExpandFileName(char const *s)
{
    if(s[0] != '~') return s;
    std::string name = s;
    if(name.size() > 1 && s[1] != '/') return s;

    char const *p = getenv("HOME");
    if (p) {
	std::string UserHOME = p;
	if (!UserHOME.empty()) {
	    if (name.size() == 1) 
		return UserHOME;
	    else
		return UserHOME + name.substr(1);
	}
    }
    return name;
}


void doSystem(std::string const *command)
{
    std::system(command->c_str());
}

void listModules(){
  std::vector<std::string> mods = jags::Console::listModules();
  std::cout << "Modules:" << std::endl;
  for (unsigned int i = 0; i < mods.size(); ++i) {
      std::cout << "  " << mods[i] << std::endl;
  }
}


void listFactories(jags::FactoryType type)
{
    std::vector<std::pair<std::string, bool> > faclist = 
	jags::Console::listFactories(type);

    std::vector<std::pair<std::string, bool> >::const_iterator p;
    unsigned int max_strlen = 0;
    for (p = faclist.begin(); p != faclist.end(); ++p) {
	if (p->first.length() > max_strlen)
	    max_strlen = p->first.length();
    }
    if (max_strlen < 4)
	max_strlen = 4;

    //Header
    std::cout << "Name";
    for (int i = max_strlen - 4; i >=0; --i) {
	std::cout << " ";
    }
    std::cout << "Status\n";

    //Body
    for (p = faclist.begin(); p != faclist.end(); ++p) {
	std::cout << p->first << " ";
	for (int i = max_strlen - p->first.length(); i >= 0; --i) {
	    std::cout << " ";
	}
	if (p->second) {
	    std::cout << "on";
	}
	else {
	    std::cout << "off";
	}
	std::cout << "\n";
    }
}

void setFactory(std::string const &name, jags::FactoryType type, 
		std::string const &status)
{
    if (status == "on") {
	jags::Console::setFactoryActive(name, type, true);
    }
    else if (status == "off") {
	jags::Console::setFactoryActive(name, type, false);
    }
    else {
	std::cout << "status should be \"on\" or \"off\"";
    }
}

void setSeed(unsigned int seed)
{
    if (seed == 0) {
	std::cout << "seed must be non-zero";
    }
    else {
	jags::Console::setRNGSeed(seed);
    }
}
	    
bool Jtry(bool ok)
{
    if (!ok && !interactive) 
	exit(1);
    else
	return ok;
}

bool Jtry_dump(bool ok)
{
	// Allows doDump to work as described in the manual:
	if (!ok) {
	errordump();
	console->clearModel();
    if (!interactive) 
	exit(1);
	}
	return ok;
}
