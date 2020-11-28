/*============================----beg-of-source---============================*/
#include  "polymnia.h"



static char s_print     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                     small supporters                         ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_file__wipe    (tFILE *a_dst)
{
   if (a_dst == NULL)  return -1;
   DEBUG_DATA   yLOG_snote   ("wipe");
   /*---(master)------------*/
   a_dst->type     = '-';
   a_dst->name [0] = '\0';
   a_dst->sort [0] = '\0';
   /*---(stats)-------------*/
   poly_cats_counts_clear (a_dst->counts);
   /*---(tags)--------------*/
   a_dst->proj     = NULL;
   a_dst->prev     = NULL;
   a_dst->next     = NULL;
   a_dst->head     = NULL;
   a_dst->tail     = NULL;
   a_dst->count    = 0;
   a_dst->btree    = NULL;
   /*---(tags)--------------*/
   return 1;
}

char*
poly_file__unit_memory  (tFILE *a_file)
{
   /*---(master)-------------------------*/
   strlcpy (s_print, "["  , LEN_RECD);
   poly_shared__check_char (s_print, a_file->type);
   poly_shared__check_str  (s_print, a_file->name);
   poly_shared__check_str  (s_print, a_file->sort);
   poly_shared__spacer     (s_print);
   /*---(project/file)-------------------*/
   poly_shared__check_ptr  (s_print, a_file->proj);
   poly_shared__check_ptr  (s_print, a_file->prev);
   poly_shared__check_ptr  (s_print, a_file->next);
   poly_shared__spacer     (s_print);
   /*---(functions)----------------------*/
   poly_shared__check_ptr  (s_print, a_file->head);
   poly_shared__check_ptr  (s_print, a_file->tail);
   poly_shared__check_num  (s_print, a_file->count);
   poly_shared__spacer     (s_print);
   /*---(btree)--------------------------*/
   poly_shared__check_ptr  (s_print, a_file->btree);
   strlcat (s_print, "]" , LEN_RECD);
   /*---(complete)-----------------------*/
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char poly_file__new  (tFILE **a_new) { return poly_shared_new  ("file", sizeof (tFILE), a_new, NULL, '-', poly_file__wipe); }
char poly_file_force (tFILE **a_new) { return poly_shared_new  ("file", sizeof (tFILE), a_new, NULL, 'y', poly_file__wipe); }
char poly_file__free (tFILE **a_old) { return poly_shared_free ("file", a_old, NULL); }



/*====================------------------------------------====================*/
/*===----                   hooking and unhooking                      ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

char
poly_file_hook          (tPROJ *a_proj, tFILE *a_file)
{
   char        rce         =  -10;
   /*---(header)-------------------------*/
   /*> DEBUG_DATA   yLOG_senter  (__FUNCTION__);                                      <*/
   DEBUG_DATA   yLOG_enter  (__FUNCTION__);
   /*---(defense)------------------------*/
   /*> DEBUG_DATA   yLOG_spoint  (a_proj);                                            <*/
   DEBUG_DATA   yLOG_point  ("a_proj", a_proj);
   --rce;  if (a_proj == NULL) {
      /*> DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);                              <*/
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> DEBUG_DATA   yLOG_spoint  (a_file);                                            <*/
   DEBUG_DATA   yLOG_point  ("a_file", a_file);
   --rce;  if (a_file == NULL) {
      /*> DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);                              <*/
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> DEBUG_DATA   yLOG_spoint  (a_file->proj);                                      <*/
   DEBUG_DATA   yLOG_point  ("->proj", a_file->proj);
   --rce;  if (a_file->proj != NULL) {
      /*> DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);                              <*/
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> DEBUG_DATA   yLOG_snote   (a_file->name);                                      <*/
   DEBUG_DATA   yLOG_note   (a_file->name);
   /*---(into linked list)---------------*/
   /*> DEBUG_DATA   yLOG_sint    (a_file->proj->count);                               <* 
    *> DEBUG_DATA   yLOG_spoint  (a_proj->head);                                      <* 
    *> DEBUG_DATA   yLOG_spoint  (a_proj->tail);                                      <*/
   DEBUG_DATA   yLOG_value   ("count", a_proj->count);
   DEBUG_DATA   yLOG_point  ("head" , a_proj->head);
   DEBUG_DATA   yLOG_point  ("tail", a_proj->tail);
   if (a_proj->head == NULL) {
      /*> DEBUG_DATA   yLOG_snote   ("first");                                        <*/
      DEBUG_DATA   yLOG_note   ("first");
      a_proj->head = a_proj->tail = a_file;
   } else {
      /*> DEBUG_DATA   yLOG_snote   ("append");                                       <*/
      DEBUG_DATA   yLOG_note   ("append");
      a_file->prev        = a_proj->tail;
      a_proj->tail->next  = a_file;
      a_proj->tail        = a_file;
   }
   /*---(tie file back to proj)----------*/
   a_file->proj  = a_proj;
   /*---(update count)-------------------*/
   ++a_proj->count;
   ++a_proj->COUNT_FILES;
   /*> DEBUG_DATA   yLOG_sint    (a_proj->count);                                     <*/
   DEBUG_DATA   yLOG_value   ("count", a_proj->count);
   /*---(complete)------------------------------*/
   /*> DEBUG_DATA   yLOG_sexit   (__FUNCTION__);                                      <*/
   DEBUG_DATA   yLOG_exit   (__FUNCTION__);
   return 0;
}

char
poly_file_unhook        (tFILE *a_file)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_file);
   if (a_file == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   DEBUG_DATA   yLOG_spoint  (a_file->proj);
   if (a_file->proj == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -2);
      return -2;
   }
   DEBUG_DATA   yLOG_snote   (a_file->name);
   /*---(out of linked list)-------------*/
   DEBUG_DATA   yLOG_sint    (a_file->proj->count);
   DEBUG_DATA   yLOG_spoint  (a_file->proj->head);
   DEBUG_DATA   yLOG_spoint  (a_file->proj->tail);
   DEBUG_DATA   yLOG_snote   ("unlink");
   if (a_file->next != NULL)  a_file->next->prev = a_file->prev;
   else                       a_file->proj->tail = a_file->prev;
   if (a_file->prev != NULL)  a_file->prev->next = a_file->next;
   else                       a_file->proj->head = a_file->next;
   /*---(update count)-------------------*/
   --(a_file->proj->count);
   --(a_file->proj->COUNT_FILES);
   DEBUG_DATA   yLOG_sint    (a_file->proj->count);
   /*---(ground pointers)----------------*/
   a_file->proj = NULL;
   a_file->prev = NULL;
   a_file->next = NULL;
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_file_add           (tPROJ *a_proj, char *a_name, char a_type, tFILE **a_file)
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
   poly_file__new (&x_new);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   strlcpy (x_new->name, a_name, LEN_TITLE);
   x_new->type   = a_type;
   /*---(standard names to front)--------*/
   if (strncmp (a_name, a_proj->name, strlen (a_proj->name)) == 0) x_prefix = 'Y';
   /*---(headers to front)---------------*/
   if (x_new->type == 'h')  x_type = 'H';
   /*---(units come last)----------------*/
   if (strstr (x_new->name, ".unit")       != NULL)   x_prefix = 'Z';
   /*---(master to top of units)---------*/
   if (strcmp (x_new->name, "master.unit") == 0)      x_type   = 'H';
   /*---(link to project)----------------*/
   sprintf (x_new->sort, "%c%c%s", x_prefix, x_type, x_new->name);
   rc = poly_file_hook (a_proj, x_new);
   DEBUG_DATA   yLOG_value   ("addfile"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(into btree)---------------------*/
   rc = poly_btree_hook (B_FILES, x_new, x_new->name, &x_new->btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
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
poly_file_remove        (tFILE **a_file)
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
   DEBUG_DATA   yLOG_info    ("->name"    , x_file->name);
   /*---(purge assigned tags)------------*/
   rc = poly_func_purge (x_file, '-');
   DEBUG_DATA   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(out of linked list)-------------*/
   rc = poly_file_unhook (x_file);
   DEBUG_DATA   yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook from btree)--------------*/
   rc = poly_btree_unhook (&x_file->btree);
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
poly_file_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = poly_btree_init (B_FILES);
   DEBUG_PROG   yLOG_value   ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_file_purge         (tPROJ *a_proj, char a_update)
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
   DEBUG_DATA   yLOG_value   ("->count"   , a_proj->count);
   x_file = a_proj->head;
   while (x_file != NULL) {
      x_next = x_file->next;
      DEBUG_DATA   yLOG_point   ("x_file"    , x_file);
      DEBUG_DATA   yLOG_info    ("->name"    , x_file->name);
      rc = poly_file_remove  (&x_file);
      x_file = x_next;
   }
   /*---(check)--------------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_proj->count);
   --rce;  if (a_proj->count > 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update btrees)------------------*/
   --rce;  if (a_update == 'y') {
      rc = poly_btree_prepare (B_FILES);
      if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = poly_btree_prepare (B_FUNCS);
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
poly_file_wrap          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(walk through list)--------------*/
   /*> rc = poly_btree_purge (B_FILES);                                               <* 
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
poly_file__swap        (tFILE *a_one, tFILE *a_two)
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
   if (a_two->next != NULL)   a_two->next->prev = a_two->prev;
   else                       a_two->proj->tail = a_two->prev;
   if (a_two->prev != NULL)   a_two->prev->next = a_two->next;
   else                       a_two->proj->head = a_two->next;
   /*---(insert before one)--------------*/
   DEBUG_SORT   yLOG_snote   ("insert");
   if (a_one->prev != NULL)   a_one->prev->next = a_two;
   else                       a_one->proj->head = a_two;
   a_two->prev = a_one->prev;
   a_two->next = a_one;
   a_one->prev = a_two;
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_file__dgnome       (tPROJ *x_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFILE      *o           = NULL;          /* origin point                   */
   int         x_match     =    0;
   char        x_flag      =  '-';
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   o = x_proj->head;
   /*---(do the gnome walk)--------------*/
   while (o != NULL) {
      /*---(beginning)-------------------*/
      if (o == x_proj->head) {
         DEBUG_SORT   yLOG_note    ("bounce off beginning");
         o = o->next;
         continue;
      }
      /*---(compare)---------------------*/
      x_match = strcmp (o->prev->sort, o->sort);
      x_flag  = (x_match <= 0) ? 'y' : '#';
      DEBUG_SORT   yLOG_complex ("compare"   , "%-10p (%-30.30s) v %-10p (%-30.30s)   %c %4d", o->prev, o->prev->sort, o, o->sort, x_flag, x_match);
      if (x_match <= 0) {
         DEBUG_SORT   yLOG_note    ("move forward");
         o = o->next;
         continue;
      }
      /*---(swap)------------------------*/
      DEBUG_SORT   yLOG_note    ("swap and move back");
      poly_file__swap (o->prev, o);
      /*---(next)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> make a list of input files --------------------------------*/
poly_file_review        (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   DIR        *x_dir       = NULL;          /* directory pointer              */
   tDIRENT    *x_file      = NULL;          /* directory entry pointer        */
   char        x_name      [LEN_TITLE];      /* file name                      */
   int         x_len       =    0;
   char        x_point     =  '-';
   char        x_type      =  '-';
   int         x_read      =    0;          /* count of entries reviewed      */
   int         x_good      =    0;          /* count of entries processed     */
   tFILE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
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
      strlcpy (x_name, x_file->d_name, LEN_TITLE);
      DEBUG_INPT   yLOG_info    ("x_name"    , x_name);
      x_len = strlen (x_name);
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      if (x_name [0] == '.')  {
         DEBUG_INPT   yLOG_note    ("hidden, SKIP");
         continue;
      }
      /*---(cut too short)---------------*/
      if (x_len <  3)  {
         DEBUG_INPT   yLOG_note    ("name too short, SKIP");
         continue;
      }
      /*---(cut too long)----------------*/
      if (x_len > 50) {
         DEBUG_INPT   yLOG_note    ("crazy long name, SKIP");
         continue;
      }
      /*---(one character suffixes)------*/
      x_point = x_name [x_len - 2];
      DEBUG_INPT   yLOG_char    ("x_point"   , x_point);
      if (x_point == '.') {
         x_type = x_name [x_len - 1];
         DEBUG_INPT   yLOG_char    ("x_type"    , x_type);
         if (strchr ("ch", x_type) == NULL) {
            DEBUG_INPT   yLOG_note    ("not a c or h file, SKIP");
            continue;
         }
         if (x_len > 7 && strcmp ("_unit.c", x_name + x_len - 7) == 0) {
            DEBUG_INPT   yLOG_note    ("cut the unit testing code files, SKIP");
            continue;
         }
      }
      /*---(unit tests)------------------*/
      else if (x_len >= 6) {
         x_point = x_name [x_len - 5];
         DEBUG_INPT   yLOG_char    ("x_point"   , x_point);
         if (x_point != '.') {
            DEBUG_INPT   yLOG_note    ("not the right length suffix, SKIP");
            continue;
         }
         if (strcmp ("unit", x_name + x_len - 4) != 0) {
            DEBUG_INPT   yLOG_note    ("not a unit suffix, SKIP");
            continue;
         }
         /*---(quick calloff)------------------*/
         DEBUG_INPT   yLOG_char    ("g_unit"    , my.g_unit);
         if (my.g_unit != 'y') {
            DEBUG_INPT   yLOG_note    ("called with --nounit");
            continue;
         }
         x_type = 'u';
      }
      /*---(all else)--------------------*/
      else {
         DEBUG_INPT   yLOG_note    ("bad suffix, SKIP");
         continue;
      }
      /*---(save)------------------------*/
      x_curr = NULL;
      poly_file_add (a_proj, x_name, x_type, &x_curr);
      ++x_good;
      DEBUG_INPT   yLOG_note    ("added to inventory");
      /*---(check globals)---------------*/
      if (x_type == 'h')  poly_vars_inventory (x_curr);
      /*---(done)------------------------*/
   }
   DEBUG_INPT   yLOG_value   ("x_read"    , x_read);
   DEBUG_INPT   yLOG_value   ("x_good"    , x_good);
   /*---(close dir)----------------------*/
   DEBUG_INPT   yLOG_note    ("closing directory");
   rc = closedir (x_dir);
   DEBUG_INPT   yLOG_value   ("close_rc"  , rc);
   /*---(check count)--------------------*/
   DEBUG_INPT   yLOG_value   ("count"     , poly_btree_count (B_FILES));
   --rce;  if (poly_btree_count (B_FILES) <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare for use)----------------*/
   rc = poly_file__dgnome  (a_proj);
   DEBUG_SORT   yLOG_value   ("files sort" , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_btree_dgnome   (B_FILES);
   DEBUG_SORT   yLOG_value   ("dgnome"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_btree_build (B_FILES);
   DEBUG_SORT   yLOG_value   ("build"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> poly_extern_list ();                                                           <*/
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        searching                             ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char
poly_file_by_name       (uchar *a_name, tFILE **a_file)
{
   if (a_file == NULL)   return -1;
   *a_file = (tFILE *) poly_btree_search  (B_FILES, a_name);
   if (*a_file == NULL)  return -2;
   return 0;
}

char
poly_file_by_index      (int n, tFILE **a_file)
{
   if (a_file == NULL)   return -1;
   *a_file = (tFILE *) poly_btree_entry (B_FILES, n);
   if (*a_file == NULL)  return -2;
   return 0;
}

char
poly_file_cursor        (char a_dir, tFILE **a_file)
{
   return poly_btree_cursor  (B_FILES, a_dir, a_file);
}



/*====================------------------------------------====================*/
/*===----                   size and memory footprint                  ----===*/
/*====================------------------------------------====================*/
static void  o___FOOTPRINT_______o () { return; }

char
poly_file_footprint    (tFILE *a_file)
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
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->name);
   DEBUG_INPT   yLOG_char    ("type"      , a_file->type);
   --rce;  if (a_file->type != 'c') {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(defaults)-----------------------*/
   a_file->COUNT_TEXT = 0;
   a_file->COUNT_DATA = 0;
   a_file->COUNT_BSS  = 0;
   /*---(prepare name)--------------------------*/
   strlcpy (x_name, a_file->name, LEN_TITLE);
   x_len = strlen (x_name);
   x_name [--x_len] = 'o';
   x_name [++x_len] = 's';
   x_name [++x_len] = '\0';
   DEBUG_INPT   yLOG_info    ("x_name"    , x_name);
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
   a_file->proj->COUNT_TEXT += a_file->COUNT_TEXT = atoi (p);
   p = strtok_r (NULL  , " ", &r);
   a_file->proj->COUNT_DATA += a_file->COUNT_DATA = atoi (p);
   p = strtok_r (NULL  , " ", &r);
   a_file->proj->COUNT_BSS  += a_file->COUNT_BSS  = atoi (p);
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

char
poly_file_line          (tFILE *a_file, char a_style, int a, int b, char a_print)
{
   /*  n  name    , just the name
    *  s  stats   , short count, name, plus statistics
    *  a  all     , long count, name, plus statistics
    *
    */
   char       *x_count     = "fil";
   char       *x_all       = "prj § fil § fnc";
   char       *x_name      = "---name------------------";
   char       *x_stats     = "files § funcs § --lines § --empty § ---docs § --debug § ---code § --slocl";
   char        t           [LEN_RECD] = "";
   char        x_type      = '-';
   /*---(prepare)------------------------*/
   strlcpy (s_print, "", LEN_RECD);
   if (a_file == NULL)  x_type = 'h';
   /*---(index)--------------------------*/
   if (strchr ("aA", a_style) != NULL) {
      switch (x_type) {
      case '-' :   sprintf (t, "%-3d § %-3d § -   § ", a + 1, b + 1);  break;
      case 'h' :   sprintf (t, "%s § ", x_all);                        break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   if (strchr ("sL", a_style) != NULL) {
      switch (x_type) {
      case '-' :   sprintf (t, "%-3d § ", b + 1);  break;
      case 'h' :   sprintf (t, "%s § ", x_count);              break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(name)---------------------------*/
   switch (x_type) {
   case '-' :   sprintf (t, "%-25.25s § ", a_file->name);      break;
   case 'h' :   sprintf (t, "%s § "      , x_name);            break;
   }
   strlcat (s_print, t, LEN_RECD);
   /*---(statistics)---------------------*/
   if (strchr ("sLaA", a_style) != NULL) {
      switch (x_type) {
      case '-' : sprintf (t, "    - § %5d § %7d § %7d § %7d § %7d § %7d § %7d § ",
                       a_file->COUNT_FUNCS,
                       a_file->COUNT_LINES, a_file->COUNT_EMPTY,
                       a_file->COUNT_DOCS , a_file->COUNT_DEBUG,
                       a_file->COUNT_CODE , a_file->COUNT_SLOCL);
                 break;
      case 'h' : sprintf (t, "%-s § "   , x_stats);            break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(newline)------------------------*/
   if (a_print == 'y')  printf ("%s\n", s_print);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_file__unit         (char *a_question, int i)
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
      snprintf (unit_answer, LEN_RECD, "FILE count       : %3d", poly_btree_count (B_FILES));
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
      poly_file_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         snprintf (unit_answer, LEN_RECD, "FILE stats  (%2d) : %-22.22s     · %3d %3d   %3d %3d %3d %3d %3d %3d", i, t, u->COUNT_FUNCS, u->COUNT_YLIBS, u->COUNT_LINES, u->COUNT_EMPTY, u->COUNT_DOCS, u->COUNT_DEBUG, u->COUNT_CODE, u->COUNT_SLOCL);
      } else {
         snprintf (unit_answer, LEN_RECD, "FILE stats  (%2d) : []                         ·   -   -     -   -   -   -   -   -", i);
      }
   }
   else if (strcmp (a_question, "funcs"     )     == 0) {
      poly_file_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->head != NULL) {
            sprintf  (s, "[%.15s]", u->head->name);
            sprintf  (r, "[%.15s]", u->tail->name);
            v = u->head; while (v != NULL) { ++x_fore; v = v->next; }
            v = u->tail; while (v != NULL) { ++x_back; v = v->prev; }
         }
         snprintf (unit_answer, LEN_RECD, "FILE funcs  (%2d) : %-22.22s   %3dc %3df %3db   %-17.17s %s", i, t, u->count, x_fore, x_back, s, r);
      } else {
         snprintf (unit_answer, LEN_RECD, "FILE funcs  (%2d) : []                         -c   -f   -b   []                []", i);
      }
   }
   else if (strcmp (a_question, "footprint" )     == 0) {
      poly_file_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         snprintf (unit_answer, LEN_RECD, "FILE foot   (%2d) : %-22.22s   %7d text, %7d data, %7d bss", i, t, u->COUNT_TEXT, u->COUNT_DATA, u->COUNT_BSS);
      } else {
         snprintf (unit_answer, LEN_RECD, "FILE foot   (%2d) : []                             - text,       - data,       - bss", i);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
