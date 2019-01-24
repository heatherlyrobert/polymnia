/*============================----beg-of-source---============================*/
#include  "polymnia.h"


char
poly_rptg__stats        (tTAG *a_tag)
{
   printf ("%c   ", a_tag->oneline);
   if (strncmp (a_tag->name, "o___", 4) != 0) {
      printf ("%c %c %c  %c %c %c  %c %c %c %c %c   %c %c  %c %c %c %c %c  %c %c %c %c   %c %c  %c %c %c %c  %c %c %c %c %c   ",
            a_tag->scope , a_tag->rtype , a_tag->psize ,
            a_tag->tsize , a_tag->dsize , a_tag->ssize ,
            a_tag->lsize , a_tag->csize , a_tag->rsize , a_tag->isize , a_tag->msize ,
            a_tag->Gsize , a_tag->Lsize ,
            a_tag->Fsize , a_tag->Isize , a_tag->Csize , a_tag->Ysize , a_tag->Msize ,
            a_tag->Rflag , a_tag->Wflag , a_tag->Lflag , a_tag->Sflag ,
            a_tag->Dstyle, a_tag->Dmacro,
            a_tag->Nsize , a_tag->Osize , a_tag->Wsize , a_tag->Zsize ,
            a_tag->Pstyle, a_tag->Esize , a_tag->Xsize , '-', '-');
      printf ("[%c%c%c.%c%c%c.%c%c%c%c%c] [%c%c.%c%c%c%c%c.%c%c%c%c] [%c%c.%c%c%c%c.%c%c%c%c%c]   ",
            a_tag->scope , a_tag->rtype , a_tag->psize ,
            a_tag->tsize , a_tag->dsize , a_tag->ssize ,
            a_tag->lsize , a_tag->csize , a_tag->rsize , a_tag->isize , a_tag->msize ,
            a_tag->Gsize , a_tag->Lsize ,
            a_tag->Fsize , a_tag->Isize , a_tag->Csize , a_tag->Ysize , a_tag->Msize ,
            a_tag->Rflag , a_tag->Wflag , a_tag->Lflag , a_tag->Sflag ,
            a_tag->Dstyle, a_tag->Dmacro,
            a_tag->Nsize , a_tag->Osize , a_tag->Wsize , a_tag->Zsize ,
            a_tag->Pstyle, a_tag->Esize , a_tag->Xsize , '-', '-');
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
      if (g_mode != MODE_DUMP) {
         printf ("  %-23.23s       %7d %7d %7d %7d %7d %7d %7d\n",
               x_file->name , x_file->count,
               x_file->lines, x_file->empty,
               x_file->docs , x_file->debug,
               x_file->code , x_file->slocl);
      }
      switch (g_mode) {
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
poly_rptg_proj          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_files = s_funcs = s_lines = s_empty = s_docs  = s_debug = s_code  = s_slocl = 0;
   if (g_mode != MODE_DUMP) {
      printf ("---name------------------  file --ntags --lines --empty ---docs --debug ---code --slocl  ---code-size---  ---greek-heritage-------------------------------------------  ---purpose-statement----------------------------------------  -ver- ---version-description--------------------------------------  ---focus------------  ---niche------------  --created-  ---home-directory-------------------------------------------\n\n");
   }
   /*---(projects)-----------------------*/
   DEBUG_RPTG   yLOG_value   ("projects"  , poly_btree_count (B_PROJ));
   x_proj = (tPROJ *) poly_btree_first (B_PROJ);
   DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
   while (x_proj != NULL) {
      DEBUG_RPTG   yLOG_info    ("->name"    , x_proj->name);
      DEBUG_RPTG   yLOG_value   ("files"     , x_proj->count);
      s_files += x_proj->count;
      s_funcs += x_proj->ntags;
      s_lines += x_proj->lines;
      s_empty += x_proj->empty;
      s_docs  += x_proj->docs;
      s_debug += x_proj->debug;
      s_code  += x_proj->code;
      s_slocl += x_proj->slocl;
      if (g_mode != MODE_DUMP) {
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
      switch (g_mode) {
      case MODE_PROJ :
         break;
      case MODE_FILE :
      case MODE_TAGS :
      case MODE_DUMP :
         rc = poly_rptg_file (x_proj);
         printf ("\n");
         break;
      }
      x_proj = (tPROJ *) poly_btree_next  (B_PROJ);
      DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
   }
   printf ("%25.25s  %4d %7d %7d %7d %7d %7d %7d %7d\n", "GRAND TOTALS",
         s_files, s_funcs, s_lines, s_empty, s_docs, s_debug, s_code, s_slocl);
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
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(projects)-----------------------*/
   DEBUG_RPTG   yLOG_note    ("review all tags and code");
   DEBUG_RPTG   yLOG_value   ("projects"  , poly_btree_count (B_PROJ));
   x_proj = (tPROJ *) poly_btree_first (B_PROJ);
   DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
   while (x_proj != NULL) {
      DEBUG_RPTG   yLOG_info    ("->name"    , x_proj->name);
      DEBUG_RPTG   yLOG_value   ("files"     , x_proj->count);
      x_file = x_proj->head;
      DEBUG_RPTG   yLOG_point   ("file"      , x_file);
      while (x_file != NULL) {
         DEBUG_RPTG   yLOG_info    ("->name"    , x_file->name);
         DEBUG_RPTG   yLOG_value   ("tags"      , x_file->count);
         x_tag  = x_file->head;
         DEBUG_RPTG   yLOG_point   ("tag"       , x_tag);
         while (x_tag  != NULL) {
            DEBUG_RPTG   yLOG_info    ("->name"    , x_tag->name);
            rc = poly_rptg__dump_line (x_tag);
            x_tag  = x_tag->next;
            DEBUG_RPTG   yLOG_point   ("tag"       , x_tag);
         }
         x_file = x_file->next;
         DEBUG_RPTG   yLOG_point   ("file"      , x_file);
      }
      x_proj = (tPROJ *) poly_btree_next  (B_PROJ);
      DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
   }
   /*---(complete)-----------------------*/
   DEBUG_RPTG   yLOG_exit    (__FUNCTION__);
   return 0;
}
