/*============================----beg-of-source---============================*/
#include  "polymnia.h"



tMY         my;


char      unit_answer [LEN_RECD] = "";

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/



/*====================------------------------------------====================*/
/*===----                         support functions                    ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

char*        /*--: return versioning information ---------[ ------ [ ------ ]-*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strcpy (t, "[tcc built  ]");
#elif  __GNUC__  > 0
   strcpy (t, "[gnu gcc    ]");
#elif  __CBANG__  > 0
   strcpy (t, "[cbang      ]");
#elif  __HEPH__  > 0
   strcpy (t, "[hephaestus ]");
#else
   strcpy (t, "[unknown    ]");
#endif
   snprintf (my.version, LEN_HUND, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return my.version;
}

char
PROG_vershow       (void)
{
   printf ("%s\n", PROG_version ());
   exit (0);
}



/*====================------------------------------------====================*/
/*===----                        program startup                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

char         /*--> pre-debugging code --------------------[ leaf   [ ------ ]-*/
PROG_preinit       (void)
{
   return 0;
}

char         /*-> very first setup -------------------[ shoot  [gz.633.201.0A]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG_init          (int a_argc, char *a_argv[])
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(run-time-config)----------------*/
   DEBUG_PROG   yLOG_note    ("initialize run-time settings");
   my.g_mode      = MODE_SEARCH;
   my.g_titles    = RPTG_NOTITLES;
   my.g_filter    = FILTER_NONE;
   /*---(filtering)----------------------*/
   DEBUG_PROG   yLOG_note    ("initialize global filtering");
   my.g_project [0]  = '\0';
   my.g_proj         = NULL;
   my.g_extern [0]   = '\0';
   my.g_hint   [0]   = '\0';
   /*---(files)--------------------------*/
   DEBUG_PROG   yLOG_note    ("initialize file pointers");
   my.f_code      = NULL;
   my.f_ctags     = NULL;
   my.f_cflow     = NULL;
   my.f_extern    = NULL;
   my.f_mystry    = NULL;
   my.f_vars      = NULL;
   my.f_units     = NULL;
   my.f_error     = stderr;
   /*---(global counts)------------------*/
   DEBUG_PROG   yLOG_note    ("initialize global counts");
   poly_cats_counts_clear (my.counts);
   /*---(initialization)-----------------*/
   DEBUG_PROG   yLOG_note    ("run sub initialization functions");
   poly_db_init      ();
   poly_proj_init    ();
   poly_files_init   ();
   poly_func_init    ();
   poly_extern_init  ();
   poly_vars_init    ();
   poly_proto_init   ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

#define  TWOARG  if (++i >= a_argc)  printf ("%s option requires an argument (%d)\n", a, --rc); else 

char         /*-> process the command line args ------[ ------ [gz.952.251.B4]*/ /*-[01.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG_args          (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           = 0;
   char       *a           = NULL;
   int         x_total     = 0;
   int         x_args      = 0;
   char        x_name      [LEN_RECD]   = "";
   char        t           [LEN_RECD]   = "";
   /*---(header)-------------------------*/
   DEBUG_TOPS  yLOG_enter   (__FUNCTION__);
   /*> FILE_rename ("");                                                              <*/
   /*---(process)------------------------*/
   for (i = 1; i < a_argc; ++i) {
      a = a_argv [i];
      ++x_total;
      if (a[0] == '@')  continue;
      DEBUG_ARGS  yLOG_info    ("cli arg", a);
      ++x_args;
      /*---(simple)----------------------*/
      if      (strcmp (a, "--version"  ) == 0)  PROG_vershow ();
      else if (strcmp (a, "--htags"    ) == 0)  my.g_mode   = MODE_HTAGS;
      else if (strcmp (a, "--about"    ) == 0)  my.g_mode   = MODE_ABOUT;
      else if (strcmp (a, "--dump"     ) == 0)  my.g_mode   = MODE_DUMP;
      else if (strcmp (a, "--report"   ) == 0)  my.g_mode   = MODE_RPTG;
      else if (strcmp (a, "--write"    ) == 0)  my.g_mode   = MODE_WRITE;
      else if (strcmp (a, "--update"   ) == 0)  my.g_mode   = MODE_UPDATE;
      else if (strcmp (a, "--projects" ) == 0)  my.g_mode   = MODE_PROJ;
      else if (strcmp (a, "--files"    ) == 0)  my.g_mode   = MODE_FILE;
      else if (strcmp (a, "--system"   ) == 0)  my.g_mode   = MODE_SYSTEM;
      else if (strcmp (a, "--vars"     ) == 0)  my.g_mode   = MODE_VARS;
      else if (strcmp (a, "--titles"   ) == 0)  my.g_titles = RPTG_TITLES;
      else if (strcmp (a, "--notitles" ) == 0)  my.g_titles = RPTG_NOTITLES;
      else if (strcmp (a, "--treeview" ) == 0)  my.g_titles = RPTG_TREEVIEW;
      else if (strcmp (a, "--debug"    ) == 0)  my.g_filter = FILTER_DEBUG;
      else if (strcmp (a, "--param"    ) == 0)  my.g_filter = FILTER_PARAMS;
      else if (strcmp (a, "--data"     ) == 0)  my.g_filter = FILTER_DATA;
      else if (strcmp (a, "--linux"    ) == 0)  my.g_filter = FILTER_LINUX;
      else if (strcmp (a, "--noerror"  ) == 0 && my.f_error == stderr)  my.f_error  = fopen ("/dev/null", "wt");
      /*---(special names)---------------*/
      else if (strcmp (a, "--database" ) == 0)  TWOARG rc = poly_db_name (a_argv [i], 'y');
      /*---(compound)--------------------*/
      else if (strcmp (a, "--remove" ) == 0) {
         my.g_mode = MODE_REMOVE;
         if (++i < a_argc)  strlcpy (my.g_project, a_argv [i], LEN_TITLE);
         else {
            DEBUG_TOPS  yLOG_note  ("project name not included");
            DEBUG_TOPS  yLOG_exitr (__FUNCTION__, -1);
            return -1;
         }
      }
      else if (strcmp (a, "--project") == 0) {
         if (++i < a_argc)  strlcpy (my.g_project, a_argv [i], LEN_TITLE);
         else {
            DEBUG_TOPS  yLOG_note  ("project name not included");
            DEBUG_TOPS  yLOG_exitr (__FUNCTION__, -1);
            return -1;
         }
      }
      else if (strcmp (a, "--extern" ) == 0) {
         my.g_mode = MODE_EXTERN;
         if (++i < a_argc)  strlcpy (my.g_extern, a_argv [i], LEN_TITLE);
         else {
            DEBUG_TOPS  yLOG_note  ("extern name not included");
            DEBUG_TOPS  yLOG_exitr (__FUNCTION__, -1);
            return -1;
         }
      }
      else if (strcmp (a, "--libuse" ) == 0) {
         my.g_mode = MODE_LIBUSE;
         if (++i < a_argc)  strlcpy (my.g_libuse, a_argv [i], LEN_TITLE);
         else {
            DEBUG_TOPS  yLOG_note  ("library name not included");
            DEBUG_TOPS  yLOG_exitr (__FUNCTION__, -1);
            return -1;
         }
      }
      else if (strcmp (a, "--hint"   ) == 0) {
         if (++i < a_argc)  strlcpy (my.g_hint, a_argv [i], LEN_TERSE);
         else {
            DEBUG_TOPS  yLOG_note  ("hint not included");
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
      /*> else if (a[0] != '-'                     )   strlcpy (x_name , a_argv[i]  , LEN_RECD);   <*/
      if (rc < 0)  break;
   }
   DEBUG_ARGS  yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS  yLOG_value  ("arguments" , x_args);
   if (x_args == 0) {
      DEBUG_ARGS  yLOG_note   ("no arguments identified");
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS  yLOG_exit  (__FUNCTION__);
   return rc;
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



/*====================------------------------------------====================*/
/*===----                         unknown                              ----===*/
/*====================------------------------------------====================*/
static void      o___OTHER___________________o (void) {;}

char
PROG_prepare            (void)
{
   my.COUNT_FILES = my.COUNT_FUNCS = my.COUNT_LINES = my.COUNT_EMPTY = my.COUNT_DOCS  = my.COUNT_DEBUG = my.COUNT_CODE  = my.COUNT_SLOCL = 0;
   return 0;
}

char
PROG_summarize          (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   tFUNC      *x_tag       = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_point   ("a_proj"    , a_proj);
   DEBUG_PROG   yLOG_info    ("->name"    , a_proj->name);
   /*---(prepare)------------------------*/
   if      (a_proj->COUNT_SLOCL < 100    )  strlcpy (a_proj->codesize, "u.micro        (< 100 slocl)"             , LEN_DESC);
   else if (a_proj->COUNT_SLOCL < 500    )  strlcpy (a_proj->codesize, "t.tiny         (100 - 499 slocl)"         , LEN_DESC);
   else if (a_proj->COUNT_SLOCL < 2000   )  strlcpy (a_proj->codesize, "s.small        (500 - 1,999 slocl)"       , LEN_DESC);
   else if (a_proj->COUNT_SLOCL < 10000  )  strlcpy (a_proj->codesize, "m.moderate     (2,000 - 9,999 slocl)"     , LEN_DESC);
   else if (a_proj->COUNT_SLOCL < 50000  )  strlcpy (a_proj->codesize, "l.large        (10,000 - 49,999 slocl)"   , LEN_DESC);
   else if (a_proj->COUNT_SLOCL < 250000 )  strlcpy (a_proj->codesize, "h.huge         (50,000 - 249,999 slocl)"  , LEN_DESC);
   else if (a_proj->COUNT_SLOCL < 1000000)  strlcpy (a_proj->codesize, "e.elephantine  (250,000 - 999,999 slocl)" , LEN_DESC);
   else                                     strlcpy (a_proj->codesize, "g.gargantuan   (>= 1,000,000 slocl)"      , LEN_DESC);
   /*---(output)-------------------------*/
   DEBUG_PROG   yLOG_note    ("review all tags and code");
   a_proj->funcs = 0;
   x_file = a_proj->head;
   while (x_file != NULL) {
      x_tag = x_file->head;
      while (x_tag != NULL)  {
         poly_cats_function (x_tag);
         x_tag = x_tag->next;
      }
      a_proj->funcs += x_file->count;
      x_file = x_file->next;
   }
   poly_proj_header (a_proj);
   poly_proto_units ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN________________o (void) {;}

char         /*-> shutdown program and free memory ---[ ------ [gz.422.001.03]*/ /*-[00.0000.111.!]-*/ /*-[--.---.---.--]-*/
PROG_end             (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(wrap-up)------------------------*/
   poly_proj_purge   ();
   poly_extern_wrap  ();
   /*---(remove global files)------------*/
   system ("rm -f htags.gcalls");
   system ("rm -f htags.flow");
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS   yLOGS_end    ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       unit testing                           ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

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
   char       *x_args [4]  = { "polymnia_unit", "@@kitchen", "@@nosort", "@@main_only" };
   yURG_logger (4, x_args);
   PROG_init   (4, x_args);
   yURG_urgs   (4, x_args);
   PROG_args   (4, x_args);
   PROG_begin  ();
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
PROG__unit_end       (void)
{
   PROG_end       ();
   return 0;
}


