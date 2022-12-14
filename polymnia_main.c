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
   if (rc >= 0)  rc = PROG_urgents   (argc, argv);
   if (rc >= 0)  rc = PROG_startup   (argc, argv);
   if (rc <  0) { PROG_shutdown (); return -1; }
   /*---(dispatch)-----------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   rc = yJOBS_driver (P_ONELINE, poly_yjobs_callback);
   /*> rc = PROG_dispatch ();                                                         <*/
   DEBUG_PROG   yLOG_value   ("driver"    , rc);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   /*---(wrap-up)------------------------*/
   PROG_shutdown ();
   /*---(complete)-----------------------*/
   return rc;
}



/*============================----end-of-source---============================*/
