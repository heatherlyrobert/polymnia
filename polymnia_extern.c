/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
#define     MAX_EXTERN  2000
typedef     struct      cEXTERN     tEXTERN;
struct      cEXTERN {
   char        name        [LEN_LABEL];
   int         len;
   char        type;
   int         count;
};
static      tEXTERN     s_externs   [MAX_EXTERN];
static      int         s_nextern   = 0;


char
poly_extern_init        (void)
{
   s_nextern = 0;
   return 0;
}

char
poly_extern__copy       (tEXTERN *a_dst, tEXTERN *a_src)
{
   strlcpy (a_dst->name, a_src->name, LEN_LABEL);
   a_dst->len    = a_src->len;
   a_dst->type   = a_src->type;
   a_dst->count  = a_src->count;
   return 0;
}

char
poly_extern__gnome      (void)
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
         DEBUG_SORT   yLOG_complex ("correct"   , "%2d %-20.20s v %2d %-20.20s   %4d %4d", i - 1, s_externs [i - 1].name, i, s_externs [i].name, c, s);
         ++i;
         continue;
      }
      /*---(swap)------------------------*/
      ++s;
      poly_extern__copy (&x_tmp            , &s_externs [i]    );
      poly_extern__copy (&s_externs [i]    , &s_externs [i - 1]);
      poly_extern__copy (&s_externs [i - 1], &x_tmp           );
      DEBUG_SORT   yLOG_complex ("swapped"   , "%2d %-20.20s # %2d %-20.20s   %4d %4d", i - 1, s_externs [i - 1].name, i, s_externs [i].name, c, s);
      /*---(next)------------------------*/
      --i;
   }
   DEBUG_SORT   yLOG_value   ("size"       , s_nextern);
   DEBUG_SORT   yLOG_value   ("compares"   , c);
   DEBUG_SORT   yLOG_value   ("swaps"      , s);
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_load        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   FILE       *r           = NULL;          /* external functions file        */
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   int         c           =    0;
   char        x_header    [LEN_LABEL];
   char        x_cat       [LEN_LABEL];
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   r = fopen (FILE_EXTERN, "rt");
   DEBUG_SORT   yLOG_point   ("r"          , r);
   --rce;  if (r == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   DEBUG_SORT   yLOG_value   ("s_nextern"  , s_nextern);
   while (1) {
      /*---(read)------------------------*/
      fgets (x_recd, LEN_RECD, r);
      if (feof (r)) {
         DEBUG_SORT   yLOG_note    ("end of file");
         break;
      }
      ++c;
      x_len = strlen (x_recd);
      DEBUG_SORT   yLOG_value   ("x_len"     , x_len);
      if (strlen >= 1)  x_recd [--x_len] = '\0';
      DEBUG_SORT   yLOG_value   ("x_len"     , x_len);
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      DEBUG_SORT   yLOG_info    ("x_recd"    , x_recd);
      x_len = strlen (x_recd);
      DEBUG_SORT   yLOG_value   ("x_len"     , x_len);
      DEBUG_SORT   yLOG_info    ("x_recd"    , x_recd);
      /*---(filter)----------------------*/
      if (x_len == 0) {
         DEBUG_SORT   yLOG_note    ("empty line, SKIP");
         continue;
      }
      if (strncmp (x_recd, "##", 2) == 0) {
         DEBUG_SORT   yLOG_note    ("header line, SKIP");
         continue;
      }
      if (x_recd [0] == '#') {
         DEBUG_SORT   yLOG_note    ("category line, SKIP");
         continue;
      }
      /*---(save)------------------------*/
      s_externs [s_nextern].type = '-';
      if (x_len >= 20) {
         s_externs [s_nextern].type = x_recd [19];
         x_recd [19] = '\0';
      }
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      x_len = strlen (x_recd);
      strlcpy (s_externs [s_nextern].name, x_recd, LEN_LABEL);
      s_externs [s_nextern].len   = x_len;
      s_externs [s_nextern].count = 0;
      DEBUG_SORT   yLOG_complex ("added"     , "%3d %2d:%-20.20s %c %d", s_nextern, s_externs [s_nextern].len, s_externs [s_nextern].name, s_externs [s_nextern].type, s_externs [s_nextern].count);
      /*---(done)------------------------*/
      ++s_nextern;
   }
   /*---(close)--------------------------*/
   rc = fclose (r);
   DEBUG_SORT   yLOG_value   ("close"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(sort)---------------------------*/
   rc = poly_extern__gnome ();
   /*---(display)------------------------*/
   /*> for (i = 0; i < s_nextern; ++i) {                                              <* 
    *>    printf ("%3d %2d:%-20.20s %c %d\n",                                         <* 
    *>       i, s_externs [i].len, s_externs [i].name,                                <* 
    *>       s_externs [i].type, s_externs [i].count);                                <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_check       (char *a_name)
{
   int         rce         =  -10;
   int         x_len       =    0;
   int         i           =    0;
   --rce;  if (a_name == NULL)  return rce;
   x_len = strlen (a_name);
   --rce;  if (x_len == 0)      return rce;
   for (i = 0; i < s_nextern; ++i) {
      if (s_externs [i].len != x_len)                continue;
      if (s_externs [i].name [0] != a_name [0])      continue;
      if (strcmp (s_externs [i].name, a_name) != 0)  continue;
      return s_externs [i].type;
   }
   return ' ';
}

char
poly_extern_review      (int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   FILE       *r           = NULL;          /* external functions file        */
   char       *p           = NULL;
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   int         c           =    0;
   char        x_cat       =  ' ';
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(create file)--------------------*/
   rc = system ("cflow -d 2 htags.code > polymnia.calls");
   DEBUG_SORT   yLOG_value   ("cflow"      , rc);
   /*---(open)---------------------------*/
   r = fopen ("polymnia.calls", "rt");
   DEBUG_SORT   yLOG_point   ("r"          , r);
   --rce;  if (r == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets (x_recd, LEN_RECD, r);
      if (feof (r)) {
         DEBUG_SORT   yLOG_note    ("end of file");
         break;
      }
      if (x_recd [0] != ' ') {
         DEBUG_SORT   yLOG_note    ("header line, skipping");
         continue;
      }
      ++c;
      x_len = strlen (x_recd);
      if (strlen >= 1)  x_recd [--x_len] = '\0';
      strltrim (x_recd, ySTR_EVERY, LEN_RECD);
      /*---(filter)----------------------*/
      p = strchr (x_recd, '(');
      if (p == NULL) {
         DEBUG_SORT   yLOG_note    ("not a function call, SKIPPING");
         continue;
      }
      *p = '\0';
      x_len = strlen (x_recd);
      DEBUG_SORT   yLOG_value   ("x_len"     , x_len);
      DEBUG_SORT   yLOG_info    ("x_recd"    , x_recd);
      /*---(lookup)----------------------*/
      x_cat = poly_extern_check (x_recd);
      DEBUG_SORT   yLOG_value   ("x_cat"     , x_cat);
      if (x_cat <= 0) {
         DEBUG_SORT   yLOG_note    ("not an external function");
         continue;
      }
      /*---(categorize)------------------*/
      DEBUG_SORT   yLOG_char    ("x_cat"     , x_cat);
      ++s_tags [n].funcs;
      switch (x_cat) {
      case '-' :
         ++s_tags [n].cstd;
         break;
      case 'W' :
         ++s_tags [n].cstd;
         ++s_tags [n].writes;
         break;
      case 'R' :
         ++s_tags [n].cstd;
         ++s_tags [n].reads;
         break;
      case 'N' :
         ++s_tags [n].ncurses;
         break;
      case 'O' :
         ++s_tags [n].opengl;
         break;
      case 'Y' :
         ++s_tags [n].ylibs;
         break;
      case 'M' :
         ++s_tags [n].cstd;
         ++s_tags [n].memories;
         break;
      case 'P' :
         ++s_tags [n].cstd;
         ++s_tags [n].process;
         break;
      case 'S' :
         ++s_tags [n].cstd;
         ++s_tags [n].scalls;
         break;
      }
      /*---(done)------------------------*/
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


