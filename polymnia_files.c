/*============================----beg-of-source---============================*/
#include  "polymnia.h"



char      s_pprev     [LEN_RECD] = "";
char      s_prev      [LEN_RECD] = "";
char      s_curr      [LEN_RECD] = "";

tFILE     s_totals;



char
poly_files__wipe   (tFILE *a_dst)
{
   if (a_dst == NULL)  return -1;
   strlcpy (a_dst->name, "", LEN_RECD);
   a_dst->lines    = 0;
   a_dst->empty    = 0;
   a_dst->docs     = 0;
   a_dst->debug    = 0;
   a_dst->code     = 0;
   a_dst->slocl    = 0;
   return 0;
}

char
poly_files__copy  (tFILE *a_dst, tFILE *a_src)
{
   strlcpy (a_dst->name, a_src->name, LEN_RECD);
   a_dst->lines  = a_src->lines;
   a_dst->empty  = a_src->empty;
   a_dst->docs   = a_src->docs;
   a_dst->debug  = a_src->debug;
   a_dst->code   = a_src->code;
   a_dst->slocl  = a_src->slocl;
}

char
poly_files_init         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;          /* generic return code            */
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   for (i = 0; i < MAX_FILE; ++i)   poly_files__wipe (&s_files [i]);
   poly_files__wipe (&s_totals);
   s_nfile = 0;
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_files__gnome (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;          /* generic return code            */
   int         s           =    0;
   int         c           =    0;
   tFILE       x_tmp;
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(gnome)--------------------------*/
   while (i < s_nfile) {
      if (i <= 0) {
         DEBUG_SORT   yLOG_note    ("bounce off beginning");
         ++i;
         continue;
      }
      ++c;
      if (strcmp (s_files [i - 1].name, s_files [i].name) <=  0) {
         DEBUG_SORT   yLOG_complex ("correct"   , "%2d %-20.20s v %2d %-20.20s   %4d %4d", i, s_files [i].name, i - 1, s_files [i - 1].name, c, s);
         ++i;
         continue;
      }
      /*---(swap)------------------------*/
      ++s;
      poly_files__copy  (&x_tmp          , &s_files [i]    );
      poly_files__copy  (&s_files [i]    , &s_files [i - 1]);
      poly_files__copy  (&s_files [i - 1], &x_tmp         );
      DEBUG_SORT   yLOG_complex ("swapped"   , "%2d %-20.20s v %2d %-20.20s   %4d %4d", i, s_files [i].name, i - 1, s_files [i - 1].name, c, s);
      /*---(next)------------------------*/
      --i;
   }
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_files_add    (char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   char        x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   DEBUG_INPT   yLOG_sint    (s_nfile);
   /*---(name)---------------------------*/
   DEBUG_INPT   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   strlcpy (s_files [s_nfile].name, a_name  , LEN_RECD);
   /*---(type)---------------------------*/
   x_len = strlen (a_name);
   s_files [s_nfile].type = a_name [x_len - 1];
   /*---(update count)-------------------*/
   ++s_nfile;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
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
   char        x_name      [LEN_RECD];      /* file name                      */
   int         x_len       =    0;
   int         x_read      =    0;          /* count of entries reviewed      */
   int         x_good      =    0;          /* count of entries processed     */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open dir)-----------------------*/
   x_dir = opendir(".");
   DEBUG_INPT   yLOG_point   ("x_dir"      , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_note    ("openned successfully");
   /*---(prepare)------------------------*/
   s_nfile = 0;
   /*---(process entries)----------------*/
   DEBUG_INPT   yLOG_note    ("processing entries");
   /*> printf ("FILE INVENTORY...\n");                                                <*/
   while (1) {
      /*---(read a directory entry)------*/
      x_file = readdir (x_dir);
      DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
      ++x_read;
      /*---(filter by name)--------------*/
      strlcpy (x_name, x_file->d_name, LEN_RECD);
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
      DEBUG_INPT   yLOG_char    ("x_len - 1" , x_name [x_len - 1]);
      if (strchr ("ch", x_name [x_len - 1]) == NULL) {
         DEBUG_INPT   yLOG_note    ("not a c or h file, SKIP");
         continue;
      }
      /*---(filter unit test)*-----------*/
      if (x_len > 7 && strcmp ("_unit.c", x_name + x_len - 7) == 0) {
         DEBUG_INPT   yLOG_note    ("cut the unit testing code files, SKIP");
         continue;
      }
      /*---(record)----------------------*/
      poly_files_add (x_name);
      ++x_good;
      /*> printf ("   %3d %s\n", s_nfile, s_files [s_nfile].name);                    <*/
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
   DEBUG_INPT   yLOG_value   ("s_nfile"   , s_nfile);
   --rce;  if (s_nfile <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(sort files)---------------------*/
   poly_files__gnome ();
   /*---(build analysis files)------------------*/
   /*> system ("cflow -r -d 2 *.c 2> /dev/null > htags.gcalls");                      <*/
   system ("cflow -r -d 2 $(ls -1 *.c | grep -v unit) 2> /dev/null > htags.gcalls");
   system ("cflow -d 150 $(ls -1 *.c | grep -v unit) 2> /dev/null > htags.flow");
   /*---(complete)------------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_files__unit     (char *a_question, int n)
{
   /*---(locals)-----------+-----------+-*/
   int         len         = 0;
   char        t           [LEN_RECD];
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FILE unit        : file number unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "FILE count       : %3d", s_nfile);
      return unit_answer;
   }
   if (strncmp (unit_answer, "FILE unit        :", 18) != 0)  return unit_answer;
   /*---(defense)------------------------*/
   /*> if (n <  0)       return unit_answer;                                          <*/
   /*> if (n >= s_ntag)  return unit_answer;                                          <*/
   snprintf (unit_answer, LEN_RECD, "FILE unit        : question unknown");
   /*---(complex)------------------------*/
   if (strcmp (a_question, "entry"     )     == 0) {
      sprintf  (t, "[%.20s]", s_files [n].name);
      snprintf (unit_answer, LEN_RECD, "FILE entry  (%2d) : %-22.22s %3d %3d %3d %3d %3d %3d", n, t, s_files [n].lines, s_files [n].empty, s_files [n].docs, s_files [n].debug, s_files [n].code, s_files [n].slocl);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


