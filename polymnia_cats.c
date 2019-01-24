/*============================----beg-of-source---============================*/
#include  "polymnia.h"


char      s_name      [LEN_RECD] = "";
int       s_files   = 0;
int       s_funcs   = 0;
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

#define  IN_TAG  if (a_tag != NULL && a_tag->work != NULL && (a_tag->oneline == 'y' || (a_tag->work->beg >= 0 && a_tag->work->end < 0))) 

char
poly_cats_logic    (tTAG *a_tag, char a_type)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   switch (a_type) {
   case 'r' :
      IN_TAG  ++(a_tag->work->returns);
      break;
   case 'c' :
      IN_TAG  ++(a_tag->work->choices);
      break;
   }
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

#define  IN_TAGLINES  if (a_tag != NULL && a_tag->work != NULL && a_tag->work->beg >= 0 && a_tag->work->end < 0) 

char
poly_cats_lines    (tFILE *a_file, tTAG *a_tag, char a_type)
{
   int         c           =     0;
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   ++(s_lines);
   ++(a_file->lines);
   ++(a_file->proj->lines);
   IN_TAGLINES  ++(a_tag->lines);
   switch (a_type) {
   case 'D' :
      ++(s_debug);
      ++(a_file->debug);
      ++(a_file->proj->debug);
      IN_TAGLINES  ++(a_tag->debug);
      break;
   case 'd' :
      ++(s_docs);
      ++(a_file->docs);
      ++(a_file->proj->docs);
      IN_TAGLINES  ++(a_tag->docs );
      break;
   case 'e' :
      ++(s_empty);
      ++(a_file->empty);
      ++(a_file->proj->empty);
      IN_TAGLINES  ++(a_tag->empty);
      break;
   case 'C' :
      ++(s_code);
      ++(a_file->code);
      ++(a_file->proj->code);
      IN_TAGLINES  ++(a_tag->code );
      c = strldcnt (s_curr, ';', LEN_RECD);
      if (c < 0)  c = 0;
      s_slocl += c;
      a_file->slocl += c;
      a_file->proj->slocl += c;
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
   poly_cats_scaled  ("lines"   , a_tag->lines   , &a_tag->tsize, '-');
   poly_cats_scaled  ("debug"   , a_tag->debug   , &a_tag->dsize, '-');
   poly_cats_scaled  ("slocl"   , a_tag->slocl   , &a_tag->ssize, '-');
   poly_cats_exact   ("locals"  , a_tag->work->lvars   , &a_tag->lsize, '-');
   poly_cats_exact   ("choices" , a_tag->work->choices , &a_tag->csize, '-');
   poly_cats_exact   ("returns" , a_tag->work->returns , &a_tag->rsize, '-');
   a_tag->work->indent  /= 3;
   a_tag->work->indent  -= 1;
   poly_cats_exact   ("indent"  , a_tag->work->indent  , &a_tag->isize, '-');
   poly_cats_flag    ("memories", a_tag->work->memories, &a_tag->msize, '#');
   /*---(group two)----------------------*/
   DEBUG_DATA   yLOG_note    ("group two");
   poly_cats_exact   ("gcalls"  , a_tag->work->gcalls  , &a_tag->Gsize, '-');
   poly_cats_exact   ("lcalls"  , a_tag->work->lcalls  , &a_tag->Lsize, '-');
   poly_cats_exact   ("funcs"   , a_tag->work->funcs   , &a_tag->Fsize, '-');
   poly_cats_exact   ("intern"  , a_tag->work->intern  , &a_tag->Isize, '-');
   poly_cats_exact   ("cstd"    , a_tag->work->cstd    , &a_tag->Csize, '-');
   poly_cats_exact   ("ylib"    , a_tag->work->ylibs   , &a_tag->Ysize, '-');
   a_tag->work->mystry = a_tag->work->funcs - a_tag->work->intern - a_tag->work->cstd - a_tag->work->ylibs - a_tag->work->ncurses - a_tag->work->opengl;
   poly_cats_exact   ("mystry"  , a_tag->work->mystry  , &a_tag->Msize, '-');
   poly_cats_flag    ("reads"   , a_tag->work->reads   , &a_tag->Rflag, 'r');
   poly_cats_flag    ("writes"  , a_tag->work->writes  , &a_tag->Wflag, 'w');
   if (a_tag->work->process > 0 && a_tag->work->scalls  > 0)  a_tag->Lflag = 'B';
   else if (a_tag->work->process > 0)  a_tag->Lflag = 'p';
   else if (a_tag->work->scalls  > 0)  a_tag->Lflag = 's';
   poly_cats_flag    ("recurse" , a_tag->work->recurse , &a_tag->Sflag, '#');
   /*---(group three)--------------------*/
   DEBUG_DATA   yLOG_note    ("group three");
   if (a_tag->work->dlong   > 0 && a_tag->work->dshort  > 0)  a_tag->Dstyle = 'B';
   else if (a_tag->work->dlong   > 0)  a_tag->Dstyle = 'l';
   else if (a_tag->work->dshort  > 0)  a_tag->Dstyle = 's';
   if (a_tag->work->dfree > 0)  a_tag->Dstyle = '#';
   poly_cats_exact   ("ncurses" , a_tag->work->ncurses , &a_tag->Nsize, '-');
   poly_cats_exact   ("opengl"  , a_tag->work->opengl  , &a_tag->Osize, '-');
   poly_cats_exact   ("myx"     , a_tag->work->myx     , &a_tag->Zsize, '-');
   poly_cats_exact   ("window"  , a_tag->work->window  , &a_tag->Wsize, '-');
   poly_cats_exact   ("ecalls"  , a_tag->work->ecalls  , &a_tag->Esize, '-');
   poly_cats_exact   ("extern"  , a_tag->work->xfuncs  , &a_tag->Xsize, '-');
   /*---(type)---------------------------*/
   DEBUG_DATA   yLOG_note    ("group image");
   if      (strncmp (a_tag->name, "o___", 4) == 0)        strlcpy (a_tag->image, "-"     , LEN_LABEL);
   else if (strstr  (a_tag->name, "_init") != NULL)       strlcpy (a_tag->image, "shoot" , LEN_LABEL);
   else if (strstr  (a_tag->name, "_wrap") != NULL)       strlcpy (a_tag->image, "shoot" , LEN_LABEL);
   else if (a_tag->work->funcs == a_tag->work->cstd + a_tag->work->ylibs)   strlcpy (a_tag->image, "leaf"  , LEN_LABEL);
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
               i, t, u->oneline,
               u->scope, u->rtype, u->psize,
               u->tsize, u->dsize, u->ssize,
               u->lsize, u->csize, u->rsize, u->isize, u->msize);
      } else {
         snprintf (unit_answer, LEN_RECD, "CATS complex(%2d) : %-21.21s %c [%c%c%c.%c%c%c.%c%c%c%c%c]",
               i, t, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-');
      }
   }
   else if   (strcmp (a_question, "connect"   )     == 0) {
      if (u != NULL) {
         snprintf (unit_answer, LEN_RECD, "CATS connect(%2d) : %-21.21s %c [%c%c.%c%c%c%c%c.%c%c%c%c]",
               i, t, u->oneline,
               u->Lsize, u->Gsize,
               u->Fsize, u->Isize, u->Csize, u->Ysize, u->Msize,
               u->Rflag, u->Wflag, u->Lflag, u->Sflag);
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



