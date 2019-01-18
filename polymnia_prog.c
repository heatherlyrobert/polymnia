/*============================----beg-of-source---============================*/
#include  "polymnia.h"


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
FILE       *f_prog      = NULL;
FILE       *f_tags      = NULL;
FILE       *f_flow      = NULL;
FILE       *f_extern    = NULL;
FILE       *f_mystry    = NULL;
FILE       *f_ylib      = NULL;

char       s_pprev      [LEN_RECD];
char       s_prev       [LEN_RECD];
char       s_curr       [LEN_RECD];


tFILE    s_files [MAX_FILE];

tTAG     s_tags [MAX_TAG];
int      s_ntag            =   0;

char      unit_answer [LEN_RECD] = "";

char         /*-> very first setup -------------------[ shoot  [gz.633.201.0A]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG_init          (int a_argc, char *a_argv[])
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
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
      /*> if      (strncmp (a, "-f"        ,10) == 0)  strlcpy (x_name , argv[++i], LEN_RECD);   <* 
       *> else if (strncmp (a, "-h"        ,10) == 0)  PROG_usage();                             <* 
       *> else if (strncmp (a, "--help"    ,10) == 0)  PROG_usage();                             <*/
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
   /*---(produce global files)-----------*/
   rc = poly_files_review ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS  yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_report             (char a_format)
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
   /*---(output)-------------------------*/
   DEBUG_PROG   yLOG_note    ("review all tags and code");
   x_file = (tFILE *) poly_btree_first (B_FILES);
   DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   while (x_file != NULL) {
      if (a_format == 'h') {
         /*> printf ("%-25.25s    FILE\n", x_file->name);                                                                                                 <* 
          *> printf ("lines : %4d %5d   \n", x_file->lines, s_lines);                                                                                     <* 
          *> printf ("empty : %4d %5d   \n", x_file->empty, s_empty);                                                                                     <* 
          *> printf ("docs  : %4d %5d   \n", x_file->docs , s_docs );                                                                                     <* 
          *> printf ("debug : %4d %5d   \n", x_file->debug, s_debug);                                                                                     <* 
          *> printf ("code  : %4d %5d   \n", x_file->code , s_code );                                                                                     <* 
          *> printf ("slocl : %4d %5d   \n", x_file->slocl, s_slocl);                                                                                     <* 
          *> printf ("\n");                                                                                                                               <* 
          *> printf ("functions (%2d)               [=complexity==] [=integration=] [=watch=point=]  [====source=file======]  [line]\n", x_file->ntag);   <*/
         sprintf (a, "lines : %4d %5d", x_file->lines, s_lines);
         sprintf (b, "empty : %4d %5d", x_file->empty, s_empty);
         sprintf (c, "docs  : %4d %5d", x_file->docs , s_docs );
         sprintf (d, "debug : %4d %5d", x_file->debug, s_debug);
         sprintf (e, "code  : %4d %5d", x_file->code , s_code );
         sprintf (f, "slocl : %4d %5d", x_file->slocl, s_slocl);
         sprintf (g, "functions (%2d)"  , x_file->ntag);
         printf ("%-25.25s    FILE\n", x_file->name);
         printf ("%-25.25s                     c                                                          \n", a);
         printf ("%-25.25s                   l h r i m          i     m        r   d d  e c o             \n", b);
         printf ("%-25.25s     s r p  l d s  o o e n e   g l  c n     y    w l e   s m  x u p             \n", c);
         printf ("%-25.25s     c c a  i e l  c i t d m   c c  a t c y s  r r i c   t a  t r e             \n", d);
         printf ("%-25.25s     o o r  n b o  a c u e o   a a  l e s l t  e i n u   y c  e s n             \n", e);
         printf ("%-25.25s     p d a  e u c  l e r n r   l l  l r t i r  a t u r   l r  r e g             \n", f);
         printf ("%-25.25s     e e m  s g l  s s n t y   l l  s n d b y  d e x s   e o  n s l -  - - - - -    ------------------staging area-----------------\n", "");
         printf ("%-25.25s    [------complexity-------] [------integration------] [----watch-points-------]   [-complexity--] [-integration-] [-watch-point-]  [----source-file-------] [line]    [-type-] [rdy] [-----------description-------------]\n", g);
      }
      x_tag = NULL;
      rc = poly_files_nexttag (x_file, &x_tag);
      while (rc >= 0)  {
         poly_cats_tagsumm (x_tag);
         printf ("%-2s  %-23.23s   ", x_tag->hint  , x_tag->name);
         if (strncmp (x_tag->name, "o___", 4) != 0) {
            printf ("%c %c %c  %c %c %c  %c %c %c %c %c   %c %c  %c %c %c %c %c  %c %c %c %c   %c %c  %c %c %c %c  %c %c %c %c %c    ",
                  x_tag->scope , x_tag->rtype , x_tag->psize ,
                  x_tag->tsize , x_tag->dsize , x_tag->ssize ,
                  x_tag->lsize , x_tag->csize , x_tag->rsize , x_tag->isize , x_tag->msize ,
                  x_tag->Gsize , x_tag->Lsize ,
                  x_tag->Fsize , x_tag->Isize , x_tag->Csize , x_tag->Ysize , x_tag->Msize ,
                  x_tag->Rflag , x_tag->Wflag , x_tag->Lflag , x_tag->Sflag ,
                  x_tag->Dstyle, x_tag->Dmacro,
                  x_tag->Esize , x_tag->Nsize , x_tag->Osize , '-',
                  '-', '-', '-', '-', '-');
            printf ("[%c%c%c.%c%c%c.%c%c%c%c%c] [%c%c.%c%c%c%c%c.%c%c%c%c] [%c%c.%c%c%c%c.%c%c%c%c%c]   ",
                  x_tag->scope , x_tag->rtype , x_tag->psize ,
                  x_tag->tsize , x_tag->dsize , x_tag->ssize ,
                  x_tag->lsize , x_tag->csize , x_tag->rsize , x_tag->isize , x_tag->msize ,
                  x_tag->Gsize , x_tag->Lsize ,
                  x_tag->Fsize , x_tag->Isize , x_tag->Csize , x_tag->Ysize , x_tag->Msize ,
                  x_tag->Rflag , x_tag->Wflag , x_tag->Lflag , x_tag->Sflag ,
                  x_tag->Dstyle, x_tag->Dmacro,
                  x_tag->Esize , x_tag->Nsize , x_tag->Osize , '-',
                  '-', '-', '-', '-', '-');
         } else {
            printf ("%c %c %c  %-68.68s    ", x_tag->scope , x_tag->rtype , x_tag->psize , "");
            printf ("%-47.47s   ", "");
         }
         printf ("%-23.23s  %-4d      ", x_tag->file->name, x_tag->line);
         printf ("%-6.6s    %c    %-35.35s", x_tag->image, x_tag->ready, x_tag->desc);
         printf ("\n");
         rc = poly_files_nexttag (x_file, &x_tag);
      }
      if (a_format == 'h')  for (i = 0; i < 70 - x_file->ntag; ++i)  printf ("\n");
      x_file = (tFILE *) poly_btree_next  (B_FILES);
      DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   }
   /*---(prepare for use)----------------*/
   DEBUG_PROG   yLOG_note    ("prepare tags for use");
   return 0;
}

char         /*-> shutdown program and free memory ---[ ------ [gz.422.001.03]*/ /*-[00.0000.111.!]-*/ /*-[--.---.---.--]-*/
PROG_end             (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(wrap-up)------------------------*/
   poly_files_wrap   ();
   poly_tags_wrap    ();
   poly_extern_wrap  ();
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


