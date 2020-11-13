/*============================----beg-of-source---============================*/
#include   "polymnia.h"


int          /*-> tbd --------------------------------[ ------ [gn.842.232.99]*/ /*-[01.0000.000.!]-*/ /*-[--.---.---.--]-*/
main (int argc, char *argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   tFILE      *x_file      = NULL;
   /*---(initialize)---------------------*/
   if (rc >= 0)  rc = yURG_logger  (argc, argv);
   if (rc >= 0)  rc = yURG_urgs    (argc, argv);
   yURG_stage_check (YURG_STAGE_INIT);
   if (rc >= 0)  rc = PROG_init    (argc, argv);
   if (rc >= 0)  rc = PROG_args    (argc, argv);
   if (rc >= 0)  rc = PROG_begin   ();
   if (rc >= 0)  rc = PROG_final   ();
   if (rc <  0) {
      PROG_end ();
      return -1;
   }
   yURG_stage_check (YURG_STAGE_MAIN);
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_char    ("g_mode"    , my.g_mode);
   /*---(data handling)------------------*/
   if (my.g_mode == POLY_DATA || my.g_mode == POLY_BOTH) {
      DEBUG_PROG   yLOG_char    ("g_data"    , my.g_data);
      switch (my.g_data) {
      case POLY_DATA_HTAGS  :  rc = poly_action_htags  ();   break;
      case POLY_DATA_NEW    :  rc = poly_action_new    ();   break;
      case POLY_DATA_UPDATE :  rc = poly_action_update ();   break;
      case POLY_DATA_REMOVE :  rc = poly_action_remove ();   break;
      case POLY_DATA_SYSTEM :  rc = poly_proj_system ("/home/system");  break;
      case POLY_DATA_MONKEY :  rc = poly_proj_system ("/home/monkey");  break;
      }
   }
   /*---(reporting)----------------------*/
   if (my.g_mode == POLY_RPTG || my.g_mode == POLY_BOTH) {
      DEBUG_PROG   yLOG_char    ("g_rptg"    , my.g_rptg);
      switch (my.g_rptg) {
      case POLY_RPTG_PROJS   : case POLY_RPTG_ONELINE :
         rc = poly_db_read       ();
         rc = poly_rptg_projects ();
         break;
      case POLY_RPTG_FUNC    :
         rc = poly_action_detail ();
         break;


      case POLY_RPTG_ABOUT   :
         rc = poly_action_about ();
         break;
      case POLY_RPTG_DUMP   :
         DEBUG_TOPS   yLOG_note    ("rptg processing, file read, nor htags or write");
         rc = poly_db_read     ();
         rc = poly_rptg_dump   ();
         break;
      case MODE_SEARCH :
         DEBUG_TOPS   yLOG_note    ("search processing, read, but no htags or write");
         rc = poly_action_search ();
         break;
      case MODE_FILE   :
         DEBUG_TOPS   yLOG_note    ("project processing, read, but no htags or write");
         rc = poly_db_read     ();
         rc = poly_rptg_proj   ();
         break;
      case POLY_RPTG_EXTERN :
         DEBUG_TOPS   yLOG_note    ("extern processing, read, but no htags or write");
         rc = poly_action_extern ();
         break;
      case POLY_RPTG_YLIB   :
         DEBUG_TOPS   yLOG_note    ("libuse processing, read, but no htags or write");
         rc = poly_action_libuse ();
         break;
      case POLY_RPTG_VARS   :
         DEBUG_TOPS   yLOG_note    ("htag gathering, then var/macros analysis");
         rc = poly_action_vars ();
         break;
      }

   }
   /*---(check for failure)--------------*/
   DEBUG_PROG   yLOG_value   ("rc"        , rc);
   if (rc <  0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   yURG_stage_check (YURG_STAGE_WRAP);
   rc = PROG_end     ();
   return 0;
}



/*============================----end-of-source---============================*/
