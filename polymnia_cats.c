/*============================----beg-of-source---============================*/
#include  "polymnia.h"

/*> char         /+-> 123456789-123456789-123456789-12345 -[······.···.···.····] [····.·······.···.····] [···.······] +/   <*/

/*
 *  [······.···.···.····] [····.·······.···.····] [···.······]
 *
 *  scope
 *  r.type
 *  p.cnt  
 *  p.num
 *  p.two
 *  proto
 *
 *  total
 *  debug
 *  slocl
 *
 *  l.vars 
 *  f.vars
 *  g.vars
 *
 *  choice
 *  return
 *  indent
 *  memory
 *
 *
 *
 *  extern
 *  global
 *  local
 *  recurs
 *
 *  funcs
 *  local
 *  global
 *  cstd
 *  ylib
 *  other
 *  mystry
 *
 *  input
 *  output
 *  system
 *
 *  ncurse
 *  opengl
 *  myx
 *  window
 *
 *
 *
 *  dstyle
 *  dmacro
 *  dmatch
 *
 *
 *
 */


#define     MAX_CATS    50
static struct cPOS    {
   char        grp;                         /* major group                    */
   char        sub;                         /* sub group for clarity          */
   char        pos;                         /* position in major group        */
   char        name        [LEN_LABEL];     /* short description              */
   char        desc        [LEN_LABEL];     /* longer description             */
   int         beg;                         /* short-cut to valid entries     */
   int         count;                       /* count of valid entries         */
} s_cats [MAX_CATS] = {
   /*===[[ PREFIX ]]=============================================*/
   /*--  -123456-   -123456789012345678901234567890- */
   {  0,  1,  0, "oneline", "one line function"               , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP ONE -- COMPLEXITY ]]============================*/
   {  1,  0,  0, "-----"  , "complexity"                      , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  1,  1, "scope"  , "function scope"                  , 0, 0 },
   {  1,  1,  2, "rtype"  , "return type"                     , 0, 0 },
   {  1,  1,  3, "nparam" , "number of parameters"            , 0, 0 },
   {  1,  1,  4, "pnum"   , "params use number pointers"      , 0, 0 },
   {  1,  1,  5, "ptwo"   , "params use double pointers"      , 0, 0 },
   {  1,  1,  6, "proto"  , "prototype location"              , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  2,  7, "total"  , "total lines of any type"         , 0, 0 },
   {  1,  2,  8, "debug"  , "debugging lines"                 , 0, 0 },
   {  1,  2,  9, "slocl"  , "source lines of code logical"    , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  3, 10, "Lvars"  , "number of local vars used"       , 0, 0 },
   {  1,  3, 11, "Fvars"  , "number of file vars used"        , 0, 0 },
   {  1,  3, 12, "Gvars"  , "number of global vars used"      , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  1,  4, 13, "choice" , "number of choices/decisions"     , 0, 0 },
   {  1,  4, 14, "return" , "number of return/exit points"    , 0, 0 },
   {  1,  4, 15, "indent" , "depth of indentation"            , 0, 0 },
   {  1,  4, 16, "memory" , "memory management used"          , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP TWO -- INTEGRATION ]]===========================*/
   {  2,  0,  0, "-----"  , "integration"                     , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  1,  1, "Fcalls" , "called by local functions"       , 0, 0 },
   {  2,  1,  2, "Gcalls" , "called by global functions"      , 0, 0 },
   {  3,  1,  3, "Xcalls" , "called by external programs"     , 0, 0 },
   {  2,  1,  4, "recurse", "function is recursive"           , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  2,  5, "funcs"  , "calls to any/all functions"      , 0, 0 },
   {  2,  2,  6, "Dfuncs" , "calls to debugging functions"    , 0, 0 },
   {  2,  2,  7, "Ffuncs" , "calls to local functions"        , 0, 0 },
   {  2,  2,  8, "Gfuncs" , "calls to global functions"       , 0, 0 },
   {  2,  2,  9, "cstd"   , "calls to c-std libraries"        , 0, 0 },
   {  2,  2, 10, "ylib"   , "calls to my custom libraries"    , 0, 0 },
   {  2,  2, 11, "Ofuncs" , "calls to other libraries"        , 0, 0 },
   {  2,  2, 12, "mystry" , "calls to unknown functions"      , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  3, 13, "input"  , "stdin and file input"            , 0, 0 },
   {  2,  3, 14, "output" , "stdout and file output"          , 0, 0 },
   {  2,  3, 15, "system" , "unix process or system calls"    , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  2,  4, 16, "ncurses", "ncurses function calls"          , 0, 0 },
   {  2,  4, 17, "opengl" , "opengl function calls"           , 0, 0 },
   {  2,  4, 18, "windows", "x11 and like functions calls"    , 0, 0 },
   {  2,  4, 19, "myx"    , "my x11/opengl support libs"      , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*===[[ GROUP THREE -- WATCH POINTS ]]========================*/
   {  3,  0,  0, "-----"  , "watch-points"                    , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  3,  1,  1, "Dstyle" , "debugging style"                 , 0, 0 },
   {  3,  1,  2, "Dmacro" , "debugging macros used"           , 0, 0 },
   {  3,  1,  3, "Dmatch" , "debugging trouble checks"        , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */
   {  3,  2,  4, "-"      , ""                                , 0, 0 },
   {  3,  2,  5, "-"      , ""                                , 0, 0 },
   {  3,  2,  6, "-"      , ""                                , 0, 0 },
   {  3,  2,  7, "-"      , ""                                , 0, 0 },
   {  3,  2,  8, "-"      , ""                                , 0, 0 },
   {  3,  2,  9, "-"      , ""                                , 0, 0 },
   /*--  -123456-   -123456789012345678901234567890- */

   /*--  -123456-   -123456789012345678901234567890- */
   { -1, -1, -1, ""       , ""                                , 0, 0 },
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
poly_cats_logic    (tFUNC *a_tag, char a_type)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   switch (a_type) {
   case 'r' :
      IN_TAG  ++(a_tag->WORK_RETURN);
      break;
   case 'c' :
      IN_TAG  ++(a_tag->WORK_CHOICE);
      break;
   case 'C' :
      IN_TAG  ++(a_tag->WORK_CHOICE);
      a_tag->file->COUNT_SLOCL -= 2;
      a_tag->file->proj->COUNT_SLOCL -= 2;
      IN_TAG  (a_tag->COUNT_SLOCL) -= 2;
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
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   poly_cats_scaled  ("lines"   , a_func->COUNT_LINES, &a_func->STATS_TOTAL , '-');
   poly_cats_scaled  ("debug"   , a_func->COUNT_DEBUG, &a_func->STATS_DEBUG , '-');
   poly_cats_scaled  ("slocl"   , a_func->COUNT_SLOCL, &a_func->STATS_SLOCL , '-');
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
   poly_cats_exact   ("returns" , a_func->WORK_RETURN, &a_func->STATS_RETURN, '-');
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
   char       *x_norm      = "[%c%c%c%c%c%c.%c%c%c.%c%c%c.%c%c%c%c]";
   char       *x_long      = " %c %c %c %c %c %c  %c %c %c  %c %c %c  %c %c %c %c ";
   char       *p           = x_norm;
   if (a_style == 'l')  p = x_long;
   --rce;  if (a_func == NULL) {
      if (a_out != NULL)
         sprintf (a_out, p,
               '-', '-', '-', '-', '-', '-',
               '-', '-', '-',
               '-', '-', '-',
               '-', '-', '-', '-');
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
         a_func->STATS_CHOICE, a_func->STATS_RETURN,
         a_func->STATS_INDENT, a_func->STATS_MEMORY);
   return 0;
}

char
poly_cats__group_2a     (tFUNC *a_func)
{
   char        rce         =    0;
   --rce;  if (a_func       == NULL)  return rce;
   --rce;  if (a_func->work == NULL)  return rce;
   poly_cats_exact   ("lcalls"  , a_func->WORK_LCALLS, &a_func->STATS_LCALLS, '-');
   poly_cats_exact   ("gcalls"  , a_func->WORK_GCALLS, &a_func->STATS_GCALLS, '-');
   poly_cats_exact   ("ecalls"  , a_func->WORK_ECALLS, &a_func->STATS_ECALLS, '-');
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
   if (a_func->WORK_READ   > 0)   a_func->STATS_READ  = 'r';
   if (a_func->WORK_BREAD  > 0)   a_func->STATS_READ  = 'R';
   if (a_func->WORK_OUTPUT > 0)   a_func->STATS_WRITE = 'o';
   if (a_func->WORK_WRITE  > 0)   a_func->STATS_WRITE = 'w';
   if (a_func->WORK_BWRITE > 0)   a_func->STATS_WRITE = 'W';
   if (a_func->WORK_PROCS > 0 && a_func->WORK_SYSTEM  > 0)  a_func->STATS_SYSTEM = 'B';
   else if (a_func->WORK_PROCS   > 0)  a_func->STATS_SYSTEM = 'p';
   else if (a_func->WORK_SYSTEM  > 0)  a_func->STATS_SYSTEM = 's';
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
   char       *x_norm      = "[%c%c%c%c.%c%c%c%c%c%c%c%c.%c%c%c.%c%c%c%c]";
   char       *x_long      = " %c %c %c %c  %c %c %c %c %c %c %c %c  %c %c %c  %c %c %c %c ";
   char       *p           = x_norm;
   if (a_style == 'l')  p = x_long;
   --rce;  if (a_func == NULL) {
      if (a_out != NULL) {
         sprintf (a_out, p,
               '-', '-', '-', '-',
               '-', '-', '-', '-', '-', '-', '-', '-',
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
         a_func->STATS_LCALLS, a_func->STATS_GCALLS,
         a_func->STATS_ECALLS, a_func->STATS_RECURS,
         a_func->STATS_FUNCS , a_func->STATS_DFUNCS,
         a_func->STATS_LFUNCS, a_func->STATS_GFUNCS,
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
   /*---(unguarded logging)--------------*/
   if (a_func->WORK_DFREE > 0)  a_func->STATS_DMACRO = '#';
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
   if (a_func->STATS_DMATCH != '-')   return 0;
   /*---(find exit troubles)-------------*/
   if      (a_func->WORK_DEXIT  <= 0)
      a_func->STATS_DMATCH = 'X';
   else if (a_func->WORK_RETURN != a_func->WORK_DEXIT)
      a_func->STATS_DMATCH = 'x';
   if (a_func->STATS_DMATCH != '-')   return 0;
   /*---(find short troubles)------------*/
   if (a_func->STATS_DSTYLE == 's' && a_func->WORK_GFUNCS > 0)
      a_func->STATS_DMATCH = '?';
   if (a_func->STATS_DSTYLE == 's' && a_func->WORK_YLIB   > 0)
      a_func->STATS_DMATCH = '!';
   if (a_func->STATS_DMATCH != '-')   return 0;
   /*---(final judgement)----------------*/
   a_func->STATS_DMATCH = 'y';
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_cats__watchpoints  (char a_style, tFUNC *a_func, char a_update, char *a_out)
{
   char        rce         =    0;
   char       *x_norm      = "[%c%c%c.%c%c%c%c%c%c]";
   char       *x_long      = " %c %c %c  %c %c %c %c %c %c ";
   char       *p           = x_norm;
   if (a_style == 'l')  p = x_long;
   --rce;  if (a_func == NULL) {
      if (a_out != NULL) {
         sprintf (a_out, p,
               '-', '-', '-',
               '-', '-', '-', '-', '-', '-');
      }
      return rce;
   }
   if (a_func->work != NULL && a_update == 'y') {
      poly_cats__group_3a (a_func);
   }
   --rce;  if (a_out  == NULL)  return rce;
   sprintf (a_out, p,
         a_func->STATS_DSTYLE, a_func->STATS_DMACRO, a_func->STATS_DMATCH,
         '-', '-', '-', '-', '-', '-');
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

/*> char                                                                                           <* 
 *> poly_cats_debug    (tFUNC *a_tag)                                                              <* 
 *> {                                                                                              <* 
 *>    /+---(style)--------------------------+/                                                    <* 
 *>    if      (a_tag->WORK_DLONG   > 0 && a_tag->WORK_DSHORT  > 0)   a_tag->STATS_DSTYLE = 'b';   <* 
 *>    else if (a_tag->WORK_DLONG   > 0)                              a_tag->STATS_DSTYLE = 'l';   <* 
 *>    else if (a_tag->WORK_DSHORT  > 0)                              a_tag->STATS_DSTYLE = 's';   <* 
 *>    if (a_tag->WORK_DLONG + a_tag->WORK_DSHORT < a_tag->WORK_DCOUNT) {                          <* 
 *>       switch (a_tag->STATS_DSTYLE) {                                                           <* 
 *>       case 'b' :  a_tag->STATS_DSTYLE = 'B';  break;                                           <* 
 *>       case 'l' :  a_tag->STATS_DSTYLE = 'L';  break;                                           <* 
 *>       case 's' :  a_tag->STATS_DSTYLE = 'S';  break;                                           <* 
 *>       default  :  a_tag->STATS_DSTYLE = 'f';  break;                                           <* 
 *>       }                                                                                        <* 
 *>    }                                                                                           <* 
 *>    if (a_tag->WORK_DFREE > 0)  a_tag->STATS_DSTYLE = '#';                                      <* 
 *>    if (strchr ("-f", a_tag->STATS_DSTYLE) != NULL)   return 0;                                 <* 
 *>    /+---(match)--------------------------+/                                                    <* 
 *>    a_tag->STATS_DMATCH = '-';                                                                  <* 
 *>    /+---(enters)-----------+/                                                                  <* 
 *>    if      (a_tag->WORK_DENTER <= 0)                                                           <* 
 *>       a_tag->STATS_DMATCH = 'E';                                                               <* 
 *>    else if (a_tag->WORK_DENTER == 1 && strchr ("ls", a_tag->STATS_DSTYLE) == NULL)             <* 
 *>       a_tag->STATS_DMATCH = 'E';                                                               <* 
 *>    else if (a_tag->WORK_DENTER == 2 && a_tag->STATS_DSTYLE != 'b')                             <* 
 *>       a_tag->STATS_DMATCH = 'E';                                                               <* 
 *>    else if (a_tag->WORK_DENTER >  2)                                                           <* 
 *>       a_tag->STATS_DMATCH = 'E';                                                               <* 
 *>    if (a_tag->STATS_DMATCH != '-')   return 0;                                                 <* 
 *>    /+---(exits)------------+/                                                                  <* 
 *>    if      (a_tag->WORK_DEXIT  <= 0)                                                           <* 
 *>       a_tag->STATS_DMATCH = 'X';                                                               <* 
 *>    else if (a_tag->WORK_RETURN != a_tag->WORK_DEXIT)                                           <* 
 *>       a_tag->STATS_DMATCH = 'X';                                                               <* 
 *>    if (a_tag->STATS_DMATCH != '-')   return 0;                                                 <* 
 *>    /+---(shorts)-----------+/                                                                  <* 
 *>    else if (a_tag->STATS_DSTYLE == 's' && a_tag->WORK_GFUNCS > 0)                              <* 
 *>       a_tag->STATS_DMATCH = '!';                                                               <* 
 *>    if (a_tag->STATS_DMATCH != '-')   return 0;                                                 <* 
 *>    /+---(good)-------------+/                                                                  <* 
 *>    a_tag->STATS_DMATCH = 'y';                                                                  <* 
 *>    if (a_tag->WORK_DENTER == 0 && a_tag->WORK_DEXIT == 0)                                      <* 
 *>       a_tag->STATS_DMATCH = 'p';                                                               <* 
 *>    /+---(complete)-----------------------+/                                                    <* 
 *>    return 0;                                                                                   <* 
 *> }                                                                                              <*/

/*> char                                                                                                                                              <* 
 *> poly_cats_tagsumm  (tFUNC *a_tag)                                                                                                                 <* 
 *> {                                                                                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                       <* 
 *>    char        rce         =    0;                                                                                                                <* 
 *>    /+---(header)-------------------------+/                                                                                                       <* 
 *>    DEBUG_DATA   yLOG_enter   (__FUNCTION__);                                                                                                      <* 
 *>    /+---(defense)------------------------+/                                                                                                       <* 
 *>    DEBUG_DATA   yLOG_point   ("a_tag"     , a_tag);                                                                                               <* 
 *>    --rce;  if (a_tag == NULL) {                                                                                                                   <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                                                                              <* 
 *>       return rce;                                                                                                                                 <* 
 *>    }                                                                                                                                              <* 
 *>    DEBUG_DATA   yLOG_info    ("->name"    , a_tag->name);                                                                                         <* 
 *>    DEBUG_DATA   yLOG_point   ("->work"    , a_tag->work);                                                                                         <* 
 *>    --rce;  if (a_tag->work == NULL) {                                                                                                             <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                                                                              <* 
 *>       return rce;                                                                                                                                 <* 
 *>    }                                                                                                                                              <* 
 *>    /+---(group one)----------------------+/                                                                                                       <* 
 *>    DEBUG_DATA   yLOG_note    ("group one");                                                                                                       <* 
 *>    poly_cats_scaled  ("lines"   , a_tag->COUNT_LINES , &a_tag->STATS_TOTAL, '-');                                                                 <* 
 *>    poly_cats_scaled  ("debug"   , a_tag->COUNT_DEBUG , &a_tag->STATS_DEBUG, '-');                                                                 <* 
 *>    poly_cats_scaled  ("slocl"   , a_tag->COUNT_SLOCL , &a_tag->STATS_SLOCL, '-');                                                                 <* 
 *>    poly_cats_exact   ("locals"  , a_tag->WORK_LVARS  , &a_tag->STATS_LVARS , '-');                                                                <* 
 *>    poly_cats_exact   ("choices" , a_tag->WORK_CHOICE , &a_tag->STATS_CHOICE, '-');                                                                <* 
 *>    poly_cats_exact   ("returns" , a_tag->WORK_RETURN , &a_tag->STATS_RETURN, '-');                                                                <* 
 *>    a_tag->WORK_INDENT  /= 3;                                                                                                                      <* 
 *>    a_tag->WORK_INDENT  -= 1;                                                                                                                      <* 
 *>    poly_cats_exact   ("indent"  , a_tag->WORK_INDENT , &a_tag->STATS_INDENT, '-');                                                                <* 
 *>    poly_cats_flag    ("memories", a_tag->WORK_MEMORY , &a_tag->STATS_MEMORY, '#');                                                                <* 
 *>    /+---(group two)----------------------+/                                                                                                       <* 
 *>    DEBUG_DATA   yLOG_note    ("group two");                                                                                                       <* 
 *>    poly_cats_exact   ("gcalls"  , a_tag->WORK_GCALLS , &a_tag->STATS_GCALLS, '-');                                                                <* 
 *>    poly_cats_exact   ("lcalls"  , a_tag->WORK_LCALLS , &a_tag->STATS_LCALLS, '-');                                                                <* 
 *>    poly_cats_exact   ("funcs"   , a_tag->WORK_FUNCS  , &a_tag->STATS_FUNCS, '-');                                                                 <* 
 *>    poly_cats_exact   ("global"  , a_tag->WORK_GFUNCS , &a_tag->STATS_GFUNCS, '-');                                                                <* 
 *>    poly_cats_exact   ("local"   , a_tag->WORK_LFUNCS , &a_tag->STATS_LFUNCS, '-');                                                                <* 
 *>    poly_cats_exact   ("cstd"    , a_tag->WORK_CSTD   , &a_tag->STATS_CSTD, '-');                                                                  <* 
 *>    poly_cats_exact   ("ylib"    , a_tag->WORK_YLIB   , &a_tag->STATS_YLIB, '-');                                                                  <* 
 *>    a_tag->WORK_MYSTRY = a_tag->WORK_FUNCS - a_tag->WORK_GFUNCS - a_tag->WORK_CSTD - a_tag->WORK_YLIB - a_tag->WORK_NCURSE - a_tag->WORK_OPENGL;   <* 
 *>    poly_cats_exact   ("mystry"  , a_tag->WORK_MYSTRY , &a_tag->STATS_MYSTRY, '-');                                                                <* 
 *>    if (a_tag->WORK_INPUT  > 0)   a_tag->STATS_READ  = 'i';                                                                                        <* 
 *>    if (a_tag->WORK_READ   > 0)   a_tag->STATS_READ  = 'r';                                                                                        <* 
 *>    if (a_tag->WORK_BREAD  > 0)   a_tag->STATS_READ  = 'R';                                                                                        <* 
 *>    if (a_tag->WORK_OUTPUT > 0)   a_tag->STATS_WRITE = 'o';                                                                                        <* 
 *>    if (a_tag->WORK_WRITE  > 0)   a_tag->STATS_WRITE = 'w';                                                                                        <* 
 *>    if (a_tag->WORK_BWRITE > 0)   a_tag->STATS_WRITE = 'W';                                                                                        <* 
 *>    if (a_tag->WORK_PROCS > 0 && a_tag->WORK_SYSTEM  > 0)  a_tag->STATS_SYSTEM = 'B';                                                              <* 
 *>    else if (a_tag->WORK_PROCS   > 0)  a_tag->STATS_SYSTEM = 'p';                                                                                  <* 
 *>    else if (a_tag->WORK_SYSTEM  > 0)  a_tag->STATS_SYSTEM = 's';                                                                                  <* 
 *>    else if (a_tag->WORK_FILESYS > 0)  a_tag->STATS_SYSTEM = 'f';                                                                                  <* 
 *>    poly_cats_flag    ("recurse" , a_tag->WORK_RECURS , &a_tag->STATS_RECURS, '#');                                                                <* 
 *>    /+---(group three)--------------------+/                                                                                                       <* 
 *>    DEBUG_DATA   yLOG_note    ("group three");                                                                                                     <* 
 *>    poly_cats_debug (a_tag);                                                                                                                       <* 
 *>    poly_cats_exact   ("ncurses" , a_tag->WORK_NCURSE , &a_tag->STATS_NCURSE, '-');                                                                <* 
 *>    poly_cats_exact   ("opengl"  , a_tag->WORK_OPENGL  , &a_tag->STATS_OPENGL, '-');                                                               <* 
 *>    poly_cats_exact   ("myx"     , a_tag->WORK_MYX     , &a_tag->STATS_MYX   , '-');                                                               <* 
 *>    poly_cats_exact   ("window"  , a_tag->WORK_WINDOW  , &a_tag->STATS_WINDOW, '-');                                                               <* 
 *>    poly_cats_exact   ("ecalls"  , a_tag->WORK_ECALLS  , &a_tag->STATS_ECALLS, '-');                                                               <* 
 *>    /+---(complete)-----------------------+/                                                                                                       <* 
 *>    DEBUG_DATA   yLOG_exit    (__FUNCTION__);                                                                                                      <* 
 *>    return 0;                                                                                                                                      <* 
 *> }                                                                                                                                                 <*/



/*====================------------------------------------====================*/
/*===----                      reporting support                       ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTING_______o () { return; }

char*
poly_cats_header        (int n, char *a_out)
{
   int         i           =    0;
   int         m           =    0;
   char        x_len       =    0;
   char        t           [LEN_RECD]  = "";
   char        s           [LEN_TERSE] = "";
   strlcpy (a_out, "", LEN_RECD);
   if (n == 0) {
      sprintf (a_out, "   [------------complexity------------] [---------------integration--------------] [---watch-points---]  [----complexity-----] [-----integration------] [---watch--]");
   } else {
      for (i = 0; i < MAX_CATS; ++i) {
         /*---(end-of-data)-----------------*/
         if (s_cats [i].grp <  0)  break;
         /*---(group break)-----------------*/
         if (s_cats [i].sub == 0) {
            strlcat (a_out, " ", LEN_RECD);
            continue;
         }
         /*---(subgroup break)--------------*/
         if (i > 0 && s_cats [i - 1].sub != s_cats [i].sub) {
            strlcat (a_out, " ", LEN_RECD);
         }
         /*---(vertical strip)--------------*/
         x_len = strlen (s_cats [i].name);
         m = x_len - n;
         if      (n > 7) sprintf (s, "  ");
         else if (m < 0) sprintf (s, "  ");
         else            sprintf (s, "%c ", s_cats [i].name [m]);
         strlcat (a_out, s, LEN_RECD);
         /*---(done)------------------------*/
      }
      if (n == 1)  strlcat (a_out, "  ----------------as-presented-in-source-code----------------", LEN_RECD);
      else         strlcat (a_out, "                                                             ", LEN_RECD);
   }
   return a_out;
}

char*
poly_cats_full          (tFUNC *a_func, char *a_out)
{
   char        t           [LEN_RECD]  = "";
   char        a           [LEN_RECD]  = "";
   char        b           [LEN_RECD]  = "";
   char        c           [LEN_RECD]  = "";
   char        r           [LEN_TERSE] = "";
   poly_cats__single      (a_func, r);
   if (a_func->type == '_') {
      sprintf (a_out, "%s   · · · · · ·  · · ·  · · ·  · · · ·   · · · ·  · · · · · · · ·  · · ·  · · · ·   · · ·  · · · · · ·    ······ ··· ··· ····   ···· ········ ··· ····   ··· ······  ", r);
      return a_out;
   }
   poly_cats__complexity  ('l', a_func, 'y', a);
   poly_cats__integration ('l', a_func, 'y', b);
   poly_cats__watchpoints ('l', a_func, 'y', c);
   sprintf (a_out, "%s  %s %s %s ", r, a, b, c);
   strldchg (a_out, '-', '·', LEN_RECD);
   poly_cats__complexity  ('-', a_func, 'y', a);
   poly_cats__integration ('-', a_func, 'y', b);
   poly_cats__watchpoints ('-', a_func, 'y', c);
   sprintf (t    , " %s %s %s ", a, b, c);
   strlcat (a_out, t, LEN_RECD);
   return a_out;
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
   u = (tFUNC *) poly_btree_entry (B_FUNCS, i);
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
      poly_cats_header (i, t);
      sprintf (unit_answer, "CATS header (%2d) : %3d[%s]", i, strlen (t), t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


