/*============================----beg-of-source---============================*/
#include  "polymnia.h"

/*----------+-----------+-----------+-----------+-----------+-----------+-----*/




/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_extern__add         (char *a_lib, char *a_name, char a_type, char a_more)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEXTERN    *x_new       = NULL;
   int         x_tries     =    0;
   int         x_len       =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_len    = strlen (a_name);
   --rce;  if (x_len <= 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   DEBUG_DATA   yLOG_point   ("a_lib"     , a_lib);
   --rce;  if (a_lib == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_lib"     , a_lib);
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tEXTERN *) malloc (sizeof (tEXTERN));
      if (x_tries > 10)   break;
   }
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   strlcpy (x_new->lib , a_lib , LEN_TITLE);
   strlcpy (x_new->name, a_name, LEN_TITLE);
   x_new->type   = a_type;
   x_new->more   = a_more;
   x_new->uses   = 0;
   x_new->head   = NULL;
   x_new->tail   = NULL;
   x_new->count  = 0;
   /*---(into btree)---------------------*/
   rc = poly_btree_hook (B_EXTERN, x_new, x_new->name, &x_new->btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern__del         (tEXTERN *a_extern)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_extern"  , a_extern);
   --rce;  if (a_extern == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(btree)--------------------------*/
   rc = poly_btree_unhook (&a_extern->btree);
   DEBUG_DATA   yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free)---------------------------*/
   DEBUG_DATA   yLOG_note    ("free extern");
   free (a_extern);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_load        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   char        x_lib       [LEN_RECD]  = "";
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   char        x_type      =  '-';
   char        x_more      =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(purge existing)-----------------*/
   rc = poly_btree_purge (B_EXTERN);
   /*---(open)---------------------------*/
   my.f_extern = fopen (F_EXTERN, "rt");
   DEBUG_INPT   yLOG_point   ("my.f_extern"          , my.f_extern);
   --rce;  if (my.f_extern == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets (x_recd, LEN_RECD, my.f_extern);
      if (feof (my.f_extern)) {
         DEBUG_INPT   yLOG_note    ("end of file");
         break;
      }
      x_len = strlen (x_recd);
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      if (strlen >= 1)  x_recd [--x_len] = '\0';
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
      x_len = strlen (x_recd);
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
      /*---(filter)----------------------*/
      if (x_len == 0) {
         DEBUG_INPT   yLOG_note    ("empty line, SKIP");
         continue;
      }
      if (x_recd [0] == '#') {
         DEBUG_INPT   yLOG_note    ("comment line, SKIP");
         continue;
      }
      if (x_recd [0] == '/') {
         DEBUG_INPT   yLOG_note    ("c comment line, SKIP");
         continue;
      }
      /*---(library)---------------------*/
      if (x_recd [0] == '<') {
         DEBUG_INPT   yLOG_note    ("library header name line");
         x_recd [--x_len] = '\0';
         strlcpy (x_lib, x_recd + 1, LEN_TITLE);
         DEBUG_INPT   yLOG_info    ("x_lib"     , x_lib);
         DEBUG_INPT   yLOG_note    ("CONTINUE");
         continue;
      }
      /*---(type)------------------------*/
      x_type = '-';
      if (x_len >= 25)  x_type = x_recd [24];
      x_more = '-';
      if (x_len >= 28)  x_more = x_recd [27];
      x_recd [23] = '\0';
      /*---(save)------------------------*/
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      poly_extern__add (x_lib, x_recd, x_type, x_more);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = fclose (my.f_extern);
   DEBUG_INPT   yLOG_value   ("close"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check count)--------------------*/
   DEBUG_INPT   yLOG_value   ("count"     , poly_btree_count (B_EXTERN));
   --rce;  if (poly_btree_count (B_EXTERN) <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare for use)----------------*/
   rc = poly_btree_dgnome   (B_EXTERN);
   DEBUG_INPT   yLOG_value   ("dgnome"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_btree_build (B_EXTERN);
   DEBUG_INPT   yLOG_value   ("build"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> poly_extern_list ();                                                           <*/
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_extern_init        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = poly_btree_init (B_EXTERN);
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
poly_extern__purge      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEXTERN    *u           = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_PROG   yLOG_value   ("count"     , poly_btree_count (B_EXTERN));
   /*---(walk through list)--------------*/
   u = (tEXTERN *) poly_btree_first (B_EXTERN);
   while (u != NULL) {
      DEBUG_PROG   yLOG_value   ("extern"    , u->name);
      rc = poly_extern__del (u);
      DEBUG_PROG   yLOG_value   ("del"       , rc);
      if (rc < 0) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      u = (tEXTERN *) poly_btree_first (B_EXTERN);
   }
   /*---(check)--------------------------*/
   DEBUG_PROG   yLOG_value   ("count"     , poly_btree_count (B_EXTERN));
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_wrap        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(walk through list)--------------*/
   rc = poly_extern__purge ();
   DEBUG_PROG   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> rc = poly_btree_purge (B_EXTERN);                                              <* 
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
/*===----                        searching                             ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char      poly_extern_list        (void) { return poly_btree_list (B_EXTERN); }
tEXTERN*  poly_extern_search      (char *a_name) { return (tEXTERN *) poly_btree_search  (B_EXTERN, a_name); }



/*====================------------------------------------====================*/
/*===----                        mass actions                          ----===*/
/*====================------------------------------------====================*/
static void  o___MASS____________o () { return; }

char
poly_extern__read       (char *a_curr)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         x_len       =   0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("my.f_cflow", my.f_cflow);
   --rce;  if (my.f_cflow == NULL) {
      DEBUG_INPT   yLOG_note    ("my.f_cflow not open");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_curr"    , a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read)------------------------*/
   fgets  (a_curr, LEN_RECD, my.f_cflow);
   --rce;  if (feof (my.f_cflow))  {
      DEBUG_INPT   yLOG_note    ("end of file");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)---------------------*/
   x_len = strlen (a_curr);
   if (x_len > 0)  a_curr [--x_len] = '\0';
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   DEBUG_INPT   yLOG_info    ("a_curr"    , a_curr);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern__parse      (char *a_curr, char *a_func, char *a_file, int *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           = " :";
   char       *s           = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_curr"    , a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_func, "", LEN_TITLE);
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_file, "", LEN_TITLE);
   DEBUG_INPT   yLOG_point   ("a_line"    , a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_line = -1;
   /*---(prepare)---------------------*/
   strlcpy (x_recd, a_curr, LEN_RECD);
   /*---(get function)----------------*/
   p = strtok_r (x_recd, q, &s);
   DEBUG_INPT   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_func, p, LEN_TITLE);
   DEBUG_INPT   yLOG_info    ("func name" , a_func);
   /*---(get if definition)-----------*/
   p = strtok_r (NULL  , q, &s);
   DEBUG_INPT   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      strlcpy (a_func, "", LEN_TITLE);
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_char    ("def mark"  , p [0]);
   --rce;  if (p [0] == '*') {
      strlcpy (a_func, "", LEN_TITLE);
      DEBUG_INPT   yLOG_note    ("function definition, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_file, p, LEN_TITLE);
   DEBUG_INPT   yLOG_info    ("file name" , a_file);
   /*---(get line)--------------------*/
   p = strtok_r (NULL  , q, &s);
   DEBUG_INPT   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      strlcpy (a_func, "", LEN_TITLE);
      strlcpy (a_file, "", LEN_TITLE);
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("p"         , p);
   *a_line = atoi (p);
   DEBUG_INPT   yLOG_value   ("*a_line"   , *a_line);
   --rce;  if (*a_line <= 0) {
      strlcpy (a_func, "", LEN_TITLE);
      strlcpy (a_file, "", LEN_TITLE);
      *a_line = -1;
      DEBUG_INPT   yLOG_note    ("line could not be parsed, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern__pointers   (char *a_func, char *a_file, int a_line, tFUNC **a_src, tFUNC **a_dst, tEXTERN **a_ext)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           = " :";
   char       *s           = NULL;
   tFILE      *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_func"    , a_func);
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_file"    , a_file);
   DEBUG_INPT   yLOG_value   ("a_line"    , a_line);
   DEBUG_INPT   yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_src = NULL;
   DEBUG_INPT   yLOG_point   ("a_dst"     , a_dst);
   --rce;  if (a_dst == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_dst = NULL;
   DEBUG_INPT   yLOG_point   ("a_ext"     , a_ext);
   --rce;  if (a_ext == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_ext = NULL;
   /*---(idenfify file)---------------*/
   x_file = (tFILE *) poly_btree_search (B_FILES, a_file);
   DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
   --rce;  if (x_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("file name" , x_file->name);
   /*---(get source tag)--------------*/
   rc = poly_func_search  (x_file, a_line, a_src);
   DEBUG_INPT   yLOG_point   ("*a_scr"    , *a_src);
   --rce;  if (*a_src == NULL) {
      DEBUG_INPT   yLOG_note    ("function not found");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get destination tag)---------*/
   *a_dst   = (tFUNC *)   poly_btree_search  (B_FUNCS, a_func);
   DEBUG_INPT   yLOG_point   ("*a_dst"    , *a_dst);
   *a_ext   = (tEXTERN *) poly_extern_search (a_func);
   DEBUG_INPT   yLOG_point   ("*a_ext"    , *a_ext);
   /*---(mystry)----------------------*/
   --rce;  if (*a_dst == NULL && *a_ext == NULL) {
      /*> if (x_mystry %  5 == 0)  fprintf (s_mystry, "¦");                                                                                           <* 
       *> if (x_mystry % 25 == 0)  fprintf (s_mystry, "##---calling-file-------   line   ---calling-function------   ---mystery-function------¦¦");   <* 
       *> fprintf (s_mystry, "%-25.25s  %4d   %-25.25s   %-25.25s¦",                                                                                  <* 
       *>       x_file->name, x_line, x_src->name, x_funcname);                                                                                       <* 
       *> ++x_src->WORK_MYSTRY;                                                                                                                       <* 
       *> ++x_mystry;                                                                                                                                 <*/
      DEBUG_INPT   yLOG_note    ("found a mystry function");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern__tally      (tFUNC *a_src, tFUNC *a_dst, tEXTERN *a_ext, int a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           = " :";
   char       *s           = NULL;
   tFILE      *x_file      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_dst"     , a_dst);
   DEBUG_INPT   yLOG_point   ("a_ext"     , a_ext);
   --rce;  if (a_dst == NULL && a_ext == NULL) {
      ++a_src->WORK_FUNCS;
      ++a_src->WORK_MYSTRY;
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_dst != NULL && a_ext != NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return 0;
   }
   /*---(general)------------------------*/
   ++a_src->WORK_FUNCS;
   /*---(recursive)----------------------*/
   if (a_src == a_dst) {
      DEBUG_INPT   yLOG_note    ("found a recursive reverence");
      ++a_src->WORK_RECURS;
      --a_src->WORK_FUNCS;
   }
   /*---(internal)-----------------------*/
   else if (a_dst != NULL) {
      DEBUG_INPT   yLOG_note    ("found a local/global internal call");
      DEBUG_INPT   yLOG_point   ("a_src"     , a_src);
      DEBUG_INPT   yLOG_point   ("->file"    , a_src->file);
      DEBUG_INPT   yLOG_point   ("->work"    , a_src->work);
      DEBUG_INPT   yLOG_point   ("a_dst"     , a_dst);
      DEBUG_INPT   yLOG_point   ("->file"    , a_dst->file);
      DEBUG_INPT   yLOG_point   ("->work"    , a_dst->work);
      if      (a_src->file == a_dst->file) {
         ++a_src->WORK_LFUNCS;
         ++a_dst->WORK_LCALLS;
      }
      else if (a_src->file->proj == a_dst->file->proj) {
         ++a_src->WORK_GFUNCS;
         ++a_dst->WORK_GCALLS;
      }
   }
   /*---(debugging)----------------------*/
   else if (strchr ("Dd", a_ext->type) != NULL) {
      DEBUG_INPT   yLOG_char    ("type"      , a_ext->type);
      ++a_src->WORK_DFUNCS;
      switch (a_ext->type) {
      case 'd' :
         ++a_src->WORK_DSHORT;
         switch (a_ext->more) {
         case 'e' :   ++a_src->WORK_DENTER;      break;
         case 'x' :   ++a_src->WORK_DEXIT;       break;
         }
         break;
      case 'D' :
         ++a_src->WORK_DLONG;
         switch (a_ext->more) {
         case 'e' :   ++a_src->WORK_DENTER;      break;
         case 'x' :   ++a_src->WORK_DEXIT;       break;
         }
         break;
      }
   }
   /*---(standard library)---------------*/
   else if (strchr ("-owWirRmpfs", a_ext->type) != NULL) {
      ++a_src->WORK_CSTD;
      switch (a_ext->type) {
      case '-' : break;
      case 'o' : ++a_src->WORK_OUTPUT;           break;
      case 'w' : ++a_src->WORK_WRITE;            break;
      case 'W' : ++a_src->WORK_BWRITE;           break;
      case 'i' : ++a_src->WORK_INPUT;            break;
      case 'r' : ++a_src->WORK_READ;             break;
      case 'R' : ++a_src->WORK_BREAD;            break;
      case 'm' : ++a_src->WORK_MEMORY;           break;
      case 'p' : ++a_src->WORK_PROCS;            break;
      case 'f' : ++a_src->WORK_FILESYS;          break;
      case 's' : ++a_src->WORK_SYSTEM;           break;
      }
   }
   /*---(other libraries)----------------*/
   else {
      switch (a_ext->type) {
      case 'N' : ++a_src->WORK_NCURSE;
                 ++a_src->WORK_OFUNCS;
                 break;
      case 'O' : ++a_src->WORK_OPENGL;
                 ++a_src->WORK_OFUNCS;
                 break;
      case 'X' : ++a_src->WORK_WINDOW;
                 ++a_src->WORK_OFUNCS;
                 break;
      case 'y' : ++a_src->WORK_MYX;
      case 'Y' : ++a_src->WORK_YLIB;
                 poly_ylib_add (a_src, a_ext, a_line, NULL);
                 break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_review      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   char       *p           = NULL;
   char       *q           = NULL;
   char        x_recd      [LEN_RECD];
   char        x_funcname  [LEN_TITLE];
   char        x_filename  [LEN_TITLE];
   int         x_len       =    0;
   int         x_flen      =    0;
   int         x_line      =    0;
   tFILE      *x_file      =    0;
   tFUNC      *x_src       = NULL;
   tFUNC      *x_dst       = NULL;
   tEXTERN    *x_ext       = NULL;
   int         c           =    0;
   char        x_cat       =  ' ';
   int         x_ylibs     =    0;
   int         x_mystry    =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = poly_shared_open ('f', NULL);
   DEBUG_INPT   yLOG_value   ("cflow"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   rc = poly_shared_open ('m', NULL);
   DEBUG_INPT   yLOG_value   ("mystry"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = poly_extern__read (x_recd);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("end of file");
         break;
      }
      /*---(parse)-----------------------*/
      rc = poly_extern__parse (x_recd, x_funcname, x_filename, &x_line);
      DEBUG_INPT   yLOG_value   ("parse"     , rc);
      if (rc < 0)    continue;
      /*---(get pointers)----------------*/
      rc = poly_extern__pointers (x_funcname, x_filename, x_line, &x_src, &x_dst, &x_ext);
      DEBUG_INPT   yLOG_value   ("pointers"  , rc);
      if (rc < 0)    continue;
      /*---(tally results)---------------*/
      rc = poly_extern__tally (x_src, x_dst, x_ext, x_line);
      DEBUG_INPT   yLOG_value   ("tally"     , rc);
      if (rc < 0)    continue;
      /*---(done)------------------------*/
   }
   /*---(wrapup)-------------------------*/
   rc = poly_shared_close ('f');
   DEBUG_INPT   yLOG_value   ("cflow"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   fprintf (my.f_mystry, "¦## done, finito, complete¦");
   rc = poly_shared_close ('m');
   DEBUG_INPT   yLOG_value   ("mystry"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_addylib     (tEXTERN *a_extern, tYLIB *a_ylib)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_extern);
   if (a_extern == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   DEBUG_DATA   yLOG_spoint  (a_ylib);
   if (a_ylib == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_spoint  (a_extern->head);
   DEBUG_DATA   yLOG_spoint  (a_extern->tail);
   if (a_extern->head  == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      a_extern->head  = a_extern->tail  = a_ylib;
   } else {
      DEBUG_DATA   yLOG_snote   ("append");
      a_ylib->eprev         = a_extern->tail;
      a_extern->tail->enext = a_ylib;
      a_extern->tail        = a_ylib;
   }
   /*---(tie tag back to file)-----------*/
   a_ylib->ylib  = a_extern;
   /*---(update count)-------------------*/
   ++a_extern->count;
   DEBUG_DATA   yLOG_sint    (a_extern->count);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char
poly_extern__unit_work  (char a_spc, char a_suf, char a_val, char *a_out)
{
   char        s           [LEN_LABEL] = "";
   if (a_spc == 'y')  sprintf (s, "   ");
   else               sprintf (s, " ");
   strlcat (a_out, s, LEN_RECD);
   if (a_val >  0)    sprintf (s, "%1d%c", a_val, a_suf);
   else               sprintf (s, "·%c"  ,        a_suf);
   strlcat (a_out, s, LEN_RECD);
   return 0;
}

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_extern__unit       (char *a_question, int i)
{
   /*---(locals)-----------+-----+-----+-*/
   tEXTERN    *u           = NULL;
   tFUNC      *v           = NULL;
   char        s           [LEN_RECD]  = "[]";
   char        t           [LEN_RECD]  = "";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "EXTERN unit      : tag number unknown");
   if (i <  0)       return unit_answer;
   u = (tEXTERN *) poly_btree_entry (B_EXTERN, i);
   /*---(simple)-------------------------*/
   if (u != NULL) sprintf  (s, "[%.20s]", u->name);
   if        (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "EXTERN count     : %3d", poly_btree_count (B_EXTERN));
   }
   else if   (strcmp (a_question, "entry"     )     == 0) {
      if (u != NULL)  sprintf  (t, "%2d %-22.22s %c %d", strlen (u->name), s   , u->type, u->uses);
      else            sprintf  (t, "%2d %-22.22s %c %d", 0     , "[]", '-'    , 0       );
      snprintf (unit_answer, LEN_RECD, "EXTERN entry(%2d) : %s", i, t);
   }
   else if   (strcmp (a_question, "work"      )     == 0) {
      v = (tFUNC *) poly_btree_entry (B_FUNCS, i);
      if (v != NULL) {
         sprintf  (s, "[%.13s]", v->name);
         sprintf  (unit_answer, "EXTERN work (%2d) : %-15.15s", i, s);
         poly_extern__unit_work ('y', 'e', v->WORK_ECALLS, unit_answer);
         poly_extern__unit_work ('-', 'g', v->WORK_GCALLS, unit_answer);
         poly_extern__unit_work ('-', 'n', v->WORK_LCALLS, unit_answer);
         poly_extern__unit_work ('-', 'r', v->WORK_RECURS, unit_answer);
         poly_extern__unit_work ('y', 'f', v->WORK_FUNCS , unit_answer);
         poly_extern__unit_work ('-', 'd', v->WORK_DFUNCS, unit_answer);
         poly_extern__unit_work ('-', 'n', v->WORK_LFUNCS, unit_answer);
         poly_extern__unit_work ('-', 'g', v->WORK_GFUNCS, unit_answer);
         poly_extern__unit_work ('-', 'c', v->WORK_CSTD  , unit_answer);
         poly_extern__unit_work ('-', 'y', v->WORK_YLIB  , unit_answer);
         poly_extern__unit_work ('-', 'o', v->WORK_OFUNCS, unit_answer);
         poly_extern__unit_work ('-', 'm', v->WORK_MYSTRY, unit_answer);
         poly_extern__unit_work ('y', 'r', v->WORK_INPUT  + v->WORK_READ   + v->WORK_BREAD  , unit_answer);
         poly_extern__unit_work ('-', 'w', v->WORK_OUTPUT + v->WORK_WRITE  + v->WORK_BWRITE , unit_answer);
         poly_extern__unit_work ('-', 's', v->WORK_PROCS  + v->WORK_SYSTEM + v->WORK_FILESYS, unit_answer);
         poly_extern__unit_work ('y', 'n', v->WORK_NCURSE, unit_answer);
         poly_extern__unit_work ('-', 'o', v->WORK_OPENGL, unit_answer);
         poly_extern__unit_work ('-', 'w', v->WORK_WINDOW, unit_answer);
         poly_extern__unit_work ('-', 'y', v->WORK_MYX   , unit_answer);
      }  else
         snprintf (unit_answer, LEN_RECD, "EXTERN work (%2d) : %-22.22s   ·e ·g ·l   ·f ·d ·n ·g ·c ·y ·o ·m   ·r ·w ·s   ·n ·o ·w ·y", i, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
