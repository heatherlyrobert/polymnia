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
LINE_count_all          (char a_inside, int *b_cfull, int *b_cproj, int *b_cfile, int *b_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("update counters");
   if (b_cfull != NULL)    ++(*b_cfull);
   if (b_cproj != NULL)    ++(*b_cproj);
   if (b_cfile != NULL)    ++(*b_cfile);
   /*---(function-level)-----------------*/
   if (b_cfunc != NULL && a_inside == 1)  ++(*b_cfunc);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> idenfity empty lines in code ----------------[ leaf······ ]-*/ /*-ågcg´·6á24·á4··´835´3··´1·721á·æ¬å2á·2··´EB3á··12···´···´····æ¬å>sd·>´3····43´····´117·æ-*/
LINE_count_empty        (char a_recd [LEN_RECD], char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_recd);
   /*---(prepare)------------------------*/
   ystrlcpy  (x_recd, a_recd   , LEN_RECD);
   ystrltrim (x_recd, ySTR_BOTH, LEN_RECD);
   DEBUG_DATA   yLOG_snote   (x_recd);
   /*---(filter)-------------------------*/
   l = strlen (x_recd);
   DEBUG_DATA   yLOG_sint    (l);
   if (l > 0) {
      DEBUG_DATA   yLOG_snote   ("NOPE");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("update counters");
   if (r_cfull != NULL)  ++(*r_cfull);
   if (r_cproj != NULL)  ++(*r_cproj);
   if (r_cfile != NULL)  ++(*r_cfile);
   if (a_inside == 1)  {
      DEBUG_DATA   yLOG_snote   ("inside a function");
      if (r_cfunc != NULL)  ++(*r_cfunc);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char         /*-> identify full comment lines in code ---------[ leaf       ]-*/ /*-ågcg´·6á24·á4··´A36´4··´1·G21á·æ¬å2á·2··´OCCá··A2···´···´····æ¬å>sd·>´······´····´11I·-*/
LINE_count_comment      (char a_recd [LEN_RECD], char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_recd      [LEN_RECD]  = "";
   char        x_good      =  '-';
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_recd);
   /*---(prepare)------------------------*/
   ystrlcpy  (x_recd, a_recd   , LEN_RECD);
   ystrltrim (x_recd, ySTR_BOTH, LEN_RECD);
   DEBUG_DATA   yLOG_snote   (x_recd);
   /*---(filter)-------------------------*/
   l = strlen (x_recd);
   DEBUG_DATA   yLOG_sint    (l);
   if      (strncmp ("/*"  , x_recd        , 2) == 0)  x_good = 'y';
   else if (strncmp ("/*>" , x_recd        , 3) == 0)  x_good = 'y';
   else if (strncmp ("//"  , x_recd        , 2) == 0)  x_good = 'y';
   else if (strcmp  ("*"   , x_recd           ) == 0)  x_good = 'y';
   else if (strncmp ("* "  , x_recd        , 2) == 0)  x_good = 'y';
   else if (strncmp ("*>"  , x_recd        , 2) == 0)  x_good = 'y';
   else if (strcmp  ("*/"  , x_recd           ) == 0)  x_good = 'y';
   else if (strncmp ("*/"  , x_recd + l - 2, 2) == 0)  x_good = 'y';
   else if (strncmp ("<*/" , x_recd + l - 3, 3) == 0)  x_good = 'y';
   DEBUG_DATA   yLOG_schar   (x_good);
   if (x_good != 'y') {
      DEBUG_DATA   yLOG_snote   ("NOPE");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("update counters");
   if (r_cfull != NULL)  ++(*r_cfull);
   if (r_cproj != NULL)  ++(*r_cproj);
   if (r_cfile != NULL)  ++(*r_cfile);
   if (a_inside == 1)  {
      DEBUG_DATA   yLOG_snote   ("inside a function");
      if (r_cfunc != NULL)  ++(*r_cfunc);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
LINE_count_debug        (char a_recd [LEN_RECD], char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc, int *r_dcount, int *r_dextra, char *r_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char       *x_beg       = NULL;
   char        x_extra     =  '-';
   char       *p           = NULL;
   char        x_abbr      =  '-';
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_recd);
   /*---(prepare)------------------------*/
   ystrlcpy     (x_recd, a_recd   , LEN_RECD);
   ystrltrim    (x_recd, ySTR_BOTH, LEN_RECD);
   ystrlunquote (x_recd, LEN_RECD);      /* remove all quoted characters */
   DEBUG_DATA   yLOG_snote   (x_recd);
   /*---(filter)-------------------------*/
   l = strlen (x_recd);
   DEBUG_DATA   yLOG_sint    (l);
   if (l < 7) {
      DEBUG_DATA   yLOG_snote   ("NOPE");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   x_beg = strstr (x_recd, "DEBUG_");
   DEBUG_DATA   yLOG_spoint  (x_beg);
   if (x_beg == NULL) {
      DEBUG_DATA   yLOG_snote   ("NOPE");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(check if at start)--------------*/
   if (strncmp (x_recd, "DEBUG_", 6) == 0) {
      DEBUG_DATA   yLOG_snote   ("normal");
      x_extra = '-';
   } else {
      DEBUG_DATA   yLOG_snote   ("extra");
      x_extra = 'y';
   }
   /*---(find macro)---------------------*/
   p = strchr (x_beg, ' ');
   DEBUG_DATA   yLOG_spoint  (p);
   if (p == NULL) {
      DEBUG_DATA   yLOG_snote   ("NOPE");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   p [0] = '\0'; ++p;
   DEBUG_DATA   yLOG_snote   (x_beg);
   rc = yURG_by_debug (x_beg, &x_abbr);
   DEBUG_DATA   yLOG_sint    (rc);
   if (rc < 0)  x_abbr = '¢';
   DEBUG_DATA   yLOG_schar   (x_abbr);
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("update counters");
   if (r_cfull  != NULL)  ++(*r_cfull);
   if (r_cproj  != NULL)  ++(*r_cproj);
   if (r_cfile  != NULL)  ++(*r_cfile);
   if (a_inside == 1)  {
      DEBUG_DATA   yLOG_snote   ("inside a function");
      if (r_cfunc  != NULL)  ++(*r_cfunc);
      if (r_dcount != NULL)  ++(*r_dcount);
      if (x_extra == 'y' && r_dextra != NULL)  ++(*r_dextra);
   }
   /*---(save-back)----------------------*/
   if (r_abbr  != NULL) {
      DEBUG_DATA   yLOG_schar   (*r_abbr);
      if      (*r_abbr == '·')     *r_abbr = x_abbr;
      else if (*r_abbr == '¢')     ;
      else if (x_abbr  == '¢')     *r_abbr = x_abbr;
      else if (*r_abbr == x_abbr)  ;
      else if (*r_abbr == 'p')     *r_abbr = x_abbr;
      else if (x_abbr  == 'p')     ;
      else                         *r_abbr = '!';
      DEBUG_DATA   yLOG_schar   (*r_abbr);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, 1);
   return 1;
}

char
LINE_count_unguard      (char a_recd [LEN_RECD], char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc, int *r_dcount, int *r_dfree)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char       *p           = NULL;
   char        x_good      =  '-';
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_recd);
   /*---(prepare)------------------------*/
   ystrlcpy  (x_recd, a_recd   , LEN_RECD);
   ystrltrim (x_recd, ySTR_BOTH, LEN_RECD);
   DEBUG_DATA   yLOG_snote   (x_recd);
   /*---(filter)-------------------------*/
   l = strlen (x_recd);
   DEBUG_DATA   yLOG_sint    (l);
   if      (strncmp (x_recd, "yLOG_" , 5) == 0)  x_good = 'f';
   else if (strncmp (x_recd, "yLOGS_", 5) == 0)  x_good = 'y';
   else if (strncmp (x_recd, "yURG_" , 5) == 0)  x_good = 'y';
   DEBUG_DATA   yLOG_schar   (x_good);
   if (x_good == '-') {
      DEBUG_DATA   yLOG_snote   ("NOPE");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("update counters");
   if (r_cfull != NULL)  ++(*r_cfull);
   if (r_cproj != NULL)  ++(*r_cproj);
   if (r_cfile != NULL)  ++(*r_cfile);
   if (a_inside == 1)  {
      DEBUG_DATA   yLOG_snote   ("inside a function");
      if (r_cfunc  != NULL)  ++(*r_cfunc);
      if (r_dcount != NULL)  ++(*r_dcount);
      if (r_dfree  != NULL && x_good == 'f')  ++(*r_dfree);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, 1);
   return 1;
}

char
LINE_count_code         (char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("update counters");
   if (r_cfull != NULL)  ++(*r_cfull);
   if (r_cproj != NULL)  ++(*r_cproj);
   if (r_cfile != NULL)  ++(*r_cfile);
   if (a_inside == 1)  {
      DEBUG_DATA   yLOG_snote   ("inside a function");
      if (r_cfunc != NULL)  ++(*r_cfunc);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
LINE_count_slocl        (char a_recd [LEN_RECD], char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_recd      [LEN_RECD]  = "";
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_recd);
   /*---(prepare)------------------------*/
   ystrlcpy     (x_recd, a_recd   , LEN_RECD);
   ystrltrim    (x_recd, ySTR_BOTH, LEN_RECD);
   ystrlunquote (x_recd, LEN_RECD);      /* remove all quoted characters */
   DEBUG_DATA   yLOG_snote   (x_recd);
   /*---(filter)-------------------------*/
   c = ystrldcnt (x_recd, ';', LEN_RECD);
   DEBUG_DATA   yLOG_sint    (c);
   if (c < 0)  c = 0;
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("update counters");
   if (r_cfull != NULL)  *r_cfull += c;;
   if (r_cproj != NULL)  *r_cproj += c;;
   if (r_cfile != NULL)  *r_cfile += c;;
   if (a_inside == 1)  {
      DEBUG_DATA   yLOG_snote   ("inside a function");
      if (r_cfunc != NULL)  *r_cfunc += c;;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                    included in line                          ----===*/
/*====================------------------------------------====================*/
static void  o___INCLUDE_________o () { return; }

char
LINE_exit               (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, char *r_return, char *r_rce)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_good      =  '-';
   char        x_recd      [LEN_RECD]  = "";
   char        x_return    =    0;
   char        x_rce       =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_return = ySCORE_stats_value (my.s_yscore, "RETURN"  );
      x_rce    = ySCORE_stats_value (my.s_yscore, "RCE"     );
   } else {
      if (r_return  != NULL)  x_return = *r_return;
      if (r_rce     != NULL)  x_rce    = *r_rce;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_recd);
   DEBUG_DATA   yLOG_sint    (a_inside);
   --rce;  if (a_inside != 1) {
      DEBUG_DATA   yLOG_snote   ("not inside function");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   ystrlcpy     (x_recd, a_recd     , LEN_RECD);
   ystrltrim    (x_recd, ySTR_SINGLE, LEN_RECD);
   ystrlunquote (x_recd, LEN_RECD);      /* remove all quoted characters */
   DEBUG_DATA   yLOG_snote   (x_recd);
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
   DEBUG_DATA   yLOG_schar   (x_good);
   if (x_good != 'y') {
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_snote   ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "RETURN"  , x_return);
      DEBUG_INPT   yLOG_svalue  ("ret", rc);
      rc = ySCORE_stats_set (my.s_yscore, "RCE"     , x_rce);
      DEBUG_INPT   yLOG_svalue  ("rce", rc);
   }
   /*---(save-back)----------------------*/
   if (r_return  != NULL)  *r_return = x_return;
   if (r_rce     != NULL)  *r_rce    = x_rce;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
LINE_choice             (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, char *r_choice)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_good      =  '-';
   char        x_recd      [LEN_RECD]  = "";
   char        x_choice    =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_choice = ySCORE_stats_value (my.s_yscore, "CHOICE"  );
   } else {
      if (r_choice  != NULL)  x_choice = *r_choice;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_recd);
   DEBUG_DATA   yLOG_sint    (a_inside);
   --rce;  if (a_inside != 1) {
      DEBUG_DATA   yLOG_snote   ("not inside function");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   ystrlcpy     (x_recd, a_recd     , LEN_RECD);
   ystrltrim    (x_recd, ySTR_SINGLE, LEN_RECD);
   ystrlunquote (x_recd, LEN_RECD);      /* remove all quoted characters */
   DEBUG_DATA   yLOG_snote   (x_recd);
   /*---(identify)-----------------------*/
   if (r_choice != NULL)  {
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
   DEBUG_DATA   yLOG_schar   (x_good);
   if (x_good != 'y') {
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_snote   ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "CHOICE"  , x_choice);
      DEBUG_INPT   yLOG_svalue  ("ch" , rc);
   }
   /*---(save-back)----------------------*/
   if (r_choice  != NULL)  *r_choice = x_choice;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
LINE_loop               (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, int *r_sfull, int *r_sproj, int *r_sfile, int *r_sfunc, char *r_loop)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        x_good      =  '-';
   char        x_loop      =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_loop   = ySCORE_stats_value (my.s_yscore, "LOOP"    );
   } else {
      if (r_loop    != NULL)  x_loop   = *r_loop;
   }
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_recd);
   DEBUG_DATA   yLOG_sint    (a_inside);
   --rce;  if (a_inside != 1) {
      DEBUG_DATA   yLOG_snote   ("not inside function");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   ystrlcpy     (x_recd, a_recd     , LEN_RECD);
   ystrltrim    (x_recd, ySTR_SINGLE, LEN_RECD);
   ystrlunquote (x_recd, LEN_RECD);      /* remove all quoted characters */
   DEBUG_DATA   yLOG_snote   (x_recd);
   /*---(identify)-----------------------*/
   if (r_loop != NULL)  {
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
   DEBUG_DATA   yLOG_schar   (x_good);
   if (strchr ("Yy", x_good) == NULL) {
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(update)-------------------------*/
   if (x_good == 'y') {
      DEBUG_DATA   yLOG_snote   ("update slocl for do/while");
      if (r_sfull != NULL)  ++(*r_sfull);
      if (r_sproj != NULL)  ++(*r_sproj);
      if (r_sfile != NULL)  ++(*r_sfile);
      if (r_sfunc != NULL)  ++(*r_sfunc);
   } else {
      DEBUG_DATA   yLOG_snote   ("update slocl for for");
      if (r_sfull != NULL)  --(*r_sfull);
      if (r_sproj != NULL)  --(*r_sproj);
      if (r_sfile != NULL)  --(*r_sfile);
      if (r_sfunc != NULL)  --(*r_sfunc);
   }
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_snote   ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "LOOP"    , x_loop);
      DEBUG_INPT   yLOG_svalue  ("lo" , rc);
   }
   /*---(save-back)----------------------*/
   if (r_loop    != NULL)  *r_loop   = x_loop;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
LINE_indent             (tFUNC *a_func, char a_recd [LEN_RECD], char a_inside, char *r_indent)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         i           =    0;
   char        x_indent    =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_func != NULL) {
      x_indent = ySCORE_stats_value (my.s_yscore, "INDENT"  );
   } else {
      if (r_indent != NULL)  x_indent = *r_indent;
   }
   /*---(default)------------------------*/
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_recd);
   DEBUG_DATA   yLOG_sint    (a_inside);
   --rce;  if (a_inside != 1) {
      DEBUG_DATA   yLOG_snote   ("not inside function");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(calculate indent)---------------*/
   l = strlen (a_recd);
   DEBUG_DATA   yLOG_sint    (l);
   for (i = 0; i < l; ++i) {
      if (a_recd [i] == ' ')   continue;
      if (i > x_indent) x_indent = i;
      break;
   }
   DEBUG_DATA   yLOG_sint    (x_indent);
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_snote   ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "INDENT"  , x_indent);
      DEBUG_INPT   yLOG_svalue  ("in" , rc);
   }
   /*---(save back)----------------------*/
   if (r_indent != NULL)  *r_indent = x_indent;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return x_indent;
}



/*====================------------------------------------====================*/
/*===----                       function related                       ----===*/
/*====================------------------------------------====================*/
static void  o___FUNCTION________o () { return; }

char
LINE__purpose           (char a_recd [LEN_RECD], int a_beg, char r_purpose [LEN_DESC], char *r_ready)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_RECD]  = "";;
   int         i           =    0;
   int         j           =    0;
   int         l           =    0;
   /*---(default)------------------------*/
   if (r_purpose  != NULL)  strcpy (r_purpose, "");
   if (r_ready    != NULL)  *r_ready = 'E';
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
   /*---(save-back)----------------------*/
   if (r_purpose  != NULL)  ystrlcpy (r_purpose, t, 41);
   if (r_ready    != NULL)  *r_ready = 'y';
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> extract the function purpose -------[ ------ [ge.850.137.A4]*/ /*-[02.0000.00#.!]-*/ /*-[--.---.---.--]-*/
LINE_purpose            (tFUNC *a_func, char a_recd [LEN_RECD], char r_purpose [LEN_DESC], char *r_ready)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         b           =   -1;
   char        x_purpose   [LEN_DESC]  = "";
   char        x_ready     =  'E';
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_purpose != NULL)  strcpy (r_purpose, "");
   if (r_ready   != NULL)  *r_ready = 'E';
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(modern style)-------------------*/
   if (strncmp (a_recd, "/*-[ ", 5) == 0) {
      DEBUG_INPT   yLOG_snote   ("modern format");
      b = 5;
   }
   /*---(current style)------------------*/
   else if (strncmp (a_recd, "/*-> ", 5) == 0) {
      DEBUG_INPT   yLOG_snote   ("current format");
      b = 5;
   }
   /*---(previous style)-----------------*/
   else if (strncmp (a_recd, "/*--> ",  6) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 1 format");
      b = 6;
   }
   /*---(previous style)-----------------*/
   else if (strncmp (a_recd, "/* ---- : ", 10) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 2 format");
      b = 10;
   }
   /*---(previous style)-----------------*/
   else if (strncmp (a_recd, "/*----: ",  8) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 3 format");
      b = 8;
   }
   /*---(previous style)-----------------*/
   else if (strncmp (a_recd, "/*===[[ ",  8) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 3 format");
      b = 8;
   }
   /*---(terse format)-------------------*/
   else if (strncmp (a_recd, "/* ",  3) == 0) {
      DEBUG_INPT   yLOG_snote   ("terse format");
      b = 3;
   }
   /*---(error)--------------------------*/
   else {
      DEBUG_INPT   yLOG_snote   ("not a recognized format");
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(call)---------------------------*/
   rc = LINE__purpose       (a_recd, b, x_purpose, &x_ready);
   DEBUG_INPT   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_snote   ("save to func");
      ystrlcpy (a_func->c_purpose, x_purpose, LEN_DESC);
      a_func->c_ready = x_ready;
   }
   /*---(save-back)----------------------*/
   if (r_purpose != NULL)  ystrlcpy (r_purpose, x_purpose, LEN_DESC);
   if (r_ready   != NULL)  *r_ready = x_ready;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_single != NULL)  *r_single = '·';
   if (r_scope  != NULL)  *r_scope  = '·';
   if (r_rtype  != NULL)  *r_rtype  = '·';
   if (r_rlong  != NULL)  ystrlcpy (r_rlong, "", LEN_LABEL);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_spoint  (a_prev);
   --rce;  if (a_prev == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(find name)----------------------*/
   DEBUG_INPT   yLOG_snote   (a_name);
   p = strstr (a_recd, a_name);
   DEBUG_INPT   yLOG_spoint  (p);
   /*---(figure spacing)-----------------*/
   x_len = p - a_recd;
   DEBUG_INPT   yLOG_sint    (x_len);
   /*---(set single)---------------------*/
   if (x_len == 0)   x_single = '-';
   else              x_single = 'y';
   DEBUG_INPT   yLOG_schar   (x_single);
   /*---(oneline return type)------------*/
   --rce;  if (x_single == 'y') {
      ystrlcpy (x_return, a_recd, x_len);
   }
   /*---(multiline return type)----------*/
   else {
      if (a_prev == NULL) {
         DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      r = strstr (a_prev, "/*");
      if (r == NULL)  x_len = strlen (a_prev);
      else            x_len = r - a_prev;
      ystrlcpy (x_return, a_prev, x_len + 1);
   }
   ystrltrim (x_return, ySTR_SINGLE, LEN_RECD);
   DEBUG_INPT   yLOG_snote   (x_return);
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
   DEBUG_INPT   yLOG_schar   (x_scope);
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
   DEBUG_INPT   yLOG_schar   (x_rtype);
   /*---(into-function)------------------*/
   if (a_func != NULL) {
      DEBUG_INPT   yLOG_snote   ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "SINGLE"  , x_single);
      DEBUG_INPT   yLOG_sint    (rc);
      rc = ySCORE_stats_set (my.s_yscore, "SCOPE"   , x_scope);
      DEBUG_INPT   yLOG_sint    (rc);
      rc = ySCORE_stats_set (my.s_yscore, "RTYPE"   , x_rtype);
      DEBUG_INPT   yLOG_sint    (rc);
      ystrlcpy (a_func->c_rlong, x_return, LEN_LABEL);
   }
   /*---(save-back)----------------------*/
   if (r_single != NULL)  *r_single = x_single;
   if (r_scope  != NULL)  *r_scope  = x_scope;
   if (r_rtype  != NULL)  *r_rtype  = x_rtype;
   if (r_rlong  != NULL && x_len < LEN_LABEL)  ystrlcpy (r_rlong, x_return, LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_params != NULL)   strcpy (r_params, "");
   if (r_audit  != NULL)   *r_audit =  '¢';
   if (r_count  != NULL)   *r_count =   -2;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd   == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (r_params);
   --rce;  if (r_params == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(find beg)-----------------------*/
   x_beg = strchr (a_recd, '(');
   DEBUG_DATA   yLOG_spoint  (x_beg);
   --rce;  if (x_beg == NULL) {
      DEBUG_DATA   yLOG_snote   ("can not find '(' start)");
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(find max end)-------------------*/
   x_end = strchr (a_recd, '{');
   DEBUG_DATA   yLOG_spoint  (x_end);
   if (x_end == NULL)  x_len = LEN_RECD;
   else                x_len = x_end - x_beg;
   DEBUG_DATA   yLOG_sint    (x_len);
   ystrlcpy  (x_params, x_beg, x_len);
   ystrltrim (x_params, ySTR_SINGLE, x_len);
   x_len = strlen (x_params);
   /*---(check symmetry)-----------------*/
   if (r_audit  != NULL)   *r_audit =  '(';
   x_open  = ystrldcnt (x_params, '(', LEN_RECD);
   DEBUG_DATA   yLOG_sint    (x_open);
   --rce;  if (x_open  < 1) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_close = ystrldcnt (x_params, ')', LEN_RECD);
   DEBUG_DATA   yLOG_sint    (x_close);
   --rce;  if (x_close < 1) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_open  != x_close) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check symmetry)-----------------*/
   x_on = 0;
   --rce;  for (i = j = 0; i <= x_len; ++i) {
      if (x_params [i] == ')') {
         DEBUG_INPT   yLOG_snote   (")");
         --x_on;
         if (x_on <= 0 && i < x_len - 1) {
            DEBUG_INPT   yLOG_sint    (i);
            DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
         if (x_on < 0) {
            DEBUG_INPT   yLOG_sint    (i);
            DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
      }
      if (x_on == 1)  x_final [j++] = x_params [i];
      if (x_params [i] == '(') {
         DEBUG_INPT   yLOG_sint    (i);
         DEBUG_INPT   yLOG_snote   ("(");
         ++x_on;
      }
   }
   if (r_audit  != NULL)   *r_audit =  '(';
   DEBUG_INPT   yLOG_sint    (x_on);
   if (x_on > 0) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
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
   DEBUG_INPT   yLOG_sint    (x_count);
   /*---(final touches)------------------*/
   ystrltrim (x_final, ySTR_BOTH, LEN_RECD);
   x_len = strlen (x_final);
   if (x_count == 0) {
      x_count = ystrldcnt (x_final, ',', x_len) + 1;
      if (x_count <  0)   x_count = 0;
   }
   /*---(save-back)----------------------*/
   if (r_params != NULL)   ystrlcpy (r_params, x_final, LEN_RECD);
   if (r_audit  != NULL)   *r_audit =  '·';
   if (r_count  != NULL)   *r_count = x_count;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
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
LINE__params_class      (char a_label [LEN_LABEL], char *r_class, uchar *b_in, uchar *b_out, uchar *b_both, uchar *b_conf, uchar *b_void, uchar *b_other)
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
   else if (strncmp (a_label, "e_"    , 2) == 0)  { x_class = 'e';  if (b_void  != NULL)  ++(*b_void);  }
   else if (strncmp (a_label, "v_"    , 2) == 0)  { x_class = 'v';  if (b_void  != NULL)  ++(*b_void);  }
   else                                                          {  if (b_other != NULL)  ++(*b_other); }
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
LINE__params_one        (char a_param [LEN_RECD], uchar *b_in, uchar *b_out, uchar *b_both, uchar *b_conf, uchar *b_void, uchar *b_pnum, uchar *b_pmulti, uchar *b_pfunc, uchar *b_pstruc)
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
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_param);
   --rce;  if (a_param  == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(parse)--------------------------*/
   rc = LINE__params_parse (a_param, x_type, x_label, &x_point, &x_func);
   DEBUG_DATA   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(direction)----------------------*/
   rc = LINE__params_class (x_label, &x_class, b_in, b_out, b_both, b_conf, b_void, NULL);
   DEBUG_DATA   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(point)--------------------------*/
   rc = LINE__params_point (x_type, x_point, x_func, x_class, b_pnum, b_pmulti, b_pfunc, b_pstruc);
   DEBUG_DATA   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> evaluate function parameter list ------------[ ´········· ]-*/ /*-ågcg´·Bá1A··á9··á·´D17´H··´11M22á·æ¬å1á·1··´C84á2·2····´···´····æ¬å>l!··´2···2··´····´114·æ-*/
LINE_params             (tFUNC *a_func, char a_recd [LEN_RECD], char *r_audit, uchar *r_count, uchar *b_in, uchar *b_out, uchar *b_both, uchar *b_conf, uchar *b_void, uchar *b_pnum, uchar *b_pmulti, uchar *b_pfunc, uchar *b_pstruc)
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
   uchar      x_in, x_ou, x_bo, x_cf, x_vo, x_pn, x_pm, x_pf, x_ps;
   int        c            =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_audit   != NULL)  *r_audit   = '¢';
   if (r_count   != NULL)  *r_count   =  -2;
   if (b_in      != NULL)  *b_in      =   0;
   if (b_out     != NULL)  *b_out     =   0;
   if (b_both    != NULL)  *b_both    =   0;
   if (b_conf    != NULL)  *b_conf    =   0;
   if (b_void    != NULL)  *b_void    =   0;
   if (b_pnum    != NULL)  *b_pnum    =   0;
   if (b_pmulti  != NULL)  *b_pmulti  =   0;
   if (b_pfunc   != NULL)  *b_pfunc   =   0;
   if (b_pstruc  != NULL)  *b_pstruc  =   0;
   x_co = x_in = x_ou = x_bo = x_cf = x_vo = x_pn = x_pm = x_pf = x_ps = 0;
   /*---(prepare)------------------------*/
   rc = LINE__params_cut        (a_recd, x_params, &x_au, &x_co);
   DEBUG_DATA   yLOG_value   ("cut"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (rc == 1) {
      if (x_co == -1)  x_co = 0;
      if (r_count   != NULL)  *r_count   = x_co;
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_INPT   yLOG_value   ("x_co"      , x_co);
   /*---(parse)--------------------------*/
   p = strtok_r (x_params, q, &r);
   while (p != NULL) {
      rc = LINE__params_one      (p, &x_in, &x_ou, &x_bo, &x_cf, &x_vo, &x_pn, &x_pm, &x_pf, &x_ps);
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
      DEBUG_INPT   yLOG_snote   ("save to func");
      rc = ySCORE_stats_set (my.s_yscore, "PAUDIT"  , x_au);
      DEBUG_INPT   yLOG_svalue  ("au", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PARAMS"  , x_co);
      DEBUG_INPT   yLOG_svalue  ("co", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PIN"     , x_in);
      DEBUG_INPT   yLOG_svalue  ("in", rc);
      rc = ySCORE_stats_set (my.s_yscore, "POUT"    , x_ou);
      DEBUG_INPT   yLOG_svalue  ("ou", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PBOTH"   , x_bo);
      DEBUG_INPT   yLOG_svalue  ("bo", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PCONF"   , x_cf);
      DEBUG_INPT   yLOG_svalue  ("cf", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PNUM"    , x_pn);
      DEBUG_INPT   yLOG_svalue  ("pn", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PMULTI"  , x_pm);
      DEBUG_INPT   yLOG_svalue  ("pm", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PFUNC"   , x_pf);
      DEBUG_INPT   yLOG_svalue  ("pf", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PSTRUC"  , x_ps);
      DEBUG_INPT   yLOG_svalue  ("ps", rc);
      rc = ySCORE_stats_set (my.s_yscore, "PVOID"   , x_vo);
      DEBUG_INPT   yLOG_svalue  ("vo", rc);
   }
   /*---(save-back)----------------------*/
   if (r_audit   != NULL)  *r_audit   = x_au;
   if (r_count   != NULL)  *r_count   = x_co;
   if (b_in      != NULL)  *b_in      = x_in;
   if (b_out     != NULL)  *b_out     = x_ou;
   if (b_both    != NULL)  *b_both    = x_bo;
   if (b_conf    != NULL)  *b_conf    = x_cf;
   if (b_void    != NULL)  *b_void    = x_vo;
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


