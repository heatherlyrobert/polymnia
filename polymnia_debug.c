/*============================----beg-of-source---============================*/
#include  "polymnia.h"


/*
 *
 *  always group base and mas macros
 *
 *  metis § ----- § build macro find into yURG to keep in sync
 *
 *  metis § ----- § inventory all debugging macros and functions used
 *
 *  metis § ----- § create a line placeholder in source with debugging summary
 *
 *  metis § ----- § create a line placeholder in source with code stats summary
 *
 *  metis § ----- § accept new urgents in è to ÿ for reporting (project wide)
 *
 *
 *
 */



#define   MAX_MACRO     26
struct cMACRO {
   char        name        [LEN_LABEL];
   char        abbr;
} s_macros [MAX_MACRO] = {

   { "TOPS"     , 't' },
   { "RPTG"     , 'r' },
   { "VIEW"     , 'v' },

   { "ARGS"     , 'a' },
   { "CONF"     , 'c' },
   { "PROG"     , 'p' },

   { "INPT"     , 'i' },
   { "OUTP"     , 'o' },
   { "FILE"     , 'f' },
   { "SQLS"     , 'q' },

   { "LOOP"     , 'l' },
   { "NORM"     , 'n' },
   { "USER"     , 'u' },
   { "APIS"     , 'z' },
   { "SIGN"     , 'x' },
   { "SCRP"     , 'b' },
   { "HIST"     , 'h' },

   { "GRAF"     , 'g' },
   { "WIND"     , 'w' },
   { "ENVI"     , 'e' },
   { "DATA"     , 'd' },
   { "SORT"     , 's' },
   { "TRAV"     , 'y' },
   { "MEMS"     , 'm' },

   { "---end---", 'm' },

};



/*====================------------------------------------====================*/
/*===----                         supporting                           ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_debug__macro       (char *a_macro)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   char        i           =    0;           /* return code for errors         */
   static char x_macro     [LEN_LABEL] = "";
   static char n           =   -1;
   /*---(quick out)----------------------*/
   if (a_macro == NULL)  return '?';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   if (strcmp (a_macro, x_macro) == 0) {
      DEBUG_INPT   yLOG_snote   ("short-cut");
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return n;
   }
   DEBUG_INPT   yLOG_snote   (a_macro);
   for (i = 0; i < MAX_MACRO; ++i) {
      if (s_macros [i].name [0] != a_macro [0])            continue;
      if (strncmp (s_macros [i].name, a_macro, 4) != 0)    continue;
      strlcpy (x_macro, a_macro, LEN_LABEL);
      n = i;
      DEBUG_INPT   yLOG_schar   (s_macros [i].abbr);
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return s_macros [i].abbr;
   }
   DEBUG_INPT   yLOG_schar   ('?');
   DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, -1);
   return '?';
}



/*====================------------------------------------====================*/
/*===----                       line checking                          ----===*/
/*====================------------------------------------====================*/
static void  o___CHECKING________o () { return; }

char
poly_debug__counts      (tFILE *a_file, tFUNC *a_func, char a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_inside    =   -1;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_spoint  (a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(checking)-----------------------*/
   DEBUG_DATA   yLOG_spoint  (a_func);
   if (a_func == NULL) {
      DEBUG_DATA   yLOG_snote   ("function is null");
   } else {
      DEBUG_DATA   yLOG_spoint  (a_func->work);
      if (a_func->work == NULL) {
         DEBUG_DATA   yLOG_snote   ("a_func->work null");
      } else {
         DEBUG_DATA   yLOG_sint    (a_func->WORK_BEG);
         DEBUG_DATA   yLOG_sint    (a_func->WORK_END);
         x_inside = poly_func_inside (a_func);
      }
   }
   if (x_inside == 0)    DEBUG_DATA   yLOG_snote   ("inside a function");
   /*---(line counts)--------------------*/
   ++a_file->proj->COUNT_LINES;
   ++a_file->COUNT_LINES;
   if (x_inside == 0) ++a_func->COUNT_LINES;
   /*---(debug counts)-------------------*/
   switch (a_type) {
   case 'n' :  case 'f' :
      ++a_file->proj->COUNT_DEBUG;
      ++a_file->COUNT_DEBUG;
      if (x_inside == 0) {
         ++a_func->COUNT_DEBUG;
         ++a_func->WORK_DCOUNT;
         if (a_type == 'f')  ++a_func->WORK_DFREE;
      }
      break;
   case 'd' :
      ++a_file->proj->COUNT_DOCS;
      ++a_file->COUNT_DOCS;
      if (x_inside == 0) ++a_func->COUNT_DOCS;
      break;
   case 'e' :
      ++a_file->proj->COUNT_EMPTY;
      ++a_file->COUNT_EMPTY;
      if (x_inside == 0) ++a_func->COUNT_EMPTY;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_debug_line         (tFILE *a_file, tFUNC *a_func, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_macro     =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   /*---(check debug)--------------------*/
   --rce;  if (a_recd [0] == 'D') {
      DEBUG_INPT   yLOG_note    ("check debugging type");
      if (strncmp (a_recd, "DEBUG_", 6) != 0) {
         DEBUG_INPT   yLOG_note    ("not a valid DEBUG_ macro debugging line");
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_INPT   yLOG_note    ("valid DEBUG debugging macro line");
      poly_debug__counts (a_file, a_func, 'n');
      /*---(function level)--------------*/
      if (a_func != NULL) {
         /*---(type)---------------------*/
         x_macro = poly_debug__macro (a_recd + 6);
         /*---(first debug)--------------*/
         if (a_func->STATS_DMACRO == '-')    a_func->STATS_DMACRO = x_macro;
         /*---(additional debug)---------*/
         else if (a_func->STATS_DMACRO != x_macro) {
            if      (a_func->STATS_DMACRO == 't') a_func->STATS_DMACRO = x_macro;
            else if (x_macro              != 't') a_func->STATS_DMACRO = '!';
         }
      }
      /*---(done)------------------------*/
   }
   /*---(check logging)------------------*/
   else  if (a_recd [0] == 'y') {
      if (strncmp (a_recd, "yLOG", 4) != 0) {
         DEBUG_INPT   yLOG_note    ("not a valid yLOG_ or yLOGS_ logging line");
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_INPT   yLOG_note    ("valid yLOG non-macro debugging line");
      poly_debug__counts (a_file, a_func, 'f');
   }
   /*---(check comments)-----------------*/
   else  if (a_recd [0] == '/' && a_recd [1] == '*') {
      poly_debug__counts (a_file, a_func, 'd');
   }
   else  if (a_recd [0] == '*' && strchr (" >/", a_recd [1]) != NULL) {
      poly_debug__counts (a_file, a_func, 'd');
   }
   /*---(check empties)------------------*/
   else if (strlen  (a_recd) == 0) {
      poly_debug__counts (a_file, a_func, 'e');
   }
   /*---(other)--------------------------*/
   else {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       statistics                             ----===*/
/*====================------------------------------------====================*/
static void  o___STATS___________o () { return; }

char
poly_debug_cflow        (tFUNC *a_func, char a_type, char a_more)
{
   --a_func->WORK_FUNCS;
   switch (a_type) {
   case 'd' :  ++a_func->WORK_DSHORT;       break;
   case 'D' :  ++a_func->WORK_DLONG;        break;
   }
   switch (a_more) {
   case 'e' :  ++a_func->WORK_DENTER;       break;
   case 'x' :  ++a_func->WORK_DEXIT;        break;
   }
   return 0;
}

/*
 *   DSTYLE, long, short, both, mix, none
 *      -     no debugging statements
 *      l     long form only               L  plus non-yLOG debugging
 *      s     short form only              S  plus non-yLOG debugging
 *      b     both long and short          B  plus non-yLOG debugging
 *      ?     only non-yLOG debugging
 *
 *   DMACRO, universals, others, none
 *      -     no macros used
 *      a-z   standard universals
 *      è-ÿ   non-universals tracked
 *      !     multiple macros used
 *      ?     unknown macros
 *      #     free, non-guarded yLOG debugging
 *
 *   DMATCH, enters, exits, and returns
 *      p     no enters or exits (pass-through)
 *      E     no or multiple enters found (but exits)
 *      X     no exits found (but enters)
 *      e     mix-up with enters
 *      x     not-enough or too many exits
 *      ?     internal function calls in short form
 *      !     custom library calls in short form
 *
 *
 */

char
poly_debug_function     (tFUNC *a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   /*---(defense)------------------------*/
   --rce;  if (a_func == NULL)                 return -1;
   --rce;  if (a_func->work == NULL)           return -2;
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



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char
poly_debug__fake        (tFUNC *a_func, int a_return, int a_intern, int a_ylib)
{
   char        rce         =  -10;
   --rce;  if (a_func == NULL)  return rce;
   a_func->WORK_RETURN  = a_return;
   a_func->WORK_GFUNCS  = a_intern;
   a_func->WORK_YLIB    = a_ylib;
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
      u = (tFILE *) poly_btree_entry (B_FUNCS, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->WORK_DCOUNT > 0)  sprintf (s, " %3dc", u->WORK_DCOUNT);
         else                     sprintf (s, "   ·c");
         strlcat (r, s, LEN_RECD);
         if (u->WORK_DFREE  > 0)  sprintf (s, " %3df", u->WORK_DFREE );
         else                     sprintf (s, "   ·f");
         strlcat (r, s, LEN_RECD);
         strlcat (r, "   ", LEN_RECD);
         if (u->WORK_DLONG  > 0)  sprintf (s, " %3dn", u->WORK_DLONG );
         else                     sprintf (s, "   ·n");
         strlcat (r, s, LEN_RECD);
         if (u->WORK_DSHORT > 0)  sprintf (s, " %3ds", u->WORK_DSHORT);
         else                     sprintf (s, "   ·s");
         strlcat (r, s, LEN_RECD);
         if (u->WORK_DENTER > 0)  sprintf (s, " %3de", u->WORK_DENTER);
         else                     sprintf (s, "   ·e");
         strlcat (r, s, LEN_RECD);
         if (u->WORK_DEXIT  > 0)  sprintf (s, " %3dx", u->WORK_DEXIT );
         else                     sprintf (s, "   ·x");
         strlcat (r, s, LEN_RECD);
         strlcat (r, "     ", LEN_RECD);
         sprintf (s, " %c", u->STATS_DMACRO);
         strlcat (r, s, LEN_RECD);
         snprintf (unit_answer, LEN_RECD, "DEBUG work  (%2d) : %-22.22s  %s", i, t, r);
      }  else
         snprintf (unit_answer, LEN_RECD, "DEBUG work  (%2d) : %-22.22s    -c   -f      -n   -s   -e   -x      -", i, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


