/*============================----beg-of-source---============================*/
#include   "polymnia.h"


char
poly_extern_link        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   FILE       *r           = NULL;          /* external functions file        */
   char       *p           = NULL;
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(create file)--------------------*/
   rc = system ("cflow -x $(ls -1 *.c | grep -v unit) > polymnia.calls");
   DEBUG_SORT   yLOG_value   ("cflow"      , rc);
   /*---(open)---------------------------*/
   r = fopen ("polymnia.calls", "rt");
   DEBUG_SORT   yLOG_point   ("r"          , r);
   --rce;  if (r == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }



   /*---(close)--------------------------*/
   rc = fclose (r);
   DEBUG_SORT   yLOG_value   ("close"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}
