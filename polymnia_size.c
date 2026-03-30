/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2019 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might¦"    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/



char
PROJS_footprint        (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_TITLE] = "";
   char        x_base      [LEN_LABEL] = "";
   char        x_cmd       [LEN_RECD]  = "";
   int         x_len       =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *r           = NULL;
   int         rci         =    0;
   tSTAT       st;
   int         x_text, x_data, x_bss;
   char        x_public    [LEN_TITLE] = "";
   char        x_private   [LEN_TITLE] = "";
   tFILE      *x_file      = NULL;
   tFILE      *x_header    = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_proj->j_name);
   /*---(prepare name)--------------------------*/
   ystrlcpy (x_base, a_proj->j_name, LEN_LABEL);
   ystrlcpy (x_name, a_proj->j_name, LEN_TITLE);
   if (x_name [0] == 'y' && strchr (YSTR_UPPER, x_name [1]) != NULL) {
      sprintf (x_name, "lib%s.so.%c.%c.%c", a_proj->j_name, a_proj->j_vernum [0], a_proj->j_vernum [2], a_proj->j_vernum [3]);
   }
   x_len = strlen (x_name);
   DEBUG_INPT   yLOG_info    ("x_name"    , x_name);
   /*---(save totals)--------------------*/
   x_text = a_proj->COUNT_TEXT;
   x_data = a_proj->COUNT_DATA;
   x_bss  = a_proj->COUNT_BSS;
   /*---(defaults)-----------------------*/
   a_proj->COUNT_TEXT = 0;
   a_proj->COUNT_DATA = 0;
   a_proj->COUNT_BSS  = 0;
   /*---(check for existance)------------*/
   rci = lstat (x_name, &st);
   DEBUG_FILE   yLOG_value   ("lstat"     , rci);
   --rce; if (rci < 0) {
      DEBUG_FILE   yLOG_note    ("file does not exist, can not read");
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(check for regular file)---------*/
   --rce;  if (!S_ISREG (st.st_mode)) {
      DEBUG_FILE   yLOG_note    ("not a regular file, rejected");
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(get data)------------------------------*/
   sprintf (x_cmd, "size %s > /tmp/polymnia_footprint.txt", x_name);
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("size"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pull data)-----------------------------*/
   f = fopen ("/tmp/polymnia_footprint.txt", "rt");
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get data line)-------------------------*/
   fgets  (x_recd, LEN_RECD, f);
   fgets  (x_recd, LEN_RECD, f);
   /*---(parse)---------------------------------*/
   p = strtok_r (x_recd, " ", &r);
   --rce;  if (p == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_proj->COUNT_TEXT = atoi (p);
   p = strtok_r (NULL  , " ", &r);
   --rce;  if (p == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_proj->COUNT_DATA = atoi (p);
   p = strtok_r (NULL  , " ", &r);
   --rce;  if (p == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_proj->COUNT_BSS  = atoi (p);
   /*---(close)---------------------------------*/
   rc = fclose (f);
   DEBUG_INPT   yLOG_point   ("close"     , rc);
   /*---(destroy temp file)---------------------*/
   sprintf (x_cmd, "rm -f /tmp/polymnia_footprint.txt  2> /dev/null");
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("size"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(place extra)---------------------------*/
   sprintf (x_public , "%s.h"     , x_base);
   sprintf (x_private, "%s_priv.h", x_base);
   x_file = a_proj->j_ihead;
   while (x_file != NULL) {
      if (strcmp (x_file->i_name, x_private) == 0) {
         x_header = x_file;
         break;
      }
      if (strcmp (x_file->i_name, x_public ) == 0) {
         if (x_header == NULL)   x_header = x_file;
      }
      x_file = x_file->i_next;
   }
   DEBUG_INPT   yLOG_point   ("x_header"  , x_header);
   --rce;  if (x_header == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_header->COUNT_TEXT = a_proj->COUNT_TEXT - x_text;
   x_header->COUNT_DATA = a_proj->COUNT_DATA - x_data;
   x_header->COUNT_BSS  = a_proj->COUNT_BSS  - x_bss;
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}


char
FILES_footprint        (tFILE *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_TITLE] = "";
   char        x_cmd       [LEN_RECD]  = "";
   int         x_len       =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *r           = NULL;
   int         rci         =    0;
   tSTAT       st;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_file->i_name);
   DEBUG_INPT   yLOG_char    ("type"      , a_file->i_type);
   --rce;  if (a_file->i_type != 'c') {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare name)--------------------------*/
   ystrlcpy (x_name, a_file->i_name, LEN_TITLE);
   x_len = strlen (x_name);
   x_name [--x_len] = 'o';
   x_name [++x_len] = 's';
   x_name [++x_len] = '\0';
   DEBUG_INPT   yLOG_info    ("x_name"    , x_name);
   /*---(defaults)-----------------------*/
   a_file->COUNT_TEXT = 0;
   a_file->COUNT_DATA = 0;
   a_file->COUNT_BSS  = 0;
   /*---(check for existance)------------*/
   rci = lstat (x_name, &st);
   DEBUG_FILE   yLOG_value   ("lstat"     , rci);
   --rce; if (rci < 0) {
      DEBUG_FILE   yLOG_note    ("file does not exist, can not read");
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(check for regular file)---------*/
   --rce;  if (!S_ISREG (st.st_mode)) {
      DEBUG_FILE   yLOG_note    ("not a regular file, rejected");
      DEBUG_FILE   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(get data)------------------------------*/
   sprintf (x_cmd, "size %s > /tmp/polymnia_footprint.txt", x_name);
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("size"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pull data)-----------------------------*/
   f = fopen ("/tmp/polymnia_footprint.txt", "rt");
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get data line)-------------------------*/
   fgets  (x_recd, LEN_RECD, f);
   fgets  (x_recd, LEN_RECD, f);
   /*---(parse)---------------------------------*/
   p = strtok_r (x_recd, " ", &r);
   --rce;  if (p == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_file->i_proj->COUNT_TEXT += a_file->COUNT_TEXT = atoi (p);
   p = strtok_r (NULL  , " ", &r);
   --rce;  if (p == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_file->i_proj->COUNT_DATA += a_file->COUNT_DATA = atoi (p);
   p = strtok_r (NULL  , " ", &r);
   --rce;  if (p == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_file->i_proj->COUNT_BSS  += a_file->COUNT_BSS  = atoi (p);
   /*---(close)---------------------------------*/
   rc = fclose (f);
   DEBUG_INPT   yLOG_point   ("close"     , rc);
   /*---(destroy temp file)---------------------*/
   sprintf (x_cmd, "rm -f /tmp/polymnia_footprint.txt  2> /dev/null");
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("size"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}
