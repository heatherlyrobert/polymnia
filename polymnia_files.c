/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_files__wipe   (tFILE *a_dst)
{
   if (a_dst == NULL)  return -1;
   /*---(master)------------*/
   a_dst->type     = '-';
   /*---(stats)-------------*/
   poly_cats_counts_clear (a_dst->counts);
   /*---(tags)--------------*/
   a_dst->proj     = NULL;
   a_dst->next     = NULL;
   a_dst->prev     = NULL;
   a_dst->head     = NULL;
   a_dst->tail     = NULL;
   a_dst->count    = 0;
   /*---(tags)--------------*/
   return 0;
}

tFILE*
poly_files_new           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFILE      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tFILE *) malloc (sizeof (tFILE));
      if (x_tries > 10)   break;
   }
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return NULL;
   }
   /*---(wipe clean)---------------------*/
   DEBUG_DATA   yLOG_note    ("wipe clean");
   poly_files__wipe (x_new);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return x_new;
}

char
poly_files_add          (tPROJ *a_proj, char *a_name, char a_type, tFILE **a_file)
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
   /*---(prepare)------------------------*/
   if (a_file != NULL)  *a_file = NULL;
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
   /*---(create cell)--------------------*/
   x_new = poly_files_new ();
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   strlcpy (x_new->name, a_name, LEN_NAME);
   x_new->type   = a_type;
   if (x_new->type == 'h')  x_type = 'H';
   if (strncmp (a_name, a_proj->name, strlen (a_proj->name)) == 0) x_prefix = 'Y';
   sprintf (x_new->sort, "%c%c%s", x_prefix, x_type, x_new->name);
   /*---(link to project)----------------*/
   rc = poly_proj_addfile (a_proj, x_new);
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
   if (a_file != NULL)  *a_file = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_files__del         (tFILE *a_file)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(beginning)----------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("->name"    , a_file->name);
   /*---(purge assigned tags)------------*/
   rc = poly_tags_purge_file (a_file);
   DEBUG_DATA   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(out of linked list)-------------*/
   DEBUG_DATA   yLOG_note    ("unlink");
   if (a_file->next != NULL)  a_file->next->prev = a_file->prev;
   else                       a_file->proj->tail = a_file->prev;
   if (a_file->prev != NULL)  a_file->prev->next = a_file->next;
   else                       a_file->proj->head = a_file->next;
   /*---(update count)-------------------*/
   --(a_file->proj->count);
   DEBUG_DATA   yLOG_value   ("count"     , a_file->proj->count);
   /*---(unhook from btree)--------------*/
   rc = poly_btree_unhook (&a_file->btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free main)----------------------*/
   DEBUG_DATA   yLOG_note    ("free");
   free (a_file);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_files_init         (void)
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
poly_files_purge_proj   (tPROJ *a_proj)
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
      rc = poly_tags_purge_file (x_file);
      rc = poly_files__del      (x_file);
      x_file = x_next;
   }
   /*---(check)--------------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_proj->count);
   --rce;  if (a_proj->count > 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_files_wrap         (void)
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
poly_files__swap        (tFILE *a_one, tFILE *a_two)
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
poly_files__dgnome      (tPROJ *x_proj)
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
      poly_files__swap (o->prev, o);
      /*---(next)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> make a list of input files --------------------------------*/
poly_files_review  (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   DIR        *x_dir       = NULL;          /* directory pointer              */
   tDIRENT    *x_file      = NULL;          /* directory entry pointer        */
   char        x_name      [LEN_NAME];      /* file name                      */
   int         x_len       =    0;
   char        x_type      =  '-';
   int         x_read      =    0;          /* count of entries reviewed      */
   int         x_good      =    0;          /* count of entries processed     */
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
      strlcpy (x_name, x_file->d_name, LEN_NAME);
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
      /*---(cut on suffix len)-----------*/
      DEBUG_INPT   yLOG_char    ("x_len - 2" , x_name [x_len - 2]);
      if (x_name [x_len - 2] != '.')  {
         DEBUG_INPT   yLOG_note    ("does not have a one-char suffix, SKIP");
         continue;
      }
      /*---(cut on suffix)---------------*/
      x_type = x_name [x_len - 1];
      DEBUG_INPT   yLOG_char    ("x_len - 1" , x_type);
      if (strchr ("ch", x_name [x_len - 1]) == NULL) {
         DEBUG_INPT   yLOG_note    ("not a c or h file, SKIP");
         continue;
      }
      /*---(filter unit test)*-----------*/
      if (x_len > 7 && strcmp ("_unit.c", x_name + x_len - 7) == 0) {
         DEBUG_INPT   yLOG_note    ("cut the unit testing code files, SKIP");
         continue;
      }
      /*---(save)------------------------*/
      poly_files_add (a_proj, x_name, x_type, NULL);
      ++x_good;
      DEBUG_INPT   yLOG_note    ("added to inventory");
      /*---(done)------------------------*/
   }
   DEBUG_INPT   yLOG_value   ("x_read"    , x_read);
   DEBUG_INPT   yLOG_value   ("x_good"    , x_good);
   /*---(close dir)----------------------*/
   DEBUG_INPT   yLOG_note    ("closing directory");
   rc = closedir (x_dir);
   DEBUG_INPT   yLOG_value   ("close_rc"  , rc);
   /*> printf ("   end-of-files\n\n\n");                                              <*/
   /*---(check count)--------------------*/
   DEBUG_INPT   yLOG_value   ("count"     , poly_btree_count (B_FILES));
   --rce;  if (poly_btree_count (B_FILES) <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare for use)----------------*/
   rc = poly_files__dgnome  (a_proj);
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

tFILE*  poly_files_search  (char *a_name) { return (tFILE *) poly_btree_search  (B_FILES, a_name); }
char    poly_files_list    (void)         { return poly_btree_list (B_FILES); }



/*====================------------------------------------====================*/
/*===----                         tag inventory                        ----===*/
/*====================------------------------------------====================*/
static void  o___TAGS____________o () { return; }

char
poly_files_addtag       (tFILE *a_file, tTAG *a_tag)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_file);
   if (a_file == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   DEBUG_DATA   yLOG_spoint  (a_tag);
   if (a_tag == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_spoint  (a_file->head);
   DEBUG_DATA   yLOG_spoint  (a_file->tail);
   if (a_file->head  == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      a_file->head  = a_file->tail  = a_tag;
   } else {
      DEBUG_DATA   yLOG_snote   ("append");
      a_tag->prev         = a_file->tail;
      a_file->tail->next = a_tag;
      a_file->tail        = a_tag;
   }
   /*---(tie tag back to file)-----------*/
   a_tag->file  = a_file;
   /*---(update count)-------------------*/
   ++a_file->count;
   DEBUG_DATA   yLOG_sint    (a_file->count);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_files_nexttag      (tFILE *a_file, tTAG **a_tag)
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
   DEBUG_DATA   yLOG_spoint  (a_tag);
   --rce;  if (a_tag == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_tag);
   /*---(first time)---------------------*/
   --rce;  if (*a_tag == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      if (a_file->head  == NULL) {
         DEBUG_DATA   yLOG_snote   ("head is null");
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      *a_tag = a_file->head ;
   }
   /*---(next time)----------------------*/
   else { 
      DEBUG_DATA   yLOG_snote   ("next");
      if ((*a_tag)->next == NULL) {
         DEBUG_DATA   yLOG_snote   ("next is null");
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      *a_tag = (*a_tag)->next;
   }
   DEBUG_DATA   yLOG_spoint  (*a_tag);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_files__unit     (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   tFILE      *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FILE unit        : file number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "FILE count       : %3d", poly_btree_count (B_FILES));
      return unit_answer;
   }
   if (strncmp (unit_answer, "FILE unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FILE unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "entry"     )     == 0) {
      u = (tFILE *) poly_btree_entry (B_FILES, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         snprintf (unit_answer, LEN_RECD, "FILE entry  (%2d) : %-22.22s %3d %3d %3d %3d %3d %3d", i, t, u->COUNT_LINES, u->COUNT_EMPTY, u->COUNT_DOCS, u->COUNT_DEBUG, u->COUNT_CODE, u->COUNT_SLOCL);
      } else {
         snprintf (unit_answer, LEN_RECD, "FILE entry  (%2d) : %-22.22s %3d %3d %3d %3d %3d %3d", i, t, 0, 0, 0, 0, 0, 0);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


