/*============================----beg-of-source---============================*/
#include  "htags.h"


char
htags_tags_wipe    (int n)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(master)-------------------------*/
   strlcpy (s_tags [n].name  , "", LEN_RECD);
   s_tags [n].file     = -1;
   strlcpy (s_tags [n].type  , "", LEN_RECD);
   s_tags [n].line     = -1;
   strlcpy (s_tags [n].source, "", LEN_RECD);
   strlcpy (s_tags [n].hint  , "", LEN_LABEL);
   /*---(positioning)--------------------*/
   s_tags [n].oneline  = '-';
   s_tags [n].beg      = -1;
   s_tags [n].end      = -1;
   /*---(line counts)--------------------*/
   s_tags [n].lines    = 0;
   s_tags [n].empty    = 0;
   s_tags [n].docs     = 0;
   s_tags [n].debug    = 0;
   s_tags [n].code     = 0;
   s_tags [n].slocl    = 0;
   /*---(group one outputs)--------------*/
   s_tags [n].scope    = '-';
   s_tags [n].rtype    = '-';
   s_tags [n].psize    = '-';
   s_tags [n].tsize    = '-';
   s_tags [n].dsize    = '-';
   s_tags [n].ssize    = '-';
   s_tags [n].lsize    = '-';
   s_tags [n].csize    = '-';
   s_tags [n].rsize    = '-';
   s_tags [n].isize    = '-';
   s_tags [n].msize    = '-';
   /*---(group one working)--------------*/
   strlcpy (s_tags [n].rname , "", LEN_RECD);
   strlcpy (s_tags [n].params, "", LEN_RECD);
   s_tags [n].nparam   = -3;
   s_tags [n].lvars    = 0;
   s_tags [n].choices  = 0;
   s_tags [n].returns  = 0;
   s_tags [n].indent   = 0;
   s_tags [n].memories = 0;
   /*---(group two outputs)-----------*/
   s_tags [n].Lsize    = '-';
   s_tags [n].Gsize    = '-';
   s_tags [n].Esize    = '-';
   s_tags [n].Dsize    = '-';
   s_tags [n].Fsize    = '-';
   s_tags [n].Csize    = '-';
   s_tags [n].Ysize    = '-';
   s_tags [n].Xsize    = '-';
   s_tags [n].Rsize    = '-';
   s_tags [n].Wsize    = '-';
   s_tags [n].Vsize    = '-';
   /*---(group two working)-----------*/
   s_tags [n].lcalls   = 0;
   s_tags [n].gcalls   = 0;
   s_tags [n].ecalls   = 0;
   s_tags [n].depth    = 0;
   s_tags [n].funcs    = 0;
   s_tags [n].cstd     = 0;
   s_tags [n].ylibs    = 0;
   s_tags [n].xfuncs   = 0;
   s_tags [n].reads    = 0;
   s_tags [n].writes   = 0;
   s_tags [n].opengl   = 0;
   s_tags [n].ncurses  = 0;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
htags_tags_init    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;          /* generic return code            */
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   for (i = 0; i < MAX_TAG; ++i) {
      htags_tags_wipe (i);
   }
   s_ntag = 0;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
htags_tags_hint    (int n, char *a_label)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   char       *x_1st       = "abcdefghijklmnopqrstuvwxyz";
   int         x_1len      = strlen (x_1st);
   char       *x_2nd       = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int         x_2len      = strlen (x_2nd);
   --rce;  if (a_label == NULL)  return rce;
   strlcpy (a_label, "··", LEN_LABEL);
   --rce;  if (n < 0)            return rce;
   --rce;  if (n > 1351)         return rce;
   a_label [0] = x_1st [n / x_2len];
   a_label [1] = x_2nd [n % x_2len];
   a_label [2] = '\0';
   return 0;
}

char
htags_tags_add     (int a_file, char *a_name, char *a_type, int a_line, char *a_source)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   DEBUG_INPT   yLOG_sint    (s_ntag);
   /*---(file)---------------------------*/
   DEBUG_INPT   yLOG_sint    (a_file);
   --rce;  if (a_file <  0) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   --rce;  if (a_file >= s_nfile) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   s_tags [s_ntag].file = a_file;
   /*---(name)---------------------------*/
   DEBUG_INPT   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      htags_tags_wipe (s_ntag);
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   strlcpy (s_tags [s_ntag].name  , a_name  , LEN_RECD);
   /*---(type)---------------------------*/
   DEBUG_INPT   yLOG_spoint  (a_type);
   --rce;  if (a_type == NULL) {
      htags_tags_wipe (s_ntag);
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   strlcpy (s_tags [s_ntag].type  , a_type  , LEN_RECD);
   /*---(line)---------------------------*/
   DEBUG_INPT   yLOG_sint    (a_line);
   --rce;  if (a_line <= 0) {
      htags_tags_wipe (s_ntag);
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   s_tags [s_ntag].line  = a_line;
   /*---(source)-------------------------*/
   DEBUG_INPT   yLOG_spoint  (a_source);
   --rce;  if (a_source == NULL) {
      htags_tags_wipe (s_ntag);
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   strlcpy (s_tags [s_ntag].source, a_source, LEN_RECD);
   /*---(update count)-------------------*/
   /*> printf ("%3d -- %-25.25s %4d -- %-25.25s %-25.25s -- %s\n", s_ntag,            <* 
    *>       s_files [s_tags [s_ntag].file].name, s_tags [s_ntag].line,               <* 
    *>       s_tags [s_ntag].name,                                                    <* 
    *>       s_tags [s_ntag].type, s_tags [s_ntag].source);                           <*/
   ++s_ntag;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*--> read and parse crontab lines ----------[ ------ [ ------ ]-*/
htags_tags_inventory    (int n)
{  /*---(locals)-----------+-----------+-*/
   int         rc          =   0;           /* generic return code            */
   char        rce         = -10;           /* return code for errors         */
   char        x_cmd       [LEN_RECD];      /* ctags command                  */
   char        x_recd      [LEN_RECD];      /* input record                   */
   int         x_len       = 0;             /* length of input record         */
   char       *p           = NULL;
   char       *q           = " ";
   int         c           =   0;
   char        x_name      [LEN_RECD];
   int         x_line      =   0;
   char        x_type      [LEN_RECD];
   char        x_source    [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_value   ("index"     , n);
   DEBUG_INPT   yLOG_info    ("name"      , s_files [n].name);
   /*---(prepare)------------------------*/
   sprintf (x_cmd, "cflow -r -d 2 %s 2> /dev/null > htags.lcalls", s_files [n].name);
   DEBUG_INPT   yLOG_info    ("system"    , x_cmd);
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   sprintf (x_cmd, "ctags  --language-force=c -x --sort=no --file-scope=yes %s > htags.tmp", s_files [n].name);
   DEBUG_INPT   yLOG_info    ("system"    , x_cmd);
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("system"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(open)---------------------------*/
   DEBUG_INPT   yLOG_info    ("tag file"  , "htags.tmp");
   f = fopen ("htags.tmp", "r");
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_note    ("openned successfully");
   /*---(walk tags)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets  (x_recd, LEN_RECD, f);
      if (feof (f)) {
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
      strlcpy (x_name, p, LEN_RECD);
      DEBUG_INPT   yLOG_info    ("name"      , x_name);
      /*---(type)------------------------*/
      p = strtok (NULL  , q);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("can not find type field, SKIP");
         continue;
      }
      strlcpy (x_type, p, LEN_RECD);
      if (strcmp ("function", p) != 0) {
         DEBUG_INPT   yLOG_note    ("not a function, SKIP");
         continue;
      }
      DEBUG_INPT   yLOG_info    ("name"      , x_type);
      /*---(line)------------------------*/
      p = strtok (NULL  , q);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("can not find line field, SKIP");
         continue;
      }
      x_line = atoi (p);
      DEBUG_INPT   yLOG_value   ("line"      , x_line);
      /*---(source)----------------------*/
      p = strtok (NULL  , q);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("can not find source field, SKIP");
         continue;
      }
      p = strtok (NULL  , "\n");
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("can not find source field, SKIP");
         continue;
      }
      strlcpy (x_source, p, LEN_RECD);
      strltrim (x_source, ySTR_SINGLE, LEN_RECD);
      DEBUG_INPT   yLOG_info    ("source"    , x_source);
      /*---(done)------------------------*/
      htags_tags_add (n, x_name, x_type, x_line, x_source);
      ++c;
   }
   rc = fclose (f);
   f = NULL;
   DEBUG_INPT   yLOG_point   ("fclose"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_value   ("c"         , c);
   DEBUG_INPT   yLOG_value   ("s_ntag"    , s_ntag);
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
htags_tags_find    (int a_file, int *l, int *n)
{
   /*---(locals)-----------+-----------+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   int         x_len       =    0;          /* length of input record         */
   int         p           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(update line)-----------------*/
   ++(*l);
   DEBUG_INPT   yLOG_value   ("line"      , *l);
   /*---(update tag)------------------*/
   DEBUG_INPT   yLOG_value   ("tag"       , *n);
   --rce;  if (*n < 0) {
      rc = htags_nexttag (a_file, n);
      DEBUG_INPT   yLOG_snote   ("nexttag");
      if (rc < 0) {
         DEBUG_INPT   yLOG_snote   ("no more tags to find");
         DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   if (*n < s_ntag && *l > s_tags [*n].line)  rc = htags_nexttag (a_file, n);
   DEBUG_INPT   yLOG_value   ("tag"       , *n);
   DEBUG_INPT   yLOG_value   ("line"      , s_tags [*n].line);
   DEBUG_INPT   yLOG_info    ("name"      , s_tags [*n].name);
   /*---(found)-----------------------*/
   if (*l == s_tags [*n].line) {
      DEBUG_INPT   yLOG_note    ("FOUND");
      htags_scope    (*n, *l);
   }
   /*---(oneliner)--------------------*/
   if (s_tags [*n].oneline == 'y') {
      htags_linetype (a_file, *n);
      rc = fclose (c);
      c = NULL;
      DEBUG_DATA   yLOG_point   ("fclose c"  , rc);
      --rce;  if (rc < 0) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return  rce;
      }
      htags_tagend   (*n);
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(classify)--------------------*/
   p = *n - 1;
   htags_linetype (a_file, p);
   if (p < 0) {
      DEBUG_INPT   yLOG_note    ("before first tag");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(beginning)-------------------*/
   else if (s_tags [p].beg <  0) {
      if (s_curr [0] == '{')  {
         DEBUG_INPT   yLOG_note    ("beg brace");
         s_tags [p].beg = *l;
      }
   }
   /*---(ending)----------------------*/
   else if (s_tags [p].end <  0) {
      if (s_curr [0] == '}') {
         DEBUG_INPT   yLOG_note    ("end brace");
         s_tags [p].end = *l;
         --s_tags [p].lines;
         --s_tags [p].code;
         rc = fclose (c);
         c = NULL;
         DEBUG_INPT   yLOG_note    ("close");
         --rce;  if (rc < 0) {
            DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
            return  rce;
         }
         DEBUG_INPT   yLOG_note    ("function end");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         htags_tagend   (p);
         return 0;
      }
   }
   /*---(found)-----------------------*/
   if (*l == s_tags [*n].line) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_note    ("not found");
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
htags_tags_review       (int a_file)
{
   /*---(locals)-----------+-----------+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   char        x_recd      [LEN_RECD];      /* input record                   */
   int         x_len       =    0;          /* length of input record         */
   int         x_line      =    0;
   int         n           =   -1;
   int         p           =   -1;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open file)----------------------*/
   DEBUG_INPT   yLOG_value   ("file"      , a_file);
   DEBUG_INPT   yLOG_info    ("name"      , s_files [a_file].name);
   f = fopen (s_files [a_file].name, "r");
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   while (rc >= 0) {
      /*---(read)------------------------*/
      strlcpy (s_pprev, s_prev, LEN_RECD);
      strlcpy (s_prev , s_curr, LEN_RECD);
      fgets  (s_curr, LEN_RECD, f);
      --rce;  if (feof (f))  {
         DEBUG_INPT   yLOG_note    ("end of file");
         break;
      }
      x_len = strlen (s_curr);
      s_curr [--x_len] = '\0';
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      rc = htags_tags_find (a_file, &x_line, &n);
      if (rc > 0 && n >= 0) {
         /*> htags_scope    (n);                                                      <*/
         p = n - 1;
         if (p >= 0) {
            /*> htags_tagend   (p);                                                   <*/
            /*> printf ("   tag (%3d) %-25.25s %c [%c%c%c.%c%c%c.%c%c%c%c%c] [%c%c.%c%c.%c%c%c%c.%c%c]\n",   <* 
             *>       p, s_tags [p].name, s_tags [p].oneline,                                                <* 
             *>       s_tags [p].scope, s_tags [p].rtype, s_tags [p].psize,                                  <* 
             *>       s_tags [p].tsize, s_tags [p].dsize, s_tags [p].ssize,                                  <* 
             *>       s_tags [p].lsize, s_tags [p].csize,                                                    <* 
             *>       s_tags [p].rsize, s_tags [p].isize, s_tags [p].msize,                                  <* 
             *>       s_tags [p].Fsize,                                                                      <* 
             *>       s_tags [p].Lsize, s_tags [p].Gsize,                                                    <* 
             *>       s_tags [p].Rsize, s_tags [p].Wsize,                                                    <* 
             *>       s_tags [p].Osize, s_tags [p].Vsize,                                                    <* 
             *>       '-'             , '-',                                                                 <* 
             *>       '-'             , '-');                                                                <*/
         }
      }
   }
   /*---(close)--------------------------*/
   rc = fclose (f);
   f = NULL;
   DEBUG_INPT   yLOG_point   ("fclose f"  , rc);
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
htags_tags__unit     (char *a_question, int n)
{
   /*---(locals)-----------+-----------+-*/
   int         len         = 0;
   char        t           [LEN_RECD];
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "TAGS unit        : tags number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "TAGS count       : %3d", s_ntag);
      return unit_answer;
   }
   if (strncmp (unit_answer, "TAGS unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   /*> if (n <  0)       return unit_answer;                                          <*/
   /*> if (n >= s_ntag)  return unit_answer;                                          <*/
   snprintf (unit_answer, LEN_RECD, "TAGS unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "entry"     )     == 0) {
      sprintf  (t, "[%.20s]", s_tags [n].name);
      snprintf (unit_answer, LEN_RECD, "TAGS entry  (%2d) : %-22.22s %3d %3d %3d %3d %3d %3d %3d", n, t, s_tags [n].line, s_tags [n].lines, s_tags [n].empty, s_tags [n].docs, s_tags [n].debug, s_tags [n].code, s_tags [n].slocl);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}





