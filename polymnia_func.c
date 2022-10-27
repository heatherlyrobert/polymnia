/*============================----beg-of-source---============================*/
#include  "polymnia.h"



static char s_print     [LEN_RECD] = "";

/*
 * function types (expanded on ctags)
 *    p prototype                (ctags)
 *    f function definition      (ctags)
 *    _ sub-title break
 *    s unit testing script
 *    S unit testing shared script
 *
 *
 */



/*====================------------------------------------====================*/
/*===----                     small supporters                         ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

/*> char                                                                                   <* 
 *> poly_func__hint         (int n, char *a_label)                                         <* 
 *> {                                                                                      <* 
 *>    /+---(locals)-----------+-----------+-+/                                            <* 
 *>    char        rce         = -10;           /+ return code for errors         +/       <* 
 *>    char       *x_1st       = "abcdefghijklmnopqrstuvwxyz";                             <* 
 *>    int         x_1len      = strlen (x_1st);                                           <* 
 *>    char       *x_2nd       = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";   <* 
 *>    int         x_2len      = strlen (x_2nd);                                           <* 
 *>    --rce;  if (a_label == NULL)  return rce;                                           <* 
 *>    strlcpy (a_label, "··", LEN_LABEL);                                                 <* 
 *>    --rce;  if (n < 0)            return rce;                                           <* 
 *>    --rce;  if (n > 1351)         return rce;                                           <* 
 *>    a_label [0] = x_1st [n / x_2len];                                                   <* 
 *>    a_label [1] = x_2nd [n % x_2len];                                                   <* 
 *>    a_label [2] = '\0';                                                                 <* 
 *>    return 0;                                                                           <* 
 *> }                                                                                      <*/

char
poly_func_cli           (char *a_hint, char a_loud)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   char       *x_valid     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   int         i           =    0;
   tFUNC      *x_func      = NULL;
   /*---(header)-------------------------*/
   DEBUG_ARGS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   strlcpy (my.g_hint, "--", LEN_TERSE);
   /*---(defense)------------------------*/
   DEBUG_ARGS  yLOG_point   ("a_hint"    , a_hint);
   --rce;  if (a_hint == NULL) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "hint <name>, name can not be null");
      DEBUG_ARGS  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ARGS  yLOG_info    ("a_hint"    , a_hint);
   /*---(check length)-------------------*/
   x_len = strlen (a_hint);
   DEBUG_ARGS  yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len != 2) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "hint <name>, name must be two characters long");
      DEBUG_ARGS  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check characters)---------------*/
   --rce;  for (i = 0; i < x_len; ++i) {
      if (strchr (x_valid, a_hint [i]) != NULL)  continue;
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "hint <name>, name can not have a <%c> at character %d", a_hint [i], i);
      DEBUG_ARGS  yLOG_char  ("bad char"  , a_hint [i]);
      DEBUG_ARGS  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(find it)------------------------*/
   /*> DEBUG_ARGS  yLOG_point   ("g_proj"    , my.g_proj);                            <*/
   /*> --rce;  if (my.g_proj == NULL) {                                                         <* 
    *>    if (a_loud == 'y')  yURG_err (YURG_FATAL, "hint <name>, no current project set");      <* 
    *>    DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);                                           <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> poly_func_by_hint (my.g_proj, x_recd, &x_found);                                         <* 
    *> DEBUG_ARGS  yLOG_point   ("x_found"   , x_found);                                        <* 
    *> --rce;  if (x_found == NULL) {                                                           <* 
    *>    if (a_loud == 'y')  yURG_err (YURG_FATAL, "hint <name>, name not found in project");   <* 
    *>    DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);                                           <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <*/
   /*---(copy)---------------------------*/
   strlcpy (my.g_hint, a_hint, LEN_TERSE);
   DEBUG_ARGS  yLOG_info    ("g_hint"    , my.g_hint);
   /*---(complete)-----------------------*/
   DEBUG_ARGS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_func_cli_name      (char *a_name, char a_loud)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   char       *x_valid     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   int         i           =    0;
   tFUNC      *x_func      = NULL;
   /*---(header)-------------------------*/
   DEBUG_ARGS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   strlcpy (my.g_hint, "--", LEN_TERSE);
   /*---(defense)------------------------*/
   DEBUG_ARGS  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "hint <name>, name can not be null");
      DEBUG_ARGS  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ARGS  yLOG_info    ("a_name"    , a_name);
   /*---(check length)-------------------*/
   /*> x_len = strlen (a_hint);                                                                         <* 
    *> DEBUG_ARGS  yLOG_value   ("x_len"     , x_len);                                                  <* 
    *> --rce;  if (x_len != 2) {                                                                        <* 
    *>    if (a_loud == 'y')  yURG_err (YURG_FATAL, "hint <name>, name must be two characters long");   <* 
    *>    DEBUG_ARGS  yLOG_exitr (__FUNCTION__, rce);                                                   <* 
    *>    return rce;                                                                                   <* 
    *> }                                                                                                <*/
   /*---(check characters)---------------*/
   /*> --rce;  for (i = 0; i < x_len; ++i) {                                                                                   <* 
    *>    if (strchr (x_valid, a_hint [i]) != NULL)  continue;                                                                 <* 
    *>    if (a_loud == 'y')  yURG_err (YURG_FATAL, "hint <name>, name can not have a <%c> at character %d", a_hint [i], i);   <* 
    *>    DEBUG_ARGS  yLOG_char  ("bad char"  , a_hint [i]);                                                                   <* 
    *>    DEBUG_ARGS  yLOG_exitr (__FUNCTION__, rce);                                                                          <* 
    *>    return rce;                                                                                                          <* 
    *> }                                                                                                                       <*/
   /*---(find it)------------------------*/
   /*> DEBUG_ARGS  yLOG_point   ("g_proj"    , my.g_proj);                            <*/
   /*> --rce;  if (my.g_proj == NULL) {                                                         <* 
    *>    if (a_loud == 'y')  yURG_err (YURG_FATAL, "hint <name>, no current project set");      <* 
    *>    DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);                                           <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> poly_func_by_hint (my.g_proj, x_recd, &x_found);                                         <* 
    *> DEBUG_ARGS  yLOG_point   ("x_found"   , x_found);                                        <* 
    *> --rce;  if (x_found == NULL) {                                                           <* 
    *>    if (a_loud == 'y')  yURG_err (YURG_FATAL, "hint <name>, name not found in project");   <* 
    *>    DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);                                           <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <*/
   /*---(copy)---------------------------*/
   strlcpy (my.g_funcname, a_name, LEN_DESC);
   DEBUG_ARGS  yLOG_info    ("funcname"  , my.g_funcname);
   /*---(complete)-----------------------*/
   DEBUG_ARGS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   clearing and checking                      ----===*/
/*====================------------------------------------====================*/
static void  o___CLEARING________o () { return; }

char
poly_func__wipe         (tFUNC *a_func)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(master)-------------------------*/
   a_func->type        = '-';
   a_func->name [0]    = '\0';
   a_func->line        = -1;
   a_func->hint [0]    = '\0';
   a_func->purpose [0] = '\0';
   a_func->ready       = '?';
   /*---(pointers)-----------------------*/
   a_func->file        = NULL;
   a_func->prev        = NULL;
   a_func->next        = NULL;
   a_func->work        = NULL;
   a_func->y_head      = NULL;
   a_func->y_tail      = NULL;
   a_func->y_count     = 0;
   /*---(clear counts/stats)-------------*/
   poly_cats_counts_clear (a_func->counts);
   poly_cats_stats_clear  (a_func->stats);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 1;
}

char*
poly_func__memory       (tFUNC *a_func)
{
   /*---(master)-------------------------*/
   strlcpy (s_print, "["  , LEN_RECD);
   poly_shared__check_char (s_print, a_func->type);
   poly_shared__check_str  (s_print, a_func->name);
   poly_shared__check_num  (s_print, a_func->line);
   poly_shared__check_str  (s_print, a_func->hint);
   poly_shared__check_str  (s_print, a_func->purpose);
   poly_shared__check_char (s_print, a_func->ready);
   poly_shared__spacer     (s_print);
   /*---(func/ylib)----------------------*/
   poly_shared__check_ptr  (s_print, a_func->file);
   poly_shared__check_ptr  (s_print, a_func->prev);
   poly_shared__check_ptr  (s_print, a_func->next);
   poly_shared__check_ptr  (s_print, a_func->work);
   poly_shared__check_ptr  (s_print, a_func->y_head);
   poly_shared__check_ptr  (s_print, a_func->y_tail);
   poly_shared__check_num  (s_print, a_func->y_count);
   strlcat (s_print, "]" , LEN_RECD);
   /*---(complete)-----------------------*/
   return s_print;
}

char
poly_work__wipe         (tWORK *a_work)
{
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(positioning)--------------------*/
   a_work->beg      = -1;
   a_work->end      = -1;
   for (i = 0; i < MAX_TEMPS; ++i)  a_work->temp [i] = 0;
   a_work->temp [0]   = -1;  /* params is special */
   a_work->locals [0] = '\0';
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 1;
}

char*
poly_work__memory       (tWORK *a_work)
{
   /*---(master)-------------------------*/
   strlcpy (s_print, "["  , LEN_RECD);
   poly_shared__check_num  (s_print, a_work->beg);
   poly_shared__check_num  (s_print, a_work->end);
   poly_shared__check_num  (s_print, a_work->temp [0]);
   poly_shared__check_str  (s_print, a_work->locals);
   strlcat (s_print, "]" , LEN_RECD);
   /*---(complete)-----------------------*/
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char poly_func__new  (tFUNC **a_new) { return poly_shared_new  ("func", sizeof (tFUNC), a_new, NULL, '-', poly_func__wipe); }
char poly_func_force (tFUNC **a_new) { return poly_shared_new  ("func", sizeof (tFUNC), a_new, NULL, 'y', poly_func__wipe); }
char poly_func__free (tFUNC **a_old) { return poly_shared_free ("func", a_old, NULL); }

char poly_work__new  (tWORK **a_new) { return poly_shared_new  ("work", sizeof (tWORK), a_new, NULL, '-', poly_work__wipe); }
char poly_work_force (tWORK **a_new) { return poly_shared_new  ("work", sizeof (tWORK), a_new, NULL, 'y', poly_work__wipe); }
char poly_work__free (tWORK **a_old) { return poly_shared_free ("work", a_old, NULL); }



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
   if (strchr ("fsS", a_func->type) != NULL)  {
      ++(a_file->COUNT_FUNCS);
      ++(a_file->proj->COUNT_FUNCS);
      ++(my.COUNT_FUNCS);
   }
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_func_unhook        (tFUNC *a_func)
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
   if (strchr ("fsS", a_func->type) != NULL)  {
      --(a_func->file->COUNT_FUNCS);
      --(a_func->file->proj->COUNT_FUNCS);
      --(my.COUNT_FUNCS);
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
   --rce;  if (a_type == '\0' || strchr ("f_wsS", a_type) == NULL) {
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
   rc = poly_func__new (&x_new);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (rc < 0 || x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create working data)------------*/
   rc = poly_work__new (&(x_new->work));
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
   rc = ySORT_hook (B_FUNCS, x_new, x_new->name, &x_new->btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create hint)--------------------*/
   /*> rc = poly_func__hint (ySORT_count (B_FUNCS) - 1, x_new->hint);            <*/
   rc = strlhint (ySORT_count (B_FUNCS) - 1, "lA", x_new->hint);
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
poly_func_remove        (tFUNC **a_func)
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
   /*---(purge ylib links)---------------*/
   rc = poly_ylib_purge  (*a_func, '-');
   DEBUG_DATA   yLOG_value   ("purge ylib", rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(out of linked list)-------------*/
   rc = poly_func_unhook (*a_func);
   DEBUG_DATA   yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(btree)--------------------------*/
   rc = ySORT_unhook (&((*a_func)->btree));
   DEBUG_DATA   yLOG_value   ("un-btree"  , rc);
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
   a_func->WORK_BEG  = a_line;
   a_func->beg       = a_line;
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
   a_func->end       = a_line;
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



/*====================------------------------------------====================*/
/*===----                           searching                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  poly_func_count         (void)                          { return ySORT_count     (B_FUNCS); }
char poly_func_by_name       (uchar *a_name, tFUNC **r_func) { return ySORT_by_name   (B_FUNCS, a_name, r_func); }
char poly_func_by_index      (int n, tFUNC **r_func)         { return ySORT_by_index  (B_FUNCS, n, r_func); }
char poly_func_cursor        (char a_dir, tFUNC **r_func)    { return ySORT_by_cursor (B_FUNCS, a_dir, r_func); }


char
poly_func_by_line       (tFILE *a_file, int a_line, tFUNC **a_func)
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

char
poly_func_by_hint       (tPROJ *a_proj, uchar *a_hint, tFUNC **a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   tFILE      *x_file      = NULL;
   tFUNC      *x_func      = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_proj   == NULL)   return rce;
   --rce;  if (a_hint   == NULL)   return rce;
   --rce;  if (a_func   == NULL)   return rce;
   x_len = strlen (a_hint);
   --rce;  if (x_len    != 2)      return rce;
   --rce;  if (a_hint [0] < 'a' || a_hint [0] > 'z')   return rce;
   --rce;  if (a_hint [1] < 'A' || a_hint [1] > 'z')   return rce;
   --rce;  if (a_hint [1] > 'Z' && a_hint [1] < 'a')   return rce;
   /*---(prepare)------------------------*/
   *a_func = NULL;
   /*---(walk files)---------------------*/
   x_file = a_proj->head;
   while (x_file != NULL) {
      /*---(walk functions)--------------*/
      x_func = x_file->head;
      while (x_func != NULL) {
         if (strcmp (x_func->hint, a_hint) == 0) {
            *a_func = x_func;
            return 0;
         }
         x_func = x_func->next;
      }
      x_file = x_file->next;
   }
   /*---(complete)-----------------------*/
   --rce;  return rce;
}

char         /*-[ cursor from provided position ------------[----------------]*/
poly_func_by_cursor     (tPROJ *a_proj, uchar a_mode, tFUNC **a_func)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFILE      *x_file      = NULL;
   tFUNC      *x_func      = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_proj   == NULL)   return rce;
   --rce;  if (a_func   == NULL)   return rce;
   /*---(prepare)------------------------*/
   x_func = *a_func;
   if (x_func == NULL)  x_func = a_proj->head->head;
   --rce;  if (x_func   == NULL)   return rce;
   x_file = x_func->file;
   --rce;  if (x_file   == NULL)   return rce;
   /*---(select)-------------------------*/
   switch (a_mode) {
   case '['  :
      x_func = a_proj->head->head;
      break;
   case '<'  :
      x_func = x_func->prev;
      if (x_func == NULL || x_func == *a_func) {
         if (x_file->prev != NULL) {
            x_func = x_file->prev->tail;
         }
      }
      break;
   case '.'  :
      ;;
      break;
   case '>'  :
      x_func = x_func->next;
      if (x_func == NULL || x_func == *a_func) {
         if (x_file->next != NULL) {
            x_func = x_file->next->head;
         }
      }
      break;
   case ']'  :
      x_func = a_proj->tail->tail;
      break;
   default   :
      --rce;
      return rce;
      break;
   }
   /*---(check update)-------------------*/
   --rce;  if (x_func == NULL)  return rce;
   /*---(save)---------------------------*/
   *a_func = x_func;
   /*---(complete)-----------------------*/
   return 0;
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
   rc = ySORT_btree (B_FUNCS, "functions");
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
poly_func_purge         (tFILE *a_file, char a_update)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFUNC       *x_func     = NULL;
   tFUNC       *x_next     = NULL;
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
   x_func = a_file->head;
   while (x_func != NULL) {
      x_next = x_func->next;
      DEBUG_DATA   yLOG_point   ("x_func"    , x_func);
      DEBUG_DATA   yLOG_info    ("->name"    , x_func->name);
      rc = poly_func_remove (&x_func);
      x_func = x_next;
   }
   /*---(check)--------------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_file->count);
   --rce;  if (a_file->count > 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update btrees)------------------*/
   --rce;  if (a_update == 'y') {
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
poly_func_wrap          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(walk through list)--------------*/
   /*> rc = ySORT_purge (B_FUNCS);                                                <* 
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
/*===----                       reporting support                      ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTING_______o () { return; }

static char  *s_owner     = "---project----- § ---file------------- § line";
static char  *s_ends      = "-beg § -end";
static char  *s_all       = "prj § fil § fnc";
static char  *s_count     = "fnc";

char*
poly_func__prefix       (tFUNC *a_func, char a_spec, int a, int b, int c)
{
   /*---(locals)-------------------------*/
   char        t           [LEN_RECD]  = "";
   char        s           [LEN_RECD]  = "";
   char        x_type      = '-';
   /*---(prepare)------------------------*/
   strlcpy (s_print, "", LEN_RECD);
   if (a_func == NULL)  x_type = 'h';
   if (a_spec == '\0')  return s_print;
   /*---(owner style)--------------------*/
   if (strchr ("AHOo", a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "%-15.15s § %-20.20s § %4d § ", a_func->file->proj->name, a_func->file->name, a_func->line);
         break;
      case 'h' :
         sprintf (t, "%s § ", s_owner);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(ends style)---------------------*/
   if (strchr ("AO", a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "%4d § %4d § ", a_func->beg, a_func->end);
         break;
      case 'h' :
         sprintf (t, "%s § ", s_ends);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(full counts)--------------------*/
   if (a_spec == 'N') {
      switch (x_type) {
      case '-' :
         sprintf (t, "%-3d § %-3d § %-3d § ", a + 1, b + 1, c + 1);
         break;
      case 'h' :
         sprintf (t, "%s § ", s_all);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(function count)-----------------*/
   else if (a_spec == 'n') {
      switch (x_type) {
      case '-' :
         sprintf (t, "%-3d § ", c + 1);
         break;
      case 'h' :
         sprintf (t, "%s § ", s_count);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(normal hint)--------------------*/
   if (strchr ("AHh", a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "%-2.2s § ", a_func->hint);
         break;
      case 'h' :
         sprintf (t, "-- § ");
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(tag style)----------------------*/
   if (strchr ("t"  , a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "%-2.2s  ", a_func->hint);
         break;
      case 'h' :
         sprintf (t, "func");
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(complete)-----------------------*/
   return s_print;
}

static char  *s_name      = "---name------------------";
static char  *s_stats     = "files § funcs";
static char  *s_short     = "ylibs § --lines § --empty § ---docs § --debug § ---code § --slocl";

char*
poly_func__core         (tFUNC *a_func, char a_spec, int c)
{
   /*---(locals)-------------------------*/
   char        t           [LEN_RECD]  = "";
   char        s           [LEN_RECD]  = "";
   char        x_type      = '-';
   /*---(prepare)------------------------*/
   if (a_func == NULL)  x_type = 'h';
   if (a_spec == '\0')  return s_print;
   /*---(tag entry)----------------------*/
   if (a_spec == 't') {
      switch (x_type) {
      case '-' :
         sprintf (t, "%-25.25s § ", a_func->name);
         break;
      case 'h' : 
         sprintf (t, "tion (%2d)                 § ", c);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(normal name)--------------------*/
   if (strchr ("Ssn" , a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "%-25.25s § ", a_func->name);
         break;
      case 'h' :  
         sprintf (t, "%s § "      , s_name);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(standard stats)-----------------*/
   if (strchr ("S"   , a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "    - §     - § ");
         break;
      case 'h' :
         sprintf (t, "%-s § "   , s_stats);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(short stats)--------------------*/
   if (strchr ("Ss"  , a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "%5d § %7d § %7d § %7d § %7d § %7d § %7d § ",
               a_func->COUNT_YLIBS,
               a_func->COUNT_LINES, a_func->COUNT_EMPTY, a_func->COUNT_DOCS ,
               a_func->COUNT_DEBUG, a_func->COUNT_CODE , a_func->COUNT_SLOCL);
         break;
      case 'h' :
         sprintf (t, "%-s § "   , s_short);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(complete)-----------------------*/
   return s_print;
}

/*---(details)------------------------*/
static char  *s_database  = "-  [--------------complexity--------------] [------------------integration----------------] [---------------watch-points-------------]";
static char  *s_comment   = "[-----complexity------] [-------integration-------] [------watchpoints-----]";
static char  *s_file      = "line § ---file-name----------------------------";
static char  *s_purpose   = "---purpose------------------------------";

char*
poly_func__suffix       (tFUNC *a_func, char a_spec)
{
   /*---(locals)-------------------------*/
   char        t           [LEN_RECD]  = "";
   char        x_type      = '-';
   /*---(prepare)------------------------*/
   if (a_func == NULL)  x_type = 'h';
   if (a_spec == '\0')  return s_print;
   /*---(database view)------------------*/
   if (strchr ("dt"  , a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "%-s § "   , poly_cats_database (a_func));
         break;
      case 'h' :
         sprintf (t, "%-s § "   , s_database);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(compressed view)----------------*/
   if (strchr ("ct"  , a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "%-s § "   , poly_cats_comment  (a_func));
         break;
      case 'h' :
         sprintf (t, "%-s § "   , s_comment);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(file view)----------------------*/
   if (strchr ("ft"  , a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "%4d § %-40.40s § "   , a_func->line, a_func->file->name);
         break;
      case 'h' :
         sprintf (t, "%-s § "   , s_file);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(purpose view)-------------------*/
   if (strchr ("pt"  , a_spec) != NULL) {
      switch (x_type) {
      case '-' :
         sprintf (t, "%-40.40s § "   , a_func->purpose);
         break;
      case 'h' :
         sprintf (t, "%-s § "   , s_purpose);
         break;
      }
      strlcat (s_print, t, LEN_RECD);
   }
   /*---(complete)-----------------------*/
   return s_print;
}

char*
poly_func_line          (tFUNC *a_func, char a_style, int a, int b, int c, char a_print)
{
   /*  n  name    , just the name
    *  s  stats   , short count, name, plus statistics
    *  a  all     , long count, name, plus statistics
    *  d  database, stats as shown in database format
    *  c  comment , stats as shown in function comment
    *  f  file    , name, file, and line
    *  p  purpse  , name and purpose
    */
   /*---(locals)-------------------------*/
   /*> char        t           [LEN_RECD]  = "";                                                                                                                        <* 
    *> char        s           [LEN_RECD]  = "";                                                                                                                        <* 
    *> char  *x_all       = "prj § fil § fnc";                                                                                                                          <* 
    *> char  *x_count     = "fnc";                                                                                                                                      <* 
    *> char  *x_name      = "---name------------------";                                                                                                                <* 
    *> char  *x_stats     = "files § funcs § ylibs § --lines § --empty § ---docs § --debug § ---code § --slocl";                                                        <* 
    *> char  *x_database  = "-  [------------complexity------------] [------------------integration----------------] [-----------------watch-points---------------]";   <* 
    *> char  *x_comment   = "[----complexity-----] [-------integration-------] [------watchpoints-------]";                                                             <*/
   switch (a_style) {
   case POLY_RPTG_HTAGS :
      poly_func__prefix  (a_func, 't', a, b, c);
      poly_func__core    (a_func, 't', c);
      poly_func__suffix  (a_func, 't');
      break;
   case POLY_RPTG_DUMP  :
      poly_func__prefix  (a_func, 'A', a, b, c);
      poly_func__core    (a_func, 'S', c);
      poly_func__suffix  (a_func, 't');
   }
   /*---(index)--------------------------*/
   /*> if (strchr ("aA", a_style) != NULL) {                                                <* 
    *>    switch (x_type) {                                                                 <* 
    *>    case '-' :   sprintf (t, "%-3d § %-3d § %-3d § ", a + 1, b + 1, c + 1);  break;   <* 
    *>    case 'h' :   sprintf (t, "%s § ", x_all);                        break;           <* 
    *>    }                                                                                 <* 
    *>    strlcat (s_print, t, LEN_RECD);                                                   <* 
    *> }                                                                                    <*/
   /*> if (strchr ("sL", a_style) != NULL) {                                          <* 
    *>    switch (x_type) {                                                           <* 
    *>    case '-' :   sprintf (t, "%-3d § ", c + 1);  break;                         <* 
    *>    case 'h' :   sprintf (t, "%s § ", x_count);              break;             <* 
    *>    }                                                                           <* 
    *>    strlcat (s_print, t, LEN_RECD);                                             <* 
    *> }                                                                              <*/
   /*---(name)---------------------------*/
   /*> if (strchr ("tT" , a_style) != NULL) {                                         <* 
    *>    switch (x_type) {                                                           <* 
    *>    case '-' :   sprintf (t, "%2s  %-25.25s § ",                                <* 
    *>                       a_func->hint, a_func->name);                             <* 
    *>                 break;                                                         <* 
    *>    case 'h' :   sprintf (t, "function (%2d)                 § ", c);           <* 
    *>                 break;                                                         <* 
    *>    }                                                                           <* 
    *> } else {                                                                       <* 
    *>    switch (x_type) {                                                           <* 
    *>    case '-' :   sprintf (t, "%-25.25s § ", a_func->name);      break;          <* 
    *>    case 'h' :   sprintf (t, "%s § "      , x_name);            break;          <* 
    *>    }                                                                           <* 
    *> }                                                                              <* 
    *> strlcat (s_print, t, LEN_RECD);                                                <*/
   /*---(statistics)---------------------*/
   /*> if (strchr ("sLaA", a_style) != NULL) {                                             <* 
    *>    switch (x_type) {                                                                <* 
    *>    case '-' : sprintf (t, "    - §     - § %7d § %7d § %7d § %7d § %7d § %7d § ",   <* 
    *>                     a_func->COUNT_LINES, a_func->COUNT_EMPTY,                       <* 
    *>                     a_func->COUNT_DOCS , a_func->COUNT_DEBUG,                       <* 
    *>                     a_func->COUNT_CODE , a_func->COUNT_SLOCL);                      <* 
    *>               break;                                                                <* 
    *>    case 'h' : sprintf (t, "%-s § "   , x_stats);            break;                  <* 
    *>    }                                                                                <* 
    *>    strlcat (s_print, t, LEN_RECD);                                                  <* 
    *> }                                                                                   <*/
   /*---(database view)------------------*/
   /*> if (strchr ("LAdT", a_style) != NULL) {                                        <* 
    *>    switch (x_type) {                                                           <* 
    *>    case '-' : sprintf (t, "%-s § "   , poly_cats_database (a_func)); break;    <* 
    *>    case 'h' : sprintf (t, "%-s § "   , x_database);         break;             <* 
    *>    }                                                                           <* 
    *>    strlcat (s_print, t, LEN_RECD);                                             <* 
    *> }                                                                              <*/
   /*---(compressed view)----------------*/
   /*> if (strchr ("LAcT", a_style) != NULL) {                                        <* 
    *>    switch (x_type) {                                                           <* 
    *>    case '-' : sprintf (t, "%-s § "   , poly_cats_comment  (a_func)); break;    <* 
    *>    case 'h' : sprintf (t, "%-s § "   , x_comment);          break;             <* 
    *>    }                                                                           <* 
    *>    strlcat (s_print, t, LEN_RECD);                                             <* 
    *> }                                                                              <*/
   /*---(file view)----------------------*/
   /*> if (strchr ("LAfT", a_style) != NULL) {                                        <* 
    *>    switch (x_type) {                                                           <* 
    *>    case '-' : sprintf (t, "%4d § %-40.40s § "   ,                              <* 
    *>                     a_func->line, a_func->file->name);                         <* 
    *>               break;                                                           <* 
    *>    case 'h' : sprintf (t, "%-s § "   , s_file);             break;             <* 
    *>    }                                                                           <* 
    *>    strlcat (s_print, t, LEN_RECD);                                             <* 
    *> }                                                                              <*/
   /*---(purpose view)-------------------*/
   /*> if (strchr ("LApT", a_style) != NULL) {                                        <* 
    *>    switch (x_type) {                                                           <* 
    *>    case '-' : sprintf (t, "%-40.40s § "   , a_func->purpose); break;           <* 
    *>    case 'h' : sprintf (t, "%-s § "   , s_purpose);            break;           <* 
    *>    }                                                                           <* 
    *>    strlcat (s_print, t, LEN_RECD);                                             <* 
    *> }                                                                              <*/
   /*---(newline)------------------------*/
   if (a_print == 'y')  printf ("%s\n", s_print);
   /*---(complete)-----------------------*/
   return s_print;
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
      snprintf (unit_answer, LEN_RECD, "FUNC count       : %3d", poly_func_count ());
      return unit_answer;
   }
   else if (strcmp (a_question, "print"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "FUNC print       : %4d[%-.400s]", strlen (s_print), s_print);;
      return unit_answer;
   }
   else if (strcmp (a_question, "hint"      )     == 0) {
      snprintf (unit_answer, LEN_RECD, "FUNC hint        : %s", my.g_hint);
      return unit_answer;
   }
   if (strncmp (unit_answer, "FUNC unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FUNC unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "head"      )     == 0) {
      poly_func_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         sprintf  (r, "[%.40s]", u->purpose);
         snprintf (unit_answer, LEN_RECD, "FUNC head   (%2d) : %-22.22s %2d%-42.42s  %c", i, t, strlen (u->purpose), r, u->ready);
      }  else
         snprintf (unit_answer, LEN_RECD, "FUNC head   (%2d) : []                     []         0[]                                          -", i);
   }
   else if (strcmp (a_question, "entry"     )     == 0) {
      poly_func_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->work != NULL)  snprintf (unit_answer, LEN_RECD, "FUNC entry  (%2d) : %-22.22s %3d  %c  work   %3d  %3d", i, t, u->line, u->type, u->WORK_BEG, u->WORK_END);
         else                  snprintf (unit_answer, LEN_RECD, "FUNC entry  (%2d) : %-22.22s %3d  %c  non      -    -", i, t, u->line, u->type);
      } else                   snprintf (unit_answer, LEN_RECD, "FUNC entry  (%2d) : %-22.22s   -  -  -        -    -", i, t);
   }
   else if (strcmp (a_question, "stats"     )     == 0) {
      poly_func_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->work != NULL) {
            if (u->WORK_BEG    >= 0)  sprintf  (r, "%3d",     u->WORK_BEG);
            if (u->WORK_END    >= 0)  sprintf  (s, "%3d",     u->WORK_END);
            if (u->WORK_LVARS  >  0)  sprintf  (q, "%3d",     u->WORK_LVARS );
         }
         snprintf (unit_answer, LEN_RECD, "FUNC stats  (%2d) : %-22.22s     ·   · %3d   %3d %3d %3d %3d %3d %3d   %3d %s %s %s", i, t, u->COUNT_YLIBS, u->COUNT_LINES, u->COUNT_EMPTY, u->COUNT_DOCS, u->COUNT_DEBUG, u->COUNT_CODE, u->COUNT_SLOCL, u->line, r, s, q);
      }  else
         snprintf (unit_answer, LEN_RECD, "FUNC stats  (%2d) : %-22.22s     ·   ·   -     -   -   -   -   -   -     -   -   -   -", i, t);
   }
   else if (strcmp (a_question, "units"     )     == 0) {
      poly_func_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->work != NULL) {
            if (u->WORK_TUNIT  >  0)  sprintf  (r, "%3d",     u->WORK_TUNIT);
            if (u->WORK_SUNIT  >  0)  sprintf  (s, "%3d",     u->WORK_SUNIT);
            if (u->WORK_NUNIT  >  0)  sprintf  (q, "%3d",     u->WORK_NUNIT );
         }
      }
      snprintf (unit_answer, LEN_RECD, "FUNC units  (%2d) : %-22.22s       %su   %ss   %sn", i, t, r, s, q);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

