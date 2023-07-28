/*============================----beg-of-source---============================*/
#include  "polymnia.h"


static char   s_print        [LEN_RECD] = "";

/*
 *
 *  complexity orig  (20)  [fcC##g·L44·27-·E-2D1-]
 *             long  (30)  [fcg´·C´66·´·21´L44´22·´1·E2D´·]
 *              six subsections : scope, params, pparam, lines, vars, logic, mem
 *
 * this will show in the tag window for the requested function
 *
 * 123456789-123456789-
 *
 * COMPLEXITY
 * ´· ´···········scope
 * file scope 
 * char return
 * global prototype
 * ´· ´··········params
 * ·  audit
 * 12 total
 * ´· ´··········dparam
 * 6  incomming-only
 * 6  return-only
 * ·  both directions
 * ´· ´··········pparam
 * ·  function pointer
 * 2  number pointer
 * 1  double pointer
 * ´· ´···········lines
 * L  100-105 lines
 * 4  40% debugging
 * 4  40% actual code
 * ´· ´············vars
 * 2  local
 * 2  file   ( 7 refs)
 * ·  global ( · refs)
 * ´· ´···········logic
 * 1  indent level
 * ·  loops
 * 15 choices
 * 2  normal ends
 * 14 error returns
 * ´· ´·············mem
 * ·  memory alloc
 * ´· ´·············end
 */

/*
 * complexity    [fcC##g·L44·27-·E-2D1-]
 * integration   [-----·--·-------·---·----]
 * watch-points  [?#p-#·4-2--2·----·----]
 * [fcC##g·L44·27-·E-2D1-]¬[-----·--·-------·---·----]¬[?#p-#·4-2--2·----·----]
 */


static struct cPOS    {
   char        grp;                         /* major group                    */
   char        sub;                         /* sub group for clarity          */
   char        pos;                         /* position in major group        */
   char        name        [LEN_LABEL];     /* short description              */
   char        desc        [LEN_DESC];      /* longer description             */
   int         n;                           /* statistics entry               */
} const s_cats [MAX_CATS] = {
   /*===[[ PREFIX ]]=============================================*/
   /*--  -123456-   -123456789012345678901234567890- */
   {  0,  1,  0, "oneline", "one line function"               ,  0 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP ONE -- COMPLEXITY ]]============================*/
   {  1,  0,  0, "-----"  , "complexity"                      , -1 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  1,  1, "scope"  , "function scope"                  ,  1 },
   {  1,  1,  2, "rtype"  , "return type"                     ,  2 },
   {  1,  1,  3, "proto"  , "prototype location"              ,  6 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  2,  4, "paudit" , "audit of params"                 ,  3 },
   {  1,  2,  5, "params" , "number of parameters"            ,  3 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  3,  6, "pin"    , "incomming parameters"            ,  3 },
   {  1,  3,  7, "pout"   , "outgoing parameters"             ,  3 },
   {  1,  3,  8, "pboth"  , "both in/out parameters"          ,  3 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  4,  9, "pnum"   , "params use number pointers"      ,  4 },
   {  1,  4, 10, "pmulti" , "params use multiple pointers"    ,  5 },
   {  1,  4, 11, "pfunc"  , "function pointers"               ,  5 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  5, 12, "total"  , "total actual lines (div 5)"      ,  7 },
   {  1,  5, 13, "%debug" , "debugging lines (% total)"       ,  8 },
   {  1,  5, 14, "%code"  , "lines of code logical (% total)" ,  9 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  6, 15, "Lvars"  , "number of local vars used"       , 10 },
   {  1,  6, 16, "Fvars"  , "number of file/static vars used" , 11 },
   {  1,  6, 17, "Gvars"  , "number of global vars used"      , 12 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  7, 18, "indent" , "depth of indentation"            , 15 },
   {  1,  7, 19, "loop"   , "number of loops"                 , 58 },
   {  1,  7, 20, "choice" , "number of choices/decisions"     , 13 },
   {  1,  7, 21, "return" , "number of return/exit points"    , 14 },
   {  1,  7, 22, "w´error", "return with errors"              , 57 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  8, 23, "memory" , "memory management used"          , 16 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP TWO -- INTEGRATION ]]===========================*/
   {  2,  0,  0, "-----"  , "integration"                     , -1 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  1,  1, "call´by", "called by anything else"         , 17 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  2,  2, "Fcaller", "called by in-file functions"     , 18 },
   {  2,  2,  3, "Gcaller", "called by global functions"      , 19 },
   {  3,  2,  4, "Xcaller", "called by external programs"     , 20 },
   {  2,  2,  5, "recurse", "function is recursive"           , 21 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  3,  6, "call´to", "calls to any/all functions"      , 22 },
   {  2,  3,  7, "Dfuncs" , "calls to debugging functions"    , 23 },
   {  2,  3,  8, "Rfuncs" , "calls to real/non-debug"         , 24 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  4,  9, "Ffuncs" , "calls to in-file functions"      , 25 },
   {  2,  4, 10, "Gfuncs" , "calls to global functions"       , 26 },
   {  2,  4, 11, "cstd"   , "calls to c-std libraries"        , 27 },
   {  2,  4, 12, "ylib"   , "calls to my custom libraries"    , 28 },
   {  2,  4, 13, "vikeys" , "calls to vi-keys libraries"      , 28 },
   {  2,  4, 14, "Ofuncs" , "calls to other libraries"        , 29 },
   {  2,  4, 15, "mystry" , "calls to unknown functions"      , 30 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  5, 16, "input"  , "stdin and file input"            , 31 },
   {  2,  5, 17, "output" , "stdout and file output"          , 32 },
   {  2,  5, 18, "system" , "unix process or system calls"    , 33 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  6, 19, "ncurses", "ncurses function calls"          , 34 },
   {  2,  6, 20, "opengl" , "opengl function calls"           , 35 },
   {  2,  6, 21, "windows", "x11 and like functions calls"    , 36 },
   {  2,  6, 22, "ygraph" , "my x11/opengl support libs"      , 37 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP THREE -- WATCH POINTS ]]========================*/
   {  3,  0,  0, "-----"  , "watch-points"                    , -1 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  1,  1, "Dactive", "debugging is used"               , 23 },
   {  3,  1,  2, "Dstyle" , "debugging style"                 , 38 },
   {  3,  1,  3, "Dmacro" , "debugging macros used"           , 39 },
   {  3,  1,  4, "Dmatch" , "debugging enter/exit match"      , 40 },
   {  3,  1,  5, "Dwarn"  , "debugging trouble marker"        , 42 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  3,  2,  6, "macros" , "potential #define macros"        , 43 },
   {  3,  3,  7, "file"   , "in-file #define macro use"       , 44 },
   {  3,  3,  8, "global" , "global #define macro use"        , 45 },
   {  3,  3,  9, "cstd"   , "cstd #define macro use"          , 46 },
   {  3,  3, 10, "ylib"   , "ylib #define macro use"          , 47 },
   {  3,  3, 11, "vikeys" , "vikeys #define macro use"        , 47 },
   {  3,  3, 12, "other"  , "unknown/other macros"            , 48 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  3,  4, 13, "Vmask"  , "vars masking other vars"         , 49 },
   {  3,  4, 14, "Mmask"  , "macros masking other macros"     , 50 },
   {  3,  4, 15, "Fmask"  , "funcs masking other funcs"       , 51 },
   {  3,  4, 16, "Lstatic", "local static variables"          , 52 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  3,  5, 17, "units"  , "count of unit tests used"        , 53 },
   {  3,  5, 18, "scrps"  , "count of unit scripts used"      , 54 },
   {  3,  5, 19, "steps"  , "count of unit steps used"        , 55 },
   {  3,  5, 20, "string" , "count of string tests"           , 56 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*--  -123456-   -123456789012345678901234567890- */
   { -1, -1, -1, ""       , ""                                , -1 },
   /*--  -123456-   -123456789012345678901234567890- */
};



#define     MAX_LABELS  2000
static struct cLABEL {
   char        grp;
   char        pos;
   char        low;
   char        high;
   char        terse       [LEN_TERSE];
   char        desc        [LEN_TITLE];
} const s_labels [MAX_LABELS] = {
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
   { 1,  2, '_', '_', "title"  ,  "sub-title function"             },
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
   for (i = 0; i < MAX_STATS; ++i)  a_stats [i] = '·';
   return 0;
}




/*====================------------------------------------====================*/
/*===----                   convert values to markers                  ----===*/
/*====================------------------------------------====================*/
static void  o___MARKERS_________o () { return; }

char
poly_cats_exists   (char *a_label, int a_src, char *r_dst, char a_zero)
{
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <     -1)  *r_dst = '¢';
   else if (a_src ==    -1)  *r_dst = a_zero;
   else if (a_src ==     0)  *r_dst = a_zero;
   else                      *r_dst = '#';
   DEBUG_DATA   yLOG_schar   (*r_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_cats_flag     (char *a_label, int a_src, char *r_dst, char a_flag)
{
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <     -1)  *r_dst = '¢';
   else if (a_src ==    -1)  *r_dst = '·';
   else if (a_src ==     0)  *r_dst = '·';
   else                      *r_dst = a_flag;
   DEBUG_DATA   yLOG_schar   (*r_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_cats_exact    (char *a_label, int a_src, char *r_dst, char a_zero)
{
   int         c           =    0;
   char       *x_scale     = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int         x_max       = (strlen (x_scale));
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <     -1)  *r_dst = '¢';
   else if (a_src ==    -1)  *r_dst = '·';
   else if (a_src ==     0)  *r_dst = a_zero;
   else if (a_src >= x_max)  *r_dst = '#';
   else                      *r_dst = x_scale [a_src];
   DEBUG_DATA   yLOG_schar   (*r_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_cats_scaled   (char *a_label, int a_src, char *r_dst, char a_zero)
{
   int         c           =    0;
   char       *x_scale     = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int         x_max       = (strlen (x_scale) - 1) * 5;
   char        x_save      = *r_dst;
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <     -1)  *r_dst = '¢';
   else if (a_src ==    -1)  *r_dst = '·';
   else if (a_src ==     0)  *r_dst = a_zero;
   else if (a_src >= x_max)  *r_dst = '#';
   else                      *r_dst = x_scale [a_src /  5];
   DEBUG_DATA   yLOG_schar   (*r_dst);
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
      ++(my.COUNT_SLOCL);
      ++(a_tag->file->COUNT_SLOCL);
      ++(a_tag->file->proj->COUNT_SLOCL);
      break;
   case 'L' :  /* for (remove one semi-colon from SLOCL */
      IN_TAG  ++(a_tag->WORK_LOOP);
      --(my.COUNT_SLOCL);
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



/*====================------------------------------------====================*/
/*===----                     complexity line                          ----===*/
/*====================------------------------------------====================*/
static void  o___COMPLEXITY______o () { return; }

char
poly_cats__group_1a     (tFUNC *a_func, char a_style, char a_scope, char a_rc, char a_proto, char r_out [LEN_LABEL])
{
   char       *x_norm      = "%c%c%c";
   char       *x_long      = " %c %c %c";
   char       *p           = x_norm;
   if (r_out   == NULL)  return 0;
   if (a_style == 'l')  {
      p = x_long;
      if (a_scope  == '·')  a_scope  = '´';
   }
   sprintf (r_out, p, a_scope, a_rc, a_proto);
   return 1;
}

char         /*-> display string for parameters ---------------[ ´········· ]-*/ /*-åfcg´·BáA1·á···´8·9´C··´1·62·á·æ¬å1á1···´8·8á7·1····´···´····æ¬å·····´······´····´112·æ-*/
poly_cats__group_1bcd   (tFUNC *a_func, char a_style, char a_paudit, int a_nparam, int a_pin, int a_pout, int a_pboth, int a_pnum, int a_pmulti, int a_pfunc, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%cá%c%c%cá%c%c%c";
   char       *x_long      = " %c %c  %c %c %c  %c %c %c";
   char       *p           = x_norm;
   char        x_au, x_co, x_in, x_ou, x_bo, x_pn, x_pm, x_pf;
   /*---(format individuals)-------------*/
   x_au = a_paudit;
   poly_cats_exact  ("params"  , a_nparam, &x_co, '·');
   poly_cats_exact  ("pin"     , a_pin   , &x_in, '·');
   poly_cats_exact  ("pout"    , a_pout  , &x_ou, '·');
   poly_cats_exact  ("pboth"   , a_pboth , &x_bo, '·');
   poly_cats_exact  ("pnum"    , a_pnum  , &x_pn, '·');
   poly_cats_exact  ("pmulti"  , a_pmulti, &x_pm, '·');
   poly_cats_exact  ("pfunc"   , a_pfunc , &x_pf, '·');
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_PARAMS  = x_co;
      a_func->STATS_PIN     = x_in;
      a_func->STATS_POUT    = x_ou;
      a_func->STATS_PBOTH   = x_bo;
      a_func->STATS_PNUM    = x_pn;
      a_func->STATS_PMULTI  = x_pm;
      a_func->STATS_PFUNC   = x_pf;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_au     != '>')  x_au     = '´';
      if (x_in     == '·')  x_in     = 'á';
      if (x_pn     == '·')  x_pn     = 'á';
   }
   sprintf (r_out, p, x_au, x_co, x_in, x_ou, x_bo, x_pn, x_pm, x_pf);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__group_1e     (tFUNC *a_func, char a_style, int a_lines, int a_debug, int a_slocl, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%c%c";
   char       *x_long      = " %c %c %c";
   char       *p           = x_norm;
   float       a           =  0.0;
   int         b           =    0;
   float       c           =  0.0;
   int         d           =    0;
   char        x_li, x_de, x_sl;
   /*---(format individuals)-------------*/
   poly_cats_scaled  ("lines"   , a_lines, &x_li, '·');
   if (a_lines > 0) {
      a = ((float) a_debug / a_lines);
      b = round (a * 10);
   }
   poly_cats_exact   ("debug"   , b      , &x_de, '·');
   if (a_lines > 0) {
      c = ((float) a_slocl / a_lines);
      d = round (c * 10);
   }
   poly_cats_exact   ("slocl"   , d      , &x_sl, '·');
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_TOTAL   = x_li;
      a_func->STATS_DEBUG   = x_de;
      a_func->STATS_SLOCL   = x_sl;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_li     == '·')  x_li     = '´';
   }
   sprintf (r_out, p, x_li, x_de, x_sl);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__group_1f     (tFUNC *a_func, char a_style, int a_local, int a_file, int a_global, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%c%c";
   char       *x_long      = " %c %c %c";
   char       *p           = x_norm;
   char        x_lo, x_fi, x_gl;
   /*---(format individuals)-------------*/
   poly_cats_exact   ("local"   , a_local , &x_lo, '·');
   poly_cats_exact   ("file"    , a_file  , &x_fi, '·');
   poly_cats_exact   ("global"  , a_global, &x_gl, '·');
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_LVARS   = x_lo;
      a_func->STATS_FVARS   = x_fi;
      a_func->STATS_GVARS   = x_gl;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_lo     == '·')  x_lo     = '´';
   }
   sprintf (r_out, p, x_lo, x_fi, x_gl);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__group_1gh    (tFUNC *a_func, char a_style, int a_indent, int a_loop, int a_choice, int a_return, int a_error, int a_memory, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%c%c%c%cá%c";
   char       *x_long      = " %c %c %c %c %c  %c";
   char       *p           = x_norm;
   char        n           =    0;
   char        x_in, x_ch, x_lo, x_re, x_er, x_me;
   /*---(format individuals)-------------*/
   n = (a_indent / 3) - 1;
   poly_cats_exact   ("indent"  , n       , &x_in, '·');
   poly_cats_exact   ("loops"   , a_loop  , &x_lo, '·');
   poly_cats_exact   ("choices" , a_choice, &x_ch, '·');
   poly_cats_exact   ("returns" , a_return, &x_re, '·');
   poly_cats_exact   ("rce"     , a_error , &x_er, '·');
   poly_cats_flag    ("memory"  , a_memory, &x_me, '#');
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_INDENT  = x_in;
      a_func->STATS_LOOP    = x_lo;
      a_func->STATS_CHOICE  = x_ch;
      a_func->STATS_RETURN  = x_re;
      a_func->STATS_RCE     = x_er;
      a_func->STATS_MEMORY  = x_me;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_in     == '·')  x_in     = '´';
      if (x_me     == '·')  x_me     = 'á';
   }
   sprintf (r_out, p, x_in, x_lo, x_ch, x_re, x_er, x_me);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__complexity   (tFUNC *a_func, char a_style, char a_update, char *r_out)
{
   char        rce         =  -10;
   char       *x_norm      = "å%s´%s´%s´%s´%sæ";
   char       *x_long      = "%s %s %s %s %s ";
   char       *p           = x_norm;
   char        a           [LEN_LABEL] = "";
   char        bcd         [LEN_LABEL] = "";
   char        e           [LEN_LABEL] = "";
   char        f           [LEN_LABEL] = "";
   char        gh          [LEN_LABEL] = "";
   tFUNC      *x_func      = NULL;
   if (a_style == 'l')  p = x_long;
   if (a_func == NULL) {
      if (r_out != NULL) {
         if (a_style == 'l')  strcpy (r_out, " ´ · ·  ´ ·  á · ·  á · ·  ´ · ·  ´ · ·  ´ · · · ·  á ");
         else                 strcpy (r_out, "å···´··á···á···´···´···´·····á·æ");
      }
      return 0;
   }
   if (a_func != NULL && a_func->work != NULL && a_update == 'y')   x_func = a_func;
   poly_cats__group_1a   (x_func, a_style, a_func->STATS_SCOPE , a_func->STATS_RTYPE, a_func->STATS_PROTO, a);
   poly_cats__group_1bcd (x_func, a_style, a_func->STATS_PAUDIT, a_func->WORK_PARAMS, a_func->WORK_PIN   , a_func->WORK_POUT  , a_func->WORK_PBOTH, a_func->WORK_PNUM  , a_func->WORK_PMULTI, a_func->WORK_PFUNC, bcd);
   poly_cats__group_1e   (x_func, a_style, a_func->COUNT_LINES , a_func->COUNT_DEBUG, a_func->COUNT_CODE , e);
   poly_cats__group_1f   (x_func, a_style, a_func->WORK_LVARS  , a_func->WORK_FVARS , a_func->WORK_GVARS , f);
   poly_cats__group_1gh  (x_func, a_style, a_func->WORK_INDENT , a_func->WORK_LOOP  , a_func->WORK_CHOICE, a_func->WORK_RETURN, a_func->WORK_RCE  , a_func->WORK_MEMORY, gh);
   --rce;  if (r_out  == NULL)  return rce;
   sprintf (r_out, p, a, bcd, e, f, gh);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                     intergration line                        ----===*/
/*====================------------------------------------====================*/
static void  o___INTEGRATION_____o () { return; }

char
poly_cats__group_2ab    (tFUNC *a_func, char a_style, int a_local, int a_global, int a_extern, int a_recurse, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%cá%c%c%c%c";
   char       *x_long      = " %c  %c %c %c %c";
   char       *p           = x_norm;
   char        x_total     =    0;
   char        x_al, x_lo, x_gl, x_ex, x_re;
   /*---(format individuals)-------------*/
   x_total = a_local + a_global + a_extern + a_recurse;
   poly_cats_exact   ("called"  , x_total  , &x_al, '·');
   poly_cats_exact   ("lcalls"  , a_local  , &x_lo, '·');
   poly_cats_exact   ("gcalls"  , a_global , &x_gl, '·');
   poly_cats_exact   ("ecalls"  , a_extern , &x_ex, '·');
   poly_cats_flag    ("recurse" , a_recurse, &x_re, '#');
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_ACALLS  = x_al;
      a_func->STATS_LCALLS  = x_lo;
      a_func->STATS_GCALLS  = x_gl;
      a_func->STATS_ECALLS  = x_ex;
      a_func->STATS_RECURS  = x_re;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_al     == '·')  x_al     = '´';
      if (x_lo     == '·')  x_lo     = 'á';
   }
   sprintf (r_out, p, x_al, x_lo, x_gl, x_ex, x_re);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__group_2cd    (tFUNC *a_func, char a_style, int a_funcs, int a_dfuncs, int a_lfuncs, int a_gfuncs, int a_cfuncs, int a_yfuncs, int a_vfuncs, int a_ofuncs, int a_mfuncs, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%c%cá%c%c%c%c%c%c%c";
   char       *x_long      = " %c %c %c  %c %c %c %c %c %c %c";
   char       *p           = x_norm;
   char        x_real      =    0;
   char        x_fu, x_df, x_rf, x_lo, x_gl, x_cf, x_yl, x_vi, x_ot, x_my;
   /*---(format individuals)-------------*/
   poly_cats_exact   ("funcs"   , a_funcs  , &x_fu, '·');
   poly_cats_exact   ("dfuncs"  , a_dfuncs , &x_df, '·');
   x_real = a_funcs - a_dfuncs;
   poly_cats_exact   ("rfuncs"  , x_real   , &x_rf, '·');
   poly_cats_exact   ("lfuncs"  , a_lfuncs , &x_lo, '·');
   poly_cats_exact   ("gfuncs"  , a_gfuncs , &x_gl, '·');
   poly_cats_exact   ("cfuncs"  , a_cfuncs , &x_cf, '·');
   poly_cats_exact   ("yfuncs"  , a_yfuncs , &x_yl, '·');
   poly_cats_exact   ("vfuncs"  , a_vfuncs , &x_vi, '·');
   poly_cats_exact   ("ofuncs"  , a_ofuncs , &x_ot, '·');
   poly_cats_exact   ("mfuncs"  , a_mfuncs , &x_my, '·');
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_FUNCS   = x_fu;
      a_func->STATS_DFUNCS  = x_df;
      a_func->STATS_RFUNCS  = x_rf;
      a_func->STATS_LFUNCS  = x_lo;
      a_func->STATS_GFUNCS  = x_gl;
      a_func->STATS_CSTD    = x_cf;
      a_func->STATS_YLIB    = x_yl;
      a_func->STATS_VIKEYS  = x_vi;
      a_func->STATS_OFUNCS  = x_ot;
      a_func->STATS_MYSTRY  = x_my;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_fu     == '·')  x_fu     = '´';
      if (x_lo     == '·')  x_lo     = 'á';
   }
   sprintf (r_out, p, x_fu, x_df, x_rf, x_lo, x_gl, x_cf, x_yl, x_vi, x_ot, x_my);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__group_2e     (tFUNC *a_func, char a_style, int a_input, int a_tinput, int a_binput, int a_output, int a_toutput, int a_boutput, int a_procs, int a_opsys, int a_filesys, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%c%c";
   char       *x_long      = " %c %c %c";
   char       *p           = x_norm;
   char        x_in, x_ou, x_sy;
   /*---(format for input)---------------*/
   x_in = '·';
   if (a_input   > 0)   x_in  = 'i';
   if (a_tinput  > 0) { if (x_in == '·')  x_in  = 'r';  else x_in = '*'; }
   if (a_binput  > 0) { if (x_in == '·')  x_in  = 'R';  else x_in = '*'; }
   /*---(format for output)--------------*/
   x_ou = '·';
   if (a_output  > 0)   x_ou  = 'o';
   if (a_toutput > 0) { if (x_ou == '·')  x_ou  = 'w';  else x_ou = '*'; }
   if (a_boutput > 0) { if (x_ou == '·')  x_ou  = 'W';  else x_ou = '*'; }
   /*---(format for system)--------------*/
   x_sy = '·';
   if (a_procs   > 0)   x_sy  = 'p';
   if (a_opsys   > 0) { if (x_sy == '·')  x_sy  = 's';  else x_sy = '*'; }
   if (a_filesys > 0) { if (x_sy == '·')  x_sy  = 'f';  else x_sy = '*'; }
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_READ    = x_in;
      a_func->STATS_WRITE   = x_ou;
      a_func->STATS_SYSTEM  = x_sy;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_in     == '·')  x_in     = '´';
   }
   sprintf (r_out, p, x_in, x_ou, x_sy);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__group_2f     (tFUNC *a_func, char a_style, int a_ncurse, int a_opengl, int a_window, int a_myx, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%c%c%c";
   char       *x_long      = " %c %c %c %c";
   char       *p           = x_norm;
   char        x_nc, x_op, x_wi, x_my;
   /*---(format individuals)-------------*/
   poly_cats_exact   ("ncurses" , a_ncurse , &x_nc, '·');
   poly_cats_exact   ("opengl"  , a_opengl , &x_op, '·');
   poly_cats_exact   ("window"  , a_window , &x_wi, '·');
   poly_cats_exact   ("myx"     , a_myx    , &x_my, '·');
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_NCURSE  = x_nc;
      a_func->STATS_OPENGL  = x_op;
      a_func->STATS_WINDOW  = x_wi;
      a_func->STATS_MYX     = x_my;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_nc     == '·')  x_nc     = '´';
   }
   sprintf (r_out, p, x_nc, x_op, x_wi, x_my);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__integration  (tFUNC *a_func, char a_style, char a_update, char *r_out)
{
   char        rce         =    0;
   char       *x_norm      = "å%s´%s´%s´%sæ";
   char       *x_long      = "%s %s %s %s ";
   char       *p           = x_norm;
   char        ab          [LEN_LABEL] = "";
   char        cd          [LEN_LABEL] = "";
   char        e           [LEN_LABEL] = "";
   char        f           [LEN_LABEL] = "";
   tFUNC      *x_func      = NULL;
   if (a_style == 'l')  p = x_long;
   if (a_func == NULL) {
      if (r_out != NULL) {
         if (a_style == 'l')  strcpy (r_out, " ´  á · · ·  ´ · ·  á · · · · · ·  ´ · ·  ´ · · · ");
         else                 strcpy (r_out, "å·á····´···á·······´···´····æ");
      }
      return 0;
   }
   if (a_func != NULL && a_func->work != NULL && a_update == 'y')   x_func = a_func;
   poly_cats__group_2ab  (x_func, a_style, a_func->WORK_LCALLS , a_func->WORK_GCALLS, a_func->WORK_ECALLS, a_func->WORK_RECURS , ab);
   poly_cats__group_2cd  (x_func, a_style, a_func->WORK_FUNCS  , a_func->WORK_DFUNCS, a_func->WORK_LFUNCS, a_func->WORK_GFUNCS , a_func->WORK_CSTD  , a_func->WORK_YLIB, a_func->WORK_VIKEYS, a_func->WORK_OFUNCS, a_func->WORK_MYSTRY, cd);
   poly_cats__group_2e   (x_func, a_style, a_func->WORK_INPUT  , a_func->WORK_TREAD , a_func->WORK_BREAD , a_func->WORK_OUTPUT , a_func->WORK_TWRITE, a_func->WORK_BWRITE, a_func->WORK_PROCS, a_func->WORK_OPSYS, a_func->WORK_FILESYS, e);
   poly_cats__group_2f   (x_func, a_style, a_func->WORK_NCURSE , a_func->WORK_OPENGL, a_func->WORK_WINDOW, a_func->WORK_MYX    , f);
   --rce;  if (r_out  == NULL)  return rce;
   sprintf (r_out, p, ab, cd, e, f);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                     watch-point line                         ----===*/
/*====================------------------------------------====================*/
static void  o___WATCH___________o () { return; }

char
poly_cats__group_3a     (tFUNC *a_func, char a_style, int a_lines, int a_dcount, int a_dlong, int a_dshort, char a_macro, int a_dfree, int a_denter, int a_dexit, int a_dexitr, int a_return, int a_rce, int a_lfuncs, int a_gfuncs, int a_yfuncs, int a_dextra, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%c%c%c%c";
   char       *x_long      = " %c %c %c %c %c";
   char       *p           = x_norm;
   char        x_total     =    0;
   char        x_usage, x_style, x_macro, x_match, x_dwarn;
   /*---(prepare)------------------------*/
   x_usage = x_style = x_macro = x_match = x_dwarn = '·';
   /*---(usage)--------------------------*/
   x_usage = '·';
   if (a_lines  > 0)   x_usage = '>';
   if (a_dcount > 0)   x_usage = '>';
   /*---(base style)---------------------*/
   if (a_dcount > 0 && x_match == '·') {
      if      (a_dlong  > 0 && a_dshort > 0)    { x_style = 'b';  x_dwarn = '#'; }
      else if (a_dlong  > 0)                      x_style = 'l';
      else if (a_dshort > 0)                      x_style = 's';
      else                                      { x_style = '?';  x_dwarn = '#'; }
      /*> if      (a_dlong + a_dshort != a_dcount)    x_style = toupper (x_style);    <*/
   }
   /*---(macro used)---------------------*/
   if (a_dcount > 0 && x_match == '·') {
      x_macro = a_macro;
      if (a_dfree > 0)                          { x_macro = '#';  x_dwarn = '#'; }
   }
   /*---(enters)-------------------------*/
   if (a_dcount > 0 && x_match == '·') {
      if      (a_denter  <= 0)                                    { x_match = 'E';  x_dwarn = '#'; }
      else if (a_denter  == 1 && strchr ("ls", x_style) == NULL)  { x_match = 'e';  x_dwarn = '#'; }
      else if (a_denter  == 2 && strchr ("b" , x_style) == NULL)  { x_match = 'e';  x_dwarn = '#'; }
      else if (a_denter  >  2)                                    { x_match = 'E';  x_dwarn = '#'; }
   }
   /*---(exits)--------------------------*/
   if (a_dcount > 0 && x_match == '·') {
      if      (a_dexit   <= 0)                                    { x_match = 'X';  x_dwarn = '#'; }
      else if (a_dexit + a_dexitr != a_return + a_rce)            { x_match = 'x';  x_dwarn = '#'; }
      else if (a_dexit   != a_return)                             { x_match = 'n';  x_dwarn = 'r'; }
      else if (a_dexitr  != a_rce)                                { x_match = 'r';  x_dwarn = 'r'; }
   }
   /*---(extern)-------------------------*/
   if (a_dcount > 0 && x_match == '·') {
      if      (x_style == 's' && a_lfuncs  > 0)                   { x_dwarn = 'l'; }
      if      (x_style == 's' && a_gfuncs  > 0 && x_dwarn == '·') { x_dwarn = 'g'; }
      if      (x_style == 's' && a_yfuncs  > 0 && x_dwarn == '·') { x_dwarn = '>'; }
   }
   /*---(extra)--------------------------*/
   if (a_dcount > 0 && x_match == '·') {
      if      (a_dextra >  0)                                     { x_dwarn = '+'; }
   }
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_DSTYLE  = x_style;
      a_func->STATS_DMACRO  = x_macro;
      a_func->STATS_DMATCH  = x_match;
      a_func->STATS_DWARN   = x_dwarn;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_usage  != '>')  x_usage  = '´';
   }
   sprintf (r_out, p, x_usage, x_style, x_macro, x_match, x_dwarn);
   /*---(complete)-----------------------*/
   return 1;
}

/*> char                                                                                                                      <* 
 *> poly_cats__group_3a     (tFUNC *a_func)                                                                                   <* 
 *> {                                                                                                                         <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                               <* 
 *>    char        rce         =  -10;           /+ return code for errors         +/                                         <* 
 *>    /+---(defense)------------------------+/                                                                               <* 
 *>    --rce;  if (a_func       == NULL)  return rce;                                                                         <* 
 *>    --rce;  if (a_func->work == NULL)  return rce;                                                                         <* 
 *>    /+---(defaults)-----------------------+/                                                                               <* 
 *>    a_func->STATS_DSTYLE = '-';                                                                                            <* 
 *>    a_func->STATS_DMATCH = '-';                                                                                            <* 
 *>    /+---(quick out)----------------------+/                                                                               <* 
 *>    if      (a_func->COUNT_DEBUG == 0)          return 0;                                                                  <* 
 *>    /+---(style)--------------------------+/                                                                               <* 
 *>    /+> if      (a_func->WORK_DLONG   > 0 && a_func->WORK_DSHORT  > 0)   a_func->STATS_DSTYLE = 'b';   <*                  <* 
 *>     *> else if (a_func->WORK_DLONG   > 0)                               a_func->STATS_DSTYLE = 'l';   <*                  <* 
 *>     *> else if (a_func->WORK_DSHORT  > 0)                               a_func->STATS_DSTYLE = 's';   <*                  <* 
 *>     *> else                                                             a_func->STATS_DSTYLE = '?';   <+/                 <* 
 *>    /+---(untyped lines)------------------+/                                                                               <* 
 *>    /+> if (a_func->WORK_DLONG + a_func->WORK_DSHORT < a_func->WORK_DCOUNT) {          <*                                  <* 
 *>     *>    switch (a_func->STATS_DSTYLE) {                                             <*                                  <* 
 *>     *>    case 'b' :  a_func->STATS_DSTYLE = 'B';  break;                             <*                                  <* 
 *>     *>    case 'l' :  a_func->STATS_DSTYLE = 'L';  break;                             <*                                  <* 
 *>     *>    case 's' :  a_func->STATS_DSTYLE = 'S';  break;                             <*                                  <* 
 *>     *>    default  :  a_func->STATS_DSTYLE = '?';  break;                             <*                                  <* 
 *>     *>    }                                                                           <*                                  <* 
 *>     *> }                                                                              <+/                                 <* 
 *>    /+> if (a_func->STATS_DWARN != '#' && strchr ("ls", a_func->STATS_DSTYLE) == NULL)  a_func->STATS_DWARN = '#';   <+/   <* 
 *>    /+---(unguarded logging)--------------+/                                                                               <* 
 *>    /+> if (a_func->WORK_DFREE > 0)  a_func->STATS_DMACRO = '#';                                     <*                    <* 
 *>     *> if (a_func->STATS_DWARN != '#' && a_func->STATS_DMACRO == '#')  a_func->STATS_DWARN = '#';   <+/                   <* 
 *>    /+---(check none)---------------------+/                                                                               <* 
 *>    if (a_func->WORK_DENTER == 0 && a_func->WORK_DEXIT == 0) {                                                             <* 
 *>       a_func->STATS_DMATCH = 'p';                                                                                         <* 
 *>       return 0;                                                                                                           <* 
 *>    }                                                                                                                      <* 
 *>    /+---(quick out)----------------------+/                                                                               <* 
 *>    if (strchr ("-?", a_func->STATS_DSTYLE) != NULL)   return 0;                                                           <* 
 *>    /+---(match)--------------------------+/                                                                               <* 
 *>    /+> a_func->STATS_DMATCH = '-';                                                    <+/                                 <* 
 *>    /+---(find enter troubles)------------+/                                                                               <* 
 *>    /+> if      (a_func->WORK_DENTER <= 0)                                                           <*                    <* 
 *>     *>    a_func->STATS_DMATCH = 'E';                                                               <*                    <* 
 *>     *> else if (a_func->WORK_DENTER == 1 && strchr ("ls", a_func->STATS_DSTYLE) == NULL)            <*                    <* 
 *>     *>    a_func->STATS_DMATCH = 'e';                                                               <*                    <* 
 *>     *> else if (a_func->WORK_DENTER == 2 && a_func->STATS_DSTYLE != 'b')                            <*                    <* 
 *>     *>    a_func->STATS_DMATCH = 'e';                                                               <*                    <* 
 *>     *> else if (a_func->WORK_DENTER >  2)                                                           <*                    <* 
 *>     *>    a_func->STATS_DMATCH = 'E';                                                               <*                    <* 
 *>     *> if (a_func->STATS_DWARN != '#' && a_func->STATS_DMATCH != '-')  a_func->STATS_DWARN = '#';   <*                    <* 
 *>     *> if (a_func->STATS_DMATCH != '-')   return 0;                                                 <+/                   <* 
 *>    /+---(find exit troubles)-------------+/                                                                               <* 
 *>    /+> if      (a_func->WORK_DEXIT  <= 0)                                                           <*                    <* 
 *>     *>    a_func->STATS_DMATCH = 'X';                                                               <*                    <* 
 *>     *> else if (a_func->WORK_RETURN != a_func->WORK_DEXIT)                                          <*                    <* 
 *>     *>    a_func->STATS_DMATCH = 'x';                                                               <*                    <* 
 *>     *> if (a_func->STATS_DWARN != '#' && a_func->STATS_DMATCH != '-')  a_func->STATS_DWARN = '#';   <*                    <* 
 *>     *> if (a_func->STATS_DMATCH != '-')   return 0;                                                 <+/                   <* 
 *>    /+---(find short troubles)------------+/                                                                               <* 
 *>    /+> if (a_func->STATS_DSTYLE == 's' && a_func->WORK_GFUNCS > 0)                                  <*                    <* 
 *>     *>    a_func->STATS_DMATCH = '?';                                                               <*                    <* 
 *>     *> if (a_func->STATS_DSTYLE == 's' && a_func->WORK_YLIB   > 0)                                  <*                    <* 
 *>     *>    a_func->STATS_DMATCH = '!';                                                               <*                    <* 
 *>     *> if (a_func->STATS_DWARN != '#' && a_func->STATS_DMATCH != '-')  a_func->STATS_DWARN = '#';   <*                    <* 
 *>     *> if (a_func->STATS_DMATCH != '-')   return 0;                                                 <+/                   <* 
 *>    /+---(final judgement)----------------+/                                                                               <* 
 *>    a_func->STATS_DMATCH = 'y';                                                                                            <* 
 *>    /+---(complete)-----------------------+/                                                                               <* 
 *>    return 0;                                                                                                              <* 
 *> }                                                                                                                         <*/

char
poly_cats__group_3b     (tFUNC *a_func, char a_style, int a_puse, int a_fuse, int a_guse, int a_cuse, int a_yuse, int a_vuse, int a_ouse, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%c%c%c%c%c%c";
   char       *x_long      = " %c  %c %c %c %c %c %c";
   char       *p           = x_norm;
   char        x_pu, x_fu, x_gu, x_cs, x_yu, x_vi, x_ou;
   /*---(format individuals)-------------*/
   poly_cats_exact   ("F#use"   , a_puse , &x_pu , '·');
   poly_cats_exact   ("F#use"   , a_fuse , &x_fu , '·');
   poly_cats_exact   ("G#use"   , a_guse , &x_gu , '·');
   poly_cats_exact   ("C#use"   , a_cuse , &x_cs , '·');
   poly_cats_exact   ("Y#use"   , a_yuse , &x_yu , '·');
   poly_cats_exact   ("V#use"   , a_vuse , &x_vi , '·');
   poly_cats_exact   ("O#use"   , a_ouse , &x_ou , '·');
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_PUSE    = x_pu;
      a_func->STATS_FUSE    = x_fu;
      a_func->STATS_GUSE    = x_gu;
      a_func->STATS_MUSE    = x_cs;
      a_func->STATS_YUSE    = x_yu;
      a_func->STATS_OUSE    = x_ou;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_pu     == '·')  x_pu     = '´';
      if (x_fu     == '·')  x_fu     = 'á';
   }
   sprintf (r_out, p, x_pu, x_fu, x_gu, x_cs, x_yu, x_vi, x_ou);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__group_3c     (tFUNC *a_func, char a_style, int a_vmask, int a_mmask, int a_fmask, int a_static, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%c%c%c";
   char       *x_long      = " %c %c %c %c";
   char       *p           = x_norm;
   char        x_vm, x_mm, x_fm, x_st;
   /*---(format individuals)-------------*/
   poly_cats_exact   ("vmask"   , a_vmask , &x_vm , '·');
   poly_cats_exact   ("mmask"   , a_mmask , &x_mm , '·');
   poly_cats_exact   ("fmask"   , a_fmask , &x_fm , '·');
   poly_cats_exact   ("static"  , a_static, &x_st , '·');
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_VMASK   = x_vm;
      a_func->STATS_MMASK   = x_mm;
      a_func->STATS_FMASK   = x_fm;
      a_func->STATS_LSTATIC = x_st;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_vm     == '·')  x_vm     = '´';
   }
   sprintf (r_out, p, x_vm, x_mm, x_fm, x_st);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__group_3d     (tFUNC *a_func, char a_style, int a_tunit, int a_sunit, int a_nunit, int a_stest, char r_out [LEN_LABEL])
{
   char        rce         =    0;
   char       *x_norm      = "%c%c%c%c";
   char       *x_long      = " %c %c %c %c";
   char       *p           = x_norm;
   char        x_tu, x_su, x_nu, x_st;
   /*---(format individuals)-------------*/
   poly_cats_exact   ("tunit"   , a_tunit , &x_tu , '·');
   poly_cats_exact   ("sunit"   , a_sunit , &x_su , '·');
   poly_cats_exact   ("nunit"   , a_nunit , &x_nu , '·');
   poly_cats_exact   ("stest"   , a_stest , &x_st , '·');
   /*---(update, if requested)-----------*/
   if (a_func  != NULL) {
      a_func->STATS_TUNIT   = x_tu;
      a_func->STATS_SUNIT   = x_su;
      a_func->STATS_NUNIT   = x_nu;
      a_func->STATS_STEST   = x_st;
   }
   /*---(output)-------------------------*/
   if (r_out   == NULL)  return 0;
   if (a_style == 'l') {
      p = x_long;
      if (x_tu     == '·')  x_tu     = '´';
   }
   sprintf (r_out, p, x_tu, x_su, x_nu, x_st);
   /*---(complete)-----------------------*/
   return 1;
}

char
poly_cats__watchpoints  (tFUNC *a_func, char a_style, char a_update, char *r_out)
{
   char        rce         =    0;
   char       *x_norm      = "å%s´%s´%s´%sæ";
   char       *x_long      = "%s %s %s %s ";
   char       *p           = x_norm;
   char        a           [LEN_LABEL] = "";
   char        b           [LEN_LABEL] = "";
   char        c           [LEN_LABEL] = "";
   char        d           [LEN_LABEL] = "";
   tFUNC      *x_func      = NULL;
   if (a_style == 'l')  p = x_long;
   if (a_func == NULL) {
      if (r_out != NULL) {
         if (a_style == 'l')  strcpy (r_out, " ´ · · · ·  ´  á · · · · ·  ´ · · ·  ´ · · · ");
         else                 strcpy (r_out, "å·····´á······´····´····æ");
      }
      return 0;
   }
   if (a_func != NULL && a_func->work != NULL && a_update == 'y')   x_func = a_func;
   poly_cats__group_3a   (x_func, a_style, a_func->COUNT_DEBUG , a_func->WORK_DCOUNT , a_func->WORK_DLONG  , a_func->WORK_DSHORT , a_func->STATS_DMACRO , a_func->WORK_DFREE  , a_func->WORK_DENTER , a_func->WORK_DEXIT  , a_func->WORK_DEXITR , a_func->WORK_RETURN , a_func->WORK_RCE    , a_func->WORK_LFUNCS , a_func->WORK_GFUNCS , a_func->WORK_YLIB   , a_func->WORK_DEXTRA , a);
   poly_cats__group_3b   (x_func, a_style, a_func->WORK_PUSE   , a_func->WORK_FUSE   , a_func->WORK_GUSE   , a_func->WORK_CUSE   , a_func->WORK_YUSE    , a_func->WORK_VUSE    , a_func->WORK_OUSE   , b);
   poly_cats__group_3c   (x_func, a_style, a_func->WORK_VMASK  , a_func->WORK_MMASK  , a_func->WORK_FMASK  , a_func->WORK_LSTATIC, c);
   poly_cats__group_3d   (x_func, a_style, a_func->WORK_TUNIT  , a_func->WORK_SUNIT  , a_func->WORK_NUNIT  , a_func->WORK_STEST  , d);
   --rce;  if (r_out  == NULL)  return rce;
   sprintf (r_out, p, a, b, c, d);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                      reporting support                       ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTING_______o () { return; }

char         /*-> classify function by statistics -------------[ leaf       ]-*/ /*-åfc#´·8á71·á···´4·A´1··´2·A1·á·æ¬å1á1···´8·8á······´···´····æ¬å·····´······´····´····æ-*/
poly_cats__anatomy      (char a_rtype, char a_vars, char a_calls, char a_graph, char a_read, char a_write, char a_memory, char r_anatomy [LEN_TERSE])
{
   char        x_anatomy   [LEN_TERSE] = "";
   if (a_rtype == 'c' &&  a_vars + a_calls == 0)  {
      if (a_graph == 0 && a_read  == 0 && a_write == 0) {
         if (a_memory == 0)  strlcpy (x_anatomy, "leaf"     , LEN_TERSE);
         else                strlcpy (x_anatomy, "seed"     , LEN_TERSE);
      }
      else if (a_graph >  0 && a_read  == 0 && a_write == 0)  strlcpy (x_anatomy, "flower" , LEN_TERSE);
      else if (a_graph == 0 && a_read  >  0 && a_write == 0)  strlcpy (x_anatomy, "root"   , LEN_TERSE);
      else if (a_graph == 0 && a_read  == 0 && a_write >  0)  strlcpy (x_anatomy, "tendril", LEN_TERSE);
      else                                                    strlcpy (x_anatomy, "crazy"  , LEN_TERSE);
   } else {
      strlcpy (x_anatomy, "´"        , LEN_TERSE);
   }
   if (r_anatomy != NULL)  strlcpy (r_anatomy, x_anatomy, LEN_TERSE);
   return 0;
}

char
poly_cats_anatomy       (tFUNC *a_func)
{
   char        rce         =  -10;
   char        x_vars, x_calls, x_graph, x_read, x_write, x_memory;
   --rce;  if (a_func == NULL)  return rce;
   x_vars   = a_func->WORK_FVARS  + a_func->WORK_GVARS;
   x_calls  = a_func->WORK_LFUNCS + a_func->WORK_GFUNCS;
   x_graph  = a_func->WORK_NCURSE + a_func->WORK_OPENGL + a_func->WORK_WINDOW + a_func->WORK_MYX;
   x_read   = a_func->WORK_INPUT  + a_func->WORK_TREAD  + a_func->WORK_BREAD;
   x_write  = a_func->WORK_OUTPUT + a_func->WORK_TWRITE + a_func->WORK_BWRITE;
   x_memory = a_func->WORK_MEMORY;
   poly_cats__anatomy  (a_func->STATS_RTYPE, x_vars, x_calls, x_graph, x_read, x_write, x_memory, a_func->anatomy);
   return 0;
}

char
poly_cats_function      (tFUNC *a_func)
{
   poly_cats__complexity    (a_func, '-', 'y', NULL);
   poly_cats__integration   (a_func, '-', 'y', NULL);
   poly_cats__watchpoints   (a_func, '-', 'y', NULL);
   poly_cats_anatomy        (a_func);
   return 0;
}

char*        /*-> create category headers for reporting -------[ ´          ]-*/ /*-ågs#´·4á3··á···´8·8´5··´21B2·á·æ¬å8á17··´E·Eá······´···´····æ¬å·····´······´····´117·æ-*/
poly_cats_header        (int n, char *a_title, int a_curr, int a_total)
{
   int         i           =    0;
   int         m           =    0;
   char        x_len       =    0;
   char        t           [LEN_TERSE] = "";
   char        s           [LEN_TERSE] = "";
   strlcpy (s_print, "", LEN_RECD);
   if (n <= 0 || n > 7)  return s_print;
   if (n > 1) {
      strl4main (a_curr , t , 0, 'c', '-', LEN_TERSE);
      if (a_curr  == 0)  strlcpy (t, "·", LEN_TERSE);
      strl4main (a_total, s , 0, 'c', '-', LEN_TERSE);
      if (a_total == 0)  strlcpy (s, "·", LEN_TERSE);
      sprintf (s_print, "%-4.4s%7.7s %8.8s            ", a_title, t, s);
      /*> sprintf (s_print, "%-5.5s : %4d  %5d             ", a_title, a_curr, a_total);   <*/
   }
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
   poly_cats__complexity    (x_func, 'l', 'y', a);
   poly_cats__integration   (x_func, 'l', 'y', b);
   poly_cats__watchpoints   (x_func, 'l', 'y', c);
   poly_cats_anatomy        (a_func);
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
   poly_cats__complexity    (x_func, '-', 'y', a);
   poly_cats__integration   (x_func, '-', 'y', b);
   poly_cats__watchpoints   (x_func, '-', 'y', c);
   poly_cats_anatomy        (a_func);
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
   poly_cats__complexity    (x_func, 'l', 'y', a);
   poly_cats__integration   (x_func, 'l', 'y', b);
   poly_cats__watchpoints   (x_func, 'l', 'y', c);
   sprintf (a_out, "%s  %s %s %s ", r, a, b, c);
   /*> strldchg (a_out, '-', '·', LEN_RECD);                                          <*/
   if (a_func->type == '_')  strldchg (a_out, '-', ' ', LEN_RECD);
   else                      strldchg (a_out, '-', '·', LEN_RECD);
   poly_cats__complexity    (x_func, '-', 'y', a);
   poly_cats__integration   (x_func, '-', 'y', b);
   poly_cats__watchpoints   (x_func, '-', 'y', c);
   poly_cats_anatomy        (a_func);
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

char
poly_cats_by_index      (tFUNC *a_func, char n, char *a_grp, char *a_sub, char *a_name, char *a_desc, char *a_set)
{
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_func == NULL)          return rce;
   --rce;  if (n < 0)                   return rce;
   --rce;  if (n >= MAX_CATS)           return rce;
   --rce;  if (s_cats [n].grp < 0)      return rce;
   /*---(populate)-----------------------*/
   if (a_grp  != NULL)  *a_grp = s_cats [n].grp;
   if (a_sub  != NULL)  *a_sub = s_cats [n].sub;
   if (a_name != NULL)  strlcpy (a_name, s_cats [n].name, LEN_LABEL);
   if (a_desc != NULL)  strlcpy (a_desc, s_cats [n].desc, LEN_DESC);
   if (a_set  != NULL)  *a_set = a_func->stats [s_cats [n].n];
   /*---(complete)-----------------------*/
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
      poly_cats__complexity    (u, 'l', 'y', a);
      sprintf (unit_answer, "CATS complex(%2d) : %-17.17s %s [%s]", i, t, r, a);
   }
   else if   (strcmp (a_question, "integ"     )     == 0) {
      if (u != NULL)  sprintf  (t, "[%.15s]", u->name);
      poly_cats__single      (u, r);
      poly_cats__integration (u, 'l', 'y', b);
      sprintf (unit_answer, "CATS integ  (%2d) : %-17.17s %s [%s]", i, t, r, b);
   }
   else if   (strcmp (a_question, "watch"     )     == 0) {
      if (u != NULL)  sprintf  (t, "[%.15s]", u->name);
      poly_cats__single      (u, r);
      poly_cats__watchpoints (u, 'l', 'y', c);
      poly_cats_anatomy      (u);
      sprintf (unit_answer, "CATS watch  (%2d) : %-17.17s %s [%s]", i, t, r, c);
   }
   else if   (strcmp (a_question, "full"      )     == 0) {
      if (u != NULL)  sprintf  (t, "[%.15s]", u->name);
      poly_cats__single      (u, r);
      poly_cats__complexity    (u, '-', 'y', a);
      poly_cats__integration   (u, '-', 'y', b);
      poly_cats__watchpoints   (u, '-', 'y', c);
      poly_cats_anatomy      (u);
      sprintf (unit_answer, "CATS full   (%2d) : %-17.17s %s %s %s %s", i, t, r, a, b, c);
   }
   else if   (strcmp (a_question, "header"    )     == 0) {
      strlcpy (t, poly_cats_header (i, "test", 0, 0), LEN_RECD);
      sprintf (unit_answer, "CATS header (%2d) : %3d[%s]", i, strlen (t), t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


