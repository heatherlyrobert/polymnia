/*============================----beg-of-source---============================*/
#include  "polymnia.h"


int g_nylib = 0;;



/*====================------------------------------------====================*/
/*===----                       small supports                         ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_ylib__wipe         (tYLIB *a_dst)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_snote   (__FUNCTION__);
   /*---(call)---------------------------*/
   a_dst->name [0] = '\0';
   a_dst->line     = -1;
   /*---(pointers)-----------------------*/
   a_dst->func     = NULL;
   a_dst->f_prev   = NULL;
   a_dst->f_next   = NULL;
   a_dst->ylib     = NULL;
   a_dst->e_prev   = NULL;
   a_dst->e_next   = NULL;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----               memory allocation/deallocation                 ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
poly_ylib_new           (tYLIB **a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tYLIB      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_new);
   --rce;  if (a_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_new);
   --rce;  if (*a_new != NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tYLIB *) malloc (sizeof (tYLIB));
      if (x_tries > 3)   break;
   }
   DEBUG_DATA   yLOG_sint    (x_tries);
   DEBUG_DATA   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   poly_ylib__wipe (x_new);
   ++g_nylib;
   /*---(save)---------------------------*/
   *a_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_ylib__free         (tYLIB **a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tYLIB      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_old);
   --rce;  if (*a_old == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(free memory)--------------------*/
   free (*a_old);
   --g_nylib;
   /*---(ground pointer)-----------------*/
   *a_old = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   hooking and unhooking                      ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

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
   /*---(into linked list)---------------*/
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
   /*---(ground external)----------------*/
   a_ylib->ylib = NULL;
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
   poly_ylib_new (&x_new);
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
poly_ylib_del           (tYLIB **a_ylib)
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
poly_ylib_purge_func    (tFUNC *a_func)
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
      rc = poly_ylib_del (&x_ylib);
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
            sprintf  (s, "[%2d:%.15s]", x_func->y_head->line, x_func->y_head->name);
            sprintf  (r, "[%2d:%.15s]", x_func->y_tail->line, x_func->y_tail->name);
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
            sprintf  (s, "[%2d:%.15s]", x_ext->y_head->line, x_ext->y_head->func->name);
            sprintf  (r, "[%2d:%.15s]", x_ext->y_tail->line, x_ext->y_tail->func->name);
            c = x_ext->y_count;
            o = x_ext->y_head; while (o != NULL) { ++x_fore; o = o->e_next; }
            o = x_ext->y_tail; while (o != NULL) { ++x_back; o = o->e_prev; }
         }
         snprintf (unit_answer, LEN_RECD, "YLIB extern      : %-17.17s   %3dc %3df %3db   %-20.20s   %s",
               t, c, x_fore, x_back, s, r);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


