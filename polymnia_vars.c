/*============================----beg-of-source---============================*/
#include  "polymnia.h"


#define     MAX_VARS     1000
typedef     struct     cVARS      tVARS;
struct cVARS {
   char        scope;                       /* (g)lobal, (f)ile               */
   tFILE      *file;                        /* file pointer                   */
   char        len;                         /* variable name length           */
   char        name        [LEN_TITLE];     /* variable name                  */
   char        type;                        /* (v)var, (m)macro               */
};
tVARS        s_vars        [MAX_VARS];
int          s_nvar        = 0;
int          s_nglobal     = 0;



static char *s_bad       = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";
static char *s_macro     = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_vars__purge        (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_VARS; ++i) {
      s_vars [i].file     = NULL;
      s_vars [i].scope    = '-';
      s_vars [i].len      = 0;
      s_vars [i].name [0] = '\0';
      s_vars [i].type     = '-';
   }
   s_nvar    = 0;
   s_nglobal = 0;
   return 0;
}

char
poly_vars_init          (void)
{
   poly_vars__purge ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       data adding                            ----===*/
/*====================------------------------------------====================*/
static void  o___DATA____________o () { return; }

char
poly_vars__confirm      (char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         x_len       =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL) return rce;
   /*---(prepare)------------------------*/
   x_len  = strlen (a_name);
   /*---(walk variables)-----------------*/
   for (i = 0; i < s_nvar; ++i) {
      if (s_vars [i].len      != x_len)           continue;
      if (s_vars [i].name [0] != a_name [0])      continue;
      if (strcmp (s_vars [i].name, a_name) != 0)  continue;
      return 1;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_vars__push         (tFILE *a_file, char *a_name, char a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char        x_type      =  '-';
   /*---(defense)------------------------*/
   --rce;  if (s_nvar >= MAX_VARS)  return rce;
   --rce;  if (a_file == NULL)      return rce;
   x_type = a_file->type;
   --rce;  if (x_type == 'h' && s_nvar > s_nglobal)  return rce;
   --rce;  if (a_name == NULL)      return rce;
   /*---(prepare)------------------------*/
   x_len  = strlen (a_name);
   --rce;  if (x_len  <= 0)         return rce;
   /*---(confirm)------------------------*/
   rc = poly_vars__confirm (a_name);
   --rce;  if (rc != 0)  return rce;
   /*---(add entry)----------------------*/
   if (x_type == 'h')   s_vars [s_nvar].scope = 'g';
   else                 s_vars [s_nvar].scope = 'f';
   s_vars [s_nvar].file = a_file;
   s_vars [s_nvar].len  = x_len;
   strlcpy (s_vars [s_nvar].name, a_name, LEN_TITLE);
   if (a_type == 'm')   s_vars [s_nvar].type  = 'm';
   else                 s_vars [s_nvar].type  = 'v';
   /*---(update counters)----------------*/
   if (s_vars [s_nvar].scope == 'g')  ++s_nglobal;
   ++s_nvar;
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_vars__pop_file     (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_VARS; ++i) {
      if (s_vars [i].scope != 'f')  continue;
      s_vars [i].file     = NULL;
      s_vars [i].scope    = '-';
      s_vars [i].len      = 0;
      s_vars [i].name [0] = '\0';
      s_vars [i].type     = '-';
      --s_nvar;
   }
   return 0;
}

char         /*--> read and parse crontab lines ----------[ ------ [ ------ ]-*/
poly_vars_inventory     (tFILE *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   int         rc          =    0;           /* generic return code            */
   char        x_recd      [LEN_RECD];      /* input record                   */
   int         x_len       =    0;             /* length of input record         */
   int         c           =    0;
   char       *p           = NULL;
   char       *q           = NULL;
   char       *r           = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(clear file vars)----------------*/
   rc = poly_vars__pop_file ();
   DEBUG_INPT   yLOG_value   ("clear"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare)------------------------*/
   rc = poly_shared_open ('v', a_file->name);
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk tags)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = poly_shared_read ('v', NULL, x_recd, NULL);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0)  {
         DEBUG_INPT   yLOG_note    ("reading of line failed or eof");
         break;
      }
      /*---(name)------------------------*/
      p = strtok_r (x_recd, " ", &r);
      DEBUG_INPT   yLOG_point   ("p"         , p);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("variable name not found");
         continue;
      }
      DEBUG_INPT   yLOG_info    ("p"         , p);
      /*---(type)------------------------*/
      q = strtok_r (NULL  , " ", &r);
      DEBUG_INPT   yLOG_point   ("q"         , q);
      if (q == NULL) {
         DEBUG_INPT   yLOG_note    ("variable type not found");
         continue;
      }
      DEBUG_INPT   yLOG_info    ("q"         , q);
      /*---(name)------------------------*/
      rc = poly_vars__push (a_file, p, q [0]);
      DEBUG_INPT   yLOG_value   ("push"      , rc);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("something wrong with record");
         continue;
      }
      DEBUG_INPT   yLOG_complex ("counts"    , "%3da, %3dg, %3dc", s_nvar, s_nglobal, c);
      /*---(done)------------------------*/
      ++c;
   }
   /*---(wrapup)-------------------------*/
   rc = poly_shared_close ('v');
   DEBUG_INPT   yLOG_value   ("cleanup"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(summary)------------------------*/
   DEBUG_INPT   yLOG_value   ("c"         , c);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      external macros                         ----===*/
/*====================------------------------------------====================*/
static void  o___EXTERNAL________o () { return; }

char
poly_vars__extern_tally (tFUNC *a_func, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   tEXTERN    *x_ext       = NULL;
   /*---(no matter what)-----------------*/
   ++(a_func->WORK_PUSE);
   /*---(find external)------------------*/
   x_ext   = (tEXTERN *) poly_extern_search (a_name);
   DEBUG_INPT   yLOG_point   ("x_ext"     , x_ext);
   /*---(assign category)----------------*/
   if (x_ext != NULL) {
      switch (x_ext->cat) {
      case 'Y' : ++(a_func->WORK_YUSE);         break;
      case 'y' : ++(a_func->WORK_YUSE);         break;
      case 'C' : ++(a_func->WORK_MUSE);         break;
      case 'N' : ++(a_func->WORK_MUSE);         break;
      case 'O' : ++(a_func->WORK_MUSE);         break;
      case 'X' : ++(a_func->WORK_MUSE);         break;
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_vars__extern_find  (tFUNC *a_func, int a_line, char *a_recd, char a_act)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   char        t           [LEN_RECD]  = "";
   int         i           =    0;
   char       *b           = NULL;
   char       *e           = NULL;
   char        x_name      [LEN_TITLE] = "";
   int         n           =    0;
   tEXTERN    *x_ext       = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_func   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("work"      , a_func->work);
   --rce;  if (a_func->work  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_recd   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   strlunall (t, a_recd, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("t"         , t);
   x_len = strlen (t);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   if (x_len <= 0) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(look for potential macros)------*/
   for (i = 0; i <= x_len; ++i) {
      DEBUG_INPT   yLOG_complex ("check"     , "%2d, %c, %p, %d", i, chrvisible (t [i]), b, n);
      /*---(not a macro letter)----------*/
      if (t [i] == '\0' || strchr (s_macro, t [i]) == NULL) {
         DEBUG_INPT   yLOG_note    ("not a macro letter");
         /*---(finish existing)----------*/
         if (b != NULL && n > 0) {
            DEBUG_INPT   yLOG_note    ("was inside a macro");
            if (n > 6 && strncmp ("DEBUG_", b, 6) == 0) {
               DEBUG_INPT   yLOG_note    ("debugging macro/guard, skipping");
            } else if (n == 4 && strncmp ("NULL", b, 4) == 0) {
               DEBUG_INPT   yLOG_note    ("common NULL, skipping");
            } else if (t [i] == '\0' || strchr (s_bad, t [i]) == NULL) {
               DEBUG_INPT   yLOG_note    ("good finish, increment");
               strlcpy (x_name, b, n + 1);
               DEBUG_INPT   yLOG_info    ("macro name", x_name);
               if (a_act == '-')   poly_vars__extern_tally (a_func, x_name);
            } else {
               DEBUG_INPT   yLOG_note    ("finished wrong");
            }
         }
         DEBUG_INPT   yLOG_note    ("reset macro");
         b = NULL;
         n = 0;
         continue;
      }
      /*---(not started)-----------------*/
      if (b == NULL) {
         if (strchr ("0123456789_", t [i]) != NULL) {
            DEBUG_INPT   yLOG_note    ("macro can not start with number or underscore");
            continue;
         }
         if (i == 0 || (i > 0 && strchr (s_bad, t [i - 1]) == NULL)) {
            DEBUG_INPT   yLOG_note    ("starting a new macro");
            b = t + i;
            n = 1;
         } else {
            DEBUG_INPT   yLOG_note    ("not a macro start");
         }
         continue;
      }
      /*---(continuing)------------------*/
      DEBUG_INPT   yLOG_note    ("continue on macro");
      ++n;
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     internal macros/vars                     ----===*/
/*====================------------------------------------====================*/
static void  o___INTERNAL________o () { return; }

char
poly_vars__intern_tally (tFUNC *a_func, int n)
{
   DEBUG_INPT   yLOG_char    ("scope"     , s_vars [n].scope);
   if (s_vars [n].scope == 'g') {
      if (s_vars [n].type == 'v')  ++(a_func->WORK_GVARS);
      else                         ++(a_func->WORK_GUSE);
   } else {
      if (s_vars [n].type == 'v')  ++(a_func->WORK_FVARS);
      else                         ++(a_func->WORK_FUSE);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_vars__intern_find  (tFUNC *a_func, int a_line, char *a_recd, char a_act)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   char        t           [LEN_RECD]  = "";
   int         i           =    0;
   char       *b           = NULL;
   char       *e           = NULL;
   char        x_name      [LEN_TITLE] = "";
   int         n           =    0;
   char       *x_end       = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_func   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("work"      , a_func->work);
   --rce;  if (a_func->work  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_recd   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   strlunall (t, a_recd, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("t"         , t);
   x_len = strlen (t);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   if (x_len <= 0) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   x_end = t + x_len - 1;
   DEBUG_INPT   yLOG_point   ("x_end"     , x_end);
   /*---(walk variables)-----------------*/
   DEBUG_INPT   yLOG_value   ("s_nvar"    , s_nvar);
   for (i = 0; i < s_nvar; ++i) {
      DEBUG_INPT   yLOG_info    ("search"    , s_vars [i].name);
      b = strstr (t, s_vars [i].name);
      DEBUG_INPT   yLOG_point   ("b"         , b);
      while (b != NULL && b < x_end) {
         e = b + s_vars [i].len;
         if (b != t)  DEBUG_INPT   yLOG_char    ("b [-1]"    , b [-1]);
         if (b == t || strchr (s_bad, b [-1]) == NULL) {
            if (e != x_end)   DEBUG_INPT   yLOG_char    ("e [0]"     , e [0]);
            if (e == x_end || strchr (s_bad, e [0]) == NULL) {
               if (a_act == '-')  poly_vars__intern_tally (a_func, i);
               /*> DEBUG_INPT   yLOG_char    ("scope"     , s_vars [i].scope);        <*/
               /*> if (s_vars [i].scope == 'g') {                                     <* 
                *>    if (s_vars [i].type == 'v')  ++(a_func->WORK_GVARS);            <* 
                *>    else                         ++(a_func->WORK_GUSE);             <* 
                *> } else {                                                           <* 
                *>    if (s_vars [i].type == 'v')  ++(a_func->WORK_FVARS);            <* 
                *>    else                         ++(a_func->WORK_FUSE);             <* 
                *> }                                                                  <*/
            }
         }
         b = strstr (e + 1, s_vars [i].name);
         DEBUG_INPT   yLOG_point   ("b"         , b);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_vars_find          (tFUNC *a_func, int a_line, char *a_recd, char a_act)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         x_len       =    0;
   char        t           [LEN_RECD]  = "";
   char       *b           = NULL;
   char       *e           = NULL;
   char       *x_end       = NULL;
   char        x_name      [LEN_TITLE] = "";
   int         n           =    0;
   tEXTERN    *x_ext       = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_complex ("args"      , "%p, %p", a_func, a_recd);
   /*---(defense)------------------------*/
   --rce;  if (a_func   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("work"      , a_func->work);
   --rce;  if (a_func->work  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_recd   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   strlunall (t, a_recd, LEN_RECD);
   x_len = strlen (t);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("t"         , t);
   /*---(look for potential macros)------*/
   for (i = 0; i < x_len; ++i) {
      DEBUG_INPT   yLOG_complex ("check"     , "%2d, %c, %p, %d", i, t [i], b, n);
      /*---(not a macro letter)----------*/
      if (strchr (s_macro, t [i]) == NULL) {
         DEBUG_INPT   yLOG_note    ("not a macro letter");
         /*---(finish existing)----------*/
         if (b != NULL && n > 0) {
            DEBUG_INPT   yLOG_note    ("was inside a macro");
            if (n > 6 && strncmp ("DEBUG_", b, 6) == 0) {
               DEBUG_INPT   yLOG_note    ("debugging macros, skipping");
            } else if (n == 4 && strncmp ("NULL", b, 4) == 0) {
               DEBUG_INPT   yLOG_note    ("common NULL, skipping");
            } else if (strchr (s_bad, t [i]) == NULL) {
               DEBUG_INPT   yLOG_note    ("good finish, increment");
               ++(a_func->WORK_PUSE);
               strlcpy (x_name, b, n + 1);
               DEBUG_INPT   yLOG_info    ("macro name", x_name);
               x_ext   = (tEXTERN *) poly_extern_search (x_name);
               DEBUG_INPT   yLOG_point   ("x_ext"     , x_ext);
               if (x_ext != NULL) {
                  switch (x_ext->cat) {
                  case 'Y' : ++(a_func->WORK_YUSE);         break;
                  case 'y' : ++(a_func->WORK_YUSE);         break;
                  case 'C' : ++(a_func->WORK_MUSE);         break;
                  case 'N' : ++(a_func->WORK_MUSE);         break;
                  case 'O' : ++(a_func->WORK_MUSE);         break;
                  case 'X' : ++(a_func->WORK_MUSE);         break;
                  }
               }
            } else {
               DEBUG_INPT   yLOG_note    ("finished wrong");
            }
         }
         DEBUG_INPT   yLOG_note    ("reset macro");
         b = NULL;
         n = 0;
         continue;
      }
      /*---(not started)-----------------*/
      if (b == NULL) {
         if (strchr ("0123456789_", t [i]) != NULL) {
            DEBUG_INPT   yLOG_note    ("macro can not start with number or underscore");
            continue;
         }
         if (i == 0 || (i > 0 && strchr (s_bad, t [i - 1]) == NULL)) {
            DEBUG_INPT   yLOG_note    ("starting a new macro");
            b = t + i;
            n = 1;
         } else {
            DEBUG_INPT   yLOG_note    ("not a macro start");
         }
         continue;
      }
      /*---(continuing)------------------*/
      DEBUG_INPT   yLOG_note    ("continue on macro");
      ++n;
      /*---(done)------------------------*/
   }
   /*---(prepare)------------------------*/
   x_end = t + x_len - 1;
   DEBUG_INPT   yLOG_point   ("x_end"     , x_end);
   /*---(walk variables)-----------------*/
   DEBUG_INPT   yLOG_value   ("s_nvar"    , s_nvar);
   for (i = 0; i < s_nvar; ++i) {
      DEBUG_INPT   yLOG_info    ("search"    , s_vars [i].name);
      b = strstr (t, s_vars [i].name);
      DEBUG_INPT   yLOG_point   ("b"         , b);
      while (b != NULL && b < x_end) {
         e = b + s_vars [i].len;
         if (b != t)  DEBUG_INPT   yLOG_char    ("b [-1]"    , b [-1]);
         if (b == t || strchr (s_bad, b [-1]) == NULL) {
            if (e != x_end)   DEBUG_INPT   yLOG_char    ("e [0]"     , e [0]);
            if (e == x_end || strchr (s_bad, e [0]) == NULL) {
               DEBUG_INPT   yLOG_char    ("scope"     , s_vars [i].scope);
               if (s_vars [i].scope == 'g') {
                  if (s_vars [i].type == 'v')  ++(a_func->WORK_GVARS);
                  else                         ++(a_func->WORK_GUSE);
               } else {
                  if (s_vars [i].type == 'v')  ++(a_func->WORK_FVARS);
                  else                         ++(a_func->WORK_FUSE);
               }
            }
         }
         b = strstr (e + 1, s_vars [i].name);
         DEBUG_INPT   yLOG_point   ("b"         , b);
      }
   }
   a_func->WORK_OUSE = a_func->WORK_PUSE - a_func->WORK_GUSE - a_func->WORK_FUSE - a_func->WORK_MUSE - a_func->WORK_YUSE;
   DEBUG_INPT   yLOG_value   ("gvars"   , a_func->WORK_GVARS);
   DEBUG_INPT   yLOG_value   ("fvars"   , a_func->WORK_FVARS);
   DEBUG_INPT   yLOG_value   ("guse"    , a_func->WORK_GUSE);
   DEBUG_INPT   yLOG_value   ("fuse"    , a_func->WORK_FUSE);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       function-level                         ----===*/
/*====================------------------------------------====================*/
static void  o___FUNCTION________o () { return; }

char
poly_vars_reset         (tFUNC *a_func)
{
   a_func->WORK_GVARS = 0;
   a_func->WORK_FVARS = 0;
   a_func->WORK_PUSE  = 0;
   a_func->WORK_FUSE  = 0;
   a_func->WORK_GUSE  = 0;
   a_func->WORK_MUSE  = 0;
   a_func->WORK_YUSE  = 0;
   a_func->WORK_OUSE  = 0;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-[ unit test accessor ]---------------------[us2---·A-7·6--·B21-]¬[----·T-B1H---·---·----]¬[---·------]*/
poly_vars__unit         (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_TITLE] = "[]";
   char        s           [LEN_RECD]  = "[]";
   tFUNC      *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "VARS unit        : question unknown");
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "VARS count       : %3da  %3dg", s_nvar, s_nglobal);
      return unit_answer;
   }
   else if (strcmp (a_question, "entry"     )     == 0) {
      if (s_vars [i].file != NULL)  sprintf (t, "[%0.15s]", s_vars [i].file->name);
      sprintf (s, "[%0.15s]", s_vars [i].name);
      snprintf (unit_answer, LEN_RECD, "VARS entry  (%2d) : %-17.17s   %c %c   %2d%s", i, t, s_vars [i].scope, s_vars [i].type, strlen (s_vars [i].name), s);
      return unit_answer;
   }
   else if (strcmp (a_question, "func"      )     == 0) {
      u = (tFUNC *) poly_btree_entry (B_FUNCS, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         sprintf  (s, "%3dn %3df %3dg      %3dp %3df %3dg %3dm %3dy %3do",
               u->WORK_LVARS, u->WORK_FVARS, u->WORK_GVARS, 
               u->WORK_PUSE , u->WORK_FUSE , u->WORK_GUSE , 
               u->WORK_MUSE , u->WORK_YUSE , u->WORK_OUSE );
         snprintf (unit_answer, LEN_RECD, "VARS func   (%2d) : %-22.22s  %s", i, t, s);
      }  else
         snprintf (unit_answer, LEN_RECD, "VARS func   (%2d) : []                       0n   0f   0g      0p   0f   0g   0c   0y   0o", i);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}





