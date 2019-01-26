/*============================----beg-of-source---============================*/
#include  "polymnia.h"



tMY         my;



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/



char      unit_answer [LEN_RECD] = "";

char         /*-> very first setup -------------------[ shoot  [gz.633.201.0A]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG_init          (int a_argc, char *a_argv[])
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(run-time-config)----------------*/
   my.g_mode      = MODE_SEARCH;
   my.g_titles    = RPTG_NOTITLES;
   my.g_filter    = FILTER_NONE;
   /*---(filtering)----------------------*/
   my.g_project [0]  = '\0';
   my.g_proj         = NULL;
   my.g_extern [0]   = '\0';
   /*---(files)--------------------------*/
   my.f_db        = NULL;
   my.f_prog      = NULL;
   my.f_tags      = NULL;
   my.f_flow      = NULL;
   my.f_extern    = NULL;
   my.f_mystry    = NULL;
   /*---(global counts)------------------*/
   my.s_files     = 0;
   my.s_funcs     = 0;
   my.s_lines     = 0;
   my.s_empty     = 0;
   my.s_docs      = 0;
   my.s_debug     = 0;
   my.s_code      = 0;
   my.s_slocl     = 0;
   /*---(initialization)-----------------*/
   poly_proj_init    ();
   poly_files_init   ();
   poly_tags_init    ();
   poly_extern_init  ();
   /*---(complete)-----------------------*/
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
      if      (strcmp (a, "--search"   ) == 0)  my.g_mode   = MODE_SEARCH;
      else if (strcmp (a, "--htags"    ) == 0)  my.g_mode   = MODE_HTAGS;
      else if (strcmp (a, "--dump"     ) == 0)  my.g_mode   = MODE_DUMP;
      else if (strcmp (a, "--write"    ) == 0)  my.g_mode   = MODE_WRITE;
      else if (strcmp (a, "--update"   ) == 0)  my.g_mode   = MODE_UPDATE;
      else if (strcmp (a, "--projs"    ) == 0)  my.g_mode   = MODE_PROJ;
      else if (strcmp (a, "--files"    ) == 0)  my.g_mode   = MODE_FILE;
      else if (strcmp (a, "--system"   ) == 0)  my.g_mode   = MODE_SYSTEM;
      else if (strcmp (a, "--titles"   ) == 0)  my.g_titles = RPTG_TITLES;
      else if (strcmp (a, "--notitles" ) == 0)  my.g_titles = RPTG_NOTITLES;
      else if (strcmp (a, "--treeview" ) == 0)  my.g_titles = RPTG_TREEVIEW;
      else if (strcmp (a, "--debug"    ) == 0)  my.g_filter = FILTER_DEBUG;
      /*---(compound)--------------------*/
      else if (strcmp (a, "--remove" ) == 0) {
         my.g_mode = MODE_REMOVE;
         if (++i < argc)  strlcpy (my.g_project, argv[i], LEN_NAME);
         else {
            DEBUG_TOPS  yLOG_note  ("project name not included");
            DEBUG_TOPS  yLOG_exitr (__FUNCTION__, -1);
            return -1;
         }
      }
      else if (strcmp (a, "--project") == 0) {
         if (++i < argc)  strlcpy (my.g_project, argv[i], LEN_NAME);
         else {
            DEBUG_TOPS  yLOG_note  ("project name not included");
            DEBUG_TOPS  yLOG_exitr (__FUNCTION__, -1);
            return -1;
         }
      }
      else if (strcmp (a, "--extern" ) == 0) {
         my.g_mode = MODE_EXTERN;
         if (++i < argc)  strlcpy (my.g_extern, argv[i], LEN_NAME);
         else {
            DEBUG_TOPS  yLOG_note  ("extern name not included");
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
   my.s_files = my.s_funcs = my.s_lines = my.s_empty = my.s_docs  = my.s_debug = my.s_code  = my.s_slocl = 0;
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
   if      (my.s_slocl < 100    )  strlcpy (a_proj->codesize, "u.micro"       , LEN_LABEL);
   else if (my.s_slocl < 500    )  strlcpy (a_proj->codesize, "t.tiny"        , LEN_LABEL);
   else if (my.s_slocl < 2000   )  strlcpy (a_proj->codesize, "s.small"       , LEN_LABEL);
   else if (my.s_slocl < 10000  )  strlcpy (a_proj->codesize, "m.moderate"    , LEN_LABEL);
   else if (my.s_slocl < 50000  )  strlcpy (a_proj->codesize, "l.large"       , LEN_LABEL);
   else if (my.s_slocl < 250000 )  strlcpy (a_proj->codesize, "h.huge"        , LEN_LABEL);
   else if (my.s_slocl < 1000000)  strlcpy (a_proj->codesize, "e.elephantine" , LEN_LABEL);
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


