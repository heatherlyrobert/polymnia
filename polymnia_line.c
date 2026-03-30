/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2019 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might¦"    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/



/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
#define  P_OBJECTIVE   \
   "polymnia_line.c is focused solely on reviewing individual lines of code¦"         \
   "from a c-source file and attibuting it to various analysis statistics based¦"     \
   "on contents."

/*-----  ----------------  ·········1·········2·········3·········4·········5·········*/
#define  P_IMPORTANCE     "´ (low)      useful, but not required to run"
#define  P_COMPLEXITY     "m (medium)   primarily string data handling"


/*
 *
 *  always group base and mas macros
 *
 * metis § !g4·· § build macro find into yURG to keep in sync                             § M225T6 §  · §
 *   Metis § mg4·· § inventory all debugging macros and functions used                      § M225TW §  · §
 *   Metis § mg4·· § create a line placeholder in source with debugging summary             § M225U1 §  · §
 *   Metis § mg4·· § create a line placeholder in source with code stats summary            § M225US §  · §
 *   Metis § mg4·· § accept new urgents in è to ÿ for reporting (project wide)              § M225Ud §  · §
 *
 *   Metis § mg4·· § identify all DEBUG_ macros on first line of comment, will cause errors § M323iV §  · §
 *   Metis § mg4·· § identify all DEBUG_ macros proceeded by anything but spaces ^.*DEBUG   § M323jG §  · §
 *   Metis § mg4·· § idenfify all DEBUG_ macros attempting to use curly braces              § M323jq §  · §
 *
 */



/*====================------------------------------------====================*/
/*===----                     whole line checking                      ----===*/
/*====================------------------------------------====================*/
static void  o___WHOLE___________o () { return; }

char         /*-> increment all lines count -------------------[ leaf······ ]-*/ /*-ågcg´·5á14·á4··´636´1··´2·51·á·æ¬å2á·2··´88·á·······´···´····æ¬å>sd··´·······´····´112·æ-*/
LINE_count_all          (tFUNC *a_func, char a_inside, int *b_cfull, int *b_cproj, int *b_cfile, int *b_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_cfull     =    0;
   int         x_cproj     =    0;
   int         x_cfile     =    0;
   int         x_cfunc     =    0;
   int         x_inside    =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_cfull  = my.COUNT_LINES;
      x_cproj  = a_func->c_file->i_proj->COUNT_LINES;
      x_cfile  = a_func->c_file->COUNT_LINES;
      x_cfunc  = a_func->COUNT_LINES;
      x_inside = 1;
   } else {
      if (b_cfull   != NULL)  x_cfull  = *b_cfull;
      if (b_cproj   != NULL)  x_cproj  = *b_cproj;
      if (b_cfile   != NULL)  x_cfile  = *b_cfile;
      if (b_cfunc   != NULL)  x_cfunc  = *b_cfunc;
      x_inside = a_inside;
   }
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_note    ("update counters");
   ++x_cfull;
   ++x_cproj;
   ++x_cfile;
   if (x_inside == 1)  ++x_cfunc;
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      my.COUNT_LINES                      = x_cfull;
      a_func->c_file->i_proj->COUNT_LINES = x_cproj;
      a_func->c_file->COUNT_LINES         = x_cfile;;
      a_func->COUNT_LINES                 = x_cfunc;
   }
   /*---(save-back)----------------------*/
   if (b_cfull   != NULL)  *b_cfull  = x_cfull;
   if (b_cproj   != NULL)  *b_cproj  = x_cproj;
   if (b_cfile   != NULL)  *b_cfile  = x_cfile;
   if (b_cfunc   != NULL)  *b_cfunc  = x_cfunc;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> idenfity empty lines in code ----------------[ leaf······ ]-*/ /*-ågcg´·6á24·á4··´835´3··´1·721á·æ¬å2á·2··´EB3á··12···´···´····æ¬å>sd·>´3····43´····´117·æ-*/
LINE_count_empty        (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, int *b_cfull, int *b_cproj, int *b_cfile, int *b_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_cfull     =    0;
   int         x_cproj     =    0;
   int         x_cfile     =    0;
   int         x_cfunc     =    0;
   int         x_inside    =    0;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_cfull  = my.COUNT_EMPTY;
      x_cproj  = a_func->c_file->i_proj->COUNT_EMPTY;
      x_cfile  = a_func->c_file->COUNT_EMPTY;
      x_cfunc  = a_func->COUNT_EMPTY;
      x_inside = 1;
   } else {
      if (b_cfull   != NULL)  x_cfull  = *b_cfull;
      if (b_cproj   != NULL)  x_cproj  = *b_cproj;
      if (b_cfile   != NULL)  x_cfile  = *b_cfile;
      if (b_cfunc   != NULL)  x_cfunc  = *b_cfunc;
      x_inside = a_inside;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    (a_recd);
   /*---(prepare)------------------------*/
   ystrlcpy  (x_recd, a_recd   , LEN_RECD);
   ystrltrim (x_recd, ySTR_BOTH, LEN_RECD);
   DEBUG_DATA   yLOG_note    (x_recd);
   /*---(filter)-------------------------*/
   l = strlen (x_recd);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   if (l > 0) {
      DEBUG_DATA   yLOG_note    ("NOPE");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_note    ("update counters");
   ++x_cfull;
   ++x_cproj;
   ++x_cfile;
   if (x_inside == 1)  ++x_cfunc;
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      my.COUNT_EMPTY                      = x_cfull;
      a_func->c_file->i_proj->COUNT_EMPTY = x_cproj;
      a_func->c_file->COUNT_EMPTY         = x_cfile;;
      a_func->COUNT_EMPTY                 = x_cfunc;
   }
   /*---(save-back)----------------------*/
   if (b_cfull   != NULL)  *b_cfull  = x_cfull;
   if (b_cproj   != NULL)  *b_cproj  = x_cproj;
   if (b_cfile   != NULL)  *b_cfile  = x_cfile;
   if (b_cfunc   != NULL)  *b_cfunc  = x_cfunc;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 1;
}

char         /*-> identify full comment lines in code ---------[ leaf       ]-*/ /*-ågcg´·6á24·á4··´A36´4··´1·G21á·æ¬å2á·2··´OCCá··A2···´···´····æ¬å>sd·>´······´····´11I·-*/
LINE_count_comment      (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, int *b_cfull, int *b_cproj, int *b_cfile, int *b_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_cfull     =    0;
   int         x_cproj     =    0;
   int         x_cfile     =    0;
   int         x_cfunc     =    0;
   char        x_inside    =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        x_good      =  '-';
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_cfull  = my.COUNT_DOCS;
      x_cproj  = a_func->c_file->i_proj->COUNT_DOCS;
      x_cfile  = a_func->c_file->COUNT_DOCS;
      x_cfunc  = a_func->COUNT_DOCS;
      x_inside = 1;
   } else {
      if (b_cfull   != NULL)  x_cfull  = *b_cfull;
      if (b_cproj   != NULL)  x_cproj  = *b_cproj;
      if (b_cfile   != NULL)  x_cfile  = *b_cfile;
      if (b_cfunc   != NULL)  x_cfunc  = *b_cfunc;
      x_inside = a_inside;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    (a_recd);
   /*---(prepare)------------------------*/
   ystrlcpy  (x_recd, a_recd   , LEN_RECD);
   ystrltrim (x_recd, ySTR_BOTH, LEN_RECD);
   DEBUG_DATA   yLOG_note    (x_recd);
   /*---(filter)-------------------------*/
   l = strlen (x_recd);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   if      (strncmp ("/*"  , x_recd        , 2) == 0)  x_good = 'y';
   else if (strncmp ("/*>" , x_recd        , 3) == 0)  x_good = 'y';
   else if (strncmp ("//"  , x_recd        , 2) == 0)  x_good = 'y';
   else if (strcmp  ("*"   , x_recd           ) == 0)  x_good = 'y';
   else if (strncmp ("* "  , x_recd        , 2) == 0)  x_good = 'y';
   else if (strncmp ("*>"  , x_recd        , 2) == 0)  x_good = 'y';
   else if (strcmp  ("*/"  , x_recd           ) == 0)  x_good = 'y';
   else if (strncmp ("*/"  , x_recd + l - 2, 2) == 0)  x_good = 'y';
   else if (strncmp ("<*/" , x_recd + l - 3, 3) == 0)  x_good = 'y';
   DEBUG_DATA   yLOG_char    ("x_good"    , x_good);
   if (x_good != 'y') {
      DEBUG_DATA   yLOG_note    ("NOPE");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_note    ("update counters");
   ++x_cfull;
   ++x_cproj;
   ++x_cfile;
   if (x_inside == 1)  ++x_cfunc;
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      my.COUNT_DOCS                       = x_cfull;
      a_func->c_file->i_proj->COUNT_DOCS  = x_cproj;
      a_func->c_file->COUNT_DOCS          = x_cfile;;
      a_func->COUNT_DOCS= x_cfunc;
   }
   /*---(save-back)----------------------*/
   if (b_cfull   != NULL)  *b_cfull  = x_cfull;
   if (b_cproj   != NULL)  *b_cproj  = x_cproj;
   if (b_cfile   != NULL)  *b_cfile  = x_cfile;
   if (b_cfunc   != NULL)  *b_cfunc  = x_cfunc;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
LINE_count_debug        (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, int *b_cfull, int *b_cproj, int *b_cfile, int *b_cfunc, char *b_dcount, char *b_dextra, char *b_dmacro)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_cfull     =    0;
   int         x_cproj     =    0;
   int         x_cfile     =    0;
   int         x_cfunc     =    0;
   char        x_inside    =    0;
   char        x_dcount    =    0;
   char        x_dextra    =    0;
   char        x_dmacro    =  '-';
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char       *x_beg       = NULL;
   char        x_extra     =  '-';
   char       *p           = NULL;
   char        x_abbr      =  '-';
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_cfull  = my.COUNT_DEBUG;
      x_cproj  = a_func->c_file->i_proj->COUNT_DEBUG;
      x_cfile  = a_func->c_file->COUNT_DEBUG;
      x_cfunc  = a_func->COUNT_DEBUG;
      x_dcount = ySCORE_stats_value (my.s_yscore, "DACTIVE" );
      x_dextra = ySCORE_stats_value (my.s_yscore, "DEXTRA"  );
      x_dmacro = ySCORE_stats_value (my.s_yscore, "DMACRO"  );
      x_inside = 1;
   } else {
      if (b_cfull   != NULL)  x_cfull  = *b_cfull;
      if (b_cproj   != NULL)  x_cproj  = *b_cproj;
      if (b_cfile   != NULL)  x_cfile  = *b_cfile;
      if (b_cfunc   != NULL)  x_cfunc  = *b_cfunc;
      if (b_dcount  != NULL)  x_dcount = *b_dcount;
      if (b_dextra  != NULL)  x_dextra = *b_dextra;
      if (b_dmacro  != NULL)  x_dmacro = *b_dmacro;
      x_inside = a_inside;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    (a_recd);
   /*---(prepare)------------------------*/
   ystrlcpy     (x_recd, a_recd   , LEN_RECD);
   ystrltrim    (x_recd, ySTR_BOTH, LEN_RECD);
   ystrlunquote (x_recd, LEN_RECD);      /* remove all quoted characters */
   DEBUG_DATA   yLOG_note    (x_recd);
   /*---(filter)-------------------------*/
   l = strlen (x_recd);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   if (l < 7) {
      DEBUG_DATA   yLOG_note    ("NOPE");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   x_beg = strstr (x_recd, "DEBUG_");
   DEBUG_DATA   yLOG_point   ("x_beg"     , x_beg);
   if (x_beg == NULL) {
      DEBUG_DATA   yLOG_note    ("NOPE");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check if at start)--------------*/
   if (strncmp (x_recd, "DEBUG_", 6) == 0) {
      DEBUG_DATA   yLOG_note    ("normal");
      x_extra = '-';
   } else {
      DEBUG_DATA   yLOG_note    ("extra");
      x_extra = 'y';
   }
   /*---(find macro)---------------------*/
   p = strchr (x_beg, ' ');
   DEBUG_DATA   yLOG_point   ("p"         , p);
   if (p == NULL) {
      DEBUG_DATA   yLOG_note    ("NOPE");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   p [0] = '\0'; ++p;
   DEBUG_DATA   yLOG_note    (x_beg);
   rc = yURG_by_debug (x_beg, &x_abbr);
   DEBUG_DATA   yLOG_value   ("rc"        , rc);
   if (rc < 0)  x_abbr = '¢';
   DEBUG_DATA   yLOG_char    ("x_abbr"    , x_abbr);
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_note    ("update counters");
   ++x_cfull;
   ++x_cproj;
   ++x_cfile;
   if (x_inside == 1) {
      ++x_cfunc;
      ++x_dcount;
      if (x_extra == 'y')  ++x_dextra;
   }
   /*---(save-back)----------------------*/
   DEBUG_DATA   yLOG_char    ("x_dmacro"  , x_dmacro);
   if      (x_dmacro == '·')     x_dmacro = x_abbr;
   else if (x_dmacro == '¢')     ;
   else if (x_abbr   == '¢')     x_dmacro = x_abbr;
   else if (x_dmacro == x_abbr)  ;
   else if (x_dmacro == 'p')     x_dmacro = x_abbr;
   else if (x_abbr   == 'p')     ;
   else                          x_dmacro = '!';
   DEBUG_DATA   yLOG_char    ("x_dmacro"  , x_dmacro);
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      my.COUNT_DOCS                       = x_cfull;
      a_func->c_file->i_proj->COUNT_DOCS  = x_cproj;
      a_func->c_file->COUNT_DOCS          = x_cfile;;
      a_func->COUNT_DOCS= x_cfunc;
      ySCORE_stats_set (my.s_yscore, "DACTIVE" , x_dcount);
      ySCORE_stats_set (my.s_yscore, "DEXTRA"  , x_dextra);
      ySCORE_stats_set (my.s_yscore, "DMACRO"  , x_dmacro);
   }
   /*---(save-back)----------------------*/
   if (b_cfull   != NULL)  *b_cfull  = x_cfull;
   if (b_cproj   != NULL)  *b_cproj  = x_cproj;
   if (b_cfile   != NULL)  *b_cfile  = x_cfile;
   if (b_cfunc   != NULL)  *b_cfunc  = x_cfunc;
   if (b_dcount  != NULL)  *b_dcount = x_dcount;
   if (b_dextra  != NULL)  *b_dextra = x_dextra;
   if (b_dmacro  != NULL)  *b_dmacro = x_dmacro;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exitr   (__FUNCTION__, 1);
   return 1;
}

char
LINE_count_unguard      (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, int *b_cfull, int *b_cproj, int *b_cfile, int *b_cfunc, int *b_dcount, int *b_dfree)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char       *p           = NULL;
   char        x_good      =  '-';
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    (a_recd);
   /*---(prepare)------------------------*/
   ystrlcpy  (x_recd, a_recd   , LEN_RECD);
   ystrltrim (x_recd, ySTR_BOTH, LEN_RECD);
   DEBUG_DATA   yLOG_note    (x_recd);
   /*---(filter)-------------------------*/
   l = strlen (x_recd);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   if      (strncmp (x_recd, "yLOG_" , 5) == 0)  x_good = 'f';
   else if (strncmp (x_recd, "yLOGS_", 5) == 0)  x_good = 'y';
   else if (strncmp (x_recd, "yURG_" , 5) == 0)  x_good = 'y';
   DEBUG_INPT   yLOG_char    ("x_good"    , x_good);
   if (x_good == '-') {
      DEBUG_DATA   yLOG_note    ("NOPE");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_note    ("update counters");
   if (b_cfull != NULL)  ++(*b_cfull);
   if (b_cproj != NULL)  ++(*b_cproj);
   if (b_cfile != NULL)  ++(*b_cfile);
   if (a_inside == 1)  {
      DEBUG_DATA   yLOG_note    ("inside a function");
      if (b_cfunc  != NULL)  ++(*b_cfunc);
      if (b_dcount != NULL)  ++(*b_dcount);
      if (b_dfree  != NULL && x_good == 'f')  ++(*b_dfree);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exitr   (__FUNCTION__, 1);
   return 1;
}

char
LINE_count_code         (tFUNC *a_func, char a_inside, int *b_cfull, int *b_cproj, int *b_cfile, int *b_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_note    ("update counters");
   if (b_cfull != NULL)  ++(*b_cfull);
   if (b_cproj != NULL)  ++(*b_cproj);
   if (b_cfile != NULL)  ++(*b_cfile);
   if (a_inside == 1)  {
      DEBUG_DATA   yLOG_note    ("inside a function");
      if (b_cfunc != NULL)  ++(*b_cfunc);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
LINE_count_slocl        (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, int *b_cfull, int *b_cproj, int *b_cfile, int *b_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_recd      [LEN_RECD]  = "";
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    (a_recd);
   /*---(prepare)------------------------*/
   ystrlcpy     (x_recd, a_recd   , LEN_RECD);
   ystrltrim    (x_recd, ySTR_BOTH, LEN_RECD);
   ystrlunquote (x_recd, LEN_RECD);      /* remove all quoted characters */
   DEBUG_DATA   yLOG_note    (x_recd);
   /*---(filter)-------------------------*/
   c = ystrldcnt (x_recd, ';', LEN_RECD);
   DEBUG_DATA   yLOG_value   ("c"         , c);
   if (c < 0)  c = 0;
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_note    ("update counters");
   if (b_cfull != NULL)  *b_cfull += c;;
   if (b_cproj != NULL)  *b_cproj += c;;
   if (b_cfile != NULL)  *b_cfile += c;;
   if (a_inside == 1)  {
      DEBUG_DATA   yLOG_note    ("inside a function");
      if (b_cfunc != NULL)  *b_cfunc += c;;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                    included in line                          ----===*/
/*====================------------------------------------====================*/
static void  o___INCLUDE_________o () { return; }

char
LINE_exit               (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, char *b_return, char *b_rce)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_good      =  '-';
   char        x_recd      [LEN_RECD]  = "";
   char        x_return    =    0;
   char        x_rce       =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_return = ySCORE_stats_value (my.s_yscore, "RETURN"  );
      x_rce    = ySCORE_stats_value (my.s_yscore, "RCE"     );
   } else {
      if (b_return  != NULL)  x_return = *b_return;
      if (b_rce     != NULL)  x_rce    = *b_rce;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    (a_recd);
   DEBUG_DATA   yLOG_value   ("a_inside"  , a_inside);
   --rce;  if (a_inside != 1) {
      DEBUG_DATA   yLOG_note    ("not inside function");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   ystrlcpy     (x_recd, a_recd     , LEN_RECD);
   ystrltrim    (x_recd, ySTR_SINGLE, LEN_RECD);
   ystrlunquote (x_recd, LEN_RECD);      /* remove all quoted characters */
   DEBUG_DATA   yLOG_note    (x_recd);
   /*---(identify)-----------------------*/
   if      (strncmp (x_recd, "return rce"  , 10) == 0   )  { ++x_rce   ;  x_good = 'y'; }
   else if (strstr  (x_recd, " return rce"     ) != NULL)  { ++x_rce   ;  x_good = 'y'; }
   else if (strstr  (x_recd, ";return rce"     ) != NULL)  { ++x_rce   ;  x_good = 'y'; }
   else if (strncmp (x_recd, "return -"    ,  8) == 0   )  { ++x_rce   ;  x_good = 'y'; }
   else if (strstr  (x_recd, " return -"       ) != NULL)  { ++x_rce   ;  x_good = 'y'; }
   else if (strstr  (x_recd, ";return -"       ) != NULL)  { ++x_rce   ;  x_good = 'y'; }
   else if (strncmp (x_recd, "return "     ,  7) == 0   )  { ++x_return;  x_good = 'y'; }
   else if (strstr  (x_recd, " return "        ) != NULL)  { ++x_return;  x_good = 'y'; }
   else if (strstr  (x_recd, ";return "        ) != NULL)  { ++x_return;  x_good = 'y'; }
   else if (strncmp (x_recd, "return;"     ,  7) == 0   )  { ++x_return;  x_good = 'y'; }
   else if (strstr  (x_recd, " return;"        ) != NULL)  { ++x_return;  x_good = 'y'; }
   else if (strstr  (x_recd, ";return;"        ) != NULL)  { ++x_return;  x_good = 'y'; }
   else if (strncmp (x_recd, "return ;"    ,  8) == 0   )  { ++x_return;  x_good = 'y'; }
   else if (strstr  (x_recd, " return ;"       ) != NULL)  { ++x_return;  x_good = 'y'; }
   else if (strstr  (x_recd, ";return ;"       ) != NULL)  { ++x_return;  x_good = 'y'; }
   /*---(not found)----------------------*/
   DEBUG_INPT   yLOG_char    ("x_good"    , x_good);
   if (x_good != 'y') {
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_note    ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "RETURN"  , x_return);
      DEBUG_INPT   yLOG_value   ("ret", rc);
      rc = ySCORE_stats_set (my.s_yscore, "RCE"     , x_rce);
      DEBUG_INPT   yLOG_value   ("rce", rc);
   }
   /*---(save-back)----------------------*/
   if (b_return  != NULL)  *b_return = x_return;
   if (b_rce     != NULL)  *b_rce    = x_rce;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
LINE_choice             (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, char *b_choice)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_good      =  '-';
   char        x_recd      [LEN_RECD]  = "";
   char        x_choice    =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_choice = ySCORE_stats_value (my.s_yscore, "CHOICE"  );
   } else {
      if (b_choice  != NULL)  x_choice = *b_choice;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    (a_recd);
   DEBUG_DATA   yLOG_value   ("a_inside"  , a_inside);
   --rce;  if (a_inside != 1) {
      DEBUG_DATA   yLOG_note    ("not inside function");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   ystrlcpy     (x_recd, a_recd     , LEN_RECD);
   ystrltrim    (x_recd, ySTR_SINGLE, LEN_RECD);
   ystrlunquote (x_recd, LEN_RECD);      /* remove all quoted characters */
   DEBUG_DATA   yLOG_note    (x_recd);
   /*---(identify)-----------------------*/
   if (b_choice != NULL)  {
      if      (strncmp (x_recd, "if "         ,  3) == 0   )  { ++x_choice;  x_good = 'y'; }
      else if (strncmp (x_recd, "if("         ,  3) == 0   )  { ++x_choice;  x_good = 'y'; }
      else if (strstr  (x_recd, " if "            ) != NULL)  { ++x_choice;  x_good = 'y'; }
      else if (strstr  (x_recd, ";if "            ) != NULL)  { ++x_choice;  x_good = 'y'; }
      else if (strstr  (x_recd, " if("            ) != NULL)  { ++x_choice;  x_good = 'y'; }
      else if (strstr  (x_recd, ";if("            ) != NULL)  { ++x_choice;  x_good = 'y'; }
      else if (strncmp (x_recd, "else "       ,  5) == 0   )  { ++x_choice;  x_good = 'y'; }
      else if (strstr  (x_recd, " else "          ) != NULL)  { ++x_choice;  x_good = 'y'; }
      else if (strstr  (x_recd, ";else "          ) != NULL)  { ++x_choice;  x_good = 'y'; }
      else if (strstr  (x_recd, "}else "          ) != NULL)  { ++x_choice;  x_good = 'y'; }
      else if (strncmp (x_recd, "else{"       ,  5) == 0   )  { ++x_choice;  x_good = 'y'; }
      else if (strstr  (x_recd, " else{"          ) != NULL)  { ++x_choice;  x_good = 'y'; }
      else if (strstr  (x_recd, ";else{"          ) != NULL)  { ++x_choice;  x_good = 'y'; }
      else if (strncmp (x_recd, "}else{"      ,  6) == 0   )  { ++x_choice;  x_good = 'y'; }
      else if (strstr  (x_recd, "}else{"          ) != NULL)  { ++x_choice;  x_good = 'y'; }
      else if (strncmp (x_recd, "case "       ,  5) == 0   )  { ++x_choice;  x_good = 'y'; }
      else if (strncmp (x_recd, "default "    ,  8) == 0   )  { ++x_choice;  x_good = 'y'; }
      else if (strncmp (x_recd, "default:"    ,  8) == 0   )  { ++x_choice;  x_good = 'y'; }
   }
   /*---(not found)----------------------*/
   DEBUG_INPT   yLOG_char    ("x_good"    , x_good);
   if (x_good != 'y') {
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_note    ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "CHOICE"  , x_choice);
      DEBUG_INPT   yLOG_value   ("ch" , rc);
   }
   /*---(save-back)----------------------*/
   if (b_choice  != NULL)  *b_choice = x_choice;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
LINE_loop               (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, int *b_sfull, int *b_sproj, int *b_sfile, int *b_sfunc, char *b_loop)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        x_good      =  '-';
   char        x_loop      =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_loop   = ySCORE_stats_value (my.s_yscore, "LOOP"    );
   } else {
      if (b_loop    != NULL)  x_loop   = *b_loop;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    (a_recd);
   DEBUG_DATA   yLOG_value   ("a_inside"  , a_inside);
   --rce;  if (a_inside != 1) {
      DEBUG_DATA   yLOG_note    ("not inside function");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   ystrlcpy     (x_recd, a_recd     , LEN_RECD);
   ystrltrim    (x_recd, ySTR_SINGLE, LEN_RECD);
   ystrlunquote (x_recd, LEN_RECD);      /* remove all quoted characters */
   DEBUG_DATA   yLOG_note    (x_recd);
   /*---(identify)-----------------------*/
   if (b_loop != NULL)  {
      if      (strncmp (x_recd, "while "      ,  6) == 0   )  { ++x_loop;  x_good = 'y'; }
      else if (strstr  (x_recd, " while "         ) != NULL)  { ++x_loop;  x_good = 'y'; }
      else if (strstr  (x_recd, ";while "         ) != NULL)  { ++x_loop;  x_good = 'y'; }
      else if (strstr  (x_recd, " while( "        ) != NULL)  { ++x_loop;  x_good = 'y'; }
      else if (strncmp (x_recd, "while("      ,  6) == 0   )  { ++x_loop;  x_good = 'y'; }
      else if (strstr  (x_recd, ";while( "        ) != NULL)  { ++x_loop;  x_good = 'y'; }
      else if (strstr  (x_recd, " do "            ) != NULL)  { ++x_loop;  x_good = 'y'; }
      else if (strncmp (x_recd, "do "         ,  3) == 0   )  { ++x_loop;  x_good = 'y'; }
      else if (strstr  (x_recd, "}do "            ) != NULL)  { ++x_loop;  x_good = 'y'; }
      else if (strstr  (x_recd, " do{"            ) != NULL)  { ++x_loop;  x_good = 'y'; }
      else if (strncmp (x_recd, "do{"         ,  3) == 0   )  { ++x_loop;  x_good = 'y'; }
      else if (strstr  (x_recd, "}do("            ) != NULL)  { ++x_loop;  x_good = 'y'; }
      else if (strncmp (x_recd, "for "        ,  4) == 0   )  { ++x_loop;  x_good = 'Y'; }
      else if (strstr  (x_recd, " for "           ) != NULL)  { ++x_loop;  x_good = 'Y'; }
      else if (strstr  (x_recd, ";for "           ) != NULL)  { ++x_loop;  x_good = 'Y'; }
      else if (strncmp (x_recd, "for("        ,  4) == 0   )  { ++x_loop;  x_good = 'Y'; }
      else if (strstr  (x_recd, " for("           ) != NULL)  { ++x_loop;  x_good = 'Y'; }
      else if (strstr  (x_recd, ";for("           ) != NULL)  { ++x_loop;  x_good = 'Y'; }
   }
   /*---(not found)----------------------*/
   DEBUG_INPT   yLOG_char    ("x_good"    , x_good);
   if (strchr ("Yy", x_good) == NULL) {
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(update)-------------------------*/
   if (x_good == 'y') {
      DEBUG_DATA   yLOG_note    ("update slocl for do/while");
      if (b_sfull != NULL)  ++(*b_sfull);
      if (b_sproj != NULL)  ++(*b_sproj);
      if (b_sfile != NULL)  ++(*b_sfile);
      if (b_sfunc != NULL)  ++(*b_sfunc);
   } else {
      DEBUG_DATA   yLOG_note    ("update slocl for for");
      if (b_sfull != NULL)  --(*b_sfull);
      if (b_sproj != NULL)  --(*b_sproj);
      if (b_sfile != NULL)  --(*b_sfile);
      if (b_sfunc != NULL)  --(*b_sfunc);
   }
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_note    ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "LOOP"    , x_loop);
      DEBUG_INPT   yLOG_value   ("lo" , rc);
   }
   /*---(save-back)----------------------*/
   if (b_loop    != NULL)  *b_loop   = x_loop;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
LINE_indent             (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, char *b_indent)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   char        x_indent    =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_indent = ySCORE_stats_value (my.s_yscore, "INDENT"  );
   } else {
      if (b_indent != NULL)  x_indent = *b_indent;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    (a_recd);
   DEBUG_DATA   yLOG_value   ("a_inside"  , a_inside);
   --rce;  if (a_inside != 1) {
      DEBUG_DATA   yLOG_note    ("not inside function");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(calculate indent)---------------*/
   l = strlen (a_recd);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   for (i = 0; i < l; ++i) {
      if (a_recd [i] == ' ')   continue;
      if (i > x_indent) x_indent = i;
      break;
   }
   DEBUG_DATA   yLOG_value   ("x_indent"  , x_indent);
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_note    ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "INDENT"  , x_indent);
      DEBUG_INPT   yLOG_value   ("in" , rc);
   }
   /*---(save back)----------------------*/
   if (b_indent != NULL)  *b_indent = x_indent;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return x_indent;
}



/*====================------------------------------------====================*/
/*===----                       function related                       ----===*/
/*====================------------------------------------====================*/
static void  o___FUNCTION________o () { return; }

char
LINE__purpose           (char a_recd [LEN_RECD], int a_beg, char r_purpose [LEN_DESC], char *r_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_RECD]  = "";;
   int         i           =    0;
   int         j           =    0;
   int         l           =    0;
   char        x_style     =  '?';
   /*---(default)------------------------*/
   if (r_purpose  != NULL)  strcpy (r_purpose, "");
   if (r_style    != NULL)  *r_style = '?';
   /*---(defense)------------------------*/
   --rce;  if (a_recd == NULL)   return rce;
   l = strlen (a_recd);
   --rce;  if (l      == 0)      return rce;
   --rce;  if (a_beg  <  0)      return rce;
   --rce;  if (l      <  a_beg)  return rce;
   ystrlcpy (t, a_recd + a_beg, LEN_RECD);
   l = strlen (t);
   --rce;  if (l      <  1)      return rce;
   /*---(very end)-----------------------*/
   for (i = 0; i < l; ++i)  {
      if (strchr ("*=()[]åæ", t [i]) != NULL) {
         t [i] = '\0';
         break;
      }
      if (t [i] == '-' && t [i + 1] == '-') {
         t [i] = '\0';
         break;
      }
   }
   /*---(search)-------------------------*/
   for (j = i; j > 0; --j)  {
      if (strchr (" -=[]åæ", t [j]) == NULL)   break;
      t [j] = '\0';
   }
   /*---(evalutate)----------------------*/
   l = strlen (t);
   if      (l <=  0)  x_style = '²';
   else if (l <  20)  x_style = '<';
   else if (l <= 40)  x_style = 'y';
   else if (l <= 45)  x_style = '>';
   else               x_style = '#';
   /*---(save-back)----------------------*/
   if (r_purpose  != NULL)  ystrlcpy (r_purpose, t, 41);
   if (r_style    != NULL)  *r_style = x_style;
   /*---(complete)-----------------------*/
   return 0;
}

/*>               testing extract of a purpose                                            <* 
 *> char     /+-> ··· ··· ··· ··· ··· ··· ··· ··· --------------[ leaf·· [·-·-·]-+/   <* 
 *>               123456789-123456789-123456789-123456789-12345                       <* 
 *>                                                                                       <*/

char         /*-> extract the function purpose -------[ ------ [ge.850.137.A4]*/ /*-[02.0000.00#.!]-*/ /*-[--.---.---.--]-*/
LINE_purpose            (tFUNC *a_func, char a_recd [LEN_RECD], char *r_format, char r_purpose [LEN_DESC], char *r_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         b           =   -1;
   char        x_purpose   [LEN_DESC]  = "";
   char        x_style     =  '?';
   char        x_format    =  '?';
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_purpose != NULL)  strcpy (r_purpose, "");
   if (r_style   != NULL)  *r_style = '?';
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_recd"    , a_recd);
   /*---(modern style)-------------------*/
   if      (strncmp (a_recd, "/*-[ ", 5) == 0) {
      DEBUG_INPT   yLOG_note    ("modern format");
      b = 5;
      x_format = 'M';
   }
   /*---(current style)------------------*/
   else if (strncmp (a_recd, "/*-> ", 5) == 0) {
      DEBUG_INPT   yLOG_note    ("current format");
      b = 5;
      x_format = 'c';
   }
   /*---(previous style)-----------------*/
   else if (strncmp (a_recd, "/*--> ",  6) == 0) {
      DEBUG_INPT   yLOG_note    ("previous 1 format");
      b = 6;
      x_format = '4';
   }
   /*---(previous style)-----------------*/
   else if (strncmp (a_recd, "/* ---- : ", 10) == 0) {
      DEBUG_INPT   yLOG_note    ("previous 2 format");
      b = 10;
      x_format = '3';
   }
   /*---(previous style)-----------------*/
   else if (strncmp (a_recd, "/*----: ",  8) == 0) {
      DEBUG_INPT   yLOG_note    ("previous 3 format");
      b = 8;
      x_format = '2';
   }
   /*---(previous style)-----------------*/
   else if (strncmp (a_recd, "/*===[[ ",  8) == 0) {
      DEBUG_INPT   yLOG_note    ("previous 4 format");
      b = 8;
      x_format = '1';
   }
   /*---(terse format)-------------------*/
   else if (strncmp (a_recd, "/* ",  3) == 0) {
      DEBUG_INPT   yLOG_note    ("terse format");
      b = 3;
      x_format = 't';
   }
   /*---(empty)--------------------------*/
   else if (strcmp (a_recd, "") == 0) {
      DEBUG_INPT   yLOG_note    ("empty");
      b = -1;
      x_format = '²';
      x_style  = '²';
   }
   /*---(error)--------------------------*/
   else {
      DEBUG_INPT   yLOG_note    ("not a recognized format");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   if (b >= 0) {
      rc = LINE__purpose       (a_recd, b, x_purpose, &x_style);
      DEBUG_INPT   yLOG_value   ("purpose"   , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_note    ("save to func");
      ystrlcpy (a_func->c_purpose, x_purpose, LEN_DESC);
      a_func->c_ready = x_style;
      rc = ySCORE_stats_set  (my.s_yscore, "FORMAT"  , x_format);
      DEBUG_INPT   yLOG_value   ("FORMAT"    , rc);
      rc = ySCORE_stats_set  (my.s_yscore, "PURPOS"  , x_style);
      DEBUG_INPT   yLOG_value   ("PORPOS"    , rc);
   }
   /*---(save-back)----------------------*/
   if (r_format  != NULL)  *r_format = x_format;
   if (r_purpose != NULL)  ystrlcpy (r_purpose, x_purpose, LEN_DESC);
   if (r_style   != NULL)  *r_style  = x_style;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> identify function scope/return type ---------[ leaf······ ]-*/ /*-ågcg´·7á34·á···´K27´8··´2·#14á·æ¬å1á·1··´#GTá··M7···´···´····æ¬å>si·>´······´····´11Q·æ-*/
LINE_function           (tFUNC *a_func, char a_prev [LEN_RECD], char a_recd [LEN_RECD], char a_name [LEN_TITLE], char *r_single, char *r_scope, char *r_rtype, char r_rlong [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_single    =  '·';
   char        x_scope     =  '·';
   char        x_rtype     =  '·';
   char        x_return    [LEN_RECD]  = "";
   int         x_len       =    0;
   char       *p           = NULL;
   char       *r           = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_single != NULL)  *r_single = '·';
   if (r_scope  != NULL)  *r_scope  = '·';
   if (r_rtype  != NULL)  *r_rtype  = '·';
   if (r_rlong  != NULL)  ystrlcpy (r_rlong, "", LEN_LABEL);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_prev"    , a_prev);
   --rce;  if (a_prev == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find name)----------------------*/
   DEBUG_INPT   yLOG_note    (a_name);
   p = strstr (a_recd, a_name);
   DEBUG_INPT   yLOG_point   ("p"         , p);
   /*---(figure spacing)-----------------*/
   x_len = p - a_recd;
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   /*---(set single)---------------------*/
   if (x_len == 0)   x_single = '²';
   else              x_single = 'y';
   DEBUG_INPT   yLOG_char    ("x_single"  , x_single);
   /*---(oneline return type)------------*/
   --rce;  if (x_single == 'y') {
      ystrlcpy (x_return, a_recd, x_len);
   }
   /*---(multiline return type)----------*/
   else {
      if (a_prev == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      r = strstr (a_prev, "/*");
      if (r == NULL)  x_len = strlen (a_prev);
      else            x_len = r - a_prev;
      ystrlcpy (x_return, a_prev, x_len + 1);
   }
   ystrltrim (x_return, ySTR_SINGLE, LEN_RECD);
   DEBUG_INPT   yLOG_note    (x_return);
   /*---(classify scope)-----------------*/
   x_len = strlen (a_name);
   r = strstr (x_return, "static");
   if (r == x_return) {
      ystrlcpy  (x_return, x_return  + 7, LEN_RECD);
      ystrltrim (x_return, ySTR_SINGLE, LEN_RECD);
      x_scope = 's';
   }
   else if (strncmp (a_name + x_len - 6, "__unit" , 6) == 0   )  x_scope = 'u';
   else if (strstr  (a_name            , "__unit"    ) != NULL)  x_scope = 'u';
   else if (strncmp (a_name + x_len - 6, "__fake" , 6) == 0   )  x_scope = 'u';
   else if (strstr  (a_name            , "__fake"    ) != NULL)  x_scope = 'u';
   else if (strstr  (a_name            , "__"        ) != NULL)  x_scope = 'f';
   else                                                          x_scope = 'g';
   DEBUG_INPT   yLOG_char    ("x_scope"   , x_scope);
   /*---(classify return type)-----------*/
   x_len = strlen (x_return);
   if      (strcmp (x_return   , "char*"  ) == 0   )  x_rtype = 's';
   else if (strcmp (x_return   , "char *" ) == 0   )  x_rtype = 's';
   else if (strcmp (x_return   , "char"   ) == 0   )  x_rtype = 'c';
   else if (strcmp (x_return   , "void"   ) == 0   )  x_rtype = 'v';
   else if (strcmp (x_return   , "short"  ) == 0   )  x_rtype = 'n';
   else if (strcmp (x_return   , "int"    ) == 0   )  x_rtype = 'n';
   else if (strcmp (x_return   , "long"   ) == 0   )  x_rtype = 'n';
   else if (strcmp (x_return   , "float"  ) == 0   )  x_rtype = 'n';
   else if (strcmp (x_return   , "double" ) == 0   )  x_rtype = 'n';
   else if (strstr (x_return   , "**"     ) != NULL)  x_rtype = 'P';
   else if (strstr (x_return   , "*"      ) != NULL)  x_rtype = 'p';
   else                                               x_rtype = 'o';
   DEBUG_INPT   yLOG_char    ("x_rtype"   , x_rtype);
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_note    ("save to func");
      rc = ySCORE_stats_set  (my.s_yscore, "SINGLE"  , x_single);
      DEBUG_INPT   yLOG_value   ("SINGLE"    , rc);
      rc = ySCORE_stats_set  (my.s_yscore, "SCOPE"   , x_scope);
      DEBUG_INPT   yLOG_value   ("SCOPE"     , rc);
      rc = ySCORE_stats_set  (my.s_yscore, "RTYPE"   , x_rtype);
      DEBUG_INPT   yLOG_value   ("RTYPE"     , rc);
      ystrlcpy (a_func->c_rlong, x_return, LEN_LABEL);
   }
   /*---(save-back)----------------------*/
   if (r_single != NULL)  *r_single = x_single;
   if (r_scope  != NULL)  *r_scope  = x_scope;
   if (r_rtype  != NULL)  *r_rtype  = x_rtype;
   if (r_rlong  != NULL && x_len < LEN_LABEL)  ystrlcpy (r_rlong, x_return, LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
LINE__params_cut        (char a_recd [LEN_RECD], char r_params [LEN_RECD], char *r_audit, char *r_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *x_beg       = NULL;
   char       *x_end       = NULL;
   int         x_len       =    0;
   char        x_params    [LEN_RECD]  = "";
   int         x_open      =    0;
   int         x_close     =    0;
   int         i           =    0;
   int         j           =    0;
   char        x_final     [LEN_RECD]  = "";
   char        x_on        =    1;
   int         x_count     =   -1;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_params != NULL)   strcpy (r_params, "");
   if (r_audit  != NULL)   *r_audit =  '?';
   if (r_count  != NULL)   *r_count =   -2;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("r_params"  , r_params);
   --rce;  if (r_params == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find beg)-----------------------*/
   if (r_audit  != NULL)   *r_audit =  '<';
   x_beg = strchr (a_recd, '(');
   DEBUG_DATA   yLOG_point   ("x_beg"     , x_beg);
   --rce;  if (x_beg == NULL) {
      DEBUG_DATA   yLOG_note    ("can not find '(' start)");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find max end)-------------------*/
   x_end = strchr (a_recd, '{');
   DEBUG_DATA   yLOG_point   ("x_end"     , x_end);
   if (x_end == NULL)  x_len = LEN_RECD;
   else                x_len = x_end - x_beg;
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   ystrlcpy  (x_params, x_beg, x_len);
   ystrltrim (x_params, ySTR_SINGLE, x_len);
   x_len = strlen (x_params);
   /*---(check symmetry)-----------------*/
   if (r_audit  != NULL)   *r_audit =  '<';
   x_open  = ystrldcnt (x_params, '(', LEN_RECD);
   DEBUG_INPT   yLOG_value   ("x_open"    , x_open);
   --rce;  if (x_open  < 1) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (r_audit  != NULL)   *r_audit =  '>';
   x_close = ystrldcnt (x_params, ')', LEN_RECD);
   DEBUG_INPT   yLOG_value   ("x_close"   , x_close);
   --rce;  if (x_close < 1) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (r_audit  != NULL)   *r_audit =  '=';
   --rce;  if (x_open  != x_close) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check symmetry)-----------------*/
   x_on = 0;
   --rce;  for (i = j = 0; i <= x_len; ++i) {
      if (x_params [i] == ')') {
         DEBUG_INPT   yLOG_note    (")");
         --x_on;
         if (x_on <= 0 && i < x_len - 1) {
            DEBUG_INPT   yLOG_value   ("i"         , i);
            DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         if (x_on < 0) {
            DEBUG_INPT   yLOG_value   ("i"         , i);
            DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      if (x_on == 1)  x_final [j++] = x_params [i];
      if (x_params [i] == '(') {
         DEBUG_INPT   yLOG_value   ("i"         , i);
         DEBUG_INPT   yLOG_note    ("(");
         ++x_on;
      }
   }
   if (r_audit  != NULL)   *r_audit =  '#';
   DEBUG_INPT   yLOG_value   ("x_on"      , x_on);
   if (x_on > 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check none/void)----------------*/
   if      (strcmp (x_params, "()")       == 0)  x_count = -2;
   else if (strcmp (x_params, "( )")      == 0)  x_count = -2;
   else if (strcmp (x_params, "(void)")   == 0)  x_count = -1;
   else if (strcmp (x_params, "( void)")  == 0)  x_count = -1;
   else if (strcmp (x_params, "(void )")  == 0)  x_count = -1;
   else if (strcmp (x_params, "( void )") == 0)  x_count = -1;
   else                                          x_count =  0;
   DEBUG_INPT   yLOG_value   ("x_count"   , x_count);
   /*---(final touches)------------------*/
   ystrltrim (x_final, ySTR_BOTH, LEN_RECD);
   x_len = strlen (x_final);
   if (x_count == 0) {
      x_count = ystrldcnt (x_final, ',', x_len) + 1;
      if (x_count <  0)   x_count = 0;
   }
   /*---(save-back)----------------------*/
   if (r_params != NULL)   ystrlcpy (r_params, x_final, LEN_RECD);
   if (r_audit  != NULL)   *r_audit =  'y';
   if (r_count  != NULL)   *r_count = x_count;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   if (x_count < 0)  return 1;
   return 0;
}

char
LINE__params_parse      (char a_param [LEN_RECD], char r_type [LEN_LABEL], char r_label [LEN_LABEL], char *r_point, char *r_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_work      [LEN_RECD]  = "";
   int         i           =    0;
   int         x_len       =    0;
   char       *p           = NULL;
   char        x_type      [LEN_LABEL] = "";
   char        x_label     [LEN_LABEL] = "";
   char        x_point     =    0;
   char        x_func      =  '-';
   /*---(default)------------------------*/
   if (r_type   != NULL)   strcpy (r_type  , "");
   if (r_label  != NULL)   strcpy (r_label , "");
   if (r_point  != NULL)   *r_point = 0;
   if (r_func   != NULL)   *r_func  = '-';
   /*---(defense)------------------------*/
   --rce;  if (a_param  == NULL || a_param [0] == '\0')  return rce;
   /*---(working copy)-------------------*/
   ystrlcpy  (x_work, a_param    , LEN_RECD);
   ystrltrim (x_work, ySTR_SINGLE, LEN_RECD);
   /*---(function)-----------------------*/
   p = strchr (x_work, '(');
   if (p != NULL) {
      ++x_point;
      x_func = 'y';
      p [0] = '\0';
   }
   /*---(suffix)-------------------------*/
   p = strchr (x_work, '[');
   while (p != NULL) {
      ++x_point;
      p [0] = '\0';
      p = strchr (p + 1, '[');
   }
   /*---(clean-up)-----------------------*/
   ystrltrim (x_work, ySTR_BOTH, LEN_RECD);
   x_len = strlen (x_work);
   /*---(label)--------------------------*/
   for (i = x_len - 1; i > 0; --i) {
      p = x_work + i;
      switch (x_work [i]) {
      case '*' :  ++x_point;
      case ' ' :  p [0] = '\0';
                  ystrlcpy (x_label, x_work + i + 1, LEN_LABEL);
                  break;
      default  :  continue;
                  break;
      }
      break;
   }
   /*---(pointers)-----------------------*/
   x_len = strlen (x_work);
   for (i = x_len - 1; i > 0; --i) {
      if (x_work [i] != '*')  break;
      ++x_point;
      x_work [i] = '\0';
   }
   /*---(clean-up)-----------------------*/
   ystrltrim (x_work, ySTR_BOTH, LEN_RECD);
   /*---(save-back)----------------------*/
   if (r_type   != NULL)   ystrlcpy (r_type  , x_work , LEN_LABEL);
   if (r_label  != NULL)   ystrlcpy (r_label , x_label, LEN_LABEL);
   if (r_point  != NULL)   *r_point = x_point;
   if (r_func   != NULL)   *r_func  = x_func;
   /*---(complete)-----------------------*/
   return 1;
}

char
LINE__params_class      (char a_label [LEN_LABEL], char *r_class, uchar *b_in, uchar *b_out, uchar *b_both, uchar *b_conf, uchar *b_diag, uchar *b_older)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_class     =  '-';
   /*---(default)------------------------*/
   if (r_class  != NULL)   *r_class = '-';
   /*---(defense)------------------------*/
   --rce;  if (a_label == NULL || a_label [0] == '\0')  return rce;
   --rce;  if (r_class == NULL)                         return rce;
   /*---(decide)-------------------------*/
   if      (strncmp (a_label, "a_"    , 2) == 0)  { x_class = 'a';  if (b_in    != NULL)  ++(*b_in);    }
   else if (strncmp (a_label, "r_"    , 2) == 0)  { x_class = 'r';  if (b_out   != NULL)  ++(*b_out);   }
   else if (strncmp (a_label, "b_"    , 2) == 0)  { x_class = 'b';  if (b_both  != NULL)  ++(*b_both);  }
   else if (strncmp (a_label, "c_"    , 2) == 0)  { x_class = 'c';  if (b_conf  != NULL)  ++(*b_conf);  }
   else if (strncmp (a_label, "d_"    , 2) == 0)  { x_class = 'd';  if (b_diag  != NULL)  ++(*b_diag);  }
   else if (strncmp (a_label, "e_"    , 2) == 0)  { x_class = 'e';                                      }
   else                                                          {  if (b_older != NULL)  ++(*b_older); }
   /*---(save-back)----------------------*/
   if (r_class  != NULL)   *r_class = x_class;
   /*---(complete)-----------------------*/
   if (x_class == '-')  return 0;
   return 1;
}

char
LINE__params_point      (char a_type [LEN_LABEL], char a_point, char a_func, char a_class, uchar *b_pnum, uchar *b_pmulti, uchar *b_pfunc, uchar *b_pstruc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_numeric   =  '-';
   char        x_struc     =  '-';
   char        x_found     =  'y';
   /*---(type)---------------------------*/
   if      (strstr (a_type, "float"   ) != NULL)    x_numeric = 'y';
   else if (strstr (a_type, "double"  ) != NULL)    x_numeric = 'y';
   else if (strstr (a_type, "short"   ) != NULL)    x_numeric = 'y';
   else if (strstr (a_type, "int"     ) != NULL)    x_numeric = 'y';
   else if (strstr (a_type, "long"    ) != NULL)    x_numeric = 'y';
   else if (strstr (a_type, "char"    ) != NULL)    ;
   else if (strstr (a_type, "void"    ) != NULL)    ;
   else                                              x_struc   = 'y';
   /*---(combos)-------------------------*/
   if      (a_class   == 'e' || a_func   == 'y')  { if (b_pfunc   != NULL)  ++(*b_pfunc);   }
   else if (x_struc   == 'y' && a_point  >   0 )  { if (b_pstruc  != NULL)  ++(*b_pstruc);  }
   else if (x_numeric == 'y' && a_point  ==  1 )  { if (b_pnum    != NULL)  ++(*b_pnum);    }
   else if (a_point   >   1)                      { if (b_pmulti  != NULL)  ++(*b_pmulti);  }
   else     x_found   = '-';
   /*---(complete)-----------------------*/
   if (x_found == '-')  return 0;
   return 1;
}

char
LINE__params_one        (char a_param [LEN_RECD], uchar *b_in, uchar *b_out, uchar *b_both, uchar *b_conf, uchar *b_diag, uchar *b_older, uchar *b_pnum, uchar *b_pmulti, uchar *b_pfunc, uchar *b_pstruc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      [LEN_LABEL] = "";
   char        x_label     [LEN_LABEL] = "";
   char        x_point     =    0;
   char        x_func      =    0;
   char        x_class     =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_param"   , a_param);
   --rce;  if (a_param  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(parse)--------------------------*/
   rc = LINE__params_parse (a_param, x_type, x_label, &x_point, &x_func);
   DEBUG_DATA   yLOG_value   ("parse"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(direction)----------------------*/
   rc = LINE__params_class (x_label, &x_class, b_in, b_out, b_both, b_conf, b_diag, b_older);
   DEBUG_DATA   yLOG_value   ("class"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(point)--------------------------*/
   rc = LINE__params_point (x_type, x_point, x_func, x_class, b_pnum, b_pmulti, b_pfunc, b_pstruc);
   DEBUG_DATA   yLOG_value   ("point"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> evaluate function parameter list ------------[ ´········· ]-*/ /*-ågcg´·Bá1A··á9··á·´D17´H··´11M22á·æ¬å1á·1··´C84á2·2····´···´····æ¬å>l!··´2···2··´····´114·æ-*/
LINE_params             (tFUNC *a_func, char a_recd [LEN_RECD], char *r_audit, uchar *r_count, uchar *b_in, uchar *b_out, uchar *b_both, uchar *b_conf, uchar *b_diag, uchar *b_older, uchar *b_pnum, uchar *b_pmulti, uchar *b_pfunc, uchar *b_pstruc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   char       *q           =  ",";
   char       *r           = NULL;
   char       x_params     [LEN_RECD];
   char       x_au;
   char       x_co;
   uchar      x_in, x_ou, x_bo, x_cf, x_dg, x_ol, x_pn, x_pm, x_pf, x_ps;
   int        c            =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_audit   != NULL)  *r_audit   = '?';
   if (r_count   != NULL)  *r_count   =  -2;
   if (b_in      != NULL)  *b_in      =   0;
   if (b_out     != NULL)  *b_out     =   0;
   if (b_both    != NULL)  *b_both    =   0;
   if (b_conf    != NULL)  *b_conf    =   0;
   if (b_diag    != NULL)  *b_diag    =   0;
   if (b_older   != NULL)  *b_older   =   0;
   if (b_pnum    != NULL)  *b_pnum    =   0;
   if (b_pmulti  != NULL)  *b_pmulti  =   0;
   if (b_pfunc   != NULL)  *b_pfunc   =   0;
   if (b_pstruc  != NULL)  *b_pstruc  =   0;
   x_co = x_in = x_ou = x_bo = x_cf = x_dg = x_ol = x_pn = x_pm = x_pf = x_ps = 0;
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      rc = ySCORE_stats_set (my.s_yscore, "PPAREN"  , x_au);
      rc = ySCORE_stats_set (my.s_yscore, "PARAMS"  , x_co);
      rc = ySCORE_stats_set (my.s_yscore, "PIN"     , x_in);
      rc = ySCORE_stats_set (my.s_yscore, "POUT"    , x_ou);
      rc = ySCORE_stats_set (my.s_yscore, "PBOTH"   , x_bo);
      rc = ySCORE_stats_set (my.s_yscore, "PCONF"   , x_cf);
      rc = ySCORE_stats_set (my.s_yscore, "PDIAC"   , x_dg);
      rc = ySCORE_stats_set (my.s_yscore, "POLDER"  , x_ol);
      rc = ySCORE_stats_set (my.s_yscore, "PNUM"    , x_pn);
      rc = ySCORE_stats_set (my.s_yscore, "PMULTI"  , x_pm);
      rc = ySCORE_stats_set (my.s_yscore, "PFUNC"   , x_pf);
      rc = ySCORE_stats_set (my.s_yscore, "PSTRUC"  , x_ps);
   }
   /*---(prepare)------------------------*/
   rc = LINE__params_cut        (a_recd, x_params, &x_au, &x_co);
   DEBUG_DATA   yLOG_value   ("cut"       , rc);
   DEBUG_INPT   yLOG_value   ("x_au"      , x_au);
   DEBUG_INPT   yLOG_value   ("x_co"      , x_co);
   --rce;  switch (x_co) {
   case -2  :
      rc = ySCORE_stats_set (my.s_yscore, "PPAREN"  , '?');
      rc = ySCORE_stats_set (my.s_yscore, "PARAMS"  ,  0 );
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   case -1  :
      rc = ySCORE_stats_set (my.s_yscore, "PPAREN"  , 'v');
      rc = ySCORE_stats_set (my.s_yscore, "PARAMS"  ,  0 );
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   case  0  :
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
      break;
   }
   /*---(parse)--------------------------*/
   p = strtok_r (x_params, q, &r);
   while (p != NULL) {
      rc = LINE__params_one      (p, &x_in, &x_ou, &x_bo, &x_cf, &x_dg, &x_ol, &x_pn, &x_pm, &x_pf, &x_ps);
      if (rc < 0)  break;
      ++c;
      p  = strtok_r (NULL, q, &r);
   }
   /*---(trouble)------------------------*/
   DEBUG_INPT   yLOG_value   ("c"         , c);
   --rce;  if (c != x_co) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_note    ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "PPAREN"  , x_au);
      DEBUG_INPT   yLOG_value   ("au", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PARAMS"  , x_co);
      DEBUG_INPT   yLOG_value   ("co", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PIN"     , x_in);
      DEBUG_INPT   yLOG_value   ("in", rc);
      rc = ySCORE_stats_set (my.s_yscore, "POUT"    , x_ou);
      DEBUG_INPT   yLOG_value   ("ou", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PBOTH"   , x_bo);
      DEBUG_INPT   yLOG_value   ("bo", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PCONF"   , x_cf);
      DEBUG_INPT   yLOG_value   ("cf", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PDIAG"   , x_dg);
      DEBUG_INPT   yLOG_value   ("vo", rc);
      rc = ySCORE_stats_set (my.s_yscore, "POLDER"  , x_ol);
      DEBUG_INPT   yLOG_value   ("ol", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PNUM"    , x_pn);
      DEBUG_INPT   yLOG_value   ("pn", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PMULTI"  , x_pm);
      DEBUG_INPT   yLOG_value   ("pm", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PFUNC"   , x_pf);
      DEBUG_INPT   yLOG_value   ("pf", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PSTRUC"  , x_ps);
      DEBUG_INPT   yLOG_value   ("ps", rc);
   }
   /*---(save-back)----------------------*/
   if (r_audit   != NULL)  *r_audit   = x_au;
   if (r_count   != NULL)  *r_count   = x_co;
   if (b_in      != NULL)  *b_in      = x_in;
   if (b_out     != NULL)  *b_out     = x_ou;
   if (b_both    != NULL)  *b_both    = x_bo;
   if (b_conf    != NULL)  *b_conf    = x_cf;
   if (b_diag    != NULL)  *b_diag    = x_dg;
   if (b_older   != NULL)  *b_older   = x_ol;
   if (b_pnum    != NULL)  *b_pnum    = x_pn;
   if (b_pmulti  != NULL)  *b_pmulti  = x_pm;
   if (b_pfunc   != NULL)  *b_pfunc   = x_pf;
   if (b_pstruc  != NULL)  *b_pstruc  = x_ps;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char         /*-> force data onto function --------------------[ leaf······ ]-*/ /*-åucg´·4á3··1á···á1´2·A´1··´··111á·æ¬å·á····´···á·······´···´····æ¬å·····´3·3····´····´····æ-*/
LINE__fake              (int a_return, int a_intern, int a_ylib, tFUNC *c_func)
{
   char        rce         =  -10;
   --rce;  if (c_func == NULL)  return rce;
   c_func->WORK_RETURN  = a_return;
   c_func->WORK_GFUNCS  = a_intern;
   c_func->WORK_YLIB    = a_ylib;
   return 0;
}

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
LINE__unit              (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   char        r           [LEN_RECD] = "";
   char        s           [LEN_LABEL]= "";
   tFUNC      *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "DEBUG unit       : function number unknown");
   if (strcmp (a_question, "work"      )     == 0) {
      FUNCS_by_index     (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->c_name);
         if (u->WORK_DCOUNT > 0)  sprintf (s, " %3dc", u->WORK_DCOUNT);
         else                     sprintf (s, "   ·c");
         ystrlcat (r, s, LEN_RECD);
         if (u->WORK_DFREE  > 0)  sprintf (s, " %3df", u->WORK_DFREE );
         else                     sprintf (s, "   ·f");
         ystrlcat (r, s, LEN_RECD);
         ystrlcat (r, "   ", LEN_RECD);
         if (u->WORK_DLONG  > 0)  sprintf (s, " %3dn", u->WORK_DLONG );
         else                     sprintf (s, "   ·n");
         ystrlcat (r, s, LEN_RECD);
         if (u->WORK_DSHORT > 0)  sprintf (s, " %3ds", u->WORK_DSHORT);
         else                     sprintf (s, "   ·s");
         ystrlcat (r, s, LEN_RECD);
         if (u->WORK_DENTER > 0)  sprintf (s, " %3de", u->WORK_DENTER);
         else                     sprintf (s, "   ·e");
         ystrlcat (r, s, LEN_RECD);
         if (u->WORK_DEXITR > 0)  sprintf (s, " %3dr", u->WORK_DEXITR);
         else                     sprintf (s, "   ·r");
         ystrlcat (r, s, LEN_RECD);
         if (u->WORK_DEXIT  > 0)  sprintf (s, " %3dx", u->WORK_DEXIT );
         else                     sprintf (s, "   ·x");
         ystrlcat (r, s, LEN_RECD);
         ystrlcat (r, "     ", LEN_RECD);
         sprintf (s, " %c", u->STATS_DMACRO);
         ystrlcat (r, s, LEN_RECD);
         snprintf (unit_answer, LEN_RECD, "DEBUG work  (%2d) : %-22.22s  %s", i, t, r);
      }  else
         snprintf (unit_answer, LEN_RECD, "DEBUG work  (%2d) : %-22.22s    -c   -f      -n   -s   -e   -r   -x      -", i, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


