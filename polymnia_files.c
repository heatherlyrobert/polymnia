/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_files_init         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = poly_btree_init (B_FILES);
   DEBUG_PROG   yLOG_value   ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_files_wrap         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(walk through list)--------------*/
   rc = poly_btree_purge (B_FILES);
   DEBUG_PROG   yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_files__wipe   (tFILE *a_dst)
{
   if (a_dst == NULL)  return -1;
   /*---(master)------------*/
   a_dst->type     = '-';
   /*---(stats)-------------*/
   a_dst->lines    = 0;
   a_dst->empty    = 0;
   a_dst->docs     = 0;
   a_dst->debug    = 0;
   a_dst->code     = 0;
   a_dst->slocl    = 0;
   /*---(tags)--------------*/
   a_dst->btag     = 0;
   a_dst->etag     = 0;
   a_dst->thead    = NULL;
   a_dst->ttail    = NULL;
   a_dst->ntag     = 0;
   /*---(tags)--------------*/
   return 0;
}

char
poly_files__add          (char *a_name, char a_type)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tFILE      *x_new       = NULL;
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
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tFILE *) malloc (sizeof (tFILE));
      if (x_tries > 10)   break;
   }
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   poly_files__wipe (x_new);
   x_new->name   = strdup (a_name);
   x_new->type   = a_type;
   /*---(into btree)---------------------*/
   rc = poly_btree_create (B_FILES, x_new, x_new->name);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> make a list of input files --------------------------------*/
poly_files_review  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;          /* generic return code            */
   char        rce         =  -10;          /* return code for errors         */
   DIR        *x_dir       = NULL;          /* directory pointer              */
   tDIRENT    *x_file      = NULL;          /* directory entry pointer        */
   char        x_name      [LEN_NAME];      /* file name                      */
   int         x_len       =    0;
   char        x_type      =  '-';
   int         x_read      =    0;          /* count of entries reviewed      */
   int         x_good      =    0;          /* count of entries processed     */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(purge existing)-----------------*/
   rc = poly_btree_purge (B_FILES);
   DEBUG_INPT   yLOG_point   ("purge"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(open dir)-----------------------*/
   x_dir = opendir(".");
   DEBUG_INPT   yLOG_point   ("x_dir"      , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_note    ("openned successfully");
   /*---(process entries)----------------*/
   DEBUG_INPT   yLOG_note    ("processing entries");
   while (1) {
      /*---(read a directory entry)------*/
      x_file = readdir (x_dir);
      DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
      ++x_read;
      /*---(filter by name)--------------*/
      strlcpy (x_name, x_file->d_name, LEN_NAME);
      DEBUG_INPT   yLOG_info    ("x_name"    , x_name);
      x_len = strlen (x_name);
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      if (x_name [0] == '.')  {
         DEBUG_INPT   yLOG_note    ("hidden, SKIP");
         continue;
      }
      /*---(cut too short)---------------*/
      if (x_len <  3)  {
         DEBUG_INPT   yLOG_note    ("name too short, SKIP");
         continue;
      }
      /*---(cut too long)----------------*/
      if (x_len > 50) {
         DEBUG_INPT   yLOG_note    ("crazy long name, SKIP");
         continue;
      }
      /*---(cut on suffix len)-----------*/
      DEBUG_INPT   yLOG_char    ("x_len - 2" , x_name [x_len - 2]);
      if (x_name [x_len - 2] != '.')  {
         DEBUG_INPT   yLOG_note    ("does not have a one-char suffix, SKIP");
         continue;
      }
      /*---(cut on suffix)---------------*/
      x_type = x_name [x_len - 1];
      DEBUG_INPT   yLOG_char    ("x_len - 1" , x_type);
      if (strchr ("ch", x_name [x_len - 1]) == NULL) {
         DEBUG_INPT   yLOG_note    ("not a c or h file, SKIP");
         continue;
      }
      /*---(filter unit test)*-----------*/
      if (x_len > 7 && strcmp ("_unit.c", x_name + x_len - 7) == 0) {
         DEBUG_INPT   yLOG_note    ("cut the unit testing code files, SKIP");
         continue;
      }
      /*---(save)------------------------*/
      poly_files__add (x_name, x_type);
      ++x_good;
      DEBUG_INPT   yLOG_note    ("added to inventory");
      /*---(done)------------------------*/
   }
   DEBUG_INPT   yLOG_value   ("x_read"    , x_read);
   DEBUG_INPT   yLOG_value   ("x_good"    , x_good);
   /*---(close dir)----------------------*/
   DEBUG_INPT   yLOG_note    ("closing directory");
   rc = closedir (x_dir);
   DEBUG_INPT   yLOG_value   ("close_rc"  , rc);
   /*> printf ("   end-of-files\n\n\n");                                              <*/
   /*---(check count)--------------------*/
   DEBUG_INPT   yLOG_value   ("count"     , poly_btree_count (B_FILES));
   --rce;  if (poly_btree_count (B_FILES) <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare for use)----------------*/
   rc = poly_btree_dgnome   (B_FILES);
   DEBUG_SORT   yLOG_value   ("dgnome"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_btree_build (B_FILES);
   DEBUG_SORT   yLOG_value   ("build"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> poly_extern_list ();                                                           <*/
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        searching                             ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

tFILE*  poly_files_search  (char *a_name) { return (tFILE *) poly_btree_search  (B_FILES, a_name); }
char    poly_files_list    (void)         { return poly_btree_list (B_FILES); }



/*====================------------------------------------====================*/
/*===----                         tag inventory                        ----===*/
/*====================------------------------------------====================*/
static void  o___TAGS____________o () { return; }

char
poly_files_addtag       (tFILE *a_file, tTAG *a_tag)
{
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_file);
   if (a_file == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   DEBUG_DATA   yLOG_spoint  (a_tag);
   if (a_tag == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, -1);
      return -1;
   }
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_spoint  (a_file->thead);
   DEBUG_DATA   yLOG_spoint  (a_file->ttail);
   if (a_file->thead == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      a_file->thead = a_file->ttail = a_tag;
   } else {
      DEBUG_DATA   yLOG_snote   ("append");
      a_tag->fprev         = a_file->ttail;
      a_file->ttail->fnext = a_tag;
      a_file->ttail        = a_tag;
   }
   /*---(update count)-------------------*/
   ++a_file->ntag;
   DEBUG_DATA   yLOG_sint    (a_file->ntag);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_files_nexttag      (tFILE *a_file, tTAG **a_tag)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_tag);
   --rce;  if (a_tag == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_tag);
   /*---(first time)---------------------*/
   --rce;  if (*a_tag == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      if (a_file->thead == NULL) {
         DEBUG_DATA   yLOG_snote   ("head is null");
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      *a_tag = a_file->thead;
   }
   /*---(next time)----------------------*/
   else { 
      DEBUG_DATA   yLOG_snote   ("next");
      if ((*a_tag)->fnext == NULL) {
         DEBUG_DATA   yLOG_snote   ("next is null");
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      *a_tag = (*a_tag)->fnext;
   }
   DEBUG_DATA   yLOG_spoint  (*a_tag);
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_files__unit     (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   tFILE      *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FILE unit        : file number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "FILE count       : %3d", poly_btree_count (B_FILES));
      return unit_answer;
   }
   if (strncmp (unit_answer, "FILE unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FILE unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "entry"     )     == 0) {
      u = (tFILE *) poly_btree_entry (B_FILES, i);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->name);
         snprintf (unit_answer, LEN_RECD, "FILE entry  (%2d) : %-22.22s %3d %3d %3d %3d %3d %3d", i, t, u->lines, u->empty, u->docs, u->debug, u->code, u->slocl);
      } else {
         snprintf (unit_answer, LEN_RECD, "FILE entry  (%2d) : %-22.22s %3d %3d %3d %3d %3d %3d", i, t, 0, 0, 0, 0, 0, 0);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


