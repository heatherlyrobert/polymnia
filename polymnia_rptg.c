/*============================----beg-of-source---============================*/
#include  "polymnia.h"

static char     s_prefix     [LEN_LABEL];
static int      s_lines     =    0;
static int      s_empty     =    0;
static int      s_debug     =    0;
static int      s_docs      =    0;
static int      s_code      =    0;
static int      s_slocl     =    0;

char
poly_rptg__prep         (void)
{
   s_lines = s_empty = s_debug = s_docs = s_code = s_slocl = 0;
   return 0;
}

char
poly_rptg__inc          (tPROJ *a_proj)
{
   s_lines  += a_proj->COUNT_LINES;
   s_empty  += a_proj->COUNT_EMPTY;
   s_debug  += a_proj->COUNT_DEBUG;
   s_docs   += a_proj->COUNT_DOCS;
   s_code   += a_proj->COUNT_CODE;
   s_slocl  += a_proj->COUNT_SLOCL;
   return 0;
}

char
poly_rptg__total        (void)
{
   printf ("\n");
   printf ("         TOTALS (%3d) § %5d § %5d § %5d § %7d § %7d § %7d § %7d § %7d § %7d § \n",
         poly_btree_count (B_PROJ), poly_btree_count (B_FILES),
         poly_func_count (), g_nylib,
         s_lines, s_empty, s_debug, s_docs, s_code, s_slocl);
   return 0;
}

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
            a_tag->STATS_LVARS , a_tag->STATS_CHOICE, a_tag->STATS_RETURN, a_tag->STATS_INDENT, a_tag->STATS_MEMORY ,
            a_tag->STATS_GCALLS, a_tag->STATS_LCALLS,
            a_tag->STATS_FUNCS , a_tag->STATS_GFUNCS, a_tag->STATS_CSTD  , a_tag->STATS_YLIB  , a_tag->STATS_MYSTRY ,
            a_tag->STATS_READ  , a_tag->STATS_WRITE , a_tag->STATS_SYSTEM, a_tag->STATS_RECURS,
            a_tag->STATS_DSTYLE, a_tag->STATS_DMACRO, a_tag->STATS_DMATCH,
            a_tag->STATS_NCURSE, a_tag->STATS_OPENGL, a_tag->STATS_WINDOW, a_tag->STATS_MYX   ,
            a_tag->STATS_PROTO , a_tag->STATS_ECALLS, a_tag->STATS_PTWO  , a_tag->STATS_PNUM  );
      printf ("[%c%c%c.%c%c%c.%c%c%c%c%c] [%c%c.%c%c%c%c%c.%c%c%c%c] [%c%c%c.%c%c%c%c.%c%c%c%c]   ",
            a_tag->STATS_SCOPE , a_tag->STATS_RTYPE , a_tag->STATS_PARAMS,
            a_tag->STATS_TOTAL , a_tag->STATS_DEBUG , a_tag->STATS_SLOCL ,
            a_tag->STATS_LVARS , a_tag->STATS_CHOICE, a_tag->STATS_RETURN, a_tag->STATS_INDENT, a_tag->STATS_MEMORY ,
            a_tag->STATS_GCALLS, a_tag->STATS_LCALLS,
            a_tag->STATS_FUNCS , a_tag->STATS_GFUNCS, a_tag->STATS_CSTD  , a_tag->STATS_YLIB  , a_tag->STATS_MYSTRY ,
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
poly_rptg_projects      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_RPTG   yLOG_enter   (__FUNCTION__);
   /*---(report header)------------------*/
   printf ("#!/usr/local/bin/polymnia --projects\n");
   printf ("\n");
   printf ("polymnia-hymnos (many praises) greek muse and protector of divine hymns, dancing, geometry, and grammar\n");
   printf ("version %s, %s\n", P_VERNUM, P_VERTXT);
   printf ("project inventory with key statistics\n");
   printf ("\n");
   /*---(prepare)------------------------*/
   poly_rptg__prep ();
   DEBUG_RPTG   yLOG_value   ("projects"  , poly_btree_count (B_PROJ));
   rc = poly_proj_cursor ('[', &x_proj);
   DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
   poly_proj_line (NULL, my.g_rptg, 0, 'y');
   /*---(walk projects)------------------*/
   while (rc >= 0 && x_proj != NULL) {
      /*---(prepare)---------------------*/
      DEBUG_RPTG   yLOG_info    ("->name"    , x_proj->name);
      DEBUG_RPTG   yLOG_value   ("files"     , x_proj->count);
      if (c % 5 == 0)  printf ("\n");
      poly_proj_line (x_proj, my.g_rptg, c, 'y');
      poly_rptg__inc  (x_proj);
      /*---(next)------------------------*/
      rc = poly_proj_cursor ('>', &x_proj);
      DEBUG_RPTG   yLOG_point   ("proj"      , x_proj);
      ++c;
      /*---(done)------------------------*/
   }
   printf ("\n");
   poly_proj_line (NULL, my.g_rptg, 0, 'y');
   poly_rptg__total ();
   printf ("\n");
   printf ("## end of report\n");
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
      if (my.g_mode != POLY_RPTG_DUMP) {
         printf ("  %-23.23s       %7d %7d %7d %7d %7d %7d %7d\n",
               x_file->name , x_file->count,
               x_file->COUNT_LINES, x_file->COUNT_EMPTY,
               x_file->COUNT_DOCS , x_file->COUNT_DEBUG,
               x_file->COUNT_CODE , x_file->COUNT_SLOCL);
      }
      switch (my.g_mode) {
      case POLY_RPTG_PROJS :
      case MODE_FILE :
         break;
      case POLY_RPTG_HTAGS :
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
   poly_proj_by_name  (my.g_project, &my.g_proj);
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
   if (my.g_mode != POLY_RPTG_DUMP && my.g_titles == RPTG_TITLES) {
      printf ("## project listing report\n");
      printf ("##    generated by polymnia-hymnos (many praises) muse of divine hymns, c language, dance, geometry, and grammar\n");
      printf ("\n");;
      printf ("##---name---------------- § --files § --funcs § --lines § --empty § ---docs § --debug § ---code § --slocl § ---code-size---  ---greek-heritage-------------------------------------------  ---purpose-statement----------------------------------------  -ver- ---version-description--------------------------------------  ---focus------------  ---niche------------  --created-  ---home-directory-------------------------------------------\n");
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
      if (my.g_mode != POLY_RPTG_DUMP) {
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
      case POLY_RPTG_PROJS :
         break;
      case MODE_FILE : case POLY_RPTG_HTAGS : case POLY_RPTG_DUMP :
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
   tFUNC      *x_func      = NULL;
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
         x_func  = x_file->head;
         DEBUG_RPTG   yLOG_point   ("tag"       , x_func);
         while (x_func  != NULL) {
            DEBUG_RPTG   yLOG_info    ("->name"    , x_func->name);
            switch (my.g_filter) {
            case FILTER_DEBUG  : x_show = poly_rptg__debug  (x_func);  break;
            case FILTER_PARAMS : x_show = poly_rptg__params (x_func);  break;
            case FILTER_DATA   : x_show = poly_rptg__data   (x_func);  break;
            case FILTER_LINUX  : x_show = poly_rptg__linux  (x_func);  break;
            default            : x_show = 1;
            }
            if (x_show == 1)  {
               if (my.g_titles == RPTG_TITLES && c % 25 == 0) {
                  printf ("\n##");
                  if (my.g_filter != FILTER_NONE)  printf ("-reason-  --");
                  printf ("%s\n", poly_func_line (x_func, POLY_RPTG_DUMP, 0, 0, 0, NULL));
                  /*> printf ("---project-------------   ---file------------------   line   ---function/tag----------   -  [------complexity-------] [------integration------] [----watch-points-------]  [-complexity--] [-integration-] [-watch-point-]  [----source-file----------]   [line]    [-type-] [rdy] [-----------description-------------]\n");   <*/
               }
               if (my.g_titles == RPTG_TITLES && c %  5 == 0)  printf ("\n");
               if (my.g_filter != FILTER_NONE)  printf ("%-12.12s", s_prefix);
               printf ("%s\n", poly_func_line (x_func, POLY_RPTG_DUMP, 0, 0, 0, NULL));
               ++c;
            }
            x_func  = x_func->next;
            DEBUG_RPTG   yLOG_point   ("x_func"    , x_func);
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
   tFUNC      *x_func      = NULL;
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
   x_ylib = a_extern->y_head;
   DEBUG_RPTG   yLOG_point   ("x_ylib"    , x_ylib);
   while (x_ylib != NULL) {
      /*---(project filtering)-----------*/
      if (my.g_proj != NULL && x_ylib->func->file->proj != my.g_proj) {
         x_ylib = x_ylib->e_next;
         DEBUG_RPTG   yLOG_point   ("x_ylib"    , x_ylib);
         continue;
      }
      /*---(headers)---------------------*/
      if (my.g_titles == RPTG_TITLES && c % 25 == 0)  printf ("\n##---project-------------  ---source-file-----------  line  ---source-function-------\n");
      if (my.g_titles == RPTG_TITLES && c %  5 == 0)  printf ("\n");
      DEBUG_RPTG   yLOG_info    ("->name"    , x_ylib->name);
      /*---(tree view)-------------------*/
      if (my.g_titles == RPTG_TREEVIEW) {
         if (x_ylib->func->file->proj != x_proj) {
            x_file = NULL;
            printf ("\n");
            printf ("%-25.25s\n", x_ylib->func->file->proj->name);
         }
         if (x_ylib->func->file != x_file) {
            x_func  = NULL;
            if (x_file != NULL)  printf ("\n");
            printf ("   %-25.25s\n", x_ylib->func->file->name);
         } 
         if (x_ylib->func != x_func) {
            if (x_func != NULL)  printf ("\n");
            printf ("      %-25.25s", x_ylib->func->name);
         } 
         printf ("%4d,", x_ylib->line);
         x_proj = x_ylib->func->file->proj;
         x_file = x_ylib->func->file;
         x_func = x_ylib->func;
      }
      /*---(normal view)-----------------*/
      else {
         printf ("%-25.25s  %-25.25s  %-25.25s  %4d  %-25.25s\n", a_extern->name, x_ylib->func->file->proj->name, x_ylib->func->file->name, x_ylib->line, x_ylib->func->name);
      }
      /*---(next)------------------------*/
      ++c;
      x_ylib = x_ylib->e_next;
      DEBUG_RPTG   yLOG_point   ("x_ylib"    , x_ylib);
      /*---(done)------------------------*/
   }
   if (my.g_titles == RPTG_TITLES)  printf ("\n## %d total references, %d shown\n", a_extern->y_count, c);
   /*---(complete)-----------------------*/
   DEBUG_RPTG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_rptg__htags_header (tPROJ *a_proj)
{
   printf ("##/usr/local/bin/polymnia --htags\n");
   printf ("##\n");
   printf ("##   polymnia-hymnos (many praises) greek muse and protector of divine hymns, dancing, geometry, and grammar\n");
   printf ("##   version %s, %s\n", P_VERNUM, P_VERTXT);
   printf ("##   htags reporting file for use with vim-ide\n");
   printf ("##\n");
   printf ("##\n");
   printf ("##\n");
   printf ("##   25 headers ·  [%s]\n", a_proj->header);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   name       n  [%s]\n", a_proj->name);
   printf ("##   focus      f  [%s]\n", a_proj->focus);
   printf ("##   niche      n  [%s]\n", a_proj->niche);
   printf ("##   subject    s  [%s]\n", a_proj->subject);
   printf ("##   purpose    p  [%s]\n", a_proj->purpose);
   printf ("##\n");
   printf ("##   namesake   g  [%s]\n", a_proj->namesake);
   printf ("##   heritage   h  [%s]\n", a_proj->heritage);
   printf ("##   imagery    i  [%s]\n", a_proj->imagery);
   printf ("##   reason     r  [%s]\n", a_proj->reason);
   printf ("##   one-line   o  [%s]\n", a_proj->oneline);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   homedir    d  [%s]\n", a_proj->homedir);
   printf ("##   basename   b  [%s]\n", a_proj->progname);
   printf ("##   fullpath   f  [%s]\n", a_proj->fullpath);
   printf ("##   suffix     s  [%s]\n", a_proj->suffix);
   printf ("##   content    c  [%s]\n", a_proj->content);
   printf ("##\n");
   printf ("##   system     s  [%s]\n", a_proj->systems);
   printf ("##   language   l  [%s]\n", a_proj->language);
   printf ("##   code-size  z  [%s]\n", a_proj->codesize);
   printf ("##   depends    d  [%s]\n", a_proj->depends);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n");
   printf ("##   author     a  [%s]\n", a_proj->author);
   printf ("##   created    c  [%s]\n", a_proj->created);
   printf ("##\n");
   printf ("##   vermajor   x  [%s]\n", a_proj->vermajor);
   printf ("##   verminor   n  [%s]\n", a_proj->verminor);
   printf ("##   vernum     v  [%s]\n", a_proj->vernum);
   printf ("##   vertxt     t  [%s]\n", a_proj->vertxt);
   printf ("##\n");
   printf ("##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]\n");
   printf ("##\n\n\n\n");
   return 0;
}

char
poly_rptg_htags         (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   tFUNC      *x_func      = NULL;
   int         i           =    0;
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
   if (my.g_rptg == POLY_RPTG_HTAGS)    poly_rptg__htags_header (a_proj);
   while (x_file != NULL) {
      DEBUG_PROG   yLOG_info    ("file name" , x_file->name);
      printf ("%-29.29s   FILE\n", x_file->name);
      if (my.g_rptg == POLY_RPTG_HTAGS) {
         printf ("%s\n", poly_cats_header (7, "lines", x_file->COUNT_LINES, x_file->proj->COUNT_LINES));
         printf ("%s\n", poly_cats_header (6, "empty", x_file->COUNT_EMPTY, x_file->proj->COUNT_EMPTY));
         printf ("%s\n", poly_cats_header (5, "docs" , x_file->COUNT_DOCS , x_file->proj->COUNT_DOCS ));
         printf ("%s\n", poly_cats_header (4, "debug", x_file->COUNT_DEBUG, x_file->proj->COUNT_DEBUG));
         printf ("%s\n", poly_cats_header (3, "code" , x_file->COUNT_CODE , x_file->proj->COUNT_CODE ));
         printf ("%s\n", poly_cats_header (2, "slocl", x_file->COUNT_SLOCL, x_file->proj->COUNT_SLOCL));
         printf ("%s\n", poly_cats_header (1, ""     , 0                   , 0                       ));
         printf ("%s\n", poly_func_line   (NULL, POLY_RPTG_HTAGS, 0, 0, x_file->count, '-'));
      }
      x_func = NULL;
      rc = poly_code_nextfunc (x_file, &x_func);
      DEBUG_PROG   yLOG_value   ("nexttag"   , rc);
      DEBUG_PROG   yLOG_point   ("x_func"    , x_func);
      while (rc >= 0)  {
         DEBUG_PROG   yLOG_info    ("name"      , x_func->name);
         printf ("%s\n", poly_func_line (x_func, POLY_RPTG_HTAGS, 0, 0, 0, '-'));
         rc = poly_code_nextfunc (x_file, &x_func);
         DEBUG_PROG   yLOG_value   ("nexttag"   , rc);
         DEBUG_PROG   yLOG_point   ("x_func"    , x_func);
      }
      if (my.g_rptg == POLY_RPTG_HTAGS)  for (i = 0; i < 70 - x_file->count; ++i)  printf ("\n");
      else         printf ("\n\n");
      x_file = x_file->next;
      DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}


