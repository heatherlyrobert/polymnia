/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*====================------------------------------------====================*/
/*===----                       tag working area                       ----===*/
/*====================------------------------------------====================*/
static void  o___WORK_AREA_______o () { return; }



/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_ylib__wipe         (tYLIB *a_dst)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(call)---------------------------*/
   a_dst->name [0] = '\0';
   a_dst->line     = -1;
   /*---(pointers)-----------------------*/
   a_dst->tag      = NULL;
   a_dst->tprev    = NULL;
   a_dst->tnext    = NULL;
   a_dst->ylib     = NULL;
   a_dst->eprev    = NULL;
   a_dst->enext    = NULL;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

tYLIB*
poly_ylib_new           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tYLIB      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tYLIB *) malloc (sizeof (tYLIB));
      if (x_tries > 10)   break;
   }
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return NULL;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("wipe clean");
   poly_ylib__wipe (x_new);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return x_new;
}

char
poly_ylib_add           (tTAG *a_tag, tEXTERN *a_extern, int a_line, tYLIB **a_ylib)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tYLIB      *x_new       = NULL;
   int         x_tries     =    0;
   int         x_len       =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (a_ylib != NULL)  *a_ylib = NULL;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_tag"    , a_tag);
   --rce;  if (a_tag == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("->name"   , a_tag->name);
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
   x_new = poly_ylib_new ();
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   strlcpy (x_new->name, a_extern->name, LEN_NAME);
   x_new->line   = a_line;
   /*---(into tags list)-----------------*/
   DEBUG_DATA   yLOG_note    ("tags list");
   rc = poly_tags_addylib (a_tag, x_new);
   DEBUG_DATA   yLOG_value   ("addylib"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(into extern list)---------------*/
   DEBUG_DATA   yLOG_note    ("extern list");
   rc = poly_extern_addylib (a_extern, x_new);
   DEBUG_DATA   yLOG_value   ("addylib"   , rc);
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
poly_ylib_del           (tYLIB *a_ylib)
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
   /*---(out of tag linked list)---------*/
   DEBUG_DATA   yLOG_note    ("unlink");
   DEBUG_DATA   yLOG_note    (a_ylib->tag->name);
   if (a_ylib->tnext != NULL)   a_ylib->tnext->tprev = a_ylib->tprev;
   else                         a_ylib->tag->tail    = a_ylib->tprev;
   if (a_ylib->tprev != NULL)   a_ylib->tprev->tnext = a_ylib->tnext;
   else                         a_ylib->tag->head    = a_ylib->tnext;
   /*---(update count)-------------------*/
   --(a_ylib->tag->count);
   DEBUG_DATA   yLOG_value   ("count"     , a_ylib->tag->count);
   /*---(out of extern list)-------------*/
   DEBUG_DATA   yLOG_note    ("unlink");
   DEBUG_DATA   yLOG_note    (a_ylib->ylib->name);
   if (a_ylib->enext != NULL)   a_ylib->enext->eprev = a_ylib->eprev;
   else                         a_ylib->ylib->tail   = a_ylib->eprev;
   if (a_ylib->eprev != NULL)   a_ylib->eprev->enext = a_ylib->enext;
   else                         a_ylib->ylib->head   = a_ylib->enext;
   /*---(update count)-------------------*/
   --(a_ylib->ylib->count);
   DEBUG_DATA   yLOG_value   ("count"     , a_ylib->ylib->count);
   /*---(free main)----------------------*/
   DEBUG_DATA   yLOG_note    ("free");
   free (a_ylib);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_ylib_purge_tag     (tTAG *a_tag)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tYLIB      *x_ylib      = NULL;
   tYLIB      *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_tag"    , a_tag);
   --rce;  if (a_tag == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk-through)-------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_tag->count);
   x_ylib = a_tag->head;
   while (x_ylib != NULL) {
      x_next = x_ylib->tnext;
      DEBUG_DATA   yLOG_point   ("x_ylib"    , x_ylib);
      DEBUG_DATA   yLOG_info    ("->name"    , x_ylib->name);
      rc = poly_ylib_del (x_ylib);
      x_ylib = x_next;
   }
   /*---(check)--------------------------*/
   DEBUG_DATA   yLOG_value   ("->count"   , a_tag->count);
   --rce;  if (a_tag->count > 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}


