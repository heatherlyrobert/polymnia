/*============================----beg-of-source---============================*/
#include  "polymnia.h"



static char   s_print         [LEN_RECD] = "";

static tELIB  *s_head   = NULL;
static int     s_count  = 0;


/*====================------------------------------------====================*/
/*===----                       basic support                          ----===*/
/*====================------------------------------------====================*/
static void  o___CLI_____________o () { return; }

char
poly_extern_cli         (char *a_name, char a_loud)
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
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "external <name>, name can not be null");
      DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ARGS  yLOG_info    ("a_name"    , a_name);
   strlcpy (x_recd, a_name, LEN_RECD);
   /*---(check length)-------------------*/
   l = strlen (x_recd);
   DEBUG_ARGS  yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "external <name>, name can not be blank/empty");
      DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check characters)---------------*/
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (x_valid, x_recd [i]) != NULL)  continue;
      if (a_loud == 'y')  yURG_err (YURG_FATAL, "external <name>, name can not have a <%c> at character %d", x_recd [i], i);
      DEBUG_PROG  yLOG_char  ("bad char"  , x_recd [i]);
      DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check extension)----------------*/
   if (l >= 5 && strcmp (x_recd + l - 4, ".txt") != 0) {
      strlcat (x_recd, ".txt", LEN_RECD);
      DEBUG_ARGS  yLOG_info    ("fixed"     , x_recd);
   }
   /*---(copy)---------------------------*/
   strlcpy (my.n_extern, x_recd, LEN_RECD);
   DEBUG_ARGS  yLOG_info    ("external"  , my.n_extern);
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      support functions                       ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

static char  *s_inputs  = " getc getchar gets ungetc scanf vscanf scanf vscanf ";
static char  *s_readers = " fopen freopen fclose fgetc fgets fscanf vfscanf ftell stello fseek fseeko fgetpos fsetpos rewind ";
static char  *s_outputs = " putc putchar puts printf vprintf printf vprintf ";
static char  *s_writers = " fflush fputc fputs fprintf vfprintf fprintf vfprintf ";
static char  *s_breads  = " fread ";
static char  *s_bwrites = " fwrite ";
static char  *s_memory  = " malloc calloc realloc free memset memcpy memmove memcmp memchr ";
static char  *s_filesys = " remove rename tmpfile tmpnam dup dup2 getwd lockf read readlink stat lstat fstat access chmod chown ";
static char  *s_systems = " getenv system gedgroups gethostid getlogin getlogin_r getopt getpgid pipe pread pwrite ";
static char  *s_process = " execl execle execlp execv execve execvp fork vfork nice pause wait waitpid waitid kill clone signal sigaction wait4 getpgid getpgrp getegid geteuid getgid getpid getppid getsid getuid setegid seteuid setgid setpgid setpgrp setregid setreuid setsid ";

char         /*-[ categorize external functions -------------[ leaf  [fc3---·916·19-·K-1-]¬[11---·R-·R--R---·---·----]¬[?#p-#·N-1--M·----]¬*/
poly_extern__mark        (tEXTERN *a_curr, char *a_lib, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_HUND]  = "";
   /*---(default)------------------------*/
   a_curr->cat    = '-';
   a_curr->sub    = '-';
   /*---(ncurses)------------------------*/
   if      (strcmp  (a_lib, "curses.h"   ) == 0)   a_curr->cat = 'N';
   else if (strcmp  (a_lib, "ncurses.h"  ) == 0)   a_curr->cat = 'N';
   /*---(opengl)-------------------------*/
   else if (strcmp  (a_lib, "gl.h"       ) == 0)   a_curr->cat = 'O';
   else if (strcmp  (a_lib, "glx.h"      ) == 0)   a_curr->cat = 'O';
   else if (strcmp  (a_lib, "glu.h"      ) == 0)   a_curr->cat = 'O';
   /*---(xwindows)-----------------------*/
   else if (strcmp  (a_lib, "X.h"        ) == 0)   a_curr->cat = 'X';
   else if (strcmp  (a_lib, "Xlib.h"     ) == 0)   a_curr->cat = 'X';
   else if (strcmp  (a_lib, "Xutil.h"    ) == 0)   a_curr->cat = 'X';
   else if (strcmp  (a_lib, "Xatom.h"    ) == 0)   a_curr->cat = 'X';
   else if (strcmp  (a_lib, "keysym.h"   ) == 0)   a_curr->cat = 'X';
   /*---(custom libraries)---------------*/
   else if (strcmp  (a_lib, "yFONT.h"    ) == 0)   a_curr->cat = 'y';
   else if (strcmp  (a_lib, "yGLTEX.h"   ) == 0)   a_curr->cat = 'y';
   else if (strcmp  (a_lib, "yCOLOR.h"   ) == 0)   a_curr->cat = 'y';
   else if (strcmp  (a_lib, "yX11.h"     ) == 0)   a_curr->cat = 'y';
   else if (strcmp  (a_lib, "yVIKEYS.h"  ) == 0)   a_curr->cat = 'y';
   else if (strcmp  (a_lib, "yLOG.h"     ) == 0) {
      if (strncmp (a_name, "yLOG_s"  ,  6) == 0)   a_curr->cat = 'd';
      else                                         a_curr->cat = 'D';
      if      (strstr (a_name, "enter") != NULL)   a_curr->sub = 'e';
      else if (strstr (a_name, "exit" ) != NULL)   a_curr->sub = 'x';
   }
   else if (strcmp  (a_lib, "yURG.h"     ) == 0)   a_curr->cat = 'D';
   else if (a_lib [0] == 'y' && strchr (YSTR_UPPER, a_lib [1]) != NULL)  a_curr->cat = 'Y';
   /*---(standard)-----------------------*/
   else {
      sprintf (t, " %s ", a_name);
      a_curr->cat = 'C';
      if      (strstr (s_inputs  , t) != NULL)          a_curr->sub = 'i';
      else if (strstr (s_readers , t) != NULL)          a_curr->sub = 'r';
      else if (strstr (s_breads  , t) != NULL)          a_curr->sub = 'R';
      else if (strstr (s_outputs , t) != NULL)          a_curr->sub = 'o';
      else if (strstr (s_writers , t) != NULL)          a_curr->sub = 'w';
      else if (strstr (s_bwrites , t) != NULL)          a_curr->sub = 'W';
      else if (strstr (s_memory  , t) != NULL)          a_curr->sub = 'm';
      else if (strstr (s_filesys , t) != NULL)          a_curr->sub = 'f';
      else if (strstr (s_systems , t) != NULL)          a_curr->sub = 's';
      else if (strstr (s_process , t) != NULL)          a_curr->sub = 'p';
      else if (strncmp ("pthread_", a_name, 8) == 0)    a_curr->sub = 'T';
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_extern__wipe        (tEXTERN *a_ext)
{
   /*---(info)--------------*/
   a_ext->elib     = NULL;
   a_ext->name [0] = '\0';
   a_ext->line     = -1;
   a_ext->type     = '-';
   a_ext->cat      = '-';
   a_ext->sub      = '-';
   a_ext->count    = 0;
   /*---(working)-----------*/
   a_ext->wuse     = 0;
   /*---(elibs)-------------*/
   a_ext->l_next   = NULL;
   a_ext->l_prev   = NULL;
   /*---(ylibs)-------------*/
   a_ext->y_head   = NULL;
   a_ext->y_tail   = NULL;
   a_ext->y_count  = 0;
   /*---(btree)-------------*/
   a_ext->btree    = NULL;
   /*---(done)--------------*/
   return 1;
}

char
poly_elib__wipe          (tELIB *a_elib)
{
   /*---(info)--------------*/
   a_elib->name [0] = '\0';
   a_elib->wuse     = 0;
   /*---(externs)-----------*/
   a_elib->count  = 0;
   a_elib->head   = NULL;
   a_elib->tail   = NULL;
   /*---(btree)-------------*/
   a_elib->btree    = NULL;
   /*---(done)--------------*/
   return 1;
}

char*
poly_extern__memory     (tEXTERN *a_ext)
{
   /*---(master)-------------------------*/
   strlcpy (s_print, "["  , LEN_RECD);
   poly_shared__check_ptr  (s_print, a_ext->elib);
   poly_shared__check_str  (s_print, a_ext->name);
   poly_shared__check_num  (s_print, a_ext->line);
   poly_shared__check_char (s_print, a_ext->type);
   poly_shared__check_char (s_print, a_ext->cat);
   poly_shared__check_char (s_print, a_ext->sub);
   poly_shared__check_num  (s_print, a_ext->wuse);
   poly_shared__spacer     (s_print);
   poly_shared__check_ptr  (s_print, a_ext->y_head);
   poly_shared__check_ptr  (s_print, a_ext->y_tail);
   poly_shared__check_num  (s_print, a_ext->y_count);
   poly_shared__spacer     (s_print);
   poly_shared__check_ptr  (s_print, a_ext->btree);
   strlcat (s_print, "]" , LEN_RECD);
   /*---(complete)-----------------------*/
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char poly_extern__new   (tEXTERN **a_new) { return poly_shared_new  ("ext" , sizeof (tEXTERN), a_new, NULL, '-', poly_extern__wipe); }
char poly_extern_force  (tEXTERN **a_new) { return poly_shared_new  ("ext" , sizeof (tEXTERN), a_new, NULL, 'y', poly_extern__wipe); }
char poly_extern__free  (tEXTERN **a_old) { return poly_shared_free ("ext" , a_old, NULL); }

char poly_extern__lnew  (tEXTERN **a_new) { return poly_shared_new  ("elib", sizeof (tELIB), a_new, NULL, '-', poly_elib__wipe); }
char poly_extern__lfree (tEXTERN **a_old) { return poly_shared_free ("elib", a_old, NULL); }



/*====================------------------------------------====================*/
/*===----                   hooking and unhooking                      ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

char
poly_extern_hook         (tELIB *a_elib, tEXTERN *a_ext)
{
   char        rce         =  -10;
   /*---(header)-------------------------*/
   /*> DEBUG_DATA   yLOG_senter  (__FUNCTION__);                                      <*/
   DEBUG_DATA   yLOG_enter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point  ("a_elib", a_elib);
   --rce;  if (a_elib == NULL) {
      /*> DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);                              <*/
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> DEBUG_DATA   yLOG_spoint  (a_file);                                            <*/
   DEBUG_DATA   yLOG_point  ("a_ext", a_ext);
   --rce;  if (a_ext == NULL) {
      /*> DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);                              <*/
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> DEBUG_DATA   yLOG_spoint  (a_ext->proj);                                      <*/
   DEBUG_DATA   yLOG_point  ("->proj", a_ext->elib);
   --rce;  if (a_ext->elib != NULL) {
      /*> DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);                              <*/
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> DEBUG_DATA   yLOG_snote   (a_ext->name);                                      <*/
   DEBUG_DATA   yLOG_note   (a_ext->name);
   /*---(into linked list)---------------*/
   /*> DEBUG_DATA   yLOG_sint    (a_ext->elib->count);                               <* 
    *> DEBUG_DATA   yLOG_spoint  (a_elib->head);                                      <* 
    *> DEBUG_DATA   yLOG_spoint  (a_elib->tail);                                      <*/
   DEBUG_DATA   yLOG_value   ("count", a_elib->count);
   DEBUG_DATA   yLOG_point  ("head" , a_elib->head);
   DEBUG_DATA   yLOG_point  ("tail", a_elib->tail);
   if (a_elib->head == NULL) {
      /*> DEBUG_DATA   yLOG_snote   ("first");                                        <*/
      DEBUG_DATA   yLOG_note   ("first");
      a_elib->head = a_elib->tail = a_ext;
   } else {
      /*> DEBUG_DATA   yLOG_snote   ("append");                                       <*/
      DEBUG_DATA   yLOG_note   ("append");
      a_ext->l_prev         = a_elib->tail;
      a_elib->tail->l_next  = a_ext;
      a_elib->tail          = a_ext;
   }
   /*---(tie file back to elib)----------*/
   a_ext->elib  = a_elib;
   /*---(update count)-------------------*/
   ++a_elib->count;
   DEBUG_DATA   yLOG_value   ("count", a_elib->count);
   /*---(complete)------------------------------*/
   /*> DEBUG_DATA   yLOG_sexit   (__FUNCTION__);                                      <*/
   DEBUG_DATA   yLOG_exit   (__FUNCTION__);
   return 0;
}

char
poly_extern_unhook        (tEXTERN *a_ext)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_ext);
   if (a_ext == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   DEBUG_DATA   yLOG_spoint  (a_ext->elib);
   if (a_ext->elib == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -2);
      return -2;
   }
   DEBUG_DATA   yLOG_snote   (a_ext->name);
   /*---(out of linked list)-------------*/
   DEBUG_DATA   yLOG_sint    (a_ext->elib->count);
   DEBUG_DATA   yLOG_spoint  (a_ext->elib->head);
   DEBUG_DATA   yLOG_spoint  (a_ext->elib->tail);
   DEBUG_DATA   yLOG_snote   ("unlink");
   if (a_ext->l_next != NULL)  a_ext->l_next->l_prev = a_ext->l_prev;
   else                        a_ext->elib->tail     = a_ext->l_prev;
   if (a_ext->l_prev != NULL)  a_ext->l_prev->l_next = a_ext->l_next;
   else                        a_ext->elib->head     = a_ext->l_next;
   /*---(update count)-------------------*/
   --(a_ext->elib->count);
   DEBUG_DATA   yLOG_sint    (a_ext->elib->count);
   /*---(ground pointers)----------------*/
   a_ext->elib   = NULL;
   a_ext->l_prev = NULL;
   a_ext->l_next = NULL;
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_extern_add         (char *a_lib, char *a_name, int a_line, char a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tELIB      *x_lib       = NULL;
   tEXTERN    *x_new       = NULL;
   int         x_tries     =    0;
   int         x_len       =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_len    = strlen (a_name);
   --rce;  if (x_len <= 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   DEBUG_DATA   yLOG_point   ("a_lib"     , a_lib);
   --rce;  if (a_lib == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_lib"     , a_lib);
   /*---(find lib)-----------------------*/
   ySORT_by_name (B_ELIB, a_lib, &x_lib);
   --rce;  if (x_lib == NULL) {
      poly_extern__lnew (&x_lib);
      DEBUG_DATA   yLOG_point   ("x_lib"     , x_lib);
      --rce;  if (x_lib == NULL) {
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      poly_elib__wipe (x_lib);
      strlcpy (x_lib->name, a_lib , LEN_LABEL);
      rc = ySORT_hook (B_ELIB, x_lib, x_lib->name, &x_lib->btree);
      ySORT_prepare (B_ELIB);
   }
   /*---(create cell)--------------------*/
   poly_extern__new (&x_new);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   poly_extern__wipe (x_new);
   /*> x_new->elib     = x_lib;                                                       <*/
   poly_extern_hook (x_lib, x_new);
   strlcpy (x_new->name, a_name, LEN_TITLE);
   x_new->line     = a_line;
   x_new->type     = a_type;
   poly_extern__mark (x_new, a_lib, a_name);
   /*---(into btree)---------------------*/
   rc = ySORT_hook (B_EXTERN, x_new, x_new->name, &x_new->btree);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_remove       (tEXTERN *a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(begin)--------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_old"     , a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(btree)--------------------------*/
   rc = ySORT_unhook (&a_old->btree);
   DEBUG_DATA   yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free)---------------------------*/
   poly_extern__free (&a_old);
   DEBUG_DATA   yLOG_point   ("a_old"     , a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_load        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   char        x_lib       [LEN_TITLE] = "";
   char        x_name      [LEN_TITLE] = "";
   int         x_line      =    0;
   char        x_type      =  '-';
   char       *p           = NULL;
   char       *q           = NULL;
   char       *r           = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(purge existing)-----------------*/
   rc = ySORT_purge (B_EXTERN);
   /*---(open)---------------------------*/
   rc = poly_shared_open ('e', NULL);
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = poly_shared_read ('e', NULL, x_recd, NULL);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("end of file");
         break;
      }
      /*---(parse)-----------------------*/
      rc = poly_shared_parse_tags (x_recd, x_name, &x_type, &x_line, x_lib);
      DEBUG_INPT   yLOG_value   ("parse"     , rc);
      if (rc < 0)    continue;
      /*---(save)------------------------*/
      poly_extern_add (x_lib, x_name, x_line, x_type);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = poly_shared_close ('e');
   DEBUG_INPT   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(check count)--------------------*/
   DEBUG_INPT   yLOG_value   ("count"     , poly_extern_count ());
   --rce;  if (poly_extern_count () <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare for use)----------------*/
   rc = ySORT_prepare   (B_EXTERN);
   DEBUG_INPT   yLOG_value   ("btree"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> poly_extern_list ();                                                           <*/
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_extern_init        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = ySORT_btree (B_EXTERN, "externals");
   DEBUG_PROG   yLOG_value   ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = ySORT_btree (B_ELIB  , "libraries");
   DEBUG_PROG   yLOG_value   ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (my.n_extern, F_EXTERN, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("n_extern"  , my.n_extern);
   my.f_extern = NULL;
   DEBUG_INPT   yLOG_point   ("f_extern"  , my.f_extern);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern__purge      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEXTERN    *u           = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_PROG   yLOG_value   ("count"     , poly_extern_count ());
   /*---(walk through list)--------------*/
   rc = ySORT_by_cursor (B_EXTERN, YDLST_HEAD, &u);
   DEBUG_PROG   yLOG_point   ("u"          , u);
   while (u != NULL) {
      DEBUG_PROG   yLOG_value   ("extern"    , u->name);
      rc = poly_extern_remove (u);
      DEBUG_PROG   yLOG_value   ("remove"    , rc);
      if (rc < 0) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      rc = ySORT_by_cursor (B_EXTERN, YDLST_HEAD, &u);
   }
   /*---(check)--------------------------*/
   DEBUG_PROG   yLOG_value   ("count"     , poly_extern_count ());
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_clear_uses  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tEXTERN    *u           = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_PROG   yLOG_value   ("count"     , poly_extern_count ());
   /*---(walk through list)--------------*/
   rc = ySORT_by_cursor (B_EXTERN, YDLST_HEAD, &u);
   DEBUG_PROG   yLOG_point   ("u"          , u);
   while (u != NULL) {
      DEBUG_PROG   yLOG_value   ("extern"    , u->name);
      u->wuse = 0;
      rc = ySORT_by_cursor (B_EXTERN, YDLST_NEXT, &u);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_wrap        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(walk through list)--------------*/
   /*> rc = poly_extern_count ();                                                     <*/
   /*> rc = poly_extern__purge ();                                                    <*/
   DEBUG_PROG   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> printf ("%d\n", poly_extern_count ());                                         <*/
   /*> DEBUG_PROG   printf ("%s %d\n", __FUNCTION__, poly_extern_count ());           <*/
   /*> rc = ySORT_purge (B_EXTERN);                                              <* 
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
/*===----                        searching                             ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  poly_extern_count       (void)                           { return ySORT_count     (B_EXTERN); }
char poly_extern_by_name     (uchar *a_name, tEXTERN **a_ext) { return ySORT_by_name   (B_EXTERN, a_name, a_ext); }
char poly_extern_by_index    (int n, tEXTERN **a_ext)         { return ySORT_by_index  (B_EXTERN, n, a_ext); }
char poly_extern_by_cursor   (char a_dir, tEXTERN **a_ext)    { return ySORT_by_cursor (B_EXTERN, a_dir, a_ext); }
char poly_extern_list        (void)                           { return ySORT_list      (B_EXTERN); }



/*====================------------------------------------====================*/
/*===----                        mass actions                          ----===*/
/*====================------------------------------------====================*/
static void  o___MASS____________o () { return; }

char
poly_extern__pointers   (char *a_func, char *a_file, int a_line, tFUNC **a_src, tFUNC **a_dst, tEXTERN **a_ext)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   tFILE      *x_file      = NULL;
   int         x_len       =    0;
   char        x_proj      [LEN_TITLE] = "";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_func"    , a_func);
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_file"    , a_file);
   DEBUG_INPT   yLOG_value   ("a_line"    , a_line);
   DEBUG_INPT   yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_src = NULL;
   DEBUG_INPT   yLOG_point   ("a_dst"     , a_dst);
   --rce;  if (a_dst == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_dst = NULL;
   DEBUG_INPT   yLOG_point   ("a_ext"     , a_ext);
   --rce;  if (a_ext == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *a_ext = NULL;
   /*---(idenfify file)---------------*/
   poly_file_by_name (a_file, &x_file);
   DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
   --rce;  if (x_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("file name" , x_file->name);
   /*---(get source tag)--------------*/
   rc = poly_func_by_line (x_file, a_line, a_src);
   DEBUG_INPT   yLOG_point   ("*a_scr"    , *a_src);
   --rce;  if (*a_src == NULL) {
      DEBUG_INPT   yLOG_note    ("function not found");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("->name"    , (*a_src)->name);
   DEBUG_INPT   yLOG_info    ("->file"    , (*a_src)->file->name);
   DEBUG_INPT   yLOG_info    ("->proj"    , (*a_src)->file->proj->name);
   x_len = strlen ((*a_src)->file->proj->name);
   if ((*a_src)->file->proj->name [0] == 'y') {
      if (strchr (YSTR_UPPER, (*a_src)->file->proj->name [1]) != NULL) {
         DEBUG_INPT   yLOG_note    ("found a heatherly library reference");
         strlcpy (x_proj, (*a_src)->file->proj->name, LEN_TITLE);
      }
   }
   /*---(get destination tag)---------*/
   poly_func_by_name (a_func, a_dst);
   DEBUG_INPT   yLOG_point   ("*a_dst"    , *a_dst);
   if (*a_dst != NULL) {
      DEBUG_INPT   yLOG_info    ("->name"    , (*a_dst)->name);
      DEBUG_INPT   yLOG_info    ("->file"    , (*a_dst)->file->name);
      DEBUG_INPT   yLOG_info    ("->proj"    , (*a_dst)->file->proj->name);
   }
   /*---(get external tag)------------*/
   poly_extern_by_name (a_func, a_ext);
   DEBUG_INPT   yLOG_point   ("*a_ext"    , *a_ext);
   if (*a_ext != NULL)  {
      DEBUG_INPT   yLOG_info    ("->name"    , (*a_ext)->elib->name);
      if      (strncmp (x_proj, (*a_ext)->elib->name, x_len) == 0)  *a_ext = NULL;
      else if (strcmp  (x_proj, "ySTR") == 0 && strncmp ((*a_ext)->name, "strl", 4) == 0)  *a_ext = NULL;
   }
   /*---(mystry)----------------------*/
   --rce;  if (*a_dst == NULL && *a_ext == NULL) {
      /*> if (x_mystry %  5 == 0)  fprintf (s_mystry, "¦");                                                                                           <* 
       *> if (x_mystry % 25 == 0)  fprintf (s_mystry, "##---calling-file-------   line   ---calling-function------   ---mystery-function------¦¦");   <* 
       *> fprintf (s_mystry, "%-25.25s  %4d   %-25.25s   %-25.25s¦",                                                                                  <* 
       *>       x_file->name, x_line, x_src->name, x_funcname);                                                                                       <* 
       *> ++x_src->WORK_MYSTRY;                                                                                                                       <* 
       *> ++x_mystry;                                                                                                                                 <*/
      DEBUG_INPT   yLOG_note    ("found a mystry function");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern__tally      (tFUNC *a_src, tFUNC *a_dst, tEXTERN *a_ext, int a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           = " :";
   char       *s           = NULL;
   tFILE      *x_file      = NULL;
   char        x_cat       =  '-';
   char        x_sub       =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_dst"     , a_dst);
   DEBUG_INPT   yLOG_point   ("a_ext"     , a_ext);
   --rce;  if (a_dst == NULL && a_ext == NULL) {
      ++a_src->WORK_FUNCS;
      ++a_src->WORK_MYSTRY;
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_ext != NULL) {
      x_cat = a_ext->cat;
      DEBUG_INPT   yLOG_char    ("x_cat"     , x_cat);
      x_sub = a_ext->sub;
      DEBUG_INPT   yLOG_char    ("x_sub"     , x_sub);
   }
   /*> --rce;  if (a_dst != NULL && a_ext != NULL) {                                            <* 
    *>    /+> DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <+/   <* 
    *>    /+> return 0;                                                                   <+/   <* 
    *>    a_ext = NULL;                                                                         <* 
    *>    DEBUG_INPT   yLOG_note    ("nulled out a_ext");                                       <* 
    *> }                                                                                        <*/
   /*---(general)------------------------*/
   ++a_src->WORK_FUNCS;
   /*---(recursive)----------------------*/
   if (a_src == a_dst) {
      DEBUG_INPT   yLOG_note    ("found a recursive reference");
      ++a_src->WORK_RECURS;
      --a_src->WORK_FUNCS;
   }
   /*---(internal)-----------------------*/
   else if (a_dst != NULL && a_ext == NULL) {
      DEBUG_INPT   yLOG_note    ("found a local/global internal call");
      DEBUG_INPT   yLOG_point   ("a_src"     , a_src);
      DEBUG_INPT   yLOG_point   ("->file"    , a_src->file);
      DEBUG_INPT   yLOG_point   ("->work"    , a_src->work);
      DEBUG_INPT   yLOG_point   ("a_dst"     , a_dst);
      DEBUG_INPT   yLOG_point   ("->file"    , a_dst->file);
      DEBUG_INPT   yLOG_point   ("->work"    , a_dst->work);
      if      (a_src->file == a_dst->file) {
         ++a_src->WORK_LFUNCS;
         ++a_dst->WORK_LCALLS;
      }
      else if (a_src->file->proj == a_dst->file->proj) {
         ++a_src->WORK_GFUNCS;
         ++a_dst->WORK_GCALLS;
      }
   }
   /*---(debugging)----------------------*/
   else if (strchr ("Dd", x_cat) != NULL) {
      DEBUG_INPT   yLOG_note    ("found debugging code");
      ++a_src->WORK_DFUNCS;
      ++a_ext->count;
      switch (x_cat) {
      case 'd' :
         ++a_src->WORK_DSHORT;
         switch (x_sub) {
         case 'e' :   ++a_src->WORK_DENTER;      break;
         case 'x' :   ++a_src->WORK_DEXIT;       break;
         }
         break;
      case 'D' :
         ++a_src->WORK_DLONG;
         switch (x_sub) {
         case 'e' :   ++a_src->WORK_DENTER;      break;
         case 'x' :   ++a_src->WORK_DEXIT;       break;
         }
         break;
      }
   }
   /*---(standard library)---------------*/
   /*> else if (strchr ("owWirRmpfsTC", a_ext->sub) != NULL) {                        <*/
   else if (x_cat == 'C') {
      DEBUG_INPT   yLOG_note    ("found a standard c library reference");
      ++a_src->WORK_CSTD;
      ++a_ext->count;
      switch (x_sub) {
      case 'o' : ++a_src->WORK_OUTPUT;           break;
      case 'w' : ++a_src->WORK_TWRITE;           break;
      case 'W' : ++a_src->WORK_BWRITE;           break;
      case 'i' : ++a_src->WORK_INPUT;            break;
      case 'r' : ++a_src->WORK_TREAD;            break;
      case 'R' : ++a_src->WORK_BREAD;            break;
      case 'm' : ++a_src->WORK_MEMORY;           break;
      case 'p' : ++a_src->WORK_PROCS;            break;
      case 'f' : ++a_src->WORK_FILESYS;          break;
      case 's' : ++a_src->WORK_OPSYS;            break;
      }
   }
   /*---(other libraries)----------------*/
   else {
      DEBUG_INPT   yLOG_note    ("found outside library reference");
      ++a_ext->count;
      switch (x_cat) {
      case 'N' : ++a_src->WORK_NCURSE;
                 ++a_src->WORK_OFUNCS;
                 break;
      case 'O' : ++a_src->WORK_OPENGL;
                 ++a_src->WORK_OFUNCS;
                 break;
      case 'X' : ++a_src->WORK_WINDOW;
                 ++a_src->WORK_OFUNCS;
                 break;
      case 'y' : ++a_src->WORK_MYX;
      case 'Y' : ++a_src->WORK_YLIB;
                 DEBUG_INPT   yLOG_note    ("found yLIB library reference");
                 poly_ylib_add (a_src, a_ext, a_line, NULL);
                 break;
      case '-' : ++a_src->WORK_OFUNCS;
                 break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_review      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   char       *p           = NULL;
   char       *q           = NULL;
   char        x_recd      [LEN_RECD];
   char        x_name      [LEN_TITLE];
   char        x_lib       [LEN_TITLE];
   char        x_defn      =  '-';
   int         x_len       =    0;
   int         x_flen      =    0;
   int         x_line      =    0;
   tFILE      *x_file      =    0;
   tFUNC      *x_src       = NULL;
   tFUNC      *x_dst       = NULL;
   tEXTERN    *x_ext       = NULL;
   int         c           =    0;
   char        x_cat       =  ' ';
   int         x_ylibs     =    0;
   int         x_mystry    =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = poly_shared_open ('f', NULL);
   DEBUG_INPT   yLOG_value   ("cflow"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   rc = poly_shared_open ('m', NULL);
   DEBUG_INPT   yLOG_value   ("mystry"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(read)------------------------*/
      rc = poly_shared_read ('f', NULL, x_recd, NULL);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0) {
         DEBUG_INPT   yLOG_note    ("end of file");
         break;
      }
      /*---(parse)-----------------------*/
      rc = poly_shared_parse_flow (x_recd, x_name, &x_defn, &x_line, x_lib);
      DEBUG_INPT   yLOG_value   ("parse"     , rc);
      if (rc < 0)    continue;
      /*---(get pointers)----------------*/
      rc = poly_extern__pointers (x_name, x_lib, x_line, &x_src, &x_dst, &x_ext);
      DEBUG_INPT   yLOG_value   ("pointers"  , rc);
      if (rc < 0)    continue;
      /*---(tally results)---------------*/
      rc = poly_extern__tally (x_src, x_dst, x_ext, x_line);
      DEBUG_INPT   yLOG_value   ("tally"     , rc);
      if (rc < 0)    continue;
      /*---(done)------------------------*/
   }
   /*---(wrapup)-------------------------*/
   rc = poly_shared_close ('f');
   DEBUG_INPT   yLOG_value   ("cflow"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   fprintf (my.f_mystry, "¦## done, finito, complete¦");
   rc = poly_shared_close ('m');
   DEBUG_INPT   yLOG_value   ("mystry"    , rc);
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

char
poly_extern__unit_work  (char a_spc, char a_suf, char a_val, char *a_out)
{
   char        s           [LEN_LABEL] = "";
   if (a_spc == 'y')  sprintf (s, "   ");
   else               sprintf (s, " ");
   strlcat (a_out, s, LEN_RECD);
   if (a_val >  0)    sprintf (s, "%1d%c", a_val, a_suf);
   else               sprintf (s, "·%c"  ,        a_suf);
   strlcat (a_out, s, LEN_RECD);
   return 0;
}

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_extern__unit       (char *a_question, int i)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_exist     =  '-';
   tEXTERN    *u           = NULL;
   tFUNC      *v           = NULL;
   char        t           [LEN_RECD]  = "";
   char        s           [LEN_RECD]  = "[]";
   char        r           [LEN_RECD]  = "[]";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "EXTERN unit      : tag number unknown");
   if (i <  0)       return unit_answer;
   poly_extern_by_index (i, &u);
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "file"      )     == 0) {
      rc = poly_shared_verify (my.n_extern);
      if      (rc >  0)  x_exist = 'y';
      else if (rc <= 0)  x_exist = '-';
      snprintf (unit_answer, LEN_RECD, "EXTERN file      : %c  %-10p  %c  %2d[%s]",
            (my.f_extern == NULL) ? '-' : 'y', my.f_extern,
            x_exist, strlen (my.n_extern), my.n_extern);
   }
   /*> if        (strcmp (a_question, "file"      )     == 0) {                       <* 
    *>    snprintf (unit_answer, LEN_RECD, "EXTERN file      : %s", my.n_extern);     <* 
    *> }                                                                              <*/
   if (u != NULL) sprintf  (s, "[%.20s]", u->name);
   if        (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "EXTERN count     : %3d", poly_extern_count ());
   }
   else if   (strcmp (a_question, "entry"     )     == 0) {
      if (u != NULL)  sprintf  (r, "[%.20s]", u->elib->name);
      if (u != NULL)  sprintf  (t, "%2d%-22.22s   %2d%-22.22s   %4d   %c   %c   %c   %4d", strlen (u->elib->name), r, strlen (u->name), s, u->line, u->type, u->cat, u->sub, u->wuse);
      else            sprintf  (t, "%2d%-22.22s   %2d%-22.22s   %4d   %c   %c   %c   %4d", 0, "[]", 0, "[]", 0, '-', '-', '-', 0);
      snprintf (unit_answer, LEN_RECD, "EXTERN entry(%2d) : %s", i, t);
   }
   else if   (strcmp (a_question, "work"      )     == 0) {
      poly_func_by_index (i, &v);
      if (v != NULL) {
         sprintf  (s, "[%.13s]", v->name);
         sprintf  (unit_answer, "EXTERN work (%2d) : %-15.15s", i, s);
         poly_extern__unit_work ('y', 'e', v->WORK_ECALLS, unit_answer);
         poly_extern__unit_work ('-', 'g', v->WORK_GCALLS, unit_answer);
         poly_extern__unit_work ('-', 'n', v->WORK_LCALLS, unit_answer);
         poly_extern__unit_work ('-', 'r', v->WORK_RECURS, unit_answer);
         poly_extern__unit_work ('y', 'f', v->WORK_FUNCS , unit_answer);
         poly_extern__unit_work ('-', 'd', v->WORK_DFUNCS, unit_answer);
         poly_extern__unit_work ('-', 'n', v->WORK_LFUNCS, unit_answer);
         poly_extern__unit_work ('-', 'g', v->WORK_GFUNCS, unit_answer);
         poly_extern__unit_work ('-', 'c', v->WORK_CSTD  , unit_answer);
         poly_extern__unit_work ('-', 'y', v->WORK_YLIB  , unit_answer);
         poly_extern__unit_work ('-', 'o', v->WORK_OFUNCS, unit_answer);
         poly_extern__unit_work ('-', 'm', v->WORK_MYSTRY, unit_answer);
         poly_extern__unit_work ('y', 'r', v->WORK_INPUT  + v->WORK_TREAD  + v->WORK_BREAD  , unit_answer);
         poly_extern__unit_work ('-', 'w', v->WORK_OUTPUT + v->WORK_TWRITE + v->WORK_BWRITE , unit_answer);
         poly_extern__unit_work ('-', 's', v->WORK_PROCS  + v->WORK_OPSYS  + v->WORK_FILESYS, unit_answer);
         poly_extern__unit_work ('y', 'n', v->WORK_NCURSE, unit_answer);
         poly_extern__unit_work ('-', 'o', v->WORK_OPENGL, unit_answer);
         poly_extern__unit_work ('-', 'w', v->WORK_WINDOW, unit_answer);
         poly_extern__unit_work ('-', 'y', v->WORK_MYX   , unit_answer);
      }  else
         snprintf (unit_answer, LEN_RECD, "EXTERN work (%2d) : %-22.22s   ·e ·g ·l   ·f ·d ·n ·g ·c ·y ·o ·m   ·r ·w ·s   ·n ·o ·w ·y", i, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
