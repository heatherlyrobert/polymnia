/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*====================------------------------------------====================*/
/*===----                       inventory tags                         ----===*/
/*====================------------------------------------====================*/
static void  o___INVENTORY_______o () { return; }

char
poly_tags__handler      (tFILE *a_file, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
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
      ++(a_file->tail->WORK_LVARS );
      sprintf (t, " %s ", x_name);
      strlcat (a_file->tail->WORK_LOCALS, t, LEN_RECD);
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
   char        x_name      [LEN_TITLE];
   int         x_line      =    0;
   char        x_type      =  '-';
   int         x_len       =    0;             /* length of input record         */
   char        t           [LEN_TITLE];
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare)------------------------*/
   rc = poly_shared_open ('t', a_file->name);
   DEBUG_INPT   yLOG_value   ("create"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk tags)----------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = poly_shared_read ('t', NULL, x_recd, NULL);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0)  {
         DEBUG_INPT   yLOG_note    ("reading of line failed or eof");
         break;
      }
      /*---(parse)-----------------------*/
      rc = poly_shared_parse_tags (x_recd, x_name, &x_type, &x_line, NULL);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0)  {
         DEBUG_INPT   yLOG_note    ("reading of line failed or eof");
         break;
      }
      /*---(handle locals)------------------*/
      if (x_type == 'l') {
         DEBUG_INPT   yLOG_note    ("found a file/static variable");
         if (a_file->tail == NULL) {
            DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         DEBUG_INPT   yLOG_info    ("local for" , a_file->tail->name);
         ++(a_file->tail->WORK_LVARS );
         sprintf (t, " %s ", x_name);
         strlcat (a_file->tail->WORK_LOCALS, t, LEN_RECD);
      }
      /*---(handle prototype)---------------*/
      else if (x_type == 'p') {
         DEBUG_INPT   yLOG_note    ("found a prototype");
         rc = poly_proto_push (a_file, x_line, x_name);
      }
      /*---(name)------------------------*/
      else if (x_type == 'f') {
         DEBUG_INPT   yLOG_note    ("found a function header");
         if (strncmp ("o___", x_name, 4) == 0)   x_type = '_';
         DEBUG_INPT   yLOG_char    ("type"      , x_type);
         rc = poly_func_add (a_file, x_name, x_type, x_line, NULL);
         ++c;
      }
      /*---(done)------------------------*/
   }
   /*---(wrapup)-------------------------*/
   rc = poly_shared_close ('t');
   DEBUG_INPT   yLOG_value   ("cleanup"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(summary)------------------------*/
   DEBUG_INPT   yLOG_value   ("c"         , c);
   DEBUG_INPT   yLOG_value   ("count"     , poly_func_count ());
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return c;
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
      snprintf (unit_answer, LEN_RECD, "TAGS count       : %3d", poly_func_count ());
      return unit_answer;
   }
   if (strncmp (unit_answer, "TAGS unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "TAGS unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "entry"     )     == 0) {
      poly_func_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         if (u->work != NULL)  snprintf (unit_answer, LEN_RECD, "TAGS entry  (%2d) : %-22.22s %3d  %c  work   %3d  %3d", i, t, u->line, u->type, u->WORK_BEG, u->WORK_END);
         else                  snprintf (unit_answer, LEN_RECD, "TAGS entry  (%2d) : %-22.22s %3d  %c  non      -    -", i, t, u->line, u->type);
      } else                   snprintf (unit_answer, LEN_RECD, "TAGS entry  (%2d) : %-22.22s   -  -  -        -    -", i, t);
   }
   else if (strcmp (a_question, "stats"     )     == 0) {
      poly_func_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         snprintf (unit_answer, LEN_RECD, "TAGS stats  (%2d) : %-22.22s     �   �   %3d %3d %3d %3d %3d %3d", i, t, u->COUNT_LINES, u->COUNT_EMPTY, u->COUNT_DOCS, u->COUNT_DEBUG, u->COUNT_CODE, u->COUNT_SLOCL);
      }  else
         snprintf (unit_answer, LEN_RECD, "TAGS stats  (%2d) : %-22.22s     �   �     -   -   -   -   -   -", i, t, 0, 0, 0, 0, 0, 0);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




