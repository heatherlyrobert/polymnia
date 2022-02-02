/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*====================------------------------------------====================*/
/*===----                      database handling                       ----===*/
/*====================------------------------------------====================*/
static void  o___DATABASE________o () { return; }

char
poly_action__read       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(read the database)--------------*/
   rc = poly_db_read ();
   DEBUG_PROG   yLOG_value   ("read_full"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check results)------------------*/
   c = poly_proj_count ();
   DEBUG_PROG   yLOG_point   ("c"          , c);
   --rce;  if (c <= 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action__write      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(check results)------------------*/
   c = poly_proj_count ();
   DEBUG_PROG   yLOG_point   ("c"          , c);
   --rce;  if (c <= 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save the database)--------------*/
   rc = poly_db_write    ();
   DEBUG_PROG   yLOG_value   ("db_write"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        project gathering                     ----===*/
/*====================------------------------------------====================*/
static void  o___GATHER__________o () { return; }

char
poly_action__gather     (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(produce global files)-----------*/
   rc  = poly_file_review (a_proj);
   DEBUG_PROG   yLOG_value   ("review"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for empty result)---------*/
   --rce;  if (a_proj->count == 0) {
      rc = poly_proj_remove (&a_proj);
      DEBUG_PROG   yLOG_value   ("remove"     , rc);
      if (rc < 0) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return 0;
   }
   /*---(main loop)----------------------*/
   DEBUG_PROG   yLOG_note    ("review all tags and code");
   x_file = a_proj->head;
   DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   while (x_file != NULL) {
      if (strchr ("ch", x_file->type) != NULL) {
         if (x_file->type == 'c')  rc = poly_vars_inventory (x_file);
         DEBUG_PROG   yLOG_value   ("vars"      , rc);
         rc = poly_tags_inventory (x_file);
         DEBUG_PROG   yLOG_value   ("inventory" , rc);
         rc = poly_code_review    (x_file);
         DEBUG_PROG   yLOG_value   ("review"    , rc);
         rc = poly_file_footprint (x_file);
         DEBUG_PROG   yLOG_value   ("footprint" , rc);
      } else {
         rc = poly_units_inventory (x_file);
         DEBUG_PROG   yLOG_value   ("inventory" , rc);
      }
      x_file = x_file->next;
      DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   }
   /*---(executable)---------------------*/
   rc = poly_proj_footprint (a_proj);
   /*---(prepare for use)----------------*/
   DEBUG_PROG   yLOG_note    ("prepare for use");
   rc = poly_btree_prepare_all ();
   DEBUG_PROG   yLOG_value   ("prepare"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(function calls)-----------------*/
   DEBUG_PROG   yLOG_note    ("review function calls");
   rc = poly_extern_review ();
   /*---(summarize)----------------------*/
   rc = PROG_summarize (a_proj);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action__here       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   tFILE      *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(setup project)------------------*/
   rc  = poly_proj_here    (&x_proj);
   DEBUG_PROG   yLOG_value   ("proj_here"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save off)-----------------------*/
   my.g_proj = x_proj;
   /*---(analyze project)----------------*/
   rc = poly_action__gather (x_proj);
   DEBUG_PROG   yLOG_value   ("gather"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action_whoami      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(setup project)------------------*/
   rc  = poly_proj_here    (&x_proj);
   DEBUG_PROG   yLOG_value   ("proj_here"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save off)-----------------------*/
   my.g_proj = x_proj;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       basic actions                          ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVERS_________o () { return; }

char
poly_action_htags       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(generate tags)------------------*/
   rc = poly_action__here ();
   DEBUG_PROG   yLOG_value   ("generate"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(report)-------------------------*/
   rc = poly_rptg_htags      (NULL);
   DEBUG_PROG   yLOG_value   ("report"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action_new         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(generate tags)------------------*/
   rc = poly_action__here ();
   DEBUG_PROG   yLOG_value   ("htags"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(write database)-----------------*/
   rc = poly_action__write   ();
   DEBUG_PROG   yLOG_value   ("write"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action_update      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(read database)------------------*/
   rc = poly_action__read    ();
   DEBUG_PROG   yLOG_value   ("read"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(generate tags)------------------*/
   rc = poly_action__here ();
   DEBUG_PROG   yLOG_value   ("htags"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(write database)-----------------*/
   rc = poly_action__write   ();
   DEBUG_PROG   yLOG_value   ("write"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                              <* 
 *> poly_action_update      (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    tPROJ      *x_proj      = NULL;                                                <* 
 *>    tFILE      *x_file      = NULL;                                                <* 
 *>    char        x_name      [LEN_TITLE];                                           <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    /+---(setup project)------------------+/                                       <* 
 *>    rc  = poly_proj_here    (&x_proj);                                             <* 
 *>    DEBUG_PROG   yLOG_value   ("proj_here"  , rc);                                 <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);                             <* 
 *>    --rce;  if (x_proj == NULL) {                                                  <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(save name)----------------------+/                                       <* 
 *>    strlcpy (x_name, x_proj->name, LEN_TITLE);                                     <* 
 *>    DEBUG_PROG   yLOG_info    ("x_name"     , x_name);                             <* 
 *>    /+---(remove stub)--------------------+/                                       <* 
 *>    rc = poly_proj_remove (&x_proj);                                               <* 
 *>    DEBUG_PROG   yLOG_value   ("proj_del"   , rc);                                 <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(read database)------------------+/                                       <* 
 *>    rc = poly_db_read     ();                                                      <* 
 *>    DEBUG_PROG   yLOG_value   ("db_read"    , rc);                                 <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(remove existing target)---------+/                                       <* 
 *>    poly_proj_by_name  (x_name, &x_proj);                                          <* 
 *>    DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);                             <* 
 *>    --rce;  if (x_proj != NULL) {                                                  <* 
 *>       DEBUG_PROG   yLOG_point   ("->name"     , x_proj->name);                    <* 
 *>       rc = poly_proj_remove (&x_proj);                                            <* 
 *>       DEBUG_PROG   yLOG_value   ("proj_del"   , rc);                              <* 
 *>       --rce;  if (rc < 0) {                                                       <* 
 *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                           <* 
 *>          return rce;                                                              <* 
 *>       }                                                                           <* 
 *>    }                                                                              <* 
 *>    /+---(generate)-----------------------+/                                       <* 
 *>    rc = poly_action_generate    ();                                               <* 
 *>    DEBUG_PROG   yLOG_value   ("main_gen"   , rc);                                 <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(save)---------------------------+/                                       <* 
 *>    rc = poly_db_write    ();                                                      <* 
 *>    DEBUG_PROG   yLOG_value   ("db_write"   , rc);                                 <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/



char
poly_action_search      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(read the database)--------------*/
   rc = poly_db_read ();
   DEBUG_PROG   yLOG_value   ("read_full"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get first project)--------------*/
   x_proj = (tPROJ *) poly_btree_first (B_PROJ);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(report)-------------------------*/
   rc = poly_rptg_htags (x_proj);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}


char
poly_action_about       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   char        t           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(read database)------------------*/
   rc = poly_db_read     ();
   DEBUG_PROG   yLOG_value   ("read"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find target)--------------------*/
   poly_proj_by_name  (my.g_projname, &x_proj);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_PROG   yLOG_point   ("->name"     , x_proj->name);
   /*---(display)----------+-----+-----+-*/
   printf("%s\n", P_ONELINE);
   printf("report of project-wide information (--about) for a single project\n");
   printf("\n");
   printf("focus     : %s\n", x_proj->focus);
   printf("niche     : %s\n", x_proj->niche);
   printf("subject   : %s\n", x_proj->subject);
   printf("purpose   : %s\n", x_proj->purpose);
   printf("\n");
   printf("namesake  : %s\n", x_proj->namesake);
   printf("heritage  : %s\n", x_proj->heritage);
   printf("imagery   : %s\n", x_proj->imagery);
   printf("reason    : %s\n", x_proj->reason);
   printf("\n");
   printf("oneline   : %s\n", x_proj->oneline);
   printf("\n");
   printf("basename  : %s\n", x_proj->progname);
   printf("homedir   : %s\n", x_proj->homedir);
   printf("fullpath  : %s\n", x_proj->fullpath);
   printf("suffix    : %s\n", x_proj->suffix);
   printf("content   : %s\n", x_proj->content);
   printf("\n");
   printf("system    : %s\n", x_proj->systems);
   printf("language  : %s\n", x_proj->language);
   printf("codesize  : %s\n", x_proj->codesize);
   printf("\n");
   printf("author    : %s\n", x_proj->author);
   printf("created   : %s\n", x_proj->created);
   printf("depends   : %s\n", x_proj->depends);
   printf("\n");
   printf("vermajor  : %s\n", x_proj->vermajor);
   printf("verminor  : %s\n", x_proj->verminor);
   printf("ver num   : %s\n", x_proj->vernum);
   printf("ver txt   : %s\n", x_proj->vertxt);
   printf("\n");
   printf("priority  : %s\n", P_PRIORITY);
   printf("principal : %s\n", P_PRINCIPAL);
   printf("reminder  : %s\n", P_REMINDER);
   printf("\n");
   printf("statistics...\n");
   strl4comma (x_proj->COUNT_FILES, t, 0, 'c', '-', LEN_LABEL);
   printf("files     : %10.10s\n", t);
   strl4comma (x_proj->COUNT_FUNCS, t, 0, 'c', '-', LEN_LABEL);
   printf("funcs     : %10.10s    %d\n", t, x_proj->funcs);
   strl4comma (x_proj->COUNT_LINES, t, 0, 'c', '-', LEN_LABEL);
   printf("lines     : %10.10s    %4.2f\n", t, 1.00);
   strl4comma (x_proj->COUNT_EMPTY, t, 0, 'c', '-', LEN_LABEL);
   printf("empty     : %10.10s    %4.2f\n", t, (float) x_proj->COUNT_EMPTY / x_proj->COUNT_LINES);
   strl4comma (x_proj->COUNT_DOCS , t, 0, 'c', '-', LEN_LABEL);
   printf("docs      : %10.10s    %4.2f\n", t, (float) x_proj->COUNT_DOCS  / x_proj->COUNT_LINES);
   strl4comma (x_proj->COUNT_DEBUG, t, 0, 'c', '-', LEN_LABEL);
   printf("debug     : %10.10s    %4.2f\n", t, (float) x_proj->COUNT_DEBUG / x_proj->COUNT_LINES);
   strl4comma (x_proj->COUNT_CODE , t, 0, 'c', '-', LEN_LABEL);
   printf("code      : %10.10s    %4.2f\n", t, (float) x_proj->COUNT_CODE  / x_proj->COUNT_LINES);
   strl4comma (x_proj->COUNT_SLOCL, t, 0, 'c', '-', LEN_LABEL);
   printf("slocl     : %10.10s    %4.2f\n", t, (float) x_proj->COUNT_SLOCL / x_proj->COUNT_LINES);
   printf("\n");
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action_remove      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(setup project)------------------*/
   DEBUG_PROG   yLOG_info    ("g_projname", my.g_projname);
   x_len = strlen (my.g_projname);
   DEBUG_PROG   yLOG_value   ("x_len"      , x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read database)------------------*/
   rc = poly_db_read     ();
   DEBUG_PROG   yLOG_value   ("db_read"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find target)--------------------*/
   poly_proj_by_name  (my.g_projname, &x_proj);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("->name"     , x_proj->name);
   /*---(remove existing target)---------*/
   rc = poly_proj_remove (&x_proj);
   DEBUG_PROG   yLOG_value   ("proj_del"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   rc = poly_db_write    ();
   DEBUG_PROG   yLOG_value   ("db_write"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action_extern      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEXTERN    *x_ext       = NULL;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(setup project)------------------*/
   DEBUG_PROG   yLOG_info    ("g_extern"      , my.g_extern);
   x_len = strlen (my.g_extern);
   DEBUG_PROG   yLOG_value   ("x_len"      , x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read database)------------------*/
   rc = poly_db_read     ();
   DEBUG_PROG   yLOG_value   ("db_read"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find target)--------------------*/
   poly_extern_by_name (my.g_extern, &x_ext);
   DEBUG_PROG   yLOG_point   ("x_ext"      , x_ext);
   --rce;  if (x_ext == NULL) {
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_PROG   yLOG_point   ("->name"     , x_ext->name);
   /*---(read database)------------------*/
   rc = poly_rptg_extern (x_ext);
   DEBUG_PROG   yLOG_value   ("rptg"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action_libuse      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEXTERN    *x_extern    = NULL;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(setup project)------------------*/
   DEBUG_PROG   yLOG_info    ("g_libuse"      , my.g_libuse);
   x_len = strlen (my.g_libuse);
   DEBUG_PROG   yLOG_value   ("x_len"      , x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read database)------------------*/
   rc = poly_db_read     ();
   DEBUG_PROG   yLOG_value   ("db_read"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find targets)-------------------*/
   x_extern = (tEXTERN *) poly_btree_first (B_EXTERN);
   while (x_extern != NULL) {
      if (strcmp (x_extern->lib, my.g_libuse) == 0) {
         rc = poly_rptg_extern (x_extern);
      }
      x_extern = (tEXTERN *) poly_btree_next  (B_EXTERN);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action_vars        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   tFUNC      *x_func      = NULL;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_info    ("g_hint"        , my.g_hint);
   /*---(read database)------------------*/
   rc = poly_action__here ();
   DEBUG_PROG   yLOG_value   ("generate"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get project)--------------------*/
   x_proj = (tPROJ *) poly_btree_first (B_PROJ);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get function)-------------------*/
   rc = poly_func_by_hint (x_proj, my.g_hint, &x_func);
   DEBUG_PROG   yLOG_value   ("find"       , rc);
   DEBUG_PROG   yLOG_point   ("x_func"     , x_func);
   --rce;  if (rc < 0 || x_func == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(headers)------------------------*/
   printf ("##/usr/local/bin/polymnia --vars\n");
   printf ("##\n");
   printf ("##   polymnia-hymnos (many praises) greek muse and protector of divine hymns, dancing, geometry, and grammar\n");
   printf ("##   version %s, %s\n", P_VERNUM, P_VERTXT);
   printf ("##   vars/macros reporting for use with vim-ide\n");
   printf ("##   project  : %s\n", x_proj->name);
   printf ("##   file     : %s\n", x_func->file->name);
   printf ("##   function : %s\n", x_func->name);
   printf ("##   hint     : %s\n", x_func->hint);
   printf ("##   header   : %d\n", x_func->line);
   printf ("##   beg      : %d\n", x_func->beg);
   printf ("##   end      : %d\n", x_func->end);
   printf ("\n");
   /*> printf ("line  ---name-------------  beg  end  len    ---library----------  ---found------------  line  t  c  s\n");   <*/
   poly_vars_header  (CODE_VAR_M);
   rc = poly_code_driver (x_func->file, x_func->beg, x_func->end, CODE_VAR_M);
   poly_vars_summary (x_func, CODE_VAR_M);
   poly_vars_header  (CODE_VAR_V);
   rc = poly_code_driver (x_func->file, x_func->beg, x_func->end, CODE_VAR_V);
   poly_vars_summary (x_func, CODE_VAR_V);
   poly_vars_header  (CODE_VAR_O);
   rc = poly_code_driver (x_func->file, x_func->beg, x_func->end, CODE_VAR_O);
   poly_vars_summary (x_func, CODE_VAR_O);
   poly_vars_list    ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action_detail      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFUNC      *x_proj      = NULL;
   tFUNC      *x_func      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(generate tags)------------------*/
   rc = poly_db_read ();
   DEBUG_PROG   yLOG_value   ("read"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find project)-------------------*/
   printf ("project  [%s]\n", my.g_projname);
   printf ("hint     [%s]\n", my.g_hint);
   poly_proj_by_name  (my.g_projname, &x_proj);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("->name"     , x_proj->name);
   printf ("name     [%s]\n", x_proj->name);
   /*---(find hint)----------------------*/
   rc = poly_func_by_hint (x_proj, my.g_hint, &x_func);
   DEBUG_PROG   yLOG_point   ("x_func"     , x_func);
   if (x_func == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   printf ("func     [%s]\n", x_func->name);
   /*---(run)----------------------------*/
   poly_cats_func (x_func);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



