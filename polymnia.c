/*============================----beg-of-source---============================*/
#include  "polymnia.h"


/*
 *
 *
 *
 *
 *
 *
 */





char
htags_scope        (int n, int l)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   char       *r           = NULL;
   char       *a           = NULL;
   char       *b           = NULL;
   int        x_len        =    0;
   char       x_params     [LEN_RECD];
   char       x_body       [LEN_RECD];
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_value   ("n"         , n);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   /*---(open code file)-----------------*/
   c = fopen ("htags.code"         , "w");
   DEBUG_DATA   yLOG_point   ("c"         , c);
   --rce;  if (c == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_DATA   yLOG_note    ("code file openned successfully");
   /*---(oneline)------------------------*/
   p = strstr (s_curr, s_tags [n].name);
   DEBUG_DATA   yLOG_point   ("p"         , p);
   x_len = p - s_curr;
   DEBUG_DATA   yLOG_value   ("x_len"     , x_len);
   if (x_len == 0)   s_tags [n].oneline = '-';
   else              s_tags [n].oneline = 'y';
   DEBUG_DATA   yLOG_char    ("oneline"   , s_tags [n].oneline);
   /*---(return type)--------------------*/
   if (s_tags [n].oneline == 'y') {
      strlcpy (s_tags [n].rname, s_curr, x_len);
      s_tags [n].end    = s_tags [n].beg = l;
      /*> fprintf (c, "%s\n", s_curr);                                                <*/
   } else {
      fprintf (c, "%s\n", s_pprev);
      fprintf (c, "%s\n", s_prev);
      /*> fprintf (c, "%s\n", s_curr);                                                <*/
      r = strstr (s_prev, "/*");
      if (r == NULL)  x_len = strlen (s_prev);
      else            x_len = r - s_prev;
      strlcpy (s_tags [n].rname, s_prev, x_len + 1);
   }
   strltrim (s_tags [n].rname, ySTR_SINGLE, LEN_RECD);
   if      (strstr (s_tags [n].rname, "char*" ) != NULL)  s_tags [n].rtype = 's';
   else if (strstr (s_tags [n].rname, "char"  ) != NULL)  s_tags [n].rtype = 'c';
   else if (strstr (s_tags [n].rname, "void"  ) != NULL)  s_tags [n].rtype = 'v';
   else if (strstr (s_tags [n].rname, "*"     ) != NULL)  s_tags [n].rtype = 'p';
   else                                                   s_tags [n].rtype = 'n';
   /*---(scope)--------------------------*/
   if      (strstr (s_tags [n].name, "__unit")  != NULL)  s_tags [n].scope = 'u';
   else if (strstr (s_tags [n].name, "__test")  != NULL)  s_tags [n].scope = 'u';
   else if (strstr (s_tags [n].rname, "static") != NULL)  s_tags [n].scope = 's';
   else if (strstr (s_tags [n].name, "__"    )  != NULL)  s_tags [n].scope = 'f';
   else                                                   s_tags [n].scope = 'g';
   /*---(parms)--------------------------*/
   a = strchr (p, '(');
   if (a != NULL) {
      b = strchr (p, '{');
      if (b == NULL)  x_len = LEN_RECD;
      else            x_len = b - a;
      strlcpy  (x_params         , a, x_len);
      strltrim (x_params         , ySTR_EVERY , x_len);
      strlcpy  (s_tags [n].params, a, x_len);
      strltrim (s_tags [n].params, ySTR_SINGLE, x_len);
      if      (strcmp (x_params, "()")     == 0)  s_tags [n].nparam = -1;
      else if (strcmp (x_params, "(void)") == 0)  s_tags [n].nparam =  0;
      else    s_tags [n].nparam = strldcnt (x_params, ',', x_len) + 1;
   } else {
      strlcpy  (s_tags [n].params, "-", x_len);
      s_tags [n].nparam = -2;
   }
   poly_cats_exact   ("nparam"  , s_tags [n].nparam  , &s_tags [n].psize, '0');
   /*---(one-liner)----------------------*/
   if (s_tags [n].oneline == 'y') {
      if (b != NULL) {
         p = strchr (b, '}');
         x_len = p - b;
         strlcpy  (x_body, b, x_len);
         strltrim (x_body, ySTR_EVERY , x_len);
         s_tags [n].lines  = s_tags [n].empty  = -1;
         s_tags [n].docs   = s_tags [n].debug  = -1;
         s_tags [n].code   = s_tags [n].slocl  = -1;
         if (strcmp (x_body, "{}")     == 0) {
            s_tags [n].lvars  = s_tags [n].choices = s_tags [n].returns  = -1;
            s_tags [n].memories = s_tags [n].indent = -1;
         }
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
htags_nexttag      (int a_file, int *a_last)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         x_start     =    0;
   /*---(search)-------------------------*/
   if (a_last < 0)  x_start = 0;
   else             x_start = *a_last + 1;
   for (i = x_start; i < s_ntag; ++i) {
      if (s_tags [i].file != a_file)  continue;
      *a_last = i;
      return 0;
   }
   *a_last = s_ntag;
   /*---(complete)-----------------------*/
   return -1;
}

char
htags_linetype     (int a_file, int a_tag)
{
   int         i           =    0;
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   /*> printf ("entering linetype (file = %d, tag = %d)\n", a_file, a_tag);           <*/
   strlcpy (x_recd, s_curr, LEN_RECD);
   strltrim (x_recd, ySTR_BOTH, LEN_RECD);
   /*> printf ("   [%s]\n", x_recd);                                                  <*/
   if      (strncmp (x_recd, "DEBUG_", 6) == 0)  poly_cats_lines (a_file, a_tag, 'D');
   else if (strncmp (x_recd, "yLOG_" , 5) == 0)  poly_cats_lines (a_file, a_tag, 'D');
   else if (strncmp (x_recd, "/*"    , 2) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strncmp (x_recd, "* "    , 2) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strncmp (x_recd, "*>"    , 2) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strcmp  (x_recd, "*"        ) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strcmp  (x_recd, "*/"       ) == 0)  poly_cats_lines (a_file, a_tag, 'd');
   else if (strlen  (x_recd)              == 0)  poly_cats_lines (a_file, a_tag, 'e');
   else {
      /*> printf ("   code part\n");                                                  <*/
      if (c != NULL)  fprintf (c, "%s\n", s_curr);
      poly_cats_lines (a_file, a_tag, 'c');
      /*> printf ("   [%s]\n", s_curr);                                               <*/
      if      (strstr (s_curr, " return "   ) != NULL) poly_cats_logic (a_tag, 'r');
      if      (strstr (s_curr, " return;"   ) != NULL) poly_cats_logic (a_tag, 'r');
      if      (strstr (s_curr, " if "       ) != NULL) poly_cats_logic (a_tag, 'c');
      else if (strstr (s_curr, " else "     ) != NULL) poly_cats_logic (a_tag, 'c');
      if      (strstr (s_curr, " switch "   ) != NULL) poly_cats_logic (a_tag, 'c');
      if      (strstr (s_curr, " while "    ) != NULL) poly_cats_logic (a_tag, 'c');
      if      (strstr (s_curr, " do "       ) != NULL) poly_cats_logic (a_tag, 'c');
   }
   /*> printf ("   indent part\n");                                                   <*/
   if (a_tag >= 0) {
      x_len = strlen (s_curr);
      for (i = 0; i < x_len; ++i) {
         if (s_curr [i] == ' ')   continue;
         if (i > s_tags [a_tag].indent) s_tags [a_tag].indent = i;
         break;
      }
   }
   /*> printf ("leaving linetype\n");                                                 <*/
   return 0;
}

char
htags_calls        (char *a_file, int n, int *a_dst)
{
   FILE       *r           = NULL;
   char        x_recd      [LEN_RECD];
   char        x_source    [LEN_RECD];
   char        x_found     =   '-';
   int         x_len       =     0;
   int         i           =     0;
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   r = fopen (a_file, "r");
   DEBUG_DATA   yLOG_point   ("r"         , r);
   if (r == NULL) {
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_DATA   yLOG_value   ("n"         , n);
   DEBUG_DATA   yLOG_info    ("name"      , s_tags [n].name);
   while (1) {
      fgets (x_recd, LEN_RECD, r);
      if (feof (r))  break;
      if (x_recd [0] == ' ') {
         if (x_found == 'y') {
            /*> printf ("%-25.25s %-25.25s %-50.50s\n", s_tags [n].name, x_source, x_recd);   <*/
            ++(*a_dst);
            DEBUG_DATA   yLOG_value   ("a_dst"     , *a_dst);
         }
         continue;
      }
      if (x_found == 'y') {
         DEBUG_DATA   yLOG_note    ("end of entries");
         break;
      }
      strlcpy (x_source, x_recd, LEN_RECD);
      x_len = strlen (x_source);
      for (i = 0; i < x_len; ++i) {
         if (x_source [i] != '(')  continue;
         x_source [i] = '\0';
         DEBUG_DATA   yLOG_info    ("entry"     , x_source);
         break;
      }
      /*> printf ("   next [%s] vs [%s]\n", x_source, s_tags [n].name);               <*/
      DEBUG_DATA   yLOG_complex ("compare"   , "%s to %s", x_source, s_tags [n].name);
      if (strcmp (s_tags [n].name, x_source) == 0) {
         DEBUG_DATA   yLOG_note    ("FOUND header");
         /*> printf ("   FOUND\n");                                                   <*/
         x_found = 'y';
      }
   }
   DEBUG_DATA   yLOG_note    ("closing");
   fclose (r);
   r = NULL;
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
htags_parse        (int n)
{
   FILE *r  = NULL;
   char        x_recd      [LEN_RECD];
   char        x_val       [LEN_LABEL];
   char        x_source    [LEN_RECD];
   char        x_found     =   '-';
   int         x_len       =     0;
   int         i           =     0;
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_value   ("index"     , n);
   system ("ctags --language-force=c -x --sort=no --c-kinds=l htags.code | wc -l >  htags.stats");
   system ("cflow -d 2 htags.code | wc -l >> htags.stats");
   r = fopen ("htags.stats", "r");
   DEBUG_DATA   yLOG_point   ("r"         , r);
   if (r != NULL) {
      DEBUG_DATA   yLOG_note    ("reading file");
      fgets (x_val, LEN_LABEL, r);
      x_val [strlen (x_val) - 1] = '\0';
      DEBUG_DATA   yLOG_info    ("lvars"     , x_val);
      s_tags [n].lvars  = atoi (x_val);
      fgets (x_val, LEN_LABEL, r);
      x_val [strlen (x_val) - 1] = '\0';
      DEBUG_DATA   yLOG_info    ("funcs"     , x_val);
      s_tags [n].funcs  = atoi (x_val) - 1;
      fclose (r);
      r = NULL;
   }
   htags_calls ("htags.lcalls", n, &(s_tags [n].lcalls));
   htags_calls ("htags.gcalls", n, &(s_tags [n].gcalls));
   s_tags [n].gcalls -= s_tags [n].lcalls;
   /*> if (n == 658)  exit (0);                                                       <*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



