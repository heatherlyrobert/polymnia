/*============================----beg-of-source---============================*/
#include  "polymnia.h"


static char   s_print        [LEN_RECD] = "";



#define     MAX_CATS    70
static struct cPOS    {
   char        grp;                         /* major group                    */
   char        sub;                         /* sub group for clarity          */
   char        pos;                         /* position in major group        */
   char        name        [LEN_LABEL];     /* short description              */
   char        desc        [LEN_LABEL];     /* longer description             */
   int         n;                           /* statistics entry               */
} s_cats [MAX_CATS] = {
   /*===[[ PREFIX ]]=============================================*/
   /*--  -123456-   -123456789012345678901234567890- */
   {  0,  1,  0, "oneline", "one line function"               ,  0 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP ONE -- COMPLEXITY ]]============================*/
   {  1,  0,  0, "-----"  , "complexity"                      , -1 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  1,  1, "scope"  , "function scope"                  ,  1 },
   {  1,  1,  2, "rtype"  , "return type"                     ,  2 },
   {  1,  1,  3, "nparam" , "number of parameters"            ,  3 },
   {  1,  1,  4, "pnum"   , "params use number pointers"      ,  4 },
   {  1,  1,  5, "ptwo"   , "params use double pointers"      ,  5 },
   {  1,  1,  6, "proto"  , "prototype location"              ,  6 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  2,  7, "total"  , "total lines of any type"         ,  7 },
   {  1,  2,  8, "debug"  , "debugging lines"                 ,  8 },
   {  1,  2,  9, "slocl"  , "source lines of code logical"    ,  9 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  3, 10, "Lvars"  , "number of local vars used"       , 10 },
   {  1,  3, 11, "Fvars"  , "number of file vars used"        , 11 },
   {  1,  3, 12, "Gvars"  , "number of global vars used"      , 12 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  4, 13, "choice" , "number of choices/decisions"     , 13 },
   {  1,  4, 14, "loop"   , "number of loops"                 , 57 },
   {  1,  4, 15, "return" , "number of return/exit points"    , 14 },
   {  1,  4, 16, "error"  , "return with errors"              , 56 },
   {  1,  4, 17, "indent" , "depth of indentation"            , 15 },
   {  1,  4, 18, "memory" , "memory management used"          , 16 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP TWO -- INTEGRATION ]]===========================*/
   {  2,  0,  0, "-----"  , "integration"                     , -1 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  1,  1, "called" , "called by anything else"         , 17 },
   {  2,  1,  2, "Fcaller", "called by local functions"       , 18 },
   {  2,  1,  3, "Gcaller", "called by global functions"      , 19 },
   {  3,  1,  4, "Xcaller", "called by external programs"     , 20 },
   {  2,  1,  5, "recurse", "function is recursive"           , 21 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  2,  6, "funcs"  , "calls to any/all functions"      , 22 },
   {  2,  2,  7, "Dfuncs" , "calls to debugging functions"    , 23 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  3,  8, "Rfuncs" , "calls to real/non-debug"         , 24 },
   {  2,  3,  9, "Ffuncs" , "calls to local functions"        , 25 },
   {  2,  3, 10, "Gfuncs" , "calls to global functions"       , 26 },
   {  2,  3, 11, "cstd"   , "calls to c-std libraries"        , 27 },
   {  2,  3, 12, "ylib"   , "calls to my custom libraries"    , 28 },
   {  2,  3, 13, "Ofuncs" , "calls to other libraries"        , 29 },
   {  2,  3, 14, "mystry" , "calls to unknown functions"      , 30 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  4, 15, "input"  , "stdin and file input"            , 31 },
   {  2,  4, 16, "output" , "stdout and file output"          , 32 },
   {  2,  4, 17, "system" , "unix process or system calls"    , 33 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  5, 18, "ncurses", "ncurses function calls"          , 34 },
   {  2,  5, 19, "opengl" , "opengl function calls"           , 35 },
   {  2,  5, 20, "windows", "x11 and like functions calls"    , 36 },
   {  2,  5, 21, "ygraph" , "my x11/opengl support libs"      , 37 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP THREE -- WATCH POINTS ]]========================*/
   {  3,  0,  0, "-----"  , "watch-points"                    , -1 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  3,  1,  1, "Dstyle" , "debugging style"                 , 38 },
   {  3,  1,  2, "Dmacro" , "debugging macros used"           , 39 },
   {  3,  1,  3, "Dmatch" , "debugging enter/exit match"      , 40 },
   {  2,  1,  4, "Dfuncs" , "calls to debugging functions"    , 23 },
   {  3,  1,  5, "Dwarn"  , "debugging trouble marker"        , 42 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  3,  2,  6, "P#use"  , "potential #define macros"        , 43 },
   {  3,  2,  7, "F#use"  , "file #define macro use"          , 44 },
   {  3,  2,  8, "G#use"  , "global #define macro use"        , 45 },
   {  3,  2,  9, "M#use"  , "cstd/major #define macro use"    , 46 },
   {  3,  2, 10, "Y#use"  , "ylib #define macro use"          , 47 },
   {  3,  2, 11, "O#use"  , "unknown/other macros"            , 48 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  3,  3, 12, "Vmask"  , "vars masking other vars"         , 49 },
   {  3,  3, 13, "Mmask"  , "macros masking other macros"     , 50 },
   {  3,  3, 14, "Fmask"  , "funcs masking other funcs"       , 51 },
   {  3,  3, 15, "Lstatic", "local static variables"          , 52 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  3,  4, 16, "units"  , "count of unit tests used"        , 53 },
   {  3,  4, 17, "scrps"  , "count of unit scripts used"      , 54 },
   {  3,  4, 18, "steps"  , "count of unit steps used"        , 55 },
   {  3,  4, 19, "·"      , ""                                , -1 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*--  -123456-   -123456789012345678901234567890- */
   { -1, -1, -1, ""       , ""                                , -1 },
   /*--  -123456-   -123456789012345678901234567890- */
};



#define     MAX_LABELS  2000
struct cLABEL {
   char        grp;
   char        pos;
   char        low;
   char        high;
   char        terse       [LEN_TERSE];
   char        desc        [LEN_TITLE];
} s_labels [MAX_LABELS] = {
   /*--   -   -123456789012345678901234567890- */
   { 1,  1, 'e', 'e', "extern" ,  "extern (library)"               },
   { 1,  1, 'g', 'g', "global" ,  "global (program wide)"          },
   { 1,  1, 'f', 'f', "file"   ,  "file (implicit file only)"      },
   { 1,  1, 's', 's', "static" ,  "static (explicit static)"       },
   { 1,  1, 'u', 'u', "unit"   ,  "unit test (special global)"     },
   /*--   -   -123456789012345678901234567890- */
   { 1,  2, 's', 's', "string" ,  "string (char*)"                 },
   { 1,  2, 'c', 'c', "char"   ,  "character (char)"               },
   { 1,  2, 'v', 'v', "void"   ,  "void (nothing)"                 },
   { 1,  2, 'p', 'p', "point"  ,  "pointer (* of any type)"        },
   { 1,  2, 'n', 'n', "number" ,  "number (int or real)"           },
   { 1,  2, 'o', 'o', "other"  ,  "other/unknown"                  },
   /*--   -   -123456789012345678901234567890- */
   { 1,  3, '#', '#', "JESUS"  ,  "out of control"                 },
   { 1,  3, '*', '*', "DANGER" ,  "none (dangerous)"               },
   { 1,  3, '0', '0', "void"   ,  "void (explicit none)"           },
   { 1,  3, '1', '3', "low"    ,  "common, just a feww"            },
   { 1,  3, '4', '6', "mid"    ,  "much more detailed"             },
   { 1,  3, '7', '9', "HIGH"   ,  "many and dangerous"             },
   /*--   -   -123456789012345678901234567890- */
   { 1,  6, 'g', 'g', "global" ,  "global header"                  },
   { 1,  6, 'f', 'f', "file"   ,  "top of file"                    },
   /*--   -   -123456789012345678901234567890- */
   { 1,  7, '#', '#', "JESUS"  ,  "more than 120 lines"            },
   { 1,  7, '1', '4', "small"  ,  "less than 20 lines"             },
   { 1,  7, '5', '9', "-"      ,  "20 to 40 lines"                 },
   { 1,  7, 'A', 'D', "full"   ,  "40 to 60 lines"                 },
   { 1,  7, 'E', 'H', "large"  ,  "60 to 80 lines"                 },
   { 1,  7, 'I', 'N', "huge"   ,  "80 to 120 lines"                },
   { 1,  7, 'O', 'Z', "JESUS"  ,  "more than 120 lines"            },
   /*--   -   -123456789012345678901234567890- */
   { 1,  8, '1', '1', "low"    ,  "just a smidge"                  },
   { 1,  8, '2', '4', "-"      ,  "average seems 25%"              },
   { 1,  8, '5', '7', "high"   ,  "high percentage"                },
   { 1,  8, 'A', 'A', "warn"   ,  "all debugging"                  },
   /*--   -   -123456789012345678901234567890- */
   { 1,  9, '1', '3', "low"    ,  "very little real code"          },
   { 1,  9, '4', '7', "-"      ,  "average seems 40-60%"           },
   { 1,  9, '8', '9', "high"   ,  "high percentage"                },
   { 1,  9, 'A', 'A', "warn"   ,  "no comments, no debug"          },
   /*--   -   -123456789012345678901234567890- */
   { 1, 10, '#', '#', "JESUS"  ,  "tons of local variables"        },
   { 1, 10, '1', '3', "few"    ,  "just a couple to work"          },
   { 1, 10, '4', '6', "-"      ,  "moderate amount"                },
   { 1, 10, '7', '9', "heavy"  ,  "clearly working harder"         },
   { 1, 10, 'A', 'Z', "JESUS"  ,  "tons of local variables"        },
   /*--   -   -123456789012345678901234567890- */
   { 1, 11, '#', '#', "JESUS"  ,  "tons of shared variables"       },
   { 1, 11, '1', '3', "few"    ,  "touching shared"                },
   { 1, 11, '4', '6', "-"      ,  "moderate amount"                },
   { 1, 11, '7', '9', "heavy"  ,  "dangerous sharing"              },
   { 1, 11, 'A', 'Z', "JESUS"  ,  "tons of shared variables"       },
   /*--   -   -123456789012345678901234567890- */
   { 1, 12, '#', '#', "JESUS"  ,  "tons of global variables"       },
   { 1, 12, '1', '2', "-"      ,  "touching global"                },
   { 1, 12, '3', '6', "lots"   ,  "moderate amount"                },
   { 1, 12, '7', '9', "heavy"  ,  "dangerous sharing"              },
   { 1, 12, 'A', 'Z', "JESUS"  ,  "tons of global variables"       },
   /*--   -   -123456789012345678901234567890- */
   { 1, 13, '#', '#', "JESUS"  ,  "more than 36 decisions"         },
   { 1, 13, '1', '3', "-"      ,  "just a couple decisions"        },
   { 1, 13, '4', '9', "lots"   ,  "lots of decisions"              },
   { 1, 13, 'A', 'Z', "JESUS"  ,  "tons of decision logic"         },
   /*--   -   -123456789012345678901234567890- */
   { 1, 14, '#', '#', "JESUS"  ,  ""                               },
   { 1, 14, '1', '1', "-"      ,  ""                               },
   { 1, 14, '2', '3', "few"    ,  ""                               },
   { 1, 14, '4', '9', "think"  ,  ""                               },
   { 1, 14, 'A', 'Z', "JESUS"  ,  ""                               },
   /*--   -   -123456789012345678901234567890- */
   { 1, 15, '#', '#', "JESUS"  ,  ""                               },
   { 1, 15, '1', '3', "-"      ,  ""                               },
   { 1, 15, '4', '9', "think"  ,  ""                               },
   { 1, 15, 'A', 'Z', "JESUS"  ,  ""                               },
   /*--   -   -123456789012345678901234567890- */
   { 1, 16, '#', '#', "alloc"  ,  "uses malloc/free"               },
   /*--   -   -123456789012345678901234567890- */
   /*> { 2,  8, '-', ""       ,  "no input"                       },                  <* 
    *> { 2,  8, 'i', ""       ,  "stdin input"                    },                  <* 
    *> { 2,  8, 'r', ""       ,  "text file input"                },                  <* 
    *> { 2,  8, 'R', ""       ,  "binary file input (fread)"      },                  <*/
   /*--   -   -123456789012345678901234567890- */
   /*> { 2,  9, '-', ""       ,  "no output"                      },                  <* 
    *> { 2,  9, 'o', ""       ,  "stdin output"                   },                  <* 
    *> { 2,  9, 'w', ""       ,  "text file output"               },                  <* 
    *> { 2,  9, 'W', ""       ,  "binary file output (fwrite)"    },                  <*/
   /*--   -   -123456789012345678901234567890- */
   /*> { 2, 10, '-', ""       ,  "no system access"               },                  <* 
    *> { 2, 10, 'f', ""       ,  "filesystem access"              },                  <* 
    *> { 2, 10, 'p', ""       ,  "process control"                },                  <* 
    *> { 2, 10, 's', ""       ,  "linux system calls"             },                  <* 
    *> { 2, 10, 'B', ""       ,  "both process/system calls"      },                  <*/
   /*--   -   -123456789012345678901234567890- */
   /*> { 2, 11, '-', ""       ,  "no recursion"                   },                  <* 
    *> { 2, 11, '#', ""       ,  "recursive function"             },                  <*/
   /*--   -   -123456789012345678901234567890- */
   /*--   -   -123456789012345678901234567890- */
   /*--DSTYLE--------------------------------- */
   { 3,  1, 'l', 'l', "long"   ,  ""                               },
   { 3,  1, 's', 's', "short"  ,  ""                               },
   { 3,  1, 'b', 'b', "BOTH"   ,  ""                               },
   /*--DMACRO--------------------------------- */
   { 3,  2, '!', '!', "MIXED"  ,  ""                               },
   { 3,  2, 'a', 'z', "-"      ,  ""                               },
   { 3,  2, 'A', 'Z', "mas"    ,  ""                               },
   /*--DMATCH--------------------------------- */
   { 3,  3, 'e', 'e', "ENTERS" ,  ""                               },
   { 3,  3, 'E', 'E', "ENTERS" ,  ""                               },
   { 3,  3, 'x', 'x', "EXITS"  ,  ""                               },
   { 3,  3, 'X', 'X', "EXITS"  ,  ""                               },
   { 3,  3, 's', 's', "SHORT"  ,  ""                               },
   { 3,  3, 'y', 'y', "-"      ,  ""                               },
   /*--DWARN---------------------------------- */
   { 3,  5, '#', '#', "BOOM"   ,  ""                               },
   /*--   -   -123456789012345678901234567890- */
   { 0,  0,  0 , 0 , ""       ,  ""                               },
};




/*====================------------------------------------====================*/
/*===----                        support functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_cats_counts_clear  (int a_counts [MAX_COUNTS])
{
   int         i           =    0;
   for (i = 0; i < MAX_COUNTS; ++i)  a_counts [i] = 0;
   return 0;
}

char
poly_cats_stats_clear   (char a_stats [MAX_STATS])
{
   int         i           =    0;
   for (i = 0; i < MAX_STATS; ++i)  a_stats [i] = '-';
   return 0;
}




/*====================------------------------------------====================*/
/*===----                   convert values to markers                  ----===*/
/*====================------------------------------------====================*/
static void  o___MARKERS_________o () { return; }

char
poly_cats_flag     (char *a_label, int a_src, char *a_dst, char a_flag)
{
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <     -1)  *a_dst = '*';
   else if (a_src ==    -1)  *a_dst = '-';
   else if (a_src ==     0)  *a_dst = '-';
   else                      *a_dst = a_flag;
   DEBUG_DATA   yLOG_schar   (*a_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_cats_exists   (char *a_label, int a_src, char *a_dst, char a_zero)
{
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <     -1)  *a_dst = '*';
   else if (a_src ==    -1)  *a_dst = '-';
   else if (a_src ==     0)  *a_dst = a_zero;
   else                      *a_dst = '#';
   DEBUG_DATA   yLOG_schar   (*a_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_cats_exact    (char *a_label, int a_src, char *a_dst, char a_zero)
{
   int         c           =    0;
   char       *x_scale     = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   /*> char       *x_scale     = "0123456789abcdefghijklmnopqrstuvwxyz";              <*/
   int         x_max       = (strlen (x_scale));
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <     -1)  *a_dst = '*';
   else if (a_src ==    -1)  *a_dst = '-';
   else if (a_src ==     0)  *a_dst = a_zero;
   else if (a_src >= x_max)  *a_dst = '#';
   else                      *a_dst = x_scale [a_src];
   DEBUG_DATA   yLOG_schar   (*a_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_cats_scaled   (char *a_label, int a_src, char *a_dst, char a_zero)
{
   int         c           =    0;
   char       *x_scale     = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int         x_max       = (strlen (x_scale) - 1) * 5;
   char        x_save      = *a_dst;
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <     -1)  *a_dst = '*';
   else if (a_src ==    -1)  *a_dst = '-';
   else if (a_src ==     0)  *a_dst = a_zero;
   else if (a_src >= x_max)  *a_dst = '#';
   else                      *a_dst = x_scale [a_src /  5];
   DEBUG_DATA   yLOG_schar   (*a_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    adding tags/line values                   ----===*/
/*====================------------------------------------====================*/
static void  o___ADDING__________o () { return; }

#define  IN_TAG  if (a_tag != NULL && a_tag->work != NULL && (a_tag->STATS_SINGLE == 'y' || (a_tag->WORK_BEG >= 0 && a_tag->WORK_END < 0))) 

char
poly_cats_logic    (tFUNC *a_tag, char a_type)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   switch (a_type) {
   case 'R' :  /* return with errors */
      IN_TAG  ++(a_tag->WORK_RCE);    
   case 'r' :  /* normal return */
      IN_TAG  ++(a_tag->WORK_RETURN);
      break;
   case 'c' :  /* if, switch */
      IN_TAG  ++(a_tag->WORK_CHOICE);
      break;
   case 'l' :  /* do, until */
      IN_TAG  ++(a_tag->WORK_LOOP);
      ++(a_tag->file->COUNT_SLOCL);
      break;
   case 'L' :  /* for (remove one semi-colon from SLOCL */
      IN_TAG  ++(a_tag->WORK_LOOP);
      --(a_tag->file->COUNT_SLOCL);
      --(a_tag->file->proj->COUNT_SLOCL);
      IN_TAG  --(a_tag->COUNT_SLOCL);
      break;
   }
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   creating the tag summary                   ----===*/
/*====================------------------------------------====================*/
static void  o___SUMMARY_________o () { return; }

char
poly_cats__single       (tFUNC *a_func, char *a_out)
{
   char        rce         =    0;
   --rce;  if (a_out  == NULL)  return rce;
   --rce;  if (a_func == NULL) {
      sprintf (a_out,   "-");
      return rce;
   }
   sprintf (a_out, "%c", a_func->STATS_SINGLE);
   return 0;
}

char
poly_cats__group_1a     (tFUNC *a_func)
{
   char        rce         =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   poly_cats_exact   ("nparam"  , a_func->WORK_PARAMS, &a_func->STATS_PARAMS, '0');
   return 0;
}

char
poly_cats__group_1b     (tFUNC *a_func)
{
   char        rce         =    0;
   float       a           =  0.0;
   int         b           =    0;
   float       c           =  0.0;
   int         d           =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   poly_cats_scaled  ("lines"   , a_func->COUNT_LINES, &a_func->STATS_TOTAL , '-');
   /*> poly_cats_scaled  ("debug"   , a_func->COUNT_DEBUG, &a_func->STATS_DEBUG , '-');   <*/
   a = ((float) a_func->COUNT_DEBUG / a_func->COUNT_LINES);
   b = round (a * 10);
   poly_cats_exact   ("debug"   , b                  , &a_func->STATS_DEBUG , '-');
   /*> poly_cats_scaled  ("slocl"   , a_func->COUNT_SLOCL, &a_func->STATS_SLOCL , '-');   <*/
   c = ((float) a_func->COUNT_SLOCL / a_func->COUNT_LINES);
   d = round (c * 10);
   poly_cats_exact   ("slocl"   , d                  , &a_func->STATS_SLOCL , '-');
   /*> printf ("%-15.15s %3d   %3d %4.2f %2d %c   %3d %4.2f %2d %c\n",                <* 
    *>       a_func->name, a_func->COUNT_LINES,                                       <* 
    *>       a_func->COUNT_DEBUG, a, b, a_func->STATS_DEBUG,                          <* 
    *>       a_func->COUNT_SLOCL, c, d, a_func->STATS_SLOCL);                         <*/
   return 0;
}

char
poly_cats__group_1c     (tFUNC *a_func)
{
   char        rce         =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   poly_cats_exact   ("locals"  , a_func->WORK_LVARS , &a_func->STATS_LVARS , '-');
   poly_cats_exact   ("file"    , a_func->WORK_FVARS , &a_func->STATS_FVARS , '-');
   poly_cats_exact   ("globals" , a_func->WORK_GVARS , &a_func->STATS_GVARS , '-');
   return 0;
}

char
poly_cats__group_1d     (tFUNC *a_func)
{
   char        rce         =    0;
   char        n           =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   poly_cats_exact   ("choices" , a_func->WORK_CHOICE, &a_func->STATS_CHOICE, '-');
   poly_cats_exact   ("loops"   , a_func->WORK_LOOP  , &a_func->STATS_LOOP  , '-');
   n = a_func->WORK_RETURN - a_func->WORK_RCE;
   poly_cats_exact   ("returns" , n                  , &a_func->STATS_RETURN, '-');
   poly_cats_exact   ("rce"     , a_func->WORK_RCE   , &a_func->STATS_RCE   , '-');
   poly_cats_flag    ("memories", a_func->WORK_MEMORY, &a_func->STATS_MEMORY, '#');
   DEBUG_INPT   yLOG_value   ("indent"    , a_func->WORK_INDENT);
   n = (a_func->WORK_INDENT / 3) - 1;
   poly_cats_exact   ("indent"  , n                  , &a_func->STATS_INDENT, '-');
   return 0;
}

char
poly_cats__complexity   (char a_style, tFUNC *a_func, char a_update, char *a_out)
{
   char        rce         =    0;
   char       *x_norm      = "[%c%c%c%c%c%c.%c%c%c.%c%c%c.%c%c%c%c%c%c]";
   char       *x_long      = " %c %c %c %c %c %c  %c %c %c  %c %c %c  %c %c %c %c %c %c ";
   char       *p           = x_norm;
   if (a_style == 'l')  p = x_long;
   --rce;  if (a_func == NULL) {
      if (a_out != NULL)
         sprintf (a_out, p,
               '-', '-', '-', '-', '-', '-',
               '-', '-', '-',
               '-', '-', '-',
               '-', '-', '-', '-', '-', '-');
      return rce;
   }
   if (a_func->work != NULL && a_update == 'y') {
      poly_cats__group_1a (a_func);
      poly_cats__group_1b (a_func);
      poly_cats__group_1c (a_func);
      poly_cats__group_1d (a_func);
   }
   --rce;  if (a_out  == NULL)  return rce;
   sprintf (a_out, p,
         a_func->STATS_SCOPE , a_func->STATS_RTYPE ,
         a_func->STATS_PARAMS, a_func->STATS_PNUM  ,
         a_func->STATS_PTWO  , a_func->STATS_PROTO ,
         a_func->STATS_TOTAL , a_func->STATS_DEBUG , a_func->STATS_SLOCL ,
         a_func->STATS_LVARS , a_func->STATS_FVARS , a_func->STATS_GVARS ,
         a_func->STATS_CHOICE, a_func->STATS_LOOP  ,
         a_func->STATS_RETURN, a_func->STATS_RCE   ,
         a_func->STATS_INDENT, a_func->STATS_MEMORY);
   return 0;
}

char
poly_cats__group_2a     (tFUNC *a_func)
{
   char        rce         =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   a_func->WORK_ACALLS = a_func->WORK_LCALLS + a_func->WORK_GCALLS + a_func->WORK_ECALLS + a_func->WORK_RECURS;
   poly_cats_exact   ("called"  , a_func->WORK_ACALLS, &a_func->STATS_ACALLS, '-');
   poly_cats_exact   ("lcalls"  , a_func->WORK_LCALLS, &a_func->STATS_LCALLS, '-');
   poly_cats_exact   ("gcalls"  , a_func->WORK_GCALLS, &a_func->STATS_GCALLS, '-');
   poly_cats_exact   ("ecalls"  , a_func->WORK_ECALLS, &a_func->STATS_ECALLS, '-');
   if (a_func->STATS_SINGLE == 'y')  a_func->WORK_RECURS = 0;
   poly_cats_flag    ("recurse" , a_func->WORK_RECURS, &a_func->STATS_RECURS, '#');
   return 0;
}

char
poly_cats__group_2b     (tFUNC *a_func)
{
   char        rce         =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   poly_cats_exact   ("funcs"   , a_func->WORK_FUNCS , &a_func->STATS_FUNCS , '-');
   poly_cats_exact   ("dfuncs"  , a_func->WORK_DFUNCS, &a_func->STATS_DFUNCS, '-');
   a_func->WORK_RFUNCS = a_func->WORK_FUNCS - a_func->WORK_DFUNCS;
   poly_cats_exact   ("rfuncs"  , a_func->WORK_RFUNCS, &a_func->STATS_RFUNCS, '-');
   poly_cats_exact   ("lfuncs"  , a_func->WORK_LFUNCS, &a_func->STATS_LFUNCS, '-');
   poly_cats_exact   ("gfuncs"  , a_func->WORK_GFUNCS, &a_func->STATS_GFUNCS, '-');
   poly_cats_exact   ("cstd"    , a_func->WORK_CSTD  , &a_func->STATS_CSTD  , '-');
   poly_cats_exact   ("ylib"    , a_func->WORK_YLIB  , &a_func->STATS_YLIB  , '-');
   poly_cats_exact   ("ofuncs"  , a_func->WORK_OFUNCS, &a_func->STATS_OFUNCS, '-');
   poly_cats_exact   ("mystry"  , a_func->WORK_MYSTRY, &a_func->STATS_MYSTRY, '-');
   return 0;
}

char
poly_cats__group_2c     (tFUNC *a_func)
{
   char        rce         =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   if (a_func->WORK_INPUT  > 0)   a_func->STATS_READ  = 'i';
   if (a_func->WORK_TREAD  > 0)   a_func->STATS_READ  = 'r';
   if (a_func->WORK_BREAD  > 0)   a_func->STATS_READ  = 'R';
   if (a_func->WORK_OUTPUT > 0)   a_func->STATS_WRITE = 'o';
   if (a_func->WORK_TWRITE > 0)   a_func->STATS_WRITE = 'w';
   if (a_func->WORK_BWRITE > 0)   a_func->STATS_WRITE = 'W';
   if (a_func->WORK_PROCS > 0 && a_func->WORK_OPSYS   > 0)  a_func->STATS_SYSTEM = 'B';
   else if (a_func->WORK_PROCS   > 0)  a_func->STATS_SYSTEM = 'p';
   else if (a_func->WORK_OPSYS   > 0)  a_func->STATS_SYSTEM = 's';
   else if (a_func->WORK_FILESYS > 0)  a_func->STATS_SYSTEM = 'f';
   return 0;
}

char
poly_cats__group_2d     (tFUNC *a_func)
{
   char        rce         =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   poly_cats_exact   ("ncurses" , a_func->WORK_NCURSE, &a_func->STATS_NCURSE, '-');
   poly_cats_exact   ("opengl"  , a_func->WORK_OPENGL, &a_func->STATS_OPENGL, '-');
   poly_cats_exact   ("window"  , a_func->WORK_WINDOW, &a_func->STATS_WINDOW, '-');
   poly_cats_exact   ("myx"     , a_func->WORK_MYX   , &a_func->STATS_MYX   , '-');
   return 0;
}

char
poly_cats__integration  (char a_style, tFUNC *a_func, char a_update, char *a_out)
{
   char        rce         =    0;
   char       *x_norm      = "[%c%c%c%c%c.%c%c.%c%c%c%c%c%c%c.%c%c%c.%c%c%c%c]";
   char       *x_long      = " %c %c %c %c %c  %c %c  %c %c %c %c %c %c %c  %c %c %c  %c %c %c %c ";
   char       *p           = x_norm;
   if (a_style == 'l')  p = x_long;
   --rce;  if (a_func == NULL) {
      if (a_out != NULL) {
         sprintf (a_out, p,
               '-', '-', '-', '-', '-',
               '-', '-',
               '-', '-', '-', '-', '-', '-', '-',
               '-', '-', '-',
               '-', '-', '-', '-');
      }
      return rce;
   }
   if (a_func->work != NULL && a_update == 'y') {
      poly_cats__group_2a (a_func);
      poly_cats__group_2b (a_func);
      poly_cats__group_2c (a_func);
      poly_cats__group_2d (a_func);
   }
   --rce;  if (a_out  == NULL)  return rce;
   sprintf (a_out, p,
         a_func->STATS_ACALLS,
         a_func->STATS_LCALLS, a_func->STATS_GCALLS,
         a_func->STATS_ECALLS, a_func->STATS_RECURS,
         a_func->STATS_FUNCS , a_func->STATS_DFUNCS,
         a_func->STATS_RFUNCS, a_func->STATS_LFUNCS, a_func->STATS_GFUNCS,
         a_func->STATS_CSTD  , a_func->STATS_YLIB  ,
         a_func->STATS_OFUNCS, a_func->STATS_MYSTRY,
         a_func->STATS_READ  , a_func->STATS_WRITE , a_func->STATS_SYSTEM,
         a_func->STATS_NCURSE, a_func->STATS_OPENGL,
         a_func->STATS_WINDOW, a_func->STATS_MYX   );
   return 0;
}

char
poly_cats__group_3a     (tFUNC *a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   /*---(defense)------------------------*/
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   /*---(defaults)-----------------------*/
   a_func->STATS_DSTYLE = '-';
   a_func->STATS_DMATCH = '-';
   /*---(quick out)----------------------*/
   if      (a_func->COUNT_DEBUG == 0)          return 0;
   /*---(style)--------------------------*/
   if      (a_func->WORK_DLONG   > 0 && a_func->WORK_DSHORT  > 0)   a_func->STATS_DSTYLE = 'b';
   else if (a_func->WORK_DLONG   > 0)                               a_func->STATS_DSTYLE = 'l';
   else if (a_func->WORK_DSHORT  > 0)                               a_func->STATS_DSTYLE = 's';
   else                                                             a_func->STATS_DSTYLE = '?';
   /*---(untyped lines)------------------*/
   if (a_func->WORK_DLONG + a_func->WORK_DSHORT < a_func->WORK_DCOUNT) {
      switch (a_func->STATS_DSTYLE) {
      case 'b' :  a_func->STATS_DSTYLE = 'B';  break;
      case 'l' :  a_func->STATS_DSTYLE = 'L';  break;
      case 's' :  a_func->STATS_DSTYLE = 'S';  break;
      default  :  a_func->STATS_DSTYLE = '?';  break;
      }
   }
   if (a_func->STATS_DWARN != '#' && strchr ("ls", a_func->STATS_DSTYLE) == NULL)  a_func->STATS_DWARN = '#';
   /*---(unguarded logging)--------------*/
   if (a_func->WORK_DFREE > 0)  a_func->STATS_DMACRO = '#';
   if (a_func->STATS_DWARN != '#' && a_func->STATS_DMACRO == '#')  a_func->STATS_DWARN = '#';
   /*---(check none)---------------------*/
   if (a_func->WORK_DENTER == 0 && a_func->WORK_DEXIT == 0) {
      a_func->STATS_DMATCH = 'p'; 
      return 0;
   }
   /*---(quick out)----------------------*/
   if (strchr ("-?", a_func->STATS_DSTYLE) != NULL)   return 0;
   /*---(match)--------------------------*/
   a_func->STATS_DMATCH = '-';
   /*---(find enter troubles)------------*/
   if      (a_func->WORK_DENTER <= 0) 
      a_func->STATS_DMATCH = 'E';
   else if (a_func->WORK_DENTER == 1 && strchr ("ls", a_func->STATS_DSTYLE) == NULL) 
      a_func->STATS_DMATCH = 'e';
   else if (a_func->WORK_DENTER == 2 && a_func->STATS_DSTYLE != 'b') 
      a_func->STATS_DMATCH = 'e';
   else if (a_func->WORK_DENTER >  2)
      a_func->STATS_DMATCH = 'E';
   if (a_func->STATS_DWARN != '#' && a_func->STATS_DMATCH != '-')  a_func->STATS_DWARN = '#';
   if (a_func->STATS_DMATCH != '-')   return 0;
   /*---(find exit troubles)-------------*/
   if      (a_func->WORK_DEXIT  <= 0)
      a_func->STATS_DMATCH = 'X';
   else if (a_func->WORK_RETURN != a_func->WORK_DEXIT)
      a_func->STATS_DMATCH = 'x';
   if (a_func->STATS_DWARN != '#' && a_func->STATS_DMATCH != '-')  a_func->STATS_DWARN = '#';
   if (a_func->STATS_DMATCH != '-')   return 0;
   /*---(find short troubles)------------*/
   if (a_func->STATS_DSTYLE == 's' && a_func->WORK_GFUNCS > 0)
      a_func->STATS_DMATCH = '?';
   if (a_func->STATS_DSTYLE == 's' && a_func->WORK_YLIB   > 0)
      a_func->STATS_DMATCH = '!';
   if (a_func->STATS_DWARN != '#' && a_func->STATS_DMATCH != '-')  a_func->STATS_DWARN = '#';
   if (a_func->STATS_DMATCH != '-')   return 0;
   /*---(final judgement)----------------*/
   a_func->STATS_DMATCH = 'y';
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_cats__group_3b     (tFUNC *a_func)
{
   char        rce         =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   poly_cats_exact   ("F#use"   , a_func->WORK_PUSE  , &a_func->STATS_PUSE  , '-');
   poly_cats_exact   ("F#use"   , a_func->WORK_FUSE  , &a_func->STATS_FUSE  , '-');
   poly_cats_exact   ("G#use"   , a_func->WORK_GUSE  , &a_func->STATS_GUSE  , '-');
   poly_cats_exact   ("M#use"   , a_func->WORK_MUSE  , &a_func->STATS_MUSE  , '-');
   poly_cats_exact   ("Y#use"   , a_func->WORK_YUSE  , &a_func->STATS_YUSE  , '-');
   poly_cats_exact   ("O#use"   , a_func->WORK_OUSE  , &a_func->STATS_OUSE  , '-');
   return 0;
}

char
poly_cats__group_3c     (tFUNC *a_func)
{
   char        rce         =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   if (a_func->WORK_VMASK   > 0)  a_func->STATS_VMASK   = '#';
   if (a_func->WORK_MMASK   > 0)  a_func->STATS_MMASK   = '#';
   if (a_func->WORK_FMASK   > 0)  a_func->STATS_FMASK   = '#';
   if (a_func->WORK_LSTATIC > 0)  a_func->STATS_LSTATIC = '#';
   return 0;
}

char
poly_cats__group_3d     (tFUNC *a_func)
{
   char        rce         =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   poly_cats_exact   ("tunit"   , a_func->WORK_TUNIT , &a_func->STATS_TUNIT , '-');
   poly_cats_exact   ("sunit"   , a_func->WORK_SUNIT , &a_func->STATS_SUNIT , '-');
   poly_cats_exact   ("nunit"   , a_func->WORK_NUNIT , &a_func->STATS_NUNIT , '-');
   return 0;
}

char
poly_cats__watchpoints  (char a_style, tFUNC *a_func, char a_update, char *a_out)
{
   char        rce         =    0;
   char       *x_norm      = "[%c%c%c%c%c.%c%c%c%c%c%c.%c%c%c%c.%c%c%c%c]";
   char       *x_long      = " %c %c %c %c %c  %c %c %c %c %c %c  %c %c %c %c  %c %c %c %c ";
   char       *p           = x_norm;
   if (a_style == 'l')  p = x_long;
   --rce;  if (a_func == NULL) {
      if (a_out != NULL) {
         sprintf (a_out, p,
               '-', '-', '-', '-', '-',
               '-', '-', '-', '-', '-', '-',
               '-', '-', '-', '-',
               '-', '-', '-', '-');
      }
      return rce;
   }
   if (a_func->work != NULL && a_update == 'y') {
      poly_cats__group_3a (a_func);
      poly_cats__group_3b (a_func);
      poly_cats__group_3c (a_func);
      poly_cats__group_3d (a_func);
   }
   --rce;  if (a_out  == NULL)  return rce;
   sprintf (a_out, p,
         a_func->STATS_DSTYLE, a_func->STATS_DMACRO,
         a_func->STATS_DMATCH, a_func->STATS_DFUNCS, a_func->STATS_DWARN ,
         a_func->STATS_PUSE  , a_func->STATS_FUSE  , a_func->STATS_GUSE  ,
         a_func->STATS_MUSE  , a_func->STATS_YUSE  , a_func->STATS_OUSE  ,
         a_func->STATS_VMASK , a_func->STATS_MMASK ,
         a_func->STATS_FMASK , a_func->STATS_LSTATIC,
         a_func->STATS_TUNIT , a_func->STATS_SUNIT , a_func->STATS_NUNIT ,
         '-');
   return 0;
}

char
poly_cats_function      (tFUNC *a_func)
{
   poly_cats__complexity  ('-', a_func, 'y', NULL);
   poly_cats__integration ('-', a_func, 'y', NULL);
   poly_cats__watchpoints ('-', a_func, 'y', NULL);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      reporting support                       ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTING_______o () { return; }

char*        /*-> create category headers for reporting ---[gs2---·7-5·5--·B13-]¬[18--·B---56--·---·----]¬[---·------]-*/
poly_cats_header        (int n, char *a_title, int a_curr, int a_total)
{
   int         i           =    0;
   int         m           =    0;
   char        x_len       =    0;
   char        t           [LEN_RECD]  = "";
   char        s           [LEN_TERSE] = "";
   strlcpy (s_print, "", LEN_RECD);
   if (n <= 0 || n > 7)  return s_print;
   if (n > 1)  sprintf (s_print, "%-5.5s : %4d  %5d             ", a_title, a_curr, a_total);
   else        sprintf (s_print, "                                ");
   for (i = 0; i < MAX_CATS; ++i) {
      /*---(end-of-data)-----------------*/
      if (s_cats [i].grp <  0)  break;
      /*---(group break)-----------------*/
      if (s_cats [i].sub == 0) {
         strlcat (s_print, " ", LEN_RECD);
         continue;
      }
      /*---(subgroup break)--------------*/
      if (i > 0 && s_cats [i - 1].sub != s_cats [i].sub) {
         strlcat (s_print, " ", LEN_RECD);
      }
      /*---(vertical strip)--------------*/
      x_len = strlen (s_cats [i].name);
      m = x_len - n;
      if      (n > 7) sprintf (s, "  ");
      else if (m < 0) sprintf (s, "  ");
      else            sprintf (s, "%c ", s_cats [i].name [m]);
      strlcat (s_print, s, LEN_RECD);
      /*---(done)------------------------*/
   }
   return s_print;
}

char*        /*-> create category details for functions ---[gs2---.7-5.5--.B13-]¬[18--.B---56--.---.----]¬[---.------]-*/
poly_cats_database      (tFUNC *a_func)
{
   char        t           [LEN_RECD]  = "";
   char        a           [LEN_RECD]  = "";
   char        b           [LEN_RECD]  = "";
   char        c           [LEN_RECD]  = "";
   char        r           [LEN_TERSE] = "";
   tFUNC      *x_func      = NULL;
   x_func = a_func;
   poly_cats__single      (a_func, r);
   if (x_func != NULL && a_func->type == '_')   x_func = NULL;
   poly_cats__complexity  ('l', x_func, 'y', a);
   poly_cats__integration ('l', x_func, 'y', b);
   poly_cats__watchpoints ('l', x_func, 'y', c);
   sprintf  (s_print, "%s  %s %s %s", r, a, b, c);
   if (a_func->type == '_')  strldchg (s_print, '-', ' ', LEN_RECD);
   else                      strldchg (s_print, '-', '·', LEN_RECD);
   return s_print;
}

char*        /*-> create category details for functions ---[gs2---.7-5.5--.B13-]¬[18--.B---56--.---.----]¬[---.------]-*/
poly_cats_comment       (tFUNC *a_func)
{
   char        t           [LEN_RECD]  = "";
   char        a           [LEN_RECD]  = "";
   char        b           [LEN_RECD]  = "";
   char        c           [LEN_RECD]  = "";
   char        r           [LEN_TERSE] = "";
   tFUNC      *x_func      = NULL;
   x_func = a_func;
   poly_cats__single      (a_func, r);
   if (x_func != NULL && a_func->type == '_')   x_func = NULL;
   poly_cats__complexity  ('-', x_func, 'y', a);
   poly_cats__integration ('-', x_func, 'y', b);
   poly_cats__watchpoints ('-', x_func, 'y', c);
   sprintf (s_print, "%s¬%s¬%s", a, b, c);
   if (a_func->type == '_') {
      strldchg (s_print, '[', ' ', LEN_RECD);
      strldchg (s_print, ']', ' ', LEN_RECD);
      strldchg (s_print, '.', ' ', LEN_RECD);
      strldchg (s_print, '-', '·', LEN_RECD);
      strldchg (s_print, '¬', ' ', LEN_RECD);
   } else {
      strldchg (s_print, '.', '·', LEN_RECD);
   }
   return s_print;
}

char*        /*-> create category details for functions ---[gs2---.7-5.5--.B13-]¬[18--.B---56--.---.----]¬[---.------]-*/
poly_cats_full          (tFUNC *a_func, char *a_out)
{
   char        t           [LEN_RECD]  = "";
   char        a           [LEN_RECD]  = "";
   char        b           [LEN_RECD]  = "";
   char        c           [LEN_RECD]  = "";
   char        r           [LEN_TERSE] = "";
   tFUNC      *x_func      = NULL;
   x_func = a_func;
   poly_cats__single      (a_func, r);
   if (x_func != NULL && a_func->type == '_')   x_func = NULL;
   poly_cats__complexity  ('l', x_func, 'y', a);
   poly_cats__integration ('l', x_func, 'y', b);
   poly_cats__watchpoints ('l', x_func, 'y', c);
   sprintf (a_out, "%s  %s %s %s ", r, a, b, c);
   /*> strldchg (a_out, '-', '·', LEN_RECD);                                          <*/
   if (a_func->type == '_')  strldchg (a_out, '-', ' ', LEN_RECD);
   else                      strldchg (a_out, '-', '·', LEN_RECD);
   poly_cats__complexity  ('-', x_func, 'y', a);
   poly_cats__integration ('-', x_func, 'y', b);
   poly_cats__watchpoints ('-', x_func, 'y', c);
   sprintf (t    , " %s¬%s¬%s ", a, b, c);
   if (a_func->type == '_') {
      strldchg (t, '[', ' ', LEN_RECD);
      strldchg (t, ']', ' ', LEN_RECD);
      strldchg (t, '.', ' ', LEN_RECD);
      strldchg (t, '-', '·', LEN_RECD);
      strldchg (t, '¬', ' ', LEN_RECD);
   } else {
      strldchg (t, '.', '·', LEN_RECD);
   }
   strlcat (a_out, t, LEN_RECD);
   return a_out;
}

char
poly_cats_func          (tFUNC *a_func)
{
   char        rce         =  -10;
   int         i           =    0;
   int         j           =    0;
   tFUNC      *x_func      = NULL;
   char        x_sub       =    0;
   uchar       x_ch        =  ' ';
   uchar       x_stat      =  ' ';
   char        x_terse     [LEN_TERSE] = "";
   if (a_func == NULL)  poly_func_by_index (10, &x_func);
   else                 x_func = a_func;
   if (x_func == NULL)  return 0;
   printf ("%s\n\n", x_func->name);
   for (i = 0; i < MAX_CATS; ++i) {
      /*---(end-of-data)-----------------*/
      if (s_cats [i].grp <  0)  break;
      /*---(group break)-----------------*/
      if (s_cats [i].sub == 0) {
         printf ("\n");
         x_ch = '[';
         x_ch = '*';
         x_ch = '¼';
         continue;
      }
      else if (s_cats [i + 1].sub <= 0) {
         x_ch = ']';
         x_ch = '½';
      }
      else if (s_cats [i].sub != x_sub && x_ch == (uchar) ' ') {
         x_ch = '¬';
         x_ch = '·';
      }
      /*---(vertical strip)--------------*/
      strlcpy (x_terse, "", LEN_TERSE);
      if (s_cats [i].n >= 0)  x_stat = x_func->stats [s_cats [i].n];
      if (x_stat != '-') {
         for (j = 0; j < MAX_LABELS; ++j) {
            if (s_labels [j].grp   != s_cats [i].grp)  continue;
            if (s_labels [j].pos   != s_cats [i].pos)  continue;
            if (s_labels [j].low   >  x_stat)          continue;
            if (s_labels [j].high  <  x_stat)          continue;
            strlcpy (x_terse, s_labels [j].terse, LEN_TERSE);
         }
      }
      else                x_stat = '·';
      printf ("%c%-7.7s  %c  %-9.9s\n", x_ch, s_cats [i].name, x_stat, x_terse);
      x_ch  = ' ';
      x_sub = s_cats [i].sub;
      /*---(done)------------------------*/
   }
   printf ("\n");
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_cats__unit      (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD]  = "[]";
   char        a           [LEN_RECD]  = "[]";
   char        b           [LEN_RECD]  = "[]";
   char        c           [LEN_RECD]  = "[]";
   char        r           [LEN_TERSE] = "[]";
   tFUNC      *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "CATS unit        : tag number unknown");
   if (i <  0)       return unit_answer;
   /*---(prepare)------------------------*/
   poly_func_by_index (i, &u);
   if (u != NULL)  sprintf  (t, "[%.20s]", u->name);
   /*---(simple)-------------------------*/
   if        (strcmp (a_question, "complex"   )     == 0) {
      if (u != NULL)  sprintf  (t, "[%.15s]", u->name);
      poly_cats__single      (u, r);
      poly_cats__complexity  ('l', u, 'y', a);
      sprintf (unit_answer, "CATS complex(%2d) : %-17.17s %s [%s]", i, t, r, a);
   }
   else if   (strcmp (a_question, "integ"     )     == 0) {
      if (u != NULL)  sprintf  (t, "[%.15s]", u->name);
      poly_cats__single      (u, r);
      poly_cats__integration ('l', u, 'y', b);
      sprintf (unit_answer, "CATS integ  (%2d) : %-17.17s %s [%s]", i, t, r, b);
   }
   else if   (strcmp (a_question, "watch"     )     == 0) {
      if (u != NULL)  sprintf  (t, "[%.15s]", u->name);
      poly_cats__single      (u, r);
      poly_cats__watchpoints ('l', u, 'y', c);
      sprintf (unit_answer, "CATS watch  (%2d) : %-17.17s %s [%s]", i, t, r, c);
   }
   else if   (strcmp (a_question, "full"      )     == 0) {
      if (u != NULL)  sprintf  (t, "[%.15s]", u->name);
      poly_cats__single      (u, r);
      poly_cats__complexity  ('-', u, 'y', a);
      poly_cats__integration ('-', u, 'y', b);
      poly_cats__watchpoints ('-', u, 'y', c);
      sprintf (unit_answer, "CATS full   (%2d) : %-17.17s %s %s %s %s", i, t, r, a, b, c);
   }
   else if   (strcmp (a_question, "header"    )     == 0) {
      strlcpy (t, poly_cats_header (i, "test", 0, 0), LEN_RECD);
      sprintf (unit_answer, "CATS header (%2d) : %3d[%s]", i, strlen (t), t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


