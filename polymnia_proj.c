/*============================----beg-of-source---============================*/
#include  "polymnia.h"



tPROJ      *g_head      = NULL;
tPROJ      *g_tail      = NULL;
int         g_count     =    0;;
static char s_print     [LEN_RECD] = "";


/*====================------------------------------------====================*/
/*===----                        simple support                        ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_proj_cli           (char *a_name, char a_loud)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         l           =    0;
   char       *x_valid     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   ystrlcpy (my.g_projname, ""    , LEN_LABEL);
   /*---(defense)------------------------*/
   DEBUG_ARGS  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "project <name>, name can not be null");
      DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ARGS  yLOG_info    ("a_name"    , a_name);
   /*---(check length)-------------------*/
   l = strlen (a_name);
   DEBUG_ARGS  yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "project <name>, name can not be blank/empty");
      DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (l >= LEN_LABEL) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "project <name>, name can not be longer than %d chars", LEN_LABEL);
      DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check characters)---------------*/
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (x_valid, a_name [i]) != NULL)  continue;
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "project <name>, name can not have a <%c> at character %d", a_name [i], i);
      DEBUG_PROG  yLOG_char  ("bad char"  , a_name [i]);
      DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy)---------------------------*/
   ystrlcpy (my.g_projname, a_name, LEN_LABEL);
   DEBUG_ARGS  yLOG_info    ("project"  , my.n_db);
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_proj__wipe    (tPROJ *a_dst)
{
   if (a_dst == NULL)  return -1;
   /*---(overall)-----------*/
   a_dst->j_name      [0] = '\0';
   a_dst->j_dir       [0] = '\0';
   a_dst->j_written       =    0;
   /*---(header entries)----*/
   poly_header_clear (a_dst);
   /*---(manuals)-----------*/
   ystrlcpy (a_dst->j_manual, "········", LEN_LABEL);
   a_dst->j_git       = '·';
   /*---(stats)-------------*/
   a_dst->j_funcs     = 0;
   poly_cats_counts_clear (a_dst->counts);
   /*---(files)-------------*/
   a_dst->j_ihead     = NULL;
   a_dst->j_itail     = NULL;
   a_dst->j_icount    = 0;
   /*---(btree)-------------*/
   a_dst->j_btree     = NULL;
   /*---(tags)--------------*/
   return 1;
}

char*
poly_proj__memory       (tPROJ *a_proj)
{
   /*---(overall)------------------------*/
   ystrlcpy (s_print, "å"  , LEN_RECD);
   poly_shared__check_str  (s_print, a_proj->j_name);
   poly_shared__check_str  (s_print, a_proj->j_header);
   poly_shared__spacer     (s_print);
   /*---(master)-------------------------*/
   poly_shared__check_str  (s_print, a_proj->j_focus);
   poly_shared__check_str  (s_print, a_proj->j_niche);
   poly_shared__check_str  (s_print, a_proj->j_subject);
   poly_shared__check_str  (s_print, a_proj->j_purpose);
   poly_shared__spacer     (s_print);
   /*---(greek)--------------------------*/
   poly_shared__check_str  (s_print, a_proj->j_namesake);
   poly_shared__check_str  (s_print, a_proj->j_pronounce);
   poly_shared__check_str  (s_print, a_proj->j_heritage);
   poly_shared__check_str  (s_print, a_proj->j_briefly);
   poly_shared__check_str  (s_print, a_proj->j_imagery);
   poly_shared__check_str  (s_print, a_proj->j_reason);
   poly_shared__spacer     (s_print);
   /*---(onelinne)-----------------------*/
   poly_shared__check_str  (s_print, a_proj->j_oneline);
   poly_shared__spacer     (s_print);
   /*---(location)-----------------------*/
   poly_shared__check_str  (s_print, a_proj->j_homedir);
   poly_shared__check_str  (s_print, a_proj->j_progname);
   poly_shared__check_str  (s_print, a_proj->j_fullpath);
   poly_shared__check_str  (s_print, a_proj->j_suffix);
   poly_shared__check_str  (s_print, a_proj->j_content);
   poly_shared__spacer     (s_print);
   /*---(system)-------------------------*/
   poly_shared__check_str  (s_print, a_proj->j_systems);
   poly_shared__check_str  (s_print, a_proj->j_language);
   poly_shared__check_str  (s_print, a_proj->j_compiler);
   poly_shared__check_str  (s_print, a_proj->j_codesize);
   poly_shared__spacer     (s_print);
   /*---(depends)------------------------*/
   poly_shared__check_str  (s_print, a_proj->j_dep_cstd);
   poly_shared__check_str  (s_print, a_proj->j_dep_posix);
   poly_shared__check_str  (s_print, a_proj->j_dep_core);
   poly_shared__check_str  (s_print, a_proj->j_dep_vikey);
   poly_shared__check_str  (s_print, a_proj->j_dep_other);
   poly_shared__check_str  (s_print, a_proj->j_dep_graph);
   poly_shared__check_str  (s_print, a_proj->j_dep_solo);
   poly_shared__spacer     (s_print);
   /*---(author)-------------------------*/
   poly_shared__check_str  (s_print, a_proj->j_author);
   poly_shared__check_str  (s_print, a_proj->j_created);
   poly_shared__spacer     (s_print);
   /*---(versioning)---------------------*/
   poly_shared__check_str  (s_print, a_proj->j_vermajor);
   poly_shared__check_str  (s_print, a_proj->j_verminor);
   poly_shared__check_str  (s_print, a_proj->j_vernum);
   poly_shared__check_str  (s_print, a_proj->j_vertxt);
   poly_shared__spacer     (s_print);
   /*---(stats)--------------------------*/
   poly_shared__check_num  (s_print, a_proj->j_funcs);
   poly_shared__spacer     (s_print);
   /*---(files)--------------------------*/
   poly_shared__check_ptr  (s_print, a_proj->j_ihead);
   poly_shared__check_ptr  (s_print, a_proj->j_itail);
   poly_shared__check_num  (s_print, a_proj->j_icount);
   poly_shared__spacer     (s_print);
   /*---(btree)--------------------------*/
   poly_shared__check_ptr  (s_print, a_proj->j_btree);
   ystrlcat (s_print, "æ"  , LEN_RECD);
   /*---(complete)-----------------------*/
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_proj_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = ySORT_btree (B_PROJ, "projects");
   DEBUG_PROG   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_proj_purge         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   tPROJ      *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(walk-through)-------------------*/
   DEBUG_DATA   yLOG_value   ("count"     , ySORT_count (B_PROJ));
   rc = ySORT_by_cursor (B_PROJ, YDLST_HEAD, &x_proj);
   DEBUG_PROG   yLOG_point   ("x_proj"     , x_proj);
   while (x_proj != NULL) {
      rc = ySORT_by_cursor (B_PROJ, YDLST_NEXT, &x_next);
      DEBUG_PROG   yLOG_point   ("x_next"    , x_next);
      DEBUG_DATA   yLOG_point   ("x_proj"    , x_proj);
      DEBUG_DATA   yLOG_info    ("->j_name"  , x_proj->j_name);
      rc = poly_proj_remove (&x_proj);
      x_proj = x_next;
   }
   /*---(check)--------------------------*/
   DEBUG_DATA   yLOG_value   ("count"     , ySORT_count (B_PROJ));
   --rce;  if (ySORT_count (B_PROJ) > 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_proj_wrap          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(walk through list)--------------*/
   /*> rc = ySORT_purge (B_PROJ);                                                <* 
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
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char poly_proj__new  (tPROJ **a_new) { return poly_shared_new  ("proj", sizeof (tPROJ), a_new, NULL, '-', poly_proj__wipe); }
char poly_proj_force (tPROJ **a_new) { return poly_shared_new  ("proj", sizeof (tPROJ), a_new, NULL, 'y', poly_proj__wipe); }
char poly_proj__free (tPROJ **a_old) { return poly_shared_free ("proj", a_old, NULL); }



/*====================------------------------------------====================*/
/*===----                     hooking and unhooking                    ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

char
poly_proj__hook         (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("->j_name"    , a_proj->j_name);
   --rce;  if (strlen (a_proj->j_name) <= 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(into btree)---------------------*/
   rc = ySORT_hook (B_PROJ, a_proj, a_proj->j_name, &a_proj->j_btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update count)-------------------*/
   ++(my.COUNT_PROJS);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_proj__unhook       (tPROJ *a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook from btree)--------------*/
   rc = ySORT_unhook (&a_proj->j_btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update count)-------------------*/
   --(my.COUNT_PROJS);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_proj__adder         (char *a_name, char *a_home, tPROJ **a_proj, char a_force)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   DEBUG_DATA   yLOG_point   ("a_home"    , a_home);
   --rce;  if (a_home == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_home"    , a_home);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   DEBUG_DATA   yLOG_point   ("*a_proj"   , *a_proj);
   --rce;  if (a_proj != NULL) {
      if (*a_proj != NULL) {
         DEBUG_DATA   yLOG_note    ("already set to a particular project");
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check for existing)-------------*/
   poly_proj_by_name (a_name, &x_new);
   DEBUG_DATA   yLOG_point   ("check"     , x_new);
   --rce;  if (x_new != NULL) {
      if (a_force != 'y') {
         DEBUG_DATA   yLOG_note    ("project already exists");
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      yURG_msg ('-', "project exists, clear all current data");
      rc = poly_proj_remove (&x_new);
      DEBUG_DATA   yLOG_value   ("remove"    , rc);
      DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
      if (x_new != NULL) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else {
      yURG_msg ('-', "project does not already exist, creating");
   }
   /*---(create project)-----------------*/
   if (a_force == 'y')   poly_proj_force (&x_new);
   else                  poly_proj__new  (&x_new);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   ystrlcpy (x_new->j_name    , a_name, LEN_TITLE);
   ystrlcpy (x_new->j_dir     , a_home, LEN_HUND);
   /*---(into btree)---------------------*/
   rc = poly_proj__hook (x_new);
   DEBUG_DATA   yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   if (a_proj != NULL)  *a_proj = x_new;
   /*---(update)-------------------------*/
   rc = ySORT_prepare (B_PROJ);
   if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_proj_add            (char *a_name, char *a_home, tPROJ **a_proj)
{
   return poly_proj__adder (a_name, a_home, a_proj, '-');
}

char
poly_proj_replace        (char *a_name, char *a_home, tPROJ **a_proj)
{
   return poly_proj__adder (a_name, a_home, a_proj, 'y');
}

char
poly_proj_remove        (tPROJ **a_proj)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPROJ      *x_proj      = NULL;
   /*---(beginning)----------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*a_proj"   , *a_proj);
   --rce;  if (*a_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("->j_name"    , (*a_proj)->j_name);
   /*---(purge assigned files)-----------*/
   rc = poly_file_purge  (*a_proj, '-');
   DEBUG_DATA   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   rc = poly_proj__unhook (*a_proj);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free)---------------------------*/
   rc = poly_proj__free   (a_proj);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update)-------------------------*/
   rc = ySORT_prepare (B_PROJ);
   if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      specialty                               ----===*/
/*====================------------------------------------====================*/
static void  o___SPECIAL_________o () { return; }

char
poly_proj__get_home     (char *a_home)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_home      [LEN_HUND]  = "";
   char       *p           = NULL;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (a_home);
   --rce;  if (a_home == NULL) {
      yURG_err ('f', "home pointer was null");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   ystrlcpy (a_home, ""    , LEN_HUND);
   /*---(get the home)-------------------*/
   p = getcwd (x_home, LEN_HUND);
   DEBUG_DATA   yLOG_spoint  (p);
   --rce;  if (p == NULL) {
      yURG_err ('f', "linux can not provide current working directory");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (x_home);
   x_len = strlen (x_home);
   DEBUG_DATA   yLOG_sint    (x_len);
   /*> yURG_msg ('-', "current working directory %2då%sæ", x_len, x_home);            <*/
   /*---(check valid areas)--------------*/
   --rce; if (x_len > 16 && strncmp ("/home/system/"         , x_home, 13) == 0) {
      /*> yURG_msg ('-', "sub-directory of å/home/system/æ is allowed");              <*/
      DEBUG_DATA   yLOG_snote   ("system");
      ;;
   } else if (x_len > 16 && strncmp ("/home/monkey/"         , x_home, 13) == 0) {
      /*> yURG_msg ('-', "sub-directory of å/home/monkey/æ is allowed");              <*/
      DEBUG_DATA   yLOG_snote   ("monkey");
      ;;
   } else if (x_len > 25 && strncmp ("/home/member/p_gvskav/", x_home, 22) == 0) {
      /*> yURG_msg ('-', "sub-directory of å/home/member/p_gvskav/æ is allowed");     <*/
      DEBUG_DATA   yLOG_snote   ("member");
      ;;
   } else if (x_len > 20 && strncmp ("/tmp/polymnia_test/"   , x_home, 19) == 0) {
      /*> yURG_msg ('-', "sub-directory of å/tmp/polymnia_test/æ is allowed");        <*/
      DEBUG_DATA   yLOG_snote   ("unittest");
      ;;
   } else if (x_len >  8 && strncmp ("/tmp/"                 , x_home,  5) == 0) {
      /*> yURG_msg ('-', "sub-directory of å/tmp/æ is allowed");                      <*/
      DEBUG_DATA   yLOG_snote   ("unittest");
      ;;
   } else {
      yURG_err ('f', "not one of polymnia's allowed directory prefixes");
      DEBUG_DATA   yLOG_snote   ("not allowed");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   ystrlcpy (a_home, x_home, LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_proj__get_name     (cchar *a_home, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_home      [LEN_HUND]  = "";
   char       *p           = NULL;
   char       *q           = NULL;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      yURG_err ('f', "name pointer was null");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (a_name, ""    , LEN_TITLE);
   DEBUG_DATA   yLOG_spoint  (a_home);
   --rce;  if (a_home == NULL) {
      yURG_err ('f', "home directory string was null");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_home);
   DEBUG_DATA   yLOG_sint    (x_len);
   --rce;  if (x_len <= 0) {
      yURG_err ('f', "home directory string empty");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   /*> yURG_msg ('-', "current project path %2då%sæ", strlen (a_home), a_home);       <*/
   ystrlcpy (x_home, a_home, LEN_HUND);
   if (x_home [x_len - 1] == '/') x_home [--x_len] = '\0';
   DEBUG_DATA   yLOG_snote   (x_home);
   /*---(get the name)-------------------*/
   p = strrchr (x_home, '/');
   DEBUG_DATA   yLOG_spoint  (p);
   --rce;  if (p == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_home + x_len == p) {
      DEBUG_DATA   yLOG_snote   ("at end");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ++p;
   q = strchr  (p, '.');
   DEBUG_DATA   yLOG_spoint  (q);
   if (q == NULL)  x_len = LEN_TITLE;
   else            x_len = q - p + 1;
   if (x_len > LEN_TITLE)  x_len = LEN_TITLE;
   DEBUG_DATA   yLOG_sint    (x_len);
   /*---(save back)----------------------*/
   ystrlcpy (a_name, p, x_len);
   /*> yURG_msg ('-', "current project name %2då%sæ", strlen (a_name), a_name);       <*/
   DEBUG_DATA   yLOG_snote   (a_name);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_proj_identify       (char *a_name, char *a_home)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_home      [LEN_HUND]  = "";
   char        x_name      [LEN_TITLE] = "";
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_name != NULL)    ystrlcpy (a_name, "", LEN_TITLE);
   if (a_home != NULL)    ystrlcpy (a_home, "", LEN_TITLE);
   /*---(get directory)------------------*/
   rc = poly_proj__get_home (x_home);
   DEBUG_DATA   yLOG_value   ("get_home"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get name)-----------------------*/
   rc = poly_proj__get_name (x_home, x_name);
   DEBUG_DATA   yLOG_value   ("get_name"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> yURG_msg ('-', "current project name %2då%sæ", strlen (x_name), x_name);       <*/
   /*---(save results)-------------------*/
   ystrlcpy (a_name, x_name, LEN_TITLE);
   ystrlcpy (a_home, x_home, LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_proj_here           (tPROJ **a_proj)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_home      [LEN_HUND]  = "";
   char        x_name      [LEN_TITLE] = "";
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   IF_VERIFY   yURG_msg ('>', "verify current directory");
   /*---(get directory)------------------*/
   yURG_msg ('-', "gathering information about current location");
   rc = poly_proj_identify  (x_name, x_home);
   DEBUG_DATA   yLOG_value   ("idenfity"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(add normally)-------------------*/
   rc = poly_proj_replace (x_name, x_home, a_proj);
   DEBUG_DATA   yLOG_value   ("add"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        searching                             ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  poly_proj_count         (void)                          { return ySORT_count     (B_PROJ); }
char poly_proj_by_name       (uchar *a_name, tPROJ **r_proj) { return ySORT_by_name   (B_PROJ, a_name, r_proj); }
char poly_proj_by_index      (int n, tPROJ **r_proj)         { return ySORT_by_index  (B_PROJ, n, r_proj); }
char poly_proj_by_cursor     (char a_dir, tPROJ **r_proj)    { return ySORT_by_cursor (B_PROJ, a_dir, r_proj); }



/*====================------------------------------------====================*/
/*===----                         system update                        ----===*/
/*====================------------------------------------====================*/
static void  o___SYSTEM__________o () { return; }

/*> char         /+--> update all projects in a directory ------------------------+/            <* 
 *> poly_proj_system        (char *a_path)                                                      <* 
 *> {                                                                                           <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                 <* 
 *>    int         rc          =    0;          /+ generic return code            +/            <* 
 *>    char        rce         =  -10;          /+ return code for errors         +/            <* 
 *>    DIR        *x_dir       = NULL;          /+ directory pointer              +/            <* 
 *>    tDIRENT    *x_file      = NULL;          /+ directory entry pointer        +/            <* 
 *>    char        x_base      [LEN_HUND];      /+ file name                      +/            <* 
 *>    char        x_name      [LEN_HUND];      /+ file name                      +/            <* 
 *>    int         x_len       =    0;                                                          <* 
 *>    char        x_type      =  '-';                                                          <* 
 *>    int         x_read      =    0;          /+ count of entries reviewed      +/            <* 
 *>    int         x_good      =    0;          /+ count of entries processed     +/            <* 
 *>    /+---(header)-------------------------+/                                                 <* 
 *>    DEBUG_INPT   yLOG_enter   (__FUNCTION__);                                                <* 
 *>    /+---(open dir)-----------------------+/                                                 <* 
 *>    DEBUG_INPT   yLOG_point   ("a_path"     , a_path);                                       <* 
 *>    --rce;  if (a_path == NULL) {                                                            <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
 *>       return  rce;                                                                          <* 
 *>    }                                                                                        <* 
 *>    DEBUG_INPT   yLOG_info    ("a_path"     , a_path);                                       <* 
 *>    ystrlcpy  (x_base, a_path, LEN_HUND);                                                     <* 
 *>    x_dir = opendir (a_path);                                                                <* 
 *>    DEBUG_INPT   yLOG_point   ("x_dir"      , x_dir);                                        <* 
 *>    --rce;  if (x_dir == NULL) {                                                             <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
 *>       return  rce;                                                                          <* 
 *>    }                                                                                        <* 
 *>    DEBUG_INPT   yLOG_note    ("openned successfully");                                      <* 
 *>    /+---(process entries)----------------+/                                                 <* 
 *>    DEBUG_INPT   yLOG_note    ("processing entries");                                        <* 
 *>    while (1) {                                                                              <* 
 *>       PROG_prepare ();                                                                      <* 
 *>       /+---(read a directory entry)------+/                                                 <* 
 *>       x_file = readdir (x_dir);                                                             <* 
 *>       DEBUG_INPT   yLOG_point   ("x_file"    , x_file);                                     <* 
 *>       if (x_file == NULL)  break;                                                           <* 
 *>       /+---(filter by name)--------------+/                                                 <* 
 *>       ystrlcpy (x_name, x_file->d_name, LEN_TITLE);                                          <* 
 *>       DEBUG_INPT   yLOG_info    ("x_name"    , x_name);                                     <* 
 *>       x_len = strlen (x_name);                                                              <* 
 *>       DEBUG_INPT   yLOG_value   ("x_len"     , x_len);                                      <* 
 *>       if (x_name [0] == '.')  {                                                             <* 
 *>          DEBUG_INPT   yLOG_note    ("hidden, SKIP");                                        <* 
 *>          continue;                                                                          <* 
 *>       }                                                                                     <* 
 *>       /+---(cut too short)---------------+/                                                 <* 
 *>       if (x_len <  3)  {                                                                    <* 
 *>          DEBUG_INPT   yLOG_note    ("name too short, SKIP");                                <* 
 *>          continue;                                                                          <* 
 *>       }                                                                                     <* 
 *>       /+---(move)------------------------+/                                                 <* 
 *>       sprintf (x_name, "%s/%s/", x_base, x_file->d_name);                                   <* 
 *>       printf  ("%s\n", x_name);                                                             <* 
 *>       DEBUG_INPT   yLOG_info    ("x_name"    , x_name);                                     <* 
 *>       rc = chdir (x_name);                                                                  <* 
 *>       DEBUG_INPT   yLOG_value   ("chdir"     , rc);                                         <* 
 *>       if (rc < 0) {                                                                         <* 
 *>          DEBUG_INPT   yLOG_note    ("not a directory/no access, SKIP");                     <* 
 *>          continue;                                                                          <* 
 *>       }                                                                                     <* 
 *>       /+---(update)----------------------+/                                                 <* 
 *>       rc = poly_action_update ();                                                           <* 
 *>       DEBUG_INPT   yLOG_value   ("update"    , rc);                                         <* 
 *>       if (rc < 0) {                                                                         <* 
 *>          DEBUG_INPT   yLOG_note    ("could not update project");                            <* 
 *>       }                                                                                     <* 
 *>       /+---(clean up)--------------------+/                                                 <* 
 *>       /+> rc = ySORT_purge_all ();                                               <*         <* 
 *>        *> DEBUG_INPT   yLOG_value   ("purge"     , rc);                               <*    <* 
 *>        *> if (rc < 0) {                                                               <*    <* 
 *>        *>    DEBUG_INPT   yLOG_note    ("could not purge btree");                     <*    <* 
 *>        *> }                                                                           <+/   <* 
 *>       /+---(done)------------------------+/                                                 <* 
 *>    }                                                                                        <* 
 *>    /+---(close dir)----------------------+/                                                 <* 
 *>    DEBUG_INPT   yLOG_note    ("closing directory");                                         <* 
 *>    rc = closedir (x_dir);                                                                   <* 
 *>    DEBUG_INPT   yLOG_value   ("close_rc"  , rc);                                            <* 
 *>    /+---(complete)------------------------------+/                                          <* 
 *>    DEBUG_INPT   yLOG_exit    (__FUNCTION__);                                                <* 
 *>    return 0;                                                                                <* 
 *> }                                                                                           <*/



/*====================------------------------------------====================*/
/*===----                       reporting support                      ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTING_______o () { return; }


char
poly_proj_line          (tPROJ *a_proj, char a_style, char a_use, char a_pre, int a, char a_print)
{
   /*  n  name     , just the name
    *  s  stats    , short count, name, plus statistics
    *  L  long     , short count plus everything
    *  a  all      , long count plus statistics
    *  A  all      , long count plus everything
    *  m  master   , name plus master data
    *  g  greek    , name plus greek data
    *  l  location , name plus location data
    *  c  chars    , name plus characteristic data
    *  w  who      , name plus author data
    *  v  version  , name plus versioning data
    *  f  footprint, memory footprint
    *
    */
   char        t           [LEN_RECD]  = "";
   char        x_projs     [LEN_TERSE] = "·";
   char        x_files     [LEN_TERSE] = "·";
   char        x_funcs     [LEN_TERSE] = "·";
   char        x_ylibs     [LEN_TERSE] = "·";
   char        x_lines     [LEN_TERSE] = "·";
   char        x_empty     [LEN_TERSE] = "·";
   char        x_docs      [LEN_TERSE] = "·";
   char        x_debug     [LEN_TERSE] = "·";
   char        x_code      [LEN_TERSE] = "·";
   char        x_slocl     [LEN_TERSE] = "·";
   char        x_text      [LEN_TERSE] = "·";
   char        x_data      [LEN_TERSE] = "·";
   char        x_bss       [LEN_TERSE] = "·";
   char        x_type      =  '-';
   int         x, y, x_age;
   char        x_unit      =  's';
   char        x_aged      [LEN_SHORT] = "";
   /*---(prepare)------------------------*/
   ystrlcpy (s_print, "", LEN_RECD);
   x_type = a_use;
   if (a_proj == NULL) {
      if (a_use == '-')  x_type = 'h';
      if (a_use == 'd')  x_type = 'h';
   }
   /*---(indent)-------------------------*/
   switch (a_pre) {
   case '>' :   if (strchr ("pt", x_type) != NULL)  sprintf (t, "··"); else sprintf (t, "  "); break;
   case '#' :   sprintf (t, "# ");                             break;
   default  :   ystrlcpy (t, "", LEN_RECD);                    break;
   }
   ystrlcat (s_print, t, LEN_RECD);
   /*---(index)--------------------------*/
   if (strchr ("aAT", a_style) != NULL) {
      switch (x_type) {
      case 'h' :   sprintf (t, "prj fil fnc  ");               break;
      case 'p' :   sprintf (t, "Ï--·Ï--·Ï--··");               break;
      case 't' :   sprintf (t, "prj·fil·fnc··");               break;
      case 'd' :   sprintf (t, "%-3d ·   ·    ", a + 1);       break;
      default  :   ystrlcpy (t, "", LEN_RECD);                 break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   if (strchr ("sLp", a_style) != NULL) {
      switch (x_type) {
      case 'h' :   sprintf (t, "prj  ");                       break;
      case 'p' :   sprintf (t, "Ï--··");                       break;
      case 't' :   sprintf (t, "prj··");                       break;
      case 'd' :   sprintf (t, "%-3d  ", a + 1);               break;
      default  :   ystrlcpy (t, "", LEN_RECD);                 break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(name)---------------------------*/
   switch (x_type) {
   case 'h' :   sprintf (t, "---name-----  ");                 break;
   case 'p' :   sprintf (t, "Ï-----------··");                 break;
   case 't' :   sprintf (t, "name··········");                 break;
   case 'd' :   sprintf (t, "%-12.12s  ", a_proj->j_name);     break;
   default  :   ystrlcpy (t, "", LEN_RECD);                    break;
   }
   ystrlcat (s_print, t, LEN_RECD);
   /*---(spacer for tree reporting)------*/
   if (strchr ("T", a_style) != NULL) {
      switch (x_type) {
      case 'h' :   ystrlcat (s_print, "········  ", LEN_RECD);      break;
      default  :   ystrlcat (s_print, "          ", LEN_RECD);      break;
      }
   }
   /*---(statistics)---------------------*/
   if (strchr ("sLaApPT", a_style) != NULL) {
      if (a_proj != NULL) {
         if (a_proj->COUNT_FILES > 0)  ystrl4main (a_proj->COUNT_FILES, x_files, 0, 'c', '-', LEN_TERSE);
         if (a_proj->COUNT_FUNCS > 0)  ystrl4main (a_proj->COUNT_FUNCS, x_funcs, 0, 'c', '-', LEN_TERSE);
         if (a_proj->COUNT_YLIBS > 0)  ystrl4main (a_proj->COUNT_YLIBS, x_ylibs, 0, 'c', '-', LEN_TERSE);
         if (a_proj->COUNT_LINES > 0)  ystrl4main (a_proj->COUNT_LINES, x_lines, 0, 'c', '-', LEN_TERSE);
         if (a_proj->COUNT_EMPTY > 0)  ystrl4main (a_proj->COUNT_EMPTY, x_empty, 0, 'c', '-', LEN_TERSE);
         if (a_proj->COUNT_DOCS  > 0)  ystrl4main (a_proj->COUNT_DOCS , x_docs , 0, 'c', '-', LEN_TERSE);
         if (a_proj->COUNT_DEBUG > 0)  ystrl4main (a_proj->COUNT_DEBUG, x_debug, 0, 'c', '-', LEN_TERSE);
         if (a_proj->COUNT_CODE  > 0)  ystrl4main (a_proj->COUNT_CODE , x_code , 0, 'c', '-', LEN_TERSE);
         if (a_proj->COUNT_SLOCL > 0)  ystrl4main (a_proj->COUNT_SLOCL, x_slocl, 0, 'c', '-', LEN_TERSE);
      }
      switch (x_type) {
      case 'h' :
         sprintf (t, "-files -funcs -ylibs ---lines ---empty ----docs ---debug ----code ---slocl  ");
         break;
      case 'p' :
         sprintf (t, "Ï-----·Ï-----·Ï-----·Ï-------·Ï-------·Ï-------·Ï-------·Ï-------·Ï-------··");
         break;
      case 't' :
         sprintf (t, "files··funcs··ylibs··lines····empty····docs·····debug····code·····slocl·····");
         break;
      case 'd' :
         sprintf (t, "%6.6s %6.6s %6.6s %8.8s %8.8s %8.8s %8.8s %8.8s %8.8s  ",
               x_files, x_funcs, x_ylibs,
               x_lines, x_empty, x_docs , x_debug, x_code , x_slocl);
         break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(header flags)-------------------*/
   if (strchr ("sLaA" , a_style) != NULL) {
      switch (x_type) {
      case 'h' : sprintf (t, "---header-checklist-------------------------  ");    break;
      case 'p' : sprintf (t, "Ï-------------------------------------------··");    break;
      case 't' : sprintf (t, "header-checklist······························");    break;
      case 'd' : sprintf (t, "%-44.44s  ", a_proj->j_header);               break;
      default  :   ystrlcpy (t, "", LEN_RECD);                             break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(master)-------------------------*/
   if (strchr ("LAm", a_style) != NULL) {
      switch (x_type) {
      case 'h' : sprintf (t, "---focus---------------------- ---niche---------------------- ---subject-------------------- ---purpose------------------------------------------------------------  ");  break;
      case 'p' : sprintf (t, "Ï-----------------------------·Ï-----------------------------·Ï-----------------------------·Ï---------------------------------------------------------------------··");  break;
      case 't' : sprintf (t, "focus··························niche··························subject························purpose·································································");  break;
      case 'd' : sprintf (t, "%-30.30s %-30.30s %-30.30s %-70.70s  ",
                       a_proj->j_focus   , a_proj->j_niche   ,
                       a_proj->j_subject , a_proj->j_purpose );
                 break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(greek)--------------------------*/
   if (strchr ("LAg", a_style) != NULL) {
      switch (x_type) {
      case 'h' : sprintf (t, "---namesake----------------------------- ---heritage----------------------------------------------------------- ---imagery------------------------------------------------------------ ---reason-chosen------------------------------------------------------ ---oneline------------------------------------------------------------  ");  break;
      case 'p' : sprintf (t, "Ï---------------------------------------·Ï---------------------------------------------------------------------·Ï---------------------------------------------------------------------·Ï---------------------------------------------------------------------·Ï---------------------------------------------------------------------··");  break;
      case 't' : sprintf (t, "namesake·································heritage·······························································imagery································································reason-chosen··························································oneline·································································");  break;
      case 'd' : sprintf (t, "%-40.40s %-70.70s %-70.70s %-70.70s %-70.70s  ",
                       a_proj->j_namesake, a_proj->j_heritage, a_proj->j_imagery ,
                       a_proj->j_reason  , a_proj->j_oneline );
                 break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   if (strchr ("Op" , a_style) != NULL) {
      switch (x_type) {
      case 'h' : sprintf (t, "---oneline------------------------------------------------------------  ");  break;
      case 'p' : sprintf (t, "Ï---------------------------------------------------------------------··");  break;
      case 't' : sprintf (t, "oneline·································································");  break;
      case 'd' : sprintf (t, "%-70.70s  ", a_proj->j_oneline);   break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(location)-----------------------*/
   if (strchr ("LAl", a_style) != NULL) {
      switch (x_type) {
      case 'h' : sprintf (t, "---homedir------------------------------------------------------------ ---basename--------- ---fullpath----------------------------------------------------------- suffix ---content--------------------  ");  break;
      case 'p' : sprintf (t, "Ï---------------------------------------------------------------------·Ï-------------------·Ï---------------------------------------------------------------------·Ï-----·Ï-----------------------------··");  break;
      case 't' : sprintf (t, "homedir································································basename·············fullpath·······························································suffix·content·························");  break;
      case 'd' : sprintf (t, "%-70.70s %-20.20s %-70.70s %-6.6s %-30.30s  ",
                       a_proj->j_homedir , a_proj->j_progname,
                       a_proj->j_fullpath, a_proj->j_suffix  , a_proj->j_content );
                 break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(chars)--------------------------*/
   if (strchr ("LAc", a_style) != NULL) {
      switch (x_type) {
      case 'h' : sprintf (t, "---system------------------------------------------------------------- ---language----------------------------------------------------------- ---compiler----------------------------------------------------------- ---codesize-----------------------------  ");  break;
      case 'p' : sprintf (t, "Ï---------------------------------------------------------------------·Ï---------------------------------------------------------------------·Ï---------------------------------------------------------------------·Ï---------------------------------------··");  break;
      case 't' : sprintf (t, "system·································································language·······························································compiler·······························································codesize··································");  break;
      case 'd' : sprintf (t, "%-70.70s %-70.70s %-70.70s %-40.40s  ",
                       a_proj->j_systems , a_proj->j_language,
                       a_proj->j_compiler, a_proj->j_codesize);
                 break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(author)-------------------------*/
   if (strchr ("LAw", a_style) != NULL) {
      switch (x_type) {
      case 'h' : sprintf (t, "---author------------------------------- ---created----------  ");   break;
      case 'p' : sprintf (t, "Ï---------------------------------------·Ï-------------------··");   break;
      case 't' : sprintf (t, "author···································created···············");   break;
      case 'd' : sprintf (t, "%-40.40s %-20.20s  ",
                       a_proj->j_author  , a_proj->j_created );
                 break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(version)------------------------*/
   if (strchr ("LAv", a_style) != NULL) {
      switch (x_type) {
      case 'h' : sprintf (t, "---vermajor----------------------------------------------------------- ---verminor----------------------------------------------------------- --vernum-- ---vertxt-------------------------------------------------------------  ");  break;
      case 'p' : sprintf (t, "Ï---------------------------------------------------------------------·Ï---------------------------------------------------------------------·Ï---------·Ï---------------------------------------------------------------------··");  break;
      case 't' : sprintf (t, "vermajor·······························································verminor·······························································vernum·····vertxt··································································");  break;
      case 'd' : sprintf (t, "%-70.70s %-70.70s %-10.10s %-70.70s  ",
                       a_proj->j_vermajor, a_proj->j_verminor,
                       a_proj->j_vernum  , a_proj->j_vertxt  );
                 break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   if (strchr ("p"  , a_style) != NULL) {
      x_age = 0;
      if (a_proj != NULL)  x_age = my.runtime - a_proj->j_written;
      ystrlage (x_age, 'U', x_aged);
      switch (x_type) {
      case 'h' : sprintf (t, "age  vers  g  ---codesize---  ");  break;
      case 'p' : sprintf (t, "Ï--··Ï---··Ï··Ï-------------··");  break;
      case 't' : sprintf (t, "age··vers··g··codesize········");  break;
                 /*> case 'd' : sprintf (t, "%2ld%c %-6.6s %-14.14s  ", c, x_unit, a_proj->j_vernum, a_proj->j_codesize);   <*/
      case 'd' : sprintf (t, "%-3.3s  %-4.4s  %c  %-14.14s  ",
                       x_aged, a_proj->j_vernum, a_proj->j_git, a_proj->j_codesize);
                 break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(manual)-------------------------*/
   if (strchr ("p"    , a_style) != NULL) {
      switch (x_type) {
      case 'h' : sprintf (t, "--mans--  ");  break;
      case 'p' : sprintf (t, "Ï-------··");  break;
      case 't' : sprintf (t, "mans······");  break;
      case 'd' : sprintf (t, "%8.8s  ", a_proj->j_manual);
                 break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(memory)-------------------------*/
   if (strchr ("pfT"  , a_style) != NULL) {
      if (a_proj != NULL) {
         if (a_proj->COUNT_TEXT  > 0)  ystrl4main (a_proj->COUNT_TEXT , x_text , 0, 'c', '-', LEN_TERSE);
         if (a_proj->COUNT_DATA  > 0)  ystrl4main (a_proj->COUNT_DATA , x_data , 0, 'c', '-', LEN_TERSE);
         if (a_proj->COUNT_BSS   > 0)  ystrl4main (a_proj->COUNT_BSS  , x_bss  , 0, 'c', '-', LEN_TERSE);
      }
      switch (x_type) {
      case 'h' : sprintf (t, "---text-- ---data-- ---bss---  ");  break;
      case 'p' : sprintf (t, "Ï--------·Ï--------·Ï--------··");  break;
      case 't' : sprintf (t, "text······data······bss········");  break;
      case 'd' : sprintf (t, "%9.9s %9.9s %9.9s  ", x_text, x_data, x_bss);
                 break;
      default  :   ystrlcpy (t, "", LEN_RECD);                  break;
      }
      ystrlcat (s_print, t, LEN_RECD);
   }
   /*---(newline)------------------------*/
   if (a_print == 'y') {
      if      (x_type == 'p')  printf ("#@ x-parse   å%sæ\n", s_print);
      else if (x_type == 't')  printf ("#@ titles    å%sæ\n", s_print);
      else if (x_type == 'h')  printf ("#%s\n", s_print + 1);
      else                     printf ("%s\n", s_print);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_proj_git          (tPROJ *a_proj)
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

char
poly_proj_footprint    (tPROJ *a_proj)
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



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_proj__unit     (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD]  = "[]";
   char        s           [LEN_RECD]  = "[]";
   char        r           [LEN_RECD]  = "[]";
   tPROJ      *u           = NULL;
   tFILE      *v           = NULL;
   int         x_fore      =    0;
   int         x_back      =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "PROJ unit        : index number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "PROJ count       : %3d", ySORT_count (B_PROJ));
      return unit_answer;
   }
   else if (strcmp (a_question, "print"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "PROJ print       : %4d[%-.400s]", strlen (s_print), s_print);;
      return unit_answer;
   }
   else if (strcmp (a_question, "name"      )     == 0) {
      snprintf (unit_answer, LEN_RECD, "PROJ name        : %2d[%s]", strlen (my.g_projname), my.g_projname);;
      return unit_answer;
   }
   if (strncmp (unit_answer, "PROJ unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "PROJ unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "stats"     )     == 0) {
      poly_proj_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->j_name);
         snprintf (unit_answer, LEN_RECD, "PROJ stats  (%2d) : %-22.22s   %3d %3d %3d   %3d %3d %3d %3d %3d %3d", i, t, u->COUNT_FILES, u->COUNT_FUNCS, u->COUNT_YLIBS, u->COUNT_LINES, u->COUNT_EMPTY, u->COUNT_DOCS, u->COUNT_DEBUG, u->COUNT_CODE, u->COUNT_SLOCL);
      } else {
         snprintf (unit_answer, LEN_RECD, "PROJ stats  (%2d) : %-22.22s     -   -   -     -   -   -   -   -   -", i, t);
      }
   }
   else if (strcmp (a_question, "files"     )     == 0) {
      poly_proj_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->j_name);
         if (u->j_ihead != NULL) {
            sprintf  (s, "[%.15s]", u->j_ihead->i_name);
            sprintf  (r, "[%.15s]", u->j_itail->i_name);
            v = u->j_ihead; while (v != NULL) { ++x_fore; v = v->i_next; }
            v = u->j_itail; while (v != NULL) { ++x_back; v = v->i_prev; }
         }
         snprintf (unit_answer, LEN_RECD, "PROJ files  (%2d) : %-22.22s   %3dc %3df %3db   %-17.17s %s", i, t, u->j_icount, x_fore, x_back, s, r);
      } else {
         snprintf (unit_answer, LEN_RECD, "PROJ files  (%2d) : []                         -c   -f   -b   []                []", i, t);
      }
   }
   else if (strcmp (a_question, "header"    )     == 0) {
      poly_proj_by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->j_name);
         snprintf (unit_answer, LEN_RECD, "PROJ head   (%2d) : %-22.22s   å%sæ", i, t, u->j_header);
      } else {
         snprintf (unit_answer, LEN_RECD, "PROJ head   (%2d) : %-22.22s   å%sæ", i, t, "· ····· ····· ····· ··· ··· ···· ·");
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


