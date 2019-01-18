/*============================----beg-of-source---============================*/
#include  "polymnia.h"


int       s_lines   = 0;
int       s_empty   = 0;
int       s_docs    = 0;
int       s_debug   = 0;
int       s_code    = 0;
int       s_slocl   = 0;


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

#define  IN_TAG  if (a_tag != NULL && (a_tag->oneline == 'y' || (a_tag->beg >= 0 && a_tag->end < 0))) 

char
poly_cats_logic    (tTAG *a_tag, char a_type)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   switch (a_type) {
   case 'r' :
      IN_TAG  ++(a_tag->returns);
      break;
   case 'c' :
      IN_TAG  ++(a_tag->choices);
      break;
   }
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

#define  IN_TAGLINES  if (a_tag != NULL && a_tag->beg >= 0 && a_tag->end < 0) 

char
poly_cats_lines    (tFILE *a_file, tTAG *a_tag, char a_type)
{
   int         c           =     0;
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   ++(a_file->lines);
   ++(s_lines);
   IN_TAGLINES  ++(a_tag->lines);
   switch (a_type) {
   case 'D' :
      ++(s_debug);
      ++(a_file->debug);
      IN_TAGLINES  ++(a_tag->debug);
      break;
   case 'd' :
      ++(s_docs);
      ++(a_file->docs);
      IN_TAGLINES  ++(a_tag->docs );
      break;
   case 'e' :
      ++(s_empty);
      ++(a_file->empty);
      IN_TAGLINES  ++(a_tag->empty);
      break;
   case 'C' :
      ++(s_code);
      ++(a_file->code);
      IN_TAGLINES  ++(a_tag->code );
      c = strldcnt (s_curr, ';', LEN_RECD);
      if (c < 0)  c = 0;
      s_slocl += c;
      a_file->slocl += c;
      IN_TAGLINES  a_tag->slocl += c;
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
poly_cats_tagsumm  (tTAG *a_tag)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_info    ("name"      , a_tag->name);
   a_tag->indent  /= 3;
   a_tag->indent  -= 1;
   /*---(group one)----------------------*/
   poly_cats_scaled  ("lines"   , a_tag->lines   , &a_tag->tsize, '-');
   poly_cats_scaled  ("debug"   , a_tag->debug   , &a_tag->dsize, '-');
   poly_cats_scaled  ("slocl"   , a_tag->slocl   , &a_tag->ssize, '-');
   poly_cats_exact   ("locals"  , a_tag->lvars   , &a_tag->lsize, '-');
   poly_cats_exact   ("choices" , a_tag->choices , &a_tag->csize, '-');
   poly_cats_exact   ("returns" , a_tag->returns , &a_tag->rsize, '-');
   poly_cats_exact   ("indent"  , a_tag->indent  , &a_tag->isize, '-');
   poly_cats_flag    ("memories", a_tag->memories, &a_tag->msize, '#');
   /*---(group two)----------------------*/
   poly_cats_exact   ("gcalls"  , a_tag->gcalls  , &a_tag->Gsize, '-');
   poly_cats_exact   ("lcalls"  , a_tag->lcalls  , &a_tag->Lsize, '-');
   poly_cats_exact   ("ecalls"  , a_tag->ecalls  , &a_tag->Esize, '-');
   poly_cats_exact   ("funcs"   , a_tag->funcs   , &a_tag->Fsize, '-');
   poly_cats_exact   ("intern"  , a_tag->intern  , &a_tag->Isize, '-');
   poly_cats_exact   ("cstd"    , a_tag->cstd    , &a_tag->Csize, '-');
   poly_cats_exact   ("ylib"    , a_tag->ylibs   , &a_tag->Ysize, '-');
   a_tag->mystry = a_tag->funcs - a_tag->intern - a_tag->cstd - a_tag->ylibs - a_tag->ncurses - a_tag->opengl;
   poly_cats_exact   ("mystry"  , a_tag->mystry  , &a_tag->Msize, '-');
   poly_cats_exact   ("extern"  , a_tag->xfuncs  , &a_tag->Xsize, '-');
   poly_cats_flag    ("reads"   , a_tag->reads   , &a_tag->Rflag, 'r');
   poly_cats_flag    ("writes"  , a_tag->writes  , &a_tag->Wflag, 'w');
   poly_cats_flag    ("visual"  , a_tag->ncurses + a_tag->opengl, &a_tag->Vflag, 'N');
   poly_cats_exact   ("ncurses" , a_tag->ncurses , &a_tag->Nsize, '-');
   poly_cats_exact   ("opengl"  , a_tag->opengl  , &a_tag->Osize, '-');
   if (a_tag->process > 0 && a_tag->scalls  > 0)  a_tag->Lflag = 'B';
   else if (a_tag->process > 0)  a_tag->Lflag = 'p';
   else if (a_tag->scalls  > 0)  a_tag->Lflag = 's';
   poly_cats_flag    ("recurse" , a_tag->recurse , &a_tag->Sflag, '#');
   /*---(group three)--------------------*/
   if (a_tag->dlong   > 0 && a_tag->dshort  > 0)  a_tag->Dstyle = 'B';
   else if (a_tag->dlong   > 0)  a_tag->Dstyle = 'l';
   else if (a_tag->dshort  > 0)  a_tag->Dstyle = 's';
   if (a_tag->dfree > 0)  a_tag->Dstyle = '#';
   /*---(type)---------------------------*/
   if      (strncmp (a_tag->name, "o___", 4) == 0)        strlcpy (a_tag->image, "-"     , LEN_LABEL);
   else if (strstr  (a_tag->name, "_init") != NULL)       strlcpy (a_tag->image, "shoot" , LEN_LABEL);
   else if (strstr  (a_tag->name, "_wrap") != NULL)       strlcpy (a_tag->image, "shoot" , LEN_LABEL);
   else if (a_tag->funcs == a_tag->cstd + a_tag->ylibs)   strlcpy (a_tag->image, "leaf"  , LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
htags_cats__unit     (char *a_question, int i)
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
         snprintf (unit_answer, LEN_RECD, "CATS complex(%2d) : %-22.22s  [%c%c%c.%c%c%c.%c%c%c%c%c]",
               i, t,
               u->scope, u->rtype, u->psize,
               u->tsize, u->dsize, u->ssize,
               u->lsize, u->csize, u->rsize, u->isize, u->msize);
      } else {
         snprintf (unit_answer, LEN_RECD, "CATS complex(%2d) : %-22.22s  [%c%c%c.%c%c%c.%c%c%c%c%c]",
               i, t, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-');
      }
   }
   else if   (strcmp (a_question, "connect"   )     == 0) {
      if (u != NULL) {
         snprintf (unit_answer, LEN_RECD, "CATS connect(%2d) : %-22.22s  [%c%c%c.%c%c%c.%c%c%c%c%c]",
               i, t,
               u->Lsize, u->Gsize, u->Esize,
               u->Fsize, u->Csize, u->Ysize,
               u->Rflag, u->Wflag, u->Vflag, u->Lflag, u->Sflag);
      } else {
         snprintf (unit_answer, LEN_RECD, "CATS connect(%2d) : %-22.22s  [%c%c%c.%c%c%c.%c%c%c%c%c]",
               i, t, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-');
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



