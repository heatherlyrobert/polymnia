/*============================----beg-of-source---============================*/
#include  "polymnia.h"



static char   s_print         [LEN_RECD] = "";



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

char         /*-[ categorize external functions -------------[ leaf  [fc3---�916�19-�K-1-]�[11---�R-�R--R---�---�----]�[?#p-#�N-1--M�----]�*/
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
   else if (strncmp (a_lib, "y"      ,  1) == 0)   a_curr->cat = 'Y';
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
   a_ext->lib [0]  = '\0';
   a_ext->name [0] = '\0';
   a_ext->line     = -1;
   a_ext->type     = '-';
   a_ext->cat      = '-';
   a_ext->sub      = '-';
   a_ext->uses     = 0;
   a_ext->y_head   = NULL;
   a_ext->y_tail   = NULL;
   a_ext->y_count  = 0;
   a_ext->btree    = NULL;
   return 1;
}

char*
poly_extern__memory     (tEXTERN *a_ext)
{
   /*---(master)-------------------------*/
   strlcpy (s_print, "["  , LEN_RECD);
   poly_shared__check_str  (s_print, a_ext->lib);
   poly_shared__check_str  (s_print, a_ext->name);
   poly_shared__check_num  (s_print, a_ext->line);
   poly_shared__check_char (s_print, a_ext->type);
   poly_shared__check_char (s_print, a_ext->cat);
   poly_shared__check_char (s_print, a_ext->sub);
   poly_shared__check_num  (s_print, a_ext->uses);
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

char poly_extern__new  (tEXTERN **a_new) { return poly_shared_new  ("ext", sizeof (tEXTERN), a_new, NULL, '-', poly_extern__wipe); }
char poly_extern_force (tEXTERN **a_new) { return poly_shared_new  ("ext", sizeof (tEXTERN), a_new, NULL, 'y', poly_extern__wipe); }
char poly_extern__free (tEXTERN **a_old) { return poly_shared_free ("ext", a_old, NULL); }



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
   strlcpy (x_new->lib , a_lib , LEN_TITLE);
   strlcpy (x_new->name, a_name, LEN_TITLE);
   x_new->line     = a_line;
   x_new->type     = a_type;
   poly_extern__mark (x_new, a_lib, a_name);
   /*---(into btree)---------------------*/
   rc = poly_btree_hook (B_EXTERN, x_new, x_new->name, &x_new->btree);
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
   rc = poly_btree_unhook (&a_old->btree);
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
   rc = poly_btree_purge (B_EXTERN);
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
   rc = poly_btree_dgnome   (B_EXTERN);
   DEBUG_INPT   yLOG_value   ("dgnome"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_btree_build (B_EXTERN);
   DEBUG_INPT   yLOG_value   ("build"      , rc);
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
   rc = poly_btree_init (B_EXTERN);
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
   u = (tEXTERN *) poly_btree_first (B_EXTERN);
   while (u != NULL) {
      DEBUG_PROG   yLOG_value   ("extern"    , u->name);
      rc = poly_extern_remove (u);
      DEBUG_PROG   yLOG_value   ("remove"    , rc);
      if (rc < 0) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rc);
         return rc;
      }
      u = (tEXTERN *) poly_btree_first (B_EXTERN);
   }
   /*---(check)--------------------------*/
   DEBUG_PROG   yLOG_value   ("count"     , poly_extern_count ());
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
   /*> rc = poly_btree_purge (B_EXTERN);                                              <* 
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

int poly_extern_count       (void) { return poly_btree_count (B_EXTERN); }

char
poly_extern_by_name     (uchar *a_name, tEXTERN **a_ext)
{
   if (a_ext == NULL)   return -1;
   *a_ext = (tEXTERN *) poly_btree_search  (B_EXTERN, a_name);
   if (*a_ext == NULL)  return -2;
   return 0;
}

char
poly_extern_by_index    (int n, tEXTERN **a_ext)
{
   if (a_ext == NULL)   return -1;
   *a_ext = (tEXTERN *) poly_btree_entry (B_EXTERN, n);
   if (*a_ext == NULL)  return -2;
   return 0;
}

char
poly_extern_cursor      (char a_dir, tEXTERN **a_ext)
{
   return poly_btree_cursor  (B_EXTERN, a_dir, a_ext);
}

char      poly_extern_list        (void) { return poly_btree_list (B_EXTERN); }



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
   char       *q           = " :";
   char       *s           = NULL;
   tFILE      *x_file      = NULL;
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
   /*> x_file = (tFILE *) poly_btree_search (B_FILES, a_file);                        <*/
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
   /*---(get destination tag)---------*/
   /*> *a_dst   = (tFUNC *)   poly_btree_search  (B_FUNCS, a_func);                   <*/
   poly_func_by_name (a_func, a_dst);
   DEBUG_INPT   yLOG_point   ("*a_dst"    , *a_dst);
   if (*a_dst != NULL)  DEBUG_INPT   yLOG_info    ("->name"    , (*a_dst)->name);
   poly_extern_by_name (a_func, a_ext);
   DEBUG_INPT   yLOG_point   ("*a_ext"    , *a_ext);
   if (*a_ext != NULL)  DEBUG_INPT   yLOG_info    ("->name"    , (*a_ext)->name);
   /*---(mystry)----------------------*/
   --rce;  if (*a_dst == NULL && *a_ext == NULL) {
      /*> if (x_mystry %  5 == 0)  fprintf (s_mystry, "�");                                                                                           <* 
       *> if (x_mystry % 25 == 0)  fprintf (s_mystry, "##---calling-file-------   line   ---calling-function------   ---mystery-function------��");   <* 
       *> fprintf (s_mystry, "%-25.25s  %4d   %-25.25s   %-25.25s�",                                                                                  <* 
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
   --rce;  if (a_dst != NULL && a_ext != NULL) {
      /*> DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <*/
      /*> return 0;                                                                   <*/
      a_ext = NULL;
   }
   /*---(general)------------------------*/
   ++a_src->WORK_FUNCS;
   /*---(recursive)----------------------*/
   if (a_src == a_dst) {
      DEBUG_INPT   yLOG_note    ("found a recursive reverence");
      ++a_src->WORK_RECURS;
      --a_src->WORK_FUNCS;
   }
   /*---(internal)-----------------------*/
   else if (a_dst != NULL) {
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
   else if (strchr ("Dd", a_ext->cat) != NULL) {
      DEBUG_INPT   yLOG_char    ("cat"       , a_ext->cat);
      ++a_src->WORK_DFUNCS;
      switch (a_ext->cat) {
      case 'd' :
         ++a_src->WORK_DSHORT;
         switch (a_ext->sub) {
         case 'e' :   ++a_src->WORK_DENTER;      break;
         case 'x' :   ++a_src->WORK_DEXIT;       break;
         }
         break;
      case 'D' :
         ++a_src->WORK_DLONG;
         switch (a_ext->sub) {
         case 'e' :   ++a_src->WORK_DENTER;      break;
         case 'x' :   ++a_src->WORK_DEXIT;       break;
         }
         break;
      }
   }
   /*---(standard library)---------------*/
   /*> else if (strchr ("owWirRmpfsTC", a_ext->sub) != NULL) {                        <*/
   else if (a_ext->cat == 'C') {
      ++a_src->WORK_CSTD;
      switch (a_ext->sub) {
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
      switch (a_ext->cat) {
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
   fprintf (my.f_mystry, "�## done, finito, complete�");
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
   else               sprintf (s, "�%c"  ,        a_suf);
   strlcat (a_out, s, LEN_RECD);
   return 0;
}

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_extern__unit       (char *a_question, int i)
{
   /*---(locals)-----------+-----+-----+-*/
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
   if        (strcmp (a_question, "file"      )     == 0) {
      snprintf (unit_answer, LEN_RECD, "EXTERN file      : %s", my.n_extern);
   }
   if (u != NULL) sprintf  (s, "[%.20s]", u->name);
   if        (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "EXTERN count     : %3d", poly_extern_count ());
   }
   else if   (strcmp (a_question, "entry"     )     == 0) {
      if (u != NULL)  sprintf  (r, "[%.20s]", u->lib);
      if (u != NULL)  sprintf  (t, "%2d%-22.22s   %2d%-22.22s   %4d   %c   %c   %c   %4d", strlen (u->lib), r, strlen (u->name), s, u->line, u->type, u->cat, u->sub, u->uses);
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
         snprintf (unit_answer, LEN_RECD, "EXTERN work (%2d) : %-22.22s   �e �g �l   �f �d �n �g �c �y �o �m   �r �w �s   �n �o �w �y", i, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
