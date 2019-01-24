/*============================----beg-of-source---============================*/
#include  "polymnia.h"



char        g_mode      = '-';


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
FILE       *f_db        = NULL;
FILE       *f_prog      = NULL;
FILE       *f_tags      = NULL;
FILE       *f_flow      = NULL;
FILE       *f_extern    = NULL;
FILE       *f_mystry    = NULL;
FILE       *f_ylib      = NULL;

char       s_pprev      [LEN_RECD];
char       s_prev       [LEN_RECD];
char       s_curr       [LEN_RECD];




char      unit_answer [LEN_RECD] = "";

char         /*-> very first setup -------------------[ shoot  [gz.633.201.0A]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG_init          (int a_argc, char *a_argv[])
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   poly_proj_init    ();
   poly_files_init   ();
   poly_tags_init    ();
   poly_extern_init  ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> process the command line args ------[ ------ [gz.952.251.B4]*/ /*-[01.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG_args          (int argc, char *argv[])
{
   /*---(locals)-------------------------*/
   int         i           = 0;
   char       *a           = NULL;
   int         x_total     = 0;
   int         x_args      = 0;
   char        x_name      [LEN_STR]   = "";
   char        t           [LEN_STR]   = "";
   /*---(header)-------------------------*/
   DEBUG_TOPS  yLOG_enter   (__FUNCTION__);
   /*> FILE_rename ("");                                                              <*/
   /*---(process)------------------------*/
   for (i = 1; i < argc; ++i) {
      a = argv[i];
      ++x_total;
      if (a[0] == '@')  continue;
      DEBUG_ARGS  yLOG_info    ("cli arg", a);
      ++x_args;
      /*---(simple)----------------------*/
      if      (strcmp (a, "--search" ) == 0)  g_mode = MODE_SEARCH;
      else if (strcmp (a, "--htags"  ) == 0)  g_mode = MODE_HTAGS;
      else if (strcmp (a, "--dump"   ) == 0)  g_mode = MODE_DUMP;
      else if (strcmp (a, "--write"  ) == 0)  g_mode = MODE_WRITE;
      else if (strcmp (a, "--update" ) == 0)  g_mode = MODE_UPDATE;
      else if (strcmp (a, "--projs"  ) == 0)  g_mode = MODE_PROJ;
      else if (strcmp (a, "--files"  ) == 0)  g_mode = MODE_FILE;
      else if (strcmp (a, "--system" ) == 0)  g_mode = MODE_SYSTEM;
      /*---(compound)--------------------*/
      else if (strcmp (a, "--remove" ) == 0) {
         g_mode = MODE_REMOVE;
         if (++i < argc)  strlcpy (s_name, argv[i], LEN_NAME);
         else {
            DEBUG_TOPS  yLOG_note  ("project name not included");
            DEBUG_TOPS  yLOG_exitr (__FUNCTION__, -1);
            return -1;
         }
      }
      /*---(prefixes)--------------------*/
      /*> else if (strncmp (a, "--formula-"          , 10) == 0)  PROG_layout_set ("cli", "formula"  , a + 10);   <* 
       *> else if (strncmp (a, "--status-"           ,  9) == 0)  PROG_layout_set ("cli", "status"   , a +  9);   <* 
       *> else if (strncmp (a, "--command-"          , 10) == 0)  PROG_layout_set ("cli", "command"  , a + 10);   <* 
       *> else if (strncmp (a, "--layout-"           ,  9) == 0)  PROG_layout_set ("cli", "layout"   , a +  9);   <* 
       *> else if (strncmp (a, "--function-list"     ,  9) == 0)  CALC_func_list  ();                             <*/
      /*---(other)-----------------------*/
      /*> else if (a[0] != '-'                     )   strlcpy (x_name , argv[i]  , LEN_RECD);   <*/
   }
   DEBUG_ARGS  yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS  yLOG_value  ("arguments" , x_args);
   if (x_args == 0) {
      DEBUG_ARGS  yLOG_note   ("no arguments identified");
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS  yLOG_exit  (__FUNCTION__);
   return 0;
}

char         /*-> initialize program and variables ---[ ------ [gz.741.041.07]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG_begin         (void)
{
   /*---(header)-------------------------*/
   DEBUG_TOPS  yLOG_enter   (__FUNCTION__);
   /*---(prepare files)------------------*/
   char        rc          =    0;
   rc = poly_extern_load ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS  yLOG_exit  (__FUNCTION__);
   return rc;
}

char         /*-> initialize program and variables ---[ ------ [gz.741.041.07]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG_final         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS  yLOG_enter   (__FUNCTION__);
   /*---(complete)-----------------------*/
   DEBUG_TOPS  yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_prepare            (void)
{
   s_files = s_funcs = s_lines = s_empty = s_docs  = s_debug = s_code  = s_slocl = 0;
   return 0;
}

char
PROG_summarize          (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   tTAG       *x_tag       = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_point   ("a_proj"    , a_proj);
   DEBUG_PROG   yLOG_info    ("->name"    , a_proj->name);
   /*---(prepare)------------------------*/
   if      (s_slocl < 100    )  strlcpy (a_proj->codesize, "u.micro"       , LEN_LABEL);
   else if (s_slocl < 500    )  strlcpy (a_proj->codesize, "t.tiny"        , LEN_LABEL);
   else if (s_slocl < 2000   )  strlcpy (a_proj->codesize, "s.small"       , LEN_LABEL);
   else if (s_slocl < 10000  )  strlcpy (a_proj->codesize, "m.moderate"    , LEN_LABEL);
   else if (s_slocl < 50000  )  strlcpy (a_proj->codesize, "l.large"       , LEN_LABEL);
   else if (s_slocl < 250000 )  strlcpy (a_proj->codesize, "h.huge"        , LEN_LABEL);
   else if (s_slocl < 1000000)  strlcpy (a_proj->codesize, "e.elephantine" , LEN_LABEL);
   else                         strlcpy (a_proj->codesize, "g.gargantuan"  , LEN_LABEL);
   /*---(output)-------------------------*/
   DEBUG_PROG   yLOG_note    ("review all tags and code");
   a_proj->ntags = 0;
   x_file = a_proj->head;
   while (x_file != NULL) {
      x_tag = x_file->head;
      while (x_tag != NULL)  {
         poly_cats_tagsumm (x_tag);
         x_tag = x_tag->next;
      }
      a_proj->ntags += x_file->count;
      x_file = x_file->next;
   }
   /*---(prepare for use)----------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_report             (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   tTAG       *x_tag       = NULL;
   int         i           =    0;
   char        a           [LEN_LABEL];
   char        b           [LEN_LABEL];
   char        c           [LEN_LABEL];
   char        d           [LEN_LABEL];
   char        e           [LEN_LABEL];
   char        f           [LEN_LABEL];
   char        g           [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      a_proj = (tPROJ *) poly_btree_first (B_PROJ);
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
   if (g_mode == MODE_HTAGS) {
      printf ("##/usr/local/bin/polymnia --htags\n");
      printf ("##   polymnia-hymnos (many praises) greek muse and protector of divine hymns, dancing, geometry, and grammar\n");
      printf ("##   version %s, %s\n", VER_NUM, VER_TXT);
      printf ("##\n");
      printf ("##   name       [%s]\n", a_proj->name);
      printf ("##   focus      [%s]\n", a_proj->focus);
      printf ("##   niche      [%s]\n", a_proj->niche);
      printf ("##   heritage   [%s]\n", a_proj->heritage);
      printf ("##   purpose    [%s]\n", a_proj->purpose);
      printf ("##   created    [%s]\n", a_proj->created);
      printf ("##   code-size  [%s]\n", a_proj->codesize);
      printf ("##   home       [%s]\n", a_proj->home);
      printf ("##   vernum     [%s]\n", a_proj->vernum);
      printf ("##   vertxt     [%s]\n", a_proj->vertxt);
      printf ("##\n\n\n\n");
   }
   while (x_file != NULL) {
      DEBUG_PROG   yLOG_info    ("file name" , x_file->name);
      if (g_mode == MODE_HTAGS) {
         sprintf (a, "lines : %4d  %5d", x_file->lines, s_lines);
         sprintf (b, "empty : %4d  %5d", x_file->empty, s_empty);
         sprintf (c, "docs  : %4d  %5d", x_file->docs , s_docs );
         sprintf (d, "debug : %4d  %5d", x_file->debug, s_debug);
         sprintf (e, "code  : %4d  %5d", x_file->code , s_code );
         sprintf (f, "slocl : %4d  %5d", x_file->slocl, s_slocl);
         sprintf (g, "function (%d)"   , x_file->count);
         printf ("%-29.29s   FILE\n", x_file->name);
         printf ("%-29.29s   o                   c                                                          \n", a);
         printf ("%-29.29s   n                 l h r i m          i     m        r   d d  c o w      e      \n", b);
         printf ("%-29.29s   e   s r p  l d s  o o e n e   g l  c n     y    w l e   s m  u p i    p x      \n", c);
         printf ("%-29.29s   l   c c a  i e l  c i t d m   c c  a t c y s  r r i c   t a  r e n    r t      \n", d);
         printf ("%-29.29s   i   o o r  n b o  a c u e o   a a  l e s l t  e i n u   y c  s n d m  o e      \n", e);
         printf ("%-29.29s   n   p d a  e u c  l e r n r   l l  l r t i r  a t u r   l r  e g o y  t r      \n", f);
         printf ("%-29.29s   e   e e m  s g l  s s n t y   l l  s n d b y  d e x s   e o  s l w x  o n - - -   ------------------staging area-----------------  -------------location---------------    ------------------extended-data---------------------\n", "");
         printf ("%-29.29s      [------complexity-------] [------integration------] [----watch-points-------]  [-complexity--] [-integration-] [-watch-point-]  [----source-file----------]   [line]    [-type-] [rdy] [-----------description-------------]\n", g);
      }
      x_tag = NULL;
      rc = poly_files_nexttag (x_file, &x_tag);
      DEBUG_PROG   yLOG_value   ("nexttag"   , rc);
      DEBUG_PROG   yLOG_point   ("x_tag"     , x_tag);
      while (rc >= 0)  {
         DEBUG_PROG   yLOG_info    ("tag name"  , x_tag->name);
         printf ("%-2s  %-25.25s   %c   ", x_tag->hint  , x_tag->name, x_tag->oneline);
         if (strncmp (x_tag->name, "o___", 4) != 0) {
            printf ("%c %c %c  %c %c %c  %c %c %c %c %c   %c %c  %c %c %c %c %c  %c %c %c %c   %c %c  %c %c %c %c  %c %c %c %c %c   ",
                  x_tag->scope , x_tag->rtype , x_tag->psize ,
                  x_tag->tsize , x_tag->dsize , x_tag->ssize ,
                  x_tag->lsize , x_tag->csize , x_tag->rsize , x_tag->isize , x_tag->msize ,
                  x_tag->Gsize , x_tag->Lsize ,
                  x_tag->Fsize , x_tag->Isize , x_tag->Csize , x_tag->Ysize , x_tag->Msize ,
                  x_tag->Rflag , x_tag->Wflag , x_tag->Lflag , x_tag->Sflag ,
                  x_tag->Dstyle, x_tag->Dmacro,
                  x_tag->Nsize , x_tag->Osize , x_tag->Wsize , x_tag->Zsize ,
                  x_tag->Pstyle, x_tag->Esize , x_tag->Xsize , '-', '-');
            printf ("[%c%c%c.%c%c%c.%c%c%c%c%c] [%c%c.%c%c%c%c%c.%c%c%c%c] [%c%c.%c%c%c%c.%c%c%c%c%c]   ",
                  x_tag->scope , x_tag->rtype , x_tag->psize ,
                  x_tag->tsize , x_tag->dsize , x_tag->ssize ,
                  x_tag->lsize , x_tag->csize , x_tag->rsize , x_tag->isize , x_tag->msize ,
                  x_tag->Gsize , x_tag->Lsize ,
                  x_tag->Fsize , x_tag->Isize , x_tag->Csize , x_tag->Ysize , x_tag->Msize ,
                  x_tag->Rflag , x_tag->Wflag , x_tag->Lflag , x_tag->Sflag ,
                  x_tag->Dstyle, x_tag->Dmacro,
                  x_tag->Nsize , x_tag->Osize , x_tag->Wsize , x_tag->Zsize ,
                  x_tag->Pstyle, x_tag->Esize , x_tag->Xsize , '-', '-');
         } else {
            printf ("%c %c %c  %-68.68s   ", x_tag->scope , x_tag->rtype , x_tag->psize , "");
            printf ("%-47.47s   ", "");
         }
         printf ("%-25.25s     %-4d      ", x_tag->file->name, x_tag->line);
         printf ("%-6.6s    %c    %-35.35s", x_tag->image, x_tag->ready, x_tag->desc);
         printf ("\n");
         rc = poly_files_nexttag (x_file, &x_tag);
         DEBUG_PROG   yLOG_value   ("nexttag"   , rc);
         DEBUG_PROG   yLOG_point   ("x_tag"     , x_tag);
      }
      if (g_mode == MODE_HTAGS)  for (i = 0; i < 70 - x_file->count; ++i)  printf ("\n");
      x_file = x_file->next;
      DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> shutdown program and free memory ---[ ------ [gz.422.001.03]*/ /*-[00.0000.111.!]-*/ /*-[--.---.---.--]-*/
PROG_end             (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(wrap-up)------------------------*/
   poly_extern_wrap  ();
   poly_tags_wrap    ();
   poly_files_wrap   ();
   poly_proj_wrap    ();
   /*---(remove global files)------------*/
   system ("rm -f htags.gcalls");
   system ("rm -f htags.flow");
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS   yLOG_end     ();
   return 0;
}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.#]-*/ /*-[--.---.---.--]-*/
PROG__unit_quiet   (void)
{
   char       *x_args [1]  = { "polymnia" };
   yURG_logger (1, x_args);
   PROG_init   (1, x_args);
   yURG_urgs   (1, x_args);
   PROG_args   (1, x_args);
   PROG_begin  ();
   return 0;
}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
PROG__unit_loud      (void)
{
   char       *x_args [2]  = { "polymnia_unit", "@@kitchen" };
   yURG_logger (2, x_args);
   PROG_init   (2, x_args);
   yURG_urgs   (2, x_args);
   PROG_args   (2, x_args);
   PROG_begin  ();
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
PROG__unit_end       (void)
{
   PROG_end       ();
   return 0;
}


