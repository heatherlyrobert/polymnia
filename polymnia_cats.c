/*============================----beg-of-source---============================*/
#include  "polymnia.h"



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
   if      (a_src <      0)  *a_dst = '-';
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
   if      (a_src <      0)  *a_dst = '-';
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
poly_cats_scaled   (char *a_label, int a_src, char *a_dst, char a_zero)
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



/*====================------------------------------------====================*/
/*===----                    adding tags/line values                   ----===*/
/*====================------------------------------------====================*/
static void  o___ADDING__________o () { return; }

#define  IN_TAG  if (a_tag >= 0 && (s_tags [a_tag].oneline == 'y' || (s_tags [a_tag].beg >= 0 && s_tags [a_tag].end < 0))) 

char
poly_cats_logic    (int a_tag, char a_type)
{
   switch (a_type) {
   case 'r' :
      IN_TAG  ++(s_tags [a_tag].returns);
      break;
   case 'c' :
      IN_TAG  ++(s_tags [a_tag].choices);
      break;
   }
   return 0;
}

#define  IN_TAGLINES  if (a_tag >= 0 && s_tags [a_tag].beg >= 0 && s_tags [a_tag].end < 0) 

char
poly_cats_lines    (int a_file, int a_tag, char a_type)
{
   int         c           =     0;
   ++(s_files [a_file].lines);
   ++(s_totals.lines);
   IN_TAGLINES  ++(s_tags [a_tag].lines);
   switch (a_type) {
   case 'D' :
      ++(s_totals.debug);
      ++(s_files [a_file].debug);
      IN_TAGLINES  ++(s_tags [a_tag].debug);
      break;
   case 'd' :
      ++(s_totals.docs);
      ++(s_files [a_file].docs);
      IN_TAGLINES  ++(s_tags [a_tag].docs );
      break;
   case 'e' :
      ++(s_totals.empty);
      ++(s_files [a_file].empty);
      IN_TAGLINES  ++(s_tags [a_tag].empty);
      break;
   case 'c' :
      ++(s_totals.code);
      ++(s_files [a_file].code);
      IN_TAGLINES  ++(s_tags [a_tag].code );
      c = strldcnt (s_curr, ';', LEN_RECD);
      if (c < 0)  c = 0;
      s_totals.slocl += c;
      s_files [a_file].slocl += c;
      IN_TAGLINES  s_tags [a_tag].slocl += c;
      break;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      specialty categories                    ----===*/
/*====================------------------------------------====================*/
static void  o___SPECIALTY_______o () { return; }

char
poly_cats_depth      (int n)
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
/*===----                   creating the tag summary                   ----===*/
/*====================------------------------------------====================*/
static void  o___SUMMARY_________o () { return; }

char
poly_cats_tagsumm  (int n)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_value   ("index"     , n);
   if (n < 0) {
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return -1;
   }
   DEBUG_DATA   yLOG_info    ("name"      , s_tags [n].name);
   htags_parse        (n);
   poly_extern_review (n);
   /*> poly_cats_depth  (n);                                                          <*/
   s_tags [n].indent  /= 3;
   s_tags [n].indent  -= 1;
   /*---(group one)----------------------*/
   poly_cats_scaled  ("lines"   , s_tags [n].lines   , &s_tags [n].tsize, '-');
   poly_cats_scaled  ("debug"   , s_tags [n].debug   , &s_tags [n].dsize, '-');
   poly_cats_scaled  ("slocl"   , s_tags [n].slocl   , &s_tags [n].ssize, '-');
   poly_cats_exact   ("choices" , s_tags [n].choices , &s_tags [n].csize, '-');
   poly_cats_exact   ("returns" , s_tags [n].returns , &s_tags [n].rsize, '-');
   poly_cats_exact   ("indent"  , s_tags [n].indent  , &s_tags [n].isize, '-');
   poly_cats_exact   ("locals"  , s_tags [n].lvars   , &s_tags [n].lsize, '-');
   poly_cats_flag    ("memories", s_tags [n].memories, &s_tags [n].msize, '#');
   /*---(group two)----------------------*/
   poly_cats_exact   ("lcalls"  , s_tags [n].lcalls  , &s_tags [n].Lsize, '-');
   poly_cats_exact   ("gcalls"  , s_tags [n].gcalls  , &s_tags [n].Gsize, '-');
   poly_cats_exact   ("ecalls"  , s_tags [n].ecalls  , &s_tags [n].Esize, '-');
   poly_cats_exact   ("depth"   , s_tags [n].depth   , &s_tags [n].Dsize, '-');
   poly_cats_exact   ("funcs"   , s_tags [n].funcs   , &s_tags [n].Fsize, '-');
   poly_cats_exact   ("cstd"    , s_tags [n].cstd    , &s_tags [n].Csize, '-');
   poly_cats_exact   ("ylib"    , s_tags [n].ylibs   , &s_tags [n].Ysize, '-');
   poly_cats_exact   ("extern"  , s_tags [n].xfuncs  , &s_tags [n].Xsize, '-');
   poly_cats_flag    ("reads"   , s_tags [n].reads   , &s_tags [n].Rsize, 'R');
   poly_cats_flag    ("writes"  , s_tags [n].writes  , &s_tags [n].Wsize, 'W');
   poly_cats_flag    ("visual"  , s_tags [n].ncurses + s_tags [n].opengl, &s_tags [n].Vsize, 'N');
   if (s_tags [n].ncurses > 0 && s_tags [n].opengl  > 0)  s_tags [n].Vsize = 'B';
   else if (s_tags [n].ncurses > 0)  s_tags [n].Vsize = 'N';
   else if (s_tags [n].opengl  > 0)  s_tags [n].Vsize = 'O';
   poly_cats_flag    ("process" , s_tags [n].process , &s_tags [n].Psize, 'P');
   poly_cats_flag    ("systen"  , s_tags [n].scalls  , &s_tags [n].Ssize, 'S');
   /*---(output)-------------------------*/
   printf ("   tag (%3d) %-25.25s %c [%c%c%c.%c%c%c.%c%c%c%c%c] [%c%c%c.%c%c%c.%c%c%c%c%c]\n",
         n, s_tags [n].name, s_tags [n].oneline,

         s_tags [n].scope, s_tags [n].rtype, s_tags [n].psize,
         s_tags [n].tsize, s_tags [n].dsize, s_tags [n].ssize,
         s_tags [n].lsize, s_tags [n].csize, s_tags [n].rsize, s_tags [n].isize, s_tags [n].msize,

         s_tags [n].Lsize, s_tags [n].Gsize, s_tags [n].Esize, s_tags [n].Fsize,
         s_tags [n].Csize, s_tags [n].Ysize,
         s_tags [n].Rsize, s_tags [n].Wsize, s_tags [n].Vsize,
         s_tags [n].Psize, s_tags [n].Ssize);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
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
