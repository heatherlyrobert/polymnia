/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
typedef     struct      cEXTERN     tEXTERN;
struct      cEXTERN {
   /*---(information)-------*/
   char       *name;
   int         len;
   char        type;
   int         count;
   /*---(linked list)-------*/
   tEXTERN    *prev;
   tEXTERN    *next;
   /*---(searching)---------*/
   tEXTERN    *left;
   tEXTERN    *right;
   /*---(done)--------------*/
};
/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
static      tEXTERN    *s_head      = NULL;
static      tEXTERN    *s_tail      = NULL;
static      int         s_count     = 0;
static      tEXTERN    *s_root      = NULL;



/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

tEXTERN*
poly_extern__create      (char *a_name, char a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tEXTERN    *x_new       = NULL;
   int         x_tries     =    0;
   int         x_len       =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_len    = strlen (a_name);
   --rce;  if (x_len == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tEXTERN *) malloc (sizeof (tEXTERN));
      if (x_tries > 10)   break;
   }
   DEBUG_DATA   yLOG_sint    (x_tries);
   DEBUG_DATA   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   DEBUG_DATA   yLOG_snote   ("clear");
   x_new->name   = strdup (a_name);
   x_new->len    = x_len;
   x_new->type   = a_type;
   x_new->count  = 0;
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_snote   ("link");
   x_new->next    = NULL;
   x_new->prev    = NULL;
   x_new->left    = NULL;
   x_new->right   = NULL;
   if (s_head == NULL) {
      s_head = s_tail = x_new;
   } else {
      x_new->prev  = s_tail;
      s_tail->next = x_new;
      s_tail       = x_new;
   }
   /*---(update count)-------------------*/
   ++s_count;
   DEBUG_DATA   yLOG_sint    (s_count);
   DEBUG_DATA   yLOG_snote   ("successful");
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_extern__swap       (tEXTERN *a_one, tEXTERN *a_two)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEXTERN    *t           = NULL;
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
   else                       s_tail            = a_two->prev;
   if (a_two->prev != NULL)   a_two->prev->next = a_two->next;
   else                       s_head            = a_two->next;
   /*---(insert before one)--------------*/
   DEBUG_DATA   yLOG_snote   ("insert");
   if (a_one->prev != NULL)   a_one->prev->next = a_two;
   else                       s_head            = a_two;
   a_two->prev = a_one->prev;
   a_two->next = a_one;
   a_one->prev = a_two;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_extern__destroy     (tEXTERN *a_old)
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
   /*---(clear fields)-------------------*/
   if (a_old->name != NULL)  free (a_old->name);
   /*---(out of linked list)-------------*/
   DEBUG_DATA   yLOG_snote   ("unlink");
   if (a_old->next != NULL)   a_old->next->prev = a_old->prev;
   else                       s_tail            = a_old->prev;
   if (a_old->prev != NULL)   a_old->prev->next = a_old->next;
   else                       s_head            = a_old->next;
   /*---(update count)-------------------*/
   --s_count;
   DEBUG_DATA   yLOG_sint    (s_count);
   /*---(free main)----------------------*/
   DEBUG_DATA   yLOG_snote   ("free");
   free (a_old);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_extern_init        (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   /*---(initialize)---------------------*/
   DEBUG_PROG   yLOG_snote   ("pointers");
   s_head    = NULL;
   s_tail    = NULL;
   DEBUG_PROG   yLOG_snote   ("counts");
   s_count   = 0;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_extern_wrap        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEXTERN    *x_curr      = NULL;
   tEXTERN    *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(walk through list)--------------*/
   x_next = s_head;
   DEBUG_DATA   yLOG_spoint  (s_head);
   while (x_next != NULL) {
      x_curr = x_next;
      x_next = x_curr->next;
      rc = poly_extern__destroy (x_curr);
   }
   --rce;  if (s_count > 0) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(clean ends)---------------------*/
   s_head = NULL;
   s_tail = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        searching                             ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int 
poly_extern__sdepth     (int n)
{
   int         c           =    0;
   if (n <= 0)  return -1;
   while (n > 1) {
      n /= 2;
      ++c;
   }
   ++c;
   return c;
}

tEXTERN*
poly_extern__smake      (int a_lvl, int a_pos, int a_dist, char a_dir, tEXTERN *a_node)
{
   tEXTERN    *x_node      = NULL;
   char        x_pre       [LEN_RECD] = "";
   int         x_pos       =    0;
   int         c           =    0;
   int         i           =    0;
   for (i = 0; i < a_lvl; ++i)  strcat (x_pre, "  ");
   if (a_dist == 0)   return NULL;
   x_node = a_node;
   switch (a_dir) {
   case 'L' :
      x_pos = a_pos - a_dist;
      if (x_pos <= 0) {
         /*> x_node->left  = poly_extern__smake (a_lvl, a_pos, a_dist / 2, 'L', x_node);   <*/
         return poly_extern__smake (a_lvl, a_pos, a_dist / 2, 'L', x_node);
      }
      break;
   case 'R' :
      x_pos = a_pos + a_dist;
      if (x_pos > s_count) {
         /*> x_node->right = poly_extern__smake (a_lvl, a_pos, a_dist / 2, 'R', x_node);   <*/
         return poly_extern__smake (a_lvl, a_pos, a_dist / 2, 'R', x_node);
      }
      break;
   default  :
      return NULL;
      break;
   }
   while (c < a_dist) {
      if (a_dir == 'L')   x_node = x_node->prev;
      if (a_dir == 'R')   x_node = x_node->next;
      ++c;
   }
   /*> printf ("%s%2d %c %2d (%3d) %s\n", x_pre, a_lvl, a_dir, a_dist, x_pos, x_node->name);   <*/
   x_node->left  = poly_extern__smake (a_lvl + 1, x_pos, a_dist / 2, 'L', x_node);
   x_node->right = poly_extern__smake (a_lvl + 1, x_pos, a_dist / 2, 'R', x_node);
   return x_node;
}

char
poly_extern__sform      (void)
{
   tEXTERN    *x_node      = NULL;
   int         x_lvl       =    0;
   int         x_ctr       =    0;
   int         x_span      =    0;
   int         x_dist      =    0;
   int         c           =    0;
   x_lvl  = poly_extern__sdepth (s_count);
   /*> printf ("depth  = %d\n", x_lvl);                                               <*/
   x_span = pow (2, x_lvl) - 1;
   /*> printf ("span   = %d\n", x_span);                                              <*/
   /*> printf ("use    = %5.2f\n", s_count / (float) x_span);                         <*/
   x_ctr  = (s_count / 2) + 1;
   /*> printf ("center = %d\n", x_ctr);                                               <*/
   s_root = s_head;
   c = 1;
   while (c < x_ctr) {
      s_root = s_root->next;
      ++c;
   }
   /*> printf ("ROOT %2d (%3d) %s\n", x_lvl, x_ctr, s_root->name);                    <*/
   s_root->left  = poly_extern__smake (1, x_ctr, x_span / 4 + 1, 'L', s_root);
   s_root->right = poly_extern__smake (1, x_ctr, x_span / 4 + 1, 'R', s_root);
   return 0;
}

char
poly_extern__sdisplay   (int a_lvl, tEXTERN *a_node)
{
   char        x_pre       [LEN_RECD] = "";
   int         i           =    0;
   if (a_node == NULL)  return 0;
   if (a_lvl > 20)      return 0;
   for (i = 0; i < a_lvl; ++i)  strcat (x_pre, "  ");
   poly_extern__sdisplay (a_lvl + 1, a_node->left);
   /*> printf ("%s%s\n", x_pre, a_node->name);                                        <*/
   printf ("%s\n", a_node->name);
   poly_extern__sdisplay (a_lvl + 1, a_node->right);
   return 0;
}

char
poly_extern__slist      (void)
{
   poly_extern__sdisplay (0, s_root);
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
poly_extern__dgnome          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_match     =    0;
   char        x_flag      =  '-';
   tEXTERN    *p           = NULL;          /* main index                     */
   tEXTERN    *t           = NULL;          /* teleport point                 */
   tEXTERN    *o           = NULL;          /* origin point                   */
   char        x_swap      =  '-';
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(gnome)--------------------------*/
   DEBUG_SORT   yLOG_point   ("s_head"    , s_head);
   --rce;  if (s_head == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SORT   yLOG_point   ("->next"    , s_head->next);
   --rce;  if (s_head == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   o   = s_head->next;
   if (o != NULL) {
      p = o->prev;
      t = o->next;
   }
   while (o != NULL) {
      /*---(beginning)-------------------*/
      if (p == NULL) {
         DEBUG_SORT   yLOG_note    ("bounce off beginning");
         if (x_swap == 'y') {
            ++s_swaps;
            poly_extern__swap (s_head, o);
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
      x_match = strcmp (p->name, o->name);
      x_flag  = (x_match <= 0) ? 'y' : '#';
      DEBUG_SORT   yLOG_complex ("compare"   , "%-20.20s v %-20.20s   %c %4d   %4d %4d %4d", p->name, o->name, x_flag, x_match, s_comps, s_teles, s_swaps);
      if (x_match <= 0) {
         if (x_swap == 'y') {
            ++s_swaps;
            poly_extern__swap (p->next, o);
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
   DEBUG_SORT   yLOG_value   ("size"       , s_count);
   DEBUG_SORT   yLOG_value   ("compares"   , s_comps);
   DEBUG_SORT   yLOG_value   ("teleports"  , s_teles);
   DEBUG_SORT   yLOG_value   ("swaps"      , s_swaps);
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        mass actions                          ----===*/
/*====================------------------------------------====================*/
static void  o___MASS____________o () { return; }

char
poly_extern_load        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   FILE       *r           = NULL;          /* external functions file        */
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   char        x_type      =  '-';
   int         c           =    0;
   tEXTERN    *u           = NULL;
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   r = fopen (FILE_EXTERN, "rt");
   DEBUG_SORT   yLOG_point   ("r"          , r);
   --rce;  if (r == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets (x_recd, LEN_RECD, r);
      if (feof (r)) {
         DEBUG_SORT   yLOG_note    ("end of file");
         break;
      }
      ++c;
      x_len = strlen (x_recd);
      DEBUG_SORT   yLOG_value   ("x_len"     , x_len);
      if (strlen >= 1)  x_recd [--x_len] = '\0';
      DEBUG_SORT   yLOG_value   ("x_len"     , x_len);
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      DEBUG_SORT   yLOG_info    ("x_recd"    , x_recd);
      x_len = strlen (x_recd);
      DEBUG_SORT   yLOG_value   ("x_len"     , x_len);
      DEBUG_SORT   yLOG_info    ("x_recd"    , x_recd);
      /*---(filter)----------------------*/
      if (x_len == 0) {
         DEBUG_SORT   yLOG_note    ("empty line, SKIP");
         continue;
      }
      if (strncmp (x_recd, "##", 2) == 0) {
         DEBUG_SORT   yLOG_note    ("header line, SKIP");
         continue;
      }
      if (x_recd [0] == '#') {
         DEBUG_SORT   yLOG_note    ("category line, SKIP");
         continue;
      }
      /*---(type)------------------------*/
      x_type = '-';
      if (x_len >= 20) {
         x_type = x_recd [19];
         x_recd [19] = '\0';
      }
      /*---(save)------------------------*/
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      poly_extern__create (x_recd, x_type);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = fclose (r);
   DEBUG_SORT   yLOG_value   ("close"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(sort)---------------------------*/
   /*> printf ("BEFORE gnome...\n");                                                  <* 
    *> u = s_head;                                                                    <* 
    *> c = 0;                                                                         <* 
    *> while (u != NULL) {                                                            <* 
    *>    ++c;                                                                        <* 
    *>    printf ("%3d:%-20.20s %c\n", u->len, u->name, u->type);                     <* 
    *>    u = u->next;                                                                <* 
    *> }                                                                              <* 
    *> printf ("   count = %d\n", c);                                                 <*/
   rc = poly_extern__dgnome ();
   printf ("\n\n\nAFTER gnome...\n");
   c = 0;
   u = s_head;
   while (u != NULL) {
      ++c;
      /*> printf ("%3d   %3d:%-20.20s %c\n", c, u->len, u->name, u->type);            <*/
      printf ("%s\n", u->name);
      u = u->next;
   }
   printf ("   count = %d\n", c);
   rc = poly_extern__sform  ();
   printf ("\n\n\nAFTER sform...\n");
   rc = poly_extern__slist  ();

   exit (0);

   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}


char
poly_extern_check       (char *a_name)
{
   /*> int         rce         =  -10;                                                <* 
    *> int         i           =    0;                                                <* 
    *> --rce;  if (a_name == NULL)  return rce;                                       <* 
    *> x_len = strlen (a_name);                                                       <* 
    *> --rce;  if (x_len == 0)      return rce;                                       <* 
    *> for (i = 0; i < s_nextern; ++i) {                                              <* 
    *>    if (s_externs [i].len != x_len)                continue;                    <* 
    *>    if (s_externs [i].name [0] != a_name [0])      continue;                    <* 
    *>    if (strcmp (s_externs [i].name, a_name) != 0)  continue;                    <* 
    *>    return s_externs [i].type;                                                  <* 
    *> }                                                                              <* 
    *> return ' ';                                                                    <*/
}

char
poly_extern_review      (int n)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                        <* 
    *> char        rce         =  -10;          /+ return code for errors         +/   <* 
    *> char        rc          =    0;          /+ generic return code            +/   <* 
    *> FILE       *r           = NULL;          /+ external functions file        +/   <* 
    *> char       *p           = NULL;                                                 <* 
    *> char        x_recd      [LEN_RECD];                                             <* 
    *> int         x_len       =    0;                                                 <* 
    *> int         c           =    0;                                                 <* 
    *> char        x_cat       =  ' ';                                                 <* 
    *> /+---(header)-------------------------+/                                        <* 
    *> DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                       <* 
    *> /+---(create file)--------------------+/                                        <* 
    *> rc = system ("cflow -d 2 htags.code > polymnia.calls");                         <* 
    *> DEBUG_SORT   yLOG_value   ("cflow"      , rc);                                  <* 
    *> /+---(open)---------------------------+/                                        <* 
    *> r = fopen ("polymnia.calls", "rt");                                             <* 
    *> DEBUG_SORT   yLOG_point   ("r"          , r);                                   <* 
    *> --rce;  if (r == NULL) {                                                        <* 
    *>    DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);                               <* 
    *>    return rce;                                                                  <* 
    *> }                                                                               <* 
    *> /+---(walk)---------------------------+/                                        <* 
    *> while (1) {                                                                     <* 
    *>    /+---(read)------------------------+/                                        <* 
    *>    fgets (x_recd, LEN_RECD, r);                                                 <* 
    *>    if (feof (r)) {                                                              <* 
    *>       DEBUG_SORT   yLOG_note    ("end of file");                                <* 
    *>       break;                                                                    <* 
    *>    }                                                                            <* 
    *>    if (x_recd [0] != ' ') {                                                     <* 
    *>       DEBUG_SORT   yLOG_note    ("header line, skipping");                      <* 
    *>       continue;                                                                 <* 
    *>    }                                                                            <* 
    *>    ++c;                                                                         <* 
    *>    x_len = strlen (x_recd);                                                     <* 
    *>    if (strlen >= 1)  x_recd [--x_len] = '\0';                                   <* 
    *>    strltrim (x_recd, ySTR_EVERY, LEN_RECD);                                     <* 
    *>    /+---(filter)----------------------+/                                        <* 
    *>    p = strchr (x_recd, '(');                                                    <* 
    *>    if (p == NULL) {                                                             <* 
    *>       DEBUG_SORT   yLOG_note    ("not a function call, SKIPPING");              <* 
    *>       continue;                                                                 <* 
    *>    }                                                                            <* 
    *>    *p = '\0';                                                                   <* 
    *>    x_len = strlen (x_recd);                                                     <* 
    *>    DEBUG_SORT   yLOG_value   ("x_len"     , x_len);                             <* 
    *>    DEBUG_SORT   yLOG_info    ("x_recd"    , x_recd);                            <* 
    *>    /+---(lookup)----------------------+/                                        <* 
    *>    x_cat = poly_extern_check (x_recd);                                          <* 
    *>    DEBUG_SORT   yLOG_value   ("x_cat"     , x_cat);                             <* 
    *>    if (x_cat <= 0) {                                                            <* 
    *>       DEBUG_SORT   yLOG_note    ("not an external function");                   <* 
    *>       continue;                                                                 <* 
    *>    }                                                                            <* 
    *>    /+---(categorize)------------------+/                                        <* 
    *>    DEBUG_SORT   yLOG_char    ("x_cat"     , x_cat);                             <* 
    *>    ++s_tags [n].funcs;                                                          <* 
    *>    switch (x_cat) {                                                             <* 
    *>    case '-' :                                                                   <* 
    *>       ++s_tags [n].cstd;                                                        <* 
    *>       break;                                                                    <* 
    *>    case 'W' :                                                                   <* 
    *>       ++s_tags [n].cstd;                                                        <* 
    *>       ++s_tags [n].writes;                                                      <* 
    *>       break;                                                                    <* 
    *>    case 'R' :                                                                   <* 
    *>       ++s_tags [n].cstd;                                                        <* 
    *>       ++s_tags [n].reads;                                                       <* 
    *>       break;                                                                    <* 
    *>    case 'N' :                                                                   <* 
    *>       ++s_tags [n].ncurses;                                                     <* 
   *>       break;                                                                    <* 
      *>    case 'O' :                                                                   <* 
      *>       ++s_tags [n].opengl;                                                      <* 
      *>       break;                                                                    <* 
      *>    case 'Y' :                                                                   <* 
      *>       ++s_tags [n].ylibs;                                                       <* 
      *>       break;                                                                    <* 
      *>    case 'M' :                                                                   <* 
      *>       ++s_tags [n].cstd;                                                        <* 
      *>       ++s_tags [n].memories;                                                    <* 
      *>       break;                                                                    <* 
      *>    case 'P' :                                                                   <* 
      *>       ++s_tags [n].cstd;                                                        <* 
      *>       ++s_tags [n].process;                                                     <* 
      *>       break;                                                                    <* 
      *>    case 'S' :                                                                   <* 
      *>       ++s_tags [n].cstd;                                                        <* 
      *>       ++s_tags [n].scalls;                                                      <* 
      *>       break;                                                                    <* 
      *>    }                                                                            <* 
      *>    /+---(done)------------------------+/                                        <* 
      *> }                                                                               <* 
      *> /+---(close)--------------------------+/                                        <* 
      *> rc = fclose (r);                                                                <* 
      *> DEBUG_SORT   yLOG_value   ("close"      , rc);                                  <* 
      *> --rce;  if (rc < 0) {                                                           <* 
         *>    DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);                               <* 
            *>    return rce;                                                                  <* 
            *> }                                                                               <* 
            *> /+---(complete)-----------------------+/                                        <* 
            *> DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                       <* 
            *> return 0;                                                                       <*/
}


/*> char                                                                              <* 
 *> poly_extern__copy       (tEXTERN *a_dst, tEXTERN *a_src)                          <* 
 *> {                                                                                 <* 
 *>    strlcpy (a_dst->name, a_src->name, LEN_NAME);                                  <* 
 *>    a_dst->len    = a_src->len;                                                    <* 
 *>    a_dst->type   = a_src->type;                                                   <* 
 *>    a_dst->count  = a_src->count;                                                  <* 
 *>    a_dst->pos    = a_src->pos;                                                    <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                                                                                                      <* 
 *> poly_extern__gnome_BASE      (void)                                                                                                                       <* 
 *> {                                                                                                                                                         <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                               <* 
 *>    int         i           =    0;          /+ current index                  +/                                                                          <* 
 *>    int         c           =    0;          /+ comparisons                    +/                                                                          <* 
 *>    int         s           =    0;          /+ swaps                          +/                                                                          <* 
 *>    tEXTERN     x_tmp;                                                                                                                                     <* 
 *>    /+---(header)-------------------------+/                                                                                                               <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                                                                              <* 
 *>    /+---(gnome)--------------------------+/                                                                                                               <* 
 *>    while (i < s_nextern) {                                                                                                                                <* 
 *>       /+---(beginning)-------------------+/                                                                                                               <* 
 *>       if (i <= 0) {                                                                                                                                       <* 
 *>          DEBUG_SORT   yLOG_note    ("bounce off beginning");                                                                                              <* 
 *>          ++i;                                                                                                                                             <* 
 *>          continue;                                                                                                                                        <* 
 *>       }                                                                                                                                                   <* 
 *>       /+---(compare)---------------------+/                                                                                                               <* 
 *>       ++c;                                                                                                                                                <* 
 *>       if (strcmp (s_externs [i - 1].name, s_externs [i].name) <= 0) {                                                                                     <* 
 *>          DEBUG_SORT   yLOG_complex ("correct"   , "%2d %-20.20s v %2d %-20.20s   %4d %4d", i - 1, s_externs [i - 1].name, i, s_externs [i].name, c, s);   <* 
 *>          ++i;                                                                                                                                             <* 
 *>          continue;                                                                                                                                        <* 
 *>       }                                                                                                                                                   <* 
 *>       /+---(swap)------------------------+/                                                                                                               <* 
 *>       ++s;                                                                                                                                                <* 
 *>       poly_extern__copy (&x_tmp            , &s_externs [i]    );                                                                                         <* 
 *>       poly_extern__copy (&s_externs [i]    , &s_externs [i - 1]);                                                                                         <* 
 *>       poly_extern__copy (&s_externs [i - 1], &x_tmp           );                                                                                          <* 
 *>       DEBUG_SORT   yLOG_complex ("swapped"   , "%2d %-20.20s # %2d %-20.20s   %4d %4d", i - 1, s_externs [i - 1].name, i, s_externs [i].name, c, s);      <* 
 *>       /+---(next)------------------------+/                                                                                                               <* 
 *>       --i;                                                                                                                                                <* 
 *>    }                                                                                                                                                      <* 
 *>    DEBUG_SORT   yLOG_value   ("size"       , s_nextern);                                                                                                  <* 
 *>    DEBUG_SORT   yLOG_value   ("compares"   , c);                                                                                                          <* 
 *>    DEBUG_SORT   yLOG_value   ("swaps"      , s);                                                                                                          <* 
 *>    /+---(complete)-----------------------+/                                                                                                               <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                                                                              <* 
 *>    return 0;                                                                                                                                              <* 
 *> }                                                                                                                                                         <*/

/*> char                                                                                                                                                      <* 
 *> poly_extern__gnome_TELE      (void)                                                                                                                       <* 
 *> {                                                                                                                                                         <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                               <* 
 *>    int         i           =    0;          /+ current index                  +/                                                                          <* 
 *>    int         c           =    0;          /+ comparisons                    +/                                                                          <* 
 *>    int         s           =    0;          /+ swaps                          +/                                                                          <* 
 *>    int         t           =    0;          /+ teleport index                 +/                                                                          <* 
 *>    tEXTERN     x_tmp;                                                                                                                                     <* 
 *>    /+---(header)-------------------------+/                                                                                                               <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                                                                              <* 
 *>    /+---(gnome)--------------------------+/                                                                                                               <* 
 *>    while (i < s_nextern) {                                                                                                                                <* 
 *>       if (i > t)  t = i;                                                                                                                                  <* 
 *>       /+---(beginning)-------------------+/                                                                                                               <* 
 *>       if (i <= 0) {                                                                                                                                       <* 
 *>          DEBUG_SORT   yLOG_note    ("bounce off beginning");                                                                                              <* 
 *>          ++i;                                                                                                                                             <* 
 *>          continue;                                                                                                                                        <* 
 *>       }                                                                                                                                                   <* 
 *>       /+---(compare)---------------------+/                                                                                                               <* 
 *>       ++c;                                                                                                                                                <* 
 *>       if (strcmp (s_externs [i - 1].name, s_externs [i].name) <= 0) {                                                                                     <* 
 *>          DEBUG_SORT   yLOG_complex ("correct"   , "%2d %-20.20s v %2d %-20.20s   %4d %4d", i - 1, s_externs [i - 1].name, i, s_externs [i].name, c, s);   <* 
 *>          i = t + 1;                                                                                                                                       <* 
 *>          continue;                                                                                                                                        <* 
 *>       }                                                                                                                                                   <* 
 *>       /+---(swap)------------------------+/                                                                                                               <* 
 *>       ++s;                                                                                                                                                <* 
 *>       poly_extern__copy (&x_tmp            , &s_externs [i]    );                                                                                         <* 
 *>       poly_extern__copy (&s_externs [i]    , &s_externs [i - 1]);                                                                                         <* 
 *>       poly_extern__copy (&s_externs [i - 1], &x_tmp           );                                                                                          <* 
 *>       DEBUG_SORT   yLOG_complex ("swapped"   , "%2d %-20.20s # %2d %-20.20s   %4d %4d", i - 1, s_externs [i - 1].name, i, s_externs [i].name, c, s);      <* 
 *>       /+---(next)------------------------+/                                                                                                               <* 
 *>       --i;                                                                                                                                                <* 
 *>    }                                                                                                                                                      <* 
 *>    DEBUG_SORT   yLOG_value   ("size"       , s_nextern);                                                                                                  <* 
 *>    DEBUG_SORT   yLOG_value   ("compares"   , c);                                                                                                          <* 
 *>    DEBUG_SORT   yLOG_value   ("swaps"      , s);                                                                                                          <* 
 *>    /+---(complete)-----------------------+/                                                                                                               <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                                                                              <* 
 *>    return 0;                                                                                                                                              <* 
 *> }                                                                                                                                                         <*/

/*> static  tEXTERN      s_head;                                                      <* 
 *> static  int          s_headnum;                                                   <* 
 *> static  tEXTERN      s_saved;                                                     <* 
 *> static  int          s_start;                                                     <* 
 *> static int           s_next;                                                      <* 
 *> static int           s_hole;                                                      <*/


/*> int                                                                               <* 
 *> poly_extern__move_SALTS (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_SORT   yLOG_senter  (__FUNCTION__);                                      <* 
 *>    DEBUG_SORT   yLOG_snote   ("hole");                                            <* 
 *>    DEBUG_SORT   yLOG_sint    (s_hole);                                            <* 
 *>    DEBUG_SORT   yLOG_snote   (s_externs [s_hole].name);                           <* 
 *>    DEBUG_SORT   yLOG_snote   ("next");                                            <* 
 *>    DEBUG_SORT   yLOG_sint    (s_next);                                            <* 
 *>    DEBUG_SORT   yLOG_snote   (s_externs [s_next].name);                           <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    if (s_hole == s_next) {                                                        <* 
 *>       DEBUG_SORT   yLOG_snote   ("no move required");                             <* 
 *>       DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, -1);                               <* 
 *>       return -1;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(move from original)-------------+/                                       <* 
 *>    poly_extern__copy (&s_externs [s_hole], &s_externs [s_next]);                  <* 
 *>    s_externs [s_next].name [0] = '\0';                                            <* 
 *>    s_alts [s_hole] = -1;                                                          <* 
 *>    DEBUG_SORT   yLOG_snote   ("moved");                                           <* 
 *>    ++s_swaps;                                                                     <* 
 *>    /+---(save next index)----------------+/                                       <* 
 *>    s_hole = s_next;                                                               <* 
 *>    DEBUG_SORT   yLOG_sint    (s_hole);                                            <* 
 *>    s_next = s_alts [s_next];                                                      <* 
 *>    DEBUG_SORT   yLOG_sint    (s_next);                                            <* 
 *>    if (s_hole == s_next) {                                                        <* 
 *>       DEBUG_SORT   yLOG_snote   ("end of chain");                                 <* 
 *>       DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, -2);                               <* 
 *>       return -2;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_SORT   yLOG_sexit   (__FUNCTION__);                                      <* 
 *>    return 1;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                                                       <* 
 *> poly_extern__reorder_SALTS    (void)                                                                       <* 
 *> {                                                                                                          <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                <* 
 *>    char        rc          =    0;                                                                         <* 
 *>    int         i           =    0;          /+ current index                  +/                           <* 
 *>    int         c           =    0;                                                                         <* 
 *>    /+---(header)-------------------------+/                                                                <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                               <* 
 *>    /+---(walk list)----------------------+/                                                                <* 
 *>    for (i = 0; i < s_nextern; ++i) {                                                                       <* 
 *>       /+---(header)----------------------+/                                                                <* 
 *>       DEBUG_SORT   yLOG_value   ("ROUND"     , i);                                                         <* 
 *>       DEBUG_SORT   yLOG_complex ("check"     , "%3d  %3d  %-20.20s", i, s_alts [i], s_externs [i].name);   <* 
 *>       /+---(filter)----------------------+/                                                                <* 
 *>       if (s_alts [i] < 0) {                                                                                <* 
 *>          DEBUG_SORT   yLOG_note    ("already in the right order");                                         <* 
 *>          continue;                                                                                         <* 
 *>       }                                                                                                    <* 
 *>       /+---(save starting)---------------+/                                                                <* 
 *>       c = 0;                                                                                               <* 
 *>       s_hole  = SAVE;                                                                                      <* 
 *>       s_start = s_next  = i;                                                                               <* 
 *>       rc      = 0;                                                                                         <* 
 *>       while (rc >= 0) {                                                                                    <* 
 *>          rc = poly_extern__move ();                                                                        <* 
 *>          ++c;                                                                                              <* 
 *>          if (s_next == s_start)  break;                                                                    <* 
 *>       }                                                                                                    <* 
 *>       s_next  = SAVE;                                                                                      <* 
 *>       rc = poly_extern__move ();                                                                           <* 
 *>       ++c;                                                                                                 <* 
 *>       DEBUG_SORT   yLOG_value   ("chain len" , c);                                                         <* 
 *>    }                                                                                                       <* 
 *>    /+---(complete)-----------------------+/                                                                <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                               <* 
 *>    return 0;                                                                                               <* 
 *> }                                                                                                          <*/

/*> char                                                                                                                                                                                                                                     <* 
 *> poly_extern__gnome_SALTS      (void)                                                                                                                                                                                                     <* 
 *> {                                                                                                                                                                                                                                        <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                                                                                                              <* 
 *>    char        rc          =    0;                                                                                                                                                                                                       <* 
 *>    int         i           =    0;          /+ current index                  +/                                                                                                                                                         <* 
 *>    int         t           =    0;          /+ teleport index                 +/                                                                                                                                                         <* 
 *>    int         x_tmp;                                                                                                                                                                                                                    <* 
 *>    /+---(header)-------------------------+/                                                                                                                                                                                              <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                                                                                                                                                             <* 
 *>    /+---(display)------------------------+/                                                                                                                                                                                              <* 
 *>    /+> printf ("BEFORE...\n");                                                                   <*                                                                                                                                      <* 
 *>     *> for (i = 0; i < s_nextern; ++i) {                                                         <*                                                                                                                                      <* 
 *>     *>    printf ("%3d %2d:%s\n", i, s_externs [s_alts [i]].len, s_externs [s_alts [i]].name);   <*                                                                                                                                      <* 
 *>     *> }                                                                                         <+/                                                                                                                                     <* 
 *>    /+---(gnome)--------------------------+/                                                                                                                                                                                              <* 
 *>    i = 0;                                                                                                                                                                                                                                <* 
 *>    while (i < s_nextern) {                                                                                                                                                                                                               <* 
 *>       if (i > t)  t = i;                                                                                                                                                                                                                 <* 
 *>       /+---(beginning)-------------------+/                                                                                                                                                                                              <* 
 *>       if (i <= 0) {                                                                                                                                                                                                                      <* 
 *>          DEBUG_SORT   yLOG_note    ("bounce off beginning");                                                                                                                                                                             <* 
 *>          ++s_teles;                                                                                                                                                                                                                      <* 
 *>          i = t + 1;                                                                                                                                                                                                                      <* 
 *>          continue;                                                                                                                                                                                                                       <* 
 *>       }                                                                                                                                                                                                                                  <* 
 *>       /+---(compare)---------------------+/                                                                                                                                                                                              <* 
 *>       ++s_comps;                                                                                                                                                                                                                         <* 
 *>       rc = strcmp (s_externs [s_alts[i - 1]].name, s_externs [s_alts [i]].name);                                                                                                                                                         <* 
 *>       if (rc <= 0) {                                                                                                                                                                                                                     <* 
 *>          DEBUG_SORT   yLOG_complex ("correct"   , "%3d %-20.20s v %3d %-20.20s   %c %4d   %5d %5d %5d", i - 1, s_externs [s_alts [i - 1]].name, i, s_externs [s_alts [i]].name, (rc <= 0) ? 'y' : '-', rc, s_comps, s_swaps, s_teles);   <* 
 *>          ++s_teles;                                                                                                                                                                                                                      <* 
 *>          i = t + 1;                                                                                                                                                                                                                      <* 
 *>          continue;                                                                                                                                                                                                                       <* 
 *>       }                                                                                                                                                                                                                                  <* 
 *>       /+---(swap)------------------------+/                                                                                                                                                                                              <* 
 *>       ++s_notes;                                                                                                                                                                                                                         <* 
 *>       DEBUG_SORT   yLOG_complex ("swapped"   , "%3d %-20.20s # %3d %-20.20s   %c %4d   %5d %5d %5d", i - 1, s_externs [s_alts [i - 1]].name, i, s_externs [s_alts [i]].name, (rc <= 0) ? 'y' : '-', rc, s_comps, s_swaps, s_teles);      <* 
 *>       x_tmp          = s_alts [i];                                                                                                                                                                                                       <* 
 *>       s_alts [i]     = s_alts [i - 1];                                                                                                                                                                                                   <* 
 *>       s_alts [i - 1] = x_tmp;                                                                                                                                                                                                            <* 
 *>       /+---(next)------------------------+/                                                                                                                                                                                              <* 
 *>       --i;                                                                                                                                                                                                                               <* 
 *>    }                                                                                                                                                                                                                                     <* 
 *>    /+---(display)------------------------+/                                                                                                                                                                                              <* 
 *>    /+> printf ("AFTER...\n");                                                                    <*                                                                                                                                      <* 
 *>     *> for (i = 0; i < s_nextern; ++i) {                                                         <*                                                                                                                                      <* 
 *>     *>    printf ("%3d %2d:%s\n", i, s_externs [s_alts [i]].len, s_externs [s_alts [i]].name);   <*                                                                                                                                      <* 
 *>     *> }                                                                                         <*                                                                                                                                      <* 
 *>     *> printf ("BEFORE reorder...\n");                                                           <*                                                                                                                                      <* 
 *>     *> for (i = 0; i < s_nextern; ++i) {                                                         <*                                                                                                                                      <* 
 *>     *>    printf ("%3d %3d %2d:%s\n", i, s_alts [i], s_externs [i].len, s_externs [i].name);     <*                                                                                                                                      <* 
 *>     *> }                                                                                         <+/                                                                                                                                     <* 
 *>    poly_extern__reorder_SALTS ();                                                                                                                                                                                                        <* 
 *>    printf ("AFTER reorder...\n");                                                                                                                                                                                                        <* 
 *>    for (i = 0; i < s_nextern; ++i) {                                                                                                                                                                                                     <* 
 *>       printf ("%3d %3d %2d:%s\n", i, s_alts [i], s_externs [i].len, s_externs [i].name);                                                                                                                                                 <* 
 *>    }                                                                                                                                                                                                                                     <* 
 *>    DEBUG_SORT   yLOG_value   ("size"       , s_nextern);                                                                                                                                                                                 <* 
 *>    DEBUG_SORT   yLOG_value   ("compares"   , s_comps);                                                                                                                                                                                   <* 
 *>    DEBUG_SORT   yLOG_value   ("notes"      , s_notes);                                                                                                                                                                                   <* 
 *>    DEBUG_SORT   yLOG_value   ("swaps"      , s_swaps);                                                                                                                                                                                   <* 
 *>    DEBUG_SORT   yLOG_value   ("teleports"  , s_teles);                                                                                                                                                                                   <* 
 *>    /+---(complete)-----------------------+/                                                                                                                                                                                              <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                                                                                                                                                             <* 
 *>    return 0;                                                                                                                                                                                                                             <* 
 *> }                                                                                                                                                                                                                                        <*/


/*> int                                                                               <* 
 *> poly_extern__move_INDEX (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_SORT   yLOG_senter  (__FUNCTION__);                                      <* 
 *>    DEBUG_SORT   yLOG_snote   ("hole");                                            <* 
 *>    DEBUG_SORT   yLOG_sint    (s_hole);                                            <* 
 *>    DEBUG_SORT   yLOG_snote   (s_externs [s_hole].name);                           <* 
 *>    DEBUG_SORT   yLOG_snote   ("next");                                            <* 
 *>    DEBUG_SORT   yLOG_sint    (s_next);                                            <* 
 *>    DEBUG_SORT   yLOG_snote   (s_externs [s_next].name);                           <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    if (s_hole == s_next) {                                                        <* 
 *>       DEBUG_SORT   yLOG_snote   ("no move required");                             <* 
 *>       DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, -1);                               <* 
 *>       return -1;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(move from original)-------------+/                                       <* 
 *>    poly_extern__copy (&s_externs [s_hole], &s_externs [s_next]);                  <* 
 *>    s_externs [s_next].name [0] = '\0';                                            <* 
 *>    s_externs [s_hole].pos = -1;                                                   <* 
 *>    DEBUG_SORT   yLOG_snote   ("moved");                                           <* 
 *>    ++s_swaps;                                                                     <* 
 *>    /+---(save next index)----------------+/                                       <* 
 *>    s_hole = s_next;                                                               <* 
 *>    DEBUG_SORT   yLOG_sint    (s_hole);                                            <* 
 *>    s_next = s_externs [s_next].pos;                                               <* 
 *>    DEBUG_SORT   yLOG_sint    (s_next);                                            <* 
 *>    if (s_hole == s_next) {                                                        <* 
 *>       DEBUG_SORT   yLOG_snote   ("end of chain");                                 <* 
 *>       DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, -2);                               <* 
 *>       return -2;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_SORT   yLOG_sexit   (__FUNCTION__);                                      <* 
 *>    return 1;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                                                              <* 
 *> poly_extern__reorder_INDEX (void)                                                                                 <* 
 *> {                                                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                       <* 
 *>    char        rc          =    0;                                                                                <* 
 *>    int         i           =    0;          /+ current index                  +/                                  <* 
 *>    int         c           =    0;                                                                                <* 
 *>    /+---(header)-------------------------+/                                                                       <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                                      <* 
 *>    /+---(walk list)----------------------+/                                                                       <* 
 *>    for (i = 0; i < s_nextern; ++i) {                                                                              <* 
 *>       /+---(header)----------------------+/                                                                       <* 
 *>       DEBUG_SORT   yLOG_value   ("ROUND"     , i);                                                                <* 
 *>       DEBUG_SORT   yLOG_complex ("check"     , "%3d  %3d  %-20.20s", i, s_externs [i].pos, s_externs [i].name);   <* 
 *>       /+---(filter)----------------------+/                                                                       <* 
 *>       if (s_externs [i].pos < 0) {                                                                                <* 
 *>          DEBUG_SORT   yLOG_note    ("already in the right order");                                                <* 
 *>          continue;                                                                                                <* 
 *>       }                                                                                                           <* 
 *>       /+---(save starting)---------------+/                                                                       <* 
 *>       c = 0;                                                                                                      <* 
 *>       s_hole  = SAVE;                                                                                             <* 
 *>       s_start = s_next  = i;                                                                                      <* 
 *>       rc      = 0;                                                                                                <* 
 *>       while (rc >= 0) {                                                                                           <* 
 *>          rc = poly_extern__move ();                                                                               <* 
 *>          ++c;                                                                                                     <* 
 *>          if (s_next == s_start)  break;                                                                           <* 
 *>       }                                                                                                           <* 
 *>       s_next  = SAVE;                                                                                             <* 
 *>       rc = poly_extern__move ();                                                                                  <* 
 *>       ++c;                                                                                                        <* 
 *>       DEBUG_SORT   yLOG_value   ("chain len" , c);                                                                <* 
 *>    }                                                                                                              <* 
 *>    /+---(complete)-----------------------+/                                                                       <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                                      <* 
 *>    return 0;                                                                                                      <* 
 *> }                                                                                                                 <*/

/*> char                                                                                                                                                                                                                                                   <* 
 *> poly_extern__gnome_INDEX(void)                                                                                                                                                                                                                         <* 
 *> {                                                                                                                                                                                                                                                      <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                                                                                                                            <* 
 *>    char        rc          =    0;                                                                                                                                                                                                                     <* 
 *>    int         i           =    0;          /+ current index                  +/                                                                                                                                                                       <* 
 *>    int         t           =    0;          /+ teleport index                 +/                                                                                                                                                                       <* 
 *>    int         x_tmp;                                                                                                                                                                                                                                  <* 
 *>    /+---(header)-------------------------+/                                                                                                                                                                                                            <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                                                                                                                                                                           <* 
 *>    /+---(gnome)--------------------------+/                                                                                                                                                                                                            <* 
 *>    i = 0;                                                                                                                                                                                                                                              <* 
 *>    while (i < s_nextern) {                                                                                                                                                                                                                             <* 
 *>       if (i > t)  t = i;                                                                                                                                                                                                                               <* 
 *>       /+---(beginning)-------------------+/                                                                                                                                                                                                            <* 
 *>       if (i <= 0) {                                                                                                                                                                                                                                    <* 
 *>          DEBUG_SORT   yLOG_note    ("bounce off beginning");                                                                                                                                                                                           <* 
 *>          ++s_teles;                                                                                                                                                                                                                                    <* 
 *>          i = t + 1;                                                                                                                                                                                                                                    <* 
 *>          continue;                                                                                                                                                                                                                                     <* 
 *>       }                                                                                                                                                                                                                                                <* 
 *>       /+---(compare)---------------------+/                                                                                                                                                                                                            <* 
 *>       ++s_comps;                                                                                                                                                                                                                                       <* 
 *>       rc = strcmp (s_externs [s_externs [i - 1].pos].name, s_externs [s_externs [i].pos].name);                                                                                                                                                        <* 
 *>       if (rc <= 0) {                                                                                                                                                                                                                                   <* 
 *>          DEBUG_SORT   yLOG_complex ("correct"   , "%3d %-20.20s v %3d %-20.20s   %c %4d   %5d %5d %5d", i - 1, s_externs [s_externs [i - 1].pos].name, i, s_externs [s_externs [i].pos].name, (rc <= 0) ? 'y' : '-', rc, s_comps, s_swaps, s_teles);   <* 
 *>          ++s_teles;                                                                                                                                                                                                                                    <* 
 *>          i = t + 1;                                                                                                                                                                                                                                    <* 
 *>          continue;                                                                                                                                                                                                                                     <* 
 *>       }                                                                                                                                                                                                                                                <* 
 *>       /+---(swap)------------------------+/                                                                                                                                                                                                            <* 
 *>       ++s_notes;                                                                                                                                                                                                                                       <* 
 *>       DEBUG_SORT   yLOG_complex ("swapped"   , "%3d %-20.20s # %3d %-20.20s   %c %4d   %5d %5d %5d", i - 1, s_externs [s_externs [i - 1].pos].name, i, s_externs [s_externs [i].pos].name, (rc <= 0) ? 'y' : '-', rc, s_comps, s_swaps, s_teles);      <* 
 *>       x_tmp                 = s_externs [i].pos;                                                                                                                                                                                                       <* 
 *>       s_externs [i].pos     = s_externs [i - 1].pos;                                                                                                                                                                                                   <* 
 *>       s_externs [i - 1].pos = x_tmp;                                                                                                                                                                                                                   <* 
 *>       /+---(next)------------------------+/                                                                                                                                                                                                            <* 
 *>       --i;                                                                                                                                                                                                                                             <* 
 *>    }                                                                                                                                                                                                                                                   <* 
 *>    /+---(display)------------------------+/                                                                                                                                                                                                            <* 
 *>    poly_extern__reorder ();                                                                                                                                                                                                                            <* 
 *>    printf ("AFTER reorder...\n");                                                                                                                                                                                                                      <* 
 *>    for (i = 0; i < s_nextern; ++i) {                                                                                                                                                                                                                   <* 
 *>       printf ("%3d %2d:%s\n", i, s_externs [i].len, s_externs [i].name);                                                                                                                                                                               <* 
 *>    }                                                                                                                                                                                                                                                   <* 
 *>    DEBUG_SORT   yLOG_value   ("size"       , s_nextern);                                                                                                                                                                                               <* 
 *>    DEBUG_SORT   yLOG_value   ("compares"   , s_comps);                                                                                                                                                                                                 <* 
 *>    DEBUG_SORT   yLOG_value   ("notes"      , s_notes);                                                                                                                                                                                                 <* 
 *>    DEBUG_SORT   yLOG_value   ("swaps"      , s_swaps);                                                                                                                                                                                                 <* 
 *>    DEBUG_SORT   yLOG_value   ("teleports"  , s_teles);                                                                                                                                                                                                 <* 
 *>    /+---(complete)-----------------------+/                                                                                                                                                                                                            <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                                                                                                                                                                           <* 
 *>    return 0;                                                                                                                                                                                                                                           <* 
 *> }                                                                                                                                                                                                                                                      <*/




/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_extern__unit       (char *a_question, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   tEXTERN    *u           = NULL;
   int         c           =    0;
   char        s           [LEN_RECD]  = "[]";
   char        t           [LEN_RECD]  = "";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "EXTERN unit      : tag number unknown");
   if (n <  0)       return unit_answer;
   u = s_head;
   while (c < n) {
      if (u == NULL)  break;
      u = u->next;
      ++c;
   }
   /*---(simple)-------------------------*/
   if (u != NULL) sprintf  (s, "[%.20s]", u->name);
   if        (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "EXTERN count     : %3d", s_count);
   }
   else if   (strcmp (a_question, "entry"     )     == 0) {
      if (u != NULL)  sprintf  (t, "%2d %-22.22s %c %d", u->len, s   , u->type, u->count);
      else            sprintf  (t, "%2d %-22.22s %c %d", 0     , "[]", '-'    , 0       );
      snprintf (unit_answer, LEN_RECD, "EXTERN entry(%2d) : %s", n, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
