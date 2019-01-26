/*============================----beg-of-source---============================*/
#include  "polymnia.h"

static    char     s_prefix     [LEN_LABEL];

char
poly_rptg__debug        (tTAG *a_tag)
{
   if (strchr ("Bb", a_tag->Dstyle) != NULL) {
      strlcpy (s_prefix, "style"     , LEN_LABEL);
      return 1;
   }
   if (a_tag->Dstyle == '#') {
      strlcpy (s_prefix, "boom"      , LEN_LABEL);
      return 1;
   }
   if (a_tag->Dmacro == '#' && strchr ("LSf", a_tag->Dstyle) == NULL) {
      strlcpy (s_prefix, "macro"     , LEN_LABEL);
      return 1;
   }
   if (strchr ("!#EX", a_tag->Dmatch) != NULL) {
      strlcpy (s_prefix, "match"     , LEN_LABEL);
      return 1;
   }
   if (a_tag->Dstyle == '-' && strchr ("ABCDEFGHIJKLMNOPQRSTUVWXYZ#", a_tag->tsize) != NULL) {
      strlcpy (s_prefix, "size"      , LEN_LABEL);
      return 1;
   }
   return 0;
}

char
poly_rptg__stats        (tTAG *a_tag)
{
   printf ("%c   ", a_tag->oneline);
   if (strncmp (a_tag->name, "o___", 4) != 0) {
      printf ("%c %c %c  %c %c %c  %c %c %c %c %c   %c %c  %c %c %c %c %c  %c %c %c %c   %c %c %c  %c %c %c %c  %c %c %c %c   ",
            a_tag->scope , a_tag->rtype , a_tag->psize ,
            a_tag->tsize , a_tag->dsize , a_tag->ssize ,
            a_tag->lsize , a_tag->csize , a_tag->rsize , a_tag->isize , a_tag->msize ,
            a_tag->Gsize , a_tag->Lsize ,
            a_tag->Fsize , a_tag->Isize , a_tag->Csize , a_tag->Ysize , a_tag->Msize ,
            a_tag->Rflag , a_tag->Wflag , a_tag->Lflag , a_tag->Sflag ,
            a_tag->Dstyle, a_tag->Dmacro, a_tag->Dmatch,
            a_tag->Nsize , a_tag->Osize , a_tag->Wsize , a_tag->Zsize ,
            a_tag->Pstyle, a_tag->Esize , a_tag->Xsize , '-');
      printf ("[%c%c%c.%c%c%c.%c%c%c%c%c] [%c%c.%c%c%c%c%c.%c%c%c%c] [%c%c%c.%c%c%c%c.%c%c%c%c]   ",
            a_tag->scope , a_tag->rtype , a_tag->psize ,
            a_tag->tsize , a_tag->dsize , a_tag->ssize ,
            a_tag->lsize , a_tag->csize , a_tag->rsize , a_tag->isize , a_tag->msize ,
            a_tag->Gsize , a_tag->Lsize ,
            a_tag->Fsize , a_tag->Isize , a_tag->Csize , a_tag->Ysize , a_tag->Msize ,
            a_tag->Rflag , a_tag->Wflag , a_tag->Lflag , a_tag->Sflag ,
            a_tag->Dstyle, a_tag->Dmacro, a_tag->Dmatch,
            a_tag->Nsize , a_tag->Osize , a_tag->Wsize , a_tag->Zsize ,
            a_tag->Pstyle, a_tag->Esize , a_tag->Xsize , '-');
   } else {
      printf ("%c %c %c  %-68.68s   ", a_tag->scope , a_tag->rtype , a_tag->psize , "");
      printf ("%-47.47s   ", "");
   }
   return 0;
}

char
poly_rptg__dump_line    (tTAG *a_tag)
{
   /*---(project)------------------------*/
   printf ("%-25.25s   ", a_tag->file->proj->name);
   /*---(file)---------------------------*/
   printf ("%-25.25s   ", a_tag->file->name);
   /*---(tag)----------------------------*/
   printf ("%4d   %-25.25s   ", a_tag->line, a_tag->name);
   /*---(statistics)---------------------*/
   poly_rptg__stats  (a_tag);
   /*---(suffix)-------------------------*/
   printf ("%-8.8s   %c   %-35.35s\n"  , a_tag->image, a_tag->ready, a_tag->desc);
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_rptg_file          (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(files)--------------------------*/
   x_file = a_proj->head;
   DEBUG_RPTG   yLOG_point   ("file"      , x_file);
   while (x_file != NULL) {
      DEBUG_RPTG   yLOG_info    ("->name"    , x_file->name);
      DEBUG_RPTG   yLOG_value   ("tags"      , x_file->count);
      if (my.g_mode != MODE_DUMP) {
         printf ("  %-23.23s       %7d %7d %7d %7d %7d %7d %7d\n",
               x_file->name , x_file->count,
               x_file->lines, x_file->empty,
               x_file->docs , x_file->debug,
               x_file->code , x_file->slocl);
      }
      switch (my.g_mode) {
      case MODE_PROJ :
      case MODE_FILE :
         break;
      case MODE_TAGS :
         break;
      }
      x_file = x_file->next;
      DEBUG_RPTG   yLOG_point   ("file"      , x_file);
   }
}

char
poly_rptg_projfilter    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(find target)--------------------*/
   DEBUG_PROG   yLOG_info    ("g_project"  , my.g_project);
   if (my.g_project [0] == '\0') {
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   my.g_proj = poly_proj_search (my.g_project);
   DEBUG_PROG   yLOG_point   ("g_proj"     , my.g_proj);
   --rce;  if (my.g_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("->name"     , my.g_proj->name);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}


char
poly_rptg_proj          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   my.s_files = my.s_funcs = my.s_lines = my.s_empty = my.s_docs  = my.s_debug = my.s_code  = my.s_slocl = 0;
   if (my.g_mode != MODE_DUMP) {
      if (my.g_titles == RPTG_TITLES)  printf ("---name------------------  file --ntags --lines --empty ---docs --debug ---code --slocl  ---code-size---  ---greek-heritage-------------------------------------------  ---purpose-statement----------------------------------------  -ver- ---version-description--------------------------------------  ---focus------------  ---niche------------  --created-  ---home-directory-------------------------------------------\n\n");
   }
   /*---(find target)--------------------*/
   rc = poly_rptg_projfilter ();
   DEBUG_PROG   yLOG_point   ("filter"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(projects)-----------------------*/
   DEBUG_RPTG   yLOG_value   ("projects"  , poly_btree_count (B_PROJ));
   x_proj = (tPROJ *) poly_btree_first (B_PROJ);
   DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
   while (x_proj != NULL) {
      /*---(prepare)---------------------*/
      DEBUG_RPTG   yLOG_info    ("->name"    , x_proj->name);
      DEBUG_RPTG   yLOG_value   ("files"     , x_proj->count);
      /*---(grand totals)----------------*/
      my.s_files += x_proj->count;
      my.s_funcs += x_proj->ntags;
      my.s_lines += x_proj->lines;
      my.s_empty += x_proj->empty;
      my.s_docs  += x_proj->docs;
      my.s_debug += x_proj->debug;
      my.s_code  += x_proj->code;
      my.s_slocl += x_proj->slocl;
      /*---(project filtering)-----------*/
      if (my.g_proj != NULL && x_proj != my.g_proj) {
         x_proj = (tPROJ *) poly_btree_next  (B_PROJ);
         DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
         continue;
      }
      /*---(reporting)-------------------*/
      if (my.g_mode != MODE_DUMP) {
         printf ("%-25.25s  %4d %7d %7d %7d %7d %7d %7d %7d  %-15.15s  ",
               x_proj->name , x_proj->count, x_proj->ntags,
               x_proj->lines, x_proj->empty,
               x_proj->docs , x_proj->debug,
               x_proj->code , x_proj->slocl,
               x_proj->codesize);
         printf ("%-60.60s  %-60.60s  %-5.5s %-60.65s  %-20.20s  %-20.20s  %-10.10s  %-60.60s\n",
               x_proj->heritage, x_proj->purpose,
               x_proj->vernum  , x_proj->vertxt,
               x_proj->focus   , x_proj->niche,
               x_proj->created , x_proj->home);
      }
      /*---(diving)----------------------*/
      switch (my.g_mode) {
      case MODE_PROJ :
         break;
      case MODE_FILE : case MODE_TAGS : case MODE_DUMP :
         rc = poly_rptg_file (x_proj);
         printf ("\n");
         break;
      }
      /*---(next)------------------------*/
      x_proj = (tPROJ *) poly_btree_next  (B_PROJ);
      DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
      /*---(done)------------------------*/
   }
   printf ("%25.25s  %4d %7d %7d %7d %7d %7d %7d %7d\n", "GRAND TOTALS",
         my.s_files, my.s_funcs, my.s_lines, my.s_empty, my.s_docs, my.s_debug, my.s_code, my.s_slocl);
   /*---(complete)-----------------------*/
   DEBUG_RPTG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_rptg_dump          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   tFILE      *x_file      = NULL;
   tTAG       *x_tag       = NULL;
   char        x_show      =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_RPTG   yLOG_note    ("review all tags and code");
   DEBUG_RPTG   yLOG_value   ("projects"  , poly_btree_count (B_PROJ));
   /*---(find target)--------------------*/
   rc = poly_rptg_projfilter ();
   DEBUG_PROG   yLOG_point   ("filter"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(projects)-----------------------*/
   x_proj = (tPROJ *) poly_btree_first (B_PROJ);
   DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
   while (x_proj != NULL) {
      /*---(prepare)---------------------*/
      DEBUG_RPTG   yLOG_info    ("->name"    , x_proj->name);
      DEBUG_RPTG   yLOG_value   ("files"     , x_proj->count);
      /*---(project filtering)-----------*/
      if (my.g_proj != NULL && x_proj != my.g_proj) {
         x_proj = (tPROJ *) poly_btree_next  (B_PROJ);
         DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
         continue;
      }
      /*---(files)-----------------------*/
      x_file = x_proj->head;
      DEBUG_RPTG   yLOG_point   ("file"      , x_file);
      while (x_file != NULL) {
         /*---(prepare)------------------*/
         DEBUG_RPTG   yLOG_info    ("->name"    , x_file->name);
         DEBUG_RPTG   yLOG_value   ("tags"      , x_file->count);
         /*---(tags)---------------------*/
         x_tag  = x_file->head;
         DEBUG_RPTG   yLOG_point   ("tag"       , x_tag);
         while (x_tag  != NULL) {
            DEBUG_RPTG   yLOG_info    ("->name"    , x_tag->name);
            switch (my.g_filter) {
            case FILTER_DEBUG : x_show = poly_rptg__debug (x_tag);  break;
            default           : x_show = 1;
            }
            if (x_show == 1)  {
               if (my.g_titles == RPTG_TITLES && c % 25 == 0)  printf ("\n##-reason-  -----project-------------   ---file------------------   line   ---function/tag----------   -  [------complexity-------] [------integration------] [----watch-points-------]  [-complexity--] [-integration-] [-watch-point-]  [----source-file----------]   [line]    [-type-] [rdy] [-----------description-------------]\n");
               if (my.g_titles == RPTG_TITLES && c %  5 == 0)  printf ("\n");
               printf ("%-12.12s", s_prefix);
               rc = poly_rptg__dump_line (x_tag);
               ++c;
            }
            x_tag  = x_tag->next;
            DEBUG_RPTG   yLOG_point   ("tag"       , x_tag);
         }
         x_file = x_file->next;
         DEBUG_RPTG   yLOG_point   ("file"      , x_file);
      }
      x_proj = (tPROJ *) poly_btree_next  (B_PROJ);
      DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
   }
   if (my.g_titles == RPTG_TITLES)  printf ("\n## %d total lines\n", c);
   /*---(complete)-----------------------*/
   DEBUG_RPTG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_rptg_extern        (tEXTERN *a_extern)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   tYLIB      *x_ylib      = NULL;
   tPROJ      *x_proj      = NULL;
   tFILE      *x_file      = NULL;
   tTAG       *x_tag       = NULL;
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(find target)--------------------*/
   rc = poly_rptg_projfilter ();
   DEBUG_PROG   yLOG_point   ("filter"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(projects)-----------------------*/
   if (my.g_titles == RPTG_TITLES) {
      printf ("## yLIB (external) usage report for %s\n", a_extern->name);
      printf ("##    generated by polymnia --extern %s --titles\n", a_extern->name);
   }
   if (my.g_titles == RPTG_TREEVIEW) {
      printf ("## yLIB (external) treeview report for %s\n", a_extern->name);
      printf ("##    generated by polymnia --extern %s --treeview\n", a_extern->name);
   }
   DEBUG_RPTG   yLOG_point   ("a_extern"  , a_extern);
   DEBUG_RPTG   yLOG_info    ("->name"    , a_extern->name);
   x_ylib = a_extern->head;
   DEBUG_RPTG   yLOG_point   ("x_ylib"    , x_ylib);
   while (x_ylib != NULL) {
      /*---(project filtering)-----------*/
      if (my.g_proj != NULL && x_ylib->tag->file->proj != my.g_proj) {
         x_ylib = x_ylib->enext;
         DEBUG_RPTG   yLOG_point   ("x_ylib"    , x_ylib);
         continue;
      }
      /*---(headers)---------------------*/
      if (my.g_titles == RPTG_TITLES && c % 25 == 0)  printf ("\n##---project-------------  ---source-file-----------  line  ---source-function-------\n");
      if (my.g_titles == RPTG_TITLES && c %  5 == 0)  printf ("\n");
      DEBUG_RPTG   yLOG_info    ("->name"    , x_ylib->name);
      /*---(tree view)-------------------*/
      if (my.g_titles == RPTG_TREEVIEW) {
         if (x_ylib->tag->file->proj != x_proj) {
            x_file = NULL;
            printf ("\n");
            printf ("%-25.25s\n", x_ylib->tag->file->proj->name);
         }
         if (x_ylib->tag->file != x_file) {
            x_tag  = NULL;
            if (x_file != NULL)  printf ("\n");
            printf ("   %-25.25s\n", x_ylib->tag->file->name);
         } 
         if (x_ylib->tag != x_tag) {
            if (x_tag != NULL)  printf ("\n");
            printf ("      %-25.25s", x_ylib->tag->name);
         } 
         printf ("%4d,", x_ylib->line);
         x_proj = x_ylib->tag->file->proj;
         x_file = x_ylib->tag->file;
         x_tag  = x_ylib->tag;
      }
      /*---(normal view)-----------------*/
      else {
         printf ("%-25.25s  %-25.25s  %4d  %-25.25s\n", x_ylib->tag->file->proj->name, x_ylib->tag->file->name, x_ylib->line, x_ylib->tag->name);
      }
      /*---(next)------------------------*/
      ++c;
      x_ylib = x_ylib->enext;
      DEBUG_RPTG   yLOG_point   ("x_ylib"    , x_ylib);
      /*---(done)------------------------*/
   }
   if (my.g_titles == RPTG_TITLES)  printf ("\n## %d total references, %d shown\n", a_extern->count, c);
   /*---(complete)-----------------------*/
   DEBUG_RPTG   yLOG_exit    (__FUNCTION__);
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
   if (my.g_mode == MODE_HTAGS) {
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
      if (my.g_mode == MODE_HTAGS) {
         sprintf (a, "lines : %4d  %5d", x_file->lines, my.s_lines);
         sprintf (b, "empty : %4d  %5d", x_file->empty, my.s_empty);
         sprintf (c, "docs  : %4d  %5d", x_file->docs , my.s_docs );
         sprintf (d, "debug : %4d  %5d", x_file->debug, my.s_debug);
         sprintf (e, "code  : %4d  %5d", x_file->code , my.s_code );
         sprintf (f, "slocl : %4d  %5d", x_file->slocl, my.s_slocl);
         sprintf (g, "function (%d)"   , x_file->count);
         printf ("%-29.29s   FILE\n", x_file->name);
         printf ("%-29.29s   o                   c                                                          \n", a);
         printf ("%-29.29s   n                 l h r i m          i     m        r   d d d  c o w      e    \n", b);
         printf ("%-29.29s   e   s r p  l d s  o o e n e   g l  c n     y    w l e   s m m  u p i    p x    \n", c);
         printf ("%-29.29s   l   c c a  i e l  c i t d m   c c  a t c y s  r r i c   t a a  r e n    r t    \n", d);
         printf ("%-29.29s   i   o o r  n b o  a c u e o   a a  l e s l t  e i n u   y c t  s n d m  o e    \n", e);
         printf ("%-29.29s   n   p d a  e u c  l e r n r   l l  l r t i r  a t u r   l r c  e g o y  t r    \n", f);
         printf ("%-29.29s   e   e e m  s g l  s s n t y   l l  s n d b y  d e x s   e o h  s l w x  o n - -   ------------------staging area-----------------  -------------location---------------    ------------------extended-data---------------------\n", "");
         printf ("%-29.29s      [------complexity-------] [------integration------] [----watch-points-------]  [-complexity--] [-integration-] [-watch-point-]  [----source-file----------]   [line]    [-type-] [rdy] [-----------description-------------]\n", g);
      }
      x_tag = NULL;
      rc = poly_files_nexttag (x_file, &x_tag);
      DEBUG_PROG   yLOG_value   ("nexttag"   , rc);
      DEBUG_PROG   yLOG_point   ("x_tag"     , x_tag);
      while (rc >= 0)  {
         DEBUG_PROG   yLOG_info    ("tag name"  , x_tag->name);
         printf ("%-2s  %-25.25s   ", x_tag->hint  , x_tag->name);
         poly_rptg__stats (x_tag);
         /*> if (strncmp (x_tag->name, "o___", 4) != 0) {                                                                                    <* 
          *>    printf ("%c %c %c  %c %c %c  %c %c %c %c %c   %c %c  %c %c %c %c %c  %c %c %c %c   %c %c %c  %c %c %c %c  %c %c %c %c   ",   <* 
          *>          x_tag->scope , x_tag->rtype , x_tag->psize ,                                                                           <* 
          *>          x_tag->tsize , x_tag->dsize , x_tag->ssize ,                                                                           <* 
          *>          x_tag->lsize , x_tag->csize , x_tag->rsize , x_tag->isize , x_tag->msize ,                                             <* 
          *>          x_tag->Gsize , x_tag->Lsize ,                                                                                          <* 
          *>          x_tag->Fsize , x_tag->Isize , x_tag->Csize , x_tag->Ysize , x_tag->Msize ,                                             <* 
          *>          x_tag->Rflag , x_tag->Wflag , x_tag->Lflag , x_tag->Sflag ,                                                            <* 
          *>          x_tag->Dstyle, x_tag->Dmacro, x_tag->Dmatch,                                                                           <* 
          *>          x_tag->Nsize , x_tag->Osize , x_tag->Wsize , x_tag->Zsize ,                                                            <* 
          *>          x_tag->Pstyle, x_tag->Esize , x_tag->Xsize , '-', '-');                                                                <* 
          *>    printf ("[%c%c%c.%c%c%c.%c%c%c%c%c] [%c%c.%c%c%c%c%c.%c%c%c%c] [%c%c%c.%c%c%c%c.%c%c%c%c]   ",                               <* 
          *>          x_tag->scope , x_tag->rtype , x_tag->psize ,                                                                           <* 
          *>          x_tag->tsize , x_tag->dsize , x_tag->ssize ,                                                                           <* 
          *>          x_tag->lsize , x_tag->csize , x_tag->rsize , x_tag->isize , x_tag->msize ,                                             <* 
          *>          x_tag->Gsize , x_tag->Lsize ,                                                                                          <* 
          *>          x_tag->Fsize , x_tag->Isize , x_tag->Csize , x_tag->Ysize , x_tag->Msize ,                                             <* 
          *>          x_tag->Rflag , x_tag->Wflag , x_tag->Lflag , x_tag->Sflag ,                                                            <* 
          *>          x_tag->Dstyle, x_tag->Dmacro, x_tag->Dmatch,                                                                           <* 
          *>          x_tag->Nsize , x_tag->Osize , x_tag->Wsize , x_tag->Zsize ,                                                            <* 
          *>          x_tag->Pstyle, x_tag->Esize , x_tag->Xsize , '-');                                                                     <* 
          *> } else {                                                                                                                        <* 
          *>    printf ("%c %c %c  %-68.68s   ", x_tag->scope , x_tag->rtype , x_tag->psize , "");                                           <* 
          *>    printf ("%-47.47s   ", "");                                                                                                  <* 
          *> }                                                                                                                               <*/
         printf ("%-25.25s     %-4d      ", x_tag->file->name, x_tag->line);
         printf ("%-6.6s    %c    %-35.35s", x_tag->image, x_tag->ready, x_tag->desc);
         printf ("\n");
         rc = poly_files_nexttag (x_file, &x_tag);
         DEBUG_PROG   yLOG_value   ("nexttag"   , rc);
         DEBUG_PROG   yLOG_point   ("x_tag"     , x_tag);
      }
      if (my.g_mode == MODE_HTAGS)  for (i = 0; i < 70 - x_file->count; ++i)  printf ("\n");
      x_file = x_file->next;
      DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}
