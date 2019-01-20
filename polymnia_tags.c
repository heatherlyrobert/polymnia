/*============================----beg-of-source---============================*/
#include  "polymnia.h"



#define   MAX_MACRO     26
struct cMACRO {
   char        name        [LEN_LABEL];
   char        abbr;
} s_macros [MAX_MACRO] = {

   { "TOPS"    , 't' },
   { "SUMM"    , 'r' },
   { "VERB"    , 'v' },

   { "ARGS"    , 'a' },
   { "CONF"    , 'c' },
   { "PROG"    , 'p' },

   { "INPT"    , 'i' },
   { "OUTP"    , 'o' },
   { "SQLS"    , 'q' },

   { "LOOP"    , 'l' },
   { "USER"    , 'u' },
   { "APIS"    , 'z' },
   { "SIGN"    , 'x' },
   { "SCRP"    , 'b' },
   { "HIST"    , 'h' },

   { "GRAF"    , 'g' },
   { "WIND"    , 'w' },
   { "DATA"    , 'd' },
   { "ENVI"    , 'e' },
   { "SORT"    , 's' },

};


/*====================------------------------------------====================*/
/*===----                       support functions                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_tags_macro    (char *a_macro)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   char        i           =    0;           /* return code for errors         */
   static char x_macro     [LEN_LABEL] = "";
   static char n           =   -1;
   if (a_macro == NULL)  return '?';
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   if (strcmp (a_macro, x_macro) == 0) {
      DEBUG_PROG   yLOG_snote   ("short-cut");
      DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
      return n;
   }
   DEBUG_PROG   yLOG_snote   (a_macro);
   for (i = 0; i < MAX_MACRO; ++i) {
      if (s_macros [i].name [0] != a_macro [0])            continue;
      if (strncmp (s_macros [i].name, a_macro, 4) != 0)    continue;
      strlcpy (x_macro, a_macro, LEN_LABEL);
      n = i;
      DEBUG_PROG   yLOG_schar   (s_macros [i].abbr);
      DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
      return s_macros [i].abbr;
   }
   DEBUG_PROG   yLOG_schar   ('?');
   DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, -1);
   return '?';
}

char
poly_tags__hint    (int n, char *a_label)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char       *x_1st       = "abcdefghijklmnopqrstuvwxyz";
   int         x_1len      = strlen (x_1st);
   char       *x_2nd       = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int         x_2len      = strlen (x_2nd);
   --rce;  if (a_label == NULL)  return rce;
   strlcpy (a_label, "··", LEN_LABEL);
   --rce;  if (n < 0)            return rce;
   --rce;  if (n > 1351)         return rce;
   a_label [0] = x_1st [n / x_2len];
   a_label [1] = x_2nd [n % x_2len];
   a_label [2] = '\0';
   return 0;
}

tTAG*
poly_tags_byline        (tFILE *a_file, int a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tTAG       *u           = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_spoint  ("a_file");
   --rce;  if (a_file == NULL) {
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_sint    (a_line);
   /*---(first)--------------------------*/
   u = a_file->head ;
   DEBUG_PROG   yLOG_spoint  (u);
   --rce;  if (u == NULL) {
      DEBUG_PROG   yLOG_snote   ("no tags in file");
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, rce);
      /*> return 0;                                                                   <*/
      return rce;
   }
   /*---(walk)---------------------------*/
   while (u != NULL) {
      ++c;
      /*> DEBUG_PROG   yLOG_snote   (u->name);                                        <*/
      /*> DEBUG_PROG   yLOG_sint    (u->beg);                                         <*/
      /*> DEBUG_PROG   yLOG_sint    (u->end);                                         <*/
      if (u->work->beg <= a_line && u->work->end >= a_line) {
         DEBUG_PROG   yLOG_snote   ("FOUND");
         DEBUG_PROG   yLOG_sint    (c);
         DEBUG_PROG   yLOG_snote   (u->name);
         DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
         return u;
      }
      u = u->next;
   }
   DEBUG_PROG   yLOG_snote   ("not found");
   DEBUG_PROG   yLOG_sint    (c);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return NULL;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_tags_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = poly_btree_init (B_TAGS);
   DEBUG_PROG   yLOG_value   ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_tags_wrap          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(walk through list)--------------*/
   rc = poly_btree_purge (B_TAGS);
   DEBUG_PROG   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_tags__wipe    (tTAG *a_dst)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(master)-------------------------*/
   a_dst->type     = '-';
   a_dst->name [0] = '\0';
   a_dst->line     = -1;
   a_dst->hint [0] = '\0';
   a_dst->image[0] = '\0';
   a_dst->desc [0] = '\0';
   a_dst->ready    = '?';
   /*---(pointers)-----------------------*/
   a_dst->file     = NULL;
   a_dst->prev     = NULL;
   a_dst->next     = NULL;
   a_dst->work     = NULL;
   /*---(positioning)--------------------*/
   a_dst->oneline  = '-';
   /*---(line counts)--------------------*/
   a_dst->lines    = 0;
   a_dst->empty    = 0;
   a_dst->docs     = 0;
   a_dst->debug    = 0;
   a_dst->code     = 0;
   a_dst->slocl    = 0;
   /*---(group one outputs)--------------*/
   a_dst->scope    = '-';     /* 1st sub */
   a_dst->rtype    = '-';
   a_dst->psize    = '-';
   a_dst->tsize    = '-';     /* 2nd sub */
   a_dst->dsize    = '-';
   a_dst->ssize    = '-';
   a_dst->lsize    = '-';     /* 3rd sub */
   a_dst->csize    = '-';
   a_dst->rsize    = '-';
   a_dst->isize    = '-';
   a_dst->msize    = '-';
   /*---(group two outputs)--------------*/
   a_dst->Lsize    = '-';     /* 1st sub */
   a_dst->Gsize    = '-';
   a_dst->Fsize    = '-';     /* 2nd sub */
   a_dst->Isize    = '-';
   a_dst->Csize    = '-';
   a_dst->Ysize    = '-';
   a_dst->Msize    = '-';
   a_dst->Rflag    = '-';     /* 3rd sub */
   a_dst->Wflag    = '-';
   a_dst->Lflag    = '-';
   a_dst->Sflag    = '-';
   /*---(group three outputs)------------*/
   a_dst->Dstyle   = '-';     /* 1st sub */
   a_dst->Dmacro   = '-';
   a_dst->Nsize    = '-';     /* 2nd sub */
   a_dst->Osize    = '-';
   a_dst->Wsize    = '-';
   a_dst->Zsize    = '-';
   a_dst->Pstyle   = '-';     /* 3rd sub */
   a_dst->Esize    = '-';                  
   a_dst->Xsize    = '-';
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_tags__wipe_work    (tWORK *a_dst)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(positioning)--------------------*/
   a_dst->beg      = -1;
   a_dst->end      = -1;
   /*---(group one working)--------------*/
   a_dst->nparam   = -3;
   a_dst->lvars    = 0;
   a_dst->choices  = 0;
   a_dst->returns  = 0;
   a_dst->indent   = 0;
   a_dst->memories = 0;
   /*---(group two working)-----------*/
   a_dst->lcalls   = 0;
   a_dst->gcalls   = 0;
   a_dst->ecalls   = 0;
   a_dst->depth    = 0;
   a_dst->funcs    = 0;
   a_dst->intern   = 0;
   a_dst->cstd     = 0;
   a_dst->ylibs    = 0;
   a_dst->mystry   = 0;
   a_dst->xfuncs   = 0;
   a_dst->reads    = 0;
   a_dst->writes   = 0;
   a_dst->opengl   = 0;
   a_dst->ncurses  = 0;
   a_dst->process  = 0;
   a_dst->scalls   = 0;
   a_dst->recurse  = 0;
   /*---(group three working)---------*/
   a_dst->dlong    = 0;
   a_dst->dshort   = 0;
   a_dst->dfree    = 0;
   a_dst->window   = 0;
   a_dst->myx      = 0;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

tTAG*
poly_tags_new           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tTAG       *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tTAG *) malloc (sizeof (tTAG));
      if (x_tries > 10)   break;
   }
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return NULL;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("wipe clean");
   poly_tags__wipe (x_new);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return x_new;
}

tWORK*
poly_tags_new_work      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tWORK      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tWORK *) malloc (sizeof (tWORK));
      if (x_tries > 10)   break;
   }
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return NULL;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("wipe clean");
   poly_tags__wipe_work (x_new);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return x_new;
}

char
poly_tags_add           (tFILE *a_file, char *a_name, char a_type, int a_line, tTAG **a_tag)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tTAG       *x_new       = NULL;
   int         x_tries     =    0;
   int         x_len       =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (a_tag != NULL)  *a_tag = NULL;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   DEBUG_DATA   yLOG_char    ("a_type"    , a_type);
   --rce;  if (a_type != 'f') {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_value   ("a_line"    , a_line);
   --rce;  if (a_line <= 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_tag"     , a_tag);
   /*---(create cell)--------------------*/
   x_new = poly_tags_new ();
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create cell)--------------------*/
   x_new->work = poly_tags_new_work ();
   DEBUG_DATA   yLOG_point   ("->work"    , x_new->work);
   --rce;  if (x_new->work == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   x_new->file   = a_file;
   strlcpy (x_new->name, a_name, LEN_NAME);
   x_new->type   = a_type;
   x_new->line   = a_line;
   /*---(into file list)-----------------*/
   rc = poly_files_addtag (a_file, x_new);
   DEBUG_DATA   yLOG_value   ("addtag"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(into btree)---------------------*/
   rc = poly_btree_create (B_TAGS, x_new, x_new->name);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create hint)--------------------*/
   rc = poly_tags__hint   (poly_btree_count (B_TAGS) - 1, x_new->hint);
   DEBUG_DATA   yLOG_value   ("hint"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("hint"      , x_new->hint);
   /*---(save)---------------------------*/
   if (a_tag != NULL)  *a_tag = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_tags__extracts     (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          =   0;           /* generic return code            */
   char        x_cmd       [LEN_RECD];      /* ctags command                  */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(function calls)-----------------*/
   sprintf (x_cmd, "ctags  --language-force=c -x --sort=no --file-scope=yes  --c-kinds=pfl %s > %s", a_name, F_CTAGS);
   DEBUG_INPT   yLOG_info    ("system"    , x_cmd);
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_tags__cleanup      (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          =   0;           /* generic return code            */
   char        x_cmd       [LEN_RECD];      /* ctags command                  */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(function calls)-----------------*/
   sprintf (x_cmd, "rm -f %s", F_CTAGS);
   DEBUG_INPT   yLOG_info    ("system"    , x_cmd);
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> read and parse crontab lines ----------[ ------ [ ------ ]-*/
poly_tags_inventory     (tFILE *a_file)
{  /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   int         rc          =    0;           /* generic return code            */
   char        x_recd      [LEN_RECD];      /* input record                   */
   int         x_len       =    0;             /* length of input record         */
   char       *p           = NULL;
   char       *q           =  " ";
   int         c           =    0;
   char        x_name      [LEN_NAME];
   int         x_line      =    0;
   char        x_type      =  '-';
   char        x_source    [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->name);
   /*---(prepare)------------------------*/
   poly_tags__extracts (a_file->name);
   DEBUG_INPT   yLOG_value   ("extracts"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(open)---------------------------*/
   DEBUG_INPT   yLOG_info    ("tag file"  , F_CTAGS);
   f_tags = fopen (F_CTAGS, "r");
   DEBUG_INPT   yLOG_point   ("f_tags"         , f_tags);
   --rce;  if (f_tags == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_note    ("openned successfully");
   /*---(walk tags)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets  (x_recd, LEN_RECD, f_tags);
      if (feof (f_tags)) {
         DEBUG_INPT   yLOG_note    ("end of file");
         break;
      }
      /*---(filter)----------------------*/
      x_len = strlen (x_recd);
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      if (x_len < 10) {
         DEBUG_INPT   yLOG_note    ("too short, SKIP");
         continue;
      }
      x_recd [--x_len] = '\0';
      DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
      /*---(name)------------------------*/
      p = strtok (x_recd, q);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("can not find name field, SKIP");
         continue;
      }
      strlcpy (x_name, p, LEN_NAME);
      DEBUG_INPT   yLOG_info    ("name"      , x_name);
      /*---(type)------------------------*/
      p = strtok (NULL  , q);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("can not find type field, SKIP");
         continue;
      }
      if (strcmp ("local", p) == 0) {
         DEBUG_INPT   yLOG_note    ("found a local");
         if (a_file->tail != NULL) {
            DEBUG_INPT   yLOG_info    ("local for" , a_file->tail->name);
            ++(a_file->tail->work->lvars);
         }
         continue;
      }
      if (strcmp ("function", p) != 0) {
         DEBUG_INPT   yLOG_note    ("not a function, SKIP");
         continue;
      }
      x_type = p [0];
      DEBUG_INPT   yLOG_char    ("type"      , x_type);
      /*---(line)------------------------*/
      p = strtok (NULL  , q);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("can not find line field, SKIP");
         continue;
      }
      x_line = atoi (p);
      DEBUG_INPT   yLOG_value   ("line"      , x_line);
      /*---(done)------------------------*/
      poly_tags_add (a_file, x_name, x_type, x_line, NULL);
      ++c;
   }
   rc = fclose (f_tags);
   DEBUG_INPT   yLOG_point   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   f_tags = NULL;
   /*---(wrapup)-------------------------*/
   poly_tags__cleanup ();
   DEBUG_INPT   yLOG_value   ("cleanup"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(summary)------------------------*/
   DEBUG_INPT   yLOG_value   ("c"         , c);
   DEBUG_INPT   yLOG_value   ("count"     , poly_btree_count (B_TAGS));
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> extract the function desc ----------[ ------ [ge.850.137.A4]*/ /*-[02.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_tags__desc         (tTAG *a_tag, char *a_beg)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       x_desc       [LEN_RECD];
   int        i            =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_beg == NULL) {
      a_tag->ready = 'e';
      return rce;
   }
   --rce;  if (strlen (s_prev) < 70) {
      return rce;
   }
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(current style)------------------*/
   if ((strncmp (a_beg, "/*-> ", 5) == 0 && strncmp (a_beg + 40, "-[ " , 3) == 0)) {
      DEBUG_INPT   yLOG_snote   ("current format");
      strlcpy (x_desc, a_beg + 5, 35);
      for (i = 35; i > 0; --i)  {
         if (strchr (" -=]", x_desc [i]) != NULL)   x_desc [i] = '\0';
         break;
      }
      strlcpy (a_tag->desc, x_desc, 35);
      a_tag->ready = 'y';
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_beg, "/*--> ",  6) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 1 format");
      strlcpy (x_desc, a_beg +  6, 35);
      for (i = 35; i > 0; --i)  {
         if (strchr (" -=]", x_desc [i]) != NULL)   x_desc [i] = '\0';
         break;
      }
      strlcpy (a_tag->desc, x_desc, 35);
      a_tag->ready = 'y';
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_beg, "/* ---- : ", 10) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 2 format");
      strlcpy (x_desc, a_beg + 10, 35);
      for (i = 35; i > 0; --i)  {
         if (strchr (" -=]", x_desc [i]) != NULL)   x_desc [i] = '\0';
         break;
      }
      strlcpy (a_tag->desc, x_desc, 35);
      a_tag->ready = 'y';
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_beg, "/*----: ",  8) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 3 format");
      strlcpy (x_desc, a_beg +  8, 35);
      for (i = 35; i > 0; --i)  {
         if (strchr (" -=]", x_desc [i]) != NULL)   x_desc [i] = '\0';
         break;
      }
      strlcpy (a_tag->desc, x_desc, 35);
      a_tag->ready = 'y';
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_beg, "/*===[[ ",  8) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 3 format");
      strlcpy (x_desc, a_beg +  8, 35);
      for (i = 35; i > 0; --i)  {
         if (strchr (" -=]", x_desc [i]) != NULL)   x_desc [i] = '\0';
         break;
      }
      strlcpy (a_tag->desc, x_desc, 35);
      a_tag->ready = 'y';
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_tags__scope        (tTAG *a_tag, int a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   char       *r           = NULL;
   char       *a           = NULL;
   char       *b           = NULL;
   int        x_len        =    0;
   char       x_return     [LEN_RECD];
   char       x_params     [LEN_RECD];
   char       x_body       [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_value   ("a_line"    , a_line);
   /*---(oneline)------------------------*/
   p = strstr (s_curr, a_tag->name);
   DEBUG_DATA   yLOG_point   ("p"         , p);
   x_len = p - s_curr;
   DEBUG_DATA   yLOG_value   ("x_len"     , x_len);
   if (x_len == 0)   a_tag->oneline = '-';
   else              a_tag->oneline = 'y';
   DEBUG_DATA   yLOG_char    ("oneline"   , a_tag->oneline);
   /*---(oneline return type)------------*/
   if (a_tag->oneline == 'y') {
      strlcpy (x_return, s_curr, x_len);
      a_tag->ready = ' ';
   }
   /*---(multiline return type)----------*/
   else {
      r = strstr (s_prev, "/*");
      if (r == NULL)  x_len = strlen (s_prev);
      else            x_len = r - s_prev;
      strlcpy (x_return, s_prev, x_len + 1);
      poly_tags__desc (a_tag, r);
   }
   strltrim (x_return, ySTR_SINGLE, LEN_RECD);
   DEBUG_DATA   yLOG_info    ("x_return"  , x_return);
   /*---(classify return type)-----------*/
   if      (strstr (x_return   , "char*" ) != NULL)  a_tag->rtype = 's';
   else if (strstr (x_return   , "char"  ) != NULL)  a_tag->rtype = 'c';
   else if (strstr (x_return   , "void"  ) != NULL)  a_tag->rtype = 'v';
   else if (strstr (x_return   , "*"     ) != NULL)  a_tag->rtype = 'p';
   else                                              a_tag->rtype = 'n';
   DEBUG_DATA   yLOG_char    ("rtype"     , a_tag->rtype);
   /*---(classify scope)-----------------*/
   if      (strstr (a_tag->name, "__unit") != NULL)  a_tag->scope = 'u';
   else if (strstr (a_tag->name, "__test") != NULL)  a_tag->scope = 'u';
   else if (strstr (x_return   , "static") != NULL)  a_tag->scope = 's';
   else if (strstr (a_tag->name, "__"    ) != NULL)  a_tag->scope = 'f';
   else                                              a_tag->scope = 'g';
   DEBUG_DATA   yLOG_char    ("scope"     , a_tag->scope);
   /*---(parms)--------------------------*/
   a = strchr (p, '(');
   if (a != NULL) {
      DEBUG_DATA   yLOG_note    ("found open paren");
      b = strchr (p, '{');
      if (b == NULL)  x_len = LEN_RECD;
      else            x_len = b - a;
      strlcpy  (x_params         , a, x_len);
      strltrim (x_params         , ySTR_EVERY , x_len);
      if      (strcmp (x_params, "()")     == 0)  a_tag->work->nparam = -2;
      else if (strcmp (x_params, "(void)") == 0)  a_tag->work->nparam =  0;
      else    a_tag->work->nparam = strldcnt (x_params, ',', x_len) + 1;
   } else {
      a_tag->work->nparam = -2;
   }
   poly_cats_exact   ("nparam"  , a_tag->work->nparam  , &a_tag->psize, '0');
   /*---(one-liner)----------------------*/
   if (a_tag->oneline == 'y') {
      if (b != NULL) {
         p = strchr (b, '}');
         x_len = p - b;
         strlcpy  (x_body, b, x_len);
         strltrim (x_body, ySTR_EVERY , x_len);
         /*> a_tag->lines  = a_tag->empty  = -1;                                      <* 
          *> a_tag->docs   = a_tag->debug  = -1;                                      <* 
          *> a_tag->code   = a_tag->slocl  = -1;                                      <*/
         /*> if (strcmp (x_body, "{}")     == 0) {                                         <* 
          *>    a_tag->work->lvars  = a_tag->work->choices = a_tag->work->returns  = -1;   <* 
          *>    a_tag->work->memories = a_tag->work->indent = -1;                          <* 
          *> }                                                                             <*/
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_tags__linetype     (tFILE *a_file, tTAG *a_tag)
{
   /*---(locals)-----------+-----------+-*/
   int         i           =    0;
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   char        x_macro     =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(line type)----------------------*/
   strlcpy  (x_recd, s_curr, LEN_RECD);
   strltrim (x_recd, ySTR_BOTH, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
   if      (strncmp (x_recd, "DEBUG_"   , 6) == 0) {
      DEBUG_INPT   yLOG_note    ("debug type");
      poly_cats_lines (a_file, a_tag, 'D');
      x_macro = poly_tags_macro (x_recd + 6);
      if (a_tag != NULL) {
         if (a_tag->Dmacro == '-')           a_tag->Dmacro = x_macro;
         else if (a_tag->Dmacro != x_macro)  a_tag->Dmacro = '#';
      }
   }
   else if (strncmp (x_recd, "yLOG_"    , 5) == 0)  ++a_tag->work->dfree;
   else if (strncmp (x_recd, "/*"       , 2) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strncmp (x_recd, "* "       , 2) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strncmp (x_recd, "*>"       , 2) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strcmp  (x_recd, "*"           ) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strcmp  (x_recd, "*/"          ) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strlen  (x_recd)                 == 0)  poly_cats_lines (a_file, a_tag, 'e');
   /*---(code line)----------------------*/
   else {
      DEBUG_INPT   yLOG_note    ("code type");
      DEBUG_INPT   yLOG_info    ("s_curr"    , s_curr);
      poly_cats_lines (a_file, a_tag, 'C');
      if      (strstr (s_curr, " return "   ) != NULL) poly_cats_logic (a_tag, 'r');
      if      (strstr (s_curr, " return;"   ) != NULL) poly_cats_logic (a_tag, 'r');
      if      (strstr (s_curr, " if "       ) != NULL) poly_cats_logic (a_tag, 'c');
      else if (strstr (s_curr, " else "     ) != NULL) poly_cats_logic (a_tag, 'c');
      if      (strstr (s_curr, " switch "   ) != NULL) poly_cats_logic (a_tag, 'c');
      if      (strstr (s_curr, " while "    ) != NULL) poly_cats_logic (a_tag, 'c');
      if      (strstr (s_curr, " do "       ) != NULL) poly_cats_logic (a_tag, 'c');
   }
   /*---(indent)-------------------------*/
   if (a_tag != NULL) {
      x_len = strlen (s_curr);
      for (i = 0; i < x_len; ++i) {
         if (s_curr [i] == ' ')   continue;
         if (i > a_tag->work->indent) a_tag->work->indent = i;
         break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_tags_readline      (tFILE *a_file, int *a_line, tTAG **a_tag)
{
   /*---(locals)-----------+-----------+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   int         x_len       =    0;          /* length of input record         */
   static tTAG  *a_ptag    = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->name);
   DEBUG_INPT   yLOG_point   ("a_tag"     , a_tag);
   --rce;  if (a_tag == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_point   ("*a_tag"    , *a_tag);
   /*---(update line)-----------------*/
   ++(*a_line);
   DEBUG_INPT   yLOG_value   ("line"      , *a_line);
   /*---(first tag)-------------------*/
   --rce;  if (*a_tag == NULL) {
      a_ptag = *a_tag;
      rc = poly_files_nexttag (a_file, a_tag);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("no tags in file");
         return 0;
      }
   }
   /*---(next tag)--------------------*/
   else if (*a_line > (*a_tag)->line) {
      a_ptag  = *a_tag;
      rc = poly_files_nexttag (a_file, a_tag);
   }
   DEBUG_INPT   yLOG_value   ("line"      , (*a_tag)->line);
   DEBUG_INPT   yLOG_info    ("name"      , (*a_tag)->name);
   /*---(after all tags)--------------*/
   if (*a_tag == a_ptag && a_ptag->work->end > 0) {
      poly_tags__linetype (a_file, *a_tag);
      DEBUG_INPT   yLOG_note    ("after last tag");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(found)-----------------------*/
   if (*a_line == (*a_tag)->line) {
      DEBUG_INPT   yLOG_note    ("TAG FOUND");
      poly_tags__scope (*a_tag, *a_line);
      /*---(oneliner)-----------------*/
      if ((*a_tag)->oneline == 'y') {
         DEBUG_DATA   yLOG_note    ("processing a one liner");
         (*a_tag)->work->beg  = a_line;
         poly_tags__linetype (a_file, *a_tag);
         (*a_tag)->work->end  = a_line;
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 1;
      }
      DEBUG_DATA   yLOG_note    ("processing a multi-line header");
      poly_tags__linetype (a_file, a_ptag);
      return 1;
   }
   /*---(process line)----------------*/
   poly_tags__linetype (a_file, a_ptag);
   /*---(before all tags)-------------*/
   if (a_ptag == NULL) {
      DEBUG_INPT   yLOG_note    ("before first tag");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(beginning)-------------------*/
   else if (a_ptag->work->beg <  0) {
      if (s_curr [0] == '{')  {
         DEBUG_INPT   yLOG_note    ("beg brace");
         a_ptag->work->beg = *a_line;
      }
   }
   /*---(ending)----------------------*/
   else if (a_ptag->work->end <  0) {
      if (s_curr [0] == '}') {
         DEBUG_INPT   yLOG_note    ("end brace");
         a_ptag->work->end = *a_line;
         --a_ptag->lines;
         --a_ptag->code;
         DEBUG_INPT   yLOG_note    ("function end");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         /*> poly_cats_tagsumm   (a_ptag);                                            <*/
         return 0;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_note    ("normal line");
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_tags_review        (tFILE *a_file)
{
   /*---(locals)-----------+-----------+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   char        x_recd      [LEN_RECD];      /* input record                   */
   int         x_len       =    0;          /* length of input record         */
   int         x_line      =    0;
   tTAG       *x_tag       = NULL;
   int         p           =   -1;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open file)----------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->name);
   f_prog = fopen (a_file->name, "r");
   DEBUG_INPT   yLOG_point   ("f_prog"         , f_prog);
   --rce;  if (f_prog == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   while (rc >= 0) {
      /*---(read)------------------------*/
      strlcpy (s_pprev, s_prev, LEN_RECD);
      strlcpy (s_prev , s_curr, LEN_RECD);
      fgets  (s_curr, LEN_RECD, f_prog);
      --rce;  if (feof (f_prog))  {
         DEBUG_INPT   yLOG_note    ("end of file");
         break;
      }
      x_len = strlen (s_curr);
      s_curr [--x_len] = '\0';
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      if (a_file->type == 'h') {
         DEBUG_INPT   yLOG_note    ("header file line");
         DEBUG_INPT   yLOG_info    ("s_curr"    , s_curr);
         if (strncmp (s_curr, " *   focus         : ", 21) == 0)  strlcpy (a_file->proj->focus   , s_curr + 21, LEN_FULL);
         if (strncmp (s_curr, " *   heritage      : ", 21) == 0)  strlcpy (a_file->proj->heritage, s_curr + 21, LEN_FULL);
         if (strncmp (s_curr, " *   purpose       : ", 21) == 0)  strlcpy (a_file->proj->purpose , s_curr + 21, LEN_FULL);
      }
      rc = poly_tags_readline (a_file, &x_line, &x_tag);
   }
   /*---(close)--------------------------*/
   rc = fclose (f_prog);
   f_prog = NULL;
   DEBUG_INPT   yLOG_point   ("fclose f"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_tags__unit      (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   tTAG       *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "TAGS unit        : tags number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "TAGS count       : %3d", poly_btree_count (B_TAGS));
      return unit_answer;
   }
   if (strncmp (unit_answer, "TAGS unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "TAGS unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "entry"     )     == 0) {
      u = (tFILE *) poly_btree_entry (B_TAGS, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         snprintf (unit_answer, LEN_RECD, "TAGS entry  (%2d) : %-22.22s %3d %3d %3d %3d %3d %3d %3d", i, t, u->line, u->lines, u->empty, u->docs, u->debug, u->code, u->slocl);
      } else {
         snprintf (unit_answer, LEN_RECD, "TAGS entry  (%2d) : %-22.22s %3d %3d %3d %3d %3d %3d %3d", i, t, -1, 0, 0, 0, 0, 0, 0);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




