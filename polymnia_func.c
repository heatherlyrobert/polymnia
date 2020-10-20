/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*====================------------------------------------====================*/
/*===----                     small supporters                         ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_func__wipe         (tFUNC *a_dst)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(master)-------------------------*/
   a_dst->type        = '-';
   a_dst->name [0]    = '\0';
   a_dst->line        = -1;
   a_dst->hint [0]    = '\0';
   a_dst->purpose [0] = '\0';
   a_dst->ready       = '?';
   /*---(pointers)-----------------------*/
   a_dst->file        = NULL;
   a_dst->prev        = NULL;
   a_dst->next        = NULL;
   a_dst->work        = NULL;
   a_dst->head        = NULL;
   a_dst->tail        = NULL;
   a_dst->count       = 0;
   /*---(clear counts/stats)-------------*/
   poly_cats_counts_clear (a_dst->counts);
   poly_cats_stats_clear  (a_dst->stats);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_func__wipe_work    (tWORK *a_dst)
{
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(positioning)--------------------*/
   a_dst->beg      = -1;
   a_dst->end      = -1;
   for (i = 0; i < MAX_TEMPS; ++i)  a_dst->temp [i] = 0;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_func__hint         (int n, char *a_label)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char       *x_1st       = "abcdefghijklmnopqrstuvwxyz";
   int         x_1len      = strlen (x_1st);
   char       *x_2nd       = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int         x_2len      = strlen (x_2nd);
   --rce;  if (a_label == NULL)  return rce;
   strlcpy (a_label, "��", LEN_LABEL);
   --rce;  if (n < 0)            return rce;
   --rce;  if (n > 1351)         return rce;
   a_label [0] = x_1st [n / x_2len];
   a_label [1] = x_2nd [n % x_2len];
   a_label [2] = '\0';
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    memory allocation                         ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
poly_func_new           (tFUNC **a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFUNC      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*a_func"   , *a_func);
   --rce;  if (*a_func != NULL) {
      DEBUG_DATA   yLOG_note    ("already set to a particular function");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   *a_func = NULL;
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tFUNC *) malloc (sizeof (tFUNC));
      if (x_tries > 3)   break;
   }
   DEBUG_DATA   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear and return)---------------*/
   poly_func__wipe (x_new);
   *a_func = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_func__new_work     (tWORK **a_work)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tWORK      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("a_work"    , a_work);
   --rce;  if (a_work == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*a_work"   , *a_work);
   --rce;  if (*a_work != NULL) {
      DEBUG_DATA   yLOG_note    ("already set to a particular work area");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   *a_work = NULL;
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tWORK *) malloc (sizeof (tWORK));
      if (x_tries > 3)   break;
   }
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("wipe clean");
   poly_func__wipe_work (x_new);
   *a_work = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_func__free         (tFUNC **a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFUNC      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*a_func"   , *a_func);
   --rce;  if (*a_func == NULL) {
      DEBUG_DATA   yLOG_note    ("never set to a particular function");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free work)----------------------*/
   DEBUG_DATA   yLOG_point   ("work"      , (*a_func)->work);
   if ((*a_func)->work != NULL)  free ((*a_func)->work);
   (*a_func)->work = NULL;
   /*---(clear and return)---------------*/
   free (*a_func);
   *a_func = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   hooking and unhooking                      ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

char
poly_func_hook          (tFILE *a_file, tFUNC *a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_point   ("head"      , a_file->head);
   DEBUG_DATA   yLOG_point   ("tail"      , a_file->tail);
   if (a_file->head  == NULL) {
      DEBUG_DATA   yLOG_note    ("first");
      a_file->head  = a_file->tail  = a_func;
   } else {
      DEBUG_DATA   yLOG_note    ("append");
      a_func->prev        = a_file->tail;
      a_file->tail->next  = a_func;
      a_file->tail        = a_func;
   }
   /*---(tie function back to file)------*/
   DEBUG_DATA   yLOG_note    ("set file");
   a_func->file  = a_file;
   /*---(update count)-------------------*/
   DEBUG_DATA   yLOG_note    ("increment counts");
   ++(a_file->count);
   ++(a_file->proj->funcs);
   DEBUG_DATA   yLOG_value   ("count"     , a_file->count);
   if (a_func->type == 'f')  {
      ++(a_file->COUNT_FUNCS);
      ++(a_file->proj->COUNT_FUNCS);
   }
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_func__unhook       (tFUNC *a_func)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_func);
   if (a_func == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   /*---(out of linked list)-------------*/
   DEBUG_DATA   yLOG_spoint  (a_func->file->head);
   DEBUG_DATA   yLOG_spoint  (a_func->file->tail);
   DEBUG_DATA   yLOG_note    ("unlink");
   if (a_func->next != NULL)   a_func->next->prev = a_func->prev;
   else                       a_func->file->tail = a_func->prev;
   if (a_func->prev != NULL)   a_func->prev->next = a_func->next;
   else                       a_func->file->head = a_func->next;
   /*---(update count)-------------------*/
   DEBUG_DATA   yLOG_note    ("decrement counts");
   --(a_func->file->count);
   --(a_func->file->proj->funcs);
   DEBUG_DATA   yLOG_sint    (a_func->file->count);
   if (a_func->type == 'f')  {
      --(a_func->file->COUNT_FUNCS);
      --(a_func->file->proj->COUNT_FUNCS);
   }
   /*---(untie func from file)-----------*/
   DEBUG_DATA   yLOG_snote   ("unset file");
   a_func->file  = NULL;
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    memory allocation                         ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_func_add           (tFILE *a_file, char *a_name, char a_type, int a_line, tFUNC **a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFUNC      *x_new       = NULL;
   int         x_tries     =    0;
   int         x_len       =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   DEBUG_DATA   yLOG_char    ("a_type"    , a_type);
   --rce;  if (a_type == '\0' || strchr ("f_", a_type) == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_value   ("a_line"    , a_line);
   --rce;  if (a_line <= 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func != NULL) {
      DEBUG_DATA   yLOG_point   ("*a_func"   , *a_func);
      if (*a_func != NULL) {
         DEBUG_DATA   yLOG_note    ("already set to a particular function");
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(create function)----------------*/
   rc = poly_func_new (&x_new);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (rc < 0 || x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create working data)------------*/
   rc = poly_func__new_work (&(x_new->work));
   DEBUG_DATA   yLOG_point   ("->work"    , x_new->work);
   --rce;  if (rc < 0 || x_new->work == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   strlcpy (x_new->name, a_name, LEN_TITLE);
   x_new->type   = a_type;
   x_new->line   = a_line;
   /*---(into file list)-----------------*/
   rc = poly_func_hook (a_file, x_new);
   DEBUG_DATA   yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(into btree)---------------------*/
   rc = poly_btree_hook (B_FUNCS, x_new, x_new->name, &x_new->btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create hint)--------------------*/
   rc = poly_func__hint (poly_btree_count (B_FUNCS) - 1, x_new->hint);
   DEBUG_DATA   yLOG_value   ("hint"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("hint"      , x_new->hint);
   /*---(save)---------------------------*/
   if (a_func != NULL)  *a_func = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_func_del           (tFUNC **a_func)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(beginning)----------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*a_func"   , *a_func);
   --rce;  if (*a_func == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_note    ((*a_func)->name);
   /*---(out of linked list)-------------*/
   rc = poly_func__unhook (*a_func);
   DEBUG_DATA   yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(btree)--------------------------*/
   rc = poly_btree_unhook (&((*a_func)->btree));
   DEBUG_DATA   yLOG_value   ("un-btree"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(purge ylib links)---------------*/
   rc = poly_ylib_purge_tag  (*a_func);
   DEBUG_DATA   yLOG_value   ("purge ylib", rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free main)----------------------*/
   rc = poly_func__free (a_func);
   DEBUG_DATA   yLOG_value   ("free"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        file position                         ----===*/
/*====================------------------------------------====================*/
static void  o___POSITION________o () { return; }

char
poly_func_enter         (tFUNC *a_func, int a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_note    (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_func       == NULL)             return rce;
   --rce;  if (a_func->work == NULL)             return rce;
   /*---(self)---------------------------*/
   --rce;  if (a_func->WORK_BEG >  0)            return rce;
   --rce;  if (a_func->WORK_END >  0)            return rce;
   --rce;  if (a_func->line     >  a_line)       return rce;
   /*---(sequence)-----------------------*/
   --rce;  if (a_func->prev != NULL) {
      if (a_func->prev->WORK_END < 0)            return rce;
      if (a_func->prev->WORK_END >= a_line)      return rce;
   }
   --rce;  if (a_func->next != NULL) {
      if (a_func->next->WORK_BEG > 0)            return rce;
      if (a_func->next->line     <= a_line)      return rce;
   }
   /*---(update)-------------------------*/
   a_func->WORK_BEG   = a_line;
   poly_vars_reset (a_func);
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_func_exit          (tFUNC *a_func, int a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_note    (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_func       == NULL)             return rce;
   --rce;  if (a_func->work == NULL)             return rce;
   /*---(self)---------------------------*/
   --rce;  if (a_func->WORK_BEG < 0)             return rce;
   --rce;  if (a_func->WORK_END > 0)             return rce;
   --rce;  if (a_func->WORK_BEG >  a_line)       return rce;
   /*---(sequence)-----------------------*/
   --rce;  if (a_func->prev != NULL) {
      if (a_func->prev->WORK_END < 0)            return rce;
   }
   --rce;  if (a_func->next != NULL) {
      if (a_func->next->WORK_BEG > 0)            return rce;
      if (a_func->next->line     <= a_line)      return rce;
   }
   /*---(update)-------------------------*/
   a_func->WORK_END  = a_line;
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_func_inside        (tFUNC *a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_note    (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func       == NULL)   return rce;
   /*---(filter)-------------------------*/
   DEBUG_DATA   yLOG_point   ("work"      , a_func->work);
   --rce;  if (a_func->work == NULL)   return rce;
   DEBUG_DATA   yLOG_complex ("beg/end"   , "%3d, %3d", a_func->WORK_BEG, a_func->WORK_END);
   --rce;  if (a_func->WORK_BEG <  0)  return rce;
   --rce;  if (a_func->WORK_END >  0)  return rce;
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_func_search        (tFILE *a_file, int a_line, tFUNC **a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFUNC      *x_func      = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_func          == NULL)   return rce;
   --rce;  if (a_file          == NULL)   return rce;
   /*---(locate)-------------------------*/
   x_func = a_file->head;
   while (x_func != NULL) {
      /*---(filter enter)----------------*/
      if (x_func->WORK_BEG < 0)          { x_func = x_func->next; continue; }
      if (x_func->WORK_BEG > a_line)     { x_func = x_func->next; continue; }
      /*---(filter exit)-----------------*/
      if (x_func->WORK_END > 0) {
         if (x_func->WORK_END < a_line)  { x_func = x_func->next; continue; }
      }
      /*---(return positive)-------------*/
      *a_func = x_func;
      return 0;
   }
   *a_func = NULL;
   /*---(complete)-----------------------*/
   --rce;  return rce;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_func_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = poly_btree_init (B_FUNCS);
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
poly_func_purge         (tFILE *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFUNC       *x_tag       = NULL;
   tFUNC       *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk-through)-------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_file->count);
   x_tag = a_file->head;
   while (x_tag != NULL) {
      x_next = x_tag->next;
      DEBUG_DATA   yLOG_point   ("x_tag"     , x_tag);
      DEBUG_DATA   yLOG_info    ("->name"    , x_tag->name);
      rc = poly_func_del (&x_tag);
      x_tag = x_next;
   }
   /*---(check)--------------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_file->count);
   --rce;  if (a_file->count > 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_func_wrap          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(walk through list)--------------*/
   /*> rc = poly_btree_purge (B_FUNCS);                                                <* 
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
/*===----                     reading from source                      ----===*/
/*====================------------------------------------====================*/
static void  o___SOURCE__________o () { return; }

char
poly_func__purpose_copy (tFUNC *a_func, char *a_recd, int a_beg)
{
   /*---(locals)-----------+-----+-----+-*/
   char       t            [LEN_RECD];
   int        i            =    0;
   int        j            =    0;
   int        x_len        =    0;
   /*---(prepare)------------------------*/
   strlcpy (t, a_recd + a_beg, LEN_RECD);
   x_len = strlen (t);
   /*---(very end)-----------------------*/
   for (i = 0; i < x_len; ++i)  {
      if (strchr ("*=()[]", t [i]) != NULL) {
         t [i] = '\0';
         break;
      }
      if (t [i] == '-' && t [i + 1] == '-') {
         t [i] = '\0';
         break;
      }
   }
   /*---(search)-------------------------*/
   for (j = i; j > 0; --j)  {
      if (strchr (" -=][", t [j]) == NULL)   break;
      t [j] = '\0';
   }
   /*---(save)---------------------------*/
   strlcpy (a_func->purpose, t, 41);
   a_func->ready = 'y';
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> extract the function purpose -------[ ------ [ge.850.137.A4]*/ /*-[02.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_func_purpose       (tFUNC *a_func, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_RECD];
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_func->purpose, "", 41);
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      a_func->ready = 'e';
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(modern style)-------------------*/
   if (strncmp (a_recd, "/*-[ ", 5) == 0) {
      DEBUG_INPT   yLOG_snote   ("current format");
      poly_func__purpose_copy (a_func, a_recd, 5);
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(current style)------------------*/
   if (strncmp (a_recd, "/*-> ", 5) == 0) {
      DEBUG_INPT   yLOG_snote   ("current format");
      poly_func__purpose_copy (a_func, a_recd, 5);
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_recd, "/*--> ",  6) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 1 format");
      poly_func__purpose_copy (a_func, a_recd, 6);
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_recd, "/* ---- : ", 10) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 2 format");
      poly_func__purpose_copy (a_func, a_recd, 10);
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_recd, "/*----: ",  8) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 3 format");
      poly_func__purpose_copy (a_func, a_recd, 8);
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_recd, "/*===[[ ",  8) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 3 format");
      poly_func__purpose_copy (a_func, a_recd, 8);
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(terse format)-------------------*/
   if (strncmp (a_recd, "/* ",  3) == 0) {
      DEBUG_INPT   yLOG_snote   ("terse format");
      poly_func__purpose_copy (a_func, a_recd, 3);
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(complete)-----------------------*/
   a_func->ready = 'e';
   --rce;
   DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char
poly_func_return        (tFUNC *a_func, char *a_recd, char *a_prev)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_return    [LEN_RECD];
   int         x_len       =    0;
   char       *p           = NULL;
   char       *r           = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   a_func->STATS_SINGLE = '-';
   a_func->STATS_SCOPE  = '-';
   a_func->STATS_RTYPE  = '-';
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_prev);
   /*---(find name)----------------------*/
   p = strstr (a_recd, a_func->name);
   DEBUG_DATA   yLOG_spoint  (p);
   /*---(figure spacing)-----------------*/
   x_len = p - a_recd;
   DEBUG_DATA   yLOG_sint    (x_len);
   /*---(set single)---------------------*/
   if (x_len == 0)   a_func->STATS_SINGLE = '-';
   else              a_func->STATS_SINGLE = 'y';
   DEBUG_DATA   yLOG_schar   (a_func->STATS_SINGLE);
   /*---(oneline return type)------------*/
   --rce;  if (a_func->STATS_SINGLE == 'y') {
      strlcpy (x_return, a_recd, x_len);
   }
   /*---(multiline return type)----------*/
   else {
      if (a_prev == NULL) {
         DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      r = strstr (a_prev, "/*");
      if (r == NULL)  x_len = strlen (a_prev);
      else            x_len = r - a_prev;
      strlcpy (x_return, a_prev, x_len + 1);
   }
   strltrim (x_return, ySTR_SINGLE, LEN_RECD);
   DEBUG_DATA   yLOG_snote   (x_return);
   /*---(remove static)------------------*/
   r = strstr (x_return, "static");
   if (r == x_return) {
      strlcpy  (x_return, x_return  + 7, LEN_RECD);
      strltrim (x_return, ySTR_SINGLE, LEN_RECD);
      a_func->STATS_SCOPE = 's';
   }
   /*---(classify scope)-----------------*/
   else if (strstr (a_func->name, "__unit") != NULL)  a_func->STATS_SCOPE = 'u';
   else if (strstr (a_func->name, "__test") != NULL)  a_func->STATS_SCOPE = 'u';
   else if (strstr (a_func->name, "__"    ) != NULL)  a_func->STATS_SCOPE = 'f';
   else                                               a_func->STATS_SCOPE = 'g';
   DEBUG_DATA   yLOG_schar   (a_func->STATS_SCOPE);
   /*---(classify return type)-----------*/
   if      (strcmp (x_return   , "char*"  ) == 0   )  a_func->STATS_RTYPE = 's';
   else if (strcmp (x_return   , "char *" ) == 0   )  a_func->STATS_RTYPE = 's';
   else if (strcmp (x_return   , "char"   ) == 0   )  a_func->STATS_RTYPE = 'c';
   else if (strcmp (x_return   , "void"   ) == 0   )  a_func->STATS_RTYPE = 'v';
   else if (strstr (x_return   , "*"      ) != NULL)  a_func->STATS_RTYPE = 'p';
   else if (strcmp (x_return   , "short"  ) == 0   )  a_func->STATS_RTYPE = 'n';
   else if (strcmp (x_return   , "int"    ) == 0   )  a_func->STATS_RTYPE = 'n';
   else if (strcmp (x_return   , "long"   ) == 0   )  a_func->STATS_RTYPE = 'n';
   else if (strcmp (x_return   , "float"  ) == 0   )  a_func->STATS_RTYPE = 'n';
   else if (strcmp (x_return   , "double" ) == 0   )  a_func->STATS_RTYPE = 'n';
   else                                               a_func->STATS_RTYPE = 'o';
   DEBUG_DATA   yLOG_schar   (a_func->STATS_RTYPE);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_func_params        (tFUNC *a_func, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *r           = NULL;
   char       *b           = NULL;
   char       *e           = NULL;
   int        x_len        =    0;
   char       x_return     [LEN_RECD];
   char       x_params     [LEN_RECD];
   char       x_body       [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   a_func->WORK_PARAMS  = 0;
   a_func->STATS_PARAMS = '-';
   a_func->STATS_PTWO   = '-';
   a_func->STATS_PNUM   = '-';
   DEBUG_DATA   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (t, a_recd, LEN_RECD);
   /*---(isolate parms)------------------*/
   b = strchr (a_recd, '(');
   if (b != NULL) {
      DEBUG_DATA   yLOG_note    ("found open paren");
      e = strchr (a_recd, '{');
      if (e == NULL)  x_len = LEN_RECD;
      else            x_len = e - b;
      strlcpy  (x_params, b, x_len);
      strltrim (x_params, ySTR_EVERY , x_len);
   }
   /*---(get count)----------------------*/
   if (b != NULL) {
      a_func->WORK_PARAMS = -3;
      if      (strcmp (x_params, "()")       == 0)  a_func->WORK_PARAMS = -2;
      else if (strcmp (x_params, "( )")      == 0)  a_func->WORK_PARAMS = -2;
      else if (strcmp (x_params, "(void)")   == 0)  a_func->WORK_PARAMS =  0;
      else if (strcmp (x_params, "( void)")  == 0)  a_func->WORK_PARAMS =  0;
      else if (strcmp (x_params, "(void )")  == 0)  a_func->WORK_PARAMS =  0;
      else if (strcmp (x_params, "( void )") == 0)  a_func->WORK_PARAMS =  0;
      else    a_func->WORK_PARAMS = strldcnt (x_params, ',', x_len) + 1;
   }
   /*---(find pointers)------------------*/
   if (b != NULL) {
      if      (strstr (x_params, "**"       ) != NULL)  a_func->STATS_PTWO = '#';
      else if (strstr (x_params, "[]"       ) != NULL)  a_func->STATS_PTWO = '#';
      else if (strstr (x_params, "[ ]"      ) != NULL)  a_func->STATS_PTWO = '#';
      if      (strstr (x_params, "float*"   ) != NULL)  a_func->STATS_PNUM = '#';
      else if (strstr (x_params, "float *"  ) != NULL)  a_func->STATS_PNUM = '#';
      else if (strstr (x_params, "double*"  ) != NULL)  a_func->STATS_PNUM = '#';
      else if (strstr (x_params, "double *" ) != NULL)  a_func->STATS_PNUM = '#';
      else if (strstr (x_params, "short*"   ) != NULL)  a_func->STATS_PNUM = '#';
      else if (strstr (x_params, "short *"  ) != NULL)  a_func->STATS_PNUM = '#';
      else if (strstr (x_params, "int*"     ) != NULL)  a_func->STATS_PNUM = '#';
      else if (strstr (x_params, "int *"    ) != NULL)  a_func->STATS_PNUM = '#';
      else if (strstr (x_params, "long*"    ) != NULL)  a_func->STATS_PNUM = '#';
      else if (strstr (x_params, "long *"   ) != NULL)  a_func->STATS_PNUM = '#';
   }
   /*---(no parameters)------------------*/
   --rce;  if (b == NULL) {
      a_func->WORK_PARAMS  = -2;
      a_func->STATS_PARAMS = '?';
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(create statistic)---------------*/
   poly_cats_exact   ("nparam"  , a_func->WORK_PARAMS  , &a_func->STATS_PARAMS, '0');
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_func__unit         (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   char        r           [LEN_TERSE]= "  -";
   char        s           [LEN_TERSE]= "  -";
   char        q           [LEN_TERSE]= "  -";
   tFUNC      *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FUNC unit        : function number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "FUNC count       : %3d", poly_btree_count (B_FUNCS));
      return unit_answer;
   }
   if (strncmp (unit_answer, "FUNC unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FUNC unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "head"      )     == 0) {
      u = (tFUNC *) poly_btree_entry (B_FUNCS, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         sprintf  (r, "[%.40s]", u->purpose);
         snprintf (unit_answer, LEN_RECD, "FUNC head   (%2d) : %-22.22s %2d%-42.42s  %c", i, t, strlen (u->purpose), r, u->ready);
      }  else
         snprintf (unit_answer, LEN_RECD, "FUNC head   (%2d) : []                     []         0[]                                          -", i);
   }
   else if (strcmp (a_question, "entry"     )     == 0) {
      u = (tFUNC *) poly_btree_entry (B_FUNCS, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->work != NULL)  snprintf (unit_answer, LEN_RECD, "FUNC entry  (%2d) : %-22.22s %3d  %c  work   %3d  %3d", i, t, u->line, u->type, u->WORK_BEG, u->WORK_END);
         else                  snprintf (unit_answer, LEN_RECD, "FUNC entry  (%2d) : %-22.22s %3d  %c  non      -    -", i, t, u->line, u->type);
      } else                   snprintf (unit_answer, LEN_RECD, "FUNC entry  (%2d) : %-22.22s   -  -  -        -    -", i, t);
   }
   else if (strcmp (a_question, "stats"     )     == 0) {
      u = (tFUNC *) poly_btree_entry (B_FUNCS, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->WORK_BEG    >= 0)  sprintf  (r, "%3d",     u->WORK_BEG);
         if (u->WORK_END    >= 0)  sprintf  (s, "%3d",     u->WORK_END);
         if (u->WORK_LVARS  >  0)  sprintf  (q, "%3d",     u->WORK_LVARS );
         snprintf (unit_answer, LEN_RECD, "FUNC stats  (%2d) : %-22.22s     �   �   %3d %3d %3d %3d %3d %3d   %3d %s %s   %s", i, t, u->COUNT_LINES, u->COUNT_EMPTY, u->COUNT_DOCS, u->COUNT_DEBUG, u->COUNT_CODE, u->COUNT_SLOCL, u->line, r, s, q);
      }  else
         snprintf (unit_answer, LEN_RECD, "FUNC stats  (%2d) : %-22.22s     �   �     -   -   -   -   -   -     -   -   -     -", i, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
