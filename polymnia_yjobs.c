/*============================----beg-of-source---============================*/
#include   "polymnia.h"



/*====================------------------------------------====================*/
/*===----                       database helpers                       ----===*/
/*====================------------------------------------====================*/
static void  o___DATABASE________o () { return; }

char
poly_yjobs_read         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(handle)-------------------------*/
   DEBUG_PROG    yLOG_note    ("database read action (YJOBS_READ)");
   rc = poly_db_read  ();
   DEBUG_PROG    yLOG_value   ("read"      , rc);
   /*---(complete)-----------------------*/
   return rc;
}

char
poly_yjobs_stats        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(handle)-------------------------*/
   DEBUG_PROG    yLOG_note    ("database statistics action (YJOBS_STATS)");
   rc = PROG__stats    ();
   DEBUG_PROG    yLOG_value   ("stats"     , rc);
   /*---(complete)-----------------------*/
   return rc;
}

char
poly_yjobs_write        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(handle)-------------------------*/
   DEBUG_PROG    yLOG_note    ("database write action (YJOBS_WRITE)");
   rc = poly_db_write ();
   DEBUG_PROG    yLOG_value   ("write"     , rc);
   /*---(complete)-----------------------*/
   return rc;
}



/*====================------------------------------------====================*/
/*===----                      project helpers                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROJECT_________o () { return; }

char
poly_yjobs_pull         (cchar *a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_name      [LEN_LABEL] = "";
   tPROJ      *x_proj      = NULL;
   /*---(handle)-------------------------*/
   DEBUG_PROG    yLOG_note    ("read and verify current project (YJOBS_PULL)");
   yURG_msg ('>', "read and verify current project (pull)");
   rc = poly_proj__get_name (a_data, x_name);
   DEBUG_PROG    yLOG_value   ("getname"   , rc);
   if (rc < 0) {
      yURG_err ('f', "could not get project name from path");
      yURG_msg (' ', "");
      return rc;
   }
   DEBUG_PROG    yLOG_info    ("x_name"    , x_name);
   /*---(DEBUGGING)----------------------*/
   /*> if (strcmp (x_name, "polymnia") == 0)  yLOGS_unmute ();                        <*/
   /*---(find target)--------------------*/
   poly_proj_by_name  (x_name, &x_proj);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   if (x_proj == NULL) {
      yURG_err ('w', "project does not exist in the database, nothing to do");
   } else {
      DEBUG_PROG   yLOG_point   ("->name"     , x_proj->j_name);
      /*---(remove existing target)---------*/
      yURG_msg ('-', "remove current project");
      rc = poly_proj_remove (&x_proj);
      DEBUG_PROG   yLOG_value   ("proj_del"   , rc);
      if (rc < 0) {
         yURG_err ('f', "could not remove project from database");
         yURG_msg (' ', "");
         return rc;
      }
   }
   /*---(add project)--------------------*/
   rc = poly_proj_add (x_name, a_data, &x_proj);
   DEBUG_PROG   yLOG_value   ("add"        , rc);
   if (rc < 0) {
      yURG_err ('f', "could not add project name to database");
      yURG_msg (' ', "");
      return rc;
   }
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   DEBUG_PROG   yLOG_info    ("->name"     , x_proj->j_name);
   /*---(save off)-----------------------*/
   my.g_proj = x_proj;
   x_proj->j_written = my.runtime;
   /*---(analyze project)----------------*/
   rc = poly_action__gather (x_proj);
   DEBUG_PROG   yLOG_value   ("gather"     , rc);
   if (rc < 0) {
      yURG_err ('f', "could not add project data to database");
      yURG_msg (' ', "");
      return rc;
   }
   /*---(DEBUGGING)----------------------*/
   /*> if (strcmp (x_name, "polymnia") == 0)  yLOGS_mute ();                          <*/
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_yjobs_clear        (cchar *a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_name      [LEN_LABEL] = "";
   tPROJ      *x_proj      = NULL;
   /*---(handle)-------------------------*/
   DEBUG_PROG    yLOG_note    ("read and verify current project (YJOBS_CLEAR)");
   yURG_msg ('>', "clear current project (clear)");
   rc = poly_proj__get_name (a_data, x_name);
   DEBUG_PROG    yLOG_value   ("getname"   , rc);
   if (rc < 0) {
      yURG_err ('f', "could not get project name from path");
      yURG_msg (' ', "");
      return rc;
   }
   DEBUG_PROG    yLOG_info    ("x_name"    , x_name);
   /*---(find target)--------------------*/
   poly_proj_by_name  (x_name, &x_proj);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   if (x_proj == NULL) {
      yURG_err ('w', "project does not exist in the database, nothing to do");
      yURG_msg (' ', "");
      return 1;
   } else {
      yURG_msg ('-', "found project in current data");
   }
   DEBUG_PROG   yLOG_point   ("->name"     , x_proj->j_name);
   /*---(save off)-----------------------*/
   my.g_proj = x_proj;
   x_proj->j_written = my.runtime;
   /*---(remove existing target)---------*/
   yURG_msg ('-', "remove current project");
   rc = poly_proj_remove (&x_proj);
   DEBUG_PROG   yLOG_value   ("proj_del"   , rc);
   if (rc < 0) {
      yURG_err ('f', "could not remove project from database");
      yURG_msg (' ', "");
   } else   yURG_msg ('-', "project successfully removed");
   yURG_msg (' ', "");
   /*---(complete)-----------------------*/
   return rc;
}



/*====================------------------------------------====================*/
/*===----                       report helpers                         ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTS_________o () { return; }

char
poly_yjobs_localrpt     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(handle)-------------------------*/
   DEBUG_PROG    yLOG_note    ("local report action (YJOBS_LOCALRPT)");
   my.g_data  = POLY_DATA_HTAGS;
   my.g_scope = POLY_FULL;
   my.g_rptg  = POLY_RPTG_HTAGS;
   poly_action_whoami ();
   rc = poly_rptg_htags (my.g_proj);
   DEBUG_PROG    yLOG_value   ("htags"     , rc);
   /*---(complete)-----------------------*/
   return rc;
}

char
poly_yjobs_report       (cchar *a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(handle)-------------------------*/
   DEBUG_PROG    yLOG_note    ("database report action (YJOBS_REPORT)");
   rc = poly_rptg_lookup   (a_data);
   DEBUG_PROG    yLOG_value   ("lookup"    , rc);
   if (rc < 0)  return rc;
   rc = poly_rptg_projects ();
   DEBUG_PROG    yLOG_value   ("report"    , rc);
   /*---(complete)-----------------------*/
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        main driver                           ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVER__________o () { return; }

char
poly_yjobs_callback     (cchar a_req, cchar *a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   DEBUG_PROG    yLOG_value   ("a_req"     , a_req);
   DEBUG_PROG    yLOG_char    ("a_req"     , ychrvisible (a_req));
   DEBUG_PROG    yLOG_info    ("a_data"    , a_data);
   /*---(handle)-------------------------*/
   switch (a_req) {
   case YJOBS_READ     :  rc = poly_yjobs_read     ();          break;
   case YJOBS_STATS    :  rc = poly_yjobs_stats    ();          break;
   case YJOBS_WRITE    :  rc = poly_yjobs_write    ();          break;
   case YJOBS_PULL     :  rc = poly_yjobs_pull     (a_data);    break;
   case YJOBS_CLEAR    :  rc = poly_yjobs_clear    (a_data);    break;
   case YJOBS_LOCALRPT :  rc = poly_yjobs_localrpt ();          break;
   case YJOBS_REPORT   :  rc = poly_yjobs_report   (a_data);    break;
   }
   /*---(trouble)------------------------*/
   if (rc < 0) {
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                                 <* 
 *> poly_yjobs_callback_OLD (cchar a_req, cchar *a_data)                                 <* 
 *> {                                                                                    <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                          <* 
 *>    char        rce         =  -10;                                                   <* 
 *>    char        rc          =    0;                                                   <* 
 *>    char        x_name      [LEN_LABEL] = "";                                         <* 
 *>    tPROJ      *x_proj      = NULL;                                                   <* 
 *>    char        x_done      =  '-';                                                   <* 
 *>    /+---(header)-------------------------+/                                          <* 
 *>    DEBUG_PROG    yLOG_enter   (__FUNCTION__);                                        <* 
 *>    DEBUG_PROG    yLOG_char    ("a_req"     , a_req);                                 <* 
 *>    DEBUG_PROG    yLOG_info    ("a_data"    , a_data);                                <* 
 *>    /+---(database read)------------------+/                                          <* 
 *>    --rce;  if (x_done == '-' && a_req == YJOBS_READ) {                               <* 
 *>       DEBUG_PROG    yLOG_note    ("database read action (YJOBS_READ)");              <* 
 *>       rc = poly_db_read  ();                                                         <* 
 *>       DEBUG_PROG    yLOG_value   ("read"      , rc);                                 <* 
 *>       if (rc < 0) {                                                                  <* 
 *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>          return rce;                                                                 <* 
 *>       }                                                                              <* 
 *>       x_done = 'y';                                                                  <* 
 *>    }                                                                                 <* 
 *>    /+---(database statistics-------------+/                                          <* 
 *>    --rce;  if (x_done == '-' && a_req == YJOBS_STATS) {                              <* 
 *>       DEBUG_PROG    yLOG_note    ("database read action (YJOBS_STATS)");             <* 
 *>       rc = PROG__stats    ();                                                        <* 
 *>       DEBUG_PROG    yLOG_value   ("stats"     , rc);                                 <* 
 *>       if (rc < 0) {                                                                  <* 
 *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>          return rce;                                                                 <* 
 *>       }                                                                              <* 
 *>       x_done = 'y';                                                                  <* 
 *>    }                                                                                 <* 
 *>    /+---(database write)-----------------+/                                          <* 
 *>    --rce;  if (x_done == '-' && a_req == YJOBS_WRITE) {                              <* 
 *>       DEBUG_PROG    yLOG_note    ("database write action (YJOBS_WRITE)");            <* 
 *>       rc = poly_db_write ();                                                         <* 
 *>       DEBUG_PROG    yLOG_value   ("write"     , rc);                                 <* 
 *>       if (rc < 0) {                                                                  <* 
 *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>          return rce;                                                                 <* 
 *>       }                                                                              <* 
 *>       x_done = 'y';                                                                  <* 
 *>    }                                                                                 <* 
 *>    /+---(database report)----------------+/                                          <* 
 *>    --rce;  if (x_done == '-' && a_req == YJOBS_REPORT) {                             <* 
 *>       DEBUG_PROG    yLOG_note    ("database report action (YJOBS_REPORT)");          <* 
 *>       rc = poly_rptg_lookup   (a_data);                                              <* 
 *>       DEBUG_PROG    yLOG_value   ("lookup"    , rc);                                 <* 
 *>       if (rc < 0) {                                                                  <* 
 *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>          return rce;                                                                 <* 
 *>       }                                                                              <* 
 *>       rc = poly_rptg_projects ();                                                    <* 
 *>       DEBUG_PROG    yLOG_value   ("report"    , rc);                                 <* 
 *>       if (rc < 0) {                                                                  <* 
 *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>          return rce;                                                                 <* 
 *>       }                                                                              <* 
 *>       x_done = 'y';                                                                  <* 
 *>    }                                                                                 <* 
 *>    /+---(file/dir pull)------------------+/                                          <* 
 *>    --rce;  if (x_done == '-' && a_req == YJOBS_PULL) {                               <* 
 *>       DEBUG_PROG    yLOG_note    ("read and verify current project (YJOBS_PULL)");   <* 
 *>       yURG_msg ('>', "read and verify current project (pull)");                      <* 
 *>       rc = poly_proj__get_name (a_data, x_name);                                     <* 
 *>       DEBUG_PROG    yLOG_value   ("getname"   , rc);                                 <* 
 *>       if (rc < 0) {                                                                  <* 
 *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
*>          return rce;                                                                 <* 
*>       }                                                                              <* 
*>       DEBUG_PROG    yLOG_info    ("x_name"    , x_name);                             <* 
*>       rc = poly_proj_replace (x_name, a_data, &x_proj);                              <* 
*>       DEBUG_PROG    yLOG_value   ("replace"   , rc);                                 <* 
*>       if (rc < 0) {                                                                  <* 
   *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
      *>          return rce;                                                                 <* 
      *>       }                                                                              <* 
      *>       /+---(save off)-----------------------+/                                       <* 
      *>       my.g_proj = x_proj;                                                            <* 
      *>       x_proj->j_written = my.runtime;                                                  <* 
      *>       /+---(analyze project)----------------+/                                       <* 
      *>       rc = poly_action__gather (x_proj);                                             <* 
      *>       DEBUG_PROG   yLOG_value   ("gather"     , rc);                                 <* 
      *>       --rce;  if (rc < 0) {                                                          <* 
         *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
            *>          return rce;                                                                 <* 
            *>       }                                                                              <* 
            *>       x_done = 'y';                                                                  <* 
            *>    }                                                                                 <* 
            *>    /+---(local report)-------------------+/                                          <* 
            *>    --rce;  if (x_done == '-' && a_req == YJOBS_LOCALRPT) {                           <* 
               *>       DEBUG_PROG    yLOG_note    ("local report action (YJOBS_LOCALRPT)");           <* 
                  *>       my.g_data  = POLY_DATA_HTAGS;                                                  <* 
                  *>       my.g_scope = POLY_FULL;                                                        <* 
                  *>       my.g_rptg  = POLY_RPTG_HTAGS;                                                  <* 
                  *>       rc = poly_rptg_htags (NULL);                                                   <* 
                  *>       DEBUG_PROG    yLOG_value   ("htags"     , rc);                                 <* 
                  *>       if (rc < 0) {                                                                  <* 
                     *>          DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
                        *>          return rce;                                                                 <* 
                        *>       }                                                                              <* 
                        *>       x_done = 'y';                                                                  <* 
                        *>    }                                                                                 <* 
                        *>    /+---(complete)-----------------------+/                                          <* 
                        *>    DEBUG_PROG    yLOG_exit    (__FUNCTION__);                                        <* 
                        *>    return 0;                                                                         <* 
                        *> }                                                                                    <*/

char
PROG_dispatch           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(TEMPORARY)----------------------*/
   /*> if (my.g_data == POLY_DATA_HTAGS) {                                            <* 
    *>    rc = poly_action_htags     ();                                              <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*---(title)--------------------------*/
   IF_VERBOSE   yURG_msg ('>', "%s", P_ONELINE);
   /*---(route action)-------------------*/
   DEBUG_PROG    yLOG_char    ("run_mode"  , my.run_mode);
   --rce;  switch (my.run_mode) {
      /*---(basic)-----------------------*/
      /*> case ACT_STATS       :                                                         <* 
       *>    rc = PROG__stats    ();                                                     <* 
       *>    break;                                                                      <*/
      /*---(incomming)-------------------*/
      /*> case CASE_VERIFY     :                                                         <* 
       *>    rc = PROG__verify   ();                                                     <* 
       *>    break;                                                                      <*/
      /*> case CASE_REGISTER   :                                                         <* 
       *>    rc = PROG__register ();                                                     <* 
       *>    break;                                                                      <*/
      /*> case CASE_UPDATE     :                                                         <* 
       *>    rc = PROG__update   ();                                                     <* 
       *>    break;                                                                      <*/
      /*> case CASE_INSTALL    :                                                         <* 
       *>    rc = PROG__install  ();                                                     <* 
       *>    break;                                                                      <*/
      /*---(outgoing)--------------------*/
      /*> case CASE_WITHDRAW   :                                                         <* 
       *>    rc = PROG__withdraw ();                                                     <* 
       *>    break;                                                                      <*/
      /*> case CASE_CLEAR      :                                                         <* 
       *>    rc = PROG__clear    ();                                                     <* 
       *>    break;                                                                      <*/
      /*> case CASE_REMOVE     :                                                         <* 
       *>    rc = PROG__remove   ();                                                     <* 
       *>    break;                                                                      <*/
      /*---(central)---------------------*/
      /*> case CASE_REPORT     :                                                         <* 
       *>    DEBUG_PROG    yLOG_note    ("reporting");                                   <* 
       *>    rc = poly_rptg_dispatch ();                                                 <* 
       *>    break;                                                                      <*/
      /*> case CASE_AUDIT      :                                                         <* 
       *>    rc = PROG__audit    ();                                                     <* 
       *>    break;                                                                      <*/
      /*---(execute)---------------------*/
   case CASE_GATHER     :
      rc = PROG__system   ();
      break;
   case CASE_NORMAL     :
   case CASE_STRICT     :
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

