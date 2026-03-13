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
PROJS_git              (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cmd       [LEN_RECD]  = "";
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char        x_ch        =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("name"      , a_proj->j_name);
   /*---(get data)------------------------------*/
   sprintf (x_cmd, "git status -s --untracked-files=no > /tmp/polymnia_git.txt");
   rc = system (x_cmd);
   DEBUG_INPT   yLOG_value   ("git"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pull data)-----------------------------*/
   f = fopen ("/tmp/polymnia_git.txt", "rt");
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get data line)-------------------------*/
   fgets  (x_recd, LEN_RECD, f);
   fclose (f);
   l = strlen (x_recd);
   /*---(check for current)---------------------*/
   DEBUG_INPT   yLOG_value   ("l"         , l);
   if (l == 0) {
      DEBUG_INPT   yLOG_note    ("git fully up to date");
      a_proj->j_git = '·';
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(clean up)------------------------------*/
   if (x_recd [l - 1] == '\n')  x_recd [--l] = '\0';
   DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
   /*---(check for no git)----------------------*/
   rc = strncmp (x_recd, "fatal: not a git repository", 27);
   DEBUG_INPT   yLOG_value   ("fatal"     , rc);
   if (rc == 0) {
      a_proj->j_git = ' ';
      DEBUG_SORT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(not up to date)------------------------*/
   a_proj->j_git = '¤';
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}
