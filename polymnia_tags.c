/*============================----beg-of-source---============================*/
#include  "polymnia.h"



#define     F_CTAGS     "polymnia.ctag"
static FILE *s_file = NULL;   /* ctags results file */



/*====================------------------------------------====================*/
/*===----                       support functions                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

tFUNC*
poly_tags_byline        (tFILE *a_file, int a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tFUNC       *u           = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_spoint  ("a_file");
   --rce;  if (a_file == NULL) {
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_PROG   yLOG_sint    (a_line);
   /*---(first)--------------------------*/
   u = a_file->head;
   DEBUG_PROG   yLOG_spoint  (u);
   --rce;  if (u == NULL) {
      DEBUG_PROG   yLOG_snote   ("no tags in file");
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(walk)---------------------------*/
   while (u != NULL) {
      ++c;
      DEBUG_PROG   yLOG_snote   (u->name);
      DEBUG_PROG   yLOG_spoint  (u->work);
      if (u->work == NULL) {
         u = u->next;
         continue;
      }
      DEBUG_PROG   yLOG_sint    (u->WORK_BEG);
      DEBUG_PROG   yLOG_sint    (u->WORK_END);
      if (u->WORK_BEG <= a_line && u->WORK_END >= a_line) {
         DEBUG_PROG   yLOG_snote   ("FOUND");
         DEBUG_PROG   yLOG_sint    (c);
         DEBUG_PROG   yLOG_snote   (u->name);
         DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
         return u;
      }
      u = u->next;
   }
   DEBUG_PROG   yLOG_snote   ("not found");
   DEBUG_PROG   yLOG_sint    (c);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return NULL;
}


/*====================------------------------------------====================*/
/*===----                       inventory tags                         ----===*/
/*====================------------------------------------====================*/
static void  o___INVENTORY_______o () { return; }

char
poly_tags__create       (tFILE *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tSTAT       st;
   int         rci         =    0;
   char        x_cmd       [LEN_RECD];      /* ctags command                  */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file != NULL) {
      DEBUG_INPT   yLOG_note    ("ctags s_file already open with another");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->name);
   /*---(check file)---------------------*/
   rci = lstat (a_file->name, &st);
   DEBUG_INPT   yLOG_value   ("lstat"     , rci);
   --rce; if (rci < 0) {
      DEBUG_INPT   yLOG_note    ("file does not exist, can not read");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(check regular file)-------------*/
   --rce;  if (!S_ISREG (st.st_mode)) {
      DEBUG_INPT   yLOG_note    ("not a regular file, rejected");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(function calls)-----------------*/
   sprintf (x_cmd, "ctags  --language-force=c -x --sort=no --file-scope=yes  --c-kinds=pfl %s > %s", a_file->name, F_CTAGS);
   DEBUG_INPT   yLOG_info    ("system"    , x_cmd);
   rci = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("system"    , rci);
   --rce;  if (rci < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(open)---------------------------*/
   DEBUG_INPT   yLOG_info    ("tag file"  , F_CTAGS);
   s_file = fopen (F_CTAGS, "r");
   DEBUG_INPT   yLOG_point   ("s_file"         , s_file);
   --rce;  if (s_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_note    ("openned successfully");
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_tags__cleanup      (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          =   0;           /* generic return code            */
   char        x_cmd       [LEN_RECD];      /* ctags command                  */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("s_file"    , s_file);
   --rce;  if (s_file == NULL) {
      DEBUG_INPT   yLOG_note    ("ctags s_file not open");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close file)---------------------*/
   rc = fclose (s_file);
   DEBUG_INPT   yLOG_point   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(ground pointer)-----------------*/
   s_file = NULL;
   /*---(clean up files)-----------------*/
   sprintf (x_cmd, "rm -f %s", F_CTAGS);
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
poly_tags__handler      (tFILE *a_file, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   char        rc          =    0;
   char       *p           = NULL;
   char       *q           =  " ";
   char        x_recd      [LEN_RECD];
   char        x_name      [LEN_TITLE];
   int         x_line      =    0;
   char        x_type      =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (x_recd, a_recd, LEN_RECD);
   /*---(get name)-----------------------*/
   p = strtok (x_recd, q);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_note    ("can not find name field, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (x_name, p, LEN_TITLE);
   DEBUG_INPT   yLOG_info    ("name"      , x_name);
   /*---(get type)-----------------------*/
   p = strtok (NULL  , q);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_note    ("can not find type field, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle locals)------------------*/
   --rce;  if (strcmp ("local", p) == 0) {
      DEBUG_INPT   yLOG_note    ("found a local");
      if (a_file->tail == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_INPT   yLOG_info    ("local for" , a_file->tail->name);
      ++(a_file->tail->WORK_LOCALS);
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle prototypes)--------------*/
   if (strcmp ("prototype", p) == 0) {
      DEBUG_INPT   yLOG_note    ("found a prototype");
      /* INSERT LOGIC HERE */
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle prototypes)--------------*/
   --rce;  if (strcmp ("function" , p) != 0) {
      DEBUG_INPT   yLOG_note    ("found something weird");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle functions)---------------*/
   x_type = p [0];
   rc = strncmp ("o___", x_name, 4);
   if (rc == 0)  x_type = '_';
   DEBUG_INPT   yLOG_char    ("type"      , x_type);
   /*---(line)---------------------------*/
   p = strtok (NULL  , q);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_note    ("can not find line field, SKIP");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_line = atoi (p);
   DEBUG_INPT   yLOG_value   ("line"      , x_line);
   --rce;  if (x_line <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(done)---------------------------*/
   rc = poly_func_add (a_file, x_name, x_type, x_line, NULL);
   DEBUG_INPT   yLOG_value   ("function"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> read and parse crontab lines ----------[ ------ [ ------ ]-*/
poly_tags_inventory     (tFILE *a_file)
{  /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   int         rc          =    0;           /* generic return code            */
   char        x_recd      [LEN_RECD];      /* input record                   */
   int         x_len       =    0;             /* length of input record         */
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = poly_tags__create (a_file);
   DEBUG_INPT   yLOG_value   ("create"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk tags)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets  (x_recd, LEN_RECD, s_file);
      if (feof (s_file)) {
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
      /*---(name)------------------------*/
      rc = poly_tags__handler (a_file, x_recd);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("something wrong with record");
         continue;
      }
      /*---(done)------------------------*/
      ++c;
   }
   /*---(wrapup)-------------------------*/
   rc = poly_tags__cleanup ();
   DEBUG_INPT   yLOG_value   ("cleanup"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(summary)------------------------*/
   DEBUG_INPT   yLOG_value   ("c"         , c);
   DEBUG_INPT   yLOG_value   ("count"     , poly_btree_count (B_FUNCS));
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     detailed code review                     ----===*/
/*====================------------------------------------====================*/
static void  o___REVIEW__________o () { return; }

char
poly_tags__linetype     (tFILE *a_file, tFUNC *a_tag)
{
   /*---(locals)-----------+-----------+-*/
   int         i           =    0;
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   char        x_macro     =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(line type)----------------------*/
   strlcpy  (x_recd, my.s_curr, LEN_RECD);
   strltrim (x_recd, ySTR_BOTH, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
   if      (strncmp (x_recd, "DEBUG_"   , 6) == 0) {
      DEBUG_INPT   yLOG_note    ("debug type");
      ++a_tag->WORK_DCOUNT;
      poly_cats_lines (a_file, a_tag, 'D');
      x_macro = poly_debug__macro (x_recd + 6);
      if (a_tag != NULL) {
         if (a_tag->STATS_DMACRO == '-')         a_tag->STATS_DMACRO = x_macro;
         else if (a_tag->STATS_DMACRO != x_macro) {
            if      (a_tag->STATS_DMACRO == 't') a_tag->STATS_DMACRO = x_macro;
            else if (x_macro             == 't') ;
            else                                 a_tag->STATS_DMACRO = '#';
         }
      }
   }
   else if (strncmp (x_recd, "yLOG_"    , 5) == 0)  ++a_tag->WORK_DFREE;
   else if (strncmp (x_recd, "/*"       , 2) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strncmp (x_recd, "* "       , 2) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strncmp (x_recd, "*>"       , 2) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strcmp  (x_recd, "*"           ) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strcmp  (x_recd, "*/"          ) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strlen  (x_recd)                 == 0)  poly_cats_lines (a_file, a_tag, 'e');
   /*---(code line)----------------------*/
   else {
      DEBUG_INPT   yLOG_note    ("code type");
      DEBUG_INPT   yLOG_info    ("my.s_curr"    , my.s_curr);
      poly_cats_lines (a_file, a_tag, 'C');
      if      (strstr (my.s_curr, " return "   ) != NULL) poly_cats_logic (a_tag, 'r');
      if      (strstr (my.s_curr, " return;"   ) != NULL) poly_cats_logic (a_tag, 'r');
      if      (strstr (my.s_curr, " if "       ) != NULL) poly_cats_logic (a_tag, 'c');
      else if (strstr (my.s_curr, " else "     ) != NULL) poly_cats_logic (a_tag, 'c');
      if      (strstr (my.s_curr, " switch "   ) != NULL) poly_cats_logic (a_tag, 'c');
      if      (strstr (my.s_curr, " case "     ) != NULL) poly_cats_logic (a_tag, 'c');
      if      (strstr (my.s_curr, " while "    ) != NULL) poly_cats_logic (a_tag, 'c');
      if      (strstr (my.s_curr, " do "       ) != NULL) poly_cats_logic (a_tag, 'c');
   }
   /*---(indent)-------------------------*/
   if (a_tag != NULL) {
      x_len = strlen (my.s_curr);
      for (i = 0; i < x_len; ++i) {
         if (my.s_curr [i] == ' ')   continue;
         if (i > a_tag->WORK_INDENT) a_tag->WORK_INDENT = i;
         break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_tags_readline      (tFILE *a_file, int *a_line, tFUNC **a_tag)
{
   /*---(locals)-----------+-----------+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   int         x_len       =    0;          /* length of input record         */
   static tFUNC  *a_ptag    = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->name);
   DEBUG_INPT   yLOG_point   ("a_tag"     , a_tag);
   --rce;  if (a_tag == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_point   ("*a_tag"    , *a_tag);
   /*---(update line)-----------------*/
   ++(*a_line);
   DEBUG_INPT   yLOG_value   ("line"      , *a_line);
   /*---(first tag)-------------------*/
   --rce;  if (*a_tag == NULL) {
      a_ptag = *a_tag;
      rc = poly_code_nextfunc (a_file, a_tag);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("no tags in file");
         poly_tags__linetype (a_file, *a_tag);
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(next tag)--------------------*/
   else if (*a_line > (*a_tag)->line) {
      a_ptag  = *a_tag;
      rc = poly_code_nextfunc (a_file, a_tag);
   }
   DEBUG_INPT   yLOG_value   ("line"      , (*a_tag)->line);
   DEBUG_INPT   yLOG_info    ("name"      , (*a_tag)->name);
   /*---(after all tags)--------------*/
   if (*a_tag == a_ptag && a_ptag->WORK_END > 0) {
      poly_tags__linetype (a_file, *a_tag);
      DEBUG_INPT   yLOG_note    ("after last tag");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(found)-----------------------*/
   if (*a_line == (*a_tag)->line) {
      DEBUG_INPT   yLOG_note    ("TAG FOUND");
      poly_code_function (*a_tag, *a_line, my.s_prev);
      /*---(oneliner)-----------------*/
      if ((*a_tag)->STATS_SINGLE == 'y') {
         DEBUG_DATA   yLOG_note    ("processing a one liner");
         (*a_tag)->WORK_BEG  = *a_line;
         poly_tags__linetype (a_file, *a_tag);
         (*a_tag)->WORK_END  = *a_line;
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 1;
      }
      DEBUG_DATA   yLOG_note    ("processing a multi-line header");
      poly_tags__linetype (a_file, a_ptag);
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(process line)----------------*/
   poly_tags__linetype (a_file, a_ptag);
   /*---(before all tags)-------------*/
   if (a_ptag == NULL) {
      DEBUG_INPT   yLOG_note    ("before first tag");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(beginning)-------------------*/
   else if (a_ptag->WORK_BEG <  0) {
      if (my.s_curr [0] == '{')  {
         DEBUG_INPT   yLOG_note    ("beg brace");
         a_ptag->WORK_BEG = *a_line;
      }
   }
   /*---(ending)----------------------*/
   else if (a_ptag->WORK_END <  0) {
      if (my.s_curr [0] == '}') {
         DEBUG_INPT   yLOG_note    ("end brace");
         a_ptag->WORK_END = *a_line;
         --a_ptag->COUNT_LINES;
         --a_ptag->COUNT_CODE;
         DEBUG_INPT   yLOG_note    ("function end");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         /*> poly_cats_tagsumm   (a_ptag);                                            <*/
         return 0;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_note    ("normal line");
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_tags_addylib       (tFUNC *a_tag, tYLIB *a_ylib)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_tag);
   if (a_tag == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   DEBUG_DATA   yLOG_spoint  (a_ylib);
   if (a_ylib == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_spoint  (a_tag->head);
   DEBUG_DATA   yLOG_spoint  (a_tag->tail);
   if (a_tag->head  == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      a_tag->head  = a_tag->tail  = a_ylib;
   } else {
      DEBUG_DATA   yLOG_snote   ("append");
      a_ylib->tprev      = a_tag->tail;
      a_tag->tail->tnext = a_ylib;
      a_tag->tail        = a_ylib;
   }
   /*---(tie tag back to file)-----------*/
   a_ylib->tag   = a_tag;
   /*---(update count)-------------------*/
   ++(a_tag->count);
   DEBUG_DATA   yLOG_sint    (a_tag->count);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_tags__unit      (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   tFUNC      *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "TAGS unit        : tags number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "TAGS count       : %3d", poly_btree_count (B_FUNCS));
      return unit_answer;
   }
   else if (strcmp (a_question, "file"      )     == 0) {
      snprintf (unit_answer, LEN_RECD, "TAGS file        : %c  %-10p  %s", (s_file == NULL) ? '-' : 'y', s_file, F_CTAGS);
      return unit_answer;
   }
   if (strncmp (unit_answer, "TAGS unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "TAGS unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "entry"     )     == 0) {
      u = (tFILE *) poly_btree_entry (B_FUNCS, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->work != NULL)  snprintf (unit_answer, LEN_RECD, "TAGS entry  (%2d) : %-22.22s %3d  %c  work   %3d  %3d", i, t, u->line, u->type, u->WORK_BEG, u->WORK_END);
         else                  snprintf (unit_answer, LEN_RECD, "TAGS entry  (%2d) : %-22.22s %3d  %c  non      -    -", i, t, u->line, u->type);
      } else                   snprintf (unit_answer, LEN_RECD, "TAGS entry  (%2d) : %-22.22s   -  -  -        -    -", i, t);
   }
   else if (strcmp (a_question, "stats"     )     == 0) {
      u = (tFILE *) poly_btree_entry (B_FUNCS, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         snprintf (unit_answer, LEN_RECD, "TAGS stats  (%2d) : %-22.22s     �   �   %3d %3d %3d %3d %3d %3d", i, t, u->COUNT_LINES, u->COUNT_EMPTY, u->COUNT_DOCS, u->COUNT_DEBUG, u->COUNT_CODE, u->COUNT_SLOCL);
      }  else
         snprintf (unit_answer, LEN_RECD, "TAGS stats  (%2d) : %-22.22s     �   �     -   -   -   -   -   -", i, t, 0, 0, 0, 0, 0, 0);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




