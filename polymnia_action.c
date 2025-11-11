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
   c = PROJS_count     ();
   DEBUG_PROG   yLOG_point   ("c"          , c);
   --rce;  if (c <= 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                              <* 
 *> poly_action__write      (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    int         c           =    0;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    /+---(check results)------------------+/                                       <* 
 *>    c = PROJS_count     ();                                                        <* 
 *>    DEBUG_PROG   yLOG_point   ("c"          , c);                                  <* 
 *>    --rce;  if (c <= 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(save the database)--------------+/                                       <* 
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
   char        t           [LEN_HUND]  = "";
   char        s           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(produce global files)-----------*/
   rc  = FILES_gather        (a_proj);
   DEBUG_PROG   yLOG_value   ("review"     , rc);
   --rce;  if (rc < 0) {
      yURG_msg ('f', "could not review directory");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "identified %d files requiring analysis", a_proj->j_icount);
   /*---(check for empty result)---------*/
   --rce;  if (a_proj->j_icount == 0) {
      yURG_msg ('f', "no files, so removing project");
      rc = PROJS_remove     (&a_proj);
      DEBUG_PROG   yLOG_value   ("remove"     , rc);
      if (rc < 0) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return 0;
   }
   /*---(main loop)----------------------*/
   yURG_msg ('-', "analyze code files, externals, and memory footprint");
   DEBUG_PROG   yLOG_note    ("review all tags and code");
   x_file = a_proj->j_ihead;
   DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   while (x_file != NULL) {
      DEBUG_PROG   yLOG_info    ("NAME"      , x_file->i_name);
      if (strchr ("ch", x_file->i_type) != NULL) {
         rc = poly_vars_inventory (x_file);               /*   gobal/file variable and macro definitions  */
         DEBUG_PROG   yLOG_value   ("vars"      , rc);
         rc = poly_tags_inventory (x_file);               /*   prototypes, functions/locals      */
         DEBUG_PROG   yLOG_value   ("inventory" , rc);
         rc = poly_code_review    (x_file);
         DEBUG_PROG   yLOG_value   ("review"    , rc);
         rc = FILES_footprint     (x_file);
         DEBUG_PROG   yLOG_value   ("footprint" , rc);
      } else {
         rc = poly_units_inventory (x_file);
         DEBUG_PROG   yLOG_value   ("inventory" , rc);
      }
      x_file = x_file->i_next;
      DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   }
   /*---(git status)---------------------*/
   rc = PROJS_git     (a_proj);
   /*---(executable)---------------------*/
   rc = PROJS_footprint     (a_proj);
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
   ystrl4main (a_proj->COUNT_LINES, s , 0, 'c', '-', LEN_TERSE);
   ystrlcpy   (t, "lines "  , LEN_HUND);
   ystrlcat   (t, s         , LEN_HUND);
   ystrl4main (a_proj->COUNT_EMPTY, s , 0, 'c', '-', LEN_TERSE);
   ystrlcat   (t, ", empty ", LEN_HUND);
   ystrlcat   (t, s         , LEN_HUND);
   ystrl4main (a_proj->COUNT_DOCS , s , 0, 'c', '-', LEN_TERSE);
   ystrlcat   (t, ", docs  ", LEN_HUND);
   ystrlcat   (t, s         , LEN_HUND);
   ystrl4main (a_proj->COUNT_DEBUG, s , 0, 'c', '-', LEN_TERSE);
   ystrlcat   (t, ", debug ", LEN_HUND);
   ystrlcat   (t, s         , LEN_HUND);
   ystrl4main (a_proj->COUNT_CODE , s , 0, 'c', '-', LEN_TERSE);
   ystrlcat   (t, ", code  ", LEN_HUND);
   ystrlcat   (t, s         , LEN_HUND);
   ystrl4main (a_proj->COUNT_SLOCL, s , 0, 'c', '-', LEN_TERSE);
   ystrlcat   (t, ", slocl ", LEN_HUND);
   ystrlcat   (t, s         , LEN_HUND);
   yURG_msg ('-', "%s", t);
   yURG_msg ('-', "verified %d files, %d functions, %d ylibs", a_proj->COUNT_FILES, a_proj->COUNT_FUNCS, a_proj->COUNT_YLIBS);
   ystrlcpy (t, a_proj->j_codesize, LEN_HUND);
   ystrltrim (t, ySTR_SINGLE, LEN_HUND);
   yURG_msg ('-', "evaluated as å%sæ", t);
   yURG_msg ('-', "project read and verified successfully ");
   yURG_msg (' ', "");
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
   rc  = PROJS_here        (&x_proj);
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
   x_proj->j_written = my.runtime;
   /*---(analyze project)----------------*/
   rc = poly_action__gather (x_proj);
   DEBUG_PROG   yLOG_value   ("gather"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "%d files, %d functions, %d ylibs", x_proj->COUNT_FILES, x_proj->COUNT_FUNCS, x_proj->COUNT_YLIBS);
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
   rc  = PROJS_here        (&x_proj);
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

/*> char                                                                              <* 
 *> poly_action_htags       (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    tPROJ      *x_proj      = NULL;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    /+---(generate tags)------------------+/                                       <* 
 *>    rc = poly_action__here ();                                                     <* 
 *>    DEBUG_PROG   yLOG_value   ("generate"   , rc);                                 <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(report)-------------------------+/                                       <* 
 *>    rc = poly_rptg_htags      (NULL);                                              <* 
 *>    DEBUG_PROG   yLOG_value   ("report"     , rc);                                 <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> poly_action_new         (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    tPROJ      *x_proj      = NULL;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    /+---(generate tags)------------------+/                                       <* 
 *>    rc = poly_action__here ();                                                     <* 
 *>    DEBUG_PROG   yLOG_value   ("htags"      , rc);                                 <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(write database)-----------------+/                                       <* 
 *>    rc = poly_action__write   ();                                                  <* 
 *>    DEBUG_PROG   yLOG_value   ("write"      , rc);                                 <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                                                        <* 
 *> poly_action_update      (void)                                                                              <* 
 *> {                                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                 <* 
 *>    char        rce         =  -10;                                                                          <* 
 *>    char        rc          =    0;                                                                          <* 
 *>    tPROJ      *x_proj      = NULL;                                                                          <* 
 *>    /+---(header)-------------------------+/                                                                 <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                                <* 
 *>    /+---(verify header)------------------+/                                                                 <* 
 *>    yURG_msg ('>', "update/add project details to database...");                                             <* 
 *>    /+---(read database)------------------+/                                                                 <* 
 *>    yURG_msg ('-', "import the current database å%sæ", my.n_db);                                             <* 
 *>    rc = poly_action__read    ();                                                                            <* 
 *>    DEBUG_PROG   yLOG_value   ("read"       , rc);                                                           <* 
 *>    --rce;  if (rc < 0) {                                                                                    <* 
 *>       DEBUG_PROG   yLOG_note    ("database does not exist, potential security issue");                      <* 
 *>       yURG_err ('w', "database does not exist, will create");                                               <* 
 *>    } else {                                                                                                 <* 
 *>       yURG_msg ('-', "%d files, %d functions, %d ylibs", my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_YLIBS);   <* 
 *>    }                                                                                                        <* 
 *>    /+---(generate tags)------------------+/                                                                 <* 
 *>    rc = poly_action__here ();                                                                               <* 
 *>    DEBUG_PROG   yLOG_value   ("htags"      , rc);                                                           <* 
 *>    --rce;  if (rc < 0) {                                                                                    <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                        <* 
 *>       return rce;                                                                                           <* 
 *>    } else {                                                                                                 <* 
 *>       yURG_msg ('-', "project successfully handled");                                                       <* 
 *>    }                                                                                                        <* 
 *>    /+---(write database)-----------------+/                                                                 <* 
 *>    yURG_msg ('-', "write database back to disk");                                                           <* 
 *>    rc = poly_action__write   ();                                                                            <* 
 *>    DEBUG_PROG   yLOG_value   ("write"      , rc);                                                           <* 
 *>    --rce;  if (rc < 0) {                                                                                    <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                        <* 
 *>       return rce;                                                                                           <* 
 *>    }                                                                                                        <* 
 *>    yURG_msg ('-', "%d files, %d functions, %d ylibs", my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_YLIBS);      <* 
 *>    yURG_msg ('-', "success, project updated in database");                                                  <* 
 *>    /+---(complete)-----------------------+/                                                                 <* 
 *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                                <* 
 *>    return 0;                                                                                                <* 
 *> }                                                                                                           <*/

/*> char                                                                                                 <* 
 *> poly_action_audit       (void)                                                                       <* 
 *> {                                                                                                    <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                          <* 
 *>    char        rce         =  -10;                                                                   <* 
 *>    char        rc          =    0;                                                                   <* 
 *>    tPROJ      *x_proj      = NULL;                                                                   <* 
 *>    char        x_orig      [LEN_PATH]  = "";                                                         <* 
 *>    char        x_path      [LEN_PATH]  = "";                                                         <* 
 *>    char       *p           = NULL;                                                                   <* 
 *>    char       *r           = NULL;                                                                   <* 
 *>    int         c           =    0;                                                                   <* 
 *>    /+---(header)-------------------------+/                                                          <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                         <* 
 *>    /+---(verify header)------------------+/                                                          <* 
 *>    yURG_msg ('>', "central directory setup/security...");                                            <* 
 *>    /+---(defense)-------------------------------+/                                                   <* 
 *>    /+> rc = yJOBS_central_dirs (my.run_as, NULL, x_orig, NULL, NULL);                 <+/            <* 
 *>    --rce;  if (rc <  0) {                                                                            <* 
 *>       DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);                                                <* 
 *>       return rce;                                                                                    <* 
 *>    }                                                                                                 <* 
 *>    DEBUG_YEXEC   yLOG_info    ("x_orig"    , x_orig);                                                <* 
 *>    yURG_msg ('-', "for (%c), directory å%sæ selected", my.run_as, x_orig);                           <* 
 *>    /+---(get first level)-----------------------+/                                                   <* 
 *>    p = strtok_r (x_orig, "/", &r);                                                                   <* 
 *>    DEBUG_YEXEC   yLOG_point   ("p"         , p);                                                     <* 
 *>    --rce;  if (p == NULL) {                                                                          <* 
 *>       yURG_err ('f', "can not parse directory name");                                                <* 
 *>       DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);                                                <* 
 *>       return rce;                                                                                    <* 
 *>    }                                                                                                 <* 
 *>    /+---(check each level)----------------------+/                                                   <* 
 *>    --rce;  while (p != NULL) {                                                                       <* 
 *>       sprintf (x_path, "%s/%s", x_path, p);                                                          <* 
 *>       /+> if (c < 2)  rc = yJOBS_act_checkdir (x_path, 0755);                         <+/            <* 
 *>       /+> else        rc = yJOBS_act_checkdir (x_path, 0700);                         <+/            <* 
 *>       if (rc < 0) {                                                                                  <* 
 *>          DEBUG_YEXEC   yLOG_exitr   (__FUNCTION__, rce);                                             <* 
 *>          return rce;                                                                                 <* 
 *>       }                                                                                              <* 
 *>       ++c;                                                                                           <* 
 *>       p = strtok_r (NULL, "/", &r);                                                                  <* 
 *>    }                                                                                                 <* 
 *>    /+---(complete)------------------------------+/                                                   <* 
 *>    yURG_msg ('-', "success, central directory basic security measures confirmed");                   <* 
 *>    /+---(verify header)------------------+/                                                          <* 
 *>    yURG_msg (' ', "");                                                                               <* 
 *>    yURG_msg ('>', "check the central database...");                                                  <* 
 *>    /+---(read database)------------------+/                                                          <* 
 *>    yURG_msg ('-', "import the current database å%sæ", my.n_db);                                      <* 
 *>    rc = poly_action__read    ();                                                                     <* 
 *>    DEBUG_PROG   yLOG_value   ("read"       , rc);                                                    <* 
 *>    --rce;  if (rc < 0) {                                                                             <* 
 *>       DEBUG_PROG   yLOG_note    ("database does not exist, potential security issue");               <* 
 *>       yURG_err ('w', "database does not exist, will create");                                        <* 
 *>    }                                                                                                 <* 
 *>    /+---(check projects)-----------------+/                                                          <* 
 *>    yURG_msg ('-', "projects  : contents %7d vs header  %7d", my.COUNT_PROJS, g_audit.COUNT_PROJS);   <* 
 *>    --rce;  if (my.COUNT_PROJS != g_audit.COUNT_PROJS) {                                              <* 
 *>       yURG_err ('f', "project count does not match");                                                <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
 *>       return rce;                                                                                    <* 
 *>    }                                                                                                 <* 
 *>    /+---(check files)--------------------+/                                                          <* 
 *>    yURG_msg ('-', "files     : contents %7d vs header  %7d", my.COUNT_FILES, g_audit.COUNT_FILES);   <* 
 *>    --rce;  if (my.COUNT_FILES != g_audit.COUNT_FILES) {                                              <* 
 *>       yURG_err ('f', "file count does not match");                                                   <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
 *>       return rce;                                                                                    <* 
 *>    }                                                                                                 <* 
*>    /+---(check functions)----------------+/                                                          <* 
*>    yURG_msg ('-', "functions : contents %7d vs header  %7d", my.COUNT_FUNCS, g_audit.COUNT_FUNCS);   <* 
*>    --rce;  if (my.COUNT_FUNCS != g_audit.COUNT_FUNCS) {                                              <* 
   *>       yURG_err ('f', "function count does not match");                                               <* 
      *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
      *>       return rce;                                                                                    <* 
      *>    }                                                                                                 <* 
      *>    /+---(check ylibs)--------------------+/                                                          <* 
      *>    yURG_msg ('-', "ylibs     : contents %7d vs header  %7d", my.COUNT_YLIBS, g_audit.COUNT_YLIBS);   <* 
      *>    --rce;  if (my.COUNT_YLIBS != g_audit.COUNT_YLIBS) {                                              <* 
         *>       yURG_err ('w', "ylib count does not match, likely due to external.txt change");                <* 
            *>    }                                                                                                 <* 
            *>    /+---(check lines)--------------------+/                                                          <* 
            *>    yURG_msg ('-', "lines     : contents %7d vs header  %7d", my.COUNT_LINES, g_audit.COUNT_LINES);   <* 
            *>    --rce;  if (my.COUNT_LINES != g_audit.COUNT_LINES) {                                              <* 
               *>       yURG_err ('f', "source line count does not match");                                            <* 
                  *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
                  *>       return rce;                                                                                    <* 
                  *>    }                                                                                                 <* 
                  *>    /+---(check empty)--------------------+/                                                          <* 
                  *>    yURG_msg ('-', "empty     : contents %7d vs header  %7d", my.COUNT_EMPTY, g_audit.COUNT_EMPTY);   <* 
                  *>    --rce;  if (my.COUNT_EMPTY != g_audit.COUNT_EMPTY) {                                              <* 
                     *>       yURG_err ('f', "empty line count does not match");                                             <* 
                        *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
                        *>       return rce;                                                                                    <* 
                        *>    }                                                                                                 <* 
                        *>    /+---(check documentation)------------+/                                                          <* 
                        *>    yURG_msg ('-', "docs      : contents %7d vs header  %7d", my.COUNT_DOCS , g_audit.COUNT_DOCS );   <* 
                        *>    --rce;  if (my.COUNT_DOCS  != g_audit.COUNT_DOCS ) {                                              <* 
                           *>       yURG_err ('f', "documentation line count does not match");                                     <* 
                              *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
                              *>       return rce;                                                                                    <* 
                              *>    }                                                                                                 <* 
                              *>    /+---(check debug)--------------------+/                                                          <* 
                              *>    yURG_msg ('-', "debug     : contents %7d vs header  %7d", my.COUNT_DEBUG, g_audit.COUNT_DEBUG);   <* 
                              *>    --rce;  if (my.COUNT_DEBUG != g_audit.COUNT_DEBUG) {                                              <* 
                                 *>       yURG_err ('f', "debug line count does not match");                                             <* 
                                    *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
                                    *>       return rce;                                                                                    <* 
                                    *>    }                                                                                                 <* 
                                    *>    /+---(check code)---------------------+/                                                          <* 
                                    *>    yURG_msg ('-', "code      : contents %7d vs header  %7d", my.COUNT_CODE , g_audit.COUNT_CODE );   <* 
                                    *>    --rce;  if (my.COUNT_CODE  != g_audit.COUNT_CODE ) {                                              <* 
                                       *>       yURG_err ('f', "code line count does not match");                                              <* 
                                          *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
                                          *>       return rce;                                                                                    <* 
                                          *>    }                                                                                                 <* 
                                          *>    /+---(check slocl)--------------------+/                                                          <* 
                                          *>    yURG_msg ('-', "slocl     : contents %7d vs header  %7d", my.COUNT_SLOCL, g_audit.COUNT_SLOCL);   <* 
                                          *>    --rce;  if (my.COUNT_SLOCL != g_audit.COUNT_SLOCL) {                                              <* 
                                             *>       yURG_err ('f', "slocl line count does not match");                                             <* 
                                                *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
                                                *>       return rce;                                                                                    <* 
                                                *>    }                                                                                                 <* 
                                                *>    yURG_msg ('-', "success, central database contents match header values");                         <* 
                                                *>    /+---(complete)-----------------------+/                                                          <* 
                                                *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                         <* 
                                                *>    return 0;                                                                                         <* 
                                                *> }                                                                                                    <*/

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
   rc = ySORT_by_cursor (B_PROJ, YDLST_HEAD, &x_proj, NULL);
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


/*> char                                                                                                 <* 
 *> poly_action_about       (void)                                                                       <* 
 *> {                                                                                                    <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                          <* 
 *>    char        rce         =  -10;                                                                   <* 
 *>    char        rc          =    0;                                                                   <* 
 *>    tPROJ      *x_proj      = NULL;                                                                   <* 
 *>    char        t           [LEN_LABEL] = "";                                                         <* 
 *>    /+---(header)-------------------------+/                                                          <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                         <* 
 *>    /+---(read database)------------------+/                                                          <* 
 *>    rc = poly_db_read     ();                                                                         <* 
 *>    DEBUG_PROG   yLOG_value   ("read"       , rc);                                                    <* 
 *>    --rce;  if (rc < 0) {                                                                             <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                 <* 
 *>       return rce;                                                                                    <* 
 *>    }                                                                                                 <* 
 *>    /+---(find target)--------------------+/                                                          <* 
 *>    PROJS_by_name      (my.g_projname, &x_proj);                                                      <* 
 *>    DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);                                                <* 
 *>    --rce;  if (x_proj == NULL) {                                                                     <* 
 *>       DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                      <* 
 *>       return 0;                                                                                      <* 
 *>    }                                                                                                 <* 
 *>    DEBUG_PROG   yLOG_point   ("->name"     , x_proj->j_name);                                          <* 
 *>    /+---(display)----------+-----+-----+-+/                                                          <* 
 *>    printf("%s\n", P_ONELINE);                                                                        <* 
 *>    printf("report of project-wide information (--about) for a single project\n");                    <* 
 *>    printf("\n");                                                                                     <* 
 *>    printf("focus     : %s\n", x_proj->j_focus);                                                        <* 
 *>    printf("niche     : %s\n", x_proj->j_niche);                                                        <* 
 *>    printf("subject   : %s\n", x_proj->j_subject);                                                      <* 
 *>    printf("purpose   : %s\n", x_proj->j_purpose);                                                      <* 
 *>    printf("\n");                                                                                     <* 
 *>    printf("namesake  : %s\n", x_proj->j_namesake);                                                     <* 
 *>    printf("heritage  : %s\n", x_proj->j_heritage);                                                     <* 
 *>    printf("imagery   : %s\n", x_proj->j_imagery);                                                      <* 
 *>    printf("reason    : %s\n", x_proj->j_reason);                                                       <* 
 *>    printf("\n");                                                                                     <* 
 *>    printf("oneline   : %s\n", x_proj->j_oneline);                                                      <* 
 *>    printf("\n");                                                                                     <* 
 *>    printf("basename  : %s¦", x_proj->j_progname);                                                     <* 
 *>    printf("homedir   : %s\n", x_proj->j_homedir);                                                      <* 
 *>    printf("fullpath  : %s\n", x_proj->j_fullpath);                                                     <* 
 *>    printf("suffix    : %s\n", x_proj->j_suffix);                                                       <* 
 *>    printf("content   : %s\n", x_proj->j_content);                                                      <* 
 *>    printf("\n");                                                                                     <* 
 *>    printf("system    : %s\n", x_proj->j_systems);                                                      <* 
 *>    printf("language  : %s\n", x_proj->j_language);                                                     <* 
 *>    printf("codesize  : %s\n", x_proj->j_codesize);                                                     <* 
 *>    printf("\n");                                                                                     <* 
 *>    printf("author    : %s\n", x_proj->j_author);                                                       <* 
 *>    printf("created   : %s\n", x_proj->j_created);                                                      <* 
 *>    printf("depends   : %s\n", x_proj->depends);                                                      <* 
 *>    printf("\n");                                                                                     <* 
 *>    printf("vermajor  : %s\n", x_proj->j_vermajor);                                                     <* 
 *>    printf("verminor  : %s\n", x_proj->j_verminor);                                                     <* 
 *>    printf("ver num   : %s\n", x_proj->j_vernum);                                                       <* 
 *>    printf("ver txt   : %s\n", x_proj->j_vertxt);                                                       <* 
 *>    printf("\n");                                                                                     <* 
 *>    printf("priority  : %s\n", P_PRIORITY);                                                           <* 
 *>    printf("principal : %s\n", P_PRINCIPAL);                                                          <* 
 *>    printf("reminder  : %s\n", P_REMINDER);                                                           <* 
 *>    printf("\n");                                                                                     <* 
 *>    printf("statistics...\n");                                                                        <* 
 *>    ystrl4comma (x_proj->COUNT_FILES, t, 0, 'c', '-', LEN_LABEL);                                      <* 
 *>    printf("files     : %10.10s\n", t);                                                               <* 
 *>    ystrl4comma (x_proj->COUNT_FUNCS, t, 0, 'c', '-', LEN_LABEL);                                      <* 
 *>    printf("funcs     : %10.10s    %d\n", t, x_proj->j_funcs);                                          <* 
 *>    ystrl4comma (x_proj->COUNT_LINES, t, 0, 'c', '-', LEN_LABEL);                                      <* 
 *>    printf("lines     : %10.10s    %4.2f\n", t, 1.00);                                                <* 
*>    ystrl4comma (x_proj->COUNT_EMPTY, t, 0, 'c', '-', LEN_LABEL);                                      <* 
*>    printf("empty     : %10.10s    %4.2f\n", t, (float) x_proj->COUNT_EMPTY / x_proj->COUNT_LINES);   <* 
*>    ystrl4comma (x_proj->COUNT_DOCS , t, 0, 'c', '-', LEN_LABEL);                                      <* 
*>    printf("docs      : %10.10s    %4.2f\n", t, (float) x_proj->COUNT_DOCS  / x_proj->COUNT_LINES);   <* 
*>    ystrl4comma (x_proj->COUNT_DEBUG, t, 0, 'c', '-', LEN_LABEL);                                      <* 
*>    printf("debug     : %10.10s    %4.2f\n", t, (float) x_proj->COUNT_DEBUG / x_proj->COUNT_LINES);   <* 
*>    ystrl4comma (x_proj->COUNT_CODE , t, 0, 'c', '-', LEN_LABEL);                                      <* 
*>    printf("code      : %10.10s    %4.2f\n", t, (float) x_proj->COUNT_CODE  / x_proj->COUNT_LINES);   <* 
*>    ystrl4comma (x_proj->COUNT_SLOCL, t, 0, 'c', '-', LEN_LABEL);                                      <* 
*>    printf("slocl     : %10.10s    %4.2f\n", t, (float) x_proj->COUNT_SLOCL / x_proj->COUNT_LINES);   <* 
*>    printf("\n");                                                                                     <* 
*>    /+---(complete)-----------------------+/                                                          <* 
*>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                         <* 
*>    return 0;                                                                                         <* 
*> }                                                                                                    <*/

/*> char                                                                                                        <* 
 *> poly_action_remove      (void)                                                                              <* 
 *> {                                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                 <* 
 *>    char        rce         =  -10;                                                                          <* 
 *>    char        rc          =    0;                                                                          <* 
 *>    tPROJ      *x_proj      = NULL;                                                                          <* 
 *>    int         x_len       =    0;                                                                          <* 
 *>    /+---(header)-------------------------+/                                                                 <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                                <* 
 *>    /+---(verify header)------------------+/                                                                 <* 
 *>    yURG_msg ('>', "clear/remove project details to database...");                                           <* 
 *>    /+---(setup project)------------------+/                                                                 <* 
 *>    DEBUG_PROG   yLOG_info    ("g_projname", my.g_projname);                                                 <* 
 *>    x_len = strlen (my.g_projname);                                                                          <* 
 *>    DEBUG_PROG   yLOG_value   ("x_len"      , x_len);                                                        <* 
 *>    --rce;  if (x_len <= 0) {                                                                                <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                        <* 
 *>       return rce;                                                                                           <* 
 *>    }                                                                                                        <* 
 *>    /+---(read database)------------------+/                                                                 <* 
 *>    yURG_msg ('-', "import the current database å%sæ", my.n_db);                                             <* 
 *>    rc = poly_db_read     ();                                                                                <* 
 *>    DEBUG_PROG   yLOG_value   ("db_read"    , rc);                                                           <* 
 *>    --rce;  if (rc < 0) {                                                                                    <* 
 *>       DEBUG_PROG   yLOG_note    ("database does not exist, potential security issue");                      <* 
 *>       yURG_err ('w', "database does not exist, will create");                                               <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                        <* 
 *>       return rce;                                                                                           <* 
 *>    } else {                                                                                                 <* 
 *>       yURG_msg ('-', "%d files, %d functions, %d ylibs", my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_YLIBS);   <* 
 *>    }                                                                                                        <* 
 *>    /+---(find target)--------------------+/                                                                 <* 
 *>    PROJS_by_name      (my.g_projname, &x_proj);                                                             <* 
 *>    DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);                                                       <* 
 *>    --rce;  if (x_proj == NULL) {                                                                            <* 
 *>       yURG_err ('w', "project does not exist in the database, nothing to do");                              <* 
 *>       DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                             <* 
 *>       return 1;                                                                                             <* 
 *>    } else {                                                                                                 <* 
 *>       yURG_msg ('-', "found project in current data");                                                      <* 
 *>    }                                                                                                        <* 
 *>    DEBUG_PROG   yLOG_point   ("->name"     , x_proj->j_name);                                                 <* 
 *>    /+---(remove existing target)---------+/                                                                 <* 
 *>    yURG_msg ('-', "remove current project");                                                                <* 
 *>    rc = PROJS_remove     (&x_proj);                                                                         <* 
 *>    DEBUG_PROG   yLOG_value   ("proj_del"   , rc);                                                           <* 
 *>    --rce;  if (rc < 0) {                                                                                    <* 
 *>       yURG_err ('f', "could not remove project from database");                                             <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                        <* 
 *>       return rce;                                                                                           <* 
 *>    } else {                                                                                                 <* 
 *>       yURG_msg ('-', "project successfully removed");                                                       <* 
 *>    }                                                                                                        <* 
 *>    /+---(save)---------------------------+/                                                                 <* 
 *>    yURG_msg ('-', "write database back to disk");                                                           <* 
 *>    rc = poly_db_write    ();                                                                                <* 
 *>    DEBUG_PROG   yLOG_value   ("db_write"   , rc);                                                           <* 
 *>    --rce;  if (rc < 0) {                                                                                    <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                                        <* 
 *>       return rce;                                                                                           <* 
 *>    }                                                                                                        <* 
 *>    yURG_msg ('-', "%d files, %d functions, %d ylibs", my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_YLIBS);      <* 
 *>    yURG_msg ('-', "success, project cleared from database");                                                <* 
 *>    /+---(complete)-----------------------+/                                                                 <* 
 *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                                <* 
 *>    return 0;                                                                                                <* 
 *> }                                                                                                           <*/

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
   rc = ySORT_by_cursor (B_EXTERN, YDLST_HEAD, &x_extern, NULL);
   DEBUG_PROG   yLOG_point   ("x_extern"   , x_extern);
   while (x_extern != NULL) {
      if (strcmp (x_extern->elib->name, my.g_libuse) == 0) {
         rc = poly_rptg_extern (x_extern);
      }
      rc = ySORT_by_cursor (B_EXTERN, YDLST_NEXT, &x_extern, NULL);
      DEBUG_PROG   yLOG_point   ("x_extern"   , x_extern);
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
   rc = ySORT_by_cursor (B_PROJ, YDLST_HEAD, &x_proj, NULL);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get function)-------------------*/
   rc = FUNCS_by_proj_hint (x_proj, my.g_hint, &x_func);
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
   printf ("##   project  : %s\n", x_proj->j_name);
   printf ("##   file     : %s\n", x_func->c_file->i_name);
   printf ("##   function : %s\n", x_func->c_name);
   printf ("##   hint     : %s\n", x_func->c_hint);
   printf ("##   header   : %d\n", x_func->c_line);
   printf ("##   beg      : %d\n", x_func->c_beg);
   printf ("##   end      : %d\n", x_func->c_end);
   printf ("\n");
   /*> printf ("line  ---name-------------  beg  end  len    ---library----------  ---found------------  line  t  c  s\n");   <*/
   poly_vars_header  (CODE_VAR_M);
   rc = poly_code_driver (x_func->c_file, x_func->c_beg, x_func->c_end, CODE_VAR_M);
   poly_vars_summary (x_func, CODE_VAR_M);
   poly_vars_header  (CODE_VAR_V);
   rc = poly_code_driver (x_func->c_file, x_func->c_beg, x_func->c_end, CODE_VAR_V);
   poly_vars_summary (x_func, CODE_VAR_V);
   poly_vars_header  (CODE_VAR_O);
   rc = poly_code_driver (x_func->c_file, x_func->c_beg, x_func->c_end, CODE_VAR_O);
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
   PROJS_by_name      (my.g_projname, &x_proj);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_point   ("->name"     , x_proj->c_name);
   printf ("name     [%s]\n", x_proj->c_name);
   /*---(find hint)----------------------*/
   rc = FUNCS_by_proj_hint (x_proj, my.g_hint, &x_func);
   DEBUG_PROG   yLOG_point   ("x_func"     , x_func);
   if (x_func == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   printf ("func     [%s]\n", x_func->c_name);
   /*---(run)----------------------------*/
   poly_cats_func (x_func);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



