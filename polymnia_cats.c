/*============================----beg-of-source---============================*/
#include  "htags.h"


char
htags_exists       (char *a_label, int a_src, char *a_dst, char a_zero)
{
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <      0)  *a_dst = '-';
   else if (a_src ==     0)  *a_dst = a_zero;
   else                      *a_dst = '#';
   DEBUG_DATA   yLOG_schar   (*a_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
htags_flag         (char *a_label, int a_src, char *a_dst, char a_flag)
{
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <      0)  *a_dst = '-';
   else if (a_src ==     0)  *a_dst = '-';
   else                      *a_dst = a_flag;
   DEBUG_DATA   yLOG_schar   (*a_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
htags_exact        (char *a_label, int a_src, char *a_dst, char a_zero)
{
   int         c           =    0;
   char       *x_scale     = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int         x_max       = (strlen (x_scale));
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <      0)  *a_dst = '-';
   else if (a_src ==     0)  *a_dst = a_zero;
   else if (a_src >= x_max)  *a_dst = '#';
   else                      *a_dst = x_scale [a_src];
   DEBUG_DATA   yLOG_schar   (*a_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
htags_scaled       (char *a_label, int a_src, char *a_dst, char a_zero)
{
   int         c           =    0;
   char       *x_scale     = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int         x_max       = (strlen (x_scale) - 1) * 5;
   char        x_save      = *a_dst;
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   if (a_label != NULL)  DEBUG_DATA   yLOG_snote   (a_label);
   DEBUG_DATA   yLOG_sint    (a_src);
   if      (a_src <      0)  *a_dst = '-';
   else if (a_src ==     0)  *a_dst = a_zero;
   else if (a_src >= x_max)  *a_dst = '#';
   else                      *a_dst = x_scale [a_src /  5];
   DEBUG_DATA   yLOG_schar   (*a_dst);
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

#define  IN_TAG  if (a_tag >= 0 && (s_tags [a_tag].oneline == 'y' || (s_tags [a_tag].beg >= 0 && s_tags [a_tag].end < 0))) 

char
htags_addlogic     (int a_tag, char a_type)
{
   /*> printf ("   adding a %c to %d\n", a_type, a_tag);                              <*/
   switch (a_type) {
   case 'r' :
      /*> IN_TAG printf ("    can do return\n");                                      <*/
      /*> IN_TAG printf ("    started as %d\n", s_tags [a_tag].returns);              <*/
      IN_TAG  ++(s_tags [a_tag].returns);
      /*> IN_TAG printf ("    ended as   %d\n", s_tags [a_tag].returns);              <*/
      break;
   case 'm' :
      IN_TAG  ++(s_tags [a_tag].memories);
      break;
   case 'c' :
      IN_TAG  ++(s_tags [a_tag].choices);
      break;
   case 'i' :
      IN_TAG  ++(s_tags [a_tag].reads);
      break;
   case 'o' :
      IN_TAG  ++(s_tags [a_tag].writes);
      break;
   }
   return 0;
}

#define  IN_TAGLINES  if (a_tag >= 0 && s_tags [a_tag].beg >= 0 && s_tags [a_tag].end < 0) 

char
htags_addline      (int a_file, int a_tag, char a_type)
{
   int         c           =     0;
   ++(s_files [a_file].lines);
   IN_TAGLINES  ++(s_tags [a_tag].lines);
   switch (a_type) {
   case 'D' :
      ++(s_files [a_file].debug);
      IN_TAGLINES  ++(s_tags [a_tag].debug);
      break;
   case 'd' :
      ++(s_files [a_file].docs);
      IN_TAGLINES  ++(s_tags [a_tag].docs );
      break;
   case 'e' :
      ++(s_files [a_file].empty);
      IN_TAGLINES  ++(s_tags [a_tag].empty);
      break;
   case 'c' :
      /*> if (c != NULL)  fprintf (c, "%s\n", s_curr);                                <*/
      ++(s_files [a_file].code);
      IN_TAGLINES  ++(s_tags [a_tag].code );
      c = strldcnt (s_curr, ';', LEN_RECD);
      if (c < 0)  c = 0;
      s_files [a_file].slocl += c;
      IN_TAGLINES  s_tags [a_tag].slocl += c;
      break;
   }
   return 0;
}

char
htags_cats_depth     (int n)
{
   char        x_recd      [LEN_RECD] = "";
   FILE       *d           = NULL;
   char       *p           = NULL;
   int         x_pre       =    0;
   int         x_min       =  100;
   if (n < 0)  return 0;
   d = fopen ("htags.flow", "rt");
   if (d == NULL) {
      s_tags [n].depth = -2;
      return -1;
   }
   while (1) {
      fgets (x_recd, LEN_RECD, d);
      if (feof (d))  break;
      p = strstr (x_recd, s_tags [n].name);
      if (p == NULL)  continue;
      x_pre = p - x_recd;
      if (x_pre < x_min)  x_min = x_pre;
   }
   fclose (d);
   if (x_min == 100)   s_tags [n].depth = -1;
   else                s_tags [n].depth = x_min / 4;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
htags_cats__unit     (char *a_question, int n)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD];
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "CATS unit        : tag number unknown");
   if (n <  0)       return unit_answer;
   /*> if (n >= s_ntag)  return unit_answer;                                          <*/
   /*---(simple)-------------------------*/
   sprintf  (t, "[%.20s]", s_tags [n].name);
   if        (strcmp (a_question, "complex"   )     == 0) {
      snprintf (unit_answer, LEN_RECD, "CATS complex(%2d) : %-22.22s  [%c%c%c.%c%c%c.%c%c%c%c%c]",
            n, t,
            s_tags [n].scope, s_tags [n].rtype, s_tags [n].psize,
            s_tags [n].tsize, s_tags [n].dsize, s_tags [n].ssize,
            s_tags [n].lsize, s_tags [n].csize, s_tags [n].rsize,
            s_tags [n].isize, s_tags [n].msize);
   }
   else if   (strcmp (a_question, "connect"   )     == 0) {
      snprintf (unit_answer, LEN_RECD, "CATS connect(%2d) : %-22.22s  [%c%c%c%c.%c%c%c%c.%c%c%c]",
            n, t,
            s_tags [n].Lsize, s_tags [n].Gsize, s_tags [n].Esize, s_tags [n].Dsize,
            s_tags [n].Fsize, s_tags [n].Csize, s_tags [n].Ysize, s_tags [n].Xsize,
            s_tags [n].Rsize, s_tags [n].Wsize, s_tags [n].Vsize);
   }
   else if   (strcmp (a_question, "future"    )     == 0) {
      snprintf (unit_answer, LEN_RECD, "CATS future (%2d) : %-22.22s  [%c%c%c%c.%c%c%c.%c%c%c%c]",
            n, t,
            '-', '-', '-', 
            '-', '-', '-', '-', 
            '-', '-', '-', '-');
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
