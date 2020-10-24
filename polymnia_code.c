/*============================----beg-of-source---============================*/
#include  "polymnia.h"



static FILE *s_file = NULL;           /* source file */
static char  s_name [LEN_RECD] = "";  /* source file name */
static char  s_recd [LEN_RECD] = "";  /* current record (testing use) */



/*====================------------------------------------====================*/
/*===----                         header processing                    ----===*/
/*====================------------------------------------====================*/
static void  o___HEADERS_________o () { return; }

char
poly_code__unquote      (char *a_dst, char *a_src, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *x_beg       = NULL;
   char       *x_end       = NULL;
   int         x_len       =    0;
   /*---(check destination)--------------*/
   --rce;  if (a_dst == NULL) {
      return rce;
   }
   /*---(check source)-------------------*/
   --rce;  if (a_src == NULL) {
      a_dst [0] = '\0';
      return rce;
   }
   /*---(check empty)--------------------*/
   x_len = strlen (a_src);
   if (x_len == 0) {
      a_dst [0] = '\0';
      return 0;
   }
   /*---(set beginning)------------------*/
   x_beg = a_src;
   if (x_beg [0] == '"') {
      ++x_beg;
      --x_len;
   }
   strlcpy (a_dst, x_beg, a_max);
   /*---(set ending)---------------------*/
   x_end = a_dst + x_len - 1;
   if (x_end [0] == '"') {
      x_end [0] = '\0';
      --x_len;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_code__oneliners    (tFILE *a_file, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *q           = NULL;
   char       *r           = NULL;
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
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   /*---(filter)-------------------------*/
   --rce;  if (strncmp (a_recd, "#define",  7) != 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   q = strstr (a_recd, " P_");
   DEBUG_INPT   yLOG_point   ("q"         , q);
   --rce;  if (q == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ++q;
   DEBUG_INPT   yLOG_info    ("q"         , q);
   r = strchr (a_recd, '"');
   DEBUG_INPT   yLOG_point   ("r"         , r);
   --rce;  if (r == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("r"         , r);
   /*---(master)-------------------*/
   --rce;
   if      (strncmp (q, "P_FOCUS    ", 11) == 0)  poly_code__unquote (a_file->proj->focus   , r, LEN_DESC);
   else if (strncmp (q, "P_NICHE    ", 11) == 0)  poly_code__unquote (a_file->proj->niche   , r, LEN_DESC);
   else if (strncmp (q, "P_SUBJECT  ", 11) == 0)  poly_code__unquote (a_file->proj->subject , r, LEN_TITLE);
   else if (strncmp (q, "P_PURPOSE  ", 11) == 0)  poly_code__unquote (a_file->proj->purpose , r, LEN_HUND);
   /*---(greek)--------------------*/
   else if (strncmp (q, "P_NAMESAKE ", 11) == 0)  poly_code__unquote (a_file->proj->namesake, r, LEN_HUND);
   else if (strncmp (q, "P_HERITAGE ", 11) == 0)  poly_code__unquote (a_file->proj->heritage, r, LEN_HUND);
   else if (strncmp (q, "P_IMAGERY  ", 11) == 0)  poly_code__unquote (a_file->proj->imagery , r, LEN_HUND);
   else if (strncmp (q, "P_REASON   ", 11) == 0)  poly_code__unquote (a_file->proj->reason  , r, LEN_HUND);
   else if (strncmp (q, "P_ONELINE  ", 11) == 0)  sprintf (a_file->proj->oneline, "%s %s", a_file->proj->namesake, a_file->proj->subject);
   /*---(location)-----------------*/
   else if (strncmp (q, "P_BASENAME ", 11) == 0)  poly_code__unquote (a_file->proj->progname, r, LEN_TITLE);
   else if (strncmp (q, "P_FULLPATH ", 11) == 0)  poly_code__unquote (a_file->proj->fullpath, r, LEN_HUND);
   else if (strncmp (q, "P_SUFFIX   ", 11) == 0)  poly_code__unquote (a_file->proj->suffix  , r, LEN_LABEL);
   else if (strncmp (q, "P_CONTENT  ", 11) == 0)  poly_code__unquote (a_file->proj->content , r, LEN_TITLE);
   /*---(chars)--------------------*/
   else if (strncmp (q, "P_SYSTEM   ", 11) == 0)  poly_code__unquote (a_file->proj->systems , r, LEN_HUND);
   else if (strncmp (q, "P_LANGUAGE ", 11) == 0)  poly_code__unquote (a_file->proj->language, r, LEN_HUND);
   else if (strncmp (q, "P_CODESIZE ", 11) == 0)  poly_code__unquote (a_file->proj->codesize, r, LEN_DESC);
   /*---(created)------------------*/
   else if (strncmp (q, "P_AUTHOR   ", 11) == 0)  poly_code__unquote (a_file->proj->author  , r, LEN_TITLE);
   else if (strncmp (q, "P_CREATED  ", 11) == 0)  poly_code__unquote (a_file->proj->created , r, LEN_LABEL);
   else if (strncmp (q, "P_DEPENDS  ", 11) == 0)  poly_code__unquote (a_file->proj->depends , r, LEN_HUND);
   /*---(version)------------------*/
   else if (strncmp (q, "P_VERMAJOR ", 11) == 0)  poly_code__unquote (a_file->proj->vermajor, r, LEN_HUND);
   else if (strncmp (q, "P_VERMINOR ", 11) == 0)  poly_code__unquote (a_file->proj->verminor, r, LEN_HUND);
   else if (strncmp (q, "P_VERNUM   ", 11) == 0)  poly_code__unquote (a_file->proj->vernum  , r, LEN_LABEL);
   else if (strncmp (q, "P_VERTXT   ", 11) == 0)  poly_code__unquote (a_file->proj->vertxt  , r, LEN_HUND);
   /*---(notes)--------------------*/
   else if (strncmp (q, "P_PRIORITY ", 11) == 0)  ;
   else if (strncmp (q, "P_PRINCIPLE", 11) == 0)  ;
   else if (strncmp (q, "P_REMINDER" , 11) == 0)  ;
   /*---(complete)-----------------------*/
   else {
      a_file->proj->header [33] = '?';
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       source file processing                 ----===*/
/*====================------------------------------------====================*/
static void  o___SOURCES_________o () { return; }

char
poly_code__indent       (tFUNC *a_func, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         x_len       =    0;
   char        x_inside    =   -1;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("->name"    , a_func->name);
   DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   /*---(check inside)-------------------*/
   x_inside = poly_func_inside (a_func);
   if (x_inside != 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(calculate indent)---------------*/
   x_len = strlen (a_recd);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   for (i = 0; i < x_len; ++i) {
      if (a_recd [i] == ' ')   continue;
      if (i > a_func->WORK_INDENT) a_func->WORK_INDENT = i;
      break;
   }
   DEBUG_INPT   yLOG_value   ("indent"    , a_func->WORK_INDENT);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_code__counts       (tFILE *a_file, tFUNC *a_func, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_inside    =   -1;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_func);
   if (a_func == NULL) {
      DEBUG_DATA   yLOG_snote   ("function is null");
   } else {
      DEBUG_DATA   yLOG_spoint  (a_func->work);
      if (a_func->work == NULL) {
         DEBUG_DATA   yLOG_snote   ("a_func->work null");
      } else {
         DEBUG_DATA   yLOG_sint    (a_func->WORK_BEG);
         DEBUG_DATA   yLOG_sint    (a_func->WORK_END);
      }
   }
   x_inside = poly_func_inside (a_func);
   if (x_inside == 0)    DEBUG_DATA   yLOG_snote   ("inside a function");
   /*---(line counts)--------------------*/
   ++a_file->proj->COUNT_LINES;
   ++a_file->COUNT_LINES;
   if (x_inside == 0) ++a_func->COUNT_LINES;
   /*---(code counts)--------------------*/
   ++a_file->proj->COUNT_CODE;
   ++a_file->COUNT_CODE;
   if (x_inside == 0) ++a_func->COUNT_CODE;
   /*---(slocl counts)-------------------*/
   if (a_recd [0] != '#') {
      c = strldcnt (a_recd, ';', LEN_RECD);
      DEBUG_DATA   yLOG_sint    (c);
      if (c < 0)  c = 0;
      DEBUG_DATA   yLOG_snote   ("slocl");
      a_file->COUNT_SLOCL += c;
      a_file->proj->COUNT_SLOCL += c;
      if (x_inside == 0) a_func->COUNT_SLOCL += c;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_code__reserved     (tFILE *a_file, tFUNC *a_func, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_inside    =   -1;
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
   /*---(register a code line)-----------*/
   poly_code__counts (a_file, a_func, a_recd);
   DEBUG_INPT   yLOG_note    ("after counts");
   /*---(check inside)-------------------*/
   x_inside = poly_func_inside (a_func);
   DEBUG_INPT   yLOG_value   ("x_inside"  , x_inside);
   if (x_inside != 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(function level)-----------------*/
   if (a_func != NULL) {
      /*---(returns)---------------------*/
      if      (strstr (a_recd, " return "   ) != NULL)   poly_cats_logic (a_func, 'r');
      if      (strstr (a_recd, " return;"   ) != NULL)   poly_cats_logic (a_func, 'r');
      /*---(choices)---------------------*/
      if      (strstr (a_recd, " if "       ) != NULL)   poly_cats_logic (a_func, 'c');
      else if (strstr (a_recd, " if("       ) != NULL)   poly_cats_logic (a_func, 'c');
      else if (strstr (a_recd, " else "     ) != NULL)   poly_cats_logic (a_func, 'c');
      else if (strstr (a_recd, "}else "     ) != NULL)   poly_cats_logic (a_func, 'c');
      else if (strstr (a_recd, " else{"     ) != NULL)   poly_cats_logic (a_func, 'c');
      else if (strstr (a_recd, "}else{"     ) != NULL)   poly_cats_logic (a_func, 'c');
      if      (strstr (a_recd, " case "     ) != NULL)   poly_cats_logic (a_func, 'c');
      else if (strstr (a_recd, " default "  ) != NULL)   poly_cats_logic (a_func, 'c');
      else if (strstr (a_recd, " default:"  ) != NULL)   poly_cats_logic (a_func, 'c');
      /*---(loops)-----------------------*/
      if      (strstr (a_recd, " while "    ) != NULL)   poly_cats_logic (a_func, 'c');
      else if (strstr (a_recd, " while("    ) != NULL)   poly_cats_logic (a_func, 'c');
      if      (strstr (a_recd, " do "       ) != NULL)   poly_cats_logic (a_func, 'c');
      if      (strstr (a_recd, "}do "       ) != NULL)   poly_cats_logic (a_func, 'c');
      else if (strstr (a_recd, " do("       ) != NULL)   poly_cats_logic (a_func, 'c');
      else if (strstr (a_recd, "}do("       ) != NULL)   poly_cats_logic (a_func, 'c');
      if      (strstr (a_recd, " for "      ) != NULL)   poly_cats_logic (a_func, 'C');
      else if (strstr (a_recd, " for("      ) != NULL)   poly_cats_logic (a_func, 'C');
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       source file processing                 ----===*/
/*====================------------------------------------====================*/
static void  o___REVIEW__________o () { return; }

char
poly_code__open         (tFILE *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tSTAT       st;
   int         rci         =    0;
   char        x_cmd       [LEN_RECD];      /* ctags command                  */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file != NULL) {
      DEBUG_INPT   yLOG_note    ("source s_file already open with another");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->name);
   /*---(check file)---------------------*/
   rci = lstat (a_file->name, &st);
   DEBUG_INPT   yLOG_value   ("lstat"     , rci);
   --rce; if (rci < 0) {
      DEBUG_INPT   yLOG_note    ("file does not exist, can not read");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(check regular file)-------------*/
   --rce;  if (!S_ISREG (st.st_mode)) {
      DEBUG_INPT   yLOG_note    ("not a regular file, rejected");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(open)---------------------------*/
   s_file = fopen (a_file->name, "r");
   DEBUG_INPT   yLOG_point   ("s_file"         , s_file);
   --rce;  if (s_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   strlcpy (s_name, a_file->name, LEN_RECD);
   DEBUG_INPT   yLOG_note    ("openned successfully");
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_code__read         (int *a_line, char *a_curr, char *a_prev)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         x_len       =   0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file == NULL) {
      DEBUG_INPT   yLOG_note    ("source s_file not open");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_line"    , a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_curr"    , a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_prev"    , a_prev);
   --rce;  if (a_prev == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read)------------------------*/
   strlcpy (a_prev, a_curr, LEN_RECD);
   fgets  (a_curr, LEN_RECD, s_file);
   --rce;  if (feof (s_file))  {
      DEBUG_INPT   yLOG_note    ("end of file");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update line)-----------------*/
   ++(*a_line);
   DEBUG_INPT   yLOG_value   ("*a_line"   , *a_line);
   /*---(prepare)---------------------*/
   x_len = strlen (a_curr);
   if (x_len > 0)  a_curr [--x_len] = '\0';
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   DEBUG_INPT   yLOG_info    ("a_curr"    , a_curr);
   DEBUG_INPT   yLOG_info    ("a_prev"    , a_prev);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_code__close        (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          =   0;           /* generic return code            */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file == NULL) {
      DEBUG_INPT   yLOG_note    ("source s_file not open");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close file)---------------------*/
   rc = fclose (s_file);
   DEBUG_INPT   yLOG_point   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(ground pointer)-----------------*/
   s_file = NULL;
   strlcpy (s_name, ""          , LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_code_function      (tFUNC *a_func, char *a_recd, char *a_prev)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   int        x_len        =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      a_func->ready = 'e';
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(return)-------------------------*/
   rc = poly_func_return (a_func, a_recd, a_prev);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(purpose)------------------------*/
   --rce;  if (a_func->STATS_SINGLE == '-') {
      p  = strstr (a_prev, "/*");
      if (p != NULL) {
         x_len = p - a_prev;
         rc = poly_func_purpose (a_func, a_prev + x_len);
         if (rc < 0) {
            DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
   } else {
      rc = poly_func_purpose (a_func, "/* */");
   }
   /*---(parameters)---------------------*/
   rc = poly_func_params (a_func, a_recd);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        helpers                               ----===*/
/*====================------------------------------------====================*/
static void  o___HELPERS_________o () { return; }

char
poly_code_nextfunc      (tFILE *a_file, tFUNC **a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_func);
   /*---(first time)---------------------*/
   --rce;  if (*a_func == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      *a_func = a_file->head;
   }
   /*---(next time)----------------------*/
   else { 
      DEBUG_DATA   yLOG_snote   ("next");
      *a_func = (*a_func)->next;
   }
   DEBUG_DATA   yLOG_spoint  (*a_func);
   /*---(trouble)-------------------------------*/
   --rce;  if (*a_func == NULL) {
      DEBUG_DATA   yLOG_snote   ("first/next is null");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_code__before       (tFILE *a_file, tFUNC **a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("*a_func"   , *a_func);
   /*---(check function)--------------*/
   if (*a_func == NULL) {
      rc = poly_code_nextfunc (a_file, a_func);
   }
   /*---(check after)-----------------*/
   else if ((*a_func)->WORK_END > 0) {
      rc = poly_code_nextfunc (a_file, a_func);
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_code__current      (tFILE *a_file, int a_line, tFUNC *a_func, char *a_curr, char *a_prev)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_full      [LEN_RECD]  = "";
   char        x_recd      [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("a_line"    , a_line);
   DEBUG_INPT   yLOG_point   ("a_curr"    , a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_curr"    , a_curr);
   /*---(prepare)---------------------*/
   strlcpy   (x_full, a_curr   , LEN_RECD);
   strltrim  (x_full, ySTR_BOTH, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("x_full"    , x_full);
   strlunall (x_recd, a_curr   , LEN_RECD);
   strltrim  (x_recd, ySTR_BOTH, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
   /*---(check tail of file)----------*/
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   if (a_func == NULL || a_func->WORK_END >= 0) {
      DEBUG_INPT   yLOG_note    ("file tail, after all functions");
      rc = poly_debug_line  (a_file, a_func, x_full);
      if (rc < 0)  rc = poly_code__reserved     (a_file, a_func, x_recd);
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(found header)----------------*/
   DEBUG_INPT   yLOG_value   ("line"      , a_func->line);
   if (a_line == a_func->line) {
      DEBUG_INPT   yLOG_note    ("FUNCTION HEADER FOUND");
      poly_code_function (a_func, x_full, a_prev);
   }
   /*---(check single line)-----------*/
   if (a_func->STATS_SINGLE == 'y') {
      DEBUG_DATA   yLOG_note    ("single liner entry");
      poly_func_enter (a_func, a_line);
   }
   /*---(check debugging)-------------*/
   if (a_func->STATS_SINGLE != 'y') {
      DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
      rc = poly_debug_line  (a_file, a_func, x_full);
   } else
      rc = -1;
   /*---(check source code)-----------*/
   if (rc < 0)  { 
      rc = poly_code__reserved     (a_file, a_func, x_recd);
      rc = poly_code__indent       (a_func, a_curr);
   }
   /*---(check single line)-----------*/
   if (a_func->STATS_SINGLE == 'y') {
      DEBUG_DATA   yLOG_note    ("single liner exit");
      poly_func_exit  (a_func, a_line);
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_code__after        (tFILE *a_file, int a_line, tFUNC *a_func, char *a_curr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_line"    , a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   if (a_func == NULL) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(beginning)-------------------*/
   if (a_func->WORK_BEG <  0) {
      if (a_curr [0] == '{') {
         DEBUG_INPT   yLOG_note    ("beg brace");
         poly_func_enter (a_func, a_line);
      }
   }
   /*---(ending)----------------------*/
   else if (a_func->WORK_END <  0) {
      if (a_curr [0] == '}') {
         DEBUG_INPT   yLOG_note    ("end brace");
         poly_func_exit (a_func, a_line);
         --a_func->COUNT_LINES;
         --a_func->COUNT_CODE;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_code_review        (tFILE *a_file)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_curr      [LEN_RECD];
   char        x_prev      [LEN_RECD];
   char        x_fixed     [LEN_RECD];
   int         x_len       =    0;          /* length of input record         */
   int         x_line      =    0;
   tFUNC      *x_func      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open file)----------------------*/
   rc = poly_code__open (a_file);
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0 || s_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   --rce;  while (rc >= 0) {
      /*---(read)------------------------*/
      rc = poly_code__read  (&x_line, x_curr, x_prev);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0)    break;
      DEBUG_INPT   yLOG_value   ("x_line"    , x_line);
      /*---(handle)----------------------*/
      if (a_file->type == 'h') {
         DEBUG_INPT   yLOG_note    ("header file (h) line");
         poly_code__oneliners (a_file, x_curr);
         rc = poly_code__current (a_file, 0     , NULL  , x_curr, x_prev);
      } else {
         DEBUG_INPT   yLOG_note    ("source file (c) line");
         rc = poly_code__before  (a_file, &x_func);
         rc = poly_code__current (a_file, x_line, x_func, x_curr, x_prev);
         if (x_func != NULL)  rc = poly_vars_find (x_func, x_line, x_curr, '-');
         rc = poly_code__after   (a_file, x_line, x_func, x_curr);
      }
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = poly_code__close ();
   DEBUG_INPT   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0 || s_file != NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_code__unit         (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   char        r           [LEN_RECD] = "";
   char        s           [LEN_LABEL]= "";
   tFUNC      *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "CODE unit        : function number unknown");
   if (strcmp (a_question, "work"      )     == 0) {
      u = (tFUNC *) poly_btree_entry (B_FUNCS, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->WORK_CHOICE > 0)  sprintf (s, " %3dc", u->WORK_CHOICE);
         else                     sprintf (s, "   ·c");
         strlcat (r, s, LEN_RECD);
         if (u->WORK_RETURN > 0)  sprintf (s, " %3dr", u->WORK_RETURN);
         else                     sprintf (s, "   ·r");
         strlcat (r, s, LEN_RECD);
         if (u->WORK_INDENT > 0)  sprintf (s, " %3di", u->WORK_INDENT);
         else                     sprintf (s, "   ·i");
         strlcat (r, s, LEN_RECD);
         snprintf (unit_answer, LEN_RECD, "CODE work   (%2d) : %-22.22s  %s", i, t, r);
      }  else
         snprintf (unit_answer, LEN_RECD, "CODE work   (%2d) : %-22.22s    -c   -r   -i", i, t);
   }
   else if (strcmp (a_question, "file"      )     == 0) {
      if (s_file != NULL)  sprintf  (t, "[%.20s]", s_name);
      snprintf (unit_answer, LEN_RECD, "CODE file        : %c  %-10p  %s", (s_file == NULL) ? '-' : 'y', s_file, t);
      return unit_answer;
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
