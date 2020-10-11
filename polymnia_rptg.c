/*============================----beg-of-source---============================*/
#include  "polymnia.h"

static    char     s_prefix     [LEN_LABEL];

char
poly_rptg__debug        (tFUNC *a_tag)
{
   if (strchr ("Bb", a_tag->STATS_DSTYLE) != NULL) {
      strlcpy (s_prefix, "style"     , LEN_LABEL);
      return 1;
   }
   if (a_tag->STATS_DSTYLE == '#') {
      strlcpy (s_prefix, "boom"      , LEN_LABEL);
      return 1;
   }
   if (a_tag->STATS_DMACRO == '#' && strchr ("LSf", a_tag->STATS_DSTYLE) == NULL) {
      strlcpy (s_prefix, "macro"     , LEN_LABEL);
      return 1;
   }
   if (strchr ("!#EX", a_tag->STATS_DMATCH) != NULL) {
      strlcpy (s_prefix, "match"     , LEN_LABEL);
      return 1;
   }
   if (a_tag->STATS_DSTYLE == '-' && strchr ("ABCDEFGHIJKLMNOPQRSTUVWXYZ#", a_tag->STATS_TOTAL) != NULL) {
      strlcpy (s_prefix, "size"      , LEN_LABEL);
      return 1;
   }
   return 0;
}

char
poly_rptg__params       (tFUNC *a_tag)
{
   if (strchr ("56789ABCDEFGHIJKLMNOPQRSTUVWXYZ#", a_tag->STATS_PARAMS) != NULL) {
      strlcpy (s_prefix, "count"     , LEN_LABEL);
      return 1;
   }
   if (strchr ("#" , a_tag->STATS_PTWO) != NULL) {
      strlcpy (s_prefix, "**"        , LEN_LABEL);
      return 1;
   }
   if (strchr ("#" , a_tag->STATS_PNUM) != NULL) {
      strlcpy (s_prefix, "num*"      , LEN_LABEL);
      return 1;
   }
   return 0;
}

char
poly_rptg__data         (tFUNC *a_tag)
{
   if (strchr ("rR", a_tag->STATS_READ ) != NULL) {
      strlcpy (s_prefix, "read"      , LEN_LABEL);
      return 1;
   }
   if (strchr ("wW", a_tag->STATS_WRITE) != NULL) {
      strlcpy (s_prefix, "write"     , LEN_LABEL);
      return 1;
   }
   return 0;
}

char
poly_rptg__linux        (tFUNC *a_tag)
{
   if (strchr ("p"   , a_tag->STATS_SYSTEM) != NULL) {
      strlcpy (s_prefix, "process"   , LEN_LABEL);
      return 1;
   }
   if (strchr ("s"   , a_tag->STATS_SYSTEM) != NULL) {
      strlcpy (s_prefix, "system"    , LEN_LABEL);
      return 1;
   }
   if (strchr ("f"   , a_tag->STATS_SYSTEM) != NULL) {
      strlcpy (s_prefix, "filesys"   , LEN_LABEL);
      return 1;
   }
   if (strchr ("B"   , a_tag->STATS_SYSTEM) != NULL) {
      strlcpy (s_prefix, "all"       , LEN_LABEL);
      return 1;
   }
   return 0;
}

char
poly_rptg__stats        (tFUNC *a_tag)
{
   printf ("%c   ", a_tag->STATS_SINGLE);
   if (strncmp (a_tag->name, "o___", 4) != 0) {
      printf ("%c %c %c  %c %c %c  %c %c %c %c %c   %c %c  %c %c %c %c %c  %c %c %c %c   %c %c %c  %c %c %c %c  %c %c %c %c   ",
            a_tag->STATS_SCOPE , a_tag->STATS_RTYPE , a_tag->STATS_PARAMS,
            a_tag->STATS_TOTAL , a_tag->STATS_DEBUG , a_tag->STATS_SLOCL ,
            a_tag->STATS_LOCALS, a_tag->STATS_CHOICE, a_tag->STATS_RETURN, a_tag->STATS_INDENT, a_tag->STATS_MEMORY ,
            a_tag->STATS_GCALLS, a_tag->STATS_LCALLS,
            a_tag->STATS_FUNCS , a_tag->STATS_INTERN, a_tag->STATS_CSTD  , a_tag->STATS_YLIB  , a_tag->STATS_MSTRY ,
            a_tag->STATS_READ  , a_tag->STATS_WRITE , a_tag->STATS_SYSTEM, a_tag->STATS_RECURS,
            a_tag->STATS_DSTYLE, a_tag->STATS_DMACRO, a_tag->STATS_DMATCH,
            a_tag->STATS_NCURSE, a_tag->STATS_OPENGL, a_tag->STATS_WINDOW, a_tag->STATS_MYX   ,
            a_tag->STATS_PROTO , a_tag->STATS_ECALLS, a_tag->STATS_PTWO  , a_tag->STATS_PNUM  );
      printf ("[%c%c%c.%c%c%c.%c%c%c%c%c] [%c%c.%c%c%c%c%c.%c%c%c%c] [%c%c%c.%c%c%c%c.%c%c%c%c]   ",
            a_tag->STATS_SCOPE , a_tag->STATS_RTYPE , a_tag->STATS_PARAMS,
            a_tag->STATS_TOTAL , a_tag->STATS_DEBUG , a_tag->STATS_SLOCL ,
            a_tag->STATS_LOCALS, a_tag->STATS_CHOICE, a_tag->STATS_RETURN, a_tag->STATS_INDENT, a_tag->STATS_MEMORY ,
            a_tag->STATS_GCALLS, a_tag->STATS_LCALLS,
            a_tag->STATS_FUNCS , a_tag->STATS_INTERN, a_tag->STATS_CSTD  , a_tag->STATS_YLIB  , a_tag->STATS_MSTRY ,
            a_tag->STATS_READ  , a_tag->STATS_WRITE , a_tag->STATS_SYSTEM, a_tag->STATS_RECURS,
            a_tag->STATS_DSTYLE, a_tag->STATS_DMACRO, a_tag->STATS_DMATCH,
            a_tag->STATS_NCURSE, a_tag->STATS_OPENGL, a_tag->STATS_WINDOW, a_tag->STATS_MYX   ,
            a_tag->STATS_PROTO , a_tag->STATS_ECALLS, a_tag->STATS_PTWO  , a_tag->STATS_PNUM  );
   } else {
      printf ("%c %c %c  %-68.68s   ", a_tag->STATS_SCOPE , a_tag->STATS_RTYPE , a_tag->STATS_PARAMS , "");
      printf ("%-47.47s   ", "");
   }
   return 0;
}

char
poly_rptg__dump_line    (tFUNC *a_tag)
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
   printf ("%-8.8s   %c   %-35.35s\n"  , a_tag->image, a_tag->ready, a_tag->purpose);
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
               x_file->COUNT_LINES, x_file->COUNT_EMPTY,
               x_file->COUNT_DOCS , x_file->COUNT_DEBUG,
               x_file->COUNT_CODE , x_file->COUNT_SLOCL);
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
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   my.COUNT_FILES = my.COUNT_FUNCS = my.COUNT_LINES = my.COUNT_EMPTY = my.COUNT_DOCS  = my.COUNT_DEBUG = my.COUNT_CODE  = my.COUNT_SLOCL = 0;
   if (my.g_mode != MODE_DUMP && my.g_titles == RPTG_TITLES) {
      printf ("## project listing report\n");
      printf ("##    generated by polymnia-hymnos (many praises) muse of divine hymns, c language, dance, geometry, and grammar\n");
      printf ("\n");;
      printf ("##---name----------------  file --funcs --lines --empty ---docs --debug ---code --slocl  ---code-size---  ---greek-heritage-------------------------------------------  ---purpose-statement----------------------------------------  -ver- ---version-description--------------------------------------  ---focus------------  ---niche------------  --created-  ---home-directory-------------------------------------------\n");
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
      my.COUNT_FILES += x_proj->count;
      my.COUNT_FUNCS += x_proj->funcs;
      my.COUNT_LINES += x_proj->COUNT_LINES;
      my.COUNT_EMPTY += x_proj->COUNT_EMPTY;
      my.COUNT_DOCS  += x_proj->COUNT_DOCS;
      my.COUNT_DEBUG += x_proj->COUNT_DEBUG;
      my.COUNT_CODE  += x_proj->COUNT_CODE;
      my.COUNT_SLOCL += x_proj->COUNT_SLOCL;
      /*---(project filtering)-----------*/
      if (my.g_proj != NULL && x_proj != my.g_proj) {
         x_proj = (tPROJ *) poly_btree_next  (B_PROJ);
         DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
         continue;
      }
      if (my.g_titles == RPTG_TITLES && c % 5 == 0)  printf ("\n");
      /*---(reporting)-------------------*/
      if (my.g_mode != MODE_DUMP) {
         printf ("%-25.25s  %4d %7d %7d %7d %7d %7d %7d %7d  %-13.13s  ",
               x_proj->name , x_proj->count, x_proj->funcs,
               x_proj->COUNT_LINES, x_proj->COUNT_EMPTY,
               x_proj->COUNT_DOCS , x_proj->COUNT_DEBUG,
               x_proj->COUNT_CODE , x_proj->COUNT_SLOCL,
               x_proj->codesize);
         printf ("%-60.60s  %-60.60s  %-5.5s %-60.65s  %-20.20s  %-20.20s  %-10.10s  %-60.60s\n",
               x_proj->heritage, x_proj->purpose,
               x_proj->vernum  , x_proj->vertxt,
               x_proj->focus   , x_proj->niche,
               x_proj->created , x_proj->homedir);
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
      ++c;
      /*---(done)------------------------*/
   }
   if (my.g_titles == RPTG_TITLES)  {
      printf ("\n");;
      printf ("## %17.17s (%3d) %4d %7d %7d %7d %7d %7d %7d %7d\n", "GRAND TOTALS", c,
            my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_LINES, my.COUNT_EMPTY, my.COUNT_DOCS, my.COUNT_DEBUG, my.COUNT_CODE, my.COUNT_SLOCL);
   }
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
   tFUNC      *x_tag       = NULL;
   char        x_show      =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_RPTG   yLOG_note    ("review all tags and code");
   DEBUG_RPTG   yLOG_value   ("projects"  , poly_btree_count (B_PROJ));
   /*---(header)-------------------------*/
   if (my.g_titles == RPTG_TITLES) {
      printf ("## function listing report\n");
      printf ("##    generated by polymnia-hymnos (many praises) muse of divine hymns, c language, dance, geometry, and grammar\n");
      printf ("\n");
   }
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
      if (my.g_titles == RPTG_TITLES && x_proj->count > 0) {
         printf ("\nPROJECT : %s, %s\n", x_proj->name, x_proj->purpose);
      }
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
         if (my.g_titles == RPTG_TITLES && x_file->count > 0) {
            printf ("\nFILE    : %s\n", x_file->name);
         }
         /*---(tags)---------------------*/
         x_tag  = x_file->head;
         DEBUG_RPTG   yLOG_point   ("tag"       , x_tag);
         while (x_tag  != NULL) {
            DEBUG_RPTG   yLOG_info    ("->name"    , x_tag->name);
            switch (my.g_filter) {
            case FILTER_DEBUG  : x_show = poly_rptg__debug  (x_tag);  break;
            case FILTER_PARAMS : x_show = poly_rptg__params (x_tag);  break;
            case FILTER_DATA   : x_show = poly_rptg__data   (x_tag);  break;
            case FILTER_LINUX  : x_show = poly_rptg__linux  (x_tag);  break;
            default            : x_show = 1;
            }
            if (x_show == 1)  {
               if (my.g_titles == RPTG_TITLES && c % 25 == 0) {
                  printf ("\n##");
                  if (my.g_filter != FILTER_NONE)  printf ("-reason-  --");
                  printf ("---project-------------   ---file------------------   line   ---function/tag----------   -  [------complexity-------] [------integration------] [----watch-points-------]  [-complexity--] [-integration-] [-watch-point-]  [----source-file----------]   [line]    [-type-] [rdy] [-----------description-------------]\n");
               }
               if (my.g_titles == RPTG_TITLES && c %  5 == 0)  printf ("\n");
               if (my.g_filter != FILTER_NONE)  printf ("%-12.12s", s_prefix);
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
   tFUNC      *x_tag       = NULL;
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
      printf ("## external function call usage report\n");
      printf ("##    generated by polymnia-hymnos (many praises) muse of divine hymns, c language, dance, geometry, and grammar\n");
      printf ("##    target extern : %s\n", a_extern->name);
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
         printf ("%-25.25s  %-25.25s  %-25.25s  %4d  %-25.25s\n", a_extern->name, x_ylib->tag->file->proj->name, x_ylib->tag->file->name, x_ylib->line, x_ylib->tag->name);
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
poly_rptg_htags         (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   tFUNC      *x_tag       = NULL;
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
      printf ("##\n");
      printf ("##   focus      [%s]\n", a_proj->focus);
      printf ("##   niche      [%s]\n", a_proj->niche);
      printf ("##   subject    [%s]\n", a_proj->subject);
      printf ("##   purpose    [%s]\n", a_proj->purpose);
      printf ("##\n");
      printf ("##   namesake   [%s]\n", a_proj->namesake);
      printf ("##   heritage   [%s]\n", a_proj->heritage);
      printf ("##   imagery    [%s]\n", a_proj->imagery);
      printf ("##   reason     [%s]\n", a_proj->reason);
      printf ("##   one-line   [%s]\n", a_proj->oneline);
      printf ("##\n");
      printf ("##   basename   [%s]\n", a_proj->progname);
      printf ("##   homedir    [%s]\n", a_proj->homedir);
      printf ("##   fullpath   [%s]\n", a_proj->fullpath);
      printf ("##   suffix     [%s]\n", a_proj->suffix);
      printf ("##   content    [%s]\n", a_proj->content);
      printf ("##\n");
      printf ("##   system     [%s]\n", a_proj->systems);
      printf ("##   language   [%s]\n", a_proj->language);
      printf ("##   code-size  [%s]\n", a_proj->codesize);
      printf ("##\n");
      printf ("##   author     [%s]\n", a_proj->author);
      printf ("##   created    [%s]\n", a_proj->created);
      printf ("##   depends    [%s]\n", a_proj->depends);
      printf ("##\n");
      printf ("##   vermajor   [%s]\n", a_proj->vermajor);
      printf ("##   verminor   [%s]\n", a_proj->verminor);
      printf ("##   vernum     [%s]\n", a_proj->vernum);
      printf ("##   vertxt     [%s]\n", a_proj->vertxt);
      printf ("##\n\n\n\n");
   }
   while (x_file != NULL) {
      DEBUG_PROG   yLOG_info    ("file name" , x_file->name);
      printf ("%-29.29s   FILE\n", x_file->name);
      if (my.g_mode == MODE_HTAGS) {
         sprintf (a, "lines : %4d  %5d", x_file->COUNT_LINES, x_file->proj->COUNT_LINES);
         sprintf (b, "empty : %4d  %5d", x_file->COUNT_EMPTY, x_file->proj->COUNT_EMPTY);
         sprintf (c, "docs  : %4d  %5d", x_file->COUNT_DOCS , x_file->proj->COUNT_DOCS );
         sprintf (d, "debug : %4d  %5d", x_file->COUNT_DEBUG, x_file->proj->COUNT_DEBUG);
         sprintf (e, "code  : %4d  %5d", x_file->COUNT_CODE , x_file->proj->COUNT_CODE );
         sprintf (f, "slocl : %4d  %5d", x_file->COUNT_SLOCL, x_file->proj->COUNT_SLOCL);
         sprintf (g, "function (%d)"   , x_file->count);
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
      rc = poly_code_nextfunc (x_file, &x_tag);
      DEBUG_PROG   yLOG_value   ("nexttag"   , rc);
      DEBUG_PROG   yLOG_point   ("x_tag"     , x_tag);
      while (rc >= 0)  {
         DEBUG_PROG   yLOG_info    ("tag name"  , x_tag->name);
         printf ("%-2s  %-25.25s   ", x_tag->hint  , x_tag->name);
         poly_rptg__stats (x_tag);
         printf ("%-25.25s     %-4d      ", x_tag->file->name, x_tag->line);
         printf ("%-6.6s    %c    %-35.35s", x_tag->image, x_tag->ready, x_tag->purpose);
         printf ("\n");
         rc = poly_code_nextfunc (x_file, &x_tag);
         DEBUG_PROG   yLOG_value   ("nexttag"   , rc);
         DEBUG_PROG   yLOG_point   ("x_tag"     , x_tag);
      }
      if (my.g_mode == MODE_HTAGS)  for (i = 0; i < 70 - x_file->count; ++i)  printf ("\n");
      else         printf ("\n\n");
      x_file = x_file->next;
      DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}
