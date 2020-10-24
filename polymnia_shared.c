/*============================----beg-of-source---============================*/
#include  "polymnia.h"



#define     NEW_CFLOW     "cflow  -x $(ls -1 *.c 2> /dev/null | grep -vx unit) > %s  2> /dev/null"
#define     DEL_ANY       "rm -f %s  2> /dev/null"
#define     NEW_CTAGS     "ctags  --language-force=c -x --sort=no --file-scope=yes  --c-kinds=pfl %s > %s  2> /dev/null"
#define     NEW_VARS      "ctags  --language-force=c -x --sort=no                   --c-kinds=vxd %s > %s  2> /dev/null"

static      char       *s_valid       = "ftmcxve";
static      char        s_ctags       [LEN_RECD] = "";
static      char        s_code        [LEN_RECD] = "";
static      char        s_vars        [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                       support function                       ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_shared__pointer    (char a_type, FILE ***a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(assign pointer)-----------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   DEBUG_INPT   yLOG_point   ("*a_file"   , *a_file);
   --rce;  switch (a_type) {
   case 'f' :  /* cflow */
      *a_file  = &(my.f_cflow);
      break;
   case 't' :  /* ctags */
      *a_file  = &(my.f_ctags);
      break;
   case 'm' :  /* mystery calls */
      *a_file  = &(my.f_mystry);
      break;
   case 'c' :  /* c source files */
      *a_file  = &(my.f_code);
      break;
   case 'v' :  /* variables */
      *a_file  = &(my.f_vars);
      break;
   case 'e' :  /* external */
      *a_file  = &(my.f_extern);
      break;
   default  :
      DEBUG_INPT   yLOG_note    ("type unknown");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("*a_file"   , *a_file);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       connecting to file                     ----===*/
/*====================------------------------------------====================*/
static void  o___CONNECT_________o () { return; }

char
poly_shared_open        (char a_type, char *a_focus)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         rci         =    0;
   char        x_cmd       [LEN_RECD]  = "";
   char        x_source    [LEN_RECD]  = "";
   char        x_use       [LEN_RECD]  = "";
   char        x_mode      [LEN_TERSE] = "";
   tSTAT       st;
   FILE      **x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_char    ("a_type"    , a_type);
   --rce;  if (a_type == 0 || strchr (s_valid, a_type) == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_focus"   , a_focus);
   --rce;  if (strchr ("tc", a_type) != NULL && a_focus == NULL) {
      DEBUG_INPT   yLOG_note    ("need a focus name");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_shared__pointer (a_type, &x_file);
   DEBUG_INPT   yLOG_value   ("file"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("*x_file"   , *x_file);
   /*---(assign name)--------------------*/
   --rce;  switch (a_type) {
   case 'f' :  /* cflow */
      strlcpy (x_use   , F_CFLOW , LEN_RECD);
      strlcpy (x_mode  , "rt"    , LEN_TERSE);
      break;
   case 't' :  /* ctags */
      strlcpy (x_source, a_focus , LEN_RECD);
      strlcpy (x_use   , F_CTAGS , LEN_RECD);
      strlcpy (x_mode  , "rt"    , LEN_TERSE);
      break;
   case 'm' :  /* mystery calls */
      strlcpy (x_use   , F_MYSTRY, LEN_RECD);
      strlcpy (x_mode  , "wt"    , LEN_TERSE);
      break;
   case 'c' :  /* c source files */
      strlcpy (x_source, a_focus , LEN_RECD);
      strlcpy (x_use   , a_focus , LEN_RECD);
      strlcpy (x_mode  , "rt"    , LEN_TERSE);
      break;
   case 'v' :  /* variables */
      strlcpy (x_source, a_focus , LEN_RECD);
      strlcpy (x_use   , F_VARS  , LEN_RECD);
      strlcpy (x_mode  , "rt"    , LEN_TERSE);
      break;
   case 'e' :  /* external */
      strlcpy (x_source, my.n_extern, LEN_RECD);
      strlcpy (x_use   , my.n_extern, LEN_RECD);
      strlcpy (x_mode  , "rt"    , LEN_TERSE);
      break;
   default  :
      DEBUG_INPT   yLOG_note    ("type unknown");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("x_source"   , x_source);
   DEBUG_INPT   yLOG_info    ("x_use"      , x_use);
   DEBUG_INPT   yLOG_info    ("x_mode"     , x_mode);
   DEBUG_INPT   yLOG_point   ("*x_file"   , *x_file);
   --rce;  if (*x_file != NULL) {
      DEBUG_INPT   yLOG_note    ("already open for another");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pre-check)----------------------*/
   if (strcmp (x_source, "") != 0) {
      rci = lstat (x_source, &st);
      DEBUG_INPT   yLOG_value   ("lstat"     , rci);
      --rce; if (rci < 0) {
         DEBUG_INPT   yLOG_note    ("file does not exist, can not read");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      --rce;  if (!S_ISREG (st.st_mode)) {
         DEBUG_INPT   yLOG_note    ("not a regular file, rejected");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      DEBUG_INPT   yLOG_note    ("confirmed as exists");
   }
   /*---(pre-handle)---------------------*/
   switch (a_type) {
   case  'f' :
      sprintf (x_cmd, NEW_CFLOW , x_use);
      break;
   case  'm' :
      sprintf (x_cmd, DEL_ANY   , x_use);
      break;
   case  't' :
      sprintf (x_cmd, NEW_CTAGS , x_source, x_use);
      break;
   case  'v' :
      sprintf (x_cmd, NEW_VARS  , x_source, x_use);
      break;
   }
   if (strcmp (x_cmd , "") != 0) {
      DEBUG_INPT   yLOG_info    ("x_cmd"     , x_cmd);
      rci = system (x_cmd);
      DEBUG_INPT   yLOG_value   ("system"    , rci);
      --rce;  if (rci < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return  rce;
      }
   }
   /*---(open flow)----------------------*/
   *x_file = fopen (x_use, x_mode);
   DEBUG_INPT   yLOG_point   ("*x_file"         , *x_file);
   --rce;  if (*x_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save name)----------------------*/
   switch (a_type) {
   case 't' :  /* ctags */
      strlcpy (s_ctags, a_focus , LEN_RECD);
      break;
   case 'c' :  /* c source files */
      strlcpy (s_code , a_focus , LEN_RECD);
      break;
   case 'v' :  /* varables */
      strlcpy (s_vars , a_focus , LEN_RECD);
      break;
   }
   DEBUG_INPT   yLOG_point   ("x_file"          , x_file);
   DEBUG_INPT   yLOG_point   ("*x_file"         , *x_file);
   /*---(note)---------------------------*/
   DEBUG_INPT   yLOG_note    ("openned successfully");
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_shared_close       (char a_type)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   char        rc          =   0;
   int         rci         =   0;
   char        x_cmd       [LEN_RECD]  = "";
   char        x_used      [LEN_RECD]  = "";
   FILE      **x_file      = NULL;
   tSTAT       st;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_char    ("a_type"    , a_type);
   --rce;  if (a_type == 0 || strchr (s_valid, a_type) == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_shared__pointer (a_type, &x_file);
   DEBUG_INPT   yLOG_value   ("file"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("*x_file"   , *x_file);
   /*---(assign name)--------------------*/
   --rce;  switch (a_type) {
   case 'f' :  /* cflow */
      strlcpy (x_used , F_CFLOW , LEN_RECD);
      break;
   case 't' :  /* ctags */
      strlcpy (x_used , s_ctags , LEN_RECD);
      break;
   case 'm' :  /* mystery calls */
      strlcpy (x_used , F_MYSTRY, LEN_RECD);
      break;
   case 'c' :  /* c source files */
      strlcpy (x_used , s_code  , LEN_RECD);
      break;
   case 'v' :  /* global/file variables */
      strlcpy (x_used , F_VARS  , LEN_RECD);
      break;
   case 'e' :  /* external */
      strlcpy (x_used  , my.n_extern, LEN_RECD);
      break;
   default  :
      DEBUG_INPT   yLOG_note    ("type unknown");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("name"       , x_used);
   DEBUG_INPT   yLOG_point   ("*x_file"   , *x_file);
   --rce;  if (*x_file == NULL) {
      DEBUG_INPT   yLOG_note    ("not already open");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close file)---------------------*/
   rc = fclose (*x_file);
   DEBUG_INPT   yLOG_point   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(post-handling)------------------*/
   switch (a_type) {
   case  'f' :
      sprintf (x_cmd  , DEL_ANY   , F_CFLOW);
      break;
   case  't' :
      sprintf (x_cmd  , DEL_ANY   , F_CTAGS);
      strlcpy (x_used , F_CTAGS   , LEN_RECD);
      break;
   case  'v' :
      sprintf (x_cmd  , DEL_ANY   , F_VARS);
      strlcpy (x_used , F_VARS    , LEN_RECD);
      break;
   }
   if (strcmp (x_cmd , "") != 0) {
      DEBUG_INPT   yLOG_info    ("x_cmd"     , x_cmd);
      rci = system (x_cmd);
      DEBUG_INPT   yLOG_value   ("system"    , rci);
      --rce;  if (rci < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return  rce;
      }
   }
   /*---(post-check)---------------------*/
   if (strchr ("ft", a_type) != NULL) {
      rci = lstat (x_used, &st);
      DEBUG_INPT   yLOG_value   ("lstat"     , rci);
      --rce; if (rci >= 0) {
         DEBUG_INPT   yLOG_note    ("file still exists");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      DEBUG_INPT   yLOG_note    ("confirmed as deleted");
   }
   /*---(ground and clear names)---------*/
   *x_file = NULL;
   switch (a_type) {
   case 't' :  /* ctags */
      strlcpy (s_ctags, ""      , LEN_RECD);
      break;
   case 'c' :  /* c source files */
      strlcpy (s_code , ""      , LEN_RECD);
      break;
   case 'v' :  /* variables */
      strlcpy (s_vars , ""      , LEN_RECD);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        reading the file                      ----===*/
/*====================------------------------------------====================*/
static void  o___READING_________o () { return; }

char
poly_shared_read        (char a_type, int *a_line, char *a_curr, char *a_prev)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   FILE      **x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(get file)-----------------------*/
   rc = poly_shared__pointer (a_type, &x_file);
   DEBUG_INPT   yLOG_value   ("file"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("*x_file"   , *x_file);
   --rce;  if (*x_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_curr"    , a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(rotate)-------------------------*/
   if (a_prev != NULL) {
      strlcpy (a_prev, a_curr, LEN_RECD);
      DEBUG_INPT   yLOG_info    ("a_prev"    , a_prev);
   }
   /*---(read)------------------------*/
   fgets  (a_curr, LEN_RECD, *x_file);
   --rce;  if (feof (*x_file))  {
      DEBUG_INPT   yLOG_note    ("end of file");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update line)-----------------*/
   if (a_line != NULL) {
      ++(*a_line);
      DEBUG_INPT   yLOG_value   ("*a_line"   , *a_line);
   }
   /*---(prepare)---------------------*/
   x_len = strlen (a_curr);
   if (x_len > 0)  a_curr [--x_len] = '\0';
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   DEBUG_INPT   yLOG_info    ("a_curr"    , a_curr);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_shared_parse_tags  (char *a_curr, char *a_name, char *a_type, int *a_line, char *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           = " ";
   char       *s           = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_curr"    , a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_name, "", LEN_TITLE);
   DEBUG_INPT   yLOG_point   ("a_type"    , a_type);
   --rce;  if (a_type == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_type = '-';
   DEBUG_INPT   yLOG_point   ("a_line"    , a_line);
   if (a_line != NULL)   *a_line = -1;
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   if (a_file != NULL)   strlcpy (a_file, "", LEN_TITLE);
   /*---(prepare)---------------------*/
   strlcpy (x_recd, a_curr, LEN_RECD);
   /*---(get function)-------------------*/
   p = strtok_r (x_recd, q, &s);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_note    ("can not find name field, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_name, p, LEN_TITLE);
   DEBUG_INPT   yLOG_info    ("a_name"    , a_name);
   /*---(get type)-----------------------*/
   p = strtok_r (NULL  , q, &s);
   --rce;  if (p == NULL) {
      strlcpy (a_name, "", LEN_TITLE);
      DEBUG_INPT   yLOG_note    ("can not find type field, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_type = p [0];
   /*---(line)---------------------------*/
   p = strtok_r (NULL  , q, &s);
   --rce;  if (p == NULL) {
      strlcpy (a_name, "", LEN_TITLE);
      *a_type = '-';
      DEBUG_INPT   yLOG_note    ("can not find line field, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_line != NULL) {
      *a_line = atoi (p);
      DEBUG_INPT   yLOG_value   ("*a_line"   , *a_line);
      --rce;  if (*a_line <= 0) {
         strlcpy (a_name, "", LEN_TITLE);
         *a_type = '-';
         *a_line = -1;
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(get file)-----------------------*/
   p = strtok_r (NULL  , q, &s);
   --rce;  if (p == NULL) {
      strlcpy (a_name, "", LEN_TITLE);
      *a_type = '-';
      *a_line = -1;
      DEBUG_INPT   yLOG_note    ("can not find file field, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_file != NULL) {
      strlcpy (a_file, p, LEN_TITLE);
      DEBUG_INPT   yLOG_info    ("a_file"    , a_file);
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_shared_parse_flow  (char *a_curr, char *a_name, char *a_defn, int *a_line, char *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           = " :";
   char       *s           = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_curr"    , a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_name, "", LEN_TITLE);
   DEBUG_INPT   yLOG_point   ("a_defn"    , a_defn);
   --rce;  if (a_defn == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_defn = '-';
   DEBUG_INPT   yLOG_point   ("a_line"    , a_line);
   if (a_line != NULL)   *a_line = -1;
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   if (a_file != NULL)   strlcpy (a_file, "", LEN_TITLE);
   /*---(prepare)---------------------*/
   strlcpy (x_recd, a_curr, LEN_RECD);
   /*---(get function)-------------------*/
   p = strtok_r (x_recd, q, &s);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_note    ("can not find name field, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_name, p, LEN_TITLE);
   DEBUG_INPT   yLOG_info    ("a_name"    , a_name);
   /*---(get if definition)-----------*/
   p = strtok_r (NULL  , q, &s);
   DEBUG_INPT   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      strlcpy (a_name, "", LEN_TITLE);
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_char    ("def mark"  , p [0]);
   --rce;  if (p [0] == '*') {
      *a_defn = p [0];
      p = strtok_r (NULL  , q, &s);
      DEBUG_INPT   yLOG_point   ("p"         , p);
      if (p == NULL) {
         strlcpy (a_name, "", LEN_TITLE);
         *a_defn = '-';
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(get file)-----------------------*/
   if (a_file != NULL) {
      strlcpy (a_file, p, LEN_TITLE);
      DEBUG_INPT   yLOG_info    ("a_file"    , a_file);
   }
   /*---(line)---------------------------*/
   p = strtok_r (NULL  , q, &s);
   DEBUG_INPT   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      strlcpy (a_name, "", LEN_TITLE);
      *a_defn = '-';
      strlcpy (a_file, "", LEN_TITLE);
      DEBUG_INPT   yLOG_note    ("can not find line field, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_line != NULL) {
      *a_line = atoi (p);
      DEBUG_INPT   yLOG_value   ("*a_line"   , *a_line);
      if (*a_line <= 0) {
         strlcpy (a_name, "", LEN_TITLE);
         *a_defn = '-';
         strlcpy (a_file, "", LEN_TITLE);
         *a_line = -1;
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

int
poly_shared__unit_recd  (char *a_name, int n, char *a_recd)
{
   char        t           [LEN_RECD]  = "";
   FILE       *f           = NULL;
   int         c           =    0;
   int         x_len       =    0;
   strcpy (a_recd, "");
   if (strcmp (a_name, "") == 0)  return 0;
   f = fopen (a_name, "rt");
   if (f == NULL)  return 0;
   while (1) {
      fgets (t, LEN_RECD, f);
      if (feof (f))  break;
      if (c == n)  strlcpy (a_recd, t, LEN_RECD);
      ++c;
   }
   x_len = strlen (a_recd);
   if (x_len > 0 && a_recd [x_len - 1] == '\n')  a_recd [--x_len] = '\0';
   fclose (f);
   return c;
}

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_shared__unit       (char *a_question)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_TITLE] = " - - - - - - - - -";
   char        s           [LEN_TITLE] = " - - - - - - - - -";
   char        r           [LEN_TITLE] = " - - - - - - - - -";
   char        x_recd      [LEN_RECD]  = "";
   tFUNC      *u           = NULL;
   int         c           =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "SHARED unit      : question unknown");
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "code"      )     == 0) {
      c = poly_shared__unit_recd (s_code, 0, x_recd);
      sprintf (s, "%2d[%.14s]", strlen (s_code) , s_code);
      sprintf (r, "%2d[%.14s]", strlen (x_recd) , x_recd);
      snprintf (unit_answer, LEN_RECD, "SHARED code      : %c  %-10p  %-18.18s  %-18.18s  %2d  %s", (my.f_code   == NULL) ? '-' : 'y', my.f_code  , t, s, c, r);
      return unit_answer;
   }
   else if (strcmp (a_question, "ctags"     )     == 0) {
      c = poly_shared__unit_recd (F_CTAGS, 0, x_recd);
      sprintf (t, "%2d[%.14s]", strlen (F_CTAGS), F_CTAGS);
      sprintf (s, "%2d[%.14s]", strlen (s_ctags), s_ctags);
      sprintf (r, "%2d[%.14s]", strlen (x_recd) , x_recd);
      snprintf (unit_answer, LEN_RECD, "SHARED ctags     : %c  %-10p  %-18.18s  %-18.18s  %2d  %s", (my.f_ctags  == NULL) ? '-' : 'y', my.f_ctags , t, s, c, r);
      return unit_answer;
   }
   else if (strcmp (a_question, "cflow"     )     == 0) {
      c = poly_shared__unit_recd (F_CFLOW, 0, x_recd);
      sprintf (t, "%2d[%.14s]", strlen (F_CFLOW), F_CFLOW);
      sprintf (r, "%2d[%.14s]", strlen (x_recd) , x_recd);
      snprintf (unit_answer, LEN_RECD, "SHARED cflow     : %c  %-10p  %-18.18s  %-18.18s  %2d  %s", (my.f_cflow  == NULL) ? '-' : 'y', my.f_cflow , t, s, c, r);
      return unit_answer;
   }
   else if (strcmp (a_question, "mystry"    )     == 0) {
      c = poly_shared__unit_recd (F_MYSTRY, 0, x_recd);
      sprintf (t, "%2d[%.14s]", strlen (F_MYSTRY), F_MYSTRY);
      sprintf (r, "%2d[%.14s]", strlen (x_recd) , x_recd);
      snprintf (unit_answer, LEN_RECD, "SHARED mystry    : %c  %-10p  %-18.18s  %-18.18s  %2d  %s", (my.f_mystry == NULL) ? '-' : 'y', my.f_mystry, t, s, c, r);
      return unit_answer;
   }
   else if (strcmp (a_question, "vars"      )     == 0) {
      c = poly_shared__unit_recd (F_VARS, 0, x_recd);
      sprintf (t, "%2d[%.14s]", strlen (F_VARS), F_VARS);
      sprintf (r, "%2d[%.14s]", strlen (x_recd) , x_recd);
      snprintf (unit_answer, LEN_RECD, "SHARED vars      : %c  %-10p  %-18.18s  %-18.18s  %2d  %s", (my.f_vars   == NULL) ? '-' : 'y', my.f_vars  , t, s, c, r);
      return unit_answer;
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
