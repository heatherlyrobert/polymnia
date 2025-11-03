/*============================----beg-of-source---============================*/
#include  "polymnia.h"



static char s_print     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                     small supporters                         ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
FILES_wipe         (tFILE *a_dst)
{
   if (a_dst == NULL)  return -1;
   DEBUG_DATA   yLOG_snote   ("wipe");
   /*---(master)------------*/
   a_dst->i_type     = '-';
   a_dst->i_name [0] = '\0';
   a_dst->i_sort [0] = '\0';
   /*---(stats)-------------*/
   poly_cats_counts_clear (a_dst->counts);
   /*---(tags)--------------*/
   a_dst->i_proj     = NULL;
   a_dst->i_prev     = NULL;
   a_dst->i_next     = NULL;
   a_dst->i_chead    = NULL;
   a_dst->i_ctail    = NULL;
   a_dst->i_ccount   = 0;
   a_dst->i_btree    = NULL;
   /*---(tags)--------------*/
   return 1;
}

char*
FILES__memory           (tFILE *a_file)
{
   /*---(master)-------------------------*/
   ystrlcpy (s_print, "["  , LEN_RECD);
   poly_shared__check_char (s_print, a_file->i_type);
   poly_shared__check_str  (s_print, a_file->i_name);
   poly_shared__check_str  (s_print, a_file->i_sort);
   poly_shared__spacer     (s_print);
   /*---(project/file)-------------------*/
   poly_shared__check_ptr  (s_print, a_file->i_proj);
   poly_shared__check_ptr  (s_print, a_file->i_prev);
   poly_shared__check_ptr  (s_print, a_file->i_next);
   poly_shared__spacer     (s_print);
   /*---(functions)----------------------*/
   poly_shared__check_ptr  (s_print, a_file->i_chead);
   poly_shared__check_ptr  (s_print, a_file->i_ctail);
   poly_shared__check_num  (s_print, a_file->i_ccount);
   poly_shared__spacer     (s_print);
   /*---(btree)--------------------------*/
   poly_shared__check_ptr  (s_print, a_file->i_btree);
   ystrlcat (s_print, "]" , LEN_RECD);
   /*---(complete)-----------------------*/
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char FILES__new  (tFILE **a_new) { return poly_shared_new  ("file", sizeof (tFILE), a_new, NULL, '-', FILES_wipe); }
char FILES_force (tFILE **a_new) { return poly_shared_new  ("file", sizeof (tFILE), a_new, NULL, 'y', FILES_wipe); }
char FILES__free (tFILE **a_old) { return poly_shared_free ("file", a_old, NULL); }



/*====================------------------------------------====================*/
/*===----                   hooking and unhooking                      ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

char
FILES__hook             (tPROJ *a_proj, tFILE *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("->proj"    , a_file->i_proj);
   --rce;  if (a_file->i_proj != NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    (a_file->i_name);
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_value   ("count"     , a_proj->j_icount);
   DEBUG_DATA   yLOG_point   ("->head"    , a_proj->j_ihead);
   DEBUG_DATA   yLOG_point   ("->tail"    , a_proj->j_itail);
   if (a_proj->j_ihead == NULL) {
      DEBUG_DATA   yLOG_note    ("first");
      a_proj->j_ihead = a_proj->j_itail = a_file;
   } else {
      DEBUG_DATA   yLOG_note    ("append");
      a_file->i_prev        = a_proj->j_itail;
      a_proj->j_itail->i_next  = a_file;
      a_proj->j_itail        = a_file;
   }
   /*---(tie file back to proj)----------*/
   a_file->i_proj  = a_proj;
   /*---(update count)-------------------*/
   ++a_proj->j_icount;
   ++a_proj->COUNT_FILES;
   ++my.COUNT_FILES;
   DEBUG_DATA   yLOG_value   ("count"     , a_proj->j_icount);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILES__unhook           (tFILE *a_file)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_file);
   if (a_file == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   DEBUG_DATA   yLOG_spoint  (a_file->i_proj);
   if (a_file->i_proj == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -2);
      return -2;
   }
   DEBUG_DATA   yLOG_snote   (a_file->i_name);
   /*---(out of linked list)-------------*/
   DEBUG_DATA   yLOG_sint    (a_file->i_proj->j_icount);
   DEBUG_DATA   yLOG_spoint  (a_file->i_proj->j_ihead);
   DEBUG_DATA   yLOG_spoint  (a_file->i_proj->j_itail);
   DEBUG_DATA   yLOG_snote   ("unlink");
   if (a_file->i_next != NULL)  a_file->i_next->i_prev = a_file->i_prev;
   else                       a_file->i_proj->j_itail = a_file->i_prev;
   if (a_file->i_prev != NULL)  a_file->i_prev->i_next = a_file->i_next;
   else                       a_file->i_proj->j_ihead = a_file->i_next;
   /*---(update count)-------------------*/
   --(a_file->i_proj->j_icount);
   --(a_file->i_proj->COUNT_FILES);
   --(my.COUNT_FILES);
   DEBUG_DATA   yLOG_sint    (a_file->i_proj->j_icount);
   /*---(ground pointers)----------------*/
   a_file->i_proj = NULL;
   a_file->i_prev = NULL;
   a_file->i_next = NULL;
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
FILES_add               (tPROJ *a_proj, char *a_name, char a_type, tFILE **a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_new       = NULL;
   int         x_tries     =    0;
   int         x_len       =    0;
   char        x_type      =  'c';
   char        x_prefix    =  'n';
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file != NULL) {
      DEBUG_DATA   yLOG_point   ("*a_file"   , *a_file);
      if (*a_file != NULL) {
         DEBUG_DATA   yLOG_note    ("already set to a particular file");
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(create file)--------------------*/
   FILES__new (&x_new);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   ystrlcpy (x_new->i_name, a_name, LEN_TITLE);
   x_new->i_type   = a_type;
   /*---(standard names to front)--------*/
   if (strncmp (a_name, a_proj->j_name, strlen (a_proj->j_name)) == 0) {
      DEBUG_DATA   yLOG_note    ("matches project prefix");
      x_prefix = 'Y';
   }
   /*---(headers to front)---------------*/
   if (x_new->i_type == 'h') {
      DEBUG_DATA   yLOG_note    ("header type");
      x_type = 'H';
   }
   /*---(units come last)----------------*/
   if (strstr (x_new->i_name, ".unit")       != NULL) {
      DEBUG_DATA   yLOG_note    ("unit test file");
      x_prefix = 'Z';
   }
   /*---(master to top of units)---------*/
   if (strcmp (x_new->i_name, "master.unit") == 0) {
      DEBUG_DATA   yLOG_note    ("master unit test file");
      x_type   = 'H';
   }
   /*---(into temp btree)----------------*/
   sprintf (x_new->i_sort, "%c%c%s", x_prefix, x_type, x_new->i_name);
   DEBUG_DATA   yLOG_info    ("sort"      , x_new->i_sort);
   rc = FILES__hook    (a_proj, x_new);
   DEBUG_DATA   yLOG_value   ("addfile"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> rc = ySORT_hook (B_TEMP , x_new, x_new->i_sort, &x_new->btree);                  <* 
    *> DEBUG_DATA   yLOG_value   ("temp"      , rc);                                  <* 
    *> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(into btree)---------------------*/
   rc = ySORT_hook (B_FILES, x_new, x_new->i_name, &x_new->i_btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create hint)--------------------*/
   /*> rc = ystrlhint (ySORT_count (B_FUNCS) - 1 + ySORT_count (B_FILES) - 1, "uA", x_new->c_hint);   <* 
    *> DEBUG_DATA   yLOG_value   ("hint"      , rc);                                                         <* 
    *> --rce;  if (rc < 0) {                                                                                 <* 
    *>    DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                                     <* 
    *>    return rce;                                                                                        <* 
    *> }                                                                                                     <* 
    *> DEBUG_DATA   yLOG_info    ("hint"      , x_new->c_hint);                                                <*/
   /*---(save)---------------------------*/
   if (a_file != NULL) {
      *a_file = x_new;
      DEBUG_DATA   yLOG_point   ("*a_file"   , *a_file);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILES_remove            (tFILE **a_file)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   /*---(beginning)----------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_file = *a_file;
   DEBUG_DATA   yLOG_point   ("x_file"    , x_file);
   --rce;  if (x_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("->i_name"    , x_file->i_name);
   /*---(remove line counts first)-------*/
   x_file->i_proj->COUNT_LINES -= x_file->COUNT_LINES;
   x_file->i_proj->COUNT_EMPTY -= x_file->COUNT_EMPTY;
   x_file->i_proj->COUNT_DOCS  -= x_file->COUNT_DOCS ;
   x_file->i_proj->COUNT_DEBUG -= x_file->COUNT_DEBUG;
   x_file->i_proj->COUNT_CODE  -= x_file->COUNT_CODE ;
   x_file->i_proj->COUNT_SLOCL -= x_file->COUNT_SLOCL;
   my.COUNT_LINES            -= x_file->COUNT_LINES;
   my.COUNT_EMPTY            -= x_file->COUNT_EMPTY;
   my.COUNT_DOCS             -= x_file->COUNT_DOCS ;
   my.COUNT_DEBUG            -= x_file->COUNT_DEBUG;
   my.COUNT_CODE             -= x_file->COUNT_CODE ;
   my.COUNT_SLOCL            -= x_file->COUNT_SLOCL;
   /*---(purge assigned tags)------------*/
   DEBUG_DATA   yLOG_point   ("->proj"    , x_file->i_proj);
   if (x_file->i_proj != NULL) {
      rc = poly_func_purge (x_file, '-');
      DEBUG_DATA   yLOG_value   ("purge"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(out of linked list)-------------*/
   DEBUG_DATA   yLOG_point   ("->proj"    , x_file->i_proj);
   if (x_file->i_proj != NULL) {
      rc = FILES__unhook (x_file);
      DEBUG_DATA   yLOG_value   ("unhook"    , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(unhook from btree)--------------*/
   rc = ySORT_unhook (&x_file->i_btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free main)----------------------*/
   DEBUG_DATA   yLOG_note    ("free");
   free (x_file);
   *a_file = NULL;
   DEBUG_DATA   yLOG_point   ("*a_file"   , *a_file);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
FILES_init              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = ySORT_btree (B_FILES, "files");
   DEBUG_PROG   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = ySORT_btree (B_TEMP , "temp" );
   DEBUG_PROG   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILES_purge             (tPROJ *a_proj, char a_update)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_file      = NULL;
   tFILE      *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk-through)-------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_proj->j_icount);
   x_file = a_proj->j_ihead;
   while (x_file != NULL) {
      x_next = x_file->i_next;
      DEBUG_DATA   yLOG_point   ("x_file"    , x_file);
      DEBUG_DATA   yLOG_info    ("->i_name"    , x_file->i_name);
      rc = FILES_remove      (&x_file);
      x_file = x_next;
   }
   /*---(check)--------------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_proj->j_icount);
   --rce;  if (a_proj->j_icount > 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update btrees)------------------*/
   --rce;  if (a_update == 'y') {
      rc = ySORT_prepare (B_FILES);
      if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = ySORT_prepare (B_FUNCS);
      if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILES_wrap              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(walk through list)--------------*/
   /*> rc = ySORT_purge (B_FILES);                                               <* 
    *> DEBUG_PROG   yLOG_value   ("purge"     , rc);                                  <* 
    *> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                       review files                           ----===*/
/*====================------------------------------------====================*/
static void  o___REVIEW__________o () { return; }

static  s_swaps      = 0;
static  s_comps      = 0;
static  s_teles      = 0;

char
FILES__gnome_swap      (tFILE *a_one, tFILE *a_two)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   /*---(beginning)----------------------*/
   DEBUG_SORT   yLOG_senter  (__FUNCTION__);
   DEBUG_SORT   yLOG_spoint  (a_one);
   --rce;  if (a_one == NULL) {
      DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SORT   yLOG_spoint  (a_two);
   --rce;  if (a_two == NULL) {
      DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_one == a_two) {
      DEBUG_SORT   yLOG_snote   ("same, no action");
      DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(cut two from list)--------------*/
   DEBUG_SORT   yLOG_snote   ("unlink");
   if (a_two->i_next != NULL)   a_two->i_next->i_prev = a_two->i_prev;
   else                       a_two->i_proj->j_itail = a_two->i_prev;
   if (a_two->i_prev != NULL)   a_two->i_prev->i_next = a_two->i_next;
   else                       a_two->i_proj->j_ihead = a_two->i_next;
   /*---(insert before one)--------------*/
   DEBUG_SORT   yLOG_snote   ("insert");
   if (a_one->i_prev != NULL)   a_one->i_prev->i_next = a_two;
   else                       a_one->i_proj->j_ihead = a_two;
   a_two->i_prev = a_one->i_prev;
   a_two->i_next = a_one;
   a_one->i_prev = a_two;
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
FILES__gnome            (tPROJ *x_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFILE      *o           = NULL;          /* origin point                   */
   int         x_match     =    0;
   char        x_flag      =  '-';
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   o = x_proj->j_ihead;
   /*---(do the gnome walk)--------------*/
   while (o != NULL) {
      /*---(beginning)-------------------*/
      if (o == x_proj->j_ihead) {
         DEBUG_SORT   yLOG_note    ("bounce off beginning");
         o = o->i_next;
         continue;
      }
      /*---(compare)---------------------*/
      x_match = strcmp (o->i_prev->i_sort, o->i_sort);
      x_flag  = (x_match <= 0) ? 'y' : '#';
      DEBUG_SORT   yLOG_complex ("compare"   , "%-10p (%-30.30s) v %-10p (%-30.30s)   %c %4d", o->i_prev, o->i_prev->i_sort, o, o->i_sort, x_flag, x_match);
      if (x_match <= 0) {
         DEBUG_SORT   yLOG_note    ("move forward");
         o = o->i_next;
         continue;
      }
      /*---(swap)------------------------*/
      DEBUG_SORT   yLOG_note    ("swap and move back");
      FILES__gnome_swap (o->i_prev, o);
      /*---(next)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILES__filter           (char a_name [LEN_TITLE], char a_units, char *r_type, char r_mans [LEN_LABEL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   char        x_point     =  '-';
   char        x_point2    =  '-';
   char        x_type      =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_type  != NULL)  *r_type = '-';
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_name"     , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_info    ("a_name"     , a_name);
   /*---(cut too short)---------------*/
   x_len = strlen (a_name);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   if (x_len <  3)  {
      DEBUG_INPT   yLOG_note    ("name too short, SKIP");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(cut too long)----------------*/
   if (x_len > 50) {
      DEBUG_INPT   yLOG_note    ("crazy long name, SKIP");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(hidden)-------------------------*/
   if (a_name [0] == '.')  {
      DEBUG_INPT   yLOG_note    ("hidden, SKIP");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(one character suffixes)------*/
   x_point = a_name [x_len - 2];
   DEBUG_INPT   yLOG_char    ("x_point"   , x_point);
   if (x_point == '.') {
      x_type = a_name [x_len - 1];
      DEBUG_INPT   yLOG_char    ("x_type"    , x_type);
      if (strchr ("12345678", x_type) != NULL) {
         DEBUG_INPT   yLOG_note    ("manual/documentation file");
         if (r_mans != NULL)  r_mans [x_type - '1'] = x_type;
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      if (strchr ("ch", x_type) == NULL) {
         DEBUG_INPT   yLOG_note    ("not a c or h file, SKIP");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      if (x_len > 7 && strcmp ("_unit.c", a_name + x_len - 7) == 0) {
         DEBUG_INPT   yLOG_note    ("cut the unit testing code files, SKIP");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      if (strcmp ("master.h", a_name) == 0) {
         DEBUG_INPT   yLOG_note    ("never look at testing header");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(unit tests)------------------*/
   else if (x_len >= 6) {
      x_point  = a_name [x_len - 5];
      x_point2 = a_name [x_len - 6];
      DEBUG_INPT   yLOG_complex ("x_point"   , "%c %c", x_point, x_point2);
      if (x_point != '.' && x_point2 != '.') {
         DEBUG_INPT   yLOG_note    ("not the right length suffix, SKIP");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      if (strcmp ("unit" , a_name + x_len - 4) != 0 &&
            strcmp ("sunit", a_name + x_len - 5) != 0) {
         DEBUG_INPT   yLOG_note    ("not a unit suffix, SKIP");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      /*---(quick calloff)------------------*/
      DEBUG_INPT   yLOG_char    ("g_unit"    , a_units);
      if (a_units != 'y') {
         DEBUG_INPT   yLOG_note    ("called with --nounit");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      x_type = POLY_UNIT;
   }
   /*---(all else)--------------------*/
   else {
      DEBUG_INPT   yLOG_note    ("bad suffix, SKIP");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(save-back)-----------------------------*/
   if (r_type  != NULL)  *r_type = x_type;
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
FILES__sorting          (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   tFILE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(update sorts)-------------------*/
   rc = ySORT_prepare   (B_FILES);
   DEBUG_SORT   yLOG_value   ("btree"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> rc = ySORT_prepare   (B_TEMP );                                                <* 
    *> DEBUG_SORT   yLOG_value   ("temp"       , rc);                                 <* 
    *> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(check count)--------------------*/
   /*> DEBUG_INPT   yLOG_value   ("count"     , ySORT_count (B_TEMP ));               <*/
   /*> --rce;  if (ySORT_count (B_TEMP ) <= 0) {                                      <* 
    *>    DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return  rce;                                                                <* 
    *> }                                                                              <*/
   rc = FILES__gnome (a_proj);
   DEBUG_INPT   yLOG_value   ("dgnome"    , rc);
   /*---(add to project)------------------------*/
   /*> x_curr = ySORT_by_cursor (B_TEMP , YDLST_HEAD, &x_curr);                       <* 
    *> while (x_curr != NULL) {                                                       <* 
    *>    rc = FILES__hook    (a_proj, x_curr);                                       <* 
    *>    DEBUG_DATA   yLOG_value   ("hook"      , rc);                               <* 
    *>    --rce;  if (rc < 0) {                                                       <* 
    *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                           <* 
    *>       return rce;                                                              <* 
    *>    }                                                                           <* 
    *>    x_curr = ySORT_by_cursor (B_TEMP , YDLST_NEXT, &x_curr);                    <* 
    *> }                                                                              <*/
   /*---(prepare temp)-------------------*/
   rc = ySORT_purge     (B_TEMP );
   DEBUG_SORT   yLOG_value   ("temp"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> make a list of input files --------------------------------*/
FILES_gather            (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   DIR        *x_dir       = NULL;          /* directory pointer              */
   tDIRENT    *x_file      = NULL;          /* directory entry pointer        */
   char        x_name      [LEN_TITLE];      /* file name                      */
   int         x_len       =    0;
   char        x_point     =  '-';
   char        x_point2    =  '-';
   char        x_type      =  '-';
   int         x_read      =    0;          /* count of entries reviewed      */
   int         x_good      =    0;          /* count of entries processed     */
   tFILE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_proj"     , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_info    ("a_proj"     , a_proj->j_name);
   /*---(prepare temp)-------------------*/
   rc = ySORT_purge     (B_TEMP );
   DEBUG_SORT   yLOG_value   ("temp"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open dir)-----------------------*/
   x_dir = opendir(".");
   DEBUG_INPT   yLOG_point   ("x_dir"      , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_note    ("openned successfully");
   /*---(process entries)----------------*/
   DEBUG_INPT   yLOG_note    ("processing entries");
   while (1) {
      /*---(read a directory entry)------*/
      x_file = readdir (x_dir);
      DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
      ++x_read;
      /*---(filter by name)--------------*/
      ystrlcpy (x_name, x_file->d_name, LEN_TITLE);
      DEBUG_INPT   yLOG_info    ("x_name"    , x_name);
      rc = FILES__filter     (x_name, my.g_unit, &x_type, a_proj->j_manual);
      DEBUG_INPT   yLOG_value   ("filter"    , rc);
      if (rc <= 0)   continue;
      /*---(save)------------------------*/
      x_curr = NULL;
      FILES_add     (a_proj, x_name, x_type, &x_curr);
      ++x_good;
      DEBUG_INPT   yLOG_note    ("added to inventory");
      /*---(check globals)---------------*/
      /*> if (x_type == 'h')  poly_vars_inventory (x_curr);                           <*/
      /*---(done)------------------------*/
   }
   DEBUG_INPT   yLOG_value   ("x_read"    , x_read);
   DEBUG_INPT   yLOG_value   ("x_good"    , x_good);
   /*---(close dir)----------------------*/
   DEBUG_INPT   yLOG_note    ("closing directory");
   rc = closedir (x_dir);
   DEBUG_INPT   yLOG_value   ("close_rc"  , rc);
   /*---(prepare for use)----------------*/
   rc = FILES__sorting       (a_proj);
   DEBUG_SORT   yLOG_value   ("sorting"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> poly_extern_list ();                                                           <*/
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return x_good;
}



/*====================------------------------------------====================*/
/*===----                        searching                             ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  FILES_count             (void)                          { return ySORT_count     (B_FILES); }
char FILES_by_name           (uchar *a_name, tFILE **r_file) { return ySORT_by_name   (B_FILES, a_name, r_file); }
char FILES_by_index          (int n, tFILE **r_file)         { return ySORT_by_index  (B_FILES, n, r_file); }
char FILES_by_cursor         (char a_dir, tFILE **r_file)    { return ySORT_by_cursor (B_FILES, a_dir, r_file); }

char
FILES_by_proj_cursor    (tPROJ *a_proj, char a_dir, tFILE **r_file)
{
   char        rce         =  -10;
   char        rc          =    0;
   --rce;  if (a_proj == NULL)   return --rce;
   --rce;  if (r_file == NULL)   return --rce;
   if (r_file != NULL)  *r_file = NULL;
   rc = FILES_by_cursor (a_dir, r_file);
   --rce;  while (*r_file != NULL || (*r_file)->i_proj != a_proj) {
      switch (a_dir) {
      case YDLST_HEAD  : case YDLST_NEXT  : case YDLST_CURR  :
         rc = FILES_by_cursor (YDLST_NEXT, r_file);
         break;
      case YDLST_TAIL  : case YDLST_PREV  :
         rc = FILES_by_cursor (YDLST_PREV, r_file);
         break;
      default :
         return rce;
      }
   }
   if (r_file != NULL) return 1;
   return rce;
}

char
FILES_by_proj_index     (tPROJ *a_proj, int n, tFILE **r_file)
{
   char        rce         =  -10;
   tFILE      *x_file      = NULL;
   int         c           =    0;
   --rce;  if (a_proj == NULL)   return rce;
   --rce;  if (r_file == NULL)   return rce;
   *r_file = NULL;
   x_file = a_proj->j_ihead;
   while (x_file != NULL) {
      if (c == n) {
         *r_file = x_file;
         return 0;
      }
      x_file = x_file->i_next;
      ++c;
   }
   --rce;  return rce;
}



/*====================------------------------------------====================*/
/*===----                   size and memory footprint                  ----===*/
/*====================------------------------------------====================*/
static void  o___FOOTPRINT_______o () { return; }

char
FILES_footprint        (tFILE *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_TITLE] = "";
   char        x_cmd       [LEN_RECD]  = "";
   int         x_len       =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *r           = NULL;
   int         rci         =    0;
   tSTAT       st;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->i_name);
   DEBUG_INPT   yLOG_char    ("type"      , a_file->i_type);
   --rce;  if (a_file->i_type != 'c') {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare name)--------------------------*/
   ystrlcpy (x_name, a_file->i_name, LEN_TITLE);
   x_len = strlen (x_name);
   x_name [--x_len] = 'o';
   x_name [++x_len] = 's';
   x_name [++x_len] = '\0';
   DEBUG_INPT   yLOG_info    ("x_name"    , x_name);
   /*---(defaults)-----------------------*/
   a_file->COUNT_TEXT = 0;
   a_file->COUNT_DATA = 0;
   a_file->COUNT_BSS  = 0;
   /*---(check for existance)------------*/
   rci = lstat (x_name, &st);
   DEBUG_FILE   yLOG_value   ("lstat"     , rci);
   --rce; if (rci < 0) {
      DEBUG_FILE   yLOG_note    ("file does not exist, can not read");
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(check for regular file)---------*/
   --rce;  if (!S_ISREG (st.st_mode)) {
      DEBUG_FILE   yLOG_note    ("not a regular file, rejected");
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(get data)------------------------------*/
   sprintf (x_cmd, "size %s > /tmp/polymnia_footprint.txt", x_name);
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("size"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pull data)-----------------------------*/
   f = fopen ("/tmp/polymnia_footprint.txt", "rt");
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get data line)-------------------------*/
   fgets  (x_recd, LEN_RECD, f);
   fgets  (x_recd, LEN_RECD, f);
   /*---(parse)---------------------------------*/
   p = strtok_r (x_recd, " ", &r);
   --rce;  if (p == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_file->i_proj->COUNT_TEXT += a_file->COUNT_TEXT = atoi (p);
   p = strtok_r (NULL  , " ", &r);
   --rce;  if (p == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_file->i_proj->COUNT_DATA += a_file->COUNT_DATA = atoi (p);
   p = strtok_r (NULL  , " ", &r);
   --rce;  if (p == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_file->i_proj->COUNT_BSS  += a_file->COUNT_BSS  = atoi (p);
   /*---(close)---------------------------------*/
   rc = fclose (f);
   DEBUG_INPT   yLOG_point   ("close"     , rc);
   /*---(destroy temp file)---------------------*/
   sprintf (x_cmd, "rm -f /tmp/polymnia_footprint.txt  2> /dev/null");
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("size"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       reporting support                      ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTING_______o () { return; }


/*> snprintf (unit_answer, LEN_RECD, "123456789-123456789-  ·  123456789-123456789-123456789-  123456789-123456789-123456789-    ´   -   -     ´   -   -   -   -   -  Ï    ·c   ·f   ·b  h=···                            t=···                             Ï     ·p    ·b    ·e  Ï");   <*/
/*>                                                                                                                                                                                                                                                                                    <* 
 *> char*                                                                                                                                                                                                                                                                              <* 
 *> FILES__unit_cursor      (tPROJ *a_proj, char a_dir)                                                                                                                                                                                                                                <* 
 *> {                                                                                                                                                                                                                                                                                  <* 
 *>    tFILE      *v           = NULL;                                                                                                                                                                                                                                                 <* 
 *>    int         x_fore      =    0;                                                                                                                                                                                                                                                 <* 
 *>    int         x_back      =    0;                                                                                                                                                                                                                                                 <* 
 *>    char        t           [LEN_RECD]  = "åæ";                                                                                                                                                                                                                                     <* 
 *>    char        s           [LEN_RECD]  = "åæ";                                                                                                                                                                                                                                     <* 
 *>    char        r           [LEN_RECD]  = "åæ";                                                                                                                                                                                                                                     <* 
 *>    if (a_proj == NULL) {                                                                                                                                                                                                                                                           <* 
 *>       snprintf (unit_answer, LEN_RECD, "(n/a)                 -  ´···                            ´···                              ´   -   -     ´   -   -   -   -   -    ´   -   -   Ï    ·c   ·f   ·b  h=···                            t=···                             Ï");   <* 
 *>    } else {                                                                                                                                                                                                                                                                        <* 
 *>       sprintf  (t, "å%.20sæ", a_proj->j_name);                                                                                                                                                                                                                                     <* 
 *>       if (a_proj->j_ihead != NULL) {                                                                                                                                                                                                                                               <* 
 *>          sprintf  (s, "å%.15sæ", a_proj->j_ihead->i_name);                                                                                                                                                                                                                         <* 
 *>          sprintf  (r, "å%.15sæ", a_proj->j_itail->i_name);                                                                                                                                                                                                                         <* 
 *>          v = a_proj->j_ihead; while (v != NULL) { ++x_fore; v = v->i_next; }                                                                                                                                                                                                       <* 
 *>          v = a_proj->j_itail; while (v != NULL) { ++x_back; v = v->i_prev; }                                                                                                                                                                                                       <* 
 *>       }                                                                                                                                                                                                                                                                            <* 
 *>       snprintf (unit_answer, LEN_RECD, "PROJ files       : %-22.22s   %3dc %3df %3db   %-17.17s %s", t, a_proj->j_icount, x_fore, x_back, s, r);                                                                                                                                   <* 
 *>    }                                                                                                                                                                                                                                                                               <* 
 *>    return unit_answer;                                                                                                                                                                                                                                                             <* 
 *> }                                                                                                                                                                                                                                                                                  <*/


char*
FILES__unit_by_proj     (tPROJ *a_proj, char a_dir)
{
   char        rce         =    0;
   char        rc          =    0;
   int         x_fore      =    0;
   int         x_back      =    0;
   tFILE      *u           = NULL;
   tFUNC      *v           = NULL;
   char        s           [LEN_RECD]  = "···";
   char        r           [LEN_RECD]  = "···";
   if (a_proj == NULL)  return "((a_proj null))";
   rc = FILES_by_proj_cursor (a_proj, a_dir, &u);
   if (u == NULL) {
      snprintf (unit_answer, LEN_RECD, "%-20.20s  -  (n/a)                           ´·····························    ´   -   -     ´   -   -   -   -   -  Ï    ·c   ·f   ·b  h=······························  t=······························  Ï     ´p    ·b    ·e  Ï", a_proj->j_name);
   } else {
      if (u->i_chead != NULL) {
         sprintf  (s, "%.30s", u->i_chead->c_name);
         sprintf  (r, "%.30s", u->i_ctail->c_name);
         v = u->i_chead; while (v != NULL) { ++x_fore; v = v->c_next; }
         v = u->i_ctail; while (v != NULL) { ++x_back; v = v->c_prev; }
      }
      /*> snprintf (unit_answer, LEN_RECD, "%-20.20s  %c  %-30.30s  ´·····························    - %3d %3d  %3d %3d %3d %3d %3d %3d  Ï  %3dc %3dc %3db  h=%-30.30s  t=%-30.30s  Ï     ´p    ·b    ·e  Ï",   <* 
       *>       a_proj->j_name, u->i_type, u->i_name,                                                                                                                                                            <* 
       *>       u->COUNT_FUNCS, u->COUNT_YLIBS, u->COUNT_LINES, u->COUNT_EMPTY, u->COUNT_DOCS, u->COUNT_DEBUG, u->COUNT_CODE, u->COUNT_SLOCL,                                                                    <* 
       *>       u->i_ccount, x_fore, x_back, s, r);                                                                                                                                                              <*/
   }
   return unit_answer;
}






/*> tFILE      *v           = NULL;                                                                                                                                                     <* 
 *> int         x_fore      =    0;                                                                                                                                                     <* 
 *> int         x_back      =    0;                                                                                                                                                     <* 
 *> char        t           [LEN_RECD]  = "åæ";                                                                                                                                         <* 
 *> char        s           [LEN_RECD]  = "åæ";                                                                                                                                         <* 
 *> char        r           [LEN_RECD]  = "åæ";                                                                                                                                         <* 
 *> if (a_proj == NULL) {                                                                                                                                                               <* 
 *>    snprintf (unit_answer, LEN_RECD, "PROJ files       : åæ                         ·c   ·f   ·b   åæ                åæ");                                                           <* 
 *> } else {                                                                                                                                                                            <* 
 *>    sprintf  (t, "å%.20sæ", a_proj->j_name);                                                                                                                                         <* 
 *>    if (a_proj->j_ihead != NULL) {                                                                                                                                                   <* 
 *>       sprintf  (s, "å%.15sæ", a_proj->j_ihead->i_name);                                                                                                                             <* 
 *>       sprintf  (r, "å%.15sæ", a_proj->j_itail->i_name);                                                                                                                             <* 
 *>       v = a_proj->j_ihead; while (v != NULL) { ++x_fore; v = v->i_next; }                                                                                                           <* 
 *>       v = a_proj->j_itail; while (v != NULL) { ++x_back; v = v->i_prev; }                                                                                                           <* 
 *>    }                                                                                                                                                                                <* 
 *>    snprintf (unit_answer, LEN_RECD, "PROJ files       : %-22.22s  %3d %3d %3d  %3d %3d %3d %3d %3d %3d  %3dc %3df %3db  %-17.17s %s", t, a_proj->j_icount, x_fore, x_back, s, r);   <* 
 *> }                                                                                                                                                                                   <* 
 *> return unit_answer;                                                                                                                                                                 <* 
 *> }                                                                                                                                                                                   <*/

/*> char        rce         =    0;                                                                                                                                                             <* 
 *> char        rc          =    0;                                                                                                                                                             <* 
 *> int         x_fore      =    0;                                                                                                                                                             <* 
 *> int         x_back      =    0;                                                                                                                                                             <* 
 *> tFILE      *x_file      = NULL;                                                                                                                                                             <* 
 *> tFUNC      *v           = NULL;                                                                                                                                                             <* 
 *> char        s           [LEN_RECD]  = "···";                                                                                                                                                <* 
 *> char        r           [LEN_RECD]  = "···";                                                                                                                                                <* 
 *> if (a_proj == NULL)  return "((a_proj null))";                                                                                                                                              <* 
 *> rc = FILES_by_proj_cursor (a_proj, a_dir, &x_file);                                                                                                                                         <* 
 *> if (x_file == NULL) {                                                                                                                                                                       <* 
 *>    snprintf (unit_answer, LEN_RECD, "(n/a)                 ·  ···                              ·c   ·f   ·b  h ···                               t ···                               Ï");   <* 
 *> } else {                                                                                                                                                                                    <* 
 *>    if (x_file->i_chead != NULL) {                                                                                                                                                           <* 
 *>       sprintf  (s, "%.30s", a_proj->i_chead->c_name);                                                                                                                                       <* 
 *>       sprintf  (r, "%.30s", a_proj->i_ctail->c_name);                                                                                                                                       <* 
 *>       v = a_proj->i_chead; while (v != NULL) { ++x_fore; v = v->c_next; }                                                                                                                   <* 
 *>       v = a_proj->i_ctail; while (v != NULL) { ++x_back; v = v->c_prev; }                                                                                                                   <* 
 *>    }                                                                                                                                                                                        <* 
 *>    snprintf (unit_answer, LEN_RECD, "%-20.20s  %c  %-30.30s   ·c   ·f   ·b  h %-30.30s  t %-30.30s  Ï",                                                                                     <*/
/*> a_proj->j_name, x_file->i_type, x_file->i_name, x_file->i_ccount, x_fore, x_back, s, r);   <*/



char
FILES_line              (tFILE *a_file, char a_style, char a_use, char a_pre, int a, int b, char a_print)
{
   /*  n  name     , just the name
    *  s  stats    , short count, name, plus statistics
    *  a  all      , long count, name, plus statistics
    *  f  footprint, memory footprint
    *
    */
   char        t           [LEN_RECD] = "";
   char        x_type      =  '-';
   char        x_files     [LEN_TERSE] = "·";
   char        x_funcs     [LEN_TERSE] = "·";
   char        x_ylibs     [LEN_TERSE] = "·";
   char        x_lines     [LEN_TERSE] = "·";
   char        x_empty     [LEN_TERSE] = "·";
   char        x_docs      [LEN_TERSE] = "·";
   char        x_debug     [LEN_TERSE] = "·";
   char        x_code      [LEN_TERSE] = "·";
   char        x_slocl     [LEN_TERSE] = "·";
   char        x_text      [LEN_TERSE] = "·";
   char        x_data      [LEN_TERSE] = "·";
   char        x_bss       [LEN_TERSE] = "·";
   /*---(prepare)------------------------*/
   ystrlcpy (s_print, "", LEN_RECD);
   x_type   = a_use;
   if (a_file == NULL) {
      if (a_use == '-')  x_type = 'h';
      if (a_use == 'd')  x_type = 'h';
   }
   /*---(indent)-------------------------*/
   switch (a_pre) {
   case '>' :   if (strchr ("pt", x_type) != NULL)  sprintf (t, "··"); else sprintf (t, "  "); break;
   case '#' :   sprintf (t, "# ");                             break;
   default  :   ystrlcpy (t, "", LEN_RECD);                     break;
   }
   ystrlcat (s_print, t, LEN_RECD);
   /*---(index)--------------------------*/
   if (strchr ("aA", a_style) != NULL) {
      switch (x_type) {
      case 'h' :   sprintf (t, "prj fil fnc  ");               break;
      case 'p' :   sprintf (t, "Ï--·Ï--·Ï--··");               break;
      case 't' :   sprintf (t, "prj·fil·fnc··");               break;
      case 'd' :   sprintf (t, "%-3d %-3d ·    ", a + 1, b + 1); break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   if (strchr ("sL", a_style) != NULL) {
      switch (x_type) {
      case 'h' :   sprintf (t, "fil  ");                       break;
      case 'p' :   sprintf (t, "Ï--··");                       break;
      case 't' :   sprintf (t, "fil··");                       break;
      case 'd' :   sprintf (t, "%-3d  ", b + 1);               break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(name)---------------------------*/
   switch (x_type) {
   case 'h' :   sprintf (t, "---name---------------  ");    break;
   case 'p' :   sprintf (t, "Ï---------------------··");    break;
   case 't' :   sprintf (t, "name····················");    break;
   case 'd' :   sprintf (t, "%-22.22s  ", a_file->i_name);    break;
   default  :   ystrlcpy (t, "", LEN_RECD);                  break;
   }
   ystrlcat (s_print, t, LEN_RECD);
   /*---(statistics)---------------------*/
   if (strchr ("sLaA", a_style) != NULL) {
      if (a_file != NULL) {
         if (a_file->COUNT_FUNCS > 0)  ystrl4main (a_file->COUNT_FUNCS, x_funcs, 0, 'c', '-', LEN_TERSE);
         if (a_file->COUNT_YLIBS > 0)  ystrl4main (a_file->COUNT_YLIBS, x_ylibs, 0, 'c', '-', LEN_TERSE);
         if (a_file->COUNT_LINES > 0)  ystrl4main (a_file->COUNT_LINES, x_lines, 0, 'c', '-', LEN_TERSE);
         if (a_file->COUNT_EMPTY > 0)  ystrl4main (a_file->COUNT_EMPTY, x_empty, 0, 'c', '-', LEN_TERSE);
         if (a_file->COUNT_DOCS  > 0)  ystrl4main (a_file->COUNT_DOCS , x_docs , 0, 'c', '-', LEN_TERSE);
         if (a_file->COUNT_DEBUG > 0)  ystrl4main (a_file->COUNT_DEBUG, x_debug, 0, 'c', '-', LEN_TERSE);
         if (a_file->COUNT_CODE  > 0)  ystrl4main (a_file->COUNT_CODE , x_code , 0, 'c', '-', LEN_TERSE);
         if (a_file->COUNT_SLOCL > 0)  ystrl4main (a_file->COUNT_SLOCL, x_slocl, 0, 'c', '-', LEN_TERSE);
      }
      switch (x_type) {
      case 'h' :
         sprintf (t, "-files -funcs -ylibs ---lines ---empty ----docs ---debug ----code ---slocl  ");
         break;
      case 'p' :
         sprintf (t, "Ï-----·Ï-----·Ï-----·Ï-------·Ï-------·Ï-------·Ï-------·Ï-------·Ï-------··");
         break;
      case 't' :
         sprintf (t, "files··funcs··ylibs··lines····empty····docs·····debug····code·····slocl·····");
         break;
      case 'd' :
         sprintf (t, "%6.6s %6.6s %6.6s %8.8s %8.8s %8.8s %8.8s %8.8s %8.8s  ",
               "-", x_funcs, x_ylibs,
               x_lines, x_empty, x_docs , x_debug, x_code , x_slocl);
         break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(memory)-------------------------*/
   if (strchr ("aAf"  , a_style) != NULL) {
      if (a_file != NULL) {
         if (a_file->COUNT_TEXT  > 0)  ystrl4main (a_file->COUNT_TEXT , x_text , 0, 'c', '-', LEN_TERSE);
         if (a_file->COUNT_DATA  > 0)  ystrl4main (a_file->COUNT_DATA , x_data , 0, 'c', '-', LEN_TERSE);
         if (a_file->COUNT_BSS   > 0)  ystrl4main (a_file->COUNT_BSS  , x_bss  , 0, 'c', '-', LEN_TERSE);
      }
      switch (x_type) {
      case 'h' : sprintf (t, "---text-- ---data-- ---bss---  ");  break;
      case 'p' : sprintf (t, "Ï--------·Ï--------·Ï--------··");  break;
      case 't' : sprintf (t, "text······data······bss········");  break;
      case 'd' : sprintf (t, "%9.9s %9.9s %9.9s  ", x_text, x_data, x_bss);
                 break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(newline)------------------------*/
   if (a_print == 'y') {
      if      (x_type == 'p')  printf ("#@ x-parse   å%sæ\n", s_print);
      else if (x_type == 't')  printf ("#@ titles    å%sæ\n", s_print);
      else if (x_type == 'h')  printf ("#%s\n", s_print + 1);
      else                     printf ("%s\n", s_print);
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
FILES__unit             (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   char        s           [LEN_RECD] = "[]";
   char        r           [LEN_RECD] = "[]";
   tFILE      *u           = NULL;
   tFUNC      *v           = NULL;
   int         x_fore      =    0;
   int         x_back      =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FILE unit        : file number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "FILE count       : %3d", ySORT_count (B_FILES));
      return unit_answer;
   }
   else if (strcmp (a_question, "print"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "FILE print       : %4d[%-.400s]", strlen (s_print), s_print);;
      return unit_answer;
   }
   if (strncmp (unit_answer, "FILE unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FILE unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "stats"     )     == 0) {
      FILES_by_index     (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->i_name);
         snprintf (unit_answer, LEN_RECD, "FILE stats  (%2d) : %-22.22s     · %3d %3d   %3d %3d %3d %3d %3d %3d", i, t, u->COUNT_FUNCS, u->COUNT_YLIBS, u->COUNT_LINES, u->COUNT_EMPTY, u->COUNT_DOCS, u->COUNT_DEBUG, u->COUNT_CODE, u->COUNT_SLOCL);
      } else {
         snprintf (unit_answer, LEN_RECD, "FILE stats  (%2d) : []                         ·   -   -     -   -   -   -   -   -", i);
      }
   }
   else if (strcmp (a_question, "funcs"     )     == 0) {
      FILES_by_index     (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->i_name);
         if (u->i_chead != NULL) {
            sprintf  (s, "[%.15s]", u->i_chead->c_name);
            sprintf  (r, "[%.15s]", u->i_ctail->c_name);
            v = u->i_chead; while (v != NULL) { ++x_fore; v = v->c_next; }
            v = u->i_ctail; while (v != NULL) { ++x_back; v = v->c_prev; }
         }
         snprintf (unit_answer, LEN_RECD, "FILE funcs  (%2d) : %-22.22s   %3dc %3df %3db   %-17.17s %s", i, t, u->i_ccount, x_fore, x_back, s, r);
      } else {
         snprintf (unit_answer, LEN_RECD, "FILE funcs  (%2d) : []                         -c   -f   -b   []                []", i);
      }
   }
   else if (strcmp (a_question, "footprint" )     == 0) {
      FILES_by_index     (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->i_name);
         snprintf (unit_answer, LEN_RECD, "FILE foot   (%2d) : %-22.22s   %7d text, %7d data, %7d bss", i, t, u->COUNT_TEXT, u->COUNT_DATA, u->COUNT_BSS);
      } else {
         snprintf (unit_answer, LEN_RECD, "FILE foot   (%2d) : []                             - text,       - data,       - bss", i);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
