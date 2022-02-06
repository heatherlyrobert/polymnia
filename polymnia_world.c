/*============================----beg-of-source---============================*/
#include   "polymnia.h"


/*
 *  register and deregister projects for tracking
 *
 */



static char s_print     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                       basic support                          ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
poly_world_cli          (char *a_name, char a_loud)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char       *x_valid     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_/.";
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_ARGS  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "world <name>, name can not be null");
      DEBUG_TOPS  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ARGS  yLOG_info    ("a_name"    , a_name);
   strlcpy (x_recd, a_name, LEN_RECD);
   /*---(check length)-------------------*/
   l = strlen (x_recd);
   DEBUG_ARGS  yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "world <name>, name can not be blank/empty");
      DEBUG_TOPS  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check characters)---------------*/
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (x_valid, x_recd [i]) != NULL)  continue;
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "world <name>, name can not have a <%c> at character %d", x_recd [i], i);
      DEBUG_TOPS  yLOG_char  ("bad char"  , x_recd [i]);
      DEBUG_TOPS  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check extension)----------------*/
   if (l  < 5 || strcmp (x_recd + l - 4, ".txt") != 0) {
      strlcat (x_recd, ".txt", LEN_RECD);
      DEBUG_ARGS  yLOG_info    ("fixed"     , x_recd);
   }
   /*---(copy)---------------------------*/
   strlcpy (my.n_world, x_recd, LEN_RECD);
   DEBUG_ARGS  yLOG_info    ("world"     , my.n_world);
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   clearing and checking                      ----===*/
/*====================------------------------------------====================*/
static void  o___CLEANSING_______o () { return; }

char
poly_world__wipe        (tWORLD *a_world)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(master)-------------------------*/
   a_world->name [0]    = '\0';
   a_world->home [0]    = '\0';
   a_world->btree       = NULL;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 1;
}

char*
poly_world__memory      (tWORLD *a_world)
{
   /*---(master)-------------------------*/
   strlcpy (s_print, "["  , LEN_RECD);
   poly_shared__check_str  (s_print, a_world->name);
   poly_shared__check_str  (s_print, a_world->home);
   poly_shared__check_ptr  (s_print, a_world->btree);
   strlcat (s_print, "]" , LEN_RECD);
   /*---(complete)-----------------------*/
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char poly_world__new  (tWORLD **a_new) { return poly_shared_new  ("world", sizeof (tWORLD), a_new, NULL, '-', poly_world__wipe); }
char poly_world__free (tWORLD **a_old) { return poly_shared_free ("world", a_old, NULL); }



/*====================------------------------------------====================*/
/*===----                       add and remove                         ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_world__add         (char *a_name, char *a_home)
{
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_new       = NULL;
   /*---(begin)--------------------------*/
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
   /*---(check for duplicate)------------*/
   rc = poly_world__by_name (a_name, &x_new);
   DEBUG_DATA   yLOG_point   ("by_name"   , x_new);
   --rce;  if (x_new != NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create function)----------------*/
   rc = poly_world__new (&x_new);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (rc < 0 || x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   strlcpy (x_new->name, a_name, LEN_LABEL);
   strlcpy (x_new->home, a_home, LEN_HUND);
   /*---(into btree)---------------------*/
   rc = poly_btree_hook (B_WORLD, x_new, x_new->name, &x_new->btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare functions)--------------*/
   DEBUG_PROG   yLOG_note    ("prepare btree");
   rc = poly_btree_prepare  (B_WORLD);
   DEBUG_PROG   yLOG_value   ("prepare"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_world__remove      (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_old       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   /*---(find)---------------------------*/
   rc = poly_world__by_name (a_name, &x_old);
   DEBUG_DATA   yLOG_value   ("by_name"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(btree)--------------------------*/
   rc = poly_btree_unhook (&(x_old->btree));
   DEBUG_DATA   yLOG_value   ("un-btree"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free main)----------------------*/
   rc = poly_world__free (&x_old);
   DEBUG_DATA   yLOG_value   ("free"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare functions)--------------*/
   DEBUG_PROG   yLOG_note    ("prepare btree");
   rc = poly_btree_prepare  (B_WORLD);
   DEBUG_PROG   yLOG_value   ("prepare"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           searching                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  poly_world__count        (void)                            { return poly_btree_count     (B_WORLD); }
char poly_world__by_name      (uchar *a_name, tWORLD **r_world) { return poly_btree_by_name   (B_WORLD, a_name, r_world); }
char poly_world__by_index     (int n, tWORLD **r_world)         { return poly_btree_by_index  (B_WORLD, n, r_world); }
char poly_world__by_cursor    (char a_dir, tWORLD **r_world)    { return poly_btree_by_cursor (B_WORLD, a_dir, r_world); }



/*====================------------------------------------====================*/
/*===----                        export and import                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXIM____________o () { return; }

char
poly_world__import      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*> char        x_curr      [LEN_RECD]  = "";                                      <*/
   char        x_home      [LEN_RECD]  = "";
   char        x_name      [LEN_LABEL] = "";
   /*> char       *p           = NULL;                                                <*/
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   yURG_msg ('-', "world registry is in file å%sæ", my.n_world);
   /*---(open)---------------------------*/
   rc = poly_shared_open ('w', NULL);
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(save present directory)---------*/
   /*> p = getcwd (x_curr, LEN_RECD);                                                 <* 
    *> DEBUG_INPT   yLOG_point   ("getcwd"    , p);                                   <* 
    *> --rce;  if (p == NULL) {                                                       <* 
    *>    DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(walk)---------------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = poly_shared_read ('w', NULL, x_home, NULL);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("end of file");
         break;
      }
      DEBUG_INPT   yLOG_info    ("x_home"    , x_home);
      /*---(parse)-----------------------*/
      /*> strltrim (x_home, ySTR_BOTH, LEN_RECD);                                     <*/
      /*> rc = chdir (x_home);                                                        <* 
       *> DEBUG_INPT   yLOG_value   ("chdir"     , rc);                               <* 
       *> if (rc < 0) {                                                               <* 
       *>    DEBUG_INPT   yLOG_note    ("directory not valid");                       <* 
       *>    continue;                                                                <* 
       *> }                                                                           <*/
      /*---(get name)--------------------*/
      rc = poly_proj__get_name (x_home, x_name);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("name not valid");
         continue;
      }
      /*---(save)------------------------*/
      poly_world__add (x_name, x_home);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = poly_shared_close ('w');
   DEBUG_INPT   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(return to current)--------------*/
   /*> rc = chdir (x_curr);                                                           <* 
    *> DEBUG_INPT   yLOG_value   ("chdir"     , rc);                                  <* 
    *> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   yURG_msg ('-', "imported %d entries from world registry", poly_world__count ());
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_world__export      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   rc = poly_shared_open ('W', NULL);
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk-through)-------------------*/
   DEBUG_DATA   yLOG_value   ("count"     , poly_world__count ());
   rc = poly_world__by_cursor ('[', &x_world);
   while (rc >= 0 && x_world != NULL) {
      DEBUG_DATA   yLOG_info  ("->name"    , x_world->name);
      fprintf (my.f_world, "%s\n", x_world->home);
      rc = poly_world__by_cursor ('>', &x_world);
   }
   /*---(close)--------------------------*/
   rc = poly_shared_close ('W');
   DEBUG_INPT   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   yURG_msg ('-', "exported %d entries to world registry", poly_world__count ());
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    registering and unregistering             ----===*/
/*====================------------------------------------====================*/
static void  o___REGISTER________o () { return; }

char
poly_world__register    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   char        x_name      [LEN_LABEL] = "";
   char        x_home      [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(get current project)------------*/
   rc = poly_proj_identify (x_name, x_home);
   --rce;  if (rc < 0) {
      yURG_err ('f', "could not determine current project");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "current directory is å%sæ", x_home);
   yURG_msg ('-', "therefore, project is named å%sæ", x_name);
   /*---(get current project)------------*/
   rc = poly_world__by_name (x_name, &x_world);
   if (x_world != NULL) {
      yURG_msg ('-', "project exists in registry, replacing in case subtle changes");
      poly_world__remove (x_name);
   } else {
      yURG_msg ('-', "project is new to registry, adding");
   }
   rc = poly_world__add    (x_name, x_home);
   --rce;  if (rc < 0) {
      yURG_err ('f', "project could not be added");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_world__unregister  (void)
{
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   char        x_name      [LEN_LABEL] = "";
   char        x_home      [LEN_HUND]  = "";
   rc = poly_proj_identify (x_name, x_home);
   --rce;  if (rc < 0)  return rce;
   rc = poly_world__by_name (x_name, &x_world);
   --rce;  if (x_world == NULL)  return rce;
   rc = poly_world__remove (x_name);
   --rce;  if (rc < 0)  return rce;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      major actions                           ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

char
poly_world_register     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(verify header)------------------*/
   yURG_msg ('>', "register project in world file...");
   /*---(purge)--------------------------*/
   rc = poly_world__purge ();
   DEBUG_INPT   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   rc = poly_world__import ();
   DEBUG_INPT   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_note    ("no existing file");
   }
   /*---(register)-----------------------*/
   rc = poly_world__register ();
   DEBUG_INPT   yLOG_value   ("register"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(export)-------------------------*/
   rc = poly_world__export ();
   DEBUG_INPT   yLOG_value   ("export"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(mute)---------------------------*/
   yURG_msg ('-', "success, current project confirmed in world file");
   yURG_msg (' ', "");
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_world_unregister   (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(purge)--------------------------*/
   rc = poly_world__purge ();
   DEBUG_INPT   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   rc = poly_world__import ();
   DEBUG_INPT   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_note    ("no existing file");
      return  rce;
   }
   /*---(register)-----------------------*/
   rc = poly_world__unregister ();
   DEBUG_INPT   yLOG_value   ("register"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(export)-------------------------*/
   rc = poly_world__export ();
   DEBUG_INPT   yLOG_value   ("export"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_world_system       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_curr      [LEN_RECD]  = "";
   char       *p           = NULL;
   tWORLD     *x_world     = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(save present directory)---------*/
   p = getcwd (x_curr, LEN_RECD);
   DEBUG_INPT   yLOG_point   ("getcwd"    , p);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(purge)--------------------------*/
   rc = poly_world__purge ();
   DEBUG_INPT   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(import)-------------------------*/
   rc = poly_world__import ();
   DEBUG_INPT   yLOG_value   ("import"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_note    ("no existing file");
   }
   /*---(walk-through)-------------------*/
   DEBUG_DATA   yLOG_value   ("count"     , poly_world__count ());
   rc = poly_world__by_cursor ('[', &x_world);
   while (rc >= 0 && x_world != NULL) {
      DEBUG_DATA   yLOG_point ("x_world"   , x_world);
      DEBUG_DATA   yLOG_info  ("->name"    , x_world->name);
      yURG_msg     (YURG_BASE, "%-15.15s %s", x_world->name, x_world->home);
      /*---(return to current)--------------*/
      rc = chdir (x_world->home);
      DEBUG_INPT   yLOG_value   ("chdir"     , rc);
      if (rc < 0) continue;
      rc = poly_action__here ();
      DEBUG_INPT   yLOG_value   ("here"      , rc);
      rc = poly_world__by_cursor ('>', &x_world);
   }
   /*---(write database)-----------------*/
   rc = poly_action__write   ();
   DEBUG_PROG   yLOG_value   ("write"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(return to current)--------------*/
   rc = chdir (x_curr);
   DEBUG_INPT   yLOG_value   ("chdir"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_world_init         (void)
{
   poly_world_cli (F_WORLD, '-');
   my.f_world = NULL;
   poly_world__purge ();
   return 0;
}

char
poly_world__purge       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWORLD     *x_world     = NULL;
   tWORLD     *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(walk-through)-------------------*/
   DEBUG_DATA   yLOG_value   ("count"     , poly_world__count ());
   rc = poly_world__by_cursor ('[', &x_world);
   while (rc >= 0 && x_world != NULL) {
      rc = poly_world__by_cursor ('>', &x_next);
      DEBUG_DATA   yLOG_point ("x_world"   , x_world);
      DEBUG_DATA   yLOG_info  ("->name"    , x_world->name);
      rc = poly_world__remove (x_world->name);
      x_world = x_next;
   }
   /*---(check)--------------------------*/
   DEBUG_DATA   yLOG_value   ("count"     , poly_world__count ());
   --rce;  if (poly_world__count () > 0) {
      yURG_msg ('f', "could not prepare/clear registry, %d entries remain", poly_world__count ());
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yURG_msg ('-', "current registry prepared for import");
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_world_wrap         (void)
{
   poly_world__purge ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-[ unit test accessor ]---------------------[us2---·A-7·6--·B21-]¬[----·T-B1H---·---·----]¬[---·------]*/
poly_world__unit        (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =    0;
   char        x_exist     =  '-';
   char        t           [LEN_LABEL] = " 0[]";
   char        s           [LEN_HUND]  = " 0[]";
   tWORLD     *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "WORLD unit       : question unknown");
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "WORLD count      : %3dn", poly_world__count ());
   }
   else if (strcmp (a_question, "file"      )     == 0) {
      rc = poly_shared_verify (my.n_world);
      if      (rc >  0)  x_exist = 'y';
      else if (rc <= 0)  x_exist = '-';
      snprintf (unit_answer, LEN_RECD, "WORLD file       : %c  %-10p  %c  %2d[%s]",
            (my.f_world  == NULL) ? '-' : 'y', my.f_world,
            x_exist, strlen (my.n_world), my.n_world);
   }
   else if (strcmp (a_question, "entry"     )     == 0) {
      poly_world__by_index (i, &u);
      if (u != NULL) {
         sprintf  (t, "%2d[%.15s]", strlen (u->name), u->name);
         sprintf  (s, "%2d[%.60s]", strlen (u->home), u->home);
      }
      snprintf (unit_answer, LEN_RECD, "WORLD entry (%2d) : %-19.19s  %s", i, t, s);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


