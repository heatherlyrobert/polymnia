/*============================----beg-of-source---============================*/
#include  "polymnia.h"




/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }
/*>                                                                                                <* 
 *> char                                                                                           <* 
 *> poly_tags_add           (tFILE *a_file, char *a_name, char a_type, int a_line, tFUNC **a_tag)   <* 
 *> {                                                                                              <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                    <* 
 *>    char        rce         =  -10;                                                             <* 
 *>    char        rc          =    0;                                                             <* 
 *>    tFUNC       *x_new       = NULL;                                                             <* 
 *>    int         x_tries     =    0;                                                             <* 
 *>    int         x_len       =    0;                                                             <* 
 *>    /+---(begin)--------------------------+/                                                    <* 
 *>    DEBUG_DATA   yLOG_enter   (__FUNCTION__);                                                   <* 
 *>    /+---(defense)------------------------+/                                                    <* 
 *>    DEBUG_DATA   yLOG_point   ("a_file"    , a_file);                                           <* 
 *>    --rce;  if (a_file == NULL) {                                                               <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
 *>       return rce;                                                                              <* 
 *>    }                                                                                           <* 
 *>    DEBUG_DATA   yLOG_point   ("a_name"    , a_name);                                           <* 
 *>    --rce;  if (a_name == NULL) {                                                               <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
 *>       return rce;                                                                              <* 
 *>    }                                                                                           <* 
 *>    DEBUG_DATA   yLOG_info    ("a_name"    , a_name);                                           <* 
 *>    DEBUG_DATA   yLOG_char    ("a_type"    , a_type);                                           <* 
 *>    --rce;  if (a_type == '\0' || strchr ("f_", a_type) == NULL) {                              <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
 *>       return rce;                                                                              <* 
 *>    }                                                                                           <* 
 *>    DEBUG_DATA   yLOG_value   ("a_line"    , a_line);                                           <* 
 *>    --rce;  if (a_line <= 0) {                                                                  <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
 *>       return rce;                                                                              <* 
 *>    }                                                                                           <* 
 *>    DEBUG_DATA   yLOG_point   ("a_tag"     , a_tag);                                            <* 
 *>    /+---(check return)-------------------+/                                                    <* 
 *>    DEBUG_DATA   yLOG_point   ("a_tag"     , a_tag);                                            <* 
 *>    DEBUG_DATA   yLOG_point   ("*a_tag"    , *a_tag);                                           <* 
 *>    --rce;  if (a_tag != NULL) {                                                                <* 
 *>       if (*a_tag != NULL) {                                                                    <* 
 *>          DEBUG_DATA   yLOG_note    ("already set to a particular tag");                        <* 
 *>          DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
 *>          return rce;                                                                           <* 
 *>       }                                                                                        <* 
 *>    }                                                                                           <* 
 *>    /+---(create tag)---------------------+/                                                    <* 
 *>    x_new = poly_func_new ();                                                                   <* 
 *>    DEBUG_DATA   yLOG_point   ("x_new"     , x_new);                                            <* 
 *>    --rce;  if (x_new == NULL) {                                                                <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
 *>       return rce;                                                                              <* 
 *>    }                                                                                           <* 
 *>    /+---(create cell)--------------------+/                                                    <* 
 *>    x_new->work = poly_tags__new_work ();                                                       <* 
 *>    DEBUG_DATA   yLOG_point   ("->work"    , x_new->work);                                      <* 
 *>    --rce;  if (x_new->work == NULL) {                                                          <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
 *>       return rce;                                                                              <* 
 *>    }                                                                                           <* 
 *>    /+---(populate)-----------------------+/                                                    <* 
 *>    DEBUG_DATA   yLOG_note    ("populate");                                                     <* 
 *>    x_new->file   = a_file;                                                                     <* 
 *>    strlcpy (x_new->name, a_name, LEN_TITLE);                                                   <* 
 *>    x_new->type   = a_type;                                                                     <* 
 *>    x_new->line   = a_line;                                                                     <* 
 *>    /+---(into file list)-----------------+/                                                    <* 
 *>    rc = poly_files_tag_hook   (a_file, x_new);                                                 <* 
 *>    DEBUG_DATA   yLOG_value   ("addtag"    , rc);                                               <* 
 *>    --rce;  if (rc < 0) {                                                                       <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
 *>       return rce;                                                                              <* 
 *>    }                                                                                           <* 
 *>    /+---(into btree)---------------------+/                                                    <* 
 *>    rc = poly_btree_hook (B_FUNCS, x_new, x_new->name, &x_new->btree);                           <* 
 *>    DEBUG_DATA   yLOG_value   ("btree"     , rc);                                               <* 
 *>    --rce;  if (rc < 0) {                                                                       <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
 *>       return rce;                                                                              <* 
 *>    }                                                                                           <* 
 *>    /+---(create hint)--------------------+/                                                    <* 
 *>    rc = poly_func__hint    (poly_btree_count (B_FUNCS) - 1, x_new->hint);                        <* 
 *>    DEBUG_DATA   yLOG_value   ("hint"      , rc);                                               <* 
 *>    --rce;  if (rc < 0) {                                                                       <* 
 *>       DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                                           <* 
 *>       return rce;                                                                              <* 
 *>    }                                                                                           <* 
 *>    DEBUG_DATA   yLOG_info    ("hint"      , x_new->hint);                                      <* 
 *>    /+---(save)---------------------------+/                                                    <* 
 *>    if (a_tag != NULL)  *a_tag = x_new;                                                         <* 
 *>    /+---(complete)-----------------------+/                                                    <* 
 *>    DEBUG_DATA   yLOG_exit    (__FUNCTION__);                                                   <* 
 *>    return 0;                                                                                   <* 
 *> }                                                                                              <*/



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
poly_tags__extracts     (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          =   0;           /* generic return code            */
   char        x_cmd       [LEN_RECD];      /* ctags command                  */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(function calls)-----------------*/
   sprintf (x_cmd, "ctags  --language-force=c -x --sort=no --file-scope=yes  --c-kinds=pfl %s > %s", a_name, F_CTAGS);
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
poly_tags__cleanup      (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         rc          =   0;           /* generic return code            */
   char        x_cmd       [LEN_RECD];      /* ctags command                  */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(function calls)-----------------*/
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

char         /*--> read and parse crontab lines ----------[ ------ [ ------ ]-*/
poly_tags_inventory     (tFILE *a_file)
{  /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   int         rc          =    0;           /* generic return code            */
   char        x_recd      [LEN_RECD];      /* input record                   */
   int         x_len       =    0;             /* length of input record         */
   char       *p           = NULL;
   char       *q           =  " ";
   int         c           =    0;
   char        x_name      [LEN_TITLE];
   int         x_line      =    0;
   char        x_type      =  '-';
   char        x_source    [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->name);
   /*---(prepare)------------------------*/
   poly_tags__extracts (a_file->name);
   DEBUG_INPT   yLOG_value   ("extracts"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(open)---------------------------*/
   DEBUG_INPT   yLOG_info    ("tag file"  , F_CTAGS);
   my.f_tags = fopen (F_CTAGS, "r");
   DEBUG_INPT   yLOG_point   ("my.f_tags"         , my.f_tags);
   --rce;  if (my.f_tags == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_note    ("openned successfully");
   /*---(walk tags)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets  (x_recd, LEN_RECD, my.f_tags);
      if (feof (my.f_tags)) {
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
      p = strtok (x_recd, q);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("can not find name field, SKIP");
         continue;
      }
      strlcpy (x_name, p, LEN_TITLE);
      DEBUG_INPT   yLOG_info    ("name"      , x_name);
      /*---(type)------------------------*/
      p = strtok (NULL  , q);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("can not find type field, SKIP");
         continue;
      }
      if (strcmp ("local", p) == 0) {
         DEBUG_INPT   yLOG_note    ("found a local");
         if (a_file->tail != NULL) {
            DEBUG_INPT   yLOG_info    ("local for" , a_file->tail->name);
            ++(a_file->tail->WORK_LOCALS);
         }
         continue;
      }
      if (strcmp ("function", p) != 0) {
         DEBUG_INPT   yLOG_note    ("not a function, SKIP");
         continue;
      }
      x_type = p [0];
      rc = strncmp ("o___", x_name, 4);
      /*> printf ("%-20.20s  %d\n", x_name, rc);                                      <*/
      if (rc != 0)  x_type = '_';
      DEBUG_INPT   yLOG_char    ("type"      , x_type);
      /*---(line)------------------------*/
      p = strtok (NULL  , q);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("can not find line field, SKIP");
         continue;
      }
      x_line = atoi (p);
      DEBUG_INPT   yLOG_value   ("line"      , x_line);
      /*---(done)------------------------*/
      poly_func_add (a_file, x_name, x_type, x_line, NULL);
      ++c;
   }
   rc = fclose (my.f_tags);
   DEBUG_INPT   yLOG_point   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   my.f_tags = NULL;
   /*---(wrapup)-------------------------*/
   poly_tags__cleanup ();
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

char         /*-> extract the function desc ----------[ ------ [ge.850.137.A4]*/ /*-[02.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_tags__desc         (tFUNC *a_tag, char *a_beg)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       x_desc       [LEN_RECD];
   int        i            =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_beg == NULL) {
      a_tag->ready = 'e';
      return rce;
   }
   --rce;  if (strlen (my.s_prev) < 70) {
      return rce;
   }
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(current style)------------------*/
   if (strncmp (a_beg, "/*-> ", 5) == 0) {
      DEBUG_INPT   yLOG_snote   ("current format");
      strlcpy (x_desc, a_beg + 5, 35);
      for (i = 35; i > 0; --i)  {
         if (strchr (" -=]", x_desc [i]) == NULL)   break;
         x_desc [i] = '\0';
      }
      strlcpy (a_tag->desc, x_desc, 35);
      a_tag->ready = 'y';
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_beg, "/*--> ",  6) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 1 format");
      strlcpy (x_desc, a_beg +  6, 35);
      for (i = 35; i > 0; --i)  {
         if (strchr (" -=]", x_desc [i]) == NULL)   break;
         x_desc [i] = '\0';
      }
      strlcpy (a_tag->desc, x_desc, 35);
      a_tag->ready = 'y';
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_beg, "/* ---- : ", 10) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 2 format");
      strlcpy (x_desc, a_beg + 10, 35);
      for (i = 35; i > 0; --i)  {
         if (strchr (" -=]", x_desc [i]) == NULL)   break;
         x_desc [i] = '\0';
      }
      strlcpy (a_tag->desc, x_desc, 35);
      a_tag->ready = 'y';
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_beg, "/*----: ",  8) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 3 format");
      strlcpy (x_desc, a_beg +  8, 35);
      for (i = 35; i > 0; --i)  {
         if (strchr (" -=]", x_desc [i]) == NULL)   break;
         x_desc [i] = '\0';
      }
      strlcpy (a_tag->desc, x_desc, 35);
      a_tag->ready = 'y';
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(previous style)-----------------*/
   if (strncmp (a_beg, "/*===[[ ",  8) == 0) {
      DEBUG_INPT   yLOG_snote   ("previous 3 format");
      strlcpy (x_desc, a_beg +  8, 35);
      for (i = 35; i > 0; --i)  {
         if (strchr (" -=]", x_desc [i]) == NULL)   break;
         x_desc [i] = '\0';
      }
      strlcpy (a_tag->desc, x_desc, 35);
      a_tag->ready = 'y';
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_tags__scope        (tFUNC *a_tag, int a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   char       *r           = NULL;
   char       *a           = NULL;
   char       *b           = NULL;
   int        x_len        =    0;
   char       x_return     [LEN_RECD];
   char       x_params     [LEN_RECD];
   char       x_body       [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_value   ("a_line"    , a_line);
   /*---(oneline)------------------------*/
   p = strstr (my.s_curr, a_tag->name);
   DEBUG_DATA   yLOG_point   ("p"         , p);
   x_len = p - my.s_curr;
   DEBUG_DATA   yLOG_value   ("x_len"     , x_len);
   if (x_len == 0)   a_tag->STATS_SINGLE = '-';
   else              a_tag->STATS_SINGLE = 'y';
   DEBUG_DATA   yLOG_char    ("oneline"   , a_tag->STATS_SINGLE);
   /*---(oneline return type)------------*/
   if (a_tag->STATS_SINGLE == 'y') {
      strlcpy (x_return, my.s_curr, x_len);
      a_tag->ready = ' ';
   }
   /*---(multiline return type)----------*/
   else {
      r = strstr (my.s_prev, "/*");
      if (r == NULL)  x_len = strlen (my.s_prev);
      else            x_len = r - my.s_prev;
      strlcpy (x_return, my.s_prev, x_len + 1);
      poly_tags__desc (a_tag, r);
   }
   strltrim (x_return, ySTR_SINGLE, LEN_RECD);
   DEBUG_DATA   yLOG_info    ("x_return"  , x_return);
   /*---(classify return type)-----------*/
   if      (strstr (x_return   , "char*" ) != NULL)  a_tag->STATS_RTYPE = 's';
   else if (strstr (x_return   , "char"  ) != NULL)  a_tag->STATS_RTYPE = 'c';
   else if (strstr (x_return   , "void"  ) != NULL)  a_tag->STATS_RTYPE = 'v';
   else if (strstr (x_return   , "*"     ) != NULL)  a_tag->STATS_RTYPE = 'p';
   else                                              a_tag->STATS_RTYPE = 'n';
   DEBUG_DATA   yLOG_char    ("rtype"     , a_tag->STATS_RTYPE);
   /*---(classify scope)-----------------*/
   if      (strstr (a_tag->name, "__unit") != NULL)  a_tag->STATS_SCOPE = 'u';
   else if (strstr (a_tag->name, "__test") != NULL)  a_tag->STATS_SCOPE = 'u';
   else if (strstr (x_return   , "static") != NULL)  a_tag->STATS_SCOPE = 's';
   else if (strstr (a_tag->name, "__"    ) != NULL)  a_tag->STATS_SCOPE = 'f';
   else                                              a_tag->STATS_SCOPE = 'g';
   DEBUG_DATA   yLOG_char    ("scope"     , a_tag->STATS_SCOPE);
   /*---(parms)--------------------------*/
   a = strchr (p, '(');
   if (a != NULL) {
      DEBUG_DATA   yLOG_note    ("found open paren");
      b = strchr (p, '{');
      if (b == NULL)  x_len = LEN_RECD;
      else            x_len = b - a;
      strlcpy  (x_params         , a, x_len);
      strltrim (x_params         , ySTR_EVERY , x_len);
      a_tag->WORK_PARAMS = -3;
      if      (strcmp (x_params, "()")     == 0)  a_tag->WORK_PARAMS = -2;
      else if (strcmp (x_params, "(void)") == 0)  a_tag->WORK_PARAMS =  0;
      else    a_tag->WORK_PARAMS = strldcnt (x_params, ',', x_len) + 1;
      if (strstr (x_params, "**"       ) != NULL)  a_tag->STATS_PTWO = '#';
      if (strstr (x_params, "float*"   ) != NULL)  a_tag->STATS_PNUM = '#';
      if (strstr (x_params, "double*"  ) != NULL)  a_tag->STATS_PNUM = '#';
      if (strstr (x_params, "short*"   ) != NULL)  a_tag->STATS_PNUM = '#';
      if (strstr (x_params, "int*"     ) != NULL)  a_tag->STATS_PNUM = '#';
      if (strstr (x_params, "long*"    ) != NULL)  a_tag->STATS_PNUM = '#';
   } else {
      a_tag->WORK_PARAMS = -2;
   }
   poly_cats_exact   ("nparam"  , a_tag->WORK_PARAMS  , &a_tag->STATS_PARAMS, '0');
   /*---(one-liner)----------------------*/
   if (a_tag->STATS_SINGLE == 'y') {
      if (b != NULL) {
         p = strchr (b, '}');
         x_len = p - b;
         strlcpy  (x_body, b, x_len);
         strltrim (x_body, ySTR_EVERY , x_len);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

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
      rc = poly_files_nexttag (a_file, a_tag);
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
      rc = poly_files_nexttag (a_file, a_tag);
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
      poly_tags__scope (*a_tag, *a_line);
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
poly_tags__unquote      (char *a_dst, char *a_src, int a_max)
{
   char       *x_beg       = NULL;
   char       *x_end       = NULL;
   int         x_len       =    0;
   if (a_src [0] != '"')  return 0;
   x_beg = a_src + 1;
   x_end = strrchr (x_beg, '"');
   if (x_end == NULL)  return 0;
   x_len = x_end - x_beg + 1;
   if (x_len > a_max)  x_len = a_max;
   strlcpy (a_dst, x_beg, x_len);
   a_dst [x_len] = '\0';
   return 0;
}

char
poly_tags_review        (tFILE *a_file)
{
   /*---(locals)-----------+-----------+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   char        x_recd      [LEN_RECD];      /* input record                   */
   int         x_len       =    0;          /* length of input record         */
   int         x_line      =    0;
   tFUNC       *x_tag       = NULL;
   char       *p           = NULL;
   char       *q           = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open file)----------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->name);
   my.f_prog = fopen (a_file->name, "r");
   DEBUG_INPT   yLOG_point   ("my.f_prog"         , my.f_prog);
   --rce;  if (my.f_prog == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   while (rc >= 0) {
      /*---(read)------------------------*/
      strlcpy (my.s_pprev, my.s_prev, LEN_RECD);
      strlcpy (my.s_prev , my.s_curr, LEN_RECD);
      fgets  (my.s_curr, LEN_RECD, my.f_prog);
      --rce;  if (feof (my.f_prog))  {
         DEBUG_INPT   yLOG_note    ("end of file");
         break;
      }
      x_len = strlen (my.s_curr);
      my.s_curr [--x_len] = '\0';
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      if (a_file->type == 'h') {
         DEBUG_INPT   yLOG_note    ("header file line");
         DEBUG_INPT   yLOG_info    ("my.s_curr"    , my.s_curr);
         /*---(master)-------------------*/
         if (strncmp (my.s_curr, "#define     P_FOCUS     ", 24) == 0)  poly_tags__unquote (a_file->proj->focus   , my.s_curr + 24, LEN_TITLE);
         if (strncmp (my.s_curr, "#define     P_NICHE     ", 24) == 0)  poly_tags__unquote (a_file->proj->niche   , my.s_curr + 24, LEN_TITLE);
         if (strncmp (my.s_curr, "#define     P_SUBJECT   ", 24) == 0)  poly_tags__unquote (a_file->proj->subject , my.s_curr + 24, LEN_TITLE);
         if (strncmp (my.s_curr, "#define     P_PURPOSE   ", 24) == 0)  poly_tags__unquote (a_file->proj->purpose , my.s_curr + 24, LEN_HUND);
         /*---(greek)--------------------*/
         if (strncmp (my.s_curr, "#define     P_NAMESAKE  ", 24) == 0)  poly_tags__unquote (a_file->proj->namesake, my.s_curr + 24, LEN_HUND);
         if (strncmp (my.s_curr, "#define     P_HERITAGE  ", 24) == 0)  poly_tags__unquote (a_file->proj->heritage, my.s_curr + 24, LEN_HUND);
         if (strncmp (my.s_curr, "#define     P_IMAGERY   ", 24) == 0)  poly_tags__unquote (a_file->proj->imagery , my.s_curr + 24, LEN_HUND);
         if (strncmp (my.s_curr, "#define     P_REASON    ", 24) == 0)  poly_tags__unquote (a_file->proj->reason  , my.s_curr + 24, LEN_HUND);
         if (strncmp (my.s_curr, "#define     P_ONELINE   ", 24) == 0)  sprintf (a_file->proj->oneline, "%s %s", a_file->proj->namesake, a_file->proj->subject);
         /*---(location)-----------------*/
         if (strncmp (my.s_curr, "#define     P_BASENAME  ", 24) == 0)  poly_tags__unquote (a_file->proj->progname, my.s_curr + 24, LEN_TITLE);
         if (strncmp (my.s_curr, "#define     P_FULLPATH  ", 24) == 0)  poly_tags__unquote (a_file->proj->fullpath, my.s_curr + 24, LEN_HUND);
         if (strncmp (my.s_curr, "#define     P_SUFFIX    ", 24) == 0)  poly_tags__unquote (a_file->proj->suffix  , my.s_curr + 24, LEN_LABEL);
         if (strncmp (my.s_curr, "#define     P_CONTENT   ", 24) == 0)  poly_tags__unquote (a_file->proj->content , my.s_curr + 24, LEN_TITLE);
         /*---(chars)--------------------*/
         if (strncmp (my.s_curr, "#define     P_SYSTEM    ", 24) == 0)  poly_tags__unquote (a_file->proj->systems , my.s_curr + 24, LEN_HUND);
         if (strncmp (my.s_curr, "#define     P_LANGUAGE  ", 24) == 0)  poly_tags__unquote (a_file->proj->language, my.s_curr + 24, LEN_HUND);
         if (strncmp (my.s_curr, "#define     P_CODESIZE  ", 24) == 0)  poly_tags__unquote (a_file->proj->codesize, my.s_curr + 24, LEN_DESC);
         /*---(created)------------------*/
         if (strncmp (my.s_curr, "#define     P_AUTHOR    ", 24) == 0)  poly_tags__unquote (a_file->proj->author  , my.s_curr + 24, LEN_TITLE);
         if (strncmp (my.s_curr, "#define     P_CREATED   ", 24) == 0)  poly_tags__unquote (a_file->proj->created , my.s_curr + 24, LEN_LABEL);
         if (strncmp (my.s_curr, "#define     P_DEPENDS   ", 24) == 0)  poly_tags__unquote (a_file->proj->depends , my.s_curr + 24, LEN_HUND);
         /*---(version)------------------*/
         if (strncmp (my.s_curr, "#define     P_VERMAJOR  ", 24) == 0)  poly_tags__unquote (a_file->proj->vermajor, my.s_curr + 24, LEN_HUND);
         if (strncmp (my.s_curr, "#define     P_VERMINOR  ", 24) == 0)  poly_tags__unquote (a_file->proj->verminor, my.s_curr + 24, LEN_HUND);
         if (strncmp (my.s_curr, "#define     P_VERNUM    ", 24) == 0)  poly_tags__unquote (a_file->proj->vernum  , my.s_curr + 24, LEN_LABEL);
         if (strncmp (my.s_curr, "#define     P_VERTXT    ", 24) == 0)  poly_tags__unquote (a_file->proj->vertxt  , my.s_curr + 24, LEN_HUND);
         /*> if ((p = strstr (my.s_curr, "VER_NUM")) != 0) {                          <* 
          *>    q = strchr (p, '"');                                                  <* 
          *>    x_len = strlen (q);                                                   <* 
          *>    q [--x_len] = '\0';                                                   <* 
          *>    if (q != NULL)  strlcpy (a_file->proj->vernum, q + 1, LEN_LABEL);     <* 
          *> }                                                                        <* 
          *> if ((p = strstr (my.s_curr, "VER_TXT")) != 0) {                          <* 
          *>    q = strchr (p, '"');                                                  <* 
          *>    x_len = strlen (q);                                                   <* 
          *>    q [--x_len] = '\0';                                                   <* 
          *>    if (q != NULL)  strlcpy (a_file->proj->vertxt, q + 1, LEN_HUND);      <* 
          *> }                                                                        <*/
      }
      rc = poly_tags_readline (a_file, &x_line, &x_tag);
   }
   /*---(close)--------------------------*/
   rc = fclose (my.f_prog);
   my.f_prog = NULL;
   DEBUG_INPT   yLOG_point   ("fclose f"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
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
   tFUNC       *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "TAGS unit        : tags number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "TAGS count       : %3d", poly_btree_count (B_FUNCS));
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




