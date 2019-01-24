/*============================----beg-of-source---============================*/
#include  "polymnia.h"



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
   rc = PROG_report (x_proj);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_action_generate    (void)
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
   /*---(produce global files)-----------*/
   rc  = poly_files_review (x_proj);
   DEBUG_PROG   yLOG_value   ("review"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_proj->count == 0) {
      rc = poly_proj_del (x_proj);
      DEBUG_PROG   yLOG_value   ("proj_del"   , rc);
      if (rc < 0) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return 0;
   }
   /*---(main loop)----------------------*/
   DEBUG_PROG   yLOG_note    ("review all tags and code");
   x_file = x_proj->head;
   DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   while (x_file != NULL) {
      rc = poly_tags_inventory (x_file);
      DEBUG_PROG   yLOG_value   ("inventory" , rc);
      rc = poly_tags_review    (x_file);
      DEBUG_PROG   yLOG_value   ("review"    , rc);
      x_file = x_file->next;
      DEBUG_PROG   yLOG_point   ("x_file"    , x_file);
   }
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
   rc = PROG_summarize (x_proj);
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
   tFILE      *x_file      = NULL;
   char        x_name      [LEN_NAME];
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
   /*---(save name)----------------------*/
   strlcpy (x_name, x_proj->name, LEN_NAME);
   DEBUG_PROG   yLOG_info    ("x_name"     , x_name);
   /*---(remove stub)--------------------*/
   rc = poly_proj_del (x_proj);
   DEBUG_PROG   yLOG_value   ("proj_del"   , rc);
   --rce;  if (rc < 0) {
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
   /*---(remove existing target)---------*/
   x_proj = (tPROJ *) poly_proj_search  (x_name);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj != NULL) {
      DEBUG_PROG   yLOG_point   ("->name"     , x_proj->name);
      rc = poly_proj_del (x_proj);
      DEBUG_PROG   yLOG_value   ("proj_del"   , rc);
      --rce;  if (rc < 0) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(generate)-----------------------*/
   rc = poly_action_generate    ();
   DEBUG_PROG   yLOG_value   ("main_gen"   , rc);
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
   DEBUG_PROG   yLOG_info    ("s_name"     , s_name);
   x_len = strlen (s_name);
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
   x_proj = (tPROJ *) poly_proj_search  (s_name);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_PROG   yLOG_point   ("->name"     , x_proj->name);
   /*---(remove existing target)---------*/
   rc = poly_proj_del (x_proj);
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
