/*============================----beg-of-source---============================*/
#include  "polymnia.h"

/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
static      tEXTERN    *s_head      = NULL;
static      tEXTERN    *s_tail      = NULL;
static      int         s_count     = 0;
static      tEXTERN    *s_root      = NULL;

int   g_depth   = 0;
char  g_path    [LEN_LABEL] = "";


/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_extern__add         (char *a_name, char a_type)
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
   --rce;  if (x_len == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
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
   strlcpy (x_new->name, a_name, LEN_NAME);
   x_new->type   = a_type;
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
   rc = poly_btree_purge (B_EXTERN);
   DEBUG_PROG   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
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
poly_extern_load        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   char        x_type      =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(purge existing)-----------------*/
   rc = poly_btree_purge (B_EXTERN);
   /*---(open)---------------------------*/
   f_extern = fopen (F_EXTERN, "rt");
   DEBUG_INPT   yLOG_point   ("f_extern"          , f_extern);
   --rce;  if (f_extern == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets (x_recd, LEN_RECD, f_extern);
      if (feof (f_extern)) {
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
      if (strncmp (x_recd, "##", 2) == 0) {
         DEBUG_INPT   yLOG_note    ("header line, SKIP");
         continue;
      }
      if (x_recd [0] == '#') {
         DEBUG_INPT   yLOG_note    ("category line, SKIP");
         continue;
      }
      /*---(type)------------------------*/
      x_type = '-';
      if (x_len >= 25) {
         x_type = x_recd [24];
         x_recd [24] = '\0';
      }
      /*---(save)------------------------*/
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      poly_extern__add (x_recd, x_type);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = fclose (f_extern);
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
poly_extern__extracts   (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          =   0;           /* generic return code            */
   char        x_cmd       [LEN_RECD];      /* ctags command                  */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(function calls)-----------------*/
   sprintf (x_cmd, "cflow -x $(ls -1 *.c | grep -v unit) 2> /dev/null > %s", F_CFLOW);
   DEBUG_INPT   yLOG_info    ("system"    , x_cmd);
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern__cleanup    (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          =   0;           /* generic return code            */
   char        x_cmd       [LEN_RECD];      /* ctags command                  */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(function calls)-----------------*/
   sprintf (x_cmd, "rm -f %s", F_CFLOW);
   DEBUG_INPT   yLOG_info    ("system"    , x_cmd);
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
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
   char        x_funcname  [LEN_NAME];
   char        x_filename  [LEN_NAME];
   int         x_len       =    0;
   int         x_flen      =    0;
   int         x_line      =    0;
   tFILE      *x_file      =    0;
   tTAG       *x_src       = NULL;
   tTAG       *x_dst       = NULL;
   tEXTERN    *x_extern    = NULL;
   int         c           =    0;
   char        x_cat       =  ' ';
   int         x_ylibs     =    0;
   int         x_mystry    =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   poly_extern__extracts ();
   DEBUG_INPT   yLOG_value   ("extracts"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(open)---------------------------*/
   DEBUG_INPT   yLOG_info    ("cflow file" , F_CFLOW);
   f_flow = fopen (F_CFLOW, "rt");
   DEBUG_INPT   yLOG_point   ("f_flow"          , f_flow);
   --rce;  if (f_flow == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("ylib file"  , F_YLIB);
   f_ylib   = fopen (F_YLIB, "wt");
   DEBUG_INPT   yLOG_point   ("f_ylib"          , f_ylib);
   --rce;  if (f_ylib == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("mystry file", F_MYSTRY);
   f_mystry = fopen (F_MYSTRY, "wt");
   DEBUG_INPT   yLOG_point   ("f_mystry"        , f_mystry);
   --rce;  if (f_mystry == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets  (x_recd, LEN_RECD, f_flow);
      if (feof (f_flow)) {
         DEBUG_INPT   yLOG_note    ("end of file");
         break;
      }
      /*---(filter)----------------------*/
      x_len = strlen (x_recd);
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      if (x_len < 10) {
         DEBUG_INPT   yLOG_note    ("too short, SKIP");
         continue;
      }
      x_recd [--x_len] = '\0';
      DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
      /*---(get function)----------------*/
      p = strchr (x_recd, ' ');
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("space not found, SKIP");
         continue;
      }
      DEBUG_INPT   yLOG_value   ("space"     , p - x_recd + 1);
      strlcpy (x_funcname, x_recd, p - x_recd + 1);
      DEBUG_INPT   yLOG_info    ("func name" , x_funcname);
      /*---(get if definition)-----------*/
      DEBUG_INPT   yLOG_char    ("def mark"  , p [1]);
      if (p [1] == '*') {
         DEBUG_INPT   yLOG_note    ("function definition, SKIP");
         continue;
      }
      /*---(get file)--------------------*/
      p += 3;
      DEBUG_INPT   yLOG_info    ("p"         , p);
      q = strchr (p, ':');
      if (q == NULL) {
         DEBUG_INPT   yLOG_note    ("did not find line marker, SKIP");
         continue;
      }
      q [0] = '\0';
      strlcpy (x_filename, p, LEN_NAME);
      DEBUG_INPT   yLOG_info    ("file name" , x_filename);
      x_file = (tFILE *) poly_btree_search (B_FILES, x_filename);
      if (x_file == NULL) {
         DEBUG_INPT   yLOG_note    ("file not found");
         continue;
      }
      DEBUG_INPT   yLOG_info    ("file name" , x_file->name);
      /*---(get line)--------------------*/
      ++q;
      DEBUG_INPT   yLOG_info    ("line str"  , q);
      x_line = atoi (q);
      DEBUG_INPT   yLOG_value   ("x_line"    , x_line);
      if (x_line <= 0) {
         DEBUG_INPT   yLOG_note    ("line could not be parsed, SKIP");
         continue;
      }
      /*---(get source tag)--------------*/
      x_src = poly_tags_byline (x_file, x_line);
      DEBUG_INPT   yLOG_point   ("x_scr"     , x_src);
      if (x_src == NULL) {
         DEBUG_INPT   yLOG_note    ("source tag not found");
         continue;
      }
      /*---(get destination tag)---------*/
      x_dst    = (tTAG *)    poly_btree_search  (B_TAGS, x_funcname);
      DEBUG_INPT   yLOG_point   ("x_dst"     , x_dst);
      x_extern = (tEXTERN *) poly_extern_search (x_funcname);
      DEBUG_INPT   yLOG_point   ("x_extern"  , x_extern);
      /*---(mystry)----------------------*/
      if (x_dst == NULL && x_extern == NULL) {
         if (x_mystry %  5 == 0)  fprintf (f_mystry, "\n");
         if (x_mystry % 25 == 0)  fprintf (f_mystry, "##---calling-file-------   line   ---calling-function------   ---mystery-function------\n\n");
         fprintf (f_mystry, "%-25.25s  %4d   %-25.25s   %-25.25s\n",
               x_file->name, x_line, x_src->name, x_funcname);
         ++x_mystry;
         DEBUG_INPT   yLOG_note    ("found a mystry function");
         continue;
      }
      /*---(tally)-----------------------*/
      ++x_src->work->funcs;
      if (x_src == x_dst) {
         DEBUG_INPT   yLOG_note    ("found a recursive reverence");
         ++x_src->work->recurse;
         continue;
      }
      if (x_dst != NULL) {
         DEBUG_INPT   yLOG_note    ("found a local/global internal call");
         DEBUG_INPT   yLOG_point   ("x_src"     , x_src);
         DEBUG_INPT   yLOG_point   ("->file"    , x_src->file);
         DEBUG_INPT   yLOG_point   ("->work"    , x_src->work);
         DEBUG_INPT   yLOG_point   ("x_dst"     , x_dst);
         DEBUG_INPT   yLOG_point   ("->file"    , x_dst->file);
         DEBUG_INPT   yLOG_point   ("->work"    , x_dst->work);
         if      (x_src->file == x_dst->file)  ++x_dst->work->lcalls;
         else if (x_src->file->proj == x_dst->file->proj)  ++x_dst->work->gcalls;
         ++x_src->work->intern;
         continue;
      }
      if (x_extern != NULL) {
         DEBUG_INPT   yLOG_char    ("type"      , x_extern->type);
         switch (x_extern->type) {
         case 'd' :
            --x_src->work->funcs;
            ++x_src->work->dshort;
            break;
         case 'D' :
            --x_src->work->funcs;
            ++x_src->work->dlong;
            break;
         case '-' :
            ++x_src->work->cstd;
            break;
         case 'w' :
            ++x_src->work->cstd;
            ++x_src->work->writes;
            break;
         case 'r' :
            ++x_src->work->cstd;
            ++x_src->work->reads;
            break;
         case 'n' :
            ++x_src->work->ncurses;
            break;
         case 'o' :
            ++x_src->work->opengl;
            break;
         case 'm' :
            ++x_src->work->cstd;
            ++x_src->work->memories;
            break;
         case 'p' :
            ++x_src->work->cstd;
            ++x_src->work->process;
            break;
         case 's' :
            ++x_src->work->cstd;
            ++x_src->work->scalls;
            break;
         case 'y' :
            ++x_src->work->myx;
         case 'Y' :
            ++x_src->work->ylibs;
            if (x_ylibs %  5 == 0)  fprintf (f_ylib, "\n");
            if (x_ylibs % 25 == 0)  fprintf (f_ylib, "##---ylib-function-------   ---calling-file----------   line   ---calling-function------\n\n");
            fprintf (f_ylib, "%-25.25s   %-25.25s   %4d   %-25.25s\n", x_funcname, x_file->name, x_line, x_src->name);
            ++x_ylibs;
            break;
         }
      }
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = fclose (f_flow);
   DEBUG_INPT   yLOG_value   ("flow close" , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   fprintf (f_ylib, "\n## done, finito, complete\n");
   rc = fclose (f_ylib);
   DEBUG_INPT   yLOG_value   ("ylib close" , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   fprintf (f_mystry, "\n## done, finito, complete\n");
   rc = fclose (f_mystry);
   DEBUG_INPT   yLOG_value   ("mystry clos", rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(wrapup)-------------------------*/
   poly_extern__cleanup ();
   DEBUG_INPT   yLOG_value   ("cleanup"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_extern__unit       (char *a_question, int i)
{
   /*---(locals)-----------+-----+-----+-*/
   tEXTERN    *u           = NULL;
   char        s           [LEN_RECD]  = "[]";
   char        t           [LEN_RECD]  = "";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "EXTERN unit      : tag number unknown");
   if (i <  0)       return unit_answer;
   u = (tEXTERN *) poly_btree_entry (B_EXTERN, i);
   /*---(simple)-------------------------*/
   if (u != NULL) sprintf  (s, "[%.20s]", u->name);
   if        (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "EXTERN count     : %3d", s_count);
   }
   else if   (strcmp (a_question, "entry"     )     == 0) {
      if (u != NULL)  sprintf  (t, "%2d %-22.22s %c %d", strlen (u->name), s   , u->type, u->count);
      else            sprintf  (t, "%2d %-22.22s %c %d", 0     , "[]", '-'    , 0       );
      snprintf (unit_answer, LEN_RECD, "EXTERN entry(%2d) : %s", i, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
