/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*====================------------------------------------====================*/
/*===----                     writing full database                    ----===*/
/*====================------------------------------------====================*/
static void  o___WRITING_________o () { return; }

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db_write_tag     (tFILE *x_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tTAG       *x_tag       = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_tag = poly_files_nexttag (x_file, &x_tag);
   /*---(walk projects)------------------*/
   while (x_tag != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("tag"       , x_tag->name);
      fwrite (x_tag  , sizeof (tTAG), 1, f_db);
      /*---(next)------------------------*/
      x_tag = poly_files_nexttag (x_file, &x_tag);
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db_write_file    (tPROJ *x_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_file = poly_proj_nextfile (x_proj, &x_file);
   /*---(walk projects)------------------*/
   while (x_file != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("file"      , x_file->name);
      fwrite (x_file  , sizeof (tFILE), 1, f_db);
      /*---(dive)------------------------*/
      rc = poly_db_write_tag  (x_file);
      if (rc < 0) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      /*---(next)------------------------*/
      x_file = poly_proj_nextfile (x_proj, &x_file);
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
   int         x_count     =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   DEBUG_OUTP   yLOG_info    ("db name"   , F_DB);
   f_db = fopen (F_DB, "wb");
   DEBUG_OUTP   yLOG_value   ("f_db"      , f_db);
   --rce;  if (f_db == NULL) {
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(write proj count)---------------*/
   x_count = poly_btree_count (B_PROJ);
   DEBUG_OUTP   yLOG_value   ("proj count", x_count);
   fwrite (&x_count, sizeof (int), 1, f_db);
   /*---(prepare)------------------------*/
   x_proj = (tPROJ *) poly_btree_first (B_PROJ);
   /*---(walk projects)------------------*/
   while (x_proj != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("project"   , x_proj->name);
      fwrite (x_proj  , sizeof (tPROJ), 1, f_db);
      /*---(dive)------------------------*/
      rc = poly_db_write_file (x_proj);
      if (rc < 0) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      /*---(next)------------------------*/
      x_proj = (tPROJ *) poly_btree_next  (B_PROJ);
   }
   /*---(close)--------------------------*/
   rc = fclose (f_db);
   DEBUG_OUTP   yLOG_value   ("f_db close", rc);
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
poly_db_read_tag      (tFILE *a_file, int a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_count     =    0;
   int         i           =    0;
   tTAG       *x_tag       = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(walk projects)------------------*/
   DEBUG_OUTP   yLOG_value   ("file count", a_count);
   for (i = 0; i < a_count; ++i) {
      /*---(allocate)-----------------------*/
      x_tag = poly_files_new ();
      DEBUG_OUTP   yLOG_point   ("x_tag"    , x_tag);
      --rce;  if (x_tag == NULL) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (&x_tag, sizeof (tTAG), 1, f_db);
      /*---(add to project)-----------------*/
      rc = poly_files_addtag  (a_file, x_tag);
      DEBUG_DATA   yLOG_value   ("addtag"    , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(into btree)---------------------*/
      rc = poly_btree_create (B_TAGS, x_tag, x_tag->name);
      DEBUG_DATA   yLOG_value   ("btree"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db_read_file     (tPROJ *a_proj, int a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_count     =    0;
   int         i           =    0;
   tFILE      *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(walk projects)------------------*/
   DEBUG_OUTP   yLOG_value   ("file count", a_count);
   for (i = 0; i < a_count; ++i) {
      /*---(allocate)-----------------------*/
      x_file = poly_files_new ();
      DEBUG_OUTP   yLOG_point   ("x_file"    , x_file);
      --rce;  if (x_file == NULL) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (&x_file, sizeof (tFILE), 1, f_db);
      /*---(add to project)-----------------*/
      rc = poly_proj_addfile (a_proj, x_file);
      DEBUG_DATA   yLOG_value   ("addfile"   , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(into btree)---------------------*/
      rc = poly_btree_create (B_FILES, x_file, x_file->name);
      DEBUG_DATA   yLOG_value   ("btree"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(dive)---------------------------*/
      rc = poly_db_read_tag  (x_file, x_file->count);
      DEBUG_DATA   yLOG_value   ("read_tag"  , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
poly_db_read          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_count     =    0;
   int         i           =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   DEBUG_OUTP   yLOG_info    ("db name"   , F_DB);
   f_db = fopen (F_DB, "rb");
   DEBUG_OUTP   yLOG_value   ("f_db"      , f_db);
   --rce;  if (f_db == NULL) {
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read project count)-------------*/
   fread  (&x_count, sizeof (int), 1, f_db);
   DEBUG_OUTP   yLOG_value   ("proj count", x_count);
   /*---(walk projects)------------------*/
   for (i = 0; i < x_count; ++i) {
      /*---(allocate)-----------------------*/
      x_proj = poly_proj_new ();
      DEBUG_OUTP   yLOG_point   ("x_proj"    , x_proj);
      --rce;  if (x_proj == NULL) {
         DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (&x_proj, sizeof (tPROJ), 1, f_db);
      /*---(into btree)---------------------*/
      rc = poly_btree_create (B_PROJ, x_proj, x_proj->name);
      DEBUG_DATA   yLOG_value   ("btree"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(dive)---------------------------*/
      rc = poly_db_read_file (x_proj, x_proj->count);
      DEBUG_DATA   yLOG_value   ("read_file" , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(close)--------------------------*/
   rc = fclose (f_db);
   DEBUG_OUTP   yLOG_value   ("f_db close", rc);
   --rce;  if (rc < 0) {
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return 0;
}


