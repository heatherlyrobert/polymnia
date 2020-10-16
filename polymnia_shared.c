/*============================----beg-of-source---============================*/
#include  "polymnia.h"



#define     NEW_CFLOW     "cflow  -x $(ls -1 *.c 2> /dev/null | grep -v unit) > %s  2> /dev/null"
#define     DEL_ANY       "rm -f %s  2> /dev/null"
#define     NEW_CTAGS     "ctags  --language-force=c -x --sort=no --file-scope=yes  --c-kinds=pfl %s > %s  2> /dev/null"

static      char       *s_valid       = "ftmcx";
static      char        s_ctags       [LEN_TITLE] = "";
static      char        s_code        [LEN_TITLE] = "";


char
poly_shared_open        (char a_type, char *a_focus)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
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
   /*---(assign name)--------------------*/
   --rce;  switch (a_type) {
   case 'f' :  /* cflow */
      strlcpy (x_use   , F_CFLOW , LEN_TITLE);
      strlcpy (x_mode  , "rt"    , LEN_TERSE);
      x_file  = &(my.f_cflow);
      break;
   case 't' :  /* ctags */
      strlcpy (x_source, a_focus , LEN_TITLE);
      strlcpy (x_use   , F_CTAGS , LEN_TITLE);
      strlcpy (x_mode  , "rt"    , LEN_TERSE);
      x_file  = &(my.f_ctags);
      break;
   case 'm' :  /* mystery calls */
      strlcpy (x_use   , F_MYSTRY, LEN_TITLE);
      strlcpy (x_mode  , "wt"    , LEN_TERSE);
      x_file  = &(my.f_mystry);
      break;
   case 'c' :  /* c source files */
      strlcpy (x_source, a_focus , LEN_TITLE);
      strlcpy (x_use   , a_focus , LEN_TITLE);
      strlcpy (x_mode  , "rt"    , LEN_TERSE);
      x_file  = &(my.f_code);
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
      strlcpy (s_ctags, a_focus , LEN_TITLE);
      break;
   case 'c' :  /* c source files */
      strlcpy (s_code , a_focus , LEN_TITLE);
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
   char        x_used      [LEN_TITLE] = "";
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
   /*---(assign name)--------------------*/
   --rce;  switch (a_type) {
   case 'f' :  /* cflow */
      strlcpy (x_used , F_CFLOW , LEN_TITLE);
      x_file  = &my.f_cflow;
      break;
   case 't' :  /* ctags */
      strlcpy (x_used , s_ctags , LEN_TITLE);
      x_file  = &my.f_ctags;
      break;
   case 'm' :  /* mystery calls */
      strlcpy (x_used , F_MYSTRY, LEN_RECD);
      x_file  = &my.f_mystry;
      break;
   case 'c' :  /* c source files */
      strlcpy (x_used , s_code  , LEN_TITLE);
      x_file  = &my.f_code;
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
      strlcpy (x_used , F_CTAGS   , LEN_TITLE);
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
   /*---(ground pointer)-----------------*/
   *x_file = NULL;
   switch (a_type) {
   case 't' :  /* ctags */
      strlcpy (s_ctags, ""      , LEN_TITLE);
      break;
   case 'c' :  /* c source files */
      strlcpy (s_code , ""      , LEN_TITLE);
      break;
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
      snprintf (unit_answer, LEN_RECD, "SHARED code      : %c  %-10p  %-18.18s  %-18.18s  %2d  %s", (my.f_code  == NULL) ? '-' : 'y', my.f_code , t, s, c, r);
      return unit_answer;
   }
   else if (strcmp (a_question, "ctags"     )     == 0) {
      c = poly_shared__unit_recd (F_CTAGS, 0, x_recd);
      sprintf (t, "%2d[%.14s]", strlen (F_CTAGS), F_CTAGS);
      sprintf (s, "%2d[%.14s]", strlen (s_ctags), s_ctags);
      sprintf (r, "%2d[%.14s]", strlen (x_recd) , x_recd);
      snprintf (unit_answer, LEN_RECD, "SHARED ctags     : %c  %-10p  %-18.18s  %-18.18s  %2d  %s", (my.f_ctags == NULL) ? '-' : 'y', my.f_ctags, t, s, c, r);
      return unit_answer;
   }
   else if (strcmp (a_question, "cflow"     )     == 0) {
      c = poly_shared__unit_recd (F_CFLOW, 0, x_recd);
      sprintf (t, "%2d[%.14s]", strlen (F_CFLOW), F_CFLOW);
      sprintf (r, "%2d[%.14s]", strlen (x_recd) , x_recd);
      snprintf (unit_answer, LEN_RECD, "SHARED cflow     : %c  %-10p  %-18.18s  %-18.18s  %2d  %s", (my.f_cflow == NULL) ? '-' : 'y', my.f_cflow, t, s, c, r);
      return unit_answer;
   }
   else if (strcmp (a_question, "mystry"    )     == 0) {
      c = poly_shared__unit_recd (F_MYSTRY, 0, x_recd);
      sprintf (t, "%2d[%.14s]", strlen (F_MYSTRY), F_MYSTRY);
      sprintf (r, "%2d[%.14s]", strlen (x_recd) , x_recd);
      snprintf (unit_answer, LEN_RECD, "SHARED mystry    : %c  %-10p  %-18.18s  %-18.18s  %2d  %s", (my.f_mystry == NULL) ? '-' : 'y', my.f_mystry, t, s, c, r);
      return unit_answer;
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
