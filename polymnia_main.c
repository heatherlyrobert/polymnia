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
   if (rc >= 0)  rc = PROG_init    (argc, argv);
   if (rc >= 0)  rc = PROG_args    (argc, argv);
   if (rc >= 0)  rc = PROG_begin   ();
   if (rc >= 0)  rc = PROG_final   ();
   if (rc <  0) {
      PROG_end ();
      return -1;
   }
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_char    ("g_mode"    , my.g_mode);
   /*---(dispatch)-----------------------*/
   switch (my.g_mode) {
   case MODE_HTAGS  :
      DEBUG_TOPS   yLOG_note    ("htags processing, no file read or write");
      rc = poly_action_generate    ();
      rc = poly_rptg_htags  (NULL);
      break;
   case MODE_ABOUT  :
      DEBUG_TOPS   yLOG_note    ("about processing, file read, nor htags or write");
      rc = poly_action_about ();
      break;
   case MODE_RPTG   :
   case MODE_DUMP   :
      DEBUG_TOPS   yLOG_note    ("rptg processing, file read, nor htags or write");
      rc = poly_db_read     ();
      rc = poly_rptg_dump   ();
      break;
   case MODE_WRITE  :
      DEBUG_TOPS   yLOG_note    ("write processing, htags and write, no read");
      rc = poly_action_generate    ();
      rc = poly_db_write    ();
      break;
   case MODE_UPDATE :
      DEBUG_TOPS   yLOG_note    ("update processing, read, htags and write");
      rc = poly_action_update ();
      break;
   case MODE_REMOVE :
      DEBUG_TOPS   yLOG_note    ("remove processing, no htags, but read and write");
      rc = poly_action_remove ();
      break;
   case MODE_SYSTEM :
      DEBUG_TOPS   yLOG_note    ("system processing, lots of htags and write");
      rc = poly_proj_system ("/home/system");
      rc = poly_proj_system ("/home/monkey");
      break;
   case MODE_SEARCH :
      DEBUG_TOPS   yLOG_note    ("search processing, read, but no htags or write");
      rc = poly_action_search ();
      break;
   case MODE_PROJ   :
      DEBUG_TOPS   yLOG_note    ("project read, but no htags or write");
      rc = poly_db_read       ();
      rc = poly_rptg_projects ();
      break;
   case MODE_FILE   :
      DEBUG_TOPS   yLOG_note    ("project processing, read, but no htags or write");
      rc = poly_db_read     ();
      rc = poly_rptg_proj   ();
      break;
   case MODE_EXTERN :
      DEBUG_TOPS   yLOG_note    ("extern processing, read, but no htags or write");
      rc = poly_action_extern ();
      break;
   case MODE_LIBUSE :
      DEBUG_TOPS   yLOG_note    ("libuse processing, read, but no htags or write");
      rc = poly_action_libuse ();
      break;
   }
   /*---(check for failure)--------------*/
   DEBUG_PROG   yLOG_value   ("rc"        , rc);
   if (rc <  0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   rc = PROG_end     ();
   return 0;
}



/*============================----end-of-source---============================*/
