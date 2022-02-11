/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*====================------------------------------------====================*/
/*===----                     function unit tests                      ----===*/
/*====================------------------------------------====================*/
static void  o___FUNCTION________o () { return; }

char
poly_units_by_func      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   int         rc          =    0;           /* generic return code            */
   char        x_recd      [LEN_RECD];      /* input record                   */
   char        x_verb      [LEN_LABEL];
   char        x_name      [LEN_TITLE];
   tFUNC      *x_func      = NULL;
   int         x_test      =    0;
   int         x_scrp      =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(quick calloff)------------------*/
   DEBUG_INPT   yLOG_char    ("g_unit"    , my.g_unit);
   if (my.g_unit != 'y') {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   rc = poly_shared_open ('u', NULL);
   DEBUG_INPT   yLOG_value   ("create"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk tags)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = poly_shared_read ('u', NULL, x_recd, NULL);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0)  {
         DEBUG_INPT   yLOG_note    ("reading of line failed or eof");
         break;
      }
      /*> printf ("%4d[%s]\n", strlen (x_recd), x_recd);                              <*/
      /*---(parse)-----------------------*/
      rc = poly_shared_parse_unit (x_recd, x_verb, x_name);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0)  {
         DEBUG_INPT   yLOG_note    ("reading of line failed or eof");
         break;
      }
      /*> printf ("%4d[%s]\n", strlen (x_name), x_name);                              <*/
      /*---(test change)-----------------*/
      if (strncmp (x_verb, "PREP", 4) == 0) {
         DEBUG_INPT   yLOG_note    ("increment tests, continue");
         ++x_test;
         continue;
      }
      if (strncmp (x_verb, "SCRP", 4) == 0) {
         DEBUG_INPT   yLOG_note    ("increment scripts, continue");
         ++x_scrp;
         continue;
      }
      /*---(idenfify function)-----------*/
      rc = poly_func_by_name (x_name, &x_func);
      DEBUG_INPT   yLOG_point   ("x_func"    , x_func);
      if (x_func == NULL) {
         DEBUG_INPT   yLOG_note    ("could not find function");
         continue;
      }
      DEBUG_INPT   yLOG_info    ("function"  , x_func->name);
      DEBUG_INPT   yLOG_point   ("project"   , x_func->file->proj);
      DEBUG_INPT   yLOG_point   ("g_proj"    , my.g_proj);
      /*---(verify the right project)-------*/
      while (x_func->file->proj != my.g_proj) {
         DEBUG_INPT   yLOG_note    ("project does not match, next function");
         rc = poly_func_cursor ('>', &x_func);
         DEBUG_INPT   yLOG_point   ("x_func"    , x_func);
         if (rc < 0)                              break;
         if (x_func == NULL)                     { rc = -1;  break; }
         DEBUG_INPT   yLOG_info    ("name"      , x_func->name);
         if (strcmp (x_name, x_func->name) != 0) { rc = -2;  break; }
      }
      if (rc < 0 || x_func == NULL) {
         DEBUG_INPT   yLOG_note    ("could not find function in right project");
         continue;
      }
      if (x_func->work == NULL) {
         DEBUG_INPT   yLOG_note    ("function does not have WORK setup");
         continue;
      }
      /*---(update counter)-----------------*/
      if (x_test != x_func->WORK_TSAVE) {
         DEBUG_INPT   yLOG_note    ("new unit file");
         ++x_func->WORK_TUNIT;
         x_func->WORK_TSAVE = x_test;
      }
      if (x_scrp != x_func->WORK_SSAVE) {
         DEBUG_INPT   yLOG_note    ("new script");
         ++x_func->WORK_SUNIT;
         x_func->WORK_SSAVE = x_scrp;
      }
      ++x_func->WORK_NUNIT;
      DEBUG_INPT   yLOG_note    ("incrementing unit test count");
      /*---(done)------------------------*/
   }
   /*---(wrapup)-------------------------*/
   rc = poly_shared_close ('u');
   DEBUG_INPT   yLOG_value   ("cleanup"   , rc);
   /*> printf ("poly_shared_close %d\n", rc);                                         <*/
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_units__scripts     (tFILE *a_file, int a_line, char *a_recd, tFUNC **a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   int         rc          =    0;           /* generic return code            */
   char        t           [LEN_LABEL] = "";
   static int  c           =    1;
   static int  d           =    1;
   static int  e           =    1;
   tFUNC      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(reset numbers)---------------*/
   if (a_line <= 1)  c = d = e = 1;
   /*---(func-like)-------------------*/
   if      (strncmp (a_recd, "PREP ", 5) == 0) {
      rc = poly_func_add (a_file, "prep", 's', a_line, &x_curr);
      /* add purpose from description */
      if (x_curr != NULL) {
         *a_func = x_curr;
         (*a_func)->beg      = a_line;
         (*a_func)->WORK_BEG = a_line;
         (*a_func)->end      = a_line;
         (*a_func)->WORK_END = a_line;
      }
      rc = 1;
   }
   else if (strncmp (a_recd, "SECT ", 5) == 0) {
      sprintf (t, "o___%02d___o", e++);
      rc = poly_func_add (a_file, t, '_', a_line, &x_curr);
      /* add purpose from description */
      if (x_curr != NULL) {
         *a_func = x_curr;
         (*a_func)->beg      = a_line;
         (*a_func)->WORK_BEG = a_line;
         (*a_func)->end      = a_line;
         (*a_func)->WORK_END = a_line;
      }
      rc = 1;
   }
   else if (strncmp (a_recd, "SCRP ", 5) == 0) {
      sprintf (t, "script_%02d", c++);
      rc = poly_func_add (a_file, t, 's', a_line, &x_curr);
      /* add purpose from description */
      if (x_curr != NULL) {
         *a_func = x_curr;
         (*a_func)->beg      = a_line;
         (*a_func)->WORK_BEG = a_line;
         (*a_func)->end      = a_line;
         (*a_func)->WORK_END = a_line;
      }
      rc = 1;
   }
   else if (strncmp (a_recd, "SHARED ", 7) == 0) {
      sprintf (t, "shared_%c", 'A' - 1 + d++);
      rc = poly_func_add (a_file, t, 'S', a_line, &x_curr);
      /* add purpose from description */
      /* change name to be single char lettes identifier in unit test */
      if (x_curr != NULL) {
         *a_func = x_curr;
         (*a_func)->beg      = a_line;
         (*a_func)->WORK_BEG = a_line;
         (*a_func)->end      = a_line;
         (*a_func)->WORK_END = a_line;
      }
      rc = 1;
   }
   else if (strncmp (a_recd, "WAVE "  , 5) == 0) {
      sprintf (t, "o___wave_%c___o", (uchar) 'è' - 1 + c++);
      rc = poly_func_add (a_file, t, '_', a_line, &x_curr);
      /* add purpose from description */
      /* change name to be single char lettes identifier in unit test */
      if (x_curr != NULL) {
         *a_func = x_curr;
         (*a_func)->beg      = a_line;
         (*a_func)->WORK_BEG = a_line;
         (*a_func)->end      = a_line;
         (*a_func)->WORK_END = a_line;
      }
      rc = 1;
   }
   else if (strncmp (a_recd, "stage " , 6) == 0) {
      sprintf (t, "stage_%02d", d++);
      rc = poly_func_add (a_file, t, '_', a_line, &x_curr);
      /* add purpose from description */
      /* change name to be single char lettes identifier in unit test */
      if (x_curr != NULL) {
         *a_func = x_curr;
         (*a_func)->beg      = a_line;
         (*a_func)->WORK_BEG = a_line;
         (*a_func)->end      = a_line;
         (*a_func)->WORK_END = a_line;
      }
      rc = 1;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
poly_units__classify    (tFILE *a_file, tFUNC *a_func, int a_line, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   int         rc          =    0;           /* generic return code            */
   char        g           =  '-';
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   l = strlen (a_recd);
   /*---(add a line)------------------*/
   DEBUG_INPT   yLOG_note    ("found empty");
   ++(my.COUNT_LINES);
   ++(a_file->proj->COUNT_LINES);
   ++(a_file->COUNT_LINES);
   if (a_func != NULL)  ++(a_func->COUNT_LINES);
   /*---(tag verbs)-------------------*/
   if (l > 10) {
      if      (strncmp (a_recd, "PREP "   , 5) == 0)  g = 'y';
      else if (strncmp (a_recd, "SECT "   , 5) == 0)  g = 'y';
      else if (strncmp (a_recd, "SHARED " , 7) == 0)  g = 'y';
      else if (strncmp (a_recd, "GROUP "  , 6) == 0)  g = 'y';
      else if (strncmp (a_recd, "SCRP "   , 5) == 0)  g = 'y';
      else if (strncmp (a_recd, "COND "   , 5) == 0)  g = 'y';
      else if (strncmp (a_recd, "WAVE "   , 5) == 0)  g = 'y';
      else if (strncmp (a_recd, "stage "  , 6) == 0)  g = 'y';
   }
   DEBUG_INPT   yLOG_char    ("g"         , g);
   /*---(empties)---------------------*/
   if (l <= 0) {
      DEBUG_INPT   yLOG_note    ("found empty");
      ++my.COUNT_EMPTY;
      ++(a_file->proj->COUNT_EMPTY);
      ++(a_file->COUNT_EMPTY);
      if (a_func != NULL)  ++(a_func->COUNT_EMPTY);
   }
   /*---(comments)--------------------*/
   else if (a_recd [0] == '#') {
      DEBUG_INPT   yLOG_note    ("found comment");
      ++(my.COUNT_DOCS);
      ++(a_file->proj->COUNT_DOCS);
      ++(a_file->COUNT_DOCS);
      if (a_func != NULL)  ++(a_func->COUNT_DOCS);
   }
   /*---(breaks/debugging)------------*/
   else if (g == 'y') {
      DEBUG_INPT   yLOG_note    ("found debugging");
      ++(my.COUNT_DEBUG);
      ++(a_file->proj->COUNT_DEBUG);
      ++(a_file->COUNT_DEBUG);
      if (a_func != NULL)  ++(a_func->COUNT_DEBUG);
   }
   /*---(others)----------------------*/
   else {
      DEBUG_INPT   yLOG_note    ("found code");
      ++(my.COUNT_CODE);
      ++(a_file->proj->COUNT_CODE);
      ++(a_file->COUNT_CODE);
      if (a_func != NULL)  ++(a_func->COUNT_CODE);
      ++(my.COUNT_SLOCL);
      ++(a_file->proj->COUNT_SLOCL);
      ++(a_file->COUNT_SLOCL);
      if (a_func != NULL)  ++(a_func->COUNT_SLOCL);
   }
   /*---(update lines)-------------------*/
   if (a_func != NULL && a_line > a_func->end) {
      a_func->end      = a_line;
      a_func->WORK_END = a_line;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_units_inventory    (tFILE *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   int         rc          =    0;           /* generic return code            */
   char        x_recd      [LEN_RECD];      /* input record                   */
   char        x_name      [LEN_TITLE];
   int         x_line      =    0;
   char        x_type      =  '-';
   int         x_len       =    0;             /* length of input record         */
   char        t           [LEN_TITLE];
   int         c           =    0;
   int         d           =    0;
   tFUNC      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(quick calloff)------------------*/
   DEBUG_INPT   yLOG_char    ("g_unit"    , my.g_unit);
   if (my.g_unit != 'y') {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare)------------------------*/
   rc = poly_shared_open ('s', a_file->name);
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk tags)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = poly_shared_read ('s', &x_line, x_recd, NULL);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0)  {
         DEBUG_INPT   yLOG_note    ("reading of line failed or eof");
         break;
      }
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      /*---(function-like)---------------*/
      rc = poly_units__scripts  (a_file, x_line, x_recd, &x_curr);
      rc = poly_units__classify (a_file, x_curr, x_line, x_recd);
      /*---(done)------------------------*/
   }
   /*---(wrapup)-------------------------*/
   rc = poly_shared_close ('s');
   DEBUG_INPT   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(summary)------------------------*/
   DEBUG_INPT   yLOG_value   ("count"     , poly_func_count ());
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

