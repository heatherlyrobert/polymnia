/*============================----beg-of-source---============================*/
#include  "polymnia.h"



tPROJ      *g_head      = NULL;
tPROJ      *g_tail      = NULL;
int         g_count     =    0;;



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_proj_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = poly_btree_init (B_PROJ);
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
poly_proj_wrap          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(walk through list)--------------*/
   /*> rc = poly_btree_purge (B_PROJ);                                                <* 
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
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_proj__wipe    (tPROJ *a_dst)
{
   if (a_dst == NULL)  return -1;
   /*---(master)------------*/
   a_dst->name     [0] = '\0';
   a_dst->focus    [0] = '\0';
   a_dst->niche    [0] = '\0';
   a_dst->subject  [0] = '\0';
   a_dst->purpose  [0] = '\0';
   /*---(greek)-------------*/
   a_dst->namesake [0] = '\0';
   a_dst->heritage [0] = '\0';
   a_dst->imagery  [0] = '\0';
   a_dst->reason   [0] = '\0';
   a_dst->oneline  [0] = '\0';
   /*---(location)----------*/
   a_dst->progname [0] = '\0';
   a_dst->homedir  [0] = '\0';
   a_dst->fullpath [0] = '\0';
   a_dst->suffix   [0] = '\0';
   a_dst->content  [0] = '\0';
   /*---(chars)-------------*/
   a_dst->systems  [0] = '\0';
   a_dst->language [0] = '\0';
   a_dst->codesize [0] = '\0';
   /*---(when)--------------*/
   a_dst->author   [0] = '\0';
   a_dst->created  [0] = '\0';
   a_dst->depends  [0] = '\0';
   /*---(versioning)--------*/
   a_dst->vermajor [0] = '\0';
   a_dst->verminor [0] = '\0';
   a_dst->vernum   [0] = '\0';
   a_dst->vertxt   [0] = '\0';
   /*---(stats)-------------*/
   a_dst->funcs     = 0;
   poly_cats_counts_clear (a_dst->counts);
   /*---(files)-------------*/
   a_dst->head      = NULL;
   a_dst->tail      = NULL;
   a_dst->count     = 0;
   /*---(tags)--------------*/
   return 0;
}

tPROJ*
poly_proj_new            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tPROJ      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tPROJ *) malloc (sizeof (tPROJ));
      if (x_tries > 10)   break;
   }
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return NULL;
   }
   /*---(wipe clean)---------------------*/
   DEBUG_DATA   yLOG_note    ("wipe clean");
   poly_proj__wipe (x_new);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return x_new;
}

char
poly_proj_add            (char *a_name, char *a_home, tPROJ **a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_new       = NULL;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   DEBUG_DATA   yLOG_point   ("a_home"    , a_home);
   --rce;  if (a_home == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_home"    , a_home);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   DEBUG_DATA   yLOG_point   ("*a_proj"   , *a_proj);
   --rce;  if (a_proj != NULL) {
      if (*a_proj != NULL) {
         DEBUG_DATA   yLOG_note    ("already set to a particular project");
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(create project)-----------------*/
   x_new = poly_proj_new ();
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   strlcpy (x_new->name    , a_name, LEN_TITLE);
   strlcpy (x_new->homedir , a_home, LEN_HUND);
   /*---(into btree)---------------------*/
   rc = poly_btree_hook (B_PROJ, x_new, x_new->name, &x_new->btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   if (a_proj != NULL)  *a_proj = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_proj_here           (tPROJ **a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   char       *p           = NULL;
   char       *q           = NULL;
   int         x_len       =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_proj"     , a_proj);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("*a_proj"   , *a_proj);
   --rce;  if (a_proj != NULL && *a_proj != NULL) {
      DEBUG_DATA   yLOG_note    ("already set to a particular project");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create project)-----------------*/
   x_proj = poly_proj_new ();
   DEBUG_DATA   yLOG_point   ("x_proj"     , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get the home)-------------------*/
   p = getcwd (x_proj->homedir, LEN_HUND);
   DEBUG_DATA   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      free (x_proj);
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("home"      , x_proj->homedir);
   x_len = strlen (x_proj->homedir);
   DEBUG_DATA   yLOG_value   ("x_len"     , x_len);
   /*---(check valid areas)--------------*/
   --rce; if (x_len > 16 && strncmp ("/home/system/"         , x_proj->homedir, 13) == 0) {
      ;;
   } else if (x_len > 16 && strncmp ("/home/monkey/"         , x_proj->homedir, 13) == 0) {
      ;;
   } else if (x_len > 25 && strncmp ("/home/member/p_gvskav/", x_proj->homedir, 22) == 0) {
      ;;
   } else {
      free (x_proj);
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get the name)-------------------*/
   p = strrchr (x_proj->homedir, '/');
   DEBUG_DATA   yLOG_point   ("strrchr"   , p);
   --rce;  if (p == NULL) {
      free (x_proj);
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   ++p;
   q = strchr  (p, '.');
   DEBUG_DATA   yLOG_point   ("strchr"    , q);
   if (q == NULL)  x_len = strlen (p);
   else            x_len = q - p + 1;
   DEBUG_DATA   yLOG_value   ("x_len"     , x_len);
   strlcpy (x_proj->name, p, x_len);
   DEBUG_DATA   yLOG_info    ("name"      , x_proj->name);
   /*---(into btree)---------------------*/
   rc = poly_btree_hook (B_PROJ, x_proj, x_proj->name, &x_proj->btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      free (x_proj);
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   if (a_proj != NULL)  *a_proj = x_proj;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_proj_prepare       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(prepare for use)----------------*/
   rc = poly_btree_dgnome   (B_PROJ);
   DEBUG_SORT   yLOG_value   ("dgnome"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_btree_build (B_PROJ);
   DEBUG_SORT   yLOG_value   ("build"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_proj_del          (tPROJ **a_proj)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   /*---(beginning)----------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_proj = *a_proj;
   DEBUG_DATA   yLOG_point   ("x_proj"    , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("->name"    , x_proj->name);
   /*---(purge assigned files)-----------*/
   rc = poly_files_purge_proj (x_proj);
   DEBUG_DATA   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook from btree)--------------*/
   rc = poly_btree_unhook (&x_proj->btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free main)----------------------*/
   DEBUG_DATA   yLOG_note    ("free");
   free (x_proj);
   *a_proj = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_proj_purge         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   tPROJ      *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(walk-through)-------------------*/
   DEBUG_DATA   yLOG_value   ("count"     , poly_btree_count (B_PROJ));
   x_proj = (tPROJ * )poly_btree_first (B_PROJ);
   while (x_proj != NULL) {
      x_next = (tPROJ *) poly_btree_next  (B_PROJ);
      DEBUG_DATA   yLOG_point   ("x_proj"    , x_proj);
      DEBUG_DATA   yLOG_info    ("->name"    , x_proj->name);
      rc = poly_files_purge_proj (x_proj);
      rc = poly_proj_del         (&x_proj);
      x_proj = x_next;
   }
   /*---(check)--------------------------*/
   DEBUG_DATA   yLOG_value   ("count"     , poly_btree_count (B_PROJ));
   --rce;  if (poly_btree_count (B_PROJ) > 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        searching                             ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

tPROJ*  poly_proj_search  (char *a_name) { return (tPROJ *) poly_btree_search  (B_PROJ, a_name); }
char    poly_proj_list    (void)         { return poly_btree_list (B_PROJ); }



/*====================------------------------------------====================*/
/*===----                      sequential access                       ----===*/
/*====================------------------------------------====================*/
static void  o___SEQUENCIAL______o () { return; }

char
poly_proj_nextfile      (tPROJ *a_proj, tFILE **a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_file);
   /*---(first time)---------------------*/
   --rce;  if (*a_file == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      if (a_proj->head  == NULL) {
         DEBUG_DATA   yLOG_snote   ("head is null");
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      *a_file = a_proj->head;
   }
   /*---(next time)----------------------*/
   else { 
      DEBUG_DATA   yLOG_snote   ("next");
      if ((*a_file)->next == NULL) {
         DEBUG_DATA   yLOG_snote   ("next is null");
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      *a_file = (*a_file)->next;
   }
   DEBUG_DATA   yLOG_spoint  (*a_file);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       file handling                          ----===*/
/*====================------------------------------------====================*/
static void  o___FILES___________o () { return; }

int
poly_proj_file_count    (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_proj);
   if (a_proj == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   /*---(complete)------------------------------*/
   c = a_proj->count;
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return c;
}

char
poly_proj_file_hook     (tPROJ *a_proj, tFILE *a_file)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_proj);
   if (a_proj == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   DEBUG_DATA   yLOG_spoint  (a_file);
   if (a_file == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_spoint  (a_proj->head);
   DEBUG_DATA   yLOG_spoint  (a_proj->tail);
   if (a_proj->head == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      a_proj->head = a_proj->tail = a_file;
   } else {
      DEBUG_DATA   yLOG_snote   ("append");
      a_file->prev        = a_proj->tail;
      a_proj->tail->next  = a_file;
      a_proj->tail        = a_file;
   }
   /*---(tie file back to proj)----------*/
   a_file->proj  = a_proj;
   /*---(update count)-------------------*/
   ++a_proj->count;
   ++a_proj->COUNT_FILES;
   DEBUG_DATA   yLOG_sint    (a_proj->count);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_proj_file_unhook   (tFILE *a_file)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_file);
   if (a_file == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   /*---(out of linked list)-------------*/
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
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_proj_nexttag      (tPROJ *a_proj, tFILE **a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_file);
   /*---(first time)---------------------*/
   --rce;  if (*a_file == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      if (a_proj->head == NULL) {
         DEBUG_DATA   yLOG_snote   ("head is null");
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      *a_file = a_proj->head;
   }
   /*---(next time)----------------------*/
   else { 
      DEBUG_DATA   yLOG_snote   ("next");
      if ((*a_file)->next  == NULL) {
         DEBUG_DATA   yLOG_snote   ("next is null");
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      *a_file = (*a_file)->next;
   }
   DEBUG_DATA   yLOG_spoint  (*a_file);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         system update                        ----===*/
/*====================------------------------------------====================*/
static void  o___SYSTEM__________o () { return; }

char         /*--> update all projects in a directory ------------------------*/
poly_proj_system        (char *a_path)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   DIR        *x_dir       = NULL;          /* directory pointer              */
   tDIRENT    *x_file      = NULL;          /* directory entry pointer        */
   char        x_base      [LEN_HUND];      /* file name                      */
   char        x_name      [LEN_HUND];      /* file name                      */
   int         x_len       =    0;
   char        x_type      =  '-';
   int         x_read      =    0;          /* count of entries reviewed      */
   int         x_good      =    0;          /* count of entries processed     */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open dir)-----------------------*/
   DEBUG_INPT   yLOG_point   ("a_path"     , a_path);
   --rce;  if (a_path == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_info    ("a_path"     , a_path);
   strlcpy  (x_base, a_path, LEN_HUND);
   x_dir = opendir(a_path);
   DEBUG_INPT   yLOG_point   ("x_dir"      , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_note    ("openned successfully");
   /*---(process entries)----------------*/
   DEBUG_INPT   yLOG_note    ("processing entries");
   while (1) {
      PROG_prepare ();
      /*---(read a directory entry)------*/
      x_file = readdir (x_dir);
      DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
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
      /*---(move)------------------------*/
      sprintf (x_name, "%s/%s/", x_base, x_file->d_name);
      printf  ("%s\n", x_name);
      DEBUG_INPT   yLOG_info    ("x_name"    , x_name);
      rc = chdir (x_name);
      DEBUG_INPT   yLOG_value   ("chdir"     , rc);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("not a directory/no access, SKIP");
         continue;
      }
      /*---(update)----------------------*/
      rc = poly_action_update ();
      DEBUG_INPT   yLOG_value   ("update"    , rc);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("could not update project");
      }
      /*---(clean up)--------------------*/
      rc = poly_btree_purge_all ();
      DEBUG_INPT   yLOG_value   ("purge"     , rc);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("could not purge btree");
      }
      /*---(done)------------------------*/
   }
   /*---(close dir)----------------------*/
   DEBUG_INPT   yLOG_note    ("closing directory");
   rc = closedir (x_dir);
   DEBUG_INPT   yLOG_value   ("close_rc"  , rc);
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_proj__unit     (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD]  = "[]";
   char        s           [LEN_RECD]  = "[]";
   char        r           [LEN_RECD]  = "[]";
   tPROJ      *u           = NULL;
   tFILE      *v           = NULL;
   int         x_fore      =    0;
   int         x_back      =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "PROJ unit        : index number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "PROJ count       : %3d", poly_btree_count (B_PROJ));
      return unit_answer;
   }
   if (strncmp (unit_answer, "PROJ unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "PROJ unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "stats"     )     == 0) {
      u = (tPROJ *) poly_btree_entry (B_PROJ, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         snprintf (unit_answer, LEN_RECD, "PROJ stats  (%2d) : %-22.22s   %3d %3d   %3d %3d %3d %3d %3d %3d", i, t, u->COUNT_FILES, u->COUNT_FUNCS, u->COUNT_LINES, u->COUNT_EMPTY, u->COUNT_DOCS, u->COUNT_DEBUG, u->COUNT_CODE, u->COUNT_SLOCL);
      } else {
         snprintf (unit_answer, LEN_RECD, "PROJ stats  (%2d) : %-22.22s     -   -     -   -   -   -   -   -", i, t);
      }
   }
   else if (strcmp (a_question, "files"     )     == 0) {
      u = (tPROJ *) poly_btree_entry (B_PROJ, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->head != NULL) {
            sprintf  (s, "[%.15s]", u->head->name);
            sprintf  (r, "[%.15s]", u->tail->name);
            v = u->head; while (v != NULL) { ++x_fore; v = v->next; }
            v = u->tail; while (v != NULL) { ++x_back; v = v->prev; }
         }
         snprintf (unit_answer, LEN_RECD, "PROJ files  (%2d) : %-22.22s   %3dc %3df %3db   %-17.17s %s", i, t, u->count, x_fore, x_back, s, r);
      } else {
         snprintf (unit_answer, LEN_RECD, "PROJ files  (%2d) : []                         -c   -f   -b   []                []", i, t);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


