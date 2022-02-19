/*============================----beg-of-source---============================*/
#include  "polymnia.h"


static char   s_print         [LEN_RECD] = "";
int g_nylib = 0;;



/*====================------------------------------------====================*/
/*===----                       small supports                         ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_ylib__wipe         (tYLIB *a_ylib)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_snote   (__FUNCTION__);
   /*---(call)---------------------------*/
   a_ylib->name [0] = '\0';
   a_ylib->line     = -1;
   /*---(pointers)-----------------------*/
   a_ylib->func     = NULL;
   a_ylib->f_prev   = NULL;
   a_ylib->f_next   = NULL;
   a_ylib->ylib     = NULL;
   a_ylib->e_prev   = NULL;
   a_ylib->e_next   = NULL;
   /*---(complete)-----------------------*/
   return 1;
}

char*
poly_ylib__memory       (tYLIB *a_ylib)
{
   /*---(master)-------------------------*/
   strlcpy (s_print, "["  , LEN_RECD);
   poly_shared__check_str  (s_print, a_ylib->name);
   poly_shared__check_num  (s_print, a_ylib->line);
   poly_shared__spacer     (s_print);
   poly_shared__check_ptr  (s_print, a_ylib->func);
   poly_shared__check_ptr  (s_print, a_ylib->f_prev);
   poly_shared__check_ptr  (s_print, a_ylib->f_next);
   poly_shared__spacer     (s_print);
   poly_shared__check_ptr  (s_print, a_ylib->ylib);
   poly_shared__check_ptr  (s_print, a_ylib->e_prev);
   poly_shared__check_ptr  (s_print, a_ylib->e_next);
   strlcat (s_print, "]" , LEN_RECD);
   /*---(complete)-----------------------*/
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char poly_ylib__new  (tYLIB **a_new) { return poly_shared_new  ("ylib", sizeof (tYLIB), a_new, &g_nylib, '-', poly_ylib__wipe); }
char poly_ylib_force (tYLIB **a_new) { return poly_shared_new  ("ylib", sizeof (tYLIB), a_new, &g_nylib, 'y', poly_ylib__wipe); }
char poly_ylib__free (tYLIB **a_old) { return poly_shared_free ("ylib", a_old, &g_nylib); }



/*====================------------------------------------====================*/
/*===----                   hooking and unhooking                      ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

#define    S_NAME      a_ylib->name
#define    S_PARENT    a_func
#define    S_OWNER     a_ylib->func
#define    S_HEAD      a_ylib->func->y_head
#define    S_TAIL      a_ylib->func->y_tail
#define    S_TNEXT     a_ylib->func->y_tail->f_next
#define    S_PREV      a_ylib->f_prev
#define    S_PNEXT     (a_ylib->f_prev == NULL) ? NULL : a_ylib->f_prev->f_next
#define    S_NEXT      a_ylib->f_next
#define    S_NPREV     (a_ylib->f_next == NULL) ? NULL : a_ylib->f_next->f_prev
#define    S_COUNT     &(a_ylib->func->y_count)
#define    S_COUNTA    &(a_ylib->func->file->proj->COUNT_YLIBS)
#define    S_COUNTB    &(a_ylib->func->file->COUNT_YLIBS)
#define    S_COUNTC    &(a_ylib->func->COUNT_YLIBS)

/*> poly_shared_hook        (char *a_terse, char *a_name, void *a_here, void *a_parent, void *a_owner, void *a_head, void *a_tail, void *a_prev, void *a_tnext, int *a_count, int *a_counta, int *a_countb, int *a_countc)   <*/

/*> char poly_ylib__fhook   (tFUNC *a_func, tYLIB *a_ylib) { a_ylib->func = a_func;  return poly_shared_hook   ("ylib", S_NAME, a_ylib, S_PARENT, S_OWNER, S_HEAD, S_TAIL, S_PREV, S_TNEXT, S_COUNT, S_COUNTA, S_COUNTB, S_COUNTC); }   <* 
 *> char poly_ylib__funhook (tYLIB *a_ylib) { return poly_shared_unhook ("ylib", S_NAME, a_ylib, S_OWNER, S_HEAD, S_TAIL, S_PREV, S_PNEXT, S_NEXT, S_NPREV, S_COUNT, S_COUNTA, S_COUNTB, S_COUNTC); }                                   <*/


char
poly_ylib__fhook        (tFUNC *a_func, tYLIB *a_ylib)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_ylib);
   --rce;  if (a_ylib == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_ylib->func);
   --rce;  if (a_ylib->func != NULL) {
      DEBUG_DATA   yLOG_snote   ("already hooked");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_func->name);
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_sint    (a_func->y_count);
   DEBUG_DATA   yLOG_spoint  (a_func->y_head);
   DEBUG_DATA   yLOG_spoint  (a_func->y_tail);
   if (a_func->y_head  == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      a_func->y_head  = a_func->y_tail  = a_ylib;
   } else {
      DEBUG_DATA   yLOG_snote   ("append");
      a_ylib->f_prev         = a_func->y_tail;
      a_func->y_tail->f_next = a_ylib;
      a_func->y_tail         = a_ylib;
   }
   /*---(parent pointer)-----------------*/
   a_ylib->func  = a_func;
   /*---(function counts)----------------*/
   ++(a_func->y_count);
   DEBUG_DATA   yLOG_sint    (a_func->y_count);
   /*---(global counts)------------------*/
   ++(my.COUNT_YLIBS);
   ++(a_func->file->proj->COUNT_YLIBS);
   ++(a_func->file->COUNT_YLIBS);
   ++(a_func->COUNT_YLIBS);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_ylib__funhook      (tYLIB *a_ylib)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFUNC      *x_func      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_ylib);
   --rce;  if (a_ylib == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_ylib->func);
   --rce;  if (a_ylib->func == NULL) {
      DEBUG_DATA   yLOG_snote   ("not presently hooked");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_func = a_ylib->func;
   DEBUG_DATA   yLOG_snote   (x_func->name);
   /*---(out of linked list)-------------*/
   DEBUG_DATA   yLOG_sint    (x_func->y_count);
   DEBUG_DATA   yLOG_spoint  (x_func->y_head);
   DEBUG_DATA   yLOG_spoint  (x_func->y_tail);
   if (a_ylib->f_next != NULL)  a_ylib->f_next->f_prev = a_ylib->f_prev;
   else                         x_func->y_tail         = a_ylib->f_prev;
   if (a_ylib->f_prev != NULL)  a_ylib->f_prev->f_next = a_ylib->f_next;
   else                         x_func->y_head         = a_ylib->f_next;
   /*---(function counts)----------------*/
   --(x_func->y_count);
   DEBUG_DATA   yLOG_sint    (x_func->y_count);
   /*---(global counts)------------------*/
   --(my.COUNT_YLIBS);
   --(x_func->file->proj->COUNT_YLIBS);
   --(x_func->file->COUNT_YLIBS);
   --(x_func->COUNT_YLIBS);
   /*---(ground function)----------------*/
   a_ylib->func = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_ylib__ehook        (tEXTERN *a_ext, tYLIB *a_ylib)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_ext);
   --rce;  if (a_ext == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_ext->name);
   DEBUG_DATA   yLOG_spoint  (a_ylib);
   --rce;  if (a_ylib == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_ylib->ylib);
   --rce;  if (a_ylib->ylib != NULL) {
      DEBUG_DATA   yLOG_snote   ("already hooked");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(into linked list)---------------*/
   /*> printf ("hook   %-10p %-15.15s %3dc %-10ph %-10pt\n", a_ext, a_ext->name, a_ext->y_count, a_ext->y_head, a_ext->y_tail);   <*/
   DEBUG_DATA   yLOG_sint    (a_ext->y_count);
   DEBUG_DATA   yLOG_spoint  (a_ext->y_head);
   DEBUG_DATA   yLOG_spoint  (a_ext->y_tail);
   if (a_ext->y_head  == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      a_ext->y_head  = a_ext->y_tail  = a_ylib;
   } else {
      DEBUG_DATA   yLOG_snote   ("append");
      a_ylib->e_prev        = a_ext->y_tail;
      a_ext->y_tail->e_next = a_ylib;
      a_ext->y_tail         = a_ylib;
   }
   /*---(parent pointer)-----------------*/
   a_ylib->ylib  = a_ext;
   /*---(external counts)----------------*/
   ++(a_ext->y_count);
   DEBUG_DATA   yLOG_sint    (a_ext->y_count);
   DEBUG_DATA   yLOG_spoint  (a_ext->y_head);
   DEBUG_DATA   yLOG_spoint  (a_ext->y_tail);
   /*> printf ("                                  %3dc %-10ph %-10pt\n", a_ext->y_count, a_ext->y_head, a_ext->y_tail);   <*/
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_ylib__eunhook      (tYLIB *a_ylib)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tEXTERN    *x_ext       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_ylib);
   --rce;  if (a_ylib == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_ylib->ylib);
   --rce;  if (a_ylib->ylib == NULL) {
      DEBUG_DATA   yLOG_snote   ("not presently hooked");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_ext  = a_ylib->ylib;
   DEBUG_DATA   yLOG_snote   (x_ext->name);
   /*---(out of linked list)-------------*/
   /*> printf ("unhook %-10p %-15.15s %3dc %-10ph %-10pt\n", x_ext, x_ext->name, x_ext->y_count, x_ext->y_head, x_ext->y_tail);   <*/
   DEBUG_DATA   yLOG_sint    (x_ext->y_count);
   DEBUG_DATA   yLOG_spoint  (x_ext->y_head);
   DEBUG_DATA   yLOG_spoint  (x_ext->y_tail);
   if (a_ylib->e_next != NULL)  a_ylib->e_next->e_prev = a_ylib->e_prev;
   else                         a_ylib->ylib->y_tail   = a_ylib->e_prev;
   if (a_ylib->e_prev != NULL)  a_ylib->e_prev->e_next = a_ylib->e_next;
   else                         a_ylib->ylib->y_head   = a_ylib->e_next;
   /*---(external counts)----------------*/
   --(x_ext->y_count);
   DEBUG_DATA   yLOG_sint    (x_ext->y_count);
   DEBUG_DATA   yLOG_spoint  (x_ext->y_head);
   DEBUG_DATA   yLOG_spoint  (x_ext->y_tail);
   /*---(ground external)----------------*/
   /*> printf ("                                  %3dc %-10ph %-10pt\n", x_ext->y_count, x_ext->y_head, x_ext->y_tail);   <*/
   a_ylib->ylib   = NULL;
   a_ylib->e_next = NULL;
   a_ylib->e_prev = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    memory allocation                         ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_ylib_add           (tFUNC *a_func, tEXTERN *a_extern, int a_line, tYLIB **a_ylib)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tYLIB      *x_new       = NULL;
   int         x_len       =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (a_ylib != NULL)  *a_ylib = NULL;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_func"   , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("->name"   , a_func->name);
   DEBUG_DATA   yLOG_point   ("a_extern" , a_extern);
   --rce;  if (a_extern == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("->name"   , a_extern->name);
   DEBUG_DATA   yLOG_value   ("a_line"    , a_line);
   --rce;  if (a_line <= 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_ylib"    , a_ylib);
   /*---(create cell)--------------------*/
   poly_ylib__new (&x_new);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   strlcpy (x_new->name, a_extern->name, LEN_TITLE);
   x_new->line   = a_line;
   /*---(into function list)-------------*/
   DEBUG_DATA   yLOG_note    ("hook");
   rc = poly_ylib__fhook (a_func, x_new);
   DEBUG_DATA   yLOG_value   ("fhook"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(into extern list)---------------*/
   rc = poly_ylib__ehook (a_extern, x_new);
   DEBUG_DATA   yLOG_value   ("ehook"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   if (a_ylib != NULL)  *a_ylib = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_ylib_remove        (tYLIB **a_ylib)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(beginning)----------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_ylib"     , a_ylib);
   --rce;  if (a_ylib == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*a_ylib"    , *a_ylib);
   --rce;  if (*a_ylib == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove from function)-----------*/
   rc = poly_ylib__funhook (*a_ylib);
   DEBUG_DATA   yLOG_value   ("funhook"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove from external)-----------*/
   rc = poly_ylib__eunhook (*a_ylib);
   DEBUG_DATA   yLOG_value   ("eunhook"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free)---------------------------*/
   rc = poly_ylib__free    (a_ylib);
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
/*===----                       program-level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_ylib_purge         (tFUNC *a_func, char a_update)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tYLIB      *x_ylib      = NULL;
   tYLIB      *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_func"   , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk-through)-------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_func->y_count);
   x_ylib = a_func->y_head;
   while (x_ylib != NULL) {
      x_next = x_ylib->f_next;
      DEBUG_DATA   yLOG_point   ("x_ylib"    , x_ylib);
      DEBUG_DATA   yLOG_info    ("->name"    , x_ylib->name);
      rc = poly_ylib_remove (&x_ylib);
      x_ylib = x_next;
   }
   /*---(check)--------------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_func->y_count);
   --rce;  if (a_func->y_count > 0) {
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

int  poly_ylib_count         (void)                          { return ySORT_count     (B_FILES); }
char poly_ylib_by_name       (uchar *a_name, tYLIB **a_ylib) { return ySORT_by_name   (B_FILES, a_name, a_ylib); }
char poly_ylib_by_index      (int n, tYLIB **a_ylib)         { return ySORT_by_index  (B_FILES, n, a_ylib); }
char poly_ylib_by_cursor     (char a_dir, tYLIB **a_ylib)    { return ySORT_by_cursor (B_FILES, a_dir, a_ylib); }

char
poly_ylib_by_func_index (tFUNC *a_func, int n, tYLIB **r_ylib)
{
   char        rce         =  -10;
   tYLIB      *x_ylib      = NULL;
   int         c           =    0;
   --rce;  if (a_func == NULL)   return rce;
   --rce;  if (r_ylib == NULL)   return rce;
   *r_ylib = NULL;
   x_ylib = a_func->y_head;
   while (x_ylib != NULL) {
      if (c == n) {
         *r_ylib = x_ylib;
         return 0;
      }
      x_ylib = x_ylib->f_next;
      ++c;
   }
   --rce;  return rce;
}

char
poly_ylib_use_by_index  (char *a_name, int n, tYLIB **r_ylib)
{
   char        rce         =  -10;
   tEXTERN    *x_ext       = NULL;
   tYLIB      *x_ylib      = NULL;
   int         c           =    0;
   if (r_ylib != NULL)  *r_ylib = NULL;
   --rce;  if (a_name == NULL)   return rce;
   --rce;  if (r_ylib == NULL)   return rce;
   poly_extern_by_name (a_name, &x_ext);
   --rce;  if (r_ylib == NULL)   return rce;
   x_ylib = x_ext->y_head;
   while (x_ylib != NULL) {
      if (c == n) {
         *r_ylib = x_ylib;
         return 0;
      }
      x_ylib = x_ylib->e_next;
      ++c;
   }
   --rce;  return rce;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_ylib__unit         (char *a_question, char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   char        s           [LEN_RECD] = "[]";
   char        r           [LEN_RECD] = "[]";
   tFUNC      *x_func      = NULL;
   tEXTERN    *x_ext       = NULL;
   tYLIB      *o           = NULL;
   int         c           =    0;
   int         x_fore      =    0;
   int         x_back      =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FILE unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "func"      )     == 0) {
      poly_func_by_name  (a_name, &x_func);
      if (x_func == NULL)  snprintf (unit_answer, LEN_RECD, "YLIB func        : function not found    -c   -f   -b   []                     []");
      else {
         sprintf  (t, "[%.15s]", x_func->name);
         if (x_func->y_head != NULL) {
            sprintf  (s, "[%02d:%.15s]", x_func->y_head->line, x_func->y_head->name);
            sprintf  (r, "[%02d:%.15s]", x_func->y_tail->line, x_func->y_tail->name);
            c = x_func->y_count;
            o = x_func->y_head; while (o != NULL) { ++x_fore; o = o->f_next; }
            o = x_func->y_tail; while (o != NULL) { ++x_back; o = o->f_prev; }
         }
         snprintf (unit_answer, LEN_RECD, "YLIB func        : %-17.17s   %3dc %3df %3db   %-20.20s   %s",
               t, c, x_fore, x_back, s, r);
      }
   }
   if (strcmp (a_question, "extern"    )     == 0) {
      poly_extern_by_name  (a_name, &x_ext);
      if (x_ext  == NULL)  snprintf (unit_answer, LEN_RECD, "YLIB extern      : function not found    -c   -f   -b   []                     []");
      else {
         sprintf  (t, "[%.15s]", x_ext->name);
         if (x_ext->y_head != NULL) {
            sprintf  (s, "[%02d:%.15s]", x_ext->y_head->line, x_ext->y_head->func->name);
            sprintf  (r, "[%02d:%.15s]", x_ext->y_tail->line, x_ext->y_tail->func->name);
            c = x_ext->y_count;
            o = x_ext->y_head; while (o != NULL) { ++x_fore; o = o->e_next; }
            o = x_ext->y_tail; while (o != NULL) { ++x_back; o = o->e_prev; }
            snprintf (unit_answer, LEN_RECD, "YLIB extern      : %-17.17s  NOT null  %-10p %-10p", t, x_ext->y_head, x_ext->y_tail);
         /*> } else {                                                                                                                      <* 
          *>    snprintf (unit_answer, LEN_RECD, "YLIB extern      : %-17.17s  null      %-10p %-10p", t, x_ext->y_head, x_ext->y_tail);   <*/
         }
         snprintf (unit_answer, LEN_RECD, "YLIB extern      : %-17.17s   %3dc %3df %3db   %-20.20s   %s",
               t, c, x_fore, x_back, s, r);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


