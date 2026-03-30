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

/*> char                                                                              <* 
 *> poly_proto__purge  (void)                                                         <* 
 *> {                                                                                 <* 
 *>    int         i           =    0;                                                <* 
 *>    for (i = 0; i < MAX_PROTO; ++i) {                                              <* 
 *>       s_protos [i].scope    = '-';                                                <* 
 *>       s_protos [i].file     = 0;                                                  <* 
 *>       s_protos [i].line     = 0;                                                  <* 
 *>       s_protos [i].len      = 0;                                                  <* 
 *>       s_protos [i].name [0] = '\0';                                               <* 
 *>       s_protos [i].func     = NULL;                                               <* 
 *>    }                                                                              <* 
 *>    s_nproto  = 0;                                                                 <* 
 *>    s_nglobal = 0;                                                                 <* 
 *>    s_npriv   = 0;                                                                 <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

/*> char                                                                              <* 
 *> poly_proto_init         (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    /+---(initialize)---------------------+/                                       <* 
 *>    rc = ySORT_btree (B_PROTO, "prototypes");                                      <* 
 *>    DEBUG_PROG   yLOG_value   ("btree"     , rc);                                  <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    poly_proto__purge ();                                                          <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/



/*====================------------------------------------====================*/
/*===----                       data adding                            ----===*/
/*====================------------------------------------====================*/
static void  o___DATA____________o () { return; }

/*> char                                                                              <* 
 *> poly_proto_push         (tFILE *a_file, int a_line, char *a_name)                 <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    int         x_len       =    0;                                                <* 
 *>    char        x_type      =  '-';                                                <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    --rce;  if (s_nproto >= MAX_PROTO)  return rce;                                <* 
 *>    --rce;  if (a_file == NULL)         return rce;                                <* 
 *>    --rce;  if (a_name == NULL)         return rce;                                <* 
 *>    /+---(prepare)------------------------+/                                       <* 
 *>    x_len  = strlen (a_name);                                                      <* 
 *>    --rce;  if (x_len  <= 0)         return rce;                                   <* 
 *>    /+---(add entry)----------------------+/                                       <* 
 *>    x_type = a_file->i_type;                                                       <* 
 *>    if (x_type == 'h') {                                                           <* 
 *>       if (strstr (a_file->i_name, "_priv.h") == NULL) {                           <* 
 *>          s_protos [s_nproto].scope = 'g';                                         <* 
 *>          ++s_nglobal;                                                             <* 
 *>       } else  {                                                                   <* 
 *>          s_protos [s_nproto].scope = 'p';                                         <* 
 *>          ++s_npriv;                                                               <* 
 *>       }                                                                           <* 
 *>    }                                                                              <* 
 *>    else                 s_protos [s_nproto].scope = 'f';                          <* 
 *>    s_protos [s_nproto].file = a_file;                                             <* 
 *>    s_protos [s_nproto].line = a_line;                                             <* 
 *>    s_protos [s_nproto].len  = x_len;                                              <* 
 *>    ystrlcpy (s_protos [s_nproto].name, a_name, LEN_TITLE);                        <* 
 *>    /+---(update counters)----------------+/                                       <* 
 *>    ++s_nproto;                                                                    <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                                                  <* 
 *> poly_proto_hook         (tFILE *a_file, tFUNC *a_func, char *a_name)                                  <* 
 *> {                                                                                                     <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                           <* 
 *>    char        rce         =  -10;                                                                    <* 
 *>    int         i           =    0;                                                                    <* 
 *>    int         x_len       =    0;                                                                    <* 
 *>    int         c           =    0;                                                                    <* 
 *>    /+---(defense)------------------------+/                                                           <* 
 *>    --rce;  if (a_name == NULL) return rce;                                                            <* 
 *>    /+---(prepare)------------------------+/                                                           <* 
 *>    x_len  = strlen (a_name);                                                                          <* 
 *>    /+---(walk variables)-----------------+/                                                           <* 
 *>    for (i = 0; i < s_nproto; ++i) {                                                                   <* 
 *>       if (s_protos [i].len      != x_len)           continue;                                         <* 
 *>       if (s_protos [i].name [0] != a_name [0])      continue;                                         <* 
 *>       if (strcmp (s_protos [i].name, a_name) != 0)  continue;                                         <* 
 *>       if (strchr ("gp", s_protos [i].scope) != NULL) {                                                <* 
 *>          s_protos [i].func   = a_func;                                                                <* 
 *>          if (strchr ("-·", a_func->STATS_PROTO) != NULL)  a_func->STATS_PROTO = s_protos [i].scope;   <* 
 *>          else                                             a_func->STATS_PROTO = '#';                  <* 
 *>          ++c;                                                                                         <* 
 *>       }                                                                                               <* 
 *>       if (s_protos [i].file  == a_file) {                                                             <* 
 *>          s_protos [i].func   = a_func;                                                                <* 
 *>          if (strchr ("-·", a_func->STATS_PROTO) != NULL)  a_func->STATS_PROTO = s_protos [i].scope;   <* 
 *>          else                                             a_func->STATS_PROTO = '#';                  <* 
 *>          ++c;                                                                                         <* 
 *>       }                                                                                               <* 
 *>    }                                                                                                  <* 
 *>    /+---(complete)-----------------------+/                                                           <* 
 *>    return c;                                                                                          <* 
 *> }                                                                                                     <*/

/*> char                                                                                                                         <* 
 *> poly_proto_list     (void)                                                                                                   <* 
 *> {                                                                                                                            <* 
 *>    int         i           =    0;                                                                                           <* 
 *>    char        t           [LEN_TITLE] = "";                                                                                 <* 
 *>    if (my.g_mode == MODE_PROTO) {                                                                                            <* 
 *>       for (i = 0; i < s_nproto; ++i) {                                                                                       <* 
 *>          if (i % 25 == 0)  printf ("\nline  ---name-------------  line  ---file-------------  s  ---function---------\n");   <* 
 *>          if (i %  5 == 0)  printf ("\n");                                                                                    <* 
 *>          if ((s_protos [i].func)->c_name == NULL)  ystrlcpy (t, "", LEN_TITLE);                                              <* 
 *>          else sprintf (t, "%-20.20s", (s_protos [i].func)->c_name);                                                          <* 
 *>          printf ("%4d  %-20.20s  %4d  %-20.20s  %c  %-20.20s\n", i,                                                          <* 
 *>                s_protos [i].file->i_name, s_protos [i].line,                                                                 <* 
 *>                s_protos [i].name, s_protos [i].scope, t);                                                                    <* 
 *>       }                                                                                                                      <* 
 *>       --i;                                                                                                                   <* 
 *>       if (i % 25 != 0)  printf ("\nline  ---name-------------  line  ---file-------------  s  ---function---------\n");      <* 
 *>       printf ("\n");                                                                                                         <* 
 *>    }                                                                                                                         <* 
 *> }                                                                                                                            <*/

char
PROTO__handler          (tFILE *a_file, char a_name [LEN_TITLE], char a_type [LEN_TERSE], int a_line, char a_fname [LEN_TITLE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors         */
   int         rc          =    0;           /* generic return code            */
   tPROJ      *x_proj      = NULL;
   tFUNC      *x_func      = NULL;
   char        x_curr      =  '-';
   char        x_targ      =  '-';
   char        x_new       =  '-';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_info    ("i_name"    , a_file->i_name);
   DEBUG_INPT   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(find-project)-------------------*/
   x_proj = a_file->i_proj;
   DEBUG_INPT   yLOG_point   ("i_proj"    , x_proj);
   --rce;  if (x_proj == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_info    ("j_name"    , x_proj->j_name);
   /*---(find-function)------------------*/
   rc = FUNCS_in_proj_by_name (x_proj, a_name, &x_func);
   DEBUG_INPT   yLOG_point   ("x_func"    , x_func);
   --rce;  if (x_func == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_INPT   yLOG_info    ("c_name"    , x_func->c_name);
   /*---(update function)----------------*/
   x_curr = ySCORE_stats_value (my.s_yscore, "PROTO"   );
   DEBUG_INPT   yLOG_char    ("x_curr"    , x_curr);
   /*---(set target)---------------------*/
   if      (a_file->i_type == 'c') {
      DEBUG_INPT   yLOG_note    ("found in c-source file");
      x_targ = 'f';       /* source file    */
   } else if (a_file->i_type == 'h') {
      if (strstr (a_file->i_name, "_priv.h") == NULL) {
         DEBUG_INPT   yLOG_note    ("found in private header");
         x_targ = 'P';    /* public header  */
      } else {
         DEBUG_INPT   yLOG_note    ("found in public header");
         x_targ = 'v';    /* private header */
      }
   } else {
      DEBUG_INPT   yLOG_note    ("not a c/h file");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_INPT   yLOG_char    ("x_targ"    , x_targ);
   /*---(identify new value)-------------*/
   if      (x_curr == x_targ)  x_new = x_targ;
   else if (x_curr == '·')     x_new = x_targ;
   else if (x_curr == 'f')     x_new = x_targ;
   else if (x_curr == 'f')     x_new = x_targ;
   else if (x_curr == 'v') {
      if      (x_targ == 'P')  x_new = 'B';
      else                     x_new = x_curr;
   }
   else if (x_curr == 'P') {
      if      (x_targ == 'v')  x_new = 'B';
      else                     x_new = x_curr;
   }
   DEBUG_INPT   yLOG_char    ("x_new"     , x_new);
   /*---(set-value)----------------------*/
   rc = ySCORE_stats_set (my.s_yscore, "PROTO", x_new);
   DEBUG_INPT   yLOG_value   ("set"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}


char PROTO__from_file        (tPROJ *a_proj, tFILE *a_file, char a_ftype) {  return FILES_ctags (a_file, 'f', PROTO__handler); }

char PROTO_gather            (tPROJ *a_proj) { return FILES_run_for_project (a_proj, PROTO__from_file); }



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

/*> char*        /+-[ unit test accessor ]---------------------[us2---·A-7·6--·B21-]¬[----·T-B1H---·---·----]¬[---·------]+/                            <* 
 *> poly_proto__unit        (char *a_question, int i)                                                                                                   <* 
 *> {                                                                                                                                                   <* 
 *>    /+---(locals)-----------+-----------+-+/                                                                                                         <* 
 *>    char        s           [LEN_TITLE] = " 0[]";                                                                                                    <* 
 *>    char        t           [LEN_TITLE] = " 0[]";                                                                                                    <* 
 *>    char        u           [LEN_TITLE] = " 0[]";                                                                                                    <* 
 *>    /+---(defense)------------------------+/                                                                                                         <* 
 *>    snprintf (unit_answer, LEN_RECD, "VARS unit        : question unknown");                                                                         <* 
 *>    /+---(simple)-------------------------+/                                                                                                         <* 
 *>    if      (strcmp (a_question, "count"     )     == 0) {                                                                                           <* 
 *>       snprintf (unit_answer, LEN_RECD, "PROTO count      : %3da  %3dg  %3dp", s_nproto, s_nglobal, s_npriv);                                        <* 
 *>    }                                                                                                                                                <* 
 *>    else if (strcmp (a_question, "entry"     )     == 0) {                                                                                           <* 
 *>       sprintf (s, "%2d[%0.15s]", strlen (s_protos [i].name), s_protos [i].name);                                                                    <* 
 *>       if (s_protos [i].file != NULL)  sprintf (t, "%2d[%0.15s]", strlen (s_protos [i].file->i_name), s_protos [i].file->i_name);                    <* 
 *>       if (s_protos [i].func != NULL)  sprintf (u, "%2d[%0.15s]", strlen (s_protos [i].func->c_name), s_protos [i].func->c_name);                    <* 
 *>       snprintf (unit_answer, LEN_RECD, "PROTO entry (%2d) : %-19.19s  %4d  %-19.19s  %c  %s", i, s, s_protos [i].line, t, s_protos [i].scope, u);   <* 
 *>    }                                                                                                                                                <* 
 *>    /+---(complete)-----------------------+/                                                                                                         <* 
 *>    return unit_answer;                                                                                                                              <* 
 *> }                                                                                                                                                   <*/






