/*============================----beg-of-source---============================*/
#include  "polymnia.h"


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
poly_line_all           (char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(update)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("update counters");
   if (r_cfull != NULL) {
      ++(*r_cfull);
      DEBUG_DATA   yLOG_sint    (*r_cfull);
   }
   if (r_cproj != NULL) {
      ++(*r_cproj);
      DEBUG_DATA   yLOG_sint    (*r_cproj);
   }
   if (r_cfile != NULL) {
      ++(*r_cfile);
      DEBUG_DATA   yLOG_sint    (*r_cfile);
   }
   if (a_inside == 1)  {
      DEBUG_DATA   yLOG_snote   ("inside a function");
      if (r_cfunc != NULL) {
         ++(*r_cfunc);
         DEBUG_DATA   yLOG_sint    (*r_cfunc);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

/*
 * o                                                   w      c  F G X r  c                            n   w     D                                L          
 * n          p p           p      %           i   c r ´  m   a  c c c e  a D R  F G     v O m    o s  c o i y   a D D D    m    g     v          s        s 
 * e   s r p  a a      p    m p  t d %  L F G  n   h e e  e   l  a a a c  l f f  f f     i f y  i u y  u p n g   c s m m D  a    l     i o  V M F t  u s s t 
 * l   c t r  u r    p b  p u f  o e c  v v v  d l o t r  m   l  l l l u  l u u  u u c y k u s  n t s  r e d r   t t a a w  c  f o c y k t  m m m a  n c t r 
 * i   o y o  d a  p o o  n l u  t b o  a a a  e o i u r  o   ´  l l l r  ´ n n  n n s l e n t  p p t  s n o a   i y c t a  r  i b s l e h  a a a t  i r e i 
 * n   p p t  i m  i u t  u t n  a u d  r r r  n o c r o  r   b  e e e s  t c c  c c t i y c r  u u e  e g w p   v l r c r  o  l a t i y e  s s s i  t p p n 
 * e   e e o  t s  n t h  m i c  l g e  s s s  t p e n r  y   y  r r r e  o s s  s s d b s s y  t t m  s l s h   e e o h n  s  e l d b s r  k k k c  s s s g 
 * á  å---------------------complexity---------------------æ å-------------------integration------------------æ å----------------watch-points---------------æ
 * ·   g c g  ´ 6  2 4 ·  4 · ·  8 3 5  3 · ·  1 · 7 2 1  á   2  á 2 · ·  E B 3  á · 1 2 · · ·  ´ · ·  ´ · · ·   > s d · >  3  á · · · 4 3  ´ · · ·  1 1 7 ·
 *
 * åleaf      æ  å  62æ  åidenfity empty lines in codeæ
 */
char         /*-> idenfity empty lines in code ----------------[ leaf······ ]-*/ /*-ågcg´·6á24·á4··´835´3··´1·721á·æ¬å2á·2··´EB3á··12···´···´····æ¬å>sd·>´3····43´····´117·æ-*/
poly_line_empty         (cchar a_recd [LEN_RECD], char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc)
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
poly_line_comment       (cchar a_recd [LEN_RECD], char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc)
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
poly_line_debug         (cchar a_recd [LEN_RECD], char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc, int *r_dcount, int *r_dextra, char *r_abbr)
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
poly_line_unguard       (cchar a_recd [LEN_RECD], char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc, int *r_dcount, int *r_dfree)
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
poly_line_code          (char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc)
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
poly_line_slocl         (cchar a_recd [LEN_RECD], char a_inside, int *r_cfull, int *r_cproj, int *r_cfile, int *r_cfunc)
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
poly_line_exit          (cchar a_recd [LEN_RECD], char a_inside, int *r_return, int *r_rce)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_good      =  '-';
   char        x_recd      [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
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
   if      (strncmp (x_recd, "return rce"  , 10) == 0    && r_rce    != NULL)  { ++(*r_rce   );  x_good = 'y'; }
   else if (strstr  (x_recd, " return rce"     ) != NULL && r_rce    != NULL)  { ++(*r_rce   );  x_good = 'y'; }
   else if (strstr  (x_recd, ";return rce"     ) != NULL && r_rce    != NULL)  { ++(*r_rce   );  x_good = 'y'; }
   else if (strncmp (x_recd, "return -"    ,  8) == 0    && r_rce    != NULL)  { ++(*r_rce   );  x_good = 'y'; }
   else if (strstr  (x_recd, " return -"       ) != NULL && r_rce    != NULL)  { ++(*r_rce   );  x_good = 'y'; }
   else if (strstr  (x_recd, ";return -"       ) != NULL && r_rce    != NULL)  { ++(*r_rce   );  x_good = 'y'; }
   else if (strncmp (x_recd, "return "     ,  7) == 0    && r_return != NULL)  { ++(*r_return);  x_good = 'y'; }
   else if (strstr  (x_recd, " return "        ) != NULL && r_return != NULL)  { ++(*r_return);  x_good = 'y'; }
   else if (strstr  (x_recd, ";return "        ) != NULL && r_return != NULL)  { ++(*r_return);  x_good = 'y'; }
   else if (strncmp (x_recd, "return;"     ,  7) == 0    && r_return != NULL)  { ++(*r_return);  x_good = 'y'; }
   else if (strstr  (x_recd, " return;"        ) != NULL && r_return != NULL)  { ++(*r_return);  x_good = 'y'; }
   else if (strstr  (x_recd, ";return;"        ) != NULL && r_return != NULL)  { ++(*r_return);  x_good = 'y'; }
   else if (strncmp (x_recd, "return ;"    ,  8) == 0    && r_return != NULL)  { ++(*r_return);  x_good = 'y'; }
   else if (strstr  (x_recd, " return ;"       ) != NULL && r_return != NULL)  { ++(*r_return);  x_good = 'y'; }
   else if (strstr  (x_recd, ";return ;"       ) != NULL && r_return != NULL)  { ++(*r_return);  x_good = 'y'; }
   /*---(not found)----------------------*/
   DEBUG_DATA   yLOG_schar   (x_good);
   if (x_good != 'y') {
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
poly_line_choice        (cchar a_recd [LEN_RECD], char a_inside, int *r_choice)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_good      =  '-';
   char        x_recd      [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
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
      if      (strncmp (x_recd, "if "         ,  3) == 0   )  { ++(*r_choice);  x_good = 'y'; }
      else if (strncmp (x_recd, "if("         ,  3) == 0   )  { ++(*r_choice);  x_good = 'y'; }
      else if (strstr  (x_recd, " if "            ) != NULL)  { ++(*r_choice);  x_good = 'y'; }
      else if (strstr  (x_recd, ";if "            ) != NULL)  { ++(*r_choice);  x_good = 'y'; }
      else if (strstr  (x_recd, " if("            ) != NULL)  { ++(*r_choice);  x_good = 'y'; }
      else if (strstr  (x_recd, ";if("            ) != NULL)  { ++(*r_choice);  x_good = 'y'; }
      else if (strncmp (x_recd, "else "       ,  5) == 0   )  { ++(*r_choice);  x_good = 'y'; }
      else if (strstr  (x_recd, " else "          ) != NULL)  { ++(*r_choice);  x_good = 'y'; }
      else if (strstr  (x_recd, ";else "          ) != NULL)  { ++(*r_choice);  x_good = 'y'; }
      else if (strstr  (x_recd, "}else "          ) != NULL)  { ++(*r_choice);  x_good = 'y'; }
      else if (strncmp (x_recd, "else{"       ,  5) == 0   )  { ++(*r_choice);  x_good = 'y'; }
      else if (strstr  (x_recd, " else{"          ) != NULL)  { ++(*r_choice);  x_good = 'y'; }
      else if (strstr  (x_recd, ";else{"          ) != NULL)  { ++(*r_choice);  x_good = 'y'; }
      else if (strncmp (x_recd, "}else{"      ,  6) == 0   )  { ++(*r_choice);  x_good = 'y'; }
      else if (strstr  (x_recd, "}else{"          ) != NULL)  { ++(*r_choice);  x_good = 'y'; }
      else if (strncmp (x_recd, "case "       ,  5) == 0   )  { ++(*r_choice);  x_good = 'y'; }
      else if (strncmp (x_recd, "default "    ,  8) == 0   )  { ++(*r_choice);  x_good = 'y'; }
      else if (strncmp (x_recd, "default:"    ,  8) == 0   )  { ++(*r_choice);  x_good = 'y'; }
   }
   /*---(not found)----------------------*/
   DEBUG_DATA   yLOG_schar   (x_good);
   if (x_good != 'y') {
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
poly_line_loop          (cchar a_recd [LEN_RECD], char a_inside, int *r_sfull, int *r_sproj, int *r_sfile, int *r_sfunc, int *r_loop)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_recd      [LEN_RECD]  = "";
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
      if      (strncmp (x_recd, "while "      ,  6) == 0   )  { ++(*r_loop  );  x_good = 'y'; }
      else if (strstr  (x_recd, " while "         ) != NULL)  { ++(*r_loop  );  x_good = 'y'; }
      else if (strstr  (x_recd, ";while "         ) != NULL)  { ++(*r_loop  );  x_good = 'y'; }
      else if (strstr  (x_recd, " while( "        ) != NULL)  { ++(*r_loop  );  x_good = 'y'; }
      else if (strncmp (x_recd, "while("      ,  6) == 0   )  { ++(*r_loop  );  x_good = 'y'; }
      else if (strstr  (x_recd, ";while( "        ) != NULL)  { ++(*r_loop  );  x_good = 'y'; }
      else if (strstr  (x_recd, " do "            ) != NULL)  { ++(*r_loop  );  x_good = 'y'; }
      else if (strncmp (x_recd, "do "         ,  3) == 0   )  { ++(*r_loop  );  x_good = 'y'; }
      else if (strstr  (x_recd, "}do "            ) != NULL)  { ++(*r_loop  );  x_good = 'y'; }
      else if (strstr  (x_recd, " do{"            ) != NULL)  { ++(*r_loop  );  x_good = 'y'; }
      else if (strncmp (x_recd, "do{"         ,  3) == 0   )  { ++(*r_loop  );  x_good = 'y'; }
      else if (strstr  (x_recd, "}do("            ) != NULL)  { ++(*r_loop  );  x_good = 'y'; }
      else if (strncmp (x_recd, "for "        ,  4) == 0   )  { ++(*r_loop  );  x_good = 'Y'; }
      else if (strstr  (x_recd, " for "           ) != NULL)  { ++(*r_loop  );  x_good = 'Y'; }
      else if (strstr  (x_recd, ";for "           ) != NULL)  { ++(*r_loop  );  x_good = 'Y'; }
      else if (strncmp (x_recd, "for("        ,  4) == 0   )  { ++(*r_loop  );  x_good = 'Y'; }
      else if (strstr  (x_recd, " for("           ) != NULL)  { ++(*r_loop  );  x_good = 'Y'; }
      else if (strstr  (x_recd, ";for("           ) != NULL)  { ++(*r_loop  );  x_good = 'Y'; }
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
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
poly_line_indent        (cchar a_recd [LEN_RECD], char a_inside, int *r_indent)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         l           =    0;
   int         i           =    0;
   char        x_indent    =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_indent != NULL)  x_indent = *r_indent;
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

/*> char                                                                              <* 
 *> poly_func__purpose_copy (cchar a_recd [LEN_RECD], int a_beg)                      <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char       t            [LEN_RECD];                                            <* 
 *>    int        i            =    0;                                                <* 
 *>    int        j            =    0;                                                <* 
 *>    int        x_len        =    0;                                                <* 
 *>    /+---(prepare)------------------------+/                                       <* 
 *>    ystrlcpy (t, a_recd + a_beg, LEN_RECD);                                         <* 
 *>    x_len = strlen (t);                                                            <* 
 *>    /+---(very end)-----------------------+/                                       <* 
 *>    for (i = 0; i < x_len; ++i)  {                                                 <* 
 *>       if (strchr ("*=()[]", t [i]) != NULL) {                                     <* 
 *>          t [i] = '\0';                                                            <* 
 *>          break;                                                                   <* 
 *>       }                                                                           <* 
 *>       if (t [i] == '-' && t [i + 1] == '-') {                                     <* 
 *>          t [i] = '\0';                                                            <* 
 *>          break;                                                                   <* 
 *>       }                                                                           <* 
 *>    }                                                                              <* 
 *>    /+---(search)-------------------------+/                                       <* 
 *>    for (j = i; j > 0; --j)  {                                                     <* 
 *>       if (strchr (" -=][", t [j]) == NULL)   break;                               <* 
 *>       t [j] = '\0';                                                               <* 
 *>    }                                                                              <* 
 *>    /+---(save)---------------------------+/                                       <* 
 *>    ystrlcpy (a_func->c_purpose, t, 41);                                              <* 
 *>    a_func->ready = 'y';                                                           <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

char
poly_line__purpose      (cchar a_recd [LEN_RECD], int a_beg, char r_purpose [LEN_DESC], char *r_ready)
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
poly_line_purpose       (cchar a_recd [LEN_RECD], char r_purpose [LEN_DESC], char *r_ready)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_RECD];
   int         i           =    0;
   int         b           =   -1;
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
   rc = poly_line__purpose  (a_recd, b, r_purpose, r_ready);
   DEBUG_INPT   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> identify function scope/return type ---------[ leaf······ ]-*/ /*-ågcg´·7á34·á···´K27´8··´2·#14á·æ¬å1á·1··´#GTá··M7···´···´····æ¬å>si·>´······´····´11Q·æ-*/
poly_line_func          (cchar a_prev [LEN_RECD], cchar a_recd [LEN_RECD], char a_name [LEN_TITLE], char *r_single, char *r_scope, char *r_rtype, char r_rlong [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
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
   else if (strstr  (a_name            , "__unit_"   ) != NULL)  x_scope = 'u';
   else if (strncmp (a_name + x_len - 6, "__fake" , 6) == 0   )  x_scope = 'u';
   else if (strstr  (a_name            , "__fake_"   ) != NULL)  x_scope = 'u';
   else if (strstr  (a_name            , "__"        ) != NULL)  x_scope = 'f';
   else                                               x_scope = 'g';
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
poly_line__params_cut   (char a_recd [LEN_RECD], char r_params [LEN_RECD], char *r_audit, int *r_count)
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
poly_line__params_one   (char a_param [LEN_RECD], int *r_in, int *r_out, int *r_both, int *r_chg, int *r_pnum, int *r_pmulti, int *r_pfunc, int *r_pstruct)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *p           = NULL;
   char       *x_end       = NULL;
   char        x_param     [LEN_RECD]  = "";
   char        x_type      =  '-';
   int         x_len       =    0;
   int         i           =    0;
   char        x_label     [LEN_LABEL] = "";
   char        x_num       =    0;
   char        x_point     =    0;
   char        x_struct    =    0;
   char        x_func      =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_param);
   --rce;  if (a_param  == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy  (x_param, a_param    , LEN_RECD);
   ystrltrim (x_param, ySTR_SINGLE, LEN_RECD);
   /*---(suffix)-------------------------*/
   x_end = strchr (x_param, '[');
   if (x_end != NULL)  x_type = '[';
   else {
      x_end = strchr (x_param, '(');
      if (x_end != NULL)  x_type = '(';
   }
   DEBUG_DATA   yLOG_schar   (x_type);
   DEBUG_DATA   yLOG_spoint  (x_end);
   if (x_end != NULL)  {
      x_end [0] = '\0';
      ystrltrim (x_param, ySTR_BOTH, LEN_RECD);
   }
   DEBUG_DATA   yLOG_snote   (x_param);
   x_len = strlen (x_param);
   DEBUG_DATA   yLOG_sint    (x_len);
   /*---(label)--------------------------*/
   for (i = x_len - 1; i > 0; --i) {
      if (strchr ("* ", x_param [i]) != NULL) {
         ystrlcpy (x_label, x_param + i + 1, LEN_LABEL);
         x_param [i + 1] = '\0';
         break;
      }
   }
   DEBUG_DATA   yLOG_sint    (i);
   --rce;  if (i == 0) {
      DEBUG_INPT   yLOG_snote   ("no room for type");
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (x_label);
   x_len = strlen (x_label);
   DEBUG_DATA   yLOG_sint    (x_len);
   --rce;  if (x_len < 1) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(direction)----------------------*/
   if      (strncmp (x_label, "a_"    , 2) == 0 && r_in   != NULL)     ++(*r_in);
   else if (strncmp (x_label, "r_"    , 2) == 0 && r_out  != NULL)     ++(*r_out);
   else if (strncmp (x_label, "b_"    , 2) == 0 && r_both != NULL)     ++(*r_both);
   else if (strncmp (x_label, "c_"    , 2) == 0 && r_chg  != NULL)     ++(*r_chg);
   /*---(point)--------------------------*/
   if      (strstr  (x_param, "***"      ) != NULL)  x_point = 3;
   else if (strstr  (x_param, "**"       ) != NULL)  x_point = 2;
   else if (strstr  (x_param, "*"        ) != NULL)  x_point = 1;
   if      (x_type == '[')                           ++x_point;
   /*---(num)----------------------------*/
   if      (strstr (x_param, "float"   ) != NULL)    ++x_num;
   else if (strstr (x_param, "double"  ) != NULL)    ++x_num;
   else if (strstr (x_param, "short"   ) != NULL)    ++x_num;
   else if (strstr (x_param, "int"     ) != NULL)    ++x_num;
   else if (strstr (x_param, "long"    ) != NULL)    ++x_num;
   else if (strstr (x_param, "char"    ) != NULL)    ;
   else if (strstr (x_param, "void"    ) != NULL)    ;
   else                                              ++x_struct;
   /*---(combos)-------------------------*/
   if      (x_type   == '(' && x_point  > 0 && r_pfunc   != NULL)   ++(*r_pfunc);
   else if (x_num    >  0   && x_point == 1 && r_pnum    != NULL)   ++(*r_pnum);
   else if (x_point  >  1   &&                 r_pmulti  != NULL)   ++(*r_pmulti);
   if      (x_struct >  0   &&                 r_pstruct != NULL)   ++(*r_pstruct);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> evaluate function parameter list ------------[ ´········· ]-*/ /*-ågcg´·Bá1A··á9··á·´D17´H··´11M22á·æ¬å1á·1··´C84á2·2····´···´····æ¬å>l!··´2···2··´····´114·æ-*/
poly_line_params        (char a_recd [LEN_RECD], char *r_audit, int *r_count, int *r_in, int *r_out, int *r_both, int *r_chg, int *r_pnum, int *r_pmulti, int *r_pfunc, int *r_pstruct)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   char       *q           =  ",";
   char       *r           = NULL;
   char       x_params     [LEN_RECD];
   char       x_one        [LEN_RECD];
   int        x_co, x_in, x_ou, x_bo, x_ch, x_pn, x_pm, x_pf, x_ps;
   int        c            =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_audit  != NULL)  *r_audit  = '¢';
   if (r_count  != NULL)  *r_count  =  -2;
   if (r_in     != NULL)  *r_in     =   0;
   if (r_out    != NULL)  *r_out    =   0;
   if (r_both   != NULL)  *r_both   =   0;
   if (r_chg    != NULL)  *r_chg    =   0;
   if (r_pnum   != NULL)  *r_pnum   =   0;
   if (r_pmulti != NULL)  *r_pmulti =   0;
   if (r_pfunc  != NULL)  *r_pfunc  =   0;
   x_co = x_in = x_ou = x_bo = x_ch = x_pn = x_pm = x_pf = x_ps = 0;
   /*---(prepare)------------------------*/
   rc = poly_line__params_cut   (a_recd, x_params, r_audit, &x_co);
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
      rc = poly_line__params_one (p, &x_in, &x_ou, &x_bo, &x_ch, &x_pn, &x_pm, &x_pf, &x_ps);
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
   /*---(save-back)----------------------*/
   if (r_count   != NULL)  *r_count   = x_co;
   if (r_in      != NULL)  *r_in      = x_in;
   if (r_out     != NULL)  *r_out     = x_ou;
   if (r_both    != NULL)  *r_both    = x_bo;
   if (r_chg     != NULL)  *r_chg     = x_ch;
   if (r_pnum    != NULL)  *r_pnum    = x_pn;
   if (r_pmulti  != NULL)  *r_pmulti  = x_pm;
   if (r_pfunc   != NULL)  *r_pfunc   = x_pf;
   if (r_pstruct != NULL)  *r_pstruct = x_ps;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char         /*-> force data onto function --------------------[ leaf······ ]-*/ /*-åucg´·4á3··1á···á1´2·A´1··´··111á·æ¬å·á····´···á·······´···´····æ¬å·····´3·3····´····´····æ-*/
poly_debug__fake        (int a_return, int a_intern, int a_ylib, tFUNC *c_func)
{
   char        rce         =  -10;
   --rce;  if (c_func == NULL)  return rce;
   c_func->WORK_RETURN  = a_return;
   c_func->WORK_GFUNCS  = a_intern;
   c_func->WORK_YLIB    = a_ylib;
   return 0;
}

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_debug__unit        (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   char        r           [LEN_RECD] = "";
   char        s           [LEN_LABEL]= "";
   tFUNC      *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "DEBUG unit       : function number unknown");
   if (strcmp (a_question, "work"      )     == 0) {
      poly_func_by_index (i, &u);
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


