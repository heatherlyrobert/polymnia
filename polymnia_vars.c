/*============================----beg-of-source---============================*/
#include  "polymnia.h"


#define     MAX_VARS     1000
typedef     struct     cVARS      tVARS;
struct cVARS {
   char        scope;                       /* (g)lobal, (f)ile               */
   tFILE      *file;                        /* file pointer                   */
   int         line;                        /* line is source file            */
   char        len;                         /* variable name length           */
   char        name        [LEN_TITLE];     /* variable name                  */
   char        type;                        /* (v)var, (m)macro               */
};
static tVARS        s_vars        [MAX_VARS];
static int          s_nvar        = 0;
static int          s_nglobal     = 0;



static char *s_bad       = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";
static char *s_macro     = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";



static char  s_smacros   [LEN_RECD] = "";       /* all macros identified      */
static int   s_nmacros   = 0;                   /* count of all               */
static char  s_macros    [LEN_RECD] = "";       /* all macros identified      */
static int   s_nextern   = 0;                   /* count of all               */
static char  s_sextern   [LEN_RECD] = "";       /* list of unique             */
static char  s_extern    [LEN_RECD] = "";       /* list of unique             */
static int   s_nintern   = 0;                   /* count of all               */
static char  s_sintern   [LEN_RECD] = "";       /* list of unique             */
static char  s_intern    [LEN_RECD] = "";       /* list of unique             */

static char  s_vhide     [LEN_RECD] = "";
static int   s_vnhide    = 0;
static char  s_mhide     [LEN_RECD] = "";
static int   s_mnhide    = 0;


/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_vars__purge        (void)
{
   int         i           =    0;
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   for (i = 0; i < MAX_VARS; ++i) {
      s_vars [i].file     = NULL;
      s_vars [i].scope    = '-';
      s_vars [i].len      = 0;
      s_vars [i].name [0] = '\0';
      s_vars [i].type     = '-';
   }
   s_nvar    = 0;
   s_nglobal = 0;
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_vars_init          (void)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   poly_vars__purge ();
   ystrlcpy (s_macros, "", LEN_RECD);
   ystrlcpy (s_smacros, "", LEN_RECD);
   s_nmacros = 0;
   ystrlcpy (s_extern, "", LEN_RECD);
   ystrlcpy (s_sextern, "", LEN_RECD);
   s_nextern = 0;
   ystrlcpy (s_intern, "", LEN_RECD);
   ystrlcpy (s_sintern, "", LEN_RECD);
   s_nintern = 0;
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       data adding                            ----===*/
/*====================------------------------------------====================*/
static void  o___DATA____________o () { return; }

char
poly_vars__confirm      (tFILE *a_file, char *a_name)
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
      if (s_vars [i].scope == 'g')                return 1;
      if (s_vars [i].file  == a_file)             return 1;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_vars__push         (tFILE *a_file, int a_line, char *a_name, char a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char        x_type      =  '-';
   /*---(defense)------------------------*/
   --rce;  if (s_nvar >= MAX_VARS)  return rce;
   --rce;  if (a_file == NULL)      return rce;
   x_type = a_file->i_type;
   --rce;  if (x_type == 'h' && s_nvar > s_nglobal)  return rce;
   --rce;  if (a_name == NULL)      return rce;
   /*---(prepare)------------------------*/
   x_len  = strlen (a_name);
   --rce;  if (x_len  <= 0)         return rce;
   /*---(confirm)------------------------*/
   rc = poly_vars__confirm (a_file, a_name);
   --rce;  if (rc != 0)  return rce;
   /*---(add entry)----------------------*/
   if (x_type == 'h')   s_vars [s_nvar].scope = 'g';
   else                 s_vars [s_nvar].scope = 'f';
   s_vars [s_nvar].file = a_file;
   s_vars [s_nvar].line = a_line;
   s_vars [s_nvar].len  = x_len;
   ystrlcpy (s_vars [s_nvar].name, a_name, LEN_TITLE);
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
   char        rce         =  -10;
   int         rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        x_name      [LEN_TITLE] = "";
   char        x_type      =  '-';
   int         x_line      =    0;
   int         x_len       =    0;
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
   /*> rc = poly_vars__pop_file ();                                                   <* 
    *> DEBUG_INPT   yLOG_value   ("clear"     , rc);                                  <* 
    *> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return  rce;                                                                <* 
    *> }                                                                              <*/
   /*---(prepare)------------------------*/
   rc = poly_shared_open ('v', a_file->i_name);
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
      /*---(parse)-----------------------*/
      rc = poly_shared_parse_tags (x_recd, x_name, &x_type, &x_line, NULL);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0)  {
         DEBUG_INPT   yLOG_note    ("reading of line failed or eof");
         break;
      }
      /*---(filter)----------------------*/
      if (strncmp (x_name, "DEBUG_", 6) == 0) {
         DEBUG_INPT   yLOG_note    ("skip debug macros");
         continue;
      }
      if (strncmp (x_name, "P_"    , 2) == 0) {
         DEBUG_INPT   yLOG_note    ("skip oneliner macros");
         continue;
      }
      /*---(name)------------------------*/
      rc = poly_vars__push (a_file, x_line, x_name, x_type);
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
poly_vars__extern_tally (tFUNC *a_func, tEXTERN *a_ext)
{
   /*---(no matter what)-----------------*/
   ++(a_func->WORK_PUSE);
   /*---(assign category)----------------*/
   if (a_ext != NULL) {
      switch (a_ext->cat) {
      case 'C' :            ++(a_func->WORK_CUSE);         break;
      case 'Y' : case 'y' : ++(a_func->WORK_YUSE);         break;
      case 'V' :            ++(a_func->WORK_VUSE);         break;
      case 'X' :            ++(a_func->WORK_OUSE);         break;
      case 'N' :            ++(a_func->WORK_OUSE);         break;
      case 'O' :            ++(a_func->WORK_OUSE);         break;
      default  :            ++(a_func->WORK_OUSE);         break;
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
   char        s           [LEN_HUND]  = "";
   int         i           =    0;
   char       *b           = NULL;
   char       *e           = NULL;
   char        x_name      [LEN_TITLE] = "";
   int         n           =    0;
   tEXTERN    *x_ext       = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_func   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("work"      , a_func->c_work);
   --rce;  if (a_func->c_work  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_recd   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   ystrlcpy   (t, a_recd, LEN_RECD);
   ystrlunall (t, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("t"         , t);
   x_len = strlen (t);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   if (x_len <= 0) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(look for potential macros)------*/
   for (i = 0; i <= x_len; ++i) {
      DEBUG_INPT   yLOG_complex ("check"     , "%2d, %c, %p, %d", i, ychrvisible (t [i]), b, n);
      /*---(not a macro letter)----------*/
      if (t [i] == '\0' || strchr (s_macro, t [i]) == NULL) {
         DEBUG_INPT   yLOG_note    ("not a macro letter");
         /*---(finish existing)----------*/
         if (b != NULL && n > 0) {
            DEBUG_INPT   yLOG_note    ("was inside a macro");
            if (n > 6 && strncmp ("DEBUG_", b, 6) == 0) {
               DEBUG_INPT   yLOG_note    ("debugging macro/guard, skipping");
            } else if (n >= 3 && strncmp ("P_"  , b, 2) == 0) {
               DEBUG_INPT   yLOG_note    ("header oneliners, skipping");
            } else if (n == 4 && strncmp ("NULL", b, 4) == 0) {
               DEBUG_INPT   yLOG_note    ("common NULL, skipping");
            } else if (t [i] == '\0' || strchr (s_bad, t [i]) == NULL) {
               DEBUG_INPT   yLOG_note    ("good finish, increment");
               ystrlcpy (x_name, b, n + 1);
               DEBUG_INPT   yLOG_info    ("macro name", x_name);
               /*---(find external)------------------*/
               poly_extern_by_name (x_name, &x_ext);
               DEBUG_INPT   yLOG_point   ("x_ext"     , x_ext);
               /*---(save for mask testing)----------*/
               sprintf (s, " %s ", x_name);
               if (strstr (s_macros, s) == NULL) {
                  ystrlcat (s_macros, s, LEN_RECD);
                  ++s_nmacros;
               }
               if (x_ext != NULL) {
                  if (strstr (s_extern, s) == NULL) {
                     ystrlcat (s_extern, s, LEN_RECD);
                     ++s_nextern;
                  }
               }
               switch (a_act) {
               case CODE_NORMAL :
                  poly_vars__extern_tally (a_func, x_ext);
                  break;
               case CODE_VAR_M :
                  sprintf (s, "<-- potenial internal or mystery");
                  if (x_ext != NULL) {
                     sprintf (s, "%-20.20s  %-20.20s  %4d  %c  %c  %c", x_ext->elib->name, x_ext->name, x_ext->line, x_ext->type, x_ext->cat, x_ext->sub);
                     ystrlcpy (s_sextern, s_extern, LEN_RECD);
                  }
                  printf ("%4d   - -  %-20.20s  %3d  %3d  %3d    %s\n", a_line, x_name, b - t, i, n, s);
                  break;
               case CODE_VAR_O :
                  ystrlcpy (s_sextern, s_extern, LEN_RECD);
                  ystrlcpy (s_smacros, s_macros, LEN_RECD);
                  break;
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
   /*---(locals)-----------+-----+-----+-*/
   char        s           [LEN_HUND]  = "";
   /*---(scope testing)------------------*/
   DEBUG_INPT   yLOG_char    ("scope"     , s_vars [n].scope);
   if (s_vars [n].scope == 'g') {
      if (s_vars [n].type == 'v')  ++(a_func->WORK_GVARS);
      else                         ++(a_func->WORK_GUSE);
   } else {
      if (s_vars [n].type == 'v')  ++(a_func->WORK_FVARS);
      else                         ++(a_func->WORK_FUSE);
   }
   /*---(mask testing)-------------------*/
   /*> sprintf (s, " %s ", s_vars [n].name);                                          <* 
    *> if (strstr (s_extern, s) != NULL)  ++a_func->WORK_MMASK;                       <*/
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
   char        s           [LEN_HUND]  = "";
   int         i           =    0;
   char       *b           = NULL;
   char       *e           = NULL;
   char        x_name      [LEN_TITLE] = "";
   int         n           =    0;
   char       *x_end       = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_func   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("work"      , a_func->c_work);
   --rce;  if (a_func->c_work  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_recd   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   ystrlcpy   (t, a_recd, LEN_RECD);
   ystrlunall (t, LEN_RECD);
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
      if (s_vars [i].scope == 'f' && s_vars [i].file != a_func->c_file)  continue;
      DEBUG_INPT   yLOG_info    ("search"    , s_vars [i].name);
      b = strstr (t, s_vars [i].name);
      DEBUG_INPT   yLOG_point   ("b"         , b);
      while (b != NULL && b < x_end) {
         e = b + s_vars [i].len;
         if (b != t)  DEBUG_INPT   yLOG_char    ("b [-1]"    , b [-1]);
         if (b == t || strchr (s_bad, b [-1]) == NULL) {
            if (e != x_end)   DEBUG_INPT   yLOG_char    ("e [0]"     , e [0]);
            if (e == x_end || strchr (s_bad, e [0]) == NULL) {
               sprintf (s, " %s ", s_vars [i].name);
               if (strstr (s_intern, s) == NULL) {
                  ystrlcat (s_intern, s, LEN_RECD);
                  ++s_nintern;
               }
               switch (a_act) {
               case CODE_NORMAL :
                  poly_vars__intern_tally (a_func, i);
                  break;
               case CODE_VAR_V :
                  printf ("%4d  %4d  %-20.20s  %3d  %3d  %3d    %-20.20s  %-20.20s  %4d  %c  %c", a_line, i, s_vars [i].name, b - t, e - t, s_vars [i].len, (s_vars [i].file)->i_name, s_vars [i].name, s_vars [i].line, s_vars [i].scope, s_vars [i].type);
                  if (strstr (s_extern, s) != NULL)  printf ("  potenally masking external\n");
                  else                               printf ("\n");
                  ystrlcpy (s_sintern, s_intern, LEN_RECD);
                  break;
               case CODE_VAR_O :
                  ystrlcpy (s_sintern, s_intern, LEN_RECD);
                  /*> sprintf (s, " %s ", s_vars [i].name);                                                                                              <* 
                   *> printf ("current %s\n", s);                                                                                                        <* 
                   *> printf ("extern  (%-10p) %s\n", strstr (s_extern, s), s_extern);                                                                   <* 
                   *> printf ("intern  (%-10p) %s\n", strstr (s_intern, s), s_intern);                                                                   <* 
                   *> if (strstr (s_extern, s) == NULL && strstr (s_intern, s) == NULL) {                                                                <* 
                   *>    printf ("%4d  %-20.20s  %3d  %3d  %3d    %s   orphan (not internal or external)\n", a_line, s_vars [i].name, b - t, i, n, s);   <* 
                   *> }                                                                                                                                  <*/
                  break;
               }
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
poly_vars_header        (char a_act)
{
   printf ("\n");
   switch (a_act) {
   case CODE_VAR_M :
      printf ("\n");
      printf ("POTENIAL MARCROS (TESTED AGAINST EXTERNALS)\n");
      printf ("line  indx  ---name-------------  beg  end  len    ---library----------  ---found------------  line  t  c  s\n");
      break;
   case CODE_VAR_V :
      printf ("\n");
      printf ("GLOBAL/FILE VARIABLES IDENTIFIED\n");
      printf ("line  indx  ---name-------------  beg  end  len    ---file-------------  ---found------------  line  s  t\n");
      break;
   }
   return 0;
}

char
poly_vars__hiding       (tFUNC *a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_RECD]  = "";
   char        u           [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *r           = NULL;
   tEXTERN    *x_ext       = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_func == NULL)  return rce;
   /*---(prepare)------------------------*/
   ystrlcpy (s_vhide, "", LEN_RECD);
   s_vnhide = 0;
   /*---(variable hiding)----------------*/
   ystrlcpy (t, a_func->WORK_LOCALS, LEN_RECD);
   p = strtok_r (t, " ", &r);
   while (p != NULL) {
      sprintf (u, " %s ", p);
      if (strstr (s_extern, u) != NULL) {
         ++a_func->WORK_VMASK;
         ystrlcat (s_vhide, u, LEN_RECD);
         ++s_vnhide;
      } else if (strstr (s_intern, u) != NULL) {
         ++a_func->WORK_VMASK;
         ystrlcat (s_vhide, u, LEN_RECD);
         ++s_vnhide;
      }
      p = strtok_r (NULL, " ", &r);
   }
   /*---(prepare)------------------------*/
   ystrlcpy (s_mhide, "", LEN_RECD);
   s_mnhide = 0;
   /*---(macro hiding)-------------------*/
   ystrlcpy (t, s_macros, LEN_RECD);
   p = strtok_r (t, " ", &r);
   while (p != NULL) {
      sprintf (u, " %s ", p);
      if (strstr (s_extern, u) != NULL) {
         if (strstr (s_intern, u) != NULL) {
            ++a_func->WORK_MMASK;
            ystrlcat (s_mhide, u, LEN_RECD);
            ++s_mnhide;
         }
      }
      p = strtok_r (NULL, " ", &r);
   }
   /*---(function hiding)----------------*/
   poly_extern_by_name (a_func->c_name, &x_ext);
   if (x_ext != NULL) {
      ++a_func->WORK_FMASK;
   } else if (poly_vars__confirm (a_func->c_file, a_func->c_name) == 1) {
      ++a_func->WORK_FMASK;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_vars_list      (void)
{
   int         i           =    0;
   if (my.g_mode == POLY_RPTG_VARS) {
      for (i = 0; i < s_nvar; ++i) {
         if (i % 25 == 0)  printf ("\nline  ---name-------------  line  ---file-------------  s  t\n");
         if (i %  5 == 0)  printf ("\n");
         printf ("%4d  %-20.20s  %4d  %-20.20s  %c  %c\n", i, s_vars [i].file->i_name, s_vars [i].line, s_vars [i].name, s_vars [i].scope, s_vars [i].type);
      }
      --i;
      if (i % 25 != 0)  printf ("\nline  ---name-------------  line  ---file-------------  s  t\n");
      printf ("\n");
   }
}

char
poly_vars_summary       (tFUNC *a_func, char a_act)
{
   int         c           =    0;
   int         d           =    0;
   char        t           [LEN_RECD]  = "";
   char        u           [LEN_RECD]  = "";
   char        v           [LEN_RECD]  = "";
   char        w           [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *r           = NULL;
   int         i           =    0;
   /*---(output)-------------------------*/
   switch (a_act) {
   case CODE_NORMAL :
      poly_vars__hiding (a_func);
      break;
   case CODE_VAR_M  :
      printf ("line  indx  ---name-------------  beg  end  len    ---library----------  ---found------------  line  t  c  s\n");
      printf ("\n");
      printf ("all macros  %3d[%s]\n" , strlen (s_macros), s_macros);
      printf ("... count   %3d\n", s_nmacros);
      printf ("\n");
      printf ("externals   %3d[%s]\n" , strlen (s_extern), s_extern);
      printf ("... count   %3d\n", s_nextern);
      break;
   case CODE_VAR_V  :
      printf ("line  indx  ---name-------------  beg  end  len    ---file-------------  ---found------------  line  s  t\n");
      printf ("\n");
      printf ("internals   %s\n" , s_sintern);
      printf ("... count    %d\n", s_nintern);
      printf ("\n");
      printf ("LOCALS      %s\n" , a_func->WORK_LOCALS);
      printf ("... vmask   %d\n" , a_func->WORK_VMASK);
      printf ("... mmask   %d\n" , a_func->WORK_MMASK);
      printf ("... fmask   %d\n" , a_func->WORK_FMASK);
      break;
   case CODE_VAR_O   :
      /*> printf ("count        %d\n" , c);                                           <*/
      /*> printf ("orphans     %s\n" , v);                                            <*/
      /*> ystrlcpy (t, s_sintern, LEN_RECD);                                           <* 
       *> p = strtok_r (t, " ", &r);                                                  <* 
       *> while (p != NULL) {                                                         <* 
       *>    if (strstr (s_sextern, p) != NULL) {                                     <* 
       *>       ++d;                                                                  <* 
       *>       sprintf (u, " %s ", p);                                               <* 
       *>       ystrlcat (w, u, LEN_RECD);                                             <* 
       *>    }                                                                        <* 
       *>    p = strtok_r (NULL, " ", &r);                                            <* 
       *> }                                                                           <*/
      /*> printf ("\n");                                                              <*/
      /*> printf ("count        %d\n" , d);                                           <*/
      /*> printf ("hiding      %s\n" , w);                                            <*/
      break;
   }
   return 0;
}

char
poly_vars_find          (tFUNC *a_func, int a_line, char *a_recd, char a_act)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
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
   DEBUG_INPT   yLOG_point   ("work"      , a_func->c_work);
   --rce;  if (a_func->c_work  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_recd   == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   ystrlcpy   (t, a_recd, LEN_RECD);
   ystrlunall (t, LEN_RECD);
   x_len = strlen (t);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("t"         , t);
   /*---(external macros)----------------*/
   rc = poly_vars__extern_find (a_func, a_line, a_recd, a_act);
   /*---(internal variables/macros)------*/
   rc = poly_vars__intern_find (a_func, a_line, a_recd, a_act);
   /*---(summarize)----------------------*/
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
   a_func->WORK_FVARS = 0;
   a_func->WORK_GVARS = 0;
   a_func->WORK_PUSE  = 0;
   a_func->WORK_FUSE  = 0;
   a_func->WORK_GUSE  = 0;
   a_func->WORK_MUSE  = 0;
   a_func->WORK_YUSE  = 0;
   a_func->WORK_OUSE  = 0;
   ystrlcpy (s_macros, "", LEN_RECD);
   s_nmacros          = 0;
   ystrlcpy (s_extern, "", LEN_RECD);
   s_nextern          = 0;
   ystrlcpy (s_intern, "", LEN_RECD);
   s_nintern          = 0;
   ystrlcpy (s_mhide , "", LEN_RECD);
   s_mnhide           = 0;
   ystrlcpy (s_vhide , "", LEN_RECD);
   s_vnhide           = 0;
   a_func->WORK_VMASK   = 0;
   a_func->WORK_MMASK   = 0;
   a_func->WORK_FMASK   = 0;
   a_func->WORK_LSTATIC = 0;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char
poly_vars__unit_set     (tFUNC *a_func, char *a_extern, char *a_intern, char *a_macros, char *a_locals)
{
   poly_vars_reset (a_func);
   ystrlcpy (s_extern, a_extern, LEN_RECD);
   ystrlcpy (s_intern, a_intern, LEN_RECD);
   ystrlcpy (s_macros, a_macros, LEN_RECD);
   ystrlcpy (a_func->WORK_LOCALS, a_locals, LEN_RECD);
   return 0;
}

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
   }
   else if (strcmp (a_question, "macros"    )     == 0) {
      snprintf (unit_answer, LEN_RECD, "VARS macros      : %2dn %3d[%-.60s]", s_nmacros, strlen (s_macros), s_macros);
   }
   else if (strcmp (a_question, "intern"    )     == 0) {
      snprintf (unit_answer, LEN_RECD, "VARS intern      : %2dn %3d[%-.60s]", s_nintern, strlen (s_intern), s_intern);
   }
   else if (strcmp (a_question, "extern"    )     == 0) {
      snprintf (unit_answer, LEN_RECD, "VARS extern      : %2dn %3d[%-.60s]", s_nextern, strlen (s_extern), s_extern);
   }
   else if (strcmp (a_question, "mhide"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "VARS mhide       : %2dn  -- %3d[%-.60s]", s_mnhide,  strlen (s_mhide), s_mhide);
   }
   else if (strcmp (a_question, "vhide"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "VARS vhide       : %2dn  -- %3d[%-.60s]", s_vnhide,  strlen (s_vhide), s_vhide);
   }
   else if (strcmp (a_question, "hide"      )     == 0) {
      poly_func_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->c_name);
         sprintf  (s, "%3dv %3dm %3df %3ds  [%-.35s]",
               u->WORK_VMASK, u->WORK_MMASK,
               u->WORK_FMASK, u->WORK_LSTATIC,
               u->WORK_LOCALS);
         snprintf (unit_answer, LEN_RECD, "VARS hide   (%2d) : %-22.22s  %s", i, t, s);
      }  else
         snprintf (unit_answer, LEN_RECD, "VARS hide   (%2d) : []                       0v   0m   0f   0s", i);
   }
   else if (strcmp (a_question, "entry"     )     == 0) {
      if (s_vars [i].file != NULL)  sprintf (t, "[%0.15s]", s_vars [i].file->i_name);
      sprintf (s, "[%0.15s]", s_vars [i].name);
      snprintf (unit_answer, LEN_RECD, "VARS entry  (%2d) : %-17.17s   %c %c   %2d%s", i, t, s_vars [i].scope, s_vars [i].type, strlen (s_vars [i].name), s);
   }
   else if (strcmp (a_question, "func"      )     == 0) {
      poly_func_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->c_name);
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





