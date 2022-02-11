/*============================----beg-of-source---============================*/
#include  "polymnia.h"



tMY         my;
tAUDIT      g_audit;


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
/*===----                       pre-initialization                     ----===*/
/*====================------------------------------------====================*/
static void      o___PREINIT_________________o (void) {;}


char
PROG_urgents            (int argc, char *argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(initialize)---------------------*/
   yURG_all_mute ();
   rc = yURG_logger  (argc, argv);
   rc = yURG_urgs    (argc, argv);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program startup                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

char
PROG_reset_yjobs   (void)
{
   my.run_as   = IAM_POLYMNIA;
   my.run_mode = ACT_NONE;
   strcpy (my.run_file, "");
   return 0;
}

char         /*-> very first setup -------------------[ shoot  [gz.633.201.0A]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG__init              (int a_argc, char *a_argv[])
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(yJOB config)--------------------*/
   PROG_reset_yjobs ();
   my.run_uid     = getuid ();
   my.runtime     = time (NULL);
   /*---(run-time-config)----------------*/
   DEBUG_PROG   yLOG_note    ("initialize run-time settings");
   my.g_mode      = POLY_NONE;
   my.g_scope     = POLY_PROJ;
   my.g_data      = POLY_DATA_NONE;
   my.g_unit      = 'y';
   my.g_rptg      = POLY_RPTG_NONE;
   my.g_titles    = RPTG_NOTITLES;
   my.g_filter    = FILTER_NONE;
   /*---(filtering)----------------------*/
   DEBUG_PROG   yLOG_note    ("initialize global filtering");
   my.g_projno       =   -1;
   my.g_proj         = NULL;
   my.g_projname [0] = '\0';
   my.g_fileno       =   -1;
   my.g_file         = NULL;
   my.g_filename [0] = '\0';
   my.g_extern [0]   = '\0';
   strlcpy (my.g_hint, "--", LEN_TERSE);
   /*---(files)--------------------------*/
   DEBUG_PROG   yLOG_note    ("initialize file pointers");
   my.f_code      = NULL;
   my.f_ctags     = NULL;
   my.f_cflow     = NULL;
   my.f_extern    = NULL;
   my.f_mystry    = NULL;
   my.f_vars      = NULL;
   my.f_units     = NULL;
   my.f_scrps     = NULL;
   my.f_error     = stderr;
   /*---(global counts)------------------*/
   DEBUG_PROG   yLOG_note    ("initialize global counts");
   poly_cats_counts_clear (my.counts);
   /*---(initialization)-----------------*/
   DEBUG_PROG   yLOG_note    ("run sub initialization functions");
   poly_db_init      ();
   poly_proj_init    ();
   poly_file_init    ();
   poly_func_init    ();
   poly_extern_init  ();
   poly_vars_init    ();
   poly_proto_init   ();
   poly_world_init   ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

#define  TWOARG  if (++i >= a_argc)  yURG_err (YURG_FATAL, "%s argument requires an additional string", a, --rc); else 

char         /*-> process the command line args ------[ ------ [gz.952.251.B4]*/ /*-[01.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG__args              (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           = 0;
   char       *a           = NULL;
   char       *b           = NULL;          /* next argument                  */
   int         x_total     = 0;
   int         x_args      = 0;
   char        x_name      [LEN_RECD]   = "";
   char        t           [LEN_RECD]   = "";
   int         x_proj      =    0;
   int         x_file      =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS  yLOG_enter   (__FUNCTION__);
   /*> FILE_rename ("");                                                              <*/
   if (a_argv > 0)  yJOBS_runas (&(my.run_as), a_argv [0]);
   /*---(process)------------------------*/
   for (i = 1; i < a_argc; ++i) {
      a = a_argv [i];
      if (a == NULL) {
         yURG_err ('f', "arg %d is NULL", i);
         DEBUG_TOPS   yLOG_note    ("FATAL, found a null argument, really bad news");
         DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ++x_total;
      if (a[0] == '@')  continue;
      DEBUG_ARGS  yLOG_info    ("cli arg", a);
      ++x_args;
      if (i < a_argc - 1)  b = a_argv [i + 1];
      else                 b = NULL;
      /*---(simple)----------------------*/
      /*> rc = poly_rptg_args (a);                                                    <*/
      /*> if (rc == 1)   continue;                                                    <*/
      /*---(simple)----------------------*/
      if      (strcmp (a, "--version"   ) == 0)  PROG_vershow ();
      /*---(complicated)-----------------*/
      else if (strcmp (a, "--htags"     ) == 0) { my.g_mode  = POLY_BOTH;  my.g_data = POLY_DATA_HTAGS;  my.g_scope = POLY_FULL;  my.g_rptg = POLY_RPTG_HTAGS;   }
      else if (strcmp (a, "--nounit"    ) == 0)   my.g_unit  = '-';
      /*---(system-wide)-----------------*/
      else if (strcmp (a, "--system"    ) == 0)  a = "--normal";
      else if (strcmp (a, "--csystem"   ) == 0)  a = "--cnormal";
      else if (strcmp (a, "--vsystem"   ) == 0)  a = "--vnormal";
      /*---(configuration)---------------*/
      else if (strcmp (a, "--database"  ) == 0)  TWOARG rc = poly_db_cli      (a_argv [i], 'y');
      else if (strcmp (a, "--world"     ) == 0)  TWOARG rc = poly_world_cli   (a_argv [i], 'y');
      else if (strcmp (a, "--external"  ) == 0)  TWOARG rc = poly_extern_cli  (a_argv [i], 'y');
      /*---(extern)----------------------*/
      /*> else if (strcmp (a, "--add-extern") == 0) { my.g_mode  = POLY_DATA;  my.g_data = POLY_DATA_YLIB;    }   <*/
      /*> else if (strcmp (a, "--rem-extern") == 0) { my.g_mode  = POLY_DATA;  my.g_data = POLY_DATA_REMOVE;  }   <*/
      /*---(reports)---------------------*/
      /*> else if (strcmp (a, "--projects"  ) == 0) { my.g_mode  = POLY_RPTG;  my.g_scope = POLY_PROJ;  my.g_rptg = POLY_RPTG_PROJS;   }   <*/
      /*> else if (strcmp (a, "--oneline"   ) == 0) { my.g_mode  = POLY_RPTG;  my.g_scope = POLY_PROJ;  my.g_rptg = POLY_RPTG_ONELINE; }   <*/
      /*> else if (strcmp (a, "--files"     ) == 0) { my.g_mode  = POLY_RPTG;  my.g_scope = POLY_FILE;  my.g_rptg = POLY_RPTG_FILES;   }   <*/
      /*> else if (strcmp (a, "--about"     ) == 0) { my.g_mode  = POLY_RPTG;  my.g_rptg = POLY_RPTG_ABOUT;   }   <*/
      /*> else if (strcmp (a, "--dump"      ) == 0) { my.g_mode  = POLY_RPTG;  my.g_rptg = POLY_RPTG_DUMP;    }   <*/
      /*> else if (strcmp (a, "--detail"    ) == 0) { my.g_mode  = POLY_RPTG;  my.g_rptg = POLY_RPTG_FUNC;    }   <*/
      /*---(others)----------------------*/
      /*> else if (strcmp (a, "--files"    ) == 0)  my.g_mode   = MODE_FILE;          <*/
      /*> else if (strcmp (a, "--vars"     ) == 0)  my.g_mode   = POLY_RPTG_VARS;     <*/
      else if (strcmp (a, "--titles"   ) == 0)  my.g_titles = RPTG_TITLES;
      else if (strcmp (a, "--notitles" ) == 0)  my.g_titles = RPTG_NOTITLES;
      else if (strcmp (a, "--treeview" ) == 0)  my.g_titles = RPTG_TREEVIEW;
      else if (strcmp (a, "--debug"    ) == 0)  my.g_filter = FILTER_DEBUG;
      else if (strcmp (a, "--param"    ) == 0)  my.g_filter = FILTER_PARAMS;
      else if (strcmp (a, "--data"     ) == 0)  my.g_filter = FILTER_DATA;
      else if (strcmp (a, "--linux"    ) == 0)  my.g_filter = FILTER_LINUX;
      /*---(filtering)-------------------*/
      else if (strcmp (a, "--project"   ) == 0)  TWOARG rc = poly_proj_cli    (a_argv [i], 'y');
      else if (strcmp (a, "--hint"      ) == 0)  TWOARG rc = poly_func_cli    (a_argv [i], 'y');
      /*> else if (strcmp (a, "--extern"   ) == 0)  TWOARG rc = poly_extern_name (a_argv [i], 'y');   <*/
      /*> else if (strcmp (a, "--ylib"     ) == 0)  TWOARG rc = poly_ylib_name   (a_argv [i], 'y');   <*/
      /*---(compound)--------------------*/
      else if (strcmp (a, "--extern" ) == 0) {
         my.g_mode = POLY_RPTG_EXTERN;
         if (++i < a_argc)  strlcpy (my.g_extern, a_argv [i], LEN_TITLE);
         else {
            DEBUG_TOPS  yLOG_note  ("extern name not included");
            DEBUG_TOPS  yLOG_exitr (__FUNCTION__, -1);
            return -1;
         }
      }
      else if (strcmp (a, "--libuse" ) == 0) {
         my.g_mode = POLY_RPTG_YLIB;
         if (++i < a_argc)  strlcpy (my.g_libuse, a_argv [i], LEN_TITLE);
         else {
            DEBUG_TOPS  yLOG_note  ("library name not included");
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
      else if (a[0] != '-'                     ) {
         c = atoi (a_argv [i]);
         if (c > 0) {
            if      (x_proj == 0)   my.g_projno = c - 1;
            else if (x_file == 0)   my.g_fileno = c - 1;
         } else {
            if      (my.g_projname [0] == '\0')   strlcpy (my.g_projname, a_argv [i], LEN_LABEL);
            else if (my.g_filename [0] == '\0')   strlcpy (my.g_filename, a_argv [i], LEN_LABEL);
         }
      }
      else {
         rc = yJOBS_args_handle (&(my.run_as), &(my.run_mode), my.run_file, &i, a, b);
         if (rc < 0) {
            DEBUG_TOPS  yLOG_note  ("argument not understood");
            DEBUG_TOPS  yLOG_exitr (__FUNCTION__, -1);
            return -1;
         }
      }
      /*> printf ("GLOBAL %c, %c, %c\n", my.g_mode, my.g_scope, my.g_rptg);           <*/
      if (rc < 0)  break;
   }
   DEBUG_ARGS  yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS  yLOG_value  ("arguments" , x_args);
   if (x_args == 0) {
      DEBUG_ARGS  yLOG_note   ("no arguments identified");
   }
   /*> printf ("FINAL  %c, %c, %c\n", my.g_mode, my.g_scope, my.g_rptg);              <*/
   yJOBS_final (my.run_uid);
   /*---(complete)-----------------------*/
   DEBUG_TOPS  yLOG_exit  (__FUNCTION__);
   return rc;
}

char         /*-> initialize program and variables ---[ ------ [gz.741.041.07]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG__begin             (void)
{
   /*---(header)-------------------------*/
   DEBUG_TOPS  yLOG_enter   (__FUNCTION__);
   /*---(prepare files)------------------*/
   char        rc          =    0;
   rc = poly_extern_load ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS  yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_startup            (int argc, char *argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   yURG_stage_check (YURG_BEG);
   DEBUG_TOPS  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   if (rc >= 0) {
      rc = PROG__init    (argc, argv);
      DEBUG_TOPS  yLOG_value   ("init"      , rc);
   }
   /*---(arguments)----------------------*/
   if (rc >= 0) {
      rc = PROG__args    (argc, argv);
      DEBUG_TOPS  yLOG_value   ("args"      , rc);
   }
   /*---(begin)--------------------------*/
   if (rc >= 0) {
      rc = PROG__begin   ();
      DEBUG_TOPS  yLOG_value   ("args"      , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS  yLOG_exit  (__FUNCTION__);
   yURG_stage_check (YURG_MID);
   return rc;
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
   poly_units_by_func ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      action dispatching                      ----===*/
/*====================------------------------------------====================*/
static void      o___DISPATCH________________o (void) {;}

char
PROG__stats             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(call action)--------------------*/
   rc = poly_action__read    ();
   if (rc < 0)  {
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(display)------------------------*/
   printf ("#!/usr/local/bin/polymnia --stats\n");
   printf ("db     å%sæ\n" , my.n_db);
   printf ("name   å%sæ\n" , g_audit.name);
   printf ("ver    å%sæ\n" , g_audit.vernum);
   strl4main (g_audit.COUNT_PROJS, t , 0, 'c', '-', LEN_LABEL);
   printf ("projs  %7.7s\n", t);
   strl4main (g_audit.COUNT_FILES, t , 0, 'c', '-', LEN_LABEL);
   printf ("files  %7.7s\n", t);
   strl4main (g_audit.COUNT_FUNCS, t , 0, 'c', '-', LEN_LABEL);
   printf ("funcs  %7.7s\n", t);
   strl4main (g_audit.COUNT_YLIBS, t , 0, 'c', '-', LEN_LABEL);
   printf ("ylibs  %7.7s\n", t);
   strl4main (g_audit.COUNT_LINES, t , 0, 'c', '-', LEN_LABEL);
   printf ("lines  %7.7s\n", t);
   strl4main (g_audit.COUNT_EMPTY, t , 0, 'c', '-', LEN_LABEL);
   printf ("empty  %7.7s\n", t);
   strl4main (g_audit.COUNT_DOCS , t , 0, 'c', '-', LEN_LABEL);
   printf ("docs   %7.7s\n", t);
   strl4main (g_audit.COUNT_DEBUG, t , 0, 'c', '-', LEN_LABEL);
   printf ("debug  %7.7s\n", t);
   strl4main (g_audit.COUNT_CODE , t , 0, 'c', '-', LEN_LABEL);
   printf ("code   %7.7s\n", t);
   strl4main (g_audit.COUNT_SLOCL, t , 0, 'c', '-', LEN_LABEL);
   printf ("slocl  %7.7s\n", t);
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG__verify            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(title)--------------------------*/
   yURG_msg ('>', "  option --vverify, check current project suitability for usage");
   yURG_msg (' ', "");
   /*---(call action)--------------------*/
   rc = poly_action__here      ();
   /*---(failure)------------------------*/
   if (rc < 0) {
      yURG_msg (' ', "");
      if (my.run_mode == ACT_CVERIFY )   yURG_msg_live ();
      if (my.run_mode == ACT_CVERIFY )   yURG_msg ('>', "FAILED, project could not be analyzed, run --vverify to identify reasons");
      if (my.run_mode == ACT_VVERIFY )   yURG_msg ('>', "FAILED, project could not be analyzed, the reasons are shown above");
      if (my.run_mode == ACT_CVERIFY )   yURG_msg_mute ();
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(success)------------------------*/
   yURG_msg (' ', "");
   IF_CONFIRM  yURG_msg_live ();
   yURG_msg ('>', "SUCCESS, project is suitable for inclusion in database");
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG__register          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(title)--------------------------*/
   IF_VERBOSE   yURG_msg ('>', "  option --vregister, analyze current project and add to registry");
   IF_VERBOSE   yURG_msg (' ', "");
   /*---(call action)--------------------*/
   rc = poly_world_register   ();
   /*---(failure)------------------------*/
   if (rc < 0) {
      yURG_msg (' ', "");
      if (my.run_mode == ACT_CREGISTER)  yURG_msg_live ();
      if (my.run_mode == ACT_CREGISTER)  yURG_msg ('>', "FAILED, project could not be registered, run --vregister to identify reasons");
      if (my.run_mode == ACT_VREGISTER)  yURG_msg ('>', "FAILED, project could not be registered, the reasons are shown above");
      if (my.run_mode == ACT_CREGISTER)  yURG_msg_mute ();
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(success)------------------------*/
   yURG_msg (' ', "");
   IF_CONFIRM  yURG_msg_live ();
   if (rc == 0)  yURG_msg ('>', "SUCCESS, project was registered in the database");
   else          yURG_msg ('>', "WARNING, project was already registered in the database");
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG__update            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(title)--------------------------*/
   IF_VERBOSE   yURG_msg ('>', "  option --vupdate, analyze current project and add to database");
   IF_VERBOSE   yURG_msg (' ', "");
   /*---(call action)--------------------*/
   rc = poly_action_update    ();
   /*---(failure)------------------------*/
   if (rc < 0) {
      yURG_msg (' ', "");
      if (my.run_mode == ACT_CUPDATE )   yURG_msg_live ();
      if (my.run_mode == ACT_CUPDATE )   yURG_msg ('>', "FAILED, could not update database, run --vupdate to identify reasons");
      if (my.run_mode == ACT_VUPDATE )   yURG_msg ('>', "FAILED, but could not update database, the reasons are shown above");
      if (my.run_mode == ACT_CUPDATE )   yURG_msg_mute ();
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(success)------------------------*/
   yURG_msg (' ', "");
   IF_CONFIRM  yURG_msg_live ();
   yURG_msg ('>', "SUCCESS, project was updated in the database");
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG__install           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(title)--------------------------*/
   IF_VERBOSE   yURG_msg ('>', "  option --vinstall, analyze current project and add to registry plus database");
   IF_VERBOSE   yURG_msg (' ', "");
   /*---(call action)--------------------*/
   rc = poly_world_register   ();
   /*---(failure)------------------------*/
   if (rc < 0) {
      yURG_msg (' ', "");
      if (my.run_mode == ACT_CINSTALL)   yURG_msg_live ();
      if (my.run_mode == ACT_CINSTALL)   yURG_msg ('>', "FAILED, project could not be registered, run --vinstall to identify reasons");
      if (my.run_mode == ACT_VINSTALL)   yURG_msg ('>', "FAILED, project could not be registered, the reasons are shown above");
      if (my.run_mode == ACT_CINSTALL)   yURG_msg_mute ();
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(call action)--------------------*/
   yURG_msg (' ', "");
   rc = poly_action_update    ();
   /*---(failure)------------------------*/
   if (rc < 0) {
      yURG_msg (' ', "");
      if (my.run_mode == ACT_CINSTALL)   yURG_msg_live ();
      if (my.run_mode == ACT_CINSTALL)   yURG_msg ('>', "FAILED, project registered, but could not update database, run --vinstall to identify reasons");
      if (my.run_mode == ACT_VINSTALL)   yURG_msg ('>', "FAILED, project registered, but could not update database, the reasons are shown above");
      if (my.run_mode == ACT_CINSTALL)   yURG_msg_mute ();
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(success)------------------------*/
   yURG_msg (' ', "");
   IF_CONFIRM  yURG_msg_live ();
   yURG_msg ('>', "SUCCESS, project was both registered and updated in the database");
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG__withdraw          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(title)--------------------------*/
   IF_VERBOSE   yURG_msg ('>', "  option --vwithdraw, remove named project from the to registry");
   IF_VERBOSE   yURG_msg (' ', "");
   /*---(call action)--------------------*/
   strlcpy (my.g_projname, my.run_file, LEN_LABEL);
   rc = poly_world_unregister ();
   /*---(failure)------------------------*/
   if (rc < 0) {
      yURG_msg (' ', "");
      if (my.run_mode == ACT_CWITHDRAW)  yURG_msg_live ();
      if (my.run_mode == ACT_CWITHDRAW)  yURG_msg ('>', "FAILED, project could not be unregistered, run --vwithdraw to identify reasons");
      if (my.run_mode == ACT_VWITHDRAW)  yURG_msg ('>', "FAILED, project could not be unregistered, the reasons are shown above");
      if (my.run_mode == ACT_CWITHDRAW)  yURG_msg_mute ();
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(success)------------------------*/
   yURG_msg (' ', "");
   IF_CONFIRM  yURG_msg_live ();
   if (rc == 0)  yURG_msg ('>', "SUCCESS, project was removed from the registry");
   else          yURG_msg ('>', "WARNING, project was not in the registry, nothing to do");
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG__clear             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(title)--------------------------*/
   IF_VERBOSE   yURG_msg ('>', "  option --vclear, remove named project from the database");
   IF_VERBOSE   yURG_msg (' ', "");
   /*---(call action)--------------------*/
   strlcpy (my.g_projname, my.run_file, LEN_LABEL);
   rc = poly_action_remove    ();
   /*---(failure)------------------------*/
   if (rc < 0) {
      yURG_msg (' ', "");
      if (my.run_mode == ACT_CCLEAR  )   yURG_msg_live ();
      if (my.run_mode == ACT_CCLEAR  )   yURG_msg ('>', "FAILED, project could not be removed, run --vclear to identify reasons");
      if (my.run_mode == ACT_VCLEAR  )   yURG_msg ('>', "FAILED, project could not be removed, the reasons are shown above");
      if (my.run_mode == ACT_CCLEAR  )   yURG_msg_mute ();
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(success)------------------------*/
   yURG_msg (' ', "");
   IF_CONFIRM  yURG_msg_live ();
   if (rc == 0)  yURG_msg ('>', "SUCCESS, project was removed from the database");
   else          yURG_msg ('>', "WARNING, project was not in database, nothing to do");
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG__remove            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(title)--------------------------*/
   IF_VERBOSE   yURG_msg ('>', "  option --vremove, remove named project from database and registry");
   IF_VERBOSE   yURG_msg (' ', "");
   /*---(call action)--------------------*/
   strlcpy (my.g_projname, my.run_file, LEN_LABEL);
   rc = poly_world_unregister ();
   /*---(failure)------------------------*/
   if (rc < 0) {
      yURG_msg (' ', "");
      if (my.run_mode == ACT_CREMOVE )   yURG_msg_live ();
      if (my.run_mode == ACT_CREMOVE )   yURG_msg ('>', "FAILED, project could not be unregistered, run --vremove to identify reasons");
      if (my.run_mode == ACT_VREMOVE )   yURG_msg ('>', "FAILED, project could not be unregistered, the reasons are shown above");
      if (my.run_mode == ACT_CREMOVE )   yURG_msg_mute ();
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(call action)--------------------*/
   yURG_msg (' ', "");
   rc = poly_action_remove    ();
   /*---(failure)------------------------*/
   if (rc < 0) {
      yURG_msg (' ', "");
      if (my.run_mode == ACT_CREMOVE )   yURG_msg_live ();
      if (my.run_mode == ACT_CREMOVE )   yURG_msg ('>', "FAILED, project could not be removed, run --vremove to identify reasons");
      if (my.run_mode == ACT_VREMOVE )   yURG_msg ('>', "FAILED, project could not be removed, the reasons are shown above");
      if (my.run_mode == ACT_CREMOVE )   yURG_msg_mute ();
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(success)------------------------*/
   yURG_msg (' ', "");
   IF_CONFIRM  yURG_msg_live ();
   if (rc == 0)  yURG_msg ('>', "SUCCESS, project was removed from database and registry");
   else          yURG_msg ('>', "WARNING, project was not in database, nothing to do");
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG__system            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(title)--------------------------*/
   IF_CONFIRM {
      yURG_msg_live ();
      yURG_msg ('>', "%s", P_ONELINE);
      yURG_msg ('>', "  option --cnormal, update data with all projects from registry");
      yURG_msg_mute ();
   }
   IF_VERBOSE   yURG_msg ('>', "  option --vnormal, update data with all projects from registry");
   IF_VERBOSE   yURG_msg (' ', "");
   /*---(call action)--------------------*/
   rc = poly_world_system     ();
   /*---(failure)------------------------*/
   if (rc < 0) {
      yURG_msg (' ', "");
      if (my.run_mode == ACT_CNORMAL )   yURG_msg_live ();
      if (my.run_mode == ACT_CNORMAL )   yURG_msg ('>', "FAILED, system update was not completed, run --vnormal to identify reasons");
      if (my.run_mode == ACT_VNORMAL )   yURG_msg ('>', "FAILED, system update was not completed, the reasons are shown above");
      if (my.run_mode == ACT_CNORMAL )   yURG_msg_mute ();
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(success)------------------------*/
   yURG_msg (' ', "");
   IF_CONFIRM  yURG_msg_live ();
   yURG_msg ('>', "SUCCESS, system update was completed for all registry projects");
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_dispatch           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(TEMPORARY)----------------------*/
   if (my.g_data == POLY_DATA_HTAGS) {
      rc = poly_action_htags     ();
      return 0;
   }
   /*---(title)--------------------------*/
   IF_VERBOSE   yURG_msg ('>', "%s", P_ONELINE);
   /*---(route action)-------------------*/
   --rce;  switch (my.run_mode) {
      /*---(basic)-----------------------*/
   case ACT_STATS       :
      rc = PROG__stats    ();
      break;
      /*---(incomming)-------------------*/
   case CASE_VERIFY     :
      rc = PROG__verify   ();
      break;
   case CASE_REGISTER   :
      rc = PROG__register ();
      break;
   case CASE_UPDATE     :
      rc = PROG__update   ();
      break;
   case CASE_INSTALL    :
      rc = PROG__install  ();
      break;
      /*---(outgoing)--------------------*/
   case CASE_WITHDRAW   :
      rc = PROG__withdraw ();
      break;
   case CASE_CLEAR      :
      rc = PROG__clear    ();
      break;
   case CASE_REMOVE     :
      rc = PROG__remove   ();
      break;
      /*---(central)---------------------*/
   case CASE_REPORT     :
      rc = poly_rptg_dispatch ();
      break;
   case CASE_AUDIT      :
      break;
      /*---(execute)---------------------*/
   case CASE_NORMAL     :
   case CASE_STRICT     :
      rc = PROG__system   ();
      break;
      /*---(trouble)---------------------*/
   default              :
      rc = rce;
      break;
   }
   /*---(cut-off)------------------------*/
   yURG_all_mute ();
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return rc;
}

char
PROG_dispatch_OLD       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_char    ("g_mode"    , my.g_mode);
   /*---(data handling)------------------*/
   if (my.g_mode == POLY_DATA || my.g_mode == POLY_BOTH) {
      DEBUG_PROG   yLOG_char    ("g_data"    , my.g_data);
      switch (my.g_data) {
      case POLY_DATA_HTAGS  :  rc = poly_action_htags     ();   break;
      case POLY_DATA_NEW    :  rc = poly_action_new       ();   break;
      case POLY_DATA_UPDATE :  rc = poly_action_update    ();   break;
      case POLY_DATA_REMOVE :  rc = poly_action_remove    ();   break;
      case POLY_DATA_REG    :  rc = poly_world_register   ();   break;
      case POLY_DATA_UNREG  :  rc = poly_world_unregister ();   break;
      case POLY_DATA_SYSTEM :  rc = poly_world_system     ();   break;
      }
   }
   /*---(reporting)----------------------*/
   if (my.g_mode == POLY_RPTG || my.g_mode == POLY_BOTH) {
      rc = poly_db_read       ();
      if (my.g_projno >= 0) {
         rc     = poly_proj_by_index (my.g_projno, &(my.g_proj));
         strlcpy (my.g_projname, my.g_proj->name, LEN_LABEL);
         /*> printf ("project %2d, %p, %s\n", my.g_projno, my.g_proj, my.g_projname);   <*/
      }
      if (my.g_fileno >= 0) {
         rc     = poly_file_by_proj_index (my.g_proj, my.g_fileno, &(my.g_file));
         strlcpy (my.g_filename, my.g_file->name, LEN_LABEL);
         /*> printf ("file    %2d, %p, %s\n", my.g_fileno, my.g_proj, my.g_projname);   <*/
      }
      DEBUG_PROG   yLOG_char    ("g_rptg"    , my.g_rptg);
      if      (my.g_scope == POLY_PROJ)    rc = poly_rptg_projects ();
      else if (my.g_scope == POLY_FILE)    rc = poly_rptg_files    ();
      else if (my.g_scope == POLY_YLIB)    rc = poly_rptg_ylibs    ();
      /*> else {                                                                                 <* 
       *>    switch (my.g_rptg) {                                                                <* 
       *>    case POLY_RPTG_PROJS   : case POLY_RPTG_ONELINE :                                   <* 
       *>       rc = poly_rptg_projects ();                                                      <* 
       *>       break;                                                                           <* 
       *>    case POLY_RPTG_FUNC    :                                                            <* 
       *>       rc = poly_action_detail ();                                                      <* 
       *>       break;                                                                           <* 
       *>    case POLY_RPTG_ABOUT   :                                                            <* 
       *>       rc = poly_action_about ();                                                       <* 
       *>       break;                                                                           <* 
       *>    case POLY_RPTG_DUMP   :                                                             <* 
       *>       DEBUG_TOPS   yLOG_note    ("rptg processing, file read, nor htags or write");    <* 
       *>       rc = poly_db_read     ();                                                        <* 
       *>       rc = poly_rptg_dump   ();                                                        <* 
       *>       break;                                                                           <* 
       *>    case MODE_SEARCH :                                                                  <* 
       *>       DEBUG_TOPS   yLOG_note    ("search processing, read, but no htags or write");    <* 
       *>       rc = poly_action_search ();                                                      <* 
       *>       break;                                                                           <* 
       *>    case MODE_FILE   :                                                                  <* 
       *>       DEBUG_TOPS   yLOG_note    ("project processing, read, but no htags or write");   <* 
       *>       rc = poly_db_read     ();                                                        <* 
       *>       rc = poly_rptg_proj   ();                                                        <* 
       *>       break;                                                                           <* 
       *>    case POLY_RPTG_EXTERN :                                                             <* 
       *>       DEBUG_TOPS   yLOG_note    ("extern processing, read, but no htags or write");    <* 
       *>       rc = poly_action_extern ();                                                      <* 
       *>       break;                                                                           <* 
       *>    case POLY_RPTG_YLIB   :                                                             <* 
       *>       DEBUG_TOPS   yLOG_note    ("libuse processing, read, but no htags or write");    <* 
       *>       rc = poly_action_libuse ();                                                      <* 
       *>       break;                                                                           <* 
       *>    case POLY_RPTG_VARS   :                                                             <* 
       *>       DEBUG_TOPS   yLOG_note    ("htag gathering, then var/macros analysis");          <* 
       *>       rc = poly_action_vars ();                                                        <* 
       *>       break;                                                                           <* 
       *>    }                                                                                   <* 
       *> }                                                                                      <*/
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return rc;
}


/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN________________o (void) {;}

char         /*-> shutdown program and free memory ---[ ------ [gz.422.001.03]*/ /*-[00.0000.111.!]-*/ /*-[--.---.---.--]-*/
PROG__end               (void)
{
   /*---(header)-------------------------*/
   yURG_stage_check (YURG_END);
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(wrap-up)------------------------*/
   poly_proj_purge   ();
   poly_extern_wrap  ();
   poly_world_wrap   ();
   /*---(remove global files)------------*/
   system ("rm -f htags.gcalls");
   system ("rm -f htags.flow");
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS   yLOGS_end    ();
   return 0;
}

char         /*-> shutdown program and free memory ---[ ------ [gz.422.001.03]*/ /*-[00.0000.111.!]-*/ /*-[--.---.---.--]-*/
PROG_shutdown          (void)
{
   return PROG__end ();
}



/*====================------------------------------------====================*/
/*===----                       unit testing                           ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.#]-*/ /*-[--.---.---.--]-*/
PROG__unit_quiet   (void)
{
   char        x_argc      = 1;
   char       *x_args [1]  = { "polymnia" };
   PROG_urgents (x_argc, x_args);
   PROG_startup (x_argc, x_args);
   return 0;
}

char         /*-> set up programgents/debugging ------[ light  [uz.320.011.05]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
PROG__unit_loud      (void)
{
   char        x_argc      = 4;
   char       *x_args [4]  = { "polymnia_unit", "@@kitchen", "@@nosort", "@@mid" };
   PROG_urgents (x_argc, x_args);
   /*> yURG_name  ("mid"          , YURG_ON);                                         <*/
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("yexec"        , YURG_ON);
   PROG_startup (x_argc, x_args);
   return 0;
}

char         /*-> set up program urgents/debugging ---[ light  [uz.210.001.01]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
PROG__unit_end       (void)
{
   PROG_shutdown  ();
   return 0;
}

char*        /*-[ unit test accessor ]---------------------[us2---·A-7·6--·B21-]¬[----·T-B1H---·---·----]¬[---·------]*/
prog__unit              (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        s           [LEN_TITLE] = " 0[]";
   char        t           [LEN_TITLE] = " 0[]";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "PROG unit        : question unknown");
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "mode"    )        == 0) {
      yJOBS_iam  (my.run_as  , s);
      yJOBS_mode (my.run_mode, t);
      snprintf (unit_answer, LEN_RECD, "PROG mode        : iam (%c) %-18.18s, run (%c) %-18.18s, å%sæ", my.run_as, s, my.run_mode, t, my.run_file);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

