/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2019 robert.s.heatherly"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website, "   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works "   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE  \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original " \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS    \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any "      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might "    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/



/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
#define  P_OBJECTIVE   \
   "polymnia_gpl.c is focused solely on gathering and reporting informational¦"    \
   "header data from source files which provides primarily narritive, but critical,¦"  \
   "information on the scope, objective, and implementation of the file"

/*-----  ----------------  ·········1·········2·········3·········4·········5·········*/
#define  P_CRITICALTY     "´ (low)      useful, but not required to run"
#define  P_COMPLEXITY     "· (tiny)     primarily string data handling"



static tFILE   s_place;

const struct {
   uchar       g_abbr;
   char        g_name        [LEN_LABEL];
   char        g_label       [LEN_LABEL];
   char        g_desc        [LEN_DESC];
   char        g_where;                    /* h) headers-only, c) c-source-only, B) headers and source      */
   char        g_type;                     /* ° means critical, ´ means set elsewhere, · means non-critical */
   long        g_offset;
   short       g_min;                      /* absolute minimum size            */
   short       g_low;                      /* lowest size without warning      */
   short       g_high;                     /* high is also the reporting width */
   short       g_max;                      /* can not hold more that this      */
   short       g_store;                    /* size stored in data structure    */
} static s_gpl [LEN_LABEL] = {
   /*-------warranty--------label------------description-------------------------where--type---offset------------------------------------------------min--low--hig--max-store--------------*/
   { 'c' , "P_COPYRIGHT"   , "copyright"    , "identifying the owner"           , 'B' , 'g' , (long) &(s_place.i_copyright   [0]) - (long) &s_place,   1,  50,  70, 100, LEN_LABEL         },
   { 'l' , "P_LICENSE"     , "license"      , "code is gpl licensed"            , 'B' , 'g' , (long) &(s_place.i_license     [0]) - (long) &s_place,   1,  50, 200, 300, LEN_LABEL         },
   { 'c' , "P_COPYLEFT"    , "copyleft"     , "derivatives free and open"       , 'B' , 'g' , (long) &(s_place.i_copyleft    [0]) - (long) &s_place,   1,  50, 200, 300, LEN_LABEL         },
   { 'i' , "P_INCLUDE"     , "include"      , "derivatives must include text"   , 'B' , 'g' , (long) &(s_place.i_include     [0]) - (long) &s_place,   1,  50, 200, 300, LEN_LABEL         },
   { 'a' , "P_AS_IS"       , "as_is"        , "no one liable for any damages"   , 'B' , 'g' , (long) &(s_place.i_as_is       [0]) - (long) &s_place,   1,  50, 200, 300, LEN_LABEL         },
   { 't' , "P_THEFT"       , "theft"        , "thoughts on cheating"            , 'B' , 'g' , (long) &(s_place.i_theft       [0]) - (long) &s_place,   1,  50, 200, 300, LEN_LABEL         },
   {  1  , ""              , ""             , ""                                , '·' , '·' , -1                                                   ,   0,   0,   0,   0, 0                 },
   /*-------extra-----------label------------description-------------------------where--type---offset------------------------------------------------min--low--hig--max-store--------------*/
   { 'o' , "P_OBJECTIVE"   , "objective"    , "file-specific objective"         , 'c' , 'f' , (long) &(s_place.i_objective   [0]) - (long) &s_place,   1,  50, 200, 300, LEN_LABEL         },
   { 'c' , "P_CRITICALITY" , "criticality"  , "how important is this code"      , 'c' , 'f' , (long) &(s_place.i_criticality [0]) - (long) &s_place,   1,   1,  70, 100, LEN_LABEL         },
   { 'c' , "P_COMPLEXITY"  , "complexity"   , "how hard to maintain"            , 'c' , 'f' , (long) &(s_place.i_complexity  [0]) - (long) &s_place,   1,   1,  70, 100, LEN_LABEL         },
   {  1  , ""              , ""             , ""                                , '·' , '·' , -1                                                   ,   0,   0,   0,   0, 0                 },
   /*-------grade-----------label------------description-------------------------where--type---offset------------------------------------------------min--low--hig--max-store--------------*/
   { ' ' , ""              , "GRADE"        , "final rating on file header"     , '·' , '°' , -1                                                   ,   0,   0,   0,   0, 0                 },
   /*-------end-------------label------------description-------------------------where--type---offset------------------------------------------------min--low--hig--max-store--------------*/
   {  0  , "end-of-list"   , ""             , ""                                , '·' , '·' , -1                                                   ,   0,   0,   0,   0, 0                 },
};



/*====================------------------------------------====================*/
/*===----                        support functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

short
GPL_count               (void)
{
   char        rce         =  -10;
   int         i           =    0;
   int         c           =    0;
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   for (i = 0; i < LEN_LABEL; ++i) {
      if (s_gpl [i].g_abbr == 0)               break;
      DEBUG_INPT   yLOG_complex ("line"      , "%2d (%4d) %s", i, s_gpl [i].g_abbr, s_gpl [i].g_label);
      if (s_gpl [i].g_abbr == 1)               continue;
      if (strcmp (s_gpl [i].g_name, "") == 0)  continue;
      ++c;
   }
   DEBUG_INPT   yLOG_value   ("c"         , c);
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return c;
}

char
GPL_wipe                (tFILE *a_file)
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_file == NULL)  return rce;
   for (i = 0; i < LEN_LABEL; ++i) {
      if (s_gpl [i].g_abbr == 0)               break;
      if (s_gpl [i].g_abbr == 1) {
         a_file->i_header [i] = 'á';
         continue;
      }
      a_file->i_header [i] = '·';
      if (strcmp (s_gpl [i].g_name, "") == 0) {
         if (strcmp (s_gpl [i].g_label, "GRADE") == 0)  a_file->i_header [i] = ' ';
         continue;
      }
      if (s_gpl [i].g_offset < 0)              continue;
      strcpy ((long) a_file + s_gpl [i].g_offset, "");
   }
   a_file->i_header [i] = '\0';
   return 0;
}

char
GPL_rando            (tFILE *a_file)
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_file == NULL)  return rce;
   for (i = 0; i < LEN_LABEL; ++i) {
      if (s_gpl [i].g_abbr == 0)               break;
      if (s_gpl [i].g_abbr == 1) {
         a_file->i_header [i] = 'á';
         continue;
      }
      a_file->i_header [i] = '·';
      if (strcmp (s_gpl [i].g_name, "") == 0) {
         if (strcmp (s_gpl [i].g_label, "GRADE") == 0)  a_file->i_header [i] = '°';
         continue;
      }
      a_file->i_header [i] = s_gpl [i].g_abbr;
      if (s_gpl [i].g_offset < 0)              continue;
      ystrlcpy ((long) a_file + s_gpl [i].g_offset, s_gpl [i].g_label, s_gpl [i].g_store);
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       searching options                      ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

short
GPL_find                (char a_label [LEN_LABEL], uchar *r_abbr, char *r_where, char *r_type, long *r_offset, short *r_min, short *r_low, short *r_high, short *r_max, short *r_store)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(default)------------------------*/
   if (r_abbr   != NULL)  *r_abbr   = '-';
   if (r_where  != NULL)  *r_where  = '-';
   if (r_type   != NULL)  *r_type   = '-';
   if (r_offset != NULL)  *r_offset = 0;
   if (r_min    != NULL)  *r_min    = 0;
   if (r_low    != NULL)  *r_low    = 0;
   if (r_high   != NULL)  *r_high   = 0;
   if (r_max    != NULL)  *r_max    = 0;
   if (r_store  != NULL)  *r_store  = 0;
   /*---(defense)------------------------*/
   --rce;  if (a_label     == NULL)   return rce;
   --rce;  if (a_label [0] == '\0')   return rce;
   --rce;  if (a_label [0] == ' ' )   return rce;
   /*---(find)---------------------------*/
   for (i = 0; i < LEN_LABEL; ++i) {
      /*---(skip and end)----------------*/
      if (s_gpl [i].g_abbr == 0)                    break;
      if (s_gpl [i].g_abbr == 1)                    continue;
      /*---(filter)----------------------*/
      if (strcmp (s_gpl [i].g_name, "") == 0)       continue;
      if (s_gpl [i].g_offset < 0)                   continue;
      if (strcmp (a_label, s_gpl [i].g_name) != 0)  continue;
      /*---(matched)---------------------*/
      if (r_abbr   != NULL)  *r_abbr   = s_gpl [i].g_abbr;
      if (r_where  != NULL)  *r_where  = s_gpl [i].g_where;
      if (r_type   != NULL)  *r_type   = s_gpl [i].g_type;
      if (r_offset != NULL)  *r_offset = s_gpl [i].g_offset;
      if (r_min    != NULL)  *r_min    = s_gpl [i].g_min;
      if (r_low    != NULL)  *r_low    = s_gpl [i].g_low;
      if (r_high   != NULL)  *r_high   = s_gpl [i].g_high;
      if (r_max    != NULL)  *r_max    = s_gpl [i].g_max;
      if (r_store  != NULL)  *r_store  = s_gpl [i].g_store;
      /*---(complete)--------------------*/
      return i;
      /*---(done)------------------------*/
   }
   /*---(trouble)------------------------*/
   return --rce;
}

char
GPL_grading             (tFILE *a_file)
{
   /*---(locals)-----------+-----------+-*/
   int         i           =    0;
   char        x_mark      =    0;
   char        x_abbr      =    0;
   int         c           =    0;
   int         x_pass      =    0;
   int         x_na        =    0;
   int         x_miss      =    0;
   int         x_warn      =    0;
   int         x_fail      =    0;
   char        t           [LEN_HUND]  = "";
   int         x_summ      =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(walk header)--------------------*/
   for (i = 0; i < LEN_LABEL; ++i) {
      /*---(base filter)-----------------*/
      if (s_gpl [i].g_abbr == 0)                break;
      DEBUG_INPT   yLOG_complex ("line"      , "%2d (%4d) %s", i, s_gpl [i].g_abbr, s_gpl [i].g_label);
      if (s_gpl [i].g_abbr == 1)                continue;
      if (s_gpl [i].g_abbr == (uchar) ' ')    { x_summ = i;  continue; }
      if (s_gpl [i].g_offset < 0)               continue;
      /*---(prepare)---------------------*/
      x_abbr = s_gpl [i].g_abbr;
      x_mark = a_file->i_header [i];
      if  (x_abbr == x_mark)   x_mark = '!';
      /*---(summarize)-------------------*/
      ++c;
      switch (x_mark) {
      case '!' :
         ++x_pass;
         break;
      case '-' :
         if (s_gpl [i].g_type == 'g')  { ++x_fail;  a_file->i_header [i] = '°'; }
         else                            ++x_na;
         break;
      case '·' :
         if (s_gpl [i].g_type == 'g')  { ++x_fail;  a_file->i_header [i] = '°'; }
         else                            ++x_miss;
         break;
      case '?' : case '<' : case '>' : case '#' :
         ++x_warn;
         break;
      case '°' :
         ++x_fail;
         break;
      }
      /*---(done)------------------------*/
   }
   /*---(final grade)--------------------*/
   DEBUG_INPT   yLOG_complex ("stats"     , "%2dP, %2dF, %2dw, %2dm, %2d·", x_pass, x_fail, x_warn, x_miss, x_na);
   DEBUG_INPT   yLOG_value   ("x_summ"    , x_summ);
   if      (x_fail > 0)  { strcpy (t, "FAIL");  a_file->i_header [x_summ] = '°'; }
   else if (x_warn > 0)  { strcpy (t, "WARN");  a_file->i_header [x_summ] = '¡'; }
   else if (x_miss > 0)  { strcpy (t, "MISS");  a_file->i_header [x_summ] = '¢'; }
   else                  { strcpy (t, "PASS");  a_file->i_header [x_summ] = ' '; }
   snprintf  (a_file->i_grade, LEN_HUND, "%s (header audit) %3dp, %3df, %3dw, %3d-, %3d·", t, x_pass, x_fail, x_warn, x_miss, x_na);
   DEBUG_INPT   yLOG_char    ("final"     , a_file->i_header [x_summ]);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
GPL_summarize           (tPROJ *a_proj, tFILE *a_file, char a_ftype)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         x_len       =    0;
   uchar       x_abbr      =  '·';
   char        x_mark      =  '·';
   char        x_type      =  '·';
   char        x_head      =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(quick-out)----------------------*/
   DEBUG_INPT   yLOG_info    ("j_name"    , a_proj->j_name);
   x_len = strlen (a_proj->j_name);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   if (strncmp (a_proj->j_name, a_file->i_name, x_len) != 0) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(quick-out)----------------------*/
   x_type = a_file->i_type;
   DEBUG_INPT   yLOG_char    ("x_type"    , x_type);
   if (x_type == 0 || strchr ("ch", x_type) == NULL) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(walk header)--------------------*/
   for (i = 0; i < LEN_LABEL; ++i) {
      /*---(base filter)-----------------*/
      if (s_gpl [i].g_abbr == 0)                break;
      DEBUG_INPT   yLOG_complex ("line"      , "%2d (%4d) %s", i, s_gpl [i].g_abbr, s_gpl [i].g_label);
      if (s_gpl [i].g_abbr == 1)                continue;
      if (s_gpl [i].g_offset < 0)               continue;
      /*---(prepare)---------------------*/
      x_abbr = s_gpl [i].g_abbr;
      x_mark = a_file->i_header [i];
      x_head = HEADER_find_simple (s_gpl [i].g_label);
      /*---(worst case)------------------*/
      if      (x_head == '°')  ;    /* already marked fail */
      else if (x_mark == '°')  a_proj->j_header [x_head] = '°';
      /*---(first update)----------------*/
      else if (x_head == '·')  a_proj->j_header [x_head] = x_mark;
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}




