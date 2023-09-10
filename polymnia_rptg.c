/*============================----beg-of-source---============================*/
#include  "polymnia.h"


/*
 *  report list
 *     htags             -- specific htag report generation
 *     project           -- single project detail
 *     projects          -- big inventory of stats
 *     project files     -- files with stats
 *     function          -- single function detail
 *     functions         -- file/functions in a particular proj
 *     ylib              -- all proj/file/func connections for a ylib
 *     project ylibs     -- all proj/ylib connects by file and function (for hyleoroi usage)
 *     world             -- all lines in world file and /home/system exceptions (not registered)
 *
 *
 */


static char     s_prefix     [LEN_LABEL];
static int      s_projs     =    0;
static int      s_files     =    0;
static int      s_funcs     =    0;
static int      s_ylibs     =    0;
static int      s_lines     =    0;
static int      s_empty     =    0;
static int      s_debug     =    0;
static int      s_docs      =    0;
static int      s_code      =    0;
static int      s_slocl     =    0;
static int      s_text      =    0;
static int      s_data      =    0;
static int      s_bss       =    0;
static int      s_memory    =    0;

#define    POLY_REPORT   'r'
#define    POLY_FORMAT   'f'
#define    POLY_DUMP     'd'
#define    POLY_NADA     '-'

static char     s_opt       = POLY_NADA;
static char     s_name      [LEN_LABEL] = "";;
static char     s_desc      [LEN_HUND]  = "";;
static char     s_options   [LEN_TERSE] = "";;

struct {
   char        name        [LEN_LABEL];
   char        scope;
   char        options     [LEN_TERSE];
   char        desc        [LEN_HUND];
} static const s_reports [] = {
   { "projects"        , POLY_PROJ , "p---"      , "main project inventory with summary statistics"     },
   { "oneline"         , POLY_PROJ , "o---"      , ""                           },
   { "files"           , POLY_FILE , "Ta--"      , "single project files inventory with statistics"     },
   { "ylibs"           , POLY_YLIB , "Ta--"      , "single project files inventory with statistics"     },
   { "externs"         , POLY_EXTS , "Ta--"      , "single project files inventory with statistics"     },
   { "function"        , POLY_FUNC , "Ta--"      , "single function details"                            },
   { ""                , -1        , ""          , ""                           },
};

char
poly_rptg_lookup        (char *a_option)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*> printf ("lookup å%sæ\n", a_option);                                            <*/
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_info    ("run_file"  , my.run_file);
   /*---(defaults)-----------------------*/
   s_opt = POLY_NADA;
   ystrlcpy (s_name   , ""    , LEN_LABEL);
   ystrlcpy (s_desc   , ""    , LEN_HUND);
   ystrlcpy (s_options, "····", LEN_TERSE);
   /*---(walk)---------------------------*/
   while (s_reports [i].scope >= 0) {
      /*> printf ("trying %2d, %s (%s)\n", i, s_reports [i].name, s_reports [i].desc);   <*/
      /*---(identify)--------------------*/
      if      (strcmp (a_option, s_reports [i].name) == 0)                                      s_opt = POLY_REPORT;
      else if (a_option [0] == POLY_REPORT && strcmp (a_option + 1, s_reports [i].name) == 0)   s_opt = POLY_REPORT;
      else if (a_option [0] == POLY_FORMAT && strcmp (a_option + 1, s_reports [i].name) == 0)   s_opt = POLY_FORMAT;
      else if (a_option [0] == POLY_DUMP   && strcmp (a_option + 1, s_reports [i].name) == 0)   s_opt = POLY_DUMP;
      /*---(handle)----------------------*/
      if  (s_opt != POLY_NADA) {
         ystrlcpy (s_name   , s_reports [i].name    , LEN_LABEL);
         ystrlcpy (s_desc   , s_reports [i].desc    , LEN_HUND);
         ystrlcpy (s_options, s_reports [i].options , LEN_TERSE);
         my.g_mode  = POLY_RPTG;
         my.g_scope = s_reports [i].scope;
         my.g_rptg  = s_reports [i].options [0];
         DEBUG_OUTP   yLOG_info    ("s_name"    , s_name);
         DEBUG_OUTP   yLOG_info    ("s_desc"    , s_desc);
         DEBUG_OUTP   yLOG_info    ("s_options" , s_options);
         DEBUG_OUTP   yLOG_char    ("g_mode"    , my.g_mode);
         DEBUG_OUTP   yLOG_char    ("g_scope"   , my.g_scope);
         DEBUG_OUTP   yLOG_char    ("g_rptg"    , my.g_rptg);
         /*> printf ("FOUND  %c, %c, %c\n", my.g_mode, my.g_scope, my.g_rptg);        <*/
         return 1;
      }
      /*---(next)------------------------*/
      ++i;
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_rptg__prep         (void)
{
   s_projs = s_files = s_funcs = s_ylibs = 0;
   s_lines = s_empty = s_debug = s_docs  = s_code  = s_slocl = 0;
   s_memory = 0;
   return 0;
}

char
poly_rptg__proj_inc     (tPROJ *a_proj)
{
   ++s_projs;
   s_files  += a_proj->COUNT_FILES;
   s_funcs  += a_proj->COUNT_FUNCS;
   s_ylibs  += a_proj->COUNT_YLIBS;
   s_lines  += a_proj->COUNT_LINES;
   s_empty  += a_proj->COUNT_EMPTY;
   s_debug  += a_proj->COUNT_DEBUG;
   s_docs   += a_proj->COUNT_DOCS;
   s_code   += a_proj->COUNT_CODE;
   s_slocl  += a_proj->COUNT_SLOCL;
   if (a_proj->COUNT_TEXT > 0) {
      s_text   += a_proj->COUNT_TEXT;
      s_data   += a_proj->COUNT_DATA;
      s_bss    += a_proj->COUNT_BSS;
      ++s_memory;
   }
   return 0;
}

char
poly_rptg__file_inc     (tFILE *a_file)
{
   s_projs   = 1;
   ++s_files;
   s_funcs  += a_file->COUNT_FUNCS;
   s_ylibs  += a_file->COUNT_YLIBS;
   s_lines  += a_file->COUNT_LINES;
   s_empty  += a_file->COUNT_EMPTY;
   s_debug  += a_file->COUNT_DEBUG;
   s_docs   += a_file->COUNT_DOCS;
   s_code   += a_file->COUNT_CODE;
   s_slocl  += a_file->COUNT_SLOCL;
   if (a_file->COUNT_TEXT > 0) {
      s_text   += a_file->COUNT_TEXT;
      s_data   += a_file->COUNT_DATA;
      s_bss    += a_file->COUNT_BSS;
      ++s_memory;
   }
   return 0;
}

char
poly_rptg__total   (char a_level)
{
   int         a           = 0;
   int         b           = 0;
   char        t           [LEN_HUND]  = "";
   char        x_projs     [LEN_TERSE] = "";
   char        x_files     [LEN_TERSE] = "";
   char        x_funcs     [LEN_TERSE] = "";
   char        x_ylibs     [LEN_TERSE] = "";
   char        x_lines     [LEN_TERSE] = "";
   char        x_empty     [LEN_TERSE] = "";
   char        x_docs      [LEN_TERSE] = "";
   char        x_debug     [LEN_TERSE] = "";
   char        x_code      [LEN_TERSE] = "";
   char        x_slocl     [LEN_TERSE] = "";
   char        x_text      [LEN_TERSE] = "";
   char        x_data      [LEN_TERSE] = "";
   char        x_bss       [LEN_TERSE] = "";
   if      (a_level == 'p')  ystrlcpy (t, "", LEN_HUND);
   else if (a_level == 'f')  ystrlcpy (t, "                    ", LEN_HUND);
   /*> s_projs  = ySORT_count (B_PROJ );                                         <* 
    *> s_files  = ySORT_count (B_FILES);                                         <* 
    *> s_funcs  = poly_func_count  ();                                                <*/
   ystrl4main (s_projs, x_projs, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_files, x_files, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_funcs, x_funcs, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_ylibs, x_ylibs, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_lines, x_lines, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_empty, x_empty, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_docs , x_docs , 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_debug, x_debug, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_code , x_code , 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_slocl, x_slocl, 0, 'c', '-', LEN_TERSE);
   if (a_level == 'f') {
      ystrl4main (s_text , x_text , 0, 'c', '-', LEN_TERSE);
      ystrl4main (s_data , x_data , 0, 'c', '-', LEN_TERSE);
      ystrl4main (s_bss  , x_bss  , 0, 'c', '-', LEN_TERSE);
   }
   printf ("\n");
   printf ("#     %s totals %3s  %6.6s %6.6s %6.6s %8.8s %8.8s %8.8s %8.8s %8.8s %8.8s  %9.9s %9.9s %9.9s  \n",
         t, x_projs, x_files, x_funcs, x_ylibs, x_lines, x_empty, x_docs , x_debug, x_code , x_slocl, x_text, x_data, x_bss);
   if      (a_level == 'p')  a = s_projs;
   else if (a_level == 'f')  a = s_files;
   ystrl4main (s_funcs / a, x_funcs, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_ylibs / a, x_ylibs, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_lines / a, x_lines, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_empty / a, x_empty, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_docs  / a, x_docs , 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_debug / a, x_debug, 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_code  / a, x_code , 0, 'c', '-', LEN_TERSE);
   ystrl4main (s_slocl / a, x_slocl, 0, 'c', '-', LEN_TERSE);
   if (a_level == 'f') {
      a = s_memory;
      b = s_text + s_data + s_bss;
      ystrl4main (s_text  / a, x_text , 0, 'c', '-', LEN_TERSE);
      ystrl4main (s_data  / a, x_data , 0, 'c', '-', LEN_TERSE);
      ystrl4main (s_bss   / a, x_bss  , 0, 'c', '-', LEN_TERSE);
   }
   printf ("#    %s           averages  %6.6s %6.6s %8.8s %8.8s %8.8s %8.8s %8.8s %8.8s  %9.9s %9.9s %9.9s  \n",
         t, x_funcs, x_ylibs, x_lines, x_empty, x_docs , x_debug, x_code , x_slocl, x_text, x_data, x_bss);
   if (a_level == 'f') {
      a = s_text + s_data + s_bss;
      ystrl4main (s_text  / (float) a, x_text , 2, 'c', '-', LEN_TERSE);
      ystrl4main (s_data  / (float) a, x_data , 2, 'c', '-', LEN_TERSE);
      ystrl4main (s_bss   / (float) a, x_bss  , 2, 'c', '-', LEN_TERSE);
   }
   printf ("#    %s                                percentages %8.2f %8.2f %8.2f %8.2f %8.2f  %9.9s %9.9s %9.9s\n",
         t, (float) s_empty / s_lines, (float) s_debug / s_lines,
         (float) s_docs  / s_lines, (float) s_code  / s_lines,
         (float) s_slocl / s_lines, x_text, x_data, x_bss);
   printf ("\n");
   printf ("# end-of-file.  done, finito, completare, whimper.\n");
   return 0;
}

char
poly_rptg__debug        (tFUNC *a_tag)
{
   if (strchr ("Bb", a_tag->STATS_DSTYLE) != NULL) {
      ystrlcpy (s_prefix, "style"     , LEN_LABEL);
      return 1;
   }
   if (a_tag->STATS_DSTYLE == '#') {
      ystrlcpy (s_prefix, "boom"      , LEN_LABEL);
      return 1;
   }
   if (a_tag->STATS_DMACRO == '#' && strchr ("LSf", a_tag->STATS_DSTYLE) == NULL) {
      ystrlcpy (s_prefix, "macro"     , LEN_LABEL);
      return 1;
   }
   if (strchr ("!#EX", a_tag->STATS_DMATCH) != NULL) {
      ystrlcpy (s_prefix, "match"     , LEN_LABEL);
      return 1;
   }
   if (a_tag->STATS_DSTYLE == '-' && strchr ("ABCDEFGHIJKLMNOPQRSTUVWXYZ#", a_tag->STATS_TOTAL) != NULL) {
      ystrlcpy (s_prefix, "size"      , LEN_LABEL);
      return 1;
   }
   return 0;
}

char
poly_rptg__params       (tFUNC *a_tag)
{
   if (strchr ("56789ABCDEFGHIJKLMNOPQRSTUVWXYZ#", a_tag->STATS_PARAMS) != NULL) {
      ystrlcpy (s_prefix, "count"     , LEN_LABEL);
      return 1;
   }
   if (strchr ("#" , a_tag->STATS_PTWO) != NULL) {
      ystrlcpy (s_prefix, "**"        , LEN_LABEL);
      return 1;
   }
   if (strchr ("#" , a_tag->STATS_PNUM) != NULL) {
      ystrlcpy (s_prefix, "num*"      , LEN_LABEL);
      return 1;
   }
   return 0;
}

char
poly_rptg__data         (tFUNC *a_tag)
{
   if (strchr ("rR", a_tag->STATS_READ ) != NULL) {
      ystrlcpy (s_prefix, "read"      , LEN_LABEL);
      return 1;
   }
   if (strchr ("wW", a_tag->STATS_WRITE) != NULL) {
      ystrlcpy (s_prefix, "write"     , LEN_LABEL);
      return 1;
   }
   return 0;
}

char
poly_rptg__linux        (tFUNC *a_tag)
{
   if (strchr ("p"   , a_tag->STATS_SYSTEM) != NULL) {
      ystrlcpy (s_prefix, "process"   , LEN_LABEL);
      return 1;
   }
   if (strchr ("s"   , a_tag->STATS_SYSTEM) != NULL) {
      ystrlcpy (s_prefix, "system"    , LEN_LABEL);
      return 1;
   }
   if (strchr ("f"   , a_tag->STATS_SYSTEM) != NULL) {
      ystrlcpy (s_prefix, "filesys"   , LEN_LABEL);
      return 1;
   }
   if (strchr ("B"   , a_tag->STATS_SYSTEM) != NULL) {
      ystrlcpy (s_prefix, "all"       , LEN_LABEL);
      return 1;
   }
   return 0;
}

char
poly_rptg__stats        (tFUNC *a_tag)
{
   printf ("%c   ", a_tag->STATS_SINGLE);
   if (strncmp (a_tag->name, "o___", 4) != 0) {
      printf ("%c %c %c  %c %c %c  %c %c %c %c %c   %c %c  %c %c %c %c %c  %c %c %c %c   %c %c %c  %c %c %c %c  %c %c %c %c   ",
            a_tag->STATS_SCOPE , a_tag->STATS_RTYPE , a_tag->STATS_PARAMS,
            a_tag->STATS_TOTAL , a_tag->STATS_DEBUG , a_tag->STATS_SLOCL ,
            a_tag->STATS_LVARS , a_tag->STATS_CHOICE, a_tag->STATS_RETURN, a_tag->STATS_INDENT, a_tag->STATS_MEMORY ,
            a_tag->STATS_GCALLS, a_tag->STATS_LCALLS,
            a_tag->STATS_FUNCS , a_tag->STATS_GFUNCS, a_tag->STATS_CSTD  , a_tag->STATS_YLIB  , a_tag->STATS_MYSTRY ,
            a_tag->STATS_READ  , a_tag->STATS_WRITE , a_tag->STATS_SYSTEM, a_tag->STATS_RECURS,
            a_tag->STATS_DSTYLE, a_tag->STATS_DMACRO, a_tag->STATS_DMATCH,
            a_tag->STATS_NCURSE, a_tag->STATS_OPENGL, a_tag->STATS_WINDOW, a_tag->STATS_MYX   ,
            a_tag->STATS_PROTO , a_tag->STATS_ECALLS, a_tag->STATS_PTWO  , a_tag->STATS_PNUM  );
      printf ("[%c%c%c.%c%c%c.%c%c%c%c%c] [%c%c.%c%c%c%c%c.%c%c%c%c] [%c%c%c.%c%c%c%c.%c%c%c%c]   ",
            a_tag->STATS_SCOPE , a_tag->STATS_RTYPE , a_tag->STATS_PARAMS,
            a_tag->STATS_TOTAL , a_tag->STATS_DEBUG , a_tag->STATS_SLOCL ,
            a_tag->STATS_LVARS , a_tag->STATS_CHOICE, a_tag->STATS_RETURN, a_tag->STATS_INDENT, a_tag->STATS_MEMORY ,
            a_tag->STATS_GCALLS, a_tag->STATS_LCALLS,
            a_tag->STATS_FUNCS , a_tag->STATS_GFUNCS, a_tag->STATS_CSTD  , a_tag->STATS_YLIB  , a_tag->STATS_MYSTRY ,
            a_tag->STATS_READ  , a_tag->STATS_WRITE , a_tag->STATS_SYSTEM, a_tag->STATS_RECURS,
            a_tag->STATS_DSTYLE, a_tag->STATS_DMACRO, a_tag->STATS_DMATCH,
            a_tag->STATS_NCURSE, a_tag->STATS_OPENGL, a_tag->STATS_WINDOW, a_tag->STATS_MYX   ,
            a_tag->STATS_PROTO , a_tag->STATS_ECALLS, a_tag->STATS_PTWO  , a_tag->STATS_PNUM  );
   } else {
      printf ("%c %c %c  %-68.68s   ", a_tag->STATS_SCOPE , a_tag->STATS_RTYPE , a_tag->STATS_PARAMS , "");
      printf ("%-47.47s   ", "");
   }
   return 0;
}

char
poly_rptg__header       (void)
{
   printf ("#!/usr/local/bin/polymnia --report %s\n", s_name);
   printf ("\n");
   printf ("#  %s %s\n", P_NAMESAKE, P_HERITAGE);
   printf ("#  version %s, %s\n", P_VERNUM, P_VERTXT);
   printf ("#  %s\n", s_desc);
   printf ("#  data ver å%sæ database å%sæ\n" , g_audit.vernum, my.n_db);
   printf ("\n");
   printf ("#@ style     V = printable columnar values\n");
   return 0;
}

char
poly_rptg_projects      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_OUTP  yLOG_enter   (__FUNCTION__);
   /*---(report header)------------------*/
   if (s_opt == POLY_REPORT) {
      poly_rptg__header    ();
      poly_proj_line (NULL, s_options [0], 'p', '-', 0, 'y');
      poly_proj_line (NULL, s_options [0], 't','-',  0, 'y');
      printf ("\n");
   }
   /*---(prepare)------------------------*/
   poly_rptg__prep ();
   DEBUG_OUTP   yLOG_value   ("projects"  , ySORT_count (B_PROJ));
   /*---(walk projects)------------------*/
   rc = poly_proj_by_cursor ('[', &x_proj);
   DEBUG_OUTP   yLOG_point   ("proj"      , x_proj);
   while (rc >= 0 && x_proj != NULL) {
      /*---(prepare)---------------------*/
      DEBUG_OUTP   yLOG_info    ("->name"    , x_proj->name);
      DEBUG_OUTP   yLOG_value   ("files"     , x_proj->count);
      if (s_opt != POLY_DUMP) {
         if (c > 0 && c %  5 == 0)  printf ("\n");
         if (c % 25 == 0)  { poly_proj_line (NULL, s_options [0], 'h', '-', 0, 'y'); printf ("\n"); }
      }
      poly_proj_line (x_proj, s_options [0], 'd', '-', c, 'y');
      poly_rptg__proj_inc  (x_proj);
      /*---(next)------------------------*/
      rc = poly_proj_by_cursor ('>', &x_proj);
      DEBUG_OUTP   yLOG_point   ("proj"      , x_proj);
      ++c;
      /*---(done)------------------------*/
   }
   if (s_opt != POLY_DUMP) {
      printf ("\n");
      if (c % 45 > 5)  poly_proj_line (NULL, s_options [0], 'h', '-', 0, 'y');
   }
   if (s_opt == POLY_REPORT)  poly_rptg__total ('p');
   return 0;
}

char
poly_rptg_files         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(report header)------------------*/
   if (s_opt == POLY_REPORT) {
      poly_rptg__header    ();
      poly_file_line (NULL, s_options [1], 'p', '>', 0, 0, 'y');
      poly_file_line (NULL, s_options [1], 't', '>', 0, 0, 'y');
   }
   /*---(prepare)------------------------*/
   poly_rptg__prep ();
   if (s_opt != POLY_DUMP) {
      poly_proj_line (my.g_proj, s_options [0], 'h', '#', my.g_projno, 'y');
      poly_proj_line (my.g_proj, s_options [0], 'd', '#', my.g_projno, 'y');
   }
   /*---(walk projects)------------------*/
   rc = poly_file_by_proj_index (my.g_proj, c, &x_file);
   DEBUG_OUTP   yLOG_point   ("proj"      , x_file);
   while (rc >= 0 && x_file != NULL) {
      /*---(prepare)---------------------*/
      DEBUG_OUTP   yLOG_info    ("->name"    , x_file->name);
      DEBUG_OUTP   yLOG_value   ("files"     , x_file->count);
      if (s_opt != POLY_DUMP) {
         if (c %  5 == 0)  printf ("\n");
         if (c % 25 == 0)  { poly_file_line (NULL, s_options [1], 'h', '>', 0, 0, 'y'); printf ("\n"); }
      }
      poly_file_line (x_file, s_options [1], 'd', '>', my.g_projno, c, 'y');
      poly_rptg__file_inc  (x_file);
      /*---(next)------------------------*/
      ++c;
      rc = poly_file_by_proj_index (my.g_proj, c, &x_file);
      DEBUG_OUTP   yLOG_point   ("proj"      , x_file);
      /*---(done)------------------------*/
   }
   if (s_opt != POLY_DUMP) {
      printf ("\n");
      if (c % 45 > 5)  poly_file_line (NULL, s_options [1], 'h', '>', 0, 0, 'y');
   }
   if (s_opt == POLY_REPORT)   poly_rptg__total ('f');
   return 0;
}

char
poly_rptg_ylibs         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   tFUNC      *x_func      = NULL;
   tYLIB      *x_ylib      = NULL;
   tEXTERN    *x_ext       = NULL;
   tELIB      *x_elib      = NULL;
   int         l           =    0;
   int         n           =    0;
   int         c           =    0;
   char        x_uses      [LEN_TERSE] = "";
   char        x_count     [LEN_TERSE] = "";
   /*---(walk projects)------------------*/
   poly_extern_clear_uses ();
   poly_rptg__header    ();
   printf ("#@ x-parse   åÏ---·Ï-----------·Ï---···Ï-------------------·Ï---···Ï------------------------·Ï---·Ï---·Ï---·Ï---···Ï---·Ï---·Ï-------------------···Ï-------------------·Ï---·Ï·Ï·Ï·Ï-----æ\n");
   printf ("#@ titles    åcum··project······cnt····file·················cnt····func······················cnt··top··beg··end····ref··line·ylib···················source···············line·t·c·s·uses··æ\n");
   printf ("\n");
   /*> poly_proj_line (my.g_proj, s_options [0], 'h', '#', my.g_projno, 'y');         <*/
   /*> poly_proj_line (my.g_proj, s_options [0], 'd', '#', my.g_projno, 'y');         <*/
   x_file = my.g_proj->head;
   while (x_file != NULL) {
      if (x_file->COUNT_YLIBS > 0) {
         /*> poly_file_line (x_file, s_options [1], 'h', '>', my.g_projno, c, 'y');   <*/
         /*> poly_file_line (x_file, s_options [1], 'd', '>', my.g_projno, c, 'y');   <*/
         x_func = x_file->head;
         while (x_func != NULL) {
            if (x_func->COUNT_YLIBS > 0) {
               /*> poly_func_line (x_func, POLY_RPTG_HTAGS, 0, 0, 0, 'y');                  <*/
               c = 0;
               x_ylib = x_func->y_head;
               while (x_ylib != NULL) {
                  if (n %  5 == 0 && n > 0)  printf ("\n");
                  if (n % 25 == 0)  printf ("#cum --proj------ cnt-   ---file------------- cnt-   ---function-------------- -cnt -top -beg -end   ref- line ---ylib-------------   ---source--- line t c s uses--\n\n");
                  ++n; ++c;
                  ++x_ylib->ylib->wuse;
                  ++x_ylib->ylib->elib->wuse;
                  ystrl4main (x_ylib->ylib->y_count, x_count, 0, 'c', '-', LEN_TERSE);
                  printf ("%-4d %-12.12s %4d   %-20.20s %4d   %-25.25s %4d %4d %4d %4d   %4d %4d %-20.20s   %-12.12s %4d %c %c %c %6s\n",
                        n, my.g_proj->name, my.g_proj->COUNT_YLIBS,
                        x_file->name, x_file->COUNT_YLIBS,
                        x_func->name, x_func->COUNT_YLIBS, x_func->line, x_func->beg, x_func->end,
                        c, x_ylib->line, x_ylib->name,
                        x_ylib->ylib->elib->name, x_ylib->ylib->line, x_ylib->ylib->type, x_ylib->ylib->cat, x_ylib->ylib->sub, x_count);
                  x_ylib = x_ylib->f_next;
               }
            }
            x_func = x_func->next;
         }
      }
      x_file = x_file->next;
   }
   /*---(summarize)----------------------*/
   c = 0;
   printf ("\n");
   printf ("# unique ylib external functions\n");
   printf ("#\n");
   printf ("#  ref- ---ylib------------- ---source--- here ---all\n");
   rc = ySORT_by_cursor (B_EXTERN, YDLST_HEAD, &x_ext);
   while (x_ext != NULL) {
      if (x_ext->wuse > 0) {
         ystrl4main (x_ext->y_count, x_count, 0, 'c', '-', LEN_TERSE);
         ystrl4main (x_ext->wuse   , x_uses , 0, 'c', '-', LEN_TERSE);
         printf ("#  %4d %-20.20s %-12.12s %4.4s %6.6s\n", ++c, x_ext->name, x_ext->elib->name, x_uses, x_count);
      }
      rc = ySORT_by_cursor (B_EXTERN, YDLST_NEXT, &x_ext);
   }
   c = 0;
   printf ("\n");
   printf ("# ylib dependencies\n");
   printf ("#\n");
   printf ("#  ref- ---source---\n");
   rc = ySORT_by_cursor (B_ELIB, YDLST_HEAD, &x_elib);
   while (x_elib != NULL) {
      if (x_elib->wuse > 0) {
         printf ("#  %4d %-20.20s\n", ++c, x_elib->name);
      }
      rc = ySORT_by_cursor (B_ELIB, YDLST_NEXT, &x_elib);
   }
   poly_extern_clear_uses ();
   printf ("\n");
   printf ("# total available tracked library dependencies %d\n", ySORT_count (B_ELIB));
   /*---(walk through list)--------------*/
   printf ("\n");
   printf ("# end-of-file.  done, finito, completare, whimper.\n");
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_rptg_exts          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tELIB      *x_elib      = NULL;
   tEXTERN    *x_ext       = NULL;
   int         l           =    0;
   int         n           =    0;
   int         c           =    0;
   char        x_count     [LEN_TERSE] = "";
   char        x_ylibs     [LEN_TERSE] = "";
   /*---(walk projects)------------------*/
   poly_rptg__header    ();
   printf ("#@ x-parse   åÏ---·Ï-----------·Ï---···Ï-------------------·Ï---···Ï------------------------·Ï---·Ï---·Ï---·Ï---···Ï---·Ï---·Ï-------------------···Ï-------------------·Ï---·Ï·Ï·Ï·Ï-----æ\n");
   printf ("#@ titles    åcum··project······cnt····file·················cnt····func······················cnt··top··beg··end····ref··line·ylib···················source···············line·t·c·s·uses··æ\n");
   rc = ySORT_by_cursor (B_ELIB, YDLST_HEAD, &x_elib);
   while (x_elib != NULL) {
      rc = ySORT_by_cursor (B_EXTERN, YDLST_HEAD, &x_ext);
      c = 0;
      while (x_ext != NULL) {
         if (x_ext->elib == x_elib && x_ext->type == 'p') {
            /*> if (x_ext->y_count > 0) {                                             <*/
            if (c == 0) {
               printf ("\n");
               printf ("%-20.20s (%d)\n", x_elib->name, x_elib->count);
            }
            ystrl4main (x_ext->count  , x_count, 0, 'c', '-', LEN_TERSE);
            ystrl4main (x_ext->y_count, x_ylibs, 0, 'c', '-', LEN_TERSE);
            printf ("%5d %4d %-20.20s %6.6s %6.6s %4.4d %c %c %c\n", ++n, ++c, x_ext->name, x_count, x_ylibs, x_ext->line, x_ext->type, x_ext->cat, x_ext->sub);
            /*> }                                                                     <*/
         }
         rc = ySORT_by_cursor (B_EXTERN, YDLST_NEXT, &x_ext);
      }
      rc = ySORT_by_cursor (B_ELIB, YDLST_NEXT, &x_elib);
   }
   /*---(walk through list)--------------*/
   printf ("\n");
   printf ("# end-of-file.  done, finito, completare, whimper.\n");
   /*---(complete)-----------------------*/
   return 0;
}


char
poly_rptg_file          (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(files)--------------------------*/
   x_file = a_proj->head;
   DEBUG_OUTP   yLOG_point   ("file"      , x_file);
   while (x_file != NULL) {
      DEBUG_OUTP   yLOG_info    ("->name"    , x_file->name);
      DEBUG_OUTP   yLOG_value   ("tags"      , x_file->count);
      if (my.g_mode != POLY_RPTG_DUMP) {
         printf ("  %-23.23s       %7d %7d %7d %7d %7d %7d %7d\n",
               x_file->name , x_file->count,
               x_file->COUNT_LINES, x_file->COUNT_EMPTY,
               x_file->COUNT_DOCS , x_file->COUNT_DEBUG,
               x_file->COUNT_CODE , x_file->COUNT_SLOCL);
      }
      switch (my.g_mode) {
      case POLY_RPTG_PROJS :
      case MODE_FILE :
         break;
      case POLY_RPTG_HTAGS :
         break;
      }
      x_file = x_file->next;
      DEBUG_OUTP   yLOG_point   ("file"      , x_file);
   }
}

char
poly_rptg_projfilter    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(find target)--------------------*/
   DEBUG_PROG   yLOG_info    ("g_projname" , my.g_projname);
   if (my.g_projname [0] == '\0') {
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   poly_proj_by_name  (my.g_projname, &my.g_proj);
   DEBUG_PROG   yLOG_point   ("g_proj"     , my.g_proj);
   --rce;  if (my.g_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("->name"     , my.g_proj->name);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}


char
poly_rptg_proj          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   my.COUNT_FILES = my.COUNT_FUNCS = my.COUNT_LINES = my.COUNT_EMPTY = my.COUNT_DOCS  = my.COUNT_DEBUG = my.COUNT_CODE  = my.COUNT_SLOCL = 0;
   if (my.g_mode != POLY_RPTG_DUMP && my.g_titles == RPTG_TITLES) {
      printf ("## project listing report\n");
      printf ("##    generated by polymnia-hymnos (many praises) muse of divine hymns, c language, dance, geometry, and grammar\n");
      printf ("##---name---------------- --files --funcs --lines --empty ---docs --debug ---code --slocl ---code-size--- ---greek-heritage-------------------------------------------  ---purpose-statement---------------------------------------- -ver- ---version-description--------------------------------------  ---focus------------  ---niche------------  --created-  ---home-directory-------------------------------------------\n");
   }
   /*---(find target)--------------------*/
   rc = poly_rptg_projfilter ();
   DEBUG_PROG   yLOG_point   ("filter"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(projects)-----------------------*/
   DEBUG_OUTP   yLOG_value   ("projects"  , ySORT_count (B_PROJ));
   rc = ySORT_by_cursor (B_PROJ, YDLST_HEAD, &x_proj);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   while (x_proj != NULL) {
      /*---(prepare)---------------------*/
      DEBUG_OUTP   yLOG_info    ("->name"    , x_proj->name);
      DEBUG_OUTP   yLOG_value   ("files"     , x_proj->count);
      /*---(grand totals)----------------*/
      my.COUNT_FILES += x_proj->COUNT_FILES;
      my.COUNT_FUNCS += x_proj->COUNT_FUNCS;
      my.COUNT_LINES += x_proj->COUNT_LINES;
      my.COUNT_EMPTY += x_proj->COUNT_EMPTY;
      my.COUNT_DOCS  += x_proj->COUNT_DOCS;
      my.COUNT_DEBUG += x_proj->COUNT_DEBUG;
      my.COUNT_CODE  += x_proj->COUNT_CODE;
      my.COUNT_SLOCL += x_proj->COUNT_SLOCL;
      /*---(project filtering)-----------*/
      if (my.g_proj != NULL && x_proj != my.g_proj) {
         rc = ySORT_by_cursor (B_PROJ, YDLST_NEXT, &x_proj);
         DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
         continue;
      }
      if (my.g_titles == RPTG_TITLES && c % 5 == 0)  printf ("\n");
      /*---(reporting)-------------------*/
      if (my.g_mode != POLY_RPTG_DUMP) {
         printf ("%-25.25s  %4d %7d %7d %7d %7d %7d %7d %7d  %-13.13s  ",
               x_proj->name , x_proj->count, x_proj->funcs,
               x_proj->COUNT_LINES, x_proj->COUNT_EMPTY,
               x_proj->COUNT_DOCS , x_proj->COUNT_DEBUG,
               x_proj->COUNT_CODE , x_proj->COUNT_SLOCL,
               x_proj->codesize);
         printf ("%-60.60s  %-60.60s  %-5.5s %-60.65s  %-20.20s  %-20.20s  %-10.10s  %-60.60s\n",
               x_proj->heritage, x_proj->purpose,
               x_proj->vernum  , x_proj->vertxt,
               x_proj->focus   , x_proj->niche,
               x_proj->created , x_proj->homedir);
      }
      /*---(diving)----------------------*/
      switch (my.g_mode) {
      case POLY_RPTG_PROJS :
         break;
      case MODE_FILE : case POLY_RPTG_HTAGS : case POLY_RPTG_DUMP :
         rc = poly_rptg_file (x_proj);
         printf ("\n");
         break;
      }
      /*---(next)------------------------*/
      rc = ySORT_by_cursor (B_PROJ, YDLST_NEXT, &x_proj);
      DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
      ++c;
      /*---(done)------------------------*/
   }
   if (my.g_titles == RPTG_TITLES)  {
      printf ("\n");;
      printf ("## %17.17s (%3d) %4d %7d %7d %7d %7d %7d %7d %7d\n", "GRAND TOTALS", c,
            my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_LINES, my.COUNT_EMPTY, my.COUNT_DOCS, my.COUNT_DEBUG, my.COUNT_CODE, my.COUNT_SLOCL);
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_rptg_dump          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   tFILE      *x_file      = NULL;
   tFUNC      *x_func      = NULL;
   char        x_show      =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_OUTP   yLOG_note    ("review all tags and code");
   DEBUG_OUTP   yLOG_value   ("projects"  , ySORT_count (B_PROJ));
   /*---(header)-------------------------*/
   if (my.g_titles == RPTG_TITLES) {
      printf ("## function listing report\n");
      printf ("##    generated by polymnia-hymnos (many praises) muse of divine hymns, c language, dance, geometry, and grammar\n");
      printf ("\n");
   }
   /*---(find target)--------------------*/
   rc = poly_rptg_projfilter ();
   DEBUG_PROG   yLOG_point   ("filter"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(projects)-----------------------*/
   rc = ySORT_by_cursor (B_PROJ, YDLST_HEAD, &x_proj);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   while (x_proj != NULL) {
      /*---(prepare)---------------------*/
      DEBUG_OUTP   yLOG_info    ("->name"    , x_proj->name);
      DEBUG_OUTP   yLOG_value   ("files"     , x_proj->count);
      if (my.g_titles == RPTG_TITLES && x_proj->count > 0) {
         printf ("\nPROJECT : %s, %s\n", x_proj->name, x_proj->purpose);
      }
      /*---(project filtering)-----------*/
      if (my.g_proj != NULL && x_proj != my.g_proj) {
         rc = ySORT_by_cursor (B_PROJ, YDLST_NEXT, &x_proj);
         DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
         continue;
      }
      /*---(files)-----------------------*/
      x_file = x_proj->head;
      DEBUG_OUTP   yLOG_point   ("file"      , x_file);
      while (x_file != NULL) {
         /*---(prepare)------------------*/
         DEBUG_OUTP   yLOG_info    ("->name"    , x_file->name);
         DEBUG_OUTP   yLOG_value   ("tags"      , x_file->count);
         if (my.g_titles == RPTG_TITLES && x_file->count > 0) {
            printf ("\nFILE    : %s\n", x_file->name);
         }
         /*---(tags)---------------------*/
         x_func  = x_file->head;
         DEBUG_OUTP   yLOG_point   ("tag"       , x_func);
         while (x_func  != NULL) {
            DEBUG_OUTP   yLOG_info    ("->name"    , x_func->name);
            switch (my.g_filter) {
            case FILTER_DEBUG  : x_show = poly_rptg__debug  (x_func);  break;
            case FILTER_PARAMS : x_show = poly_rptg__params (x_func);  break;
            case FILTER_DATA   : x_show = poly_rptg__data   (x_func);  break;
            case FILTER_LINUX  : x_show = poly_rptg__linux  (x_func);  break;
            default            : x_show = 1;
            }
            if (x_show == 1)  {
               if (my.g_titles == RPTG_TITLES && c % 25 == 0) {
                  printf ("\n##");
                  if (my.g_filter != FILTER_NONE)  printf ("-reason-  --");
                  printf ("%s\n", poly_func_line (x_func, POLY_RPTG_DUMP, 0, 0, 0, NULL));
                  /*> printf ("---project-------------   ---file------------------   line   ---function/tag----------   -  [------complexity-------] [------integration------] [----watch-points-------]  [-complexity--] [-integration-] [-watch-point-]  [----source-file----------]   [line]    [-type-] [rdy] [-----------description-------------]\n");   <*/
               }
               if (my.g_titles == RPTG_TITLES && c %  5 == 0)  printf ("\n");
               if (my.g_filter != FILTER_NONE)  printf ("%-12.12s", s_prefix);
               printf ("%s\n", poly_func_line (x_func, POLY_RPTG_DUMP, 0, 0, 0, NULL));
               ++c;
            }
            x_func  = x_func->next;
            DEBUG_OUTP   yLOG_point   ("x_func"    , x_func);
         }
         x_file = x_file->next;
         DEBUG_OUTP   yLOG_point   ("file"      , x_file);
      }
      rc = ySORT_by_cursor (B_PROJ, YDLST_NEXT, &x_proj);
      DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   }
   if (my.g_titles == RPTG_TITLES)  printf ("\n## %d total lines\n", c);
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_rptg_extern        (tEXTERN *a_extern)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   tYLIB      *x_ylib      = NULL;
   tPROJ      *x_proj      = NULL;
   tFILE      *x_file      = NULL;
   tFUNC      *x_func      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(find target)--------------------*/
   rc = poly_rptg_projfilter ();
   DEBUG_PROG   yLOG_point   ("filter"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(projects)-----------------------*/
   if (my.g_titles == RPTG_TITLES) {
      printf ("## external function call usage report\n");
      printf ("##    generated by polymnia-hymnos (many praises) muse of divine hymns, c language, dance, geometry, and grammar\n");
      printf ("##    target extern : %s\n", a_extern->name);
   }
   if (my.g_titles == RPTG_TREEVIEW) {
      printf ("## yLIB (external) treeview report for %s\n", a_extern->name);
      printf ("##    generated by polymnia --extern %s --treeview\n", a_extern->name);
   }
   DEBUG_OUTP   yLOG_point   ("a_extern"  , a_extern);
   DEBUG_OUTP   yLOG_info    ("->name"    , a_extern->name);
   x_ylib = a_extern->y_head;
   DEBUG_OUTP   yLOG_point   ("x_ylib"    , x_ylib);
   while (x_ylib != NULL) {
      /*---(project filtering)-----------*/
      if (my.g_proj != NULL && x_ylib->func->file->proj != my.g_proj) {
         x_ylib = x_ylib->e_next;
         DEBUG_OUTP   yLOG_point   ("x_ylib"    , x_ylib);
         continue;
      }
      /*---(headers)---------------------*/
      if (my.g_titles == RPTG_TITLES && c % 25 == 0)  printf ("\n##---project-------------  ---source-file-----------  line  ---source-function-------\n");
      if (my.g_titles == RPTG_TITLES && c %  5 == 0)  printf ("\n");
      DEBUG_OUTP   yLOG_info    ("->name"    , x_ylib->name);
      /*---(tree view)-------------------*/
      if (my.g_titles == RPTG_TREEVIEW) {
         if (x_ylib->func->file->proj != x_proj) {
            x_file = NULL;
            printf ("\n");
            printf ("%-25.25s\n", x_ylib->func->file->proj->name);
         }
         if (x_ylib->func->file != x_file) {
            x_func  = NULL;
            if (x_file != NULL)  printf ("\n");
            printf ("   %-25.25s\n", x_ylib->func->file->name);
         } 
         if (x_ylib->func != x_func) {
            if (x_func != NULL)  printf ("\n");
            printf ("      %-25.25s", x_ylib->func->name);
         } 
         printf ("%4d,", x_ylib->line);
         x_proj = x_ylib->func->file->proj;
         x_file = x_ylib->func->file;
         x_func = x_ylib->func;
      }
      /*---(normal view)-----------------*/
      else {
         printf ("%-25.25s  %-25.25s  %-25.25s  %4d  %-25.25s\n", a_extern->name, x_ylib->func->file->proj->name, x_ylib->func->file->name, x_ylib->line, x_ylib->func->name);
      }
      /*---(next)------------------------*/
      ++c;
      x_ylib = x_ylib->e_next;
      DEBUG_OUTP   yLOG_point   ("x_ylib"    , x_ylib);
      /*---(done)------------------------*/
   }
   if (my.g_titles == RPTG_TITLES)  printf ("\n## %d total references, %d shown\n", a_extern->y_count, c);
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_rptg__htags_header (tPROJ *a_proj)
{
   printf ("##/usr/local/bin/polymnia --htags\n");
   printf ("##\n");
   printf ("##   polymnia-hymnos (many praises) greek muse and protector of divine hymns, dancing, geometry, and grammar\n");
   printf ("##   version %s, %s\n", P_VERNUM, P_VERTXT);
   printf ("##   htags reporting file for use with vim-ide\n");
   printf ("##\n");
   printf ("##   33 headers ·  [%s]\n", a_proj->header);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   name       N  [%s]\n", a_proj->name);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   focus      f  [%s]\n", a_proj->focus);
   printf ("##   niche      n  [%s]\n", a_proj->niche);
   printf ("##   subject    s  [%s]\n", a_proj->subject);
   printf ("##   purpose    p  [%s]\n", a_proj->purpose);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   namesake   ê  [%s]\n", a_proj->namesake);
   printf ("##   pronounce  ÷  [%s]\n", a_proj->pronounce);
   printf ("##   heritage   î  [%s]\n", a_proj->heritage);
   printf ("##   briefly    é  [%s]\n", a_proj->briefly);
   printf ("##   imagery    ð  [%s]\n", a_proj->imagery);
   printf ("##   reason     ø  [%s]\n", a_proj->reason);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   one-line   ö  [%s]\n", a_proj->oneline);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   homedir    d  [%s]\n", a_proj->homedir);
   printf ("##   basename   b  [%s]\n", a_proj->progname);
   printf ("##   fullpath   f  [%s]\n", a_proj->fullpath);
   printf ("##   suffix     s  [%s]\n", a_proj->suffix);
   printf ("##   content    c  [%s]\n", a_proj->content);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   system     s  [%s]\n", a_proj->systems);
   printf ("##   language   l  [%s]\n", a_proj->language);
   printf ("##   compiler   c  [%s]\n", a_proj->compiler);
   printf ("##   code-size  z  [%s]\n", a_proj->codesize);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   dep_cstd   D  [%s]\n", a_proj->dep_cstd);
   printf ("##   dep_posix  P  [%s]\n", a_proj->dep_posix);
   printf ("##   dep_core   C  [%s]\n", a_proj->dep_core);
   printf ("##   dep_vikey  V  [%s]\n", a_proj->dep_vikey);
   printf ("##   dep_other  O  [%s]\n", a_proj->dep_other);
   printf ("##   dep_graph  G  [%s]\n", a_proj->dep_graph);
   printf ("##   dep_solo   S  [%s]\n", a_proj->dep_solo);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   author     a  [%s]\n", a_proj->author);
   printf ("##   created    c  [%s]\n", a_proj->created);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   vermajor   x  [%s]\n", a_proj->vermajor);
   printf ("##   verminor   n  [%s]\n", a_proj->verminor);
   printf ("##   vernum     v  [%s]\n", a_proj->vernum);
   printf ("##   vertxt     t  [%s]\n", a_proj->vertxt);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n\n\n\n");
   return 0;
}

char
poly_rptg_htags         (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   tFUNC      *x_func      = NULL;
   int         i           =    0;
   char        t           [LEN_TERSE] = "";
   char        s           [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      rc = ySORT_by_cursor (B_PROJ, YDLST_HEAD, &a_proj);
      DEBUG_PROG   yLOG_point   ("a_proj"    , a_proj);
      if (a_proj == NULL) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(output)-------------------------*/
   DEBUG_PROG   yLOG_note    ("review all tags and code");
   x_file = a_proj->head;
   DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   if (my.g_rptg == POLY_RPTG_HTAGS)    poly_rptg__htags_header (a_proj);
   while (x_file != NULL) {
      DEBUG_PROG   yLOG_info    ("file name" , x_file->name);
      printf ("%-29.29s   FILE\n", x_file->name);
      if (my.g_rptg == POLY_RPTG_HTAGS) {
         /*> printf ("%s\n", poly_cats_header (7, "lines", x_file->COUNT_LINES, x_file->proj->COUNT_LINES));   <* 
          *> printf ("%s\n", poly_cats_header (6, "empty", x_file->COUNT_EMPTY, x_file->proj->COUNT_EMPTY));   <* 
          *> printf ("%s\n", poly_cats_header (5, "docs" , x_file->COUNT_DOCS , x_file->proj->COUNT_DOCS ));   <* 
          *> printf ("%s\n", poly_cats_header (4, "debug", x_file->COUNT_DEBUG, x_file->proj->COUNT_DEBUG));   <* 
          *> printf ("%s\n", poly_cats_header (3, "code" , x_file->COUNT_CODE , x_file->proj->COUNT_CODE ));   <* 
          *> printf ("%s\n", poly_cats_header (2, "slocl", x_file->COUNT_SLOCL, x_file->proj->COUNT_SLOCL));   <*/
         printf ("%s\n", poly_cats_header (7, "line" , x_file->COUNT_LINES, x_file->proj->COUNT_LINES));
         printf ("%s\n", poly_cats_header (6, "empt" , x_file->COUNT_EMPTY, x_file->proj->COUNT_EMPTY));
         printf ("%s\n", poly_cats_header (5, "docs" , x_file->COUNT_DOCS , x_file->proj->COUNT_DOCS ));
         printf ("%s\n", poly_cats_header (4, "dbug" , x_file->COUNT_DEBUG, x_file->proj->COUNT_DEBUG));
         printf ("%s\n", poly_cats_header (3, "code" , x_file->COUNT_CODE , x_file->proj->COUNT_CODE ));
         printf ("%s\n", poly_cats_header (2, "sloc" , x_file->COUNT_SLOCL, x_file->proj->COUNT_SLOCL));
         printf ("%s\n", poly_cats_header (1, ""     , 0                   , 0                       ));
         printf ("%s\n", poly_func_line   (NULL, POLY_RPTG_HTAGS, 0, 0, x_file->count, '-'));
      }
      x_func = NULL;
      rc = poly_code_nextfunc (x_file, &x_func);
      DEBUG_PROG   yLOG_value   ("nexttag"   , rc);
      DEBUG_PROG   yLOG_point   ("x_func"    , x_func);
      while (rc >= 0)  {
         DEBUG_PROG   yLOG_info    ("name"      , x_func->name);
         printf ("%s\n", poly_func_line (x_func, POLY_RPTG_HTAGS, 0, 0, 0, '-'));
         rc = poly_code_nextfunc (x_file, &x_func);
         DEBUG_PROG   yLOG_value   ("nexttag"   , rc);
         DEBUG_PROG   yLOG_point   ("x_func"    , x_func);
      }
      printf ("\n");
      printf ("footprint\n");
      ystrl4main (x_file->COUNT_TEXT       , s , 0, 'c', '-', LEN_TERSE);
      ystrl4main (x_file->proj->COUNT_TEXT , t , 0, 'c', '-', LEN_TERSE);
      printf ("txt %7.7s %8.8s\n", s, t);
      ystrl4main (x_file->COUNT_DATA       , s , 0, 'c', '-', LEN_TERSE);
      ystrl4main (x_file->proj->COUNT_DATA , t , 0, 'c', '-', LEN_TERSE);
      printf ("dat %7.7s %8.8s\n", s, t);
      ystrl4main (x_file->COUNT_BSS        , s , 0, 'c', '-', LEN_TERSE);
      ystrl4main (x_file->proj->COUNT_BSS  , t , 0, 'c', '-', LEN_TERSE);
      printf ("bss %7.7s %8.8s\n", s, t);
      /*> printf ("text %6d %7d\n", x_file->COUNT_TEXT, x_file->proj->COUNT_TEXT);    <* 
       *> printf ("data %6d %7d\n", x_file->COUNT_DATA, x_file->proj->COUNT_DATA);    <* 
       *> printf ("bss  %6d %7d\n", x_file->COUNT_BSS , x_file->proj->COUNT_BSS);     <*/
      if (my.g_rptg == POLY_RPTG_HTAGS)  for (i = 0; i < 70 - x_file->count; ++i)  printf ("\n");
      else         printf ("\n\n");
      x_file = x_file->next;
      DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_rptg_func          (void)
{
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   tPROJ      *x_proj      = NULL;
   tFILE      *x_file      = NULL;
   tFUNC      *x_func      = NULL;
   char        x_grp       =   -1;
   char        x_sub       =   -1;
   char        x_name      [LEN_LABEL] = "";
   char        x_desc      [LEN_DESC]  = "";
   char        x_set       = '·';
   char        x_save      =  -1;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(find function)------------------*/
   DEBUG_PROG   yLOG_info    ("funcname"  , my.g_funcname);
   poly_func_by_name  (my.g_funcname, &x_func);
   DEBUG_PROG   yLOG_point   ("x_func"    , x_func);
   --rce;  if (x_func == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_file = x_func->file;
   DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   --rce;  if (x_file == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_proj = x_file->proj;
   DEBUG_PROG   yLOG_point   ("x_proj"    , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(report header)------------------*/
   printf ("#!/usr/local/bin/polymnia --report function\n");
   printf ("   function %s -> %s -> %s\n", x_proj->name, x_file->name, x_func->name);
   printf ("   location   head %4d, beg %4d, end %4d\n", x_func->line, x_func->beg, x_func->end);
   printf ("\n");
   /*---(display summary)----------------*/
   poly_cats_by_index (x_func, i, &x_grp, &x_sub, x_name, x_desc, &x_set);
   printf ("-  -----complexity------   -------integration-------   -----watch-points-----\n");
   printf ("%c %s\n\n", x_set, poly_cats_comment (x_func));
   /*---(display cats)-------------------*/
   while (rc >= 0) {
      ++i;
      rc = poly_cats_by_index (x_func, i - 1, &x_grp, &x_sub, x_name, x_desc, &x_set);
      if (rc <  0)  break;
      if (strcmp (x_name, "")  == 0)  continue;
      if (strcmp (x_name, "·") == 0)  continue;
      if (x_set == '-')  x_set = '·';
      if      (x_grp > 0 && x_sub == 0)   printf ("\n%s\n", x_desc);
      else if (x_grp == 0)       printf ("prefix\n·  %c  %-10.10s  %s\n", x_set, x_name, x_desc);
      else if (x_save != x_sub)  printf ("%1d  %c  %-10.10s  %s\n", x_sub, x_set, x_name, x_desc);
      else                       printf ("·  %c  %-10.10s  %s\n", x_set, x_name, x_desc);
      x_save = x_sub;
   }
   /*---(report footer)------------------*/
   printf ("\n# end-of-file.  done, finito, completare, whimper.\n");
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_rptg_dispatch      (void)
{
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   DEBUG_OUTP   yLOG_info    ("run_file"  , my.run_file);
   rc = poly_rptg_lookup   (my.run_file);
   DEBUG_OUTP   yLOG_value   ("lookup"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_db_read       ();
   DEBUG_OUTP   yLOG_value   ("db_read"   , rc);
   DEBUG_OUTP   yLOG_value   ("g_projno"  , my.g_projno);
   if (my.g_projno >= 0) {
      DEBUG_OUTP   yLOG_note    ("handle a specific project");
      rc     = poly_proj_by_index (my.g_projno, &(my.g_proj));
      ystrlcpy (my.g_projname, my.g_proj->name, LEN_LABEL);
      /*> printf ("project %2d, %p, %s\n", my.g_projno, my.g_proj, my.g_projname);   <*/
   }
   DEBUG_OUTP   yLOG_value   ("g_fileno"  , my.g_fileno);
   if (my.g_fileno >= 0) {
      DEBUG_OUTP   yLOG_note    ("handle a specific file");
      rc     = poly_file_by_proj_index (my.g_proj, my.g_fileno, &(my.g_file));
      ystrlcpy (my.g_filename, my.g_file->name, LEN_LABEL);
      /*> printf ("file    %2d, %p, %s\n", my.g_fileno, my.g_proj, my.g_projname);   <*/
   }
   DEBUG_PROG   yLOG_char    ("g_rptg"    , my.g_rptg);
   if      (my.g_scope == POLY_PROJ)    rc = poly_rptg_projects ();
   else if (my.g_scope == POLY_FILE)    rc = poly_rptg_files    ();
   else if (my.g_scope == POLY_FUNC)    rc = poly_rptg_func     ();
   else if (my.g_scope == POLY_YLIB)    rc = poly_rptg_ylibs    ();
   else if (my.g_scope == POLY_EXTS)    rc = poly_rptg_exts     ();
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}





