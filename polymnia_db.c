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
   char        rc          =    0;
   tTAG       *x_tag       = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_tag = x_file->head;
   DEBUG_OUTP   yLOG_point   ("x_tag"     , x_tag);
   /*---(walk projects)------------------*/
   while (rc >= 0 && x_tag != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("tag"       , x_tag->name);
      fwrite (x_tag  , sizeof (tTAG), 1, f_db);
      /*---(next)------------------------*/
      x_tag = x_tag->next;
      DEBUG_OUTP   yLOG_point   ("x_tag"     , x_tag);
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
   DEBUG_OUTP   yLOG_value   ("count"     , x_proj->count);
   x_file = x_proj->head;
   DEBUG_OUTP   yLOG_point   ("x_file"    , x_file);
   /*---(walk projects)------------------*/
   while (rc >= 0 && x_file != NULL) {
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
   int         x_count     =    0;
   tPROJ      *x_proj      = NULL;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   DEBUG_OUTP   yLOG_info    ("db name"   , F_DB);
   f_db = fopen (F_DB, "wb");
   DEBUG_OUTP   yLOG_point   ("f_db"      , f_db);
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
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(walk projects)------------------*/
   DEBUG_INPT   yLOG_value   ("tag count" , a_count);
   for (i = 0; i < a_count; ++i) {
      /*---(allocate)-----------------------*/
      x_tag = poly_tags_new ();
      DEBUG_INPT   yLOG_point   ("x_tag"    , x_tag);
      --rce;  if (x_tag == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (x_tag, sizeof (tTAG), 1, f_db);
      DEBUG_INPT   yLOG_info    ("tag"       , x_tag->name);
      /*---(clear the pointers)-------------*/
      x_tag->file  = NULL;
      x_tag->next  = x_tag->prev  = NULL;
      x_tag->work  = NULL;
      x_tag->btree = NULL;
      /*---(add to project)-----------------*/
      rc = poly_files_addtag  (a_file, x_tag);
      DEBUG_INPT   yLOG_value   ("addtag"    , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(into btree)---------------------*/
      rc = poly_btree_hook (B_TAGS, x_tag, x_tag->name, &x_tag->btree);
      DEBUG_INPT   yLOG_value   ("btree"     , rc);
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
poly_db_read_file     (tPROJ *a_proj, int a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_count     =    0;
   int         i           =    0;
   tFILE      *x_file      = NULL;
   int         x_ntag      =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(walk projects)------------------*/
   DEBUG_INPT   yLOG_value   ("file count", a_count);
   for (i = 0; i < a_count; ++i) {
      /*---(allocate)-----------------------*/
      x_file = poly_files_new ();
      DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
      --rce;  if (x_file == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (x_file, sizeof (tFILE), 1, f_db);
      DEBUG_INPT   yLOG_info    ("file"      , x_file->name);
      /*---(clear the pointers)-------------*/
      x_ntag        = x_file->count;
      x_file->proj  = NULL;
      x_file->head  = x_file->tail  = NULL;
      x_file->next  = x_file->prev  = NULL;
      x_file->count = 0;
      x_file->btree = NULL;
      /*---(add to project)-----------------*/
      rc = poly_proj_addfile (a_proj, x_file);
      DEBUG_INPT   yLOG_value   ("addfile"   , rc);
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
      rc = poly_db_read_tag  (x_file, x_ntag);
      DEBUG_INPT   yLOG_value   ("read_tag"  , rc);
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
   int         x_count     =    0;
   int         i           =    0;
   tPROJ      *x_proj      = NULL;
   int         x_nfile     =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   DEBUG_INPT   yLOG_info    ("db name"   , F_DB);
   f_db = fopen (F_DB, "rb");
   DEBUG_INPT   yLOG_point   ("f_db"      , f_db);
   --rce;  if (f_db == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read project count)-------------*/
   fread  (&x_count, sizeof (int), 1, f_db);
   DEBUG_INPT   yLOG_value   ("proj count", x_count);
   /*---(walk projects)------------------*/
   for (i = 0; i < x_count; ++i) {
      /*---(allocate)-----------------------*/
      x_proj = poly_proj_new ();
      DEBUG_INPT   yLOG_point   ("x_proj"    , x_proj);
      --rce;  if (x_proj == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(read)---------------------------*/
      fread  (x_proj, sizeof (tPROJ), 1, f_db);
      DEBUG_INPT   yLOG_info    ("project"   , x_proj->name);
      /*---(clear the pointers)-------------*/
      x_nfile = x_proj->count;
      x_proj->head  = x_proj->tail  = NULL;
      x_proj->count = 0;
      x_proj->btree = NULL;
      /*---(into btree)---------------------*/
      rc = poly_btree_hook (B_PROJ, x_proj, x_proj->name, &x_proj->btree);
      DEBUG_INPT   yLOG_value   ("btree"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(dive)---------------------------*/
      rc = poly_db_read_file (x_proj, x_nfile);
      DEBUG_INPT   yLOG_value   ("read_file" , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(close)--------------------------*/
   rc = fclose (f_db);
   DEBUG_INPT   yLOG_value   ("f_db close", rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare btree)------------------*/
   rc = poly_btree_prepare_all ();
   DEBUG_PROG   yLOG_value   ("prepare"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}


