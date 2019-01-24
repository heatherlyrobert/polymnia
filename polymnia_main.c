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
   /*---(dispatch)-----------------------*/
   switch (g_mode) {
   case MODE_HTAGS  :
      rc = poly_action_generate    ();
      rc = PROG_report      (NULL);
      break;
   case MODE_WRITE  :
      rc = poly_action_generate    ();
      rc = poly_db_write    ();
      break;
   case MODE_UPDATE :
      rc = poly_action_update ();
      break;
   case MODE_REMOVE :
      rc = poly_action_remove ();
      break;
   case MODE_SYSTEM :
      rc = poly_proj_system ("/home/system");
      rc = poly_proj_system ("/home/monkey");
      break;
   case MODE_SEARCH :
      rc = poly_action_search ();
      break;
   case MODE_PROJ   :
   case MODE_FILE   :
      rc = poly_db_read     ();
      rc = poly_rptg_proj   ();
      break;
   case MODE_DUMP   :
      rc = poly_db_read     ();
      rc = poly_rptg_dump   ();
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
