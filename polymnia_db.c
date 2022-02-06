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
      DEBUG_TOPS  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ARGS  yLOG_info    ("a_name"    , a_name);
   strlcpy (x_recd, a_name, LEN_RECD);
   /*---(check length)-------------------*/
   l = strlen (x_recd);
   DEBUG_ARGS  yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "database <name>, name can not be blank/empty");
      DEBUG_TOPS  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check characters)---------------*/
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (x_valid, x_recd [i]) != NULL)  continue;
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "database <name>, name can not have a <%c> at character %d", x_recd [i], i);
      DEBUG_TOPS  yLOG_char  ("bad char"  , x_recd [i]);
      DEBUG_TOPS  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check extension)----------------*/
   if (l >= 4 && strcmp (x_recd + l - 3, ".db") != 0) {
      strlcat (x_recd, ".db", LEN_RECD);
      DEBUG_ARGS  yLOG_info    ("fixed"     , x_recd);
   }
   /*---(copy)---------------------------*/
   strlcpy (my.n_db, x_recd, LEN_RECD);
   DEBUG_ARGS  yLOG_info    ("database"  , my.n_db);
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_db_init            (void)
{
   poly_db_cli (F_DB, '-');
   my.f_db = NULL;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      file control                            ----===*/
/*====================------------------------------------====================*/
static void  o___FILES___________o () { return; }

char
poly_db__open           (char a_mode, int *a_nproj, int *a_nfile, int *a_nfunc, int *a_nylib)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_mode      [LEN_TERSE] = "";
   int         n           =    0;
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
      strlcpy (x_mode, "rb", LEN_TERSE);
      break;
   case 'w' :
      strlcpy (x_mode, "wb", LEN_TERSE);
      break;
   default  :
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("x_mode"    , x_mode);
   /*---(open)---------------------------*/
   DEBUG_FILE   yLOG_info    ("my.n_db"   , my.n_db);
   my.f_db = fopen (my.n_db, x_mode);
   DEBUG_FILE   yLOG_point   ("my.f_db"   , my.f_db);
   --rce;  if (my.f_db == NULL) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(project count)------------------*/
   switch (a_mode) {
   case 'r' :
      fread  (&n, sizeof (int), 1, my.f_db);
      DEBUG_FILE   yLOG_value   ("projs"     , n);
      if (a_nproj != NULL)  *a_nproj = n;
      fread  (&n, sizeof (int), 1, my.f_db);
      DEBUG_FILE   yLOG_value   ("files"     , n);
      if (a_nfile != NULL)  *a_nfile = n;
      fread  (&n, sizeof (int), 1, my.f_db);
      DEBUG_FILE   yLOG_value   ("funcs"     , n);
      if (a_nfunc != NULL)  *a_nfunc = n;
      fread  (&n, sizeof (int), 1, my.f_db);
      DEBUG_FILE   yLOG_value   ("ylib"      , n);
      if (a_nylib != NULL)  *a_nylib = n;
      break;
   case 'w' :
      n = poly_btree_count (B_PROJ);
      DEBUG_FILE   yLOG_value   ("projs"     , n);
      fwrite (&n, sizeof (int), 1, my.f_db);
      n = poly_btree_count (B_FILES);
      DEBUG_FILE   yLOG_value   ("files"     , n);
      fwrite (&n, sizeof (int), 1, my.f_db);
      /*> n = poly_btree_count (B_FUNCS);                                             <*/
      n = poly_func_count ();
      DEBUG_FILE   yLOG_value   ("funcs"     , n);
      fwrite (&n, sizeof (int), 1, my.f_db);
      n = g_nylib;
      DEBUG_FILE   yLOG_value   ("ylib"      , n);
      fwrite (&n, sizeof (int), 1, my.f_db);
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
   x_ylib = a_func->y_head;
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
   x_func = x_file->head;
   DEBUG_OUTP   yLOG_point   ("x_func"    , x_func);
   /*---(walk projects)------------------*/
   while (x_func != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("tag"       , x_func->name);
      fwrite (x_func  , sizeof (tFUNC), 1, my.f_db);
      /*---(dive)------------------------*/
      rc = poly_db__write_ylib (x_func);
      if (rc < 0) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      /*---(next)------------------------*/
      x_func = x_func->next;
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
   DEBUG_OUTP   yLOG_value   ("count"     , x_proj->count);
   x_file = x_proj->head;
   DEBUG_OUTP   yLOG_point   ("x_file"    , x_file);
   /*---(walk projects)------------------*/
   while (rc >= 0 && x_file != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("file"      , x_file->name);
      fwrite (x_file  , sizeof (tFILE), 1, my.f_db);
      /*---(dive)------------------------*/
      rc = poly_db__write_func (x_file);
      if (rc < 0) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      /*---(next)------------------------*/
      x_file = x_file->next;
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
   /*---(open)---------------------------*/
   rc = poly_db__open ('w', NULL, NULL, NULL, NULL);
   DEBUG_OUTP   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   rc = poly_btree_by_cursor (B_PROJ, YDLST_HEAD, &x_proj);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   /*---(walk projects)------------------*/
   while (x_proj != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("project"   , x_proj->name);
      fwrite (x_proj  , sizeof (tPROJ), 1, my.f_db);
      /*---(dive)------------------------*/
      rc = poly_db__write_file (x_proj);
      if (rc < 0) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      /*---(next)------------------------*/
      rc = poly_btree_by_cursor (B_PROJ, YDLST_NEXT, &x_proj);
      DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   }
   /*---(close)--------------------------*/
   rc = poly_db__close ();
   DEBUG_OUTP   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
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
      rc = poly_func_force (&x_func);
      DEBUG_INPT   yLOG_point   ("x_func"   , x_func);
      --rce;  if (rc < 0 || x_func == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (x_func, sizeof (tFUNC), 1, my.f_db);
      DEBUG_INPT   yLOG_info    ("func"      , x_func->name);
      /*---(clear the pointers)-------------*/
      x_nylib         = x_func->y_count;
      x_func->file    = NULL;
      x_func->next    = x_func->prev    = NULL;
      x_func->y_head  = x_func->y_tail  = NULL;
      x_func->y_count = 0;
      x_func->COUNT_FILES = x_func->COUNT_FUNCS = x_func->COUNT_YLIBS = 0;
      x_func->work    = NULL;
      x_func->btree   = NULL;
      /*---(add to project)-----------------*/
      rc = poly_func_hook (a_file, x_func);
      DEBUG_INPT   yLOG_value   ("hook"      , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(into btree)---------------------*/
      rc = poly_btree_hook (B_FUNCS, x_func, x_func->name, &x_func->btree);
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
      poly_file_force (&x_file);
      DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
      --rce;  if (x_file == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (x_file, sizeof (tFILE), 1, my.f_db);
      DEBUG_INPT   yLOG_info    ("file"      , x_file->name);
      /*---(clear the pointers)-------------*/
      DEBUG_INPT   yLOG_note    ("overwrite with some defaults");
      x_nfunc       = x_file->count;
      x_file->proj  = NULL;
      x_file->head  = x_file->tail  = NULL;
      x_file->next  = x_file->prev  = NULL;
      x_file->count = x_file->COUNT_FILES = x_file->COUNT_FUNCS = x_file->COUNT_YLIBS = 0;
      x_file->btree = NULL;
      /*---(add to project)-----------------*/
      DEBUG_INPT   yLOG_note    ("prepare for hook");
      rc = poly_file_hook (a_proj, x_file);
      DEBUG_INPT   yLOG_value   ("hook"      , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(into btree)---------------------*/
      rc = poly_btree_hook (B_FILES, x_file, x_file->name, &x_file->btree);
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
   /*---(initialize)---------------------*/
   my.COUNT_PROJS = my.COUNT_FILES = my.COUNT_FUNCS = my.COUNT_YLIBS = 0;
   my.COUNT_LINES = my.COUNT_EMPTY = my.COUNT_DOCS  = my.COUNT_DEBUG = my.COUNT_CODE  = my.COUNT_SLOCL = 0;
   my.COUNT_TEXT  = my.COUNT_DATA  = my.COUNT_BSS   = 0;
   /*---(open)---------------------------*/
   rc = poly_db__open ('r', &n, NULL, NULL, NULL);
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("projects"  , n);
   /*---(walk projects)------------------*/
   for (i = 0; i < n; ++i) {
      /*---(allocate)-----------------------*/
      poly_proj_force (&x_proj);
      DEBUG_INPT   yLOG_point   ("x_proj"    , x_proj);
      --rce;  if (x_proj == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (x_proj, sizeof (tPROJ), 1, my.f_db);
      DEBUG_INPT   yLOG_info    ("project"   , x_proj->name);
      /*---(clear the pointers)-------------*/
      x_nfile = x_proj->count;
      x_proj->head  = x_proj->tail  = NULL;
      x_proj->count = x_proj->COUNT_FILES = x_proj->COUNT_FUNCS = x_proj->COUNT_YLIBS = 0;
      x_proj->btree = NULL;
      /*---(into btree)---------------------*/
      rc = poly_btree_hook (B_PROJ, x_proj, x_proj->name, &x_proj->btree);
      DEBUG_INPT   yLOG_value   ("btree"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(dive)---------------------------*/
      rc = poly_db__read_file (x_proj, x_nfile);
      DEBUG_INPT   yLOG_value   ("read_file" , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(update)-------------------------*/
      ++my.COUNT_PROJS;
      my.COUNT_FILES += x_proj->COUNT_FILES;
      my.COUNT_FUNCS += x_proj->COUNT_FUNCS;
      my.COUNT_YLIBS += x_proj->COUNT_YLIBS;
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
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare btree)------------------*/
   rc = poly_btree_prepare_all ();
   DEBUG_INPT   yLOG_value   ("prepare"    , rc);
   --rce;  if (n > 0 && rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
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
      rc = poly_shared_verify (my.n_db);
      if      (rc >  0)  x_exist = 'y';
      else if (rc <= 0)  x_exist = '-';
      snprintf (unit_answer, LEN_RECD, "DB file          : %c  %-10p  %c  %2d[%s]",
            (my.f_db     == NULL) ? '-' : 'y', my.f_db,
            x_exist, strlen (my.n_db), my.n_db);
   }
   else if (strcmp (a_question, "counts"    )     == 0) {
      snprintf (unit_answer, LEN_RECD, "DB counts        : %4dp, %4df, %4df, %4dy",
            poly_btree_count (B_PROJ), poly_btree_count (B_FILES),
            poly_func_count (), g_nylib);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


