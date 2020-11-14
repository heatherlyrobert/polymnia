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
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(dispatch)-----------------------*/
   rc = PROG_dispatch ();
   DEBUG_PROG   yLOG_value   ("dispatch"  , rc);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   yURG_stage_check (YURG_STAGE_WRAP);
   PROG_end     ();
   return rc;
}



/*============================----end-of-source---============================*/
