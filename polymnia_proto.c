/*============================----beg-of-source---============================*/
#include  "polymnia.h"



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
#define     MAX_PROTO   500
typedef     struct      cPROTO      tPROTO;
struct      cPROTO {
   char        scope;                       /* (g)lobal, (f)ile               */
   tFILE      *file;                        /* file pointer                   */
   int         line;                        /* line is source file            */
   char        len;                         /* name length                    */
   char        name        [LEN_TITLE];
   tFUNC      *func;                        /* back to actual function        */
};
static tPROTO      s_protos    [MAX_PROTO];
static int         s_nproto    =    0;
static int         s_nglobal   =    0;
static int         s_npriv     =    0;



/*====================------------------------------------====================*/
/*===----                     elemental manipulation                   ----===*/
/*====================------------------------------------====================*/
static void  o___ELEMENTAL_______o () { return; }

char
poly_proto__purge  (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_PROTO; ++i) {
      s_protos [i].scope    = '-';
      s_protos [i].file     = 0;
      s_protos [i].line     = 0;
      s_protos [i].len      = 0;
      s_protos [i].name [0] = '\0';
      s_protos [i].func     = NULL;
   }
   s_nproto  = 0;
   s_nglobal = 0;
   s_npriv   = 0;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
poly_proto_init         (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   poly_proto__purge ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       data adding                            ----===*/
/*====================------------------------------------====================*/
static void  o___DATA____________o () { return; }

char
poly_proto_push         (tFILE *a_file, int a_line, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   char        x_type      =  '-';
   /*---(defense)------------------------*/
   --rce;  if (s_nproto >= MAX_PROTO)  return rce;
   --rce;  if (a_file == NULL)         return rce;
   --rce;  if (a_name == NULL)         return rce;
   /*---(prepare)------------------------*/
   x_len  = strlen (a_name);
   --rce;  if (x_len  <= 0)         return rce;
   /*---(add entry)----------------------*/
   x_type = a_file->type;
   if (x_type == 'h') {
      if (strstr (a_file->name, "_priv.h") == NULL) {
         s_protos [s_nproto].scope = 'g';
         ++s_nglobal;
      } else  {
         s_protos [s_nproto].scope = 'p';
         ++s_npriv;
      }
   }
   else                 s_protos [s_nproto].scope = 'f';
   s_protos [s_nproto].file = a_file;
   s_protos [s_nproto].line = a_line;
   s_protos [s_nproto].len  = x_len;
   strlcpy (s_protos [s_nproto].name, a_name, LEN_TITLE);
   /*---(update counters)----------------*/
   ++s_nproto;
   /*---(complete)-----------------------*/
   return 0;
}

char
poly_proto_hook         (tFILE *a_file, tFUNC *a_func, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         x_len       =    0;
   int         c           =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL) return rce;
   /*---(prepare)------------------------*/
   x_len  = strlen (a_name);
   /*---(walk variables)-----------------*/
   for (i = 0; i < s_nproto; ++i) {
      if (s_protos [i].len      != x_len)           continue;
      if (s_protos [i].name [0] != a_name [0])      continue;
      if (strcmp (s_protos [i].name, a_name) != 0)  continue;
      if (strchr ("gp", s_protos [i].scope) != NULL) {
         s_protos [i].func   = a_func;
         if (a_func->STATS_PROTO == '-')  a_func->STATS_PROTO = s_protos [i].scope;
         else                             a_func->STATS_PROTO = '#';
         ++c;
      }
      if (s_protos [i].file  == a_file) {
         s_protos [i].func   = a_func;
         if (a_func->STATS_PROTO == '-')  a_func->STATS_PROTO = s_protos [i].scope;
         else                             a_func->STATS_PROTO = '#';
         ++c;
      }
   }
   /*---(complete)-----------------------*/
   return c;
}

char
poly_proto_list     (void)
{
   int         i           =    0;
   char        t           [LEN_TITLE] = "";
   if (my.g_mode == MODE_PROTO) {
      for (i = 0; i < s_nproto; ++i) {
         if (i % 25 == 0)  printf ("\nline  ---name-------------  line  ---file-------------  s  ---function---------\n");
         if (i %  5 == 0)  printf ("\n");
         if ((s_protos [i].func)->name == NULL)  strlcpy (t, "", LEN_TITLE);
         else sprintf (t, "%-20.20s", (s_protos [i].func)->name);
         printf ("%4d  %-20.20s  %4d  %-20.20s  %c  %-20.20s\n", i,
               s_protos [i].file->name, s_protos [i].line,
               s_protos [i].name, s_protos [i].scope, t);
      }
      --i;
      if (i % 25 != 0)  printf ("\nline  ---name-------------  line  ---file-------------  s  ---function---------\n");
      printf ("\n");
   }
}




/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-[ unit test accessor ]---------------------[us2---·A-7·6--·B21-]¬[----·T-B1H---·---·----]¬[---·------]*/
poly_proto__unit        (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        s           [LEN_TITLE] = " 0[]";
   char        t           [LEN_TITLE] = " 0[]";
   char        u           [LEN_TITLE] = " 0[]";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "VARS unit        : question unknown");
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "PROTO count      : %3da  %3dg  %3dp", s_nproto, s_nglobal, s_npriv);
   }
   else if (strcmp (a_question, "entry"     )     == 0) {
      sprintf (s, "%2d[%0.15s]", strlen (s_protos [i].name), s_protos [i].name);
      if (s_protos [i].file != NULL)  sprintf (t, "%2d[%0.15s]", strlen (s_protos [i].file->name), s_protos [i].file->name);
      if (s_protos [i].func != NULL)  sprintf (u, "%2d[%0.15s]", strlen (s_protos [i].func->name), s_protos [i].func->name);
      snprintf (unit_answer, LEN_RECD, "PROTO entry (%2d) : %-19.19s  %4d  %-19.19s  %c  %s", i, s, s_protos [i].line, t, s_protos [i].scope, u);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}






