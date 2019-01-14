/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
#define     MAX_BTREE   20
typedef     struct      cROOTS      tROOTS;
struct      cROOTS {
   /*---(ref)---------------*/
   char        which;
   /*---(tree)--------------*/
   tBTREE     *head;
   tBTREE     *tail;
   tBTREE     *root;
   /*---(stats)-------------*/
   int         count;
   /*---(done)--------------*/
} s_trees [MAX_BTREE] = {
   { B_FILES , NULL, NULL, NULL, 0},
   { B_TAGS  , NULL, NULL, NULL, 0},
   { B_EXTERN, NULL, NULL, NULL, 0},
   { B_PROTO , NULL, NULL, NULL, 0},
   { B_UNIT  , NULL, NULL, NULL, 0},
   { 0       , NULL, NULL, NULL, 0},
};



/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
#define     B_HEAD      s_trees [n].head
#define     B_TAIL      s_trees [n].tail
#define     B_ROOT      s_trees [n].root
#define     B_COUNT     s_trees [n].count



/*====================------------------------------------====================*/
/*===----                       support functions                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_btree__by_abbr     (char a_btree)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   switch (a_btree) {
   case B_FILES  :  return 0;
   case B_TAGS   :  return 1;
   case B_EXTERN :  return 2;
   case B_PROTO  :  return 3;
   case B_UNIT   :  return 4;
   default       :  return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_btree_create       (char a_btree, void *a_data, char *a_sort)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        n           =   -1;
   tBTREE     *x_new       = NULL;
   int         x_tries     =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_schar   (a_btree);
   n = poly_btree__by_abbr   (a_btree);
   DEBUG_DATA   yLOG_sint    (n);
   --rce;  if (n < 0) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_data);
   --rce;  if (a_data == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_sort);
   --rce;  if (a_sort == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tBTREE *) malloc (sizeof (tBTREE));
      if (x_tries > 10)   break;
   }
   DEBUG_DATA   yLOG_sint    (x_tries);
   DEBUG_DATA   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   DEBUG_DATA   yLOG_snote   ("data");
   x_new->sort   = a_sort;
   x_new->data   = a_data;
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_snote   ("link");
   x_new->next    = NULL;
   x_new->prev    = NULL;
   x_new->left    = NULL;
   x_new->right   = NULL;
   if (B_HEAD == NULL) {
      B_HEAD = B_TAIL = x_new;
   } else {
      x_new->prev  = B_TAIL;
      B_TAIL->next = x_new;
      B_TAIL       = x_new;
   }
   /*---(update count)-------------------*/
   ++B_COUNT;
   DEBUG_DATA   yLOG_sint    (B_COUNT);
   DEBUG_DATA   yLOG_snote   ("successful");
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_btree__destroy     (int n, tBTREE *a_old)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(beginning)----------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   DEBUG_DATA   yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(out of linked list)-------------*/
   DEBUG_DATA   yLOG_snote   ("unlink");
   if (a_old->next != NULL)   a_old->next->prev = a_old->prev;
   else                       B_TAIL            = a_old->prev;
   if (a_old->prev != NULL)   a_old->prev->next = a_old->next;
   else                       B_HEAD            = a_old->next;
   /*---(update count)-------------------*/
   --B_COUNT;
   DEBUG_DATA   yLOG_sint    (B_COUNT);
   /*---(free main)----------------------*/
   DEBUG_DATA   yLOG_snote   ("free");
   free (a_old);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_btree_purge        (char a_btree)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =   -1;
   char        rc          =    0;
   tBTREE     *x_curr      = NULL;
   tBTREE     *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_schar   (a_btree);
   n = poly_btree__by_abbr   (a_btree);
   DEBUG_DATA   yLOG_sint    (n);
   --rce;  if (n < 0) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk through list)--------------*/
   x_next = B_HEAD;
   DEBUG_DATA   yLOG_spoint  (B_HEAD);
   while (x_next != NULL) {
      x_curr = x_next;
      x_next = x_curr->next;
      rc = poly_btree__destroy (n, x_curr);
   }
   DEBUG_DATA   yLOG_sint    (B_COUNT);
   --rce;  if (B_COUNT > 0) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(clean ends)---------------------*/
   B_HEAD = NULL;
   B_TAIL = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          sorting                             ----===*/
/*====================------------------------------------====================*/
static void  o___SORT____________o () { return; }

static  s_swaps      = 0;
static  s_comps      = 0;
static  s_teles      = 0;

char
poly_btree__swap        (int n, tBTREE *a_one, tBTREE *a_two)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   /*---(beginning)----------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   DEBUG_DATA   yLOG_spoint  (a_one);
   --rce;  if (a_one == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_two);
   --rce;  if (a_two == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_one == a_two) {
      DEBUG_DATA   yLOG_snote   ("same, no action");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(cut two from list)--------------*/
   DEBUG_DATA   yLOG_snote   ("unlink");
   if (a_two->next != NULL)   a_two->next->prev = a_two->prev;
   else                       B_TAIL            = a_two->prev;
   if (a_two->prev != NULL)   a_two->prev->next = a_two->next;
   else                       B_HEAD            = a_two->next;
   /*---(insert before one)--------------*/
   DEBUG_DATA   yLOG_snote   ("insert");
   if (a_one->prev != NULL)   a_one->prev->next = a_two;
   else                       B_HEAD            = a_two;
   a_two->prev = a_one->prev;
   a_two->next = a_one;
   a_one->prev = a_two;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_btree_dgnome       (char a_btree)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =   -1;
   int         x_match     =    0;
   char        x_flag      =  '-';
   tBTREE     *p           = NULL;          /* main index                     */
   tBTREE     *t           = NULL;          /* teleport point                 */
   tBTREE     *o           = NULL;          /* origin point                   */
   char        x_swap      =  '-';
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_char    ("a_btree"   , a_btree);
   n = poly_btree__by_abbr   (a_btree);
   DEBUG_DATA   yLOG_value   ("a_btree"   , n);
   --rce;  if (n < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check list)---------------------*/
   DEBUG_SORT   yLOG_point   ("head"      , B_HEAD);
   --rce;  if (B_HEAD == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SORT   yLOG_point   ("->next"    , B_HEAD->next);
   --rce;  if (B_HEAD->next == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   o   = B_HEAD->next;
   if (o != NULL) {
      p = o->prev;
      t = o->next;
   }
   /*---(do the gnome walk)--------------*/
   while (o != NULL) {
      /*---(beginning)-------------------*/
      if (p == NULL) {
         DEBUG_SORT   yLOG_note    ("bounce off beginning");
         if (x_swap == 'y') {
            ++s_swaps;
            poly_btree__swap (n, B_HEAD, o);
            x_swap = '-';
         }
         ++s_teles;
         o = t;
         if (o != NULL) {
            p = o->prev;
            t = o->next;
         }
         continue;
      }
      /*---(compare)---------------------*/
      ++s_comps;
      x_match = strcmp (p->sort, o->sort);
      x_flag  = (x_match <= 0) ? 'y' : '#';
      DEBUG_SORT   yLOG_complex ("compare"   , "%-20.20s v %-20.20s   %c %4d   %4d %4d %4d", p->sort, o->sort, x_flag, x_match, s_comps, s_teles, s_swaps);
      if (x_match <= 0) {
         if (x_swap == 'y') {
            ++s_swaps;
            poly_btree__swap (n, p->next, o);
            x_swap = '-';
         }
         ++s_teles;
         o = t;
         if (o != NULL) {
            p = o->prev;
            t = o->next;
         }
         continue;
      }
      /*---(swap)------------------------*/
      x_swap = 'y';
      p = p->prev;
      /*---(next)------------------------*/
   }
   DEBUG_SORT   yLOG_value   ("size"       , B_COUNT);
   DEBUG_SORT   yLOG_value   ("compares"   , s_comps);
   DEBUG_SORT   yLOG_value   ("teleports"  , s_teles);
   DEBUG_SORT   yLOG_value   ("swaps"      , s_swaps);
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        searching                             ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int 
poly_btree__depth       (int a_size)
{
   int         c           =    0;
   if (a_size <= 0)  return 0;
   while (a_size > 1) {
      a_size /= 2;
      ++c;
   }
   ++c;
   return c;
}

int 
poly_btree__span        (int a_levels)
{
   if (a_levels <= 0)  return 0;
   return pow (2, a_levels) - 1;
}

tEXTERN*
poly_btree__nextlevel   (int n, int a_lvl, int a_pos, int a_dist, char a_dir, tEXTERN *a_node)
{
   /*---(locals)-----------+-----+-----+-*/
   tBTREE     *x_node      = NULL;
   int         x_pos       =    0;
   int         c           =    0;
   /*---(pre-defense)--------------------*/
   if (a_dist == 0)   return NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(check new position)-------------*/
   x_node = a_node;
   switch (a_dir) {
   case 'L' :
      x_pos = a_pos - a_dist;
      if (x_pos <= 0) {
         DEBUG_DATA   yLOG_note    ("too far left, skip level");
         x_node = poly_btree__nextlevel (n, a_lvl, a_pos, a_dist / 2, 'L', x_node);
         DEBUG_DATA   yLOG_exit    (__FUNCTION__);
         return x_node;
      }
      break;
   case 'R' :
      x_pos = a_pos + a_dist;
      if (x_pos > B_COUNT) {
         DEBUG_DATA   yLOG_note    ("too far right, skip level");
         x_node = poly_btree__nextlevel (n, a_lvl, a_pos, a_dist / 2, 'R', x_node);
         DEBUG_DATA   yLOG_exit    (__FUNCTION__);
         return x_node;
      }
      break;
   default  :
      DEBUG_DATA   yLOG_note    ("a_dir not LR, skipping");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return NULL;
      break;
   }
   /*---(get to new node)----------------*/
   while (c < a_dist) {
      if (a_dir == 'L')   x_node = x_node->prev;
      if (a_dir == 'R')   x_node = x_node->next;
      ++c;
   }
   /*---(recurse)------------------------*/
   DEBUG_DATA   yLOG_complex ("a_btree"   , "%2d %c %4d %4d %s", a_lvl, a_dir, a_dist, x_pos, x_node->sort);
   x_node->left  = poly_btree__nextlevel (n, a_lvl + 1, x_pos, a_dist / 2, 'L', x_node);
   x_node->right = poly_btree__nextlevel (n, a_lvl + 1, x_pos, a_dist / 2, 'R', x_node);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return x_node;
}

char
poly_btree_build        (char a_btree)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tBTREE     *x_node      = NULL;
   int         x_lvl       =    0;
   int         x_span      =    0;
   int         x_ctr       =    0;
   int         c           =    0;
   int         n           =  -1;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_char    ("a_btree"   , a_btree);
   n = poly_btree__by_abbr   (a_btree);
   DEBUG_DATA   yLOG_value   ("a_btree"   , n);
   --rce;  if (n < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_lvl  = poly_btree__depth (B_COUNT);
   DEBUG_DATA   yLOG_value   ("est depth" , x_lvl);
   x_span = poly_btree__span (x_lvl);
   DEBUG_DATA   yLOG_value   ("max span"  , x_span);
   DEBUG_DATA   yLOG_double  ("est usage" , B_COUNT / 2.0 + 1);
   x_ctr  = (B_COUNT / 2) + 1;
   DEBUG_DATA   yLOG_value   ("center"    , x_ctr);
   B_ROOT = B_HEAD;
   c = 1;
   while (c < x_ctr) {
      B_ROOT = B_ROOT->next;
      ++c;
   }
   DEBUG_DATA   yLOG_info    ("ROOT"      , B_ROOT->sort);
   B_ROOT->left  = poly_btree__nextlevel (n, 1, x_ctr, x_span / 4 + 1, 'L', B_ROOT);
   B_ROOT->right = poly_btree__nextlevel (n, 1, x_ctr, x_span / 4 + 1, 'R', B_ROOT);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_btree__display   (int a_lvl, tBTREE *a_node)
{
   char        x_pre       [LEN_RECD] = "";
   int         i           =    0;
   if (a_node == NULL)  return 0;
   if (a_lvl > 20)      return 0;
   for (i = 0; i < a_lvl; ++i)  strcat (x_pre, "  ");
   poly_btree__display (a_lvl + 1, a_node->left);
   printf ("%s%s\n", x_pre, a_node->sort);
   poly_btree__display (a_lvl + 1, a_node->right);
   return 0;
}

char
poly_btree_list         (char a_btree)
{
   char        rce         =  -10;
   int         n           =   -1;
   n = poly_btree__by_abbr   (a_btree);
   --rce;  if (n < 0)  return rce;
   poly_btree__display (0, B_ROOT);
   return 0;
}

tBTREE*
poly_btree__searchdown  (tBTREE *a_node, char *a_dir, char *a_name)
{
   int         rc          =    0;
   if (a_node == NULL)  return NULL;
   ++g_depth;
   strlcat (g_path, a_dir, LEN_LABEL);
   rc = strcmp  (a_node->sort, a_name);
   DEBUG_SORT   yLOG_complex ("compare"   , "%s  %-20.20s  %4d", a_dir, a_node->sort, rc);
   if (rc >  0)  return poly_btree__searchdown (a_node->left , "L", a_name);
   if (rc <  0)  return poly_btree__searchdown (a_node->right, "R", a_name);
   return a_node;
}

void*   
poly_btree_search       (char a_btree, char *a_name)
{
   char        rce         =  -10;
   int         n           =   -1;
   tBTREE     *x_node      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_char    ("a_btree"   , a_btree);
   n = poly_btree__by_abbr   (a_btree);
   DEBUG_DATA   yLOG_value   ("a_btree"   , n);
   --rce;  if (n < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   g_depth = 0;
   strlcpy (g_path, "", LEN_LABEL);
   x_node = poly_btree__searchdown (B_ROOT, "@", a_name);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return x_node->data;
}




/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_btree__unit        (char a_btree, char *a_question, int i)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =   -1;
   tBTREE     *u           = NULL;
   int         c           =    0;
   char        t           [LEN_RECD]  = "[]";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "EXTERN unit      : tag number unknown");
   n = poly_btree__by_abbr   (a_btree);
   --rce;  if (n < 0)  return rce;
   if (i <  0)       return unit_answer;
   u = B_HEAD;
   while (c < i) {
      if (u == NULL)  break;
      u = u->next;
      ++c;
   }
   /*---(simple)-------------------------*/
   if (u != NULL) sprintf  (t, "[%.20s]", u->sort);
   if        (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "BTREE count      : %3d", B_COUNT);
   }
   else if   (strcmp (a_question, "entry"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "BTREE entry (%2d) : %s", i, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
