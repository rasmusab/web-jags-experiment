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

#line 199 "parser.hh"

};
typedef union ZZSTYPE ZZSTYPE;
# define ZZSTYPE_IS_TRIVIAL 1
# define ZZSTYPE_IS_DECLARED 1
#endif


extern ZZSTYPE zzlval;


int zzparse (void);


#endif /* !YY_ZZ_PARSER_HH_INCLUDED  */
