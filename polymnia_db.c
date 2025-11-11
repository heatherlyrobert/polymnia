/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*====================------------------------------------====================*/
/*===----                       basic support                          ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_db_cli             (char *a_name, char a_loud)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char       *x_valid     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_/.";
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_ARGS  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "database <name>, name can not be null");
      DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ARGS  yLOG_info    ("a_name"    , a_name);
   ystrlcpy (x_recd, a_name, LEN_RECD);
   /*---(check length)-------------------*/
   l = strlen (x_recd);
   DEBUG_ARGS  yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "database <name>, name can not be blank/empty");
      DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check characters)---------------*/
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (x_valid, x_recd [i]) != NULL)  continue;
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "database <name>, name can not have a <%c> at character %d", x_recd [i], i);
      DEBUG_PROG  yLOG_char  ("bad char"  , x_recd [i]);
      DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check extension)----------------*/
   if (l >= 4 && strcmp (x_recd + l - 3, ".db") != 0) {
      ystrlcat (x_recd, ".db", LEN_RECD);
      DEBUG_ARGS  yLOG_info    ("fixed"     , x_recd);
   }
   /*---(copy)---------------------------*/
   ystrlcpy (my.n_db, x_recd, LEN_RECD);
   DEBUG_ARGS  yLOG_info    ("database"  , my.n_db);
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_db_init            (void)
{
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   poly_db_cli (F_DB, '-');
   my.f_db = NULL;
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      file control                            ----===*/
/*====================------------------------------------====================*/
static void  o___FILES___________o () { return; }

char
poly_db__read_head      (char *a_name, int *a_var)
{
   int         n           =    0;
   fread  (&n, sizeof (int), 1, my.f_db);
   DEBUG_FILE   yLOG_value   (a_name      , n);
   if (a_var != NULL)  *a_var = n;
   return 0;
}

char
poly_db__write_head     (char *a_name, int a_var)
{
   DEBUG_FILE   yLOG_value   (a_name      , a_var);
   fwrite (&a_var, sizeof (int), 1, my.f_db);
   return 0;
}

char
poly_db__open           (char a_mode, int *a_nproj, int *a_nfile, int *a_nfunc, int *a_nylib)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_mode      [LEN_TERSE] = "";
   int         n           =    0;
   char        t           [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_FILE   yLOG_point   ("my.f_db"   , my.f_db);
   --rce;  if (my.f_db != NULL) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set mode)-----------------------*/
   DEBUG_FILE   yLOG_char    ("a_mode"    , a_mode);
   --rce;  switch (a_mode) {
   case 'r' :
      ystrlcpy (x_mode, "rb", LEN_TERSE);
      break;
   case 'w' :
      ystrlcpy (x_mode, "wb", LEN_TERSE);
      break;
   default  :
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("x_mode"    , x_mode);
   /*---(open)---------------------------*/
   DEBUG_FILE   yLOG_info    ("my.n_db"   , my.n_db);
   yURG_msg ('-', "database is å%sæ", my.n_db);
   my.f_db = fopen (my.n_db, x_mode);
   DEBUG_FILE   yLOG_point   ("my.f_db"   , my.f_db);
   --rce;  if (my.f_db == NULL) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(project count)------------------*/
   switch (a_mode) {
   case 'r' :
      fread  (&(g_audit.name)  , LEN_LABEL, 1, my.f_db);
      DEBUG_FILE   yLOG_info    ("name"      , g_audit.name);
      fread  (&(g_audit.vernum), LEN_SHORT, 1, my.f_db);
      DEBUG_FILE   yLOG_info    ("vernum"    , g_audit.vernum);
      poly_db__read_head  ("projs", &(g_audit.COUNT_PROJS));
      if (a_nproj != NULL)  *a_nproj = g_audit.COUNT_PROJS;
      poly_db__read_head  ("files", &(g_audit.COUNT_FILES));
      if (a_nfile != NULL)  *a_nfile = g_audit.COUNT_FILES;
      poly_db__read_head  ("funcs", &(g_audit.COUNT_FUNCS));
      if (a_nfunc != NULL)  *a_nfunc = g_audit.COUNT_FUNCS;
      poly_db__read_head  ("ylibs", &(g_audit.COUNT_YLIBS));
      if (a_nylib != NULL)  *a_nylib = g_audit.COUNT_YLIBS;
      poly_db__read_head  ("lines", &(g_audit.COUNT_LINES));
      poly_db__read_head  ("empty", &(g_audit.COUNT_EMPTY));
      poly_db__read_head  ("docs" , &(g_audit.COUNT_DOCS));
      poly_db__read_head  ("debug", &(g_audit.COUNT_DEBUG));
      poly_db__read_head  ("code" , &(g_audit.COUNT_CODE));
      poly_db__read_head  ("slocl", &(g_audit.COUNT_SLOCL));
      break;
   case 'w' :
      for (n = 0; n < LEN_LABEL; n++)  t [n] = ' ';
      ystrlcpy (t, P_BASENAME, LEN_LABEL);
      fwrite (t, LEN_LABEL, 1, my.f_db);
      DEBUG_FILE   yLOG_info    ("name"      , t);
      for (n = 0; n < LEN_LABEL; n++)  t [n] = ' ';
      ystrlcpy (t, P_VERNUM  , LEN_SHORT);
      fwrite (t, LEN_SHORT, 1, my.f_db);
      DEBUG_FILE   yLOG_info    ("vernum"    , t);
      poly_db__write_head ("projs", my.COUNT_PROJS);
      poly_db__write_head ("files", my.COUNT_FILES);
      poly_db__write_head ("funcs", my.COUNT_FUNCS);
      poly_db__write_head ("ylibs", my.COUNT_YLIBS);
      poly_db__write_head ("lines", my.COUNT_LINES);
      poly_db__write_head ("empty", my.COUNT_EMPTY);
      poly_db__write_head ("docs" , my.COUNT_DOCS);
      poly_db__write_head ("debug", my.COUNT_DEBUG);
      poly_db__write_head ("code" , my.COUNT_CODE);
      poly_db__write_head ("slocl", my.COUNT_SLOCL);
      break;
   }
   DEBUG_FILE   yLOG_value   ("n"         , n);
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_db__close          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("my.f_db"   , my.f_db);
   --rce;  if (my.f_db == NULL)  return rce;
   /*---(close)--------------------------*/
   DEBUG_INPT   yLOG_info    ("my.n_db"   , my.n_db);
   rc = fclose (my.f_db);
   DEBUG_OUTP   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0)  return rce; 
   /*---(ground pointer)-----------------*/
   my.f_db = NULL;
   DEBUG_INPT   yLOG_point   ("my.f_db"   , my.f_db);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     writing full database                    ----===*/
/*====================------------------------------------====================*/
static void  o___WRITING_________o () { return; }

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db__write_ylib     (tFUNC *a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tYLIB      *x_ylib      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_ylib = a_func->c_yhead;
   DEBUG_OUTP   yLOG_point   ("x_ylib"     , x_ylib);
   /*---(walk projects)------------------*/
   while (x_ylib != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("func"      , x_ylib->name);
      fwrite (x_ylib  , sizeof (tYLIB), 1, my.f_db);
      /*---(next)------------------------*/
      x_ylib = x_ylib->f_next;
      DEBUG_OUTP   yLOG_point   ("x_ylib"     , x_ylib);
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db__write_func     (tFILE *x_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFUNC      *x_func      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_func = x_file->i_chead;
   DEBUG_OUTP   yLOG_point   ("x_func"    , x_func);
   /*---(walk projects)------------------*/
   while (x_func != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("tag"       , x_func->c_name);
      fwrite (x_func  , sizeof (tFUNC), 1, my.f_db);
      /*---(dive)------------------------*/
      rc = poly_db__write_ylib (x_func);
      if (rc < 0) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      /*---(next)------------------------*/
      x_func = x_func->c_next;
      DEBUG_OUTP   yLOG_point   ("x_func"    , x_func);
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db__write_file     (tPROJ *x_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_OUTP   yLOG_value   ("count"     , x_proj->j_icount);
   x_file = x_proj->j_ihead;
   DEBUG_OUTP   yLOG_point   ("x_file"    , x_file);
   /*---(walk projects)------------------*/
   while (rc >= 0 && x_file != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("file"      , x_file->i_name);
      fwrite (x_file  , sizeof (tFILE), 1, my.f_db);
      /*---(dive)------------------------*/
      rc = poly_db__write_func (x_file);
      if (rc < 0) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      /*---(next)------------------------*/
      x_file = x_file->i_next;
      DEBUG_OUTP   yLOG_point   ("x_file"    , x_file);
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db_write         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "write central database (write)...");
   /*---(open)---------------------------*/
   rc = poly_db__open ('w', NULL, NULL, NULL, NULL);
   DEBUG_OUTP   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "database could not be openned for writing");
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   rc = ySORT_by_cursor (B_PROJ, YDLST_HEAD, &x_proj, NULL);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   /*---(walk projects)------------------*/
   while (x_proj != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("project"   , x_proj->j_name);
      fwrite (x_proj  , sizeof (tPROJ), 1, my.f_db);
      /*---(dive)------------------------*/
      rc = poly_db__write_file (x_proj);
      if (rc < 0) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      /*---(next)------------------------*/
      rc = ySORT_by_cursor (B_PROJ, YDLST_NEXT, &x_proj, NULL);
      DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   }
   /*---(close)--------------------------*/
   rc = poly_db__close ();
   DEBUG_OUTP   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "database could not be closed after writing");
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(summary)------------------------*/
   yURG_msg ('-', "actual %4dp  %4df  %4df  %4dy     %4dl  %4de  %4dd  %4dd  %4dc  %4ds", my.COUNT_PROJS, my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_YLIBS, my.COUNT_LINES, my.COUNT_EMPTY, my.COUNT_DOCS , my.COUNT_DEBUG, my.COUNT_CODE , my.COUNT_SLOCL);
   yURG_msg ('-', "success, current database saved correctly");
   yURG_msg (' ', "");
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     reading full database                    ----===*/
/*====================------------------------------------====================*/
static void  o___READING_________o () { return; }

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db__read_ylib      (tFUNC *a_func, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   tYLIB      *x_new       = NULL;
   tEXTERN    *x_ext       = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(walk projects)------------------*/
   DEBUG_INPT   yLOG_value   ("n"         , n);
   for (i = 0; i < n; ++i) {
      /*---(allocate)-----------------------*/
      poly_ylib_force (&x_new);
      DEBUG_INPT   yLOG_point   ("x_ylib"    , x_new);
      --rce;  if (x_new == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (x_new, sizeof (tYLIB), 1, my.f_db);
      DEBUG_INPT   yLOG_info    ("ylib"      , x_new->name);
      /*---(clear the pointers)-------------*/
      x_new->func   = NULL;
      x_new->f_next = x_new->f_prev = NULL;
      x_new->ylib   = NULL;
      x_new->e_next = x_new->e_prev = NULL;
      /*---(into function list)-------------*/
      rc = poly_ylib__fhook (a_func, x_new);
      DEBUG_DATA   yLOG_value   ("fhook"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(find extern)--------------------*/
      poly_extern_by_name (x_new->name, &x_ext);
      DEBUG_INPT   yLOG_point   ("x_ext"     , x_ext);
      --rce;  if (x_ext == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(into extern list)---------------*/
      rc = poly_ylib__ehook (x_ext, x_new);
      DEBUG_DATA   yLOG_value   ("ehook"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(done)---------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db__read_func      (tFILE *a_file, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   tFUNC      *x_func      = NULL;
   int         x_nylib     =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(walk projects)------------------*/
   DEBUG_INPT   yLOG_value   ("n"         , n);
   for (i = 0; i < n; ++i) {
      /*---(allocate)-----------------------*/
      rc = FUNCS_force     (&x_func);
      DEBUG_INPT   yLOG_point   ("x_func"   , x_func);
      --rce;  if (rc < 0 || x_func == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (x_func, sizeof (tFUNC), 1, my.f_db);
      DEBUG_INPT   yLOG_info    ("func"      , x_func->c_name);
      /*---(clear the pointers)-------------*/
      x_nylib         = x_func->c_ycount;
      x_func->c_file    = NULL;
      x_func->c_next    = x_func->c_prev    = NULL;
      x_func->c_yhead  = x_func->c_ytail  = NULL;
      x_func->c_ycount = 0;
      x_func->COUNT_PROJS = x_func->COUNT_FILES = x_func->COUNT_FUNCS = x_func->COUNT_YLIBS = 0;
      x_func->c_work    = NULL;
      x_func->c_btree   = NULL;
      /*---(add to project)-----------------*/
      rc = FUNCS__hook    (a_file, x_func);
      DEBUG_INPT   yLOG_value   ("hook"      , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(into btree)---------------------*/
      rc = ySORT_hook (B_FUNCS, x_func, x_func->c_name, &x_func->c_btree);
      DEBUG_INPT   yLOG_value   ("btree"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(dive)---------------------------*/
      rc = poly_db__read_ylib (x_func, x_nylib);
      DEBUG_INPT   yLOG_value   ("ylibs"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db__read_file      (tPROJ *a_proj, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   tFILE      *x_file      = NULL;
   int         x_nfunc     =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_point   ("a_proj"    , a_proj);
   /*---(walk projects)------------------*/
   DEBUG_INPT   yLOG_value   ("files"     , n);
   for (i = 0; i < n; ++i) {
      /*---(allocate)-----------------------*/
      FILES_force     (&x_file);
      DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
      --rce;  if (x_file == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (x_file, sizeof (tFILE), 1, my.f_db);
      DEBUG_INPT   yLOG_info    ("file"      , x_file->i_name);
      /*---(clear the pointers)-------------*/
      DEBUG_INPT   yLOG_note    ("overwrite with some defaults");
      x_nfunc       = x_file->i_ccount;
      x_file->i_proj  = NULL;
      x_file->i_chead  = x_file->i_ctail  = NULL;
      x_file->i_next  = x_file->i_prev  = NULL;
      x_file->i_ccount = x_file->COUNT_PROJS = x_file->COUNT_FILES = x_file->COUNT_FUNCS = x_file->COUNT_YLIBS = 0;
      x_file->i_btree = NULL;
      /*---(add to project)-----------------*/
      DEBUG_INPT   yLOG_note    ("prepare for hook");
      rc = FILES__hook    (a_proj, x_file);
      DEBUG_INPT   yLOG_value   ("hook"      , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(into btree)---------------------*/
      rc = ySORT_hook (B_FILES, x_file, x_file->i_name, &x_file->i_btree);
      DEBUG_INPT   yLOG_value   ("btree"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(dive)---------------------------*/
      rc = poly_db__read_func (x_file, x_nfunc);
      DEBUG_INPT   yLOG_value   ("funcs"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_db__read_zero      (void)
{
   my.COUNT_PROJS = my.COUNT_FILES = my.COUNT_FUNCS = my.COUNT_YLIBS = 0;
   my.COUNT_LINES = my.COUNT_EMPTY = my.COUNT_DOCS  = my.COUNT_DEBUG = my.COUNT_CODE  = my.COUNT_SLOCL = 0;
   my.COUNT_TEXT  = my.COUNT_DATA  = my.COUNT_BSS   = 0;
   g_audit.COUNT_PROJS = g_audit.COUNT_FILES = g_audit.COUNT_FUNCS = g_audit.COUNT_YLIBS = 0;
   g_audit.COUNT_LINES = g_audit.COUNT_EMPTY = g_audit.COUNT_DOCS  = g_audit.COUNT_DEBUG = g_audit.COUNT_CODE  = g_audit.COUNT_SLOCL = 0;
   g_audit.COUNT_TEXT  = g_audit.COUNT_DATA  = g_audit.COUNT_BSS   = 0;
   return 0;
}

char
poly_db__stats          (void)
{
   DEBUG_FILE   yLOG_complex ("my"        , "%4dp  %4df  %4df  %4dy     %4dl  %4de  %4dd  %4dd  %4dc  %4ds", my.COUNT_PROJS, my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_YLIBS, my.COUNT_LINES, my.COUNT_EMPTY, my.COUNT_DOCS , my.COUNT_DEBUG, my.COUNT_CODE , my.COUNT_SLOCL);
   DEBUG_FILE   yLOG_complex ("g_audit"   , "%4dp  %4df  %4df  %4dy     %4dl  %4de  %4dd  %4dd  %4dc  %4ds", g_audit.COUNT_PROJS, g_audit.COUNT_FILES, g_audit.COUNT_FUNCS, g_audit.COUNT_YLIBS, g_audit.COUNT_LINES, g_audit.COUNT_EMPTY, g_audit.COUNT_DOCS , g_audit.COUNT_DEBUG, g_audit.COUNT_CODE , g_audit.COUNT_SLOCL);
   return 0;
}

char
poly_db__read_audit     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   --rce;  if (my.COUNT_PROJS != g_audit.COUNT_PROJS) {
      DEBUG_INPT   yLOG_note    ("project count does not match");
      yURG_msg ('F', "project count does not match");
      return rce;
   }
   --rce;  if (my.COUNT_FILES != g_audit.COUNT_FILES) {
      DEBUG_INPT   yLOG_note    ("file count does not match");
      yURG_msg ('F', "file count does not match");
      return rce;
   }
   --rce;  if (my.COUNT_FUNCS != g_audit.COUNT_FUNCS) {
      DEBUG_INPT   yLOG_note    ("function count does not match");
      yURG_msg ('F', "function count does not match");
      return rce;
   }
   --rce;  if (my.COUNT_YLIBS != g_audit.COUNT_YLIBS) {
      DEBUG_INPT   yLOG_note    ("ylib count does not match");
      yURG_msg ('F', "ylib count does not match");
      return rce;
   }
   --rce;  if (my.COUNT_LINES != g_audit.COUNT_LINES) {
      DEBUG_INPT   yLOG_note    ("source line count does not match");
      yURG_msg ('F', "source line count does not match");
      return rce;
   }
   --rce;  if (my.COUNT_EMPTY != g_audit.COUNT_EMPTY) {
      DEBUG_INPT   yLOG_note    ("empty line count does not match");
      yURG_msg ('F', "empty line count does not match");
      return rce;
   }
   --rce;  if (my.COUNT_DOCS  != g_audit.COUNT_DOCS ) {
      DEBUG_INPT   yLOG_note    ("documentation line count does not match");
      yURG_msg ('F', "documentation line count does not match");
      return rce;
   }
   --rce;  if (my.COUNT_DEBUG != g_audit.COUNT_DEBUG) {
      DEBUG_INPT   yLOG_note    ("debug line count does not match");
      yURG_msg ('F', "debug line count does not match");
      return rce;
   }
   --rce;  if (my.COUNT_CODE  != g_audit.COUNT_CODE ) {
      DEBUG_INPT   yLOG_note    ("code line count does not match");
      yURG_msg ('F', "code line count does not match");
      return rce;
   }
   --rce;  if (my.COUNT_SLOCL != g_audit.COUNT_SLOCL) {
      DEBUG_INPT   yLOG_note    ("slocl line count does not match");
      yURG_msg ('F', "slocl line count does not match");
      return rce;
   }
   yURG_msg ('-', "success, current database passed load audits");
   return 0;
}

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db_read          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   int         i           =    0;
   tPROJ      *x_proj      = NULL;
   int         x_nfile     =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   yURG_msg ('>', "read central database (read)...");
   /*---(initialize)---------------------*/
   PROJS_purge        ();
   poly_db__read_zero ();
   poly_db__stats     ();
   /*---(open)---------------------------*/
   rc = poly_db__open ('r', &n, NULL, NULL, NULL);
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "database could not be openned for reading");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("projects"  , n);
   poly_db__stats     ();
   /*---(walk projects)------------------*/
   for (i = 0; i < n; ++i) {
      /*---(allocate)-----------------------*/
      PROJS_force (&x_proj);
      DEBUG_INPT   yLOG_point   ("x_proj"    , x_proj);
      --rce;  if (x_proj == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (x_proj, sizeof (tPROJ), 1, my.f_db);
      DEBUG_INPT   yLOG_info    ("project"   , x_proj->j_name);
      /*---(clear the pointers)-------------*/
      x_nfile = x_proj->j_icount;
      x_proj->j_ihead  = x_proj->j_itail  = NULL;
      x_proj->j_icount = x_proj->COUNT_PROJS = x_proj->COUNT_FILES = x_proj->COUNT_FUNCS = x_proj->COUNT_YLIBS = 0;
      x_proj->j_btree = NULL;
      /*---(into btree)---------------------*/
      rc = ySORT_hook (B_PROJ, x_proj, x_proj->j_name, &x_proj->j_btree);
      DEBUG_INPT   yLOG_value   ("btree"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(update count)-------------------*/
      ++(my.COUNT_PROJS);
      /*---(dive)---------------------------*/
      rc = poly_db__read_file (x_proj, x_nfile);
      DEBUG_INPT   yLOG_value   ("read_file" , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(update)-------------------------*/
      my.COUNT_LINES += x_proj->COUNT_LINES;
      my.COUNT_EMPTY += x_proj->COUNT_EMPTY;
      my.COUNT_DOCS  += x_proj->COUNT_DOCS ;
      my.COUNT_DEBUG += x_proj->COUNT_DEBUG;
      my.COUNT_CODE  += x_proj->COUNT_CODE ;
      my.COUNT_SLOCL += x_proj->COUNT_SLOCL;
      my.COUNT_TEXT  += x_proj->COUNT_TEXT ;
      my.COUNT_DATA  += x_proj->COUNT_DATA ;
      my.COUNT_BSS   += x_proj->COUNT_BSS  ;
   }
   /*---(close)--------------------------*/
   rc = poly_db__close ();
   DEBUG_INPT   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      yURG_err ('f', "database could not be closed after reading");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare btree)------------------*/
   rc = poly_btree_prepare_all ();
   DEBUG_INPT   yLOG_value   ("prepare"    , rc);
   --rce;  if (n > 0 && rc < 0) {
      yURG_err ('f', "btree preparations were not successful");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(statistics)---------------------*/
   poly_db__stats     ();
   yURG_msg ('-', "audit  %4dp  %4df  %4df  %4dy     %4dl  %4de  %4dd  %4dd  %4dc  %4ds", g_audit.COUNT_PROJS, g_audit.COUNT_FILES, g_audit.COUNT_FUNCS, g_audit.COUNT_YLIBS, g_audit.COUNT_LINES, g_audit.COUNT_EMPTY, g_audit.COUNT_DOCS , g_audit.COUNT_DEBUG, g_audit.COUNT_CODE , g_audit.COUNT_SLOCL);
   yURG_msg ('-', "actual %4dp  %4df  %4df  %4dy     %4dl  %4de  %4dd  %4dd  %4dc  %4ds", my.COUNT_PROJS, my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_YLIBS, my.COUNT_LINES, my.COUNT_EMPTY, my.COUNT_DOCS , my.COUNT_DEBUG, my.COUNT_CODE , my.COUNT_SLOCL);
   poly_db__read_audit ();
   yURG_msg (' ', "");
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char
DATA__unit_format       (char a_proj [LEN_LABEL], char a_ftype, char a_file [LEN_TITLE], char a_func [LEN_TITLE], int a_projs, int a_files, int a_funcs, int a_ylibs, int a_lines, int a_empty, int a_docs, int a_debug, int a_code, int a_slocl, int a_count, int a_fore, int a_back, char a_head [LEN_TITLE], char a_tail [LEN_TITLE], int a_proto, int a_defn, int a_beg, int a_end)
{
   char        x_ftype     [LEN_SHORT] = "";

   strcpy   (unit_answer, "");
   sprintf (x_ftype, "%c", ychrvisible (a_ftype));

   ystrlcat (unit_answer, ystrlpadquick  (a_proj, '<', '.', 20), LEN_RECD);
   ystrlcat (unit_answer, "  ", LEN_RECD);
   ystrlcat (unit_answer, x_ftype, LEN_RECD);
   ystrlcat (unit_answer, "  ", LEN_RECD);
   ystrlcat (unit_answer, ystrlpadquick  (a_file, '<', '.', 30), LEN_RECD);
   ystrlcat (unit_answer, "  ", LEN_RECD);
   ystrlcat (unit_answer, ystrlpadquick  (a_func, '<', '.', 30), LEN_RECD);
   ystrlcat (unit_answer, "  ", LEN_RECD);

   ystrlcat (unit_answer, ystrl4quick ((double) a_projs, '>', ',', 0, '-', '.', '´', '-',  3), LEN_RECD);
   ystrlcat (unit_answer, " ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_files, '>', ',', 0, '-', '.', '´', '-',  5), LEN_RECD);
   ystrlcat (unit_answer, " ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_funcs, '>', ',', 0, '-', '.', '´', '-',  6), LEN_RECD);
   ystrlcat (unit_answer, " ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_ylibs, '>', ',', 0, '-', '.', '´', '-',  6), LEN_RECD);

   ystrlcat (unit_answer, " / ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_lines, '>', ',', 0, '-', '.', '´', '-',  7), LEN_RECD);
   ystrlcat (unit_answer, " ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_empty, '>', ',', 0, '-', '.', '´', '-',  7), LEN_RECD);
   ystrlcat (unit_answer, " ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_docs , '>', ',', 0, '-', '.', '´', '-',  7), LEN_RECD);
   ystrlcat (unit_answer, " ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_debug, '>', ',', 0, '-', '.', '´', '-',  7), LEN_RECD);
   ystrlcat (unit_answer, " ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_code , '>', ',', 0, '-', '.', '´', '-',  7), LEN_RECD);
   ystrlcat (unit_answer, " ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_slocl, '>', ',', 0, '-', '.', '´', '-',  7), LEN_RECD);

   ystrlcat (unit_answer, "  Ï  ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_count, '>', ',', 0, '-', '.', '´', '-',  3), LEN_RECD);
   ystrlcat (unit_answer, "c ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_fore , '>', ',', 0, '-', '.', '´', '-',  3), LEN_RECD);
   ystrlcat (unit_answer, "f ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_back , '>', ',', 0, '-', '.', '´', '-',  3), LEN_RECD);
   ystrlcat (unit_answer, "b  ", LEN_RECD);

   ystrlcat (unit_answer, "h=", LEN_RECD);
   ystrlcat (unit_answer, ystrlpadquick  (a_head, '<', '.', 30), LEN_RECD);
   ystrlcat (unit_answer, "  t=", LEN_RECD);
   ystrlcat (unit_answer, ystrlpadquick  (a_tail, '<', '.', 30), LEN_RECD);

   ystrlcat (unit_answer, "  Ï  ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_proto, '>', ',', 0, '-', '.', '´', '-',  4), LEN_RECD);
   ystrlcat (unit_answer, "p ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_defn , '>', ',', 0, '-', '.', '´', '-',  4), LEN_RECD);
   ystrlcat (unit_answer, "d ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_beg  , '>', ',', 0, '-', '.', '´', '-',  4), LEN_RECD);
   ystrlcat (unit_answer, "b ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick ((double) a_end  , '>', ',', 0, '-', '.', '´', '-',  4), LEN_RECD);
   ystrlcat (unit_answer, "e  Ï", LEN_RECD);

   return 0;
}

char*
DATA__unit_entry        (void)
{
   tPROJ      *u           = NULL;
   int         c           =    0;
   char        s           [LEN_DESC]  = "(null)";
   char        r           [LEN_DESC]  = "(null)";
   c = PROJS_count ();
   if (c > 0) {
      PROJS_by_cursor ('[', &u);
      ystrlcpy (s, u->j_name, LEN_TITLE);
      PROJS_by_cursor (']', &u);
      ystrlcpy (r, u->j_name, LEN_TITLE);
   }
   DATA__unit_format (
         /* master */  "TOTAL", '-', "´", "´", 
         /* counts */  my.COUNT_PROJS, my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_YLIBS, my.COUNT_LINES, my.COUNT_EMPTY, my.COUNT_DOCS , my.COUNT_DEBUG, my.COUNT_CODE , my.COUNT_SLOCL,
         /* projs  */  c, c, c, s, r,
         /* lines  */  -1, -1, -1, -1);
   return unit_answer;
}

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_db__unit           (char *a_question)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_exist     =  '-';
   int         n           =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "DB unit          : question unknown");
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "file"      )     == 0) {
      rc = poly_shared_verify ('-', my.n_db);
      if      (rc >  0)  x_exist = 'y';
      else if (rc <= 0)  x_exist = '-';
      snprintf (unit_answer, LEN_RECD, "DB file          : %c  %-10p  %c  %2d[%s]",
            (my.f_db     == NULL) ? '-' : 'y', my.f_db,
            x_exist, strlen (my.n_db), my.n_db);
   }
   else if (strcmp (a_question, "btrees"    )     == 0) {
      snprintf (unit_answer, LEN_RECD, "DB btrees        : %4dp  %4df  %4df",
            ySORT_count (B_PROJ) , ySORT_count (B_FILES),
            ySORT_count (B_FUNCS));
   }
   else if (strcmp (a_question, "counts"    )     == 0) {
      snprintf (unit_answer, LEN_RECD, "DB counts        : %4dp  %4df  %4df  %4dy     %4dl  %4de  %4dd  %4dd  %4dc  %4ds",
            my.COUNT_PROJS, my.COUNT_FILES, my.COUNT_FUNCS, my.COUNT_YLIBS, 
            my.COUNT_LINES, my.COUNT_EMPTY, my.COUNT_DOCS ,
            my.COUNT_DEBUG, my.COUNT_CODE , my.COUNT_SLOCL);
   }
   else if (strcmp (a_question, "audits"    )     == 0) {
      snprintf (unit_answer, LEN_RECD, "DB audits        : %4dp  %4df  %4df  %4dy     %4dl  %4de  %4dd  %4dd  %4dc  %4ds",
            g_audit.COUNT_PROJS, g_audit.COUNT_FILES, g_audit.COUNT_FUNCS, g_audit.COUNT_YLIBS, 
            g_audit.COUNT_LINES, g_audit.COUNT_EMPTY, g_audit.COUNT_DOCS ,
            g_audit.COUNT_DEBUG, g_audit.COUNT_CODE , g_audit.COUNT_SLOCL);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


