/*============================----beg-of-source---============================*/
#include  "polymnia.h"




#define     MAX_POS     50
static struct cPOS    {
   char        grp;                         /* major groups of 11 stats       */
   char        sub;                         /* sub group for clarity          */
   char        pos;                         /* position in major group        */
   char        name        [LEN_LABEL];     /* short description              */
   char        desc        [LEN_LABEL];     /* longer description             */
   int         beg;                         /* short-cut to valid entries     */
   int         count;                       /* count of valid entries         */
} s_poss [MAX_POS] = {
   /*===[[ PREFIX ]]=============================================*/
   /*--  -123456-   -123456789012345678901234567890- */
   { 0, 0,  0, "one"   , "one line function"               , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP ONE -- COMPLEXITY ]]============================*/
   /*--  -123456-   -123456789012345678901234567890- */
   { 1, 1,  1, "scope" , "function scope"                  , 0, 0 },
   { 1, 1,  2, "rtype" , "return type"                     , 0, 0 },
   { 1, 1,  3, "params", "parameter count"                 , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   { 1, 2,  4, "total" , "total lines of any type"         , 0, 0 },
   { 1, 2,  5, "debug" , "debugging lines"                 , 0, 0 },
   { 1, 2,  6, "slocl" , "source lines of code logical"    , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   { 1, 3,  7, "locals", "number of local variables"       , 0, 0 },
   { 1, 3,  8, "choice", "number of choices/decisions"     , 0, 0 },
   { 1, 3,  9, "return", "number of return/exit points"    , 0, 0 },
   { 1, 3, 10, "indent", "depth of indentation"            , 0, 0 },
   { 1, 3, 11, "memory", "memory management used"          , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP TWO -- INTEGRATION ]]===========================*/
   /*--  -123456-   -123456789012345678901234567890- */
   { 2, 1,  1, "gcalls", "called by global functions"      , 0, 0 },
   { 2, 1,  2, "lcalls", "called by local functions"       , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   { 2, 2,  3, "funcs" , "calls to any/all functions"      , 0, 0 },
   { 2, 2,  4, "intern", "calls to internal functions"     , 0, 0 },
   { 2, 2,  5, "cstd"  , "calls to c-std libraries"        , 0, 0 },
   { 2, 2,  6, "ylib"  , "calls to my custom libraries"    , 0, 0 },
   { 2, 2,  7, "mystry", "calls to unknown libraries"      , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   { 2, 3,  8, "input" , "stdin and file input"            , 0, 0 },
   { 2, 3,  9, "output", "stdout and file output"          , 0, 0 },
   { 2, 3, 10, "system", "unix process or system calls"    , 0, 0 },
   { 2, 3, 11, "recurs", "function is recursive"           , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP THREE -- WATCH POINTS ]]========================*/
   /*--  -123456-   -123456789012345678901234567890- */
   { 3, 1,  1, "dstyle", "debugging style"                 , 0, 0 },
   { 3, 1,  2, "dmacro", "debugging macros used"           , 0, 0 },
   { 3, 1,  3, "dmatch", "debugging trouble checks"        , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   { 3, 2,  4, "ncurse", "ncurses function calls"          , 0, 0 },
   { 3, 2,  5, "opengl", "opengl function calls"           , 0, 0 },
   { 3, 2,  6, "window", "x11 and like functions calls"    , 0, 0 },
   { 3, 2,  7, "myx"   , "my x11/opengl support libs"      , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   { 3, 3,  8, "proto" , "prototype location"              , 0, 0 },
   { 3, 3,  9, "extern", "called by external programs"     , 0, 0 },
   { 3, 3, 10, "ptwo"  , "params use double pointers"      , 0, 0 },
   { 3, 3, 11, "pnum"  , "params use number pointers"      , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*--  -123456-   -123456789012345678901234567890- */
   { 0, 0,  0, ""      , ""                                , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
};
 


#define     MAX_LABELS  2000
struct cLABEL {
   char        grp;
   char        pos;
   char        value;
   char        desc        [LEN_TITLE];
} s_labels [MAX_LABELS] = {
   /*--   -   -123456789012345678901234567890- */
   { 1,  1, 'e', "extern (library)"               },
   { 1,  1, 'g', "global (program wide)"          },
   { 1,  1, 'f', "file (source file only)"        },
   { 1,  1, 's', "static (explicit static)"       },
   { 1,  1, 'u', "unit test (special global)"     },
   /*--   -   -123456789012345678901234567890- */
   { 1,  2, 's', "string (char*)"                 },
   { 1,  2, 'c', "character (char)"               },
   { 1,  2, 'v', "void (nothing)"                 },
   { 1,  2, 'p', "pointer (* of any type)"        },
   { 1,  2, 'n', "number (int or real)"           },
   /*--   -   -123456789012345678901234567890- */
   { 1,  3, '*', "none (dangerous)"               },
   { 1,  3, '0', "void (explicit none)"           },
   { 1,  3, '9', "explicit one to nine"           },
   { 1,  3, '#', "more than nine (wow)"           },
   /*--   -   -123456789012345678901234567890- */
   { 1,  4, '-', "no lines in function"           },
   { 1,  4, 'Z', "line scale by fives"            },
   { 1,  4, '#', "more than 180 lines"            },
   /*--   -   -123456789012345678901234567890- */
   { 1,  5, '-', "no debug lines in function"     },
   { 1,  5, 'Z', "debug line scale by fives"      },
   { 1,  5, '#', "more than 180 debug lines"      },
   /*--   -   -123456789012345678901234567890- */
   { 1,  6, '-', "no slocl lines in function"     },
   { 1,  6, 'Z', "slocl line scale by fives"      },
   { 1,  6, '#', "more than 180 slocl lines"      },
   /*--   -   -123456789012345678901234567890- */
   { 1,  7, '-', "no local variables"             },
   { 1,  7, 'z', "local variables on scale"       },
   { 1,  7, '#', "more than 36 local vars"        },
   /*--   -   -123456789012345678901234567890- */
   { 1,  8, '-', "no decision/choices"            },
   { 1,  8, 'z', "decisions on scale"             },
   { 1,  8, '#', "more than 36 decisions"         },
   /*--   -   -123456789012345678901234567890- */
   { 1,  9, '-', "no returns"                     },
   { 1,  9, 'z', "returns on scale"               },
   { 1,  9, '#', "more than 36 returns"           },
   /*--   -   -123456789012345678901234567890- */
   { 1, 10, '-', "no indentation"                 },
   { 1, 10, 'Z', "indents on scale by threes"     },
   { 1, 10, '#', "more than 36 indents"           },
   /*--   -   -123456789012345678901234567890- */
   { 1, 11, '-', "no dynamic memory mgmt"         },
   { 1, 11, '#', "uses malloc/free"               },
   /*--   -   -123456789012345678901234567890- */
   { 2,  8, '-', "no input"                       },
   { 2,  8, 'i', "stdin input"                    },
   { 2,  8, 'r', "text file input"                },
   { 2,  8, 'R', "binary file input (fread)"      },
   /*--   -   -123456789012345678901234567890- */
   { 2,  9, '-', "no output"                      },
   { 2,  9, 'o', "stdin output"                   },
   { 2,  9, 'w', "text file output"               },
   { 2,  9, 'W', "binary file output (fwrite)"    },
   /*--   -   -123456789012345678901234567890- */
   { 2, 10, '-', "no system access"               },
   { 2, 10, 'f', "filesystem access"              },
   { 2, 10, 'p', "process control"                },
   { 2, 10, 's', "linux system calls"             },
   { 2, 10, 'B', "both process/system calls"      },
   /*--   -   -123456789012345678901234567890- */
   { 2, 11, '-', "no recursion"                   },
   { 2, 11, '#', "recursive function"             },
   /*--   -   -123456789012345678901234567890- */
   { 0,  0,  0 , ""                               },
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
poly_cats_logic    (tTAG *a_tag, char a_type)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   switch (a_type) {
   case 'r' :
      IN_TAG  ++(a_tag->WORK_RETURN);
      break;
   case 'c' :
      IN_TAG  ++(a_tag->WORK_CHOICE);
      break;
   }
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

#define  IN_TAGLINES  if (a_tag != NULL && a_tag->work != NULL && a_tag->WORK_BEG >= 0 && a_tag->WORK_END < 0) 

char
poly_cats_lines    (tFILE *a_file, tTAG *a_tag, char a_type)
{
   int         c           =     0;
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   DEBUG_DATA   yLOG_spoint  (a_tag);
   if (a_tag == NULL) {
      DEBUG_DATA   yLOG_snote   ("tag null");
   } else {
      DEBUG_DATA   yLOG_spoint  (a_tag->work);
      if (a_tag->work == NULL) {
         DEBUG_DATA   yLOG_snote   ("tag->work null");
      } else {
         DEBUG_DATA   yLOG_sint    (a_tag->WORK_BEG);
         DEBUG_DATA   yLOG_sint    (a_tag->WORK_END);
      }
   }
   IN_TAGLINES  DEBUG_DATA   yLOG_snote   ("in_taglines");
   ++(my.COUNT_LINES);
   ++(a_file->COUNT_LINES);
   ++(a_file->proj->COUNT_LINES);
   IN_TAGLINES  ++(a_tag->COUNT_LINES);
   switch (a_type) {
   case 'D' :
      DEBUG_DATA   yLOG_snote   ("debug");
      ++(my.COUNT_DEBUG);
      ++(a_file->COUNT_DEBUG);
      ++(a_file->proj->COUNT_DEBUG);
      IN_TAGLINES  ++(a_tag->COUNT_DEBUG);
      break;
   case 'd' :
      DEBUG_DATA   yLOG_snote   ("docs");
      ++(my.COUNT_DOCS);
      ++(a_file->COUNT_DOCS);
      ++(a_file->proj->COUNT_DOCS);
      IN_TAGLINES  ++(a_tag->COUNT_DOCS );
      break;
   case 'e' :
      DEBUG_DATA   yLOG_snote   ("empty");
      ++(my.COUNT_EMPTY);
      ++(a_file->COUNT_EMPTY);
      ++(a_file->proj->COUNT_EMPTY);
      IN_TAGLINES  ++(a_tag->COUNT_EMPTY);
      break;
   case 'C' :
      DEBUG_DATA   yLOG_snote   ("code");
      ++(my.COUNT_CODE);
      ++(a_file->COUNT_CODE);
      ++(a_file->proj->COUNT_CODE);
      IN_TAGLINES  ++(a_tag->COUNT_CODE );
      c = strldcnt (my.s_curr, ';', LEN_RECD);
      DEBUG_DATA   yLOG_sint    (c);
      if (c < 0)  c = 0;
      DEBUG_DATA   yLOG_snote   ("slocl");
      my.COUNT_SLOCL += c;
      a_file->COUNT_SLOCL += c;
      a_file->proj->COUNT_SLOCL += c;
      IN_TAGLINES  a_tag->COUNT_SLOCL += c;
      break;
   }
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   creating the tag summary                   ----===*/
/*====================------------------------------------====================*/
static void  o___SUMMARY_________o () { return; }

char
poly_cats_debug    (tTAG *a_tag)
{
   /*---(style)--------------------------*/
   if      (a_tag->WORK_DLONG   > 0 && a_tag->WORK_DSHORT  > 0)  a_tag->STATS_DSTYLE = 'b';
   else if (a_tag->WORK_DLONG   > 0)                              a_tag->STATS_DSTYLE = 'l';
   else if (a_tag->WORK_DSHORT  > 0)                              a_tag->STATS_DSTYLE = 's';
   if (a_tag->WORK_DLONG + a_tag->WORK_DSHORT < a_tag->WORK_DCOUNT) {
      switch (a_tag->STATS_DSTYLE) {
      case 'b' :  a_tag->STATS_DSTYLE = 'B';  break;
      case 'l' :  a_tag->STATS_DSTYLE = 'L';  break;
      case 's' :  a_tag->STATS_DSTYLE = 'S';  break;
      default  :  a_tag->STATS_DSTYLE = 'f';  break;
      }
   }
   if (a_tag->WORK_DFREE > 0)  a_tag->STATS_DSTYLE = '#';
   if (strchr ("-f", a_tag->STATS_DSTYLE) != NULL)   return 0;
   /*---(match)--------------------------*/
   a_tag->STATS_DMATCH = '-';
   /*---(enters)-----------*/
   if      (a_tag->WORK_DENTER <= 0) 
      a_tag->STATS_DMATCH = 'E';
   else if (a_tag->WORK_DENTER == 1 && strchr ("ls", a_tag->STATS_DSTYLE) == NULL) 
      a_tag->STATS_DMATCH = 'E';
   else if (a_tag->WORK_DENTER == 2 && a_tag->STATS_DSTYLE != 'b') 
      a_tag->STATS_DMATCH = 'E';
   else if (a_tag->WORK_DENTER >  2)
      a_tag->STATS_DMATCH = 'E';
   if (a_tag->STATS_DMATCH != '-')   return 0;
   /*---(exits)------------*/
   if      (a_tag->WORK_DEXIT  <= 0)
      a_tag->STATS_DMATCH = 'X';
   else if (a_tag->WORK_RETURN != a_tag->WORK_DEXIT)
      a_tag->STATS_DMATCH = 'X';
   if (a_tag->STATS_DMATCH != '-')   return 0;
   /*---(shorts)-----------*/
   else if (a_tag->STATS_DSTYLE == 's' && a_tag->WORK_INTERN > 0)
      a_tag->STATS_DMATCH = '!';
   if (a_tag->STATS_DMATCH != '-')   return 0;
   /*---(good)-------------*/
   a_tag->STATS_DMATCH = 'y';
   if (a_tag->WORK_DENTER == 0 && a_tag->WORK_DEXIT == 0)
      a_tag->STATS_DMATCH = 'p'; 
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_cats_tagsumm  (tTAG *a_tag)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_tag"     , a_tag);
   --rce;  if (a_tag == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("->name"    , a_tag->name);
   DEBUG_DATA   yLOG_point   ("->work"    , a_tag->work);
   --rce;  if (a_tag->work == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(group one)----------------------*/
   DEBUG_DATA   yLOG_note    ("group one");
   poly_cats_scaled  ("lines"   , a_tag->COUNT_LINES , &a_tag->STATS_TOTAL, '-');
   poly_cats_scaled  ("debug"   , a_tag->COUNT_DEBUG , &a_tag->STATS_DEBUG, '-');
   poly_cats_scaled  ("slocl"   , a_tag->COUNT_SLOCL , &a_tag->STATS_SLOCL, '-');
   poly_cats_exact   ("locals"  , a_tag->WORK_LOCALS , &a_tag->STATS_LOCALS, '-');
   poly_cats_exact   ("choices" , a_tag->WORK_CHOICE , &a_tag->STATS_CHOICE, '-');
   poly_cats_exact   ("returns" , a_tag->WORK_RETURN , &a_tag->STATS_RETURN, '-');
   a_tag->WORK_INDENT  /= 3;
   a_tag->WORK_INDENT  -= 1;
   poly_cats_exact   ("indent"  , a_tag->WORK_INDENT , &a_tag->STATS_INDENT, '-');
   poly_cats_flag    ("memories", a_tag->WORK_MEMORY , &a_tag->STATS_MEMORY, '#');
   /*---(group two)----------------------*/
   DEBUG_DATA   yLOG_note    ("group two");
   poly_cats_exact   ("gcalls"  , a_tag->WORK_GCALLS , &a_tag->STATS_GCALLS, '-');
   poly_cats_exact   ("lcalls"  , a_tag->WORK_LCALLS , &a_tag->STATS_LCALLS, '-');
   poly_cats_exact   ("funcs"   , a_tag->WORK_FUNCS  , &a_tag->STATS_FUNCS, '-');
   poly_cats_exact   ("intern"  , a_tag->WORK_INTERN , &a_tag->STATS_INTERN, '-');
   poly_cats_exact   ("cstd"    , a_tag->WORK_CSTD   , &a_tag->STATS_CSTD, '-');
   poly_cats_exact   ("ylib"    , a_tag->WORK_YLIB   , &a_tag->STATS_YLIB, '-');
   a_tag->WORK_MYSTRY = a_tag->WORK_FUNCS - a_tag->WORK_INTERN - a_tag->WORK_CSTD - a_tag->WORK_YLIB - a_tag->WORK_NCURSE - a_tag->WORK_OPENGL;
   poly_cats_exact   ("mystry"  , a_tag->WORK_MYSTRY , &a_tag->STATS_MSTRY, '-');
   if (a_tag->WORK_INPUT  > 0)   a_tag->STATS_READ  = 'i';
   if (a_tag->WORK_READ   > 0)   a_tag->STATS_READ  = 'r';
   if (a_tag->WORK_BREAD  > 0)   a_tag->STATS_READ  = 'R';
   if (a_tag->WORK_OUTPUT > 0)   a_tag->STATS_WRITE = 'o';
   if (a_tag->WORK_WRITE  > 0)   a_tag->STATS_WRITE = 'w';
   if (a_tag->WORK_BWRITE > 0)   a_tag->STATS_WRITE = 'W';
   if (a_tag->WORK_PROCS > 0 && a_tag->WORK_SYSTEM  > 0)  a_tag->STATS_SYSTEM = 'B';
   else if (a_tag->WORK_PROCS   > 0)  a_tag->STATS_SYSTEM = 'p';
   else if (a_tag->WORK_SYSTEM  > 0)  a_tag->STATS_SYSTEM = 's';
   else if (a_tag->WORK_FILESYS > 0)  a_tag->STATS_SYSTEM = 'f';
   poly_cats_flag    ("recurse" , a_tag->WORK_RECURS , &a_tag->STATS_RECURS, '#');
   /*---(group three)--------------------*/
   DEBUG_DATA   yLOG_note    ("group three");
   poly_cats_debug (a_tag);
   poly_cats_exact   ("ncurses" , a_tag->WORK_NCURSE , &a_tag->STATS_NCURSE, '-');
   poly_cats_exact   ("opengl"  , a_tag->WORK_OPENGL  , &a_tag->STATS_OPENGL, '-');
   poly_cats_exact   ("myx"     , a_tag->WORK_MYX     , &a_tag->STATS_MYX   , '-');
   poly_cats_exact   ("window"  , a_tag->WORK_WINDOW  , &a_tag->STATS_WINDOW, '-');
   poly_cats_exact   ("ecalls"  , a_tag->WORK_ECALLS  , &a_tag->STATS_ECALLS, '-');
   /*---(type)---------------------------*/
   DEBUG_DATA   yLOG_note    ("group image");
   if      (strncmp (a_tag->name, "o___", 4) == 0)        strlcpy (a_tag->image, "-"     , LEN_LABEL);
   else if (strstr  (a_tag->name, "_init") != NULL)       strlcpy (a_tag->image, "shoot" , LEN_LABEL);
   else if (strstr  (a_tag->name, "_wrap") != NULL)       strlcpy (a_tag->image, "shoot" , LEN_LABEL);
   else if (a_tag->WORK_FUNCS == a_tag->WORK_CSTD + a_tag->WORK_YLIB)   strlcpy (a_tag->image, "leaf"  , LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
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
   char        t           [LEN_RECD] = "[]";
   tTAG       *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "CATS unit        : tag number unknown");
   if (i <  0)       return unit_answer;
   /*---(prepare)------------------------*/
   u = (tTAG *) poly_btree_entry (B_TAGS, i);
   if (u != NULL)  sprintf  (t, "[%.20s]", u->name);
   /*---(simple)-------------------------*/
   if        (strcmp (a_question, "complex"   )     == 0) {
      if (u != NULL) {
         snprintf (unit_answer, LEN_RECD, "CATS complex(%2d) : %-21.21s %c [%c%c%c.%c%c%c.%c%c%c%c%c]",
               i, t, u->STATS_SINGLE,
               u->STATS_SCOPE , u->STATS_RTYPE , u->STATS_PARAMS,
               u->STATS_TOTAL , u->STATS_DEBUG , u->STATS_SLOCL ,
               u->STATS_LOCALS, u->STATS_CHOICE, u->STATS_RETURN, u->STATS_INDENT, u->STATS_MEMORY);
      } else {
         snprintf (unit_answer, LEN_RECD, "CATS complex(%2d) : %-21.21s %c [%c%c%c.%c%c%c.%c%c%c%c%c]",
               i, t, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-');
      }
   }
   else if   (strcmp (a_question, "connect"   )     == 0) {
      if (u != NULL) {
         snprintf (unit_answer, LEN_RECD, "CATS connect(%2d) : %-21.21s %c [%c%c.%c%c%c%c%c.%c%c%c%c]",
               i, t, u->STATS_SINGLE,
               u->STATS_LCALLS, u->STATS_GCALLS,
               u->STATS_FUNCS, u->STATS_INTERN, u->STATS_CSTD  , u->STATS_YLIB  , u->STATS_MSTRY,
               u->STATS_READ , u->STATS_WRITE , u->STATS_SYSTEM, u->STATS_RECURS);
      } else {
         snprintf (unit_answer, LEN_RECD, "CATS connect(%2d) : %-21.21s %c [%c%c.%c%c%c%c%c.%c%c%c%c]",
               i, t, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-');
      }
   }
   else if   (strcmp (a_question, "future"    )     == 0) {
      if (u != NULL) {
         snprintf (unit_answer, LEN_RECD, "CATS future (%2d) : %-22.22s  [%c%c%c%c.%c%c%c.%c%c%c%c]",
               i, t, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-');
      } else {
         snprintf (unit_answer, LEN_RECD, "CATS future (%2d) : %-22.22s  [%c%c%c%c.%c%c%c.%c%c%c%c]",
               i, t, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-');
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



