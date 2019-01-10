/*============================----beg-of-source---============================*/
#include  "htags.h"



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
#define     MAX_EXTERN  2000
typedef     struct      cEXTERN     tEXTERN;
struct      cEXTERN {
   char        name        [LEN_LABEL];
   char        type;
   int         count;
};
static      tEXTERN     s_externs   [MAX_EXTERN];
static      int         s_nextern   = 0;

char
htags_extern__copy      (tEXTERN *a_dst, tEXTERN *a_src)
{
   strlcpy (a_dst->type, a_src->type, LEN_LABEL);
   a_dst->type   = a_src->type;
   a_dst->count  = a_src->count;
   return 0;
}

char
htags_extern__gnome     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;          /* current index                  */
   int         c           =    0;          /* comparisons                    */
   int         s           =    0;          /* swaps                          */
   tEXTERN     x_tmp;
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(gnome)--------------------------*/
   while (i < s_nextern) {
      /*---(beginning)-------------------*/
      if (i <= 0) {
         DEBUG_SORT   yLOG_note    ("bounce off beginning");
         ++i;
         continue;
      }
      /*---(compare)---------------------*/
      ++c;
      if (strcmp (s_externs [i - 1].name, s_externs [i].name) <= 0) {
         DEBUG_SORT   yLOG_complex ("correct"   , "%2d %-20.20s v %2d %-20.20s   %4d %4d", i, s_externs [i].name, i - 1, s_externs [i - 1].name, c, s);
         ++i;
         continue;
      }
      /*---(swap)------------------------*/
      ++s;
      htags_extern__copy (&x_tmp            , &s_externs [i]    );
      htags_extern__copy (&s_externs [i]    , &s_externs [i - 1]);
      htags_extern__copy (&s_externs [i - 1], &x_tmp           );
      /*---(next)------------------------*/
      ++i;
   }
   DEBUG_SORT   yLOG_value   ("size"       , s_nextern);
   DEBUG_SORT   yLOG_value   ("compares"   , c);
   DEBUG_SORT   yLOG_value   ("swaps"      , s);
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
htags_extern_load       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   FILE       *r           = NULL;          /* external functions file        */
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   r = fopen ("/

   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}


