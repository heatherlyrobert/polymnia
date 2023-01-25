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
   DEBUG_PROG  yLOG_char    ("run_as"    , my.run_as);
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
   my.g_funcname [0] = '\0';
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
   /*> poly_world_init   ();                                                          <*/
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
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*> FILE_rename ("");                                                              <*/
   rc = yJOBS_runas (a_argv [0], &(my.run_as), P_FOCUS, P_NICHE, P_SUBJECT, P_PURPOSE, P_NAMESAKE, P_HERITAGE, P_IMAGERY, P_REASON, P_ONELINE, P_HOMEDIR, P_BASENAME, P_FULLPATH, P_SUFFIX, P_CONTENT, P_SYSTEM, P_LANGUAGE, P_CODESIZE, P_DEPENDS, P_AUTHOR, P_CREATED, P_VERMAJOR, P_VERMINOR, P_VERNUM, P_VERTXT, P_ITCH, P_EXISTS, P_AVOID, P_SCRATCH, P_SUMMARY, P_ASSUME, P_GREEK, NULL);
   DEBUG_PROG  yLOG_value   ("runas"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG  yLOG_char    ("run_as"    , my.run_as);
   /*---(process)------------------------*/
   for (i = 1; i < a_argc; ++i) {
      a = a_argv [i];
      if (a == NULL) {
         yURG_err ('f', "arg %d is NULL", i);
         DEBUG_PROG   yLOG_note    ("FATAL, found a null argument, really bad news");
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ++x_total;
      if (a[0] == '@')  continue;
      DEBUG_ARGS  yLOG_info    ("cli arg", a);
      ++x_args;
      if (i < a_argc - 1)  b = a_argv [i + 1];
      else                 b = NULL;
      /*---(standards first)-------------*/
      if (strcmp (a, "--htags"     ) == 0)  a = "--local";
      rc = yJOBS_argument (&i, a, b, &(my.run_as), &(my.run_mode), my.run_file);
      if (rc < 0) {
         DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
         return rce;
      }
      if (rc == 1)  continue;
      /*> rc = poly_rptg_args (a);                                                    <*/
      /*> if (rc == 1)   continue;                                                    <*/
      /*---(simple)----------------------*/
      if      (strcmp (a, "--version"   ) == 0)  PROG_vershow ();
      /*---(complicated)-----------------*/
      /*> else if (strcmp (a, "--htags"     ) == 0) { my.g_mode  = POLY_BOTH;  my.g_data = POLY_DATA_HTAGS;  my.g_scope = POLY_FULL;  my.g_rptg = POLY_RPTG_HTAGS;   }   <*/
      else if (strcmp (a, "--nounit"    ) == 0)   my.g_unit  = '-';
      /*---(configuration)---------------*/
      /*> else if (strcmp (a, "--local"     ) == 0)  rc = poly_db_cli  ("polymnia_local.db", 'y');   <*/
      else if (strcmp (a, "--database"  ) == 0)  TWOARG rc = poly_db_cli      (a_argv [i], 'y');
      /*> else if (strcmp (a, "--world"     ) == 0)  TWOARG rc = poly_world_cli   (a_argv [i], 'y');   <*/
      else if (strcmp (a, "--external"  ) == 0)  TWOARG rc = poly_extern_cli  (a_argv [i], 'y');
      /*---(others)----------------------*/
      else if (strcmp (a, "--treeview" ) == 0)  my.g_titles = RPTG_TREEVIEW;
      else if (strcmp (a, "--debug"    ) == 0)  my.g_filter = FILTER_DEBUG;
      else if (strcmp (a, "--param"    ) == 0)  my.g_filter = FILTER_PARAMS;
      else if (strcmp (a, "--data"     ) == 0)  my.g_filter = FILTER_DATA;
      else if (strcmp (a, "--linux"    ) == 0)  my.g_filter = FILTER_LINUX;
      /*---(filtering)-------------------*/
      else if (strcmp (a, "--project"   ) == 0)  TWOARG rc = poly_proj_cli    (a_argv [i], 'y');
      else if (strcmp (a, "--function"  ) == 0)  TWOARG rc = poly_func_cli_name (a_argv [i], 'y');
      else if (strcmp (a, "--hint"      ) == 0)  TWOARG rc = poly_func_cli    (a_argv [i], 'y');
      /*> else if (strcmp (a, "--extern"   ) == 0)  TWOARG rc = poly_extern_name (a_argv [i], 'y');   <*/
      /*> else if (strcmp (a, "--ylib"     ) == 0)  TWOARG rc = poly_ylib_name   (a_argv [i], 'y');   <*/
      /*---(compound)--------------------*/
      else if (strcmp (a, "--extern" ) == 0) {
         my.g_mode = POLY_RPTG_EXTERN;
         if (++i < a_argc)  strlcpy (my.g_extern, a_argv [i], LEN_TITLE);
         else {
            DEBUG_PROG  yLOG_note  ("extern name not included");
            DEBUG_PROG  yLOG_exitr (__FUNCTION__, -1);
            return -1;
         }
      }
      else if (strcmp (a, "--libuse" ) == 0) {
         my.g_mode = POLY_RPTG_YLIB;
         if (++i < a_argc)  strlcpy (my.g_libuse, a_argv [i], LEN_TITLE);
         else {
            DEBUG_PROG  yLOG_note  ("library name not included");
            DEBUG_PROG  yLOG_exitr (__FUNCTION__, -1);
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
         DEBUG_PROG  yLOG_note  ("argument not understood");
         DEBUG_PROG  yLOG_exitr (__FUNCTION__, -1);
         return -1;
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
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return rc;
}

char         /*-> initialize program and variables ---[ ------ [gz.741.041.07]*/ /*-[00.0000.121.!]-*/ /*-[--.---.---.--]-*/
PROG__begin             (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(prepare files)------------------*/
   char        rc          =    0;
   rc = poly_extern_load ();
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
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
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   if (rc >= 0) {
      rc = PROG__init    (argc, argv);
      DEBUG_PROG  yLOG_value   ("init"      , rc);
   }
   /*---(arguments)----------------------*/
   if (rc >= 0) {
      rc = PROG__args    (argc, argv);
      DEBUG_PROG  yLOG_value   ("args"      , rc);
   }
   /*---(begin)--------------------------*/
   if (rc >= 0) {
      rc = PROG__begin   ();
      DEBUG_PROG  yLOG_value   ("args"      , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
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
   /*> rc = poly_action__read    ();                                                  <* 
    *> if (rc < 0)  {                                                                 <* 
    *>    DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                              <* 
    *>    return rc;                                                                  <* 
    *> }                                                                              <*/
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

/*> char                                                                                                                                   <* 
 *> PROG__verify            (void)                                                                                                         <* 
 *> {                                                                                                                                      <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                            <* 
 *>    char        rce         =  -10;                                                                                                     <* 
 *>    char        rc          =    0;                                                                                                     <* 
 *>    /+---(header)-------------------------+/                                                                                            <* 
 *>    DEBUG_PROG    yLOG_enter   (__FUNCTION__);                                                                                          <* 
 *>    /+---(title)--------------------------+/                                                                                            <* 
 *>    yURG_msg ('>', "  option --vverify, check current project suitability for usage");                                                  <* 
 *>    yURG_msg (' ', "");                                                                                                                 <* 
 *>    /+---(call action)--------------------+/                                                                                            <* 
 *>    rc = poly_action__here      ();                                                                                                     <* 
 *>    /+---(failure)------------------------+/                                                                                            <* 
 *>    if (rc < 0) {                                                                                                                       <* 
 *>       yURG_msg (' ', "");                                                                                                              <* 
 *>       if (my.run_mode == ACT_CVERIFY )   yURG_msg_live ();                                                                             <* 
 *>       if (my.run_mode == ACT_CVERIFY )   yURG_msg ('>', "FAILED, project could not be analyzed, run --vverify to identify reasons");   <* 
 *>       if (my.run_mode == ACT_VVERIFY )   yURG_msg ('>', "FAILED, project could not be analyzed, the reasons are shown above");         <* 
 *>       if (my.run_mode == ACT_CVERIFY )   yURG_msg_mute ();                                                                             <* 
 *>       DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                                                                                   <* 
 *>       return rc;                                                                                                                       <* 
 *>    }                                                                                                                                   <* 
 *>    /+---(success)------------------------+/                                                                                            <* 
 *>    yURG_msg (' ', "");                                                                                                                 <* 
 *>    IF_CONFIRM  yURG_msg_live ();                                                                                                       <* 
 *>    yURG_msg ('>', "SUCCESS, project is suitable for inclusion in database");                                                           <* 
 *>    /+---(complete)-----------------------+/                                                                                            <* 
 *>    DEBUG_PROG    yLOG_exit    (__FUNCTION__);                                                                                          <* 
 *>    return rc;                                                                                                                          <* 
 *> }                                                                                                                                      <*/

/*> char                                                                                                                                       <* 
 *> PROG__register          (void)                                                                                                             <* 
 *> {                                                                                                                                          <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                <* 
 *>    char        rce         =  -10;                                                                                                         <* 
 *>    char        rc          =    0;                                                                                                         <* 
 *>    /+---(header)-------------------------+/                                                                                                <* 
 *>    DEBUG_PROG    yLOG_enter   (__FUNCTION__);                                                                                              <* 
 *>    /+---(title)--------------------------+/                                                                                                <* 
 *>    IF_VERBOSE   yURG_msg ('>', "  option --vregister, analyze current project and add to registry");                                       <* 
 *>    IF_VERBOSE   yURG_msg (' ', "");                                                                                                        <* 
 *>    /+---(call action)--------------------+/                                                                                                <* 
 *>    /+> rc = poly_world_register   ();                                                 <+/                                                  <* 
 *>    /+---(failure)------------------------+/                                                                                                <* 
 *>    if (rc < 0) {                                                                                                                           <* 
 *>       yURG_msg (' ', "");                                                                                                                  <* 
 *>       if (my.run_mode == ACT_CREGISTER)  yURG_msg_live ();                                                                                 <* 
 *>       if (my.run_mode == ACT_CREGISTER)  yURG_msg ('>', "FAILED, project could not be registered, run --vregister to identify reasons");   <* 
 *>       if (my.run_mode == ACT_VREGISTER)  yURG_msg ('>', "FAILED, project could not be registered, the reasons are shown above");           <* 
 *>       if (my.run_mode == ACT_CREGISTER)  yURG_msg_mute ();                                                                                 <* 
 *>       DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                                                                                       <* 
 *>       return rc;                                                                                                                           <* 
 *>    }                                                                                                                                       <* 
 *>    /+---(success)------------------------+/                                                                                                <* 
 *>    yURG_msg (' ', "");                                                                                                                     <* 
 *>    IF_CONFIRM  yURG_msg_live ();                                                                                                           <* 
 *>    if (rc == 0)  yURG_msg ('>', "SUCCESS, project was registered in the database");                                                        <* 
 *>    else          yURG_msg ('>', "WARNING, project was already registered in the database");                                                <* 
 *>    /+---(complete)-----------------------+/                                                                                                <* 
 *>    DEBUG_PROG    yLOG_exit    (__FUNCTION__);                                                                                              <* 
 *>    return rc;                                                                                                                              <* 
 *> }                                                                                                                                          <*/

/*> char                                                                                                                               <* 
 *> PROG__update            (void)                                                                                                     <* 
 *> {                                                                                                                                  <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                        <* 
 *>    char        rce         =  -10;                                                                                                 <* 
 *>    char        rc          =    0;                                                                                                 <* 
 *>    /+---(header)-------------------------+/                                                                                        <* 
 *>    DEBUG_PROG    yLOG_enter   (__FUNCTION__);                                                                                      <* 
 *>    /+---(title)--------------------------+/                                                                                        <* 
 *>    IF_VERBOSE   yURG_msg ('>', "  option --vupdate, analyze current project and add to database");                                 <* 
 *>    IF_VERBOSE   yURG_msg (' ', "");                                                                                                <* 
 *>    /+---(call action)--------------------+/                                                                                        <* 
 *>    rc = poly_action_update    ();                                                                                                  <* 
 *>    /+---(failure)------------------------+/                                                                                        <* 
 *>    if (rc < 0) {                                                                                                                   <* 
 *>       yURG_msg (' ', "");                                                                                                          <* 
 *>       if (my.run_mode == ACT_CUPDATE )   yURG_msg_live ();                                                                         <* 
 *>       if (my.run_mode == ACT_CUPDATE )   yURG_msg ('>', "FAILED, could not update database, run --vupdate to identify reasons");   <* 
 *>       if (my.run_mode == ACT_VUPDATE )   yURG_msg ('>', "FAILED, but could not update database, the reasons are shown above");     <* 
 *>       if (my.run_mode == ACT_CUPDATE )   yURG_msg_mute ();                                                                         <* 
 *>       DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                                                                               <* 
 *>       return rc;                                                                                                                   <* 
 *>    }                                                                                                                               <* 
 *>    /+---(success)------------------------+/                                                                                        <* 
 *>    yURG_msg (' ', "");                                                                                                             <* 
 *>    IF_CONFIRM  yURG_msg_live ();                                                                                                   <* 
 *>    yURG_msg ('>', "SUCCESS, project was updated in the database");                                                                 <* 
 *>    /+---(complete)-----------------------+/                                                                                        <* 
 *>    DEBUG_PROG    yLOG_exit    (__FUNCTION__);                                                                                      <* 
 *>    return rc;                                                                                                                      <* 
 *> }                                                                                                                                  <*/

/*> char                                                                                                                                                        <* 
 *> PROG__install           (void)                                                                                                                              <* 
 *> {                                                                                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                                 <* 
 *>    char        rce         =  -10;                                                                                                                          <* 
 *>    char        rc          =    0;                                                                                                                          <* 
 *>    /+---(header)-------------------------+/                                                                                                                 <* 
 *>    DEBUG_PROG    yLOG_enter   (__FUNCTION__);                                                                                                               <* 
 *>    /+---(title)--------------------------+/                                                                                                                 <* 
 *>    IF_VERBOSE   yURG_msg ('>', "  option --vinstall, analyze current project and add to registry plus database");                                           <* 
 *>    IF_VERBOSE   yURG_msg (' ', "");                                                                                                                         <* 
 *>    /+---(call action)--------------------+/                                                                                                                 <* 
 *>    /+> rc = poly_world_register   ();                                                 <+/                                                                   <* 
 *>    /+---(failure)------------------------+/                                                                                                                 <* 
 *>    if (rc < 0) {                                                                                                                                            <* 
 *>       yURG_msg (' ', "");                                                                                                                                   <* 
 *>       if (my.run_mode == ACT_CINSTALL)   yURG_msg_live ();                                                                                                  <* 
 *>       if (my.run_mode == ACT_CINSTALL)   yURG_msg ('>', "FAILED, project could not be registered, run --vinstall to identify reasons");                     <* 
 *>       if (my.run_mode == ACT_VINSTALL)   yURG_msg ('>', "FAILED, project could not be registered, the reasons are shown above");                            <* 
 *>       if (my.run_mode == ACT_CINSTALL)   yURG_msg_mute ();                                                                                                  <* 
 *>       DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                                                                                                        <* 
 *>       return rc;                                                                                                                                            <* 
 *>    }                                                                                                                                                        <* 
 *>    /+---(call action)--------------------+/                                                                                                                 <* 
 *>    yURG_msg (' ', "");                                                                                                                                      <* 
 *>    rc = poly_action_update    ();                                                                                                                           <* 
 *>    /+---(failure)------------------------+/                                                                                                                 <* 
 *>    if (rc < 0) {                                                                                                                                            <* 
 *>       yURG_msg (' ', "");                                                                                                                                   <* 
 *>       if (my.run_mode == ACT_CINSTALL)   yURG_msg_live ();                                                                                                  <* 
 *>       if (my.run_mode == ACT_CINSTALL)   yURG_msg ('>', "FAILED, project registered, but could not update database, run --vinstall to identify reasons");   <* 
 *>       if (my.run_mode == ACT_VINSTALL)   yURG_msg ('>', "FAILED, project registered, but could not update database, the reasons are shown above");          <* 
 *>       if (my.run_mode == ACT_CINSTALL)   yURG_msg_mute ();                                                                                                  <* 
 *>       DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                                                                                                        <* 
 *>       return rc;                                                                                                                                            <* 
 *>    }                                                                                                                                                        <* 
 *>    /+---(success)------------------------+/                                                                                                                 <* 
 *>    yURG_msg (' ', "");                                                                                                                                      <* 
 *>    IF_CONFIRM  yURG_msg_live ();                                                                                                                            <* 
 *>    yURG_msg ('>', "SUCCESS, project was both registered and updated in the database");                                                                      <* 
 *>    /+---(complete)-----------------------+/                                                                                                                 <* 
 *>    DEBUG_PROG    yLOG_exit    (__FUNCTION__);                                                                                                               <* 
 *>    return rc;                                                                                                                                               <* 
 *> }                                                                                                                                                           <*/

/*> char                                                                                                                                         <* 
 *> PROG__withdraw          (void)                                                                                                               <* 
 *> {                                                                                                                                            <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                  <* 
 *>    char        rce         =  -10;                                                                                                           <* 
 *>    char        rc          =    0;                                                                                                           <* 
 *>    /+---(header)-------------------------+/                                                                                                  <* 
 *>    DEBUG_PROG    yLOG_enter   (__FUNCTION__);                                                                                                <* 
 *>    /+---(title)--------------------------+/                                                                                                  <* 
 *>    IF_VERBOSE   yURG_msg ('>', "  option --vwithdraw, remove named project from the to registry");                                           <* 
 *>    IF_VERBOSE   yURG_msg (' ', "");                                                                                                          <* 
 *>    /+---(call action)--------------------+/                                                                                                  <* 
 *>    strlcpy (my.g_projname, my.run_file, LEN_LABEL);                                                                                          <* 
 *>    /+> rc = poly_world_unregister ();                                                 <+/                                                    <* 
 *>    /+---(failure)------------------------+/                                                                                                  <* 
 *>    if (rc < 0) {                                                                                                                             <* 
 *>       yURG_msg (' ', "");                                                                                                                    <* 
 *>       if (my.run_mode == ACT_CWITHDRAW)  yURG_msg_live ();                                                                                   <* 
 *>       if (my.run_mode == ACT_CWITHDRAW)  yURG_msg ('>', "FAILED, project could not be unregistered, run --vwithdraw to identify reasons");   <* 
 *>       if (my.run_mode == ACT_VWITHDRAW)  yURG_msg ('>', "FAILED, project could not be unregistered, the reasons are shown above");           <* 
 *>       if (my.run_mode == ACT_CWITHDRAW)  yURG_msg_mute ();                                                                                   <* 
 *>       DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                                                                                         <* 
 *>       return rc;                                                                                                                             <* 
 *>    }                                                                                                                                         <* 
 *>    /+---(success)------------------------+/                                                                                                  <* 
 *>    yURG_msg (' ', "");                                                                                                                       <* 
 *>    IF_CONFIRM  yURG_msg_live ();                                                                                                             <* 
 *>    if (rc == 0)  yURG_msg ('>', "SUCCESS, project was removed from the registry");                                                           <* 
 *>    else          yURG_msg ('>', "WARNING, project was not in the registry, nothing to do");                                                  <* 
 *>    /+---(complete)-----------------------+/                                                                                                  <* 
 *>    DEBUG_PROG    yLOG_exit    (__FUNCTION__);                                                                                                <* 
 *>    return rc;                                                                                                                                <* 
 *> }                                                                                                                                            <*/

/*> char                                                                                                                                 <* 
 *> PROG__clear             (void)                                                                                                       <* 
 *> {                                                                                                                                    <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                          <* 
 *>    char        rce         =  -10;                                                                                                   <* 
 *>    char        rc          =    0;                                                                                                   <* 
 *>    /+---(header)-------------------------+/                                                                                          <* 
 *>    DEBUG_PROG    yLOG_enter   (__FUNCTION__);                                                                                        <* 
 *>    /+---(title)--------------------------+/                                                                                          <* 
 *>    IF_VERBOSE   yURG_msg ('>', "  option --vclear, remove named project from the database");                                         <* 
 *>    IF_VERBOSE   yURG_msg (' ', "");                                                                                                  <* 
 *>    /+---(call action)--------------------+/                                                                                          <* 
 *>    strlcpy (my.g_projname, my.run_file, LEN_LABEL);                                                                                  <* 
 *>    rc = poly_action_remove    ();                                                                                                    <* 
 *>    /+---(failure)------------------------+/                                                                                          <* 
 *>    if (rc < 0) {                                                                                                                     <* 
 *>       yURG_msg (' ', "");                                                                                                            <* 
 *>       if (my.run_mode == ACT_CCLEAR  )   yURG_msg_live ();                                                                           <* 
 *>       if (my.run_mode == ACT_CCLEAR  )   yURG_msg ('>', "FAILED, project could not be removed, run --vclear to identify reasons");   <* 
 *>       if (my.run_mode == ACT_VCLEAR  )   yURG_msg ('>', "FAILED, project could not be removed, the reasons are shown above");        <* 
 *>       if (my.run_mode == ACT_CCLEAR  )   yURG_msg_mute ();                                                                           <* 
 *>       DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                                                                                 <* 
 *>       return rc;                                                                                                                     <* 
 *>    }                                                                                                                                 <* 
 *>    /+---(success)------------------------+/                                                                                          <* 
 *>    yURG_msg (' ', "");                                                                                                               <* 
 *>    IF_CONFIRM  yURG_msg_live ();                                                                                                     <* 
 *>    if (rc == 0)  yURG_msg ('>', "SUCCESS, project was removed from the database");                                                   <* 
 *>    else          yURG_msg ('>', "WARNING, project was not in database, nothing to do");                                              <* 
 *>    /+---(complete)-----------------------+/                                                                                          <* 
 *>    DEBUG_PROG    yLOG_exit    (__FUNCTION__);                                                                                        <* 
 *>    return rc;                                                                                                                        <* 
 *> }                                                                                                                                    <*/

/*> char                                                                                                                                       <* 
 *> PROG__remove            (void)                                                                                                             <* 
 *> {                                                                                                                                          <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                <* 
 *>    char        rce         =  -10;                                                                                                         <* 
 *>    char        rc          =    0;                                                                                                         <* 
 *>    /+---(header)-------------------------+/                                                                                                <* 
 *>    DEBUG_PROG    yLOG_enter   (__FUNCTION__);                                                                                              <* 
 *>    /+---(title)--------------------------+/                                                                                                <* 
 *>    IF_VERBOSE   yURG_msg ('>', "  option --vremove, remove named project from database and registry");                                     <* 
 *>    IF_VERBOSE   yURG_msg (' ', "");                                                                                                        <* 
 *>    /+---(call action)--------------------+/                                                                                                <* 
 *>    strlcpy (my.g_projname, my.run_file, LEN_LABEL);                                                                                        <* 
 *>    /+> rc = poly_world_unregister ();                                                 <+/                                                  <* 
 *>    /+---(failure)------------------------+/                                                                                                <* 
 *>    if (rc < 0) {                                                                                                                           <* 
 *>       yURG_msg (' ', "");                                                                                                                  <* 
 *>       if (my.run_mode == ACT_CREMOVE )   yURG_msg_live ();                                                                                 <* 
 *>       if (my.run_mode == ACT_CREMOVE )   yURG_msg ('>', "FAILED, project could not be unregistered, run --vremove to identify reasons");   <* 
 *>       if (my.run_mode == ACT_VREMOVE )   yURG_msg ('>', "FAILED, project could not be unregistered, the reasons are shown above");         <* 
 *>       if (my.run_mode == ACT_CREMOVE )   yURG_msg_mute ();                                                                                 <* 
 *>       DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                                                                                       <* 
 *>       return rc;                                                                                                                           <* 
 *>    }                                                                                                                                       <* 
 *>    /+---(call action)--------------------+/                                                                                                <* 
 *>    yURG_msg (' ', "");                                                                                                                     <* 
 *>    rc = poly_action_remove    ();                                                                                                          <* 
 *>    /+---(failure)------------------------+/                                                                                                <* 
 *>    if (rc < 0) {                                                                                                                           <* 
 *>       yURG_msg (' ', "");                                                                                                                  <* 
 *>       if (my.run_mode == ACT_CREMOVE )   yURG_msg_live ();                                                                                 <* 
 *>       if (my.run_mode == ACT_CREMOVE )   yURG_msg ('>', "FAILED, project could not be removed, run --vremove to identify reasons");        <* 
 *>       if (my.run_mode == ACT_VREMOVE )   yURG_msg ('>', "FAILED, project could not be removed, the reasons are shown above");              <* 
 *>       if (my.run_mode == ACT_CREMOVE )   yURG_msg_mute ();                                                                                 <* 
 *>       DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                                                                                       <* 
 *>       return rc;                                                                                                                           <* 
 *>    }                                                                                                                                       <* 
 *>    /+---(success)------------------------+/                                                                                                <* 
 *>    yURG_msg (' ', "");                                                                                                                     <* 
 *>    IF_CONFIRM  yURG_msg_live ();                                                                                                           <* 
 *>    if (rc == 0)  yURG_msg ('>', "SUCCESS, project was removed from database and registry");                                                <* 
 *>    else          yURG_msg ('>', "WARNING, project was not in database, nothing to do");                                                    <* 
 *>    /+---(complete)-----------------------+/                                                                                                <* 
 *>    DEBUG_PROG    yLOG_exit    (__FUNCTION__);                                                                                              <* 
 *>    return rc;                                                                                                                              <* 
 *> }                                                                                                                                          <*/

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
   /*> rc = poly_world_system     ();                                                 <*/
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

/*> char                                                                                                                             <* 
 *> PROG__audit             (void)                                                                                                   <* 
 *> {                                                                                                                                <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                      <* 
 *>    char        rce         =  -10;                                                                                               <* 
 *>    char        rc          =    0;                                                                                               <* 
 *>    /+---(header)-------------------------+/                                                                                      <* 
 *>    DEBUG_PROG    yLOG_enter   (__FUNCTION__);                                                                                    <* 
 *>    /+---(title)--------------------------+/                                                                                      <* 
 *>    IF_VERBOSE   yURG_msg ('>', "  option --vaudit, verify central security and files");                                          <* 
 *>    IF_VERBOSE   yURG_msg (' ', "");                                                                                              <* 
 *>    /+---(call action)--------------------+/                                                                                      <* 
 *>    rc = poly_action_audit     ();                                                                                                <* 
 *>    /+---(failure)------------------------+/                                                                                      <* 
 *>    if (rc < 0) {                                                                                                                 <* 
 *>       yURG_msg (' ', "");                                                                                                        <* 
 *>       if (my.run_mode == ACT_CAUDIT  )   yURG_msg_live ();                                                                       <* 
 *>       if (my.run_mode == ACT_CAUDIT  )   yURG_msg ('>', "FAILED, audit was not successful, run --vaudit to identify reasons");   <* 
 *>       if (my.run_mode == ACT_VAUDIT  )   yURG_msg ('>', "FAILED, audit was not successful, the reasons are shown above");        <* 
 *>       if (my.run_mode == ACT_CAUDIT  )   yURG_msg_mute ();                                                                       <* 
 *>       DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);                                                                             <* 
 *>       return rc;                                                                                                                 <* 
 *>    }                                                                                                                             <* 
 *>    /+---(success)------------------------+/                                                                                      <* 
 *>    yURG_msg (' ', "");                                                                                                           <* 
 *>    IF_CONFIRM  yURG_msg_live ();                                                                                                 <* 
 *>    yURG_msg ('>', "SUCCESS, central security and files are clean");                                                              <* 
 *>    /+---(complete)-----------------------+/                                                                                      <* 
 *>    DEBUG_PROG    yLOG_exit    (__FUNCTION__);                                                                                    <* 
 *>    return 0;                                                                                                                     <* 
 *> }                                                                                                                                <*/



/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN________________o (void) {;}

char         /*-> shutdown program and free memory ---[ ------ [gz.422.001.03]*/ /*-[00.0000.111.!]-*/ /*-[--.---.---.--]-*/
PROG__end               (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(wrap-up)------------------------*/
   poly_proj_purge   ();
   poly_extern_wrap  ();
   /*> poly_world_wrap   ();                                                          <*/
   /*---(remove global files)------------*/
   system ("rm -f htags.gcalls");
   system ("rm -f htags.flow");
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   DEBUG_PROG   yLOGS_end    ();
   return 0;
}

char         /*-> shutdown program and free memory ---[ ------ [gz.422.001.03]*/ /*-[00.0000.111.!]-*/ /*-[--.---.---.--]-*/
PROG_shutdown          (void)
{
   yURG_stage_check (YURG_END);
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
   /*> yURG_by_name  ("mid"          , YURG_ON);                                         <*/
   yURG_by_name  ("kitchen"      , YURG_ON);
   yURG_by_name  ("yexec"        , YURG_ON);
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
      strlcpy (s, yJOBS_iam  (), LEN_TITLE);
      strlcpy (t, yJOBS_mode (), LEN_TITLE);
      snprintf (unit_answer, LEN_RECD, "PROG mode        : iam (%c) %-18.18s, run (%c) %-18.18s, å%sæ", my.run_as, s, my.run_mode, t, my.run_file);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

