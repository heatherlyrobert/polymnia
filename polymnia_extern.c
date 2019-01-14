/*============================----beg-of-source---============================*/
#include  "polymnia.h"

/*----------+-----------+-----------+-----------+-----------+-----------+-----*/
static      tEXTERN    *s_head      = NULL;
static      tEXTERN    *s_tail      = NULL;
static      int         s_count     = 0;
static      tEXTERN    *s_root      = NULL;

int   g_depth   = 0;
char  g_path    [LEN_LABEL] = "";


/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
poly_extern__add         (char *a_name, char a_type)
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
   --rce;  if (x_len == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   /*---(create cell)--------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tEXTERN *) malloc (sizeof (tEXTERN));
      if (x_tries > 10)   break;
   }
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_DATA   yLOG_note    ("populate");
   x_new->name   = strdup (a_name);
   x_new->type   = a_type;
   x_new->count  = 0;
   /*---(into btree)---------------------*/
   rc = poly_btree_create (B_EXTERN, x_new, x_new->name);
   DEBUG_DATA   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
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
   rc = poly_btree_purge (B_EXTERN);
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
/*===----                        searching                             ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char      poly_extern_list        (void) { return poly_btree_list (B_EXTERN); }
tEXTERN*  poly_extern_search      (char *a_name) { return (tEXTERN *) poly_btree_search  (B_EXTERN, a_name); }



/*====================------------------------------------====================*/
/*===----                        mass actions                          ----===*/
/*====================------------------------------------====================*/
static void  o___MASS____________o () { return; }

char
poly_extern_load        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* generic return code            */
   FILE       *r           = NULL;          /* external functions file        */
   char        x_recd      [LEN_RECD];
   int         x_len       =    0;
   char        x_type      =  '-';
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(purge existing)-----------------*/
   rc = poly_btree_purge (B_EXTERN);
   /*---(open)---------------------------*/
   r = fopen (FILE_EXTERN, "rt");
   DEBUG_SORT   yLOG_point   ("r"          , r);
   --rce;  if (r == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(read)------------------------*/
      fgets (x_recd, LEN_RECD, r);
      if (feof (r)) {
         DEBUG_SORT   yLOG_note    ("end of file");
         break;
      }
      x_len = strlen (x_recd);
      DEBUG_SORT   yLOG_value   ("x_len"     , x_len);
      if (strlen >= 1)  x_recd [--x_len] = '\0';
      DEBUG_SORT   yLOG_value   ("x_len"     , x_len);
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      DEBUG_SORT   yLOG_info    ("x_recd"    , x_recd);
      x_len = strlen (x_recd);
      DEBUG_SORT   yLOG_value   ("x_len"     , x_len);
      DEBUG_SORT   yLOG_info    ("x_recd"    , x_recd);
      /*---(filter)----------------------*/
      if (x_len == 0) {
         DEBUG_SORT   yLOG_note    ("empty line, SKIP");
         continue;
      }
      if (strncmp (x_recd, "##", 2) == 0) {
         DEBUG_SORT   yLOG_note    ("header line, SKIP");
         continue;
      }
      if (x_recd [0] == '#') {
         DEBUG_SORT   yLOG_note    ("category line, SKIP");
         continue;
      }
      /*---(type)------------------------*/
      x_type = '-';
      if (x_len >= 20) {
         x_type = x_recd [19];
         x_recd [19] = '\0';
      }
      /*---(save)------------------------*/
      strltrim (x_recd, ySTR_BOTH, LEN_RECD);
      poly_extern__add (x_recd, x_type);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = fclose (r);
   DEBUG_SORT   yLOG_value   ("close"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check count)--------------------*/
   DEBUG_INPT   yLOG_value   ("s_nfile"   , poly_btree_count (B_EXTERN));
   --rce;  if (poly_btree_count (B_EXTERN) <= 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(prepare for use)----------------*/
   rc = poly_btree_dgnome   (B_EXTERN);
   DEBUG_SORT   yLOG_value   ("dgnome"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = poly_btree_build (B_EXTERN);
   DEBUG_SORT   yLOG_value   ("build"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> poly_extern_list ();                                                           <*/
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_extern_check       (char *a_name)
{
   /*> int         rce         =  -10;                                                <* 
    *> int         i           =    0;                                                <* 
    *> --rce;  if (a_name == NULL)  return rce;                                       <* 
    *> x_len = strlen (a_name);                                                       <* 
    *> --rce;  if (x_len == 0)      return rce;                                       <* 
    *> for (i = 0; i < s_nextern; ++i) {                                              <* 
    *>    if (s_externs [i].len != x_len)                continue;                    <* 
    *>    if (s_externs [i].name [0] != a_name [0])      continue;                    <* 
    *>    if (strcmp (s_externs [i].name, a_name) != 0)  continue;                    <* 
    *>    return s_externs [i].type;                                                  <* 
    *> }                                                                              <* 
    *> return ' ';                                                                    <*/
}

char
poly_extern_review      (int n)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                        <* 
    *> char        rce         =  -10;          /+ return code for errors         +/   <* 
    *> char        rc          =    0;          /+ generic return code            +/   <* 
    *> FILE       *r           = NULL;          /+ external functions file        +/   <* 
    *> char       *p           = NULL;                                                 <* 
    *> char        x_recd      [LEN_RECD];                                             <* 
    *> int         x_len       =    0;                                                 <* 
    *> int         c           =    0;                                                 <* 
    *> char        x_cat       =  ' ';                                                 <* 
    *> /+---(header)-------------------------+/                                        <* 
    *> DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                       <* 
    *> /+---(create file)--------------------+/                                        <* 
    *> rc = system ("cflow -d 2 htags.code > polymnia.calls");                         <* 
    *> DEBUG_SORT   yLOG_value   ("cflow"      , rc);                                  <* 
    *> /+---(open)---------------------------+/                                        <* 
    *> r = fopen ("polymnia.calls", "rt");                                             <* 
    *> DEBUG_SORT   yLOG_point   ("r"          , r);                                   <* 
    *> --rce;  if (r == NULL) {                                                        <* 
    *>    DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);                               <* 
    *>    return rce;                                                                  <* 
    *> }                                                                               <* 
    *> /+---(walk)---------------------------+/                                        <* 
    *> while (1) {                                                                     <* 
    *>    /+---(read)------------------------+/                                        <* 
    *>    fgets (x_recd, LEN_RECD, r);                                                 <* 
    *>    if (feof (r)) {                                                              <* 
    *>       DEBUG_SORT   yLOG_note    ("end of file");                                <* 
    *>       break;                                                                    <* 
    *>    }                                                                            <* 
    *>    if (x_recd [0] != ' ') {                                                     <* 
    *>       DEBUG_SORT   yLOG_note    ("header line, skipping");                      <* 
    *>       continue;                                                                 <* 
    *>    }                                                                            <* 
    *>    ++c;                                                                         <* 
    *>    x_len = strlen (x_recd);                                                     <* 
    *>    if (strlen >= 1)  x_recd [--x_len] = '\0';                                   <* 
    *>    strltrim (x_recd, ySTR_EVERY, LEN_RECD);                                     <* 
    *>    /+---(filter)----------------------+/                                        <* 
    *>    p = strchr (x_recd, '(');                                                    <* 
    *>    if (p == NULL) {                                                             <* 
    *>       DEBUG_SORT   yLOG_note    ("not a function call, SKIPPING");              <* 
    *>       continue;                                                                 <* 
    *>    }                                                                            <* 
    *>    *p = '\0';                                                                   <* 
    *>    x_len = strlen (x_recd);                                                     <* 
    *>    DEBUG_SORT   yLOG_value   ("x_len"     , x_len);                             <* 
    *>    DEBUG_SORT   yLOG_info    ("x_recd"    , x_recd);                            <* 
    *>    /+---(lookup)----------------------+/                                        <* 
    *>    x_cat = poly_extern_check (x_recd);                                          <* 
    *>    DEBUG_SORT   yLOG_value   ("x_cat"     , x_cat);                             <* 
    *>    if (x_cat <= 0) {                                                            <* 
    *>       DEBUG_SORT   yLOG_note    ("not an external function");                   <* 
    *>       continue;                                                                 <* 
    *>    }                                                                            <* 
    *>    /+---(categorize)------------------+/                                        <* 
    *>    DEBUG_SORT   yLOG_char    ("x_cat"     , x_cat);                             <* 
    *>    ++s_tags [n].funcs;                                                          <* 
    *>    switch (x_cat) {                                                             <* 
    *>    case '-' :                                                                   <* 
    *>       ++s_tags [n].cstd;                                                        <* 
    *>       break;                                                                    <* 
    *>    case 'W' :                                                                   <* 
    *>       ++s_tags [n].cstd;                                                        <* 
    *>       ++s_tags [n].writes;                                                      <* 
    *>       break;                                                                    <* 
    *>    case 'R' :                                                                   <* 
    *>       ++s_tags [n].cstd;                                                        <* 
    *>       ++s_tags [n].reads;                                                       <* 
    *>       break;                                                                    <* 
    *>    case 'N' :                                                                   <* 
    *>       ++s_tags [n].ncurses;                                                     <* 
   *>       break;                                                                    <* 
      *>    case 'O' :                                                                   <* 
      *>       ++s_tags [n].opengl;                                                      <* 
      *>       break;                                                                    <* 
      *>    case 'Y' :                                                                   <* 
      *>       ++s_tags [n].ylibs;                                                       <* 
      *>       break;                                                                    <* 
      *>    case 'M' :                                                                   <* 
      *>       ++s_tags [n].cstd;                                                        <* 
      *>       ++s_tags [n].memories;                                                    <* 
      *>       break;                                                                    <* 
      *>    case 'P' :                                                                   <* 
      *>       ++s_tags [n].cstd;                                                        <* 
      *>       ++s_tags [n].process;                                                     <* 
      *>       break;                                                                    <* 
      *>    case 'S' :                                                                   <* 
      *>       ++s_tags [n].cstd;                                                        <* 
      *>       ++s_tags [n].scalls;                                                      <* 
      *>       break;                                                                    <* 
      *>    }                                                                            <* 
      *>    /+---(done)------------------------+/                                        <* 
      *> }                                                                               <* 
      *> /+---(close)--------------------------+/                                        <* 
      *> rc = fclose (r);                                                                <* 
      *> DEBUG_SORT   yLOG_value   ("close"      , rc);                                  <* 
      *> --rce;  if (rc < 0) {                                                           <* 
         *>    DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);                               <* 
            *>    return rce;                                                                  <* 
            *> }                                                                               <* 
            *> /+---(complete)-----------------------+/                                        <* 
            *> DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                       <* 
            *> return 0;                                                                       <*/
}


/*> char                                                                              <* 
 *> poly_extern__copy       (tEXTERN *a_dst, tEXTERN *a_src)                          <* 
 *> {                                                                                 <* 
 *>    strlcpy (a_dst->name, a_src->name, LEN_NAME);                                  <* 
 *>    a_dst->len    = a_src->len;                                                    <* 
 *>    a_dst->type   = a_src->type;                                                   <* 
 *>    a_dst->count  = a_src->count;                                                  <* 
 *>    a_dst->pos    = a_src->pos;                                                    <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                                                                                                      <* 
 *> poly_extern__gnome_BASE      (void)                                                                                                                       <* 
 *> {                                                                                                                                                         <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                               <* 
 *>    int         i           =    0;          /+ current index                  +/                                                                          <* 
 *>    int         c           =    0;          /+ comparisons                    +/                                                                          <* 
 *>    int         s           =    0;          /+ swaps                          +/                                                                          <* 
 *>    tEXTERN     x_tmp;                                                                                                                                     <* 
 *>    /+---(header)-------------------------+/                                                                                                               <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                                                                              <* 
 *>    /+---(gnome)--------------------------+/                                                                                                               <* 
 *>    while (i < s_nextern) {                                                                                                                                <* 
 *>       /+---(beginning)-------------------+/                                                                                                               <* 
 *>       if (i <= 0) {                                                                                                                                       <* 
 *>          DEBUG_SORT   yLOG_note    ("bounce off beginning");                                                                                              <* 
 *>          ++i;                                                                                                                                             <* 
 *>          continue;                                                                                                                                        <* 
 *>       }                                                                                                                                                   <* 
 *>       /+---(compare)---------------------+/                                                                                                               <* 
 *>       ++c;                                                                                                                                                <* 
 *>       if (strcmp (s_externs [i - 1].name, s_externs [i].name) <= 0) {                                                                                     <* 
 *>          DEBUG_SORT   yLOG_complex ("correct"   , "%2d %-20.20s v %2d %-20.20s   %4d %4d", i - 1, s_externs [i - 1].name, i, s_externs [i].name, c, s);   <* 
 *>          ++i;                                                                                                                                             <* 
 *>          continue;                                                                                                                                        <* 
 *>       }                                                                                                                                                   <* 
 *>       /+---(swap)------------------------+/                                                                                                               <* 
 *>       ++s;                                                                                                                                                <* 
 *>       poly_extern__copy (&x_tmp            , &s_externs [i]    );                                                                                         <* 
 *>       poly_extern__copy (&s_externs [i]    , &s_externs [i - 1]);                                                                                         <* 
 *>       poly_extern__copy (&s_externs [i - 1], &x_tmp           );                                                                                          <* 
 *>       DEBUG_SORT   yLOG_complex ("swapped"   , "%2d %-20.20s # %2d %-20.20s   %4d %4d", i - 1, s_externs [i - 1].name, i, s_externs [i].name, c, s);      <* 
 *>       /+---(next)------------------------+/                                                                                                               <* 
 *>       --i;                                                                                                                                                <* 
 *>    }                                                                                                                                                      <* 
 *>    DEBUG_SORT   yLOG_value   ("size"       , s_nextern);                                                                                                  <* 
 *>    DEBUG_SORT   yLOG_value   ("compares"   , c);                                                                                                          <* 
 *>    DEBUG_SORT   yLOG_value   ("swaps"      , s);                                                                                                          <* 
 *>    /+---(complete)-----------------------+/                                                                                                               <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                                                                              <* 
 *>    return 0;                                                                                                                                              <* 
 *> }                                                                                                                                                         <*/

/*> char                                                                                                                                                      <* 
 *> poly_extern__gnome_TELE      (void)                                                                                                                       <* 
 *> {                                                                                                                                                         <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                               <* 
 *>    int         i           =    0;          /+ current index                  +/                                                                          <* 
 *>    int         c           =    0;          /+ comparisons                    +/                                                                          <* 
 *>    int         s           =    0;          /+ swaps                          +/                                                                          <* 
 *>    int         t           =    0;          /+ teleport index                 +/                                                                          <* 
 *>    tEXTERN     x_tmp;                                                                                                                                     <* 
 *>    /+---(header)-------------------------+/                                                                                                               <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                                                                              <* 
 *>    /+---(gnome)--------------------------+/                                                                                                               <* 
 *>    while (i < s_nextern) {                                                                                                                                <* 
 *>       if (i > t)  t = i;                                                                                                                                  <* 
 *>       /+---(beginning)-------------------+/                                                                                                               <* 
 *>       if (i <= 0) {                                                                                                                                       <* 
 *>          DEBUG_SORT   yLOG_note    ("bounce off beginning");                                                                                              <* 
 *>          ++i;                                                                                                                                             <* 
 *>          continue;                                                                                                                                        <* 
 *>       }                                                                                                                                                   <* 
 *>       /+---(compare)---------------------+/                                                                                                               <* 
 *>       ++c;                                                                                                                                                <* 
 *>       if (strcmp (s_externs [i - 1].name, s_externs [i].name) <= 0) {                                                                                     <* 
 *>          DEBUG_SORT   yLOG_complex ("correct"   , "%2d %-20.20s v %2d %-20.20s   %4d %4d", i - 1, s_externs [i - 1].name, i, s_externs [i].name, c, s);   <* 
 *>          i = t + 1;                                                                                                                                       <* 
 *>          continue;                                                                                                                                        <* 
 *>       }                                                                                                                                                   <* 
 *>       /+---(swap)------------------------+/                                                                                                               <* 
 *>       ++s;                                                                                                                                                <* 
 *>       poly_extern__copy (&x_tmp            , &s_externs [i]    );                                                                                         <* 
 *>       poly_extern__copy (&s_externs [i]    , &s_externs [i - 1]);                                                                                         <* 
 *>       poly_extern__copy (&s_externs [i - 1], &x_tmp           );                                                                                          <* 
 *>       DEBUG_SORT   yLOG_complex ("swapped"   , "%2d %-20.20s # %2d %-20.20s   %4d %4d", i - 1, s_externs [i - 1].name, i, s_externs [i].name, c, s);      <* 
 *>       /+---(next)------------------------+/                                                                                                               <* 
 *>       --i;                                                                                                                                                <* 
 *>    }                                                                                                                                                      <* 
 *>    DEBUG_SORT   yLOG_value   ("size"       , s_nextern);                                                                                                  <* 
 *>    DEBUG_SORT   yLOG_value   ("compares"   , c);                                                                                                          <* 
 *>    DEBUG_SORT   yLOG_value   ("swaps"      , s);                                                                                                          <* 
 *>    /+---(complete)-----------------------+/                                                                                                               <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                                                                              <* 
 *>    return 0;                                                                                                                                              <* 
 *> }                                                                                                                                                         <*/

/*> static  tEXTERN      s_head;                                                      <* 
 *> static  int          s_headnum;                                                   <* 
 *> static  tEXTERN      s_saved;                                                     <* 
 *> static  int          s_start;                                                     <* 
 *> static int           s_next;                                                      <* 
 *> static int           s_hole;                                                      <*/


/*> int                                                                               <* 
 *> poly_extern__move_SALTS (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_SORT   yLOG_senter  (__FUNCTION__);                                      <* 
 *>    DEBUG_SORT   yLOG_snote   ("hole");                                            <* 
 *>    DEBUG_SORT   yLOG_sint    (s_hole);                                            <* 
 *>    DEBUG_SORT   yLOG_snote   (s_externs [s_hole].name);                           <* 
 *>    DEBUG_SORT   yLOG_snote   ("next");                                            <* 
 *>    DEBUG_SORT   yLOG_sint    (s_next);                                            <* 
 *>    DEBUG_SORT   yLOG_snote   (s_externs [s_next].name);                           <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    if (s_hole == s_next) {                                                        <* 
 *>       DEBUG_SORT   yLOG_snote   ("no move required");                             <* 
 *>       DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, -1);                               <* 
 *>       return -1;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(move from original)-------------+/                                       <* 
 *>    poly_extern__copy (&s_externs [s_hole], &s_externs [s_next]);                  <* 
 *>    s_externs [s_next].name [0] = '\0';                                            <* 
 *>    s_alts [s_hole] = -1;                                                          <* 
 *>    DEBUG_SORT   yLOG_snote   ("moved");                                           <* 
 *>    ++s_swaps;                                                                     <* 
 *>    /+---(save next index)----------------+/                                       <* 
 *>    s_hole = s_next;                                                               <* 
 *>    DEBUG_SORT   yLOG_sint    (s_hole);                                            <* 
 *>    s_next = s_alts [s_next];                                                      <* 
 *>    DEBUG_SORT   yLOG_sint    (s_next);                                            <* 
 *>    if (s_hole == s_next) {                                                        <* 
 *>       DEBUG_SORT   yLOG_snote   ("end of chain");                                 <* 
 *>       DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, -2);                               <* 
 *>       return -2;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_SORT   yLOG_sexit   (__FUNCTION__);                                      <* 
 *>    return 1;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                                                       <* 
 *> poly_extern__reorder_SALTS    (void)                                                                       <* 
 *> {                                                                                                          <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                <* 
 *>    char        rc          =    0;                                                                         <* 
 *>    int         i           =    0;          /+ current index                  +/                           <* 
 *>    int         c           =    0;                                                                         <* 
 *>    /+---(header)-------------------------+/                                                                <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                               <* 
 *>    /+---(walk list)----------------------+/                                                                <* 
 *>    for (i = 0; i < s_nextern; ++i) {                                                                       <* 
 *>       /+---(header)----------------------+/                                                                <* 
 *>       DEBUG_SORT   yLOG_value   ("ROUND"     , i);                                                         <* 
 *>       DEBUG_SORT   yLOG_complex ("check"     , "%3d  %3d  %-20.20s", i, s_alts [i], s_externs [i].name);   <* 
 *>       /+---(filter)----------------------+/                                                                <* 
 *>       if (s_alts [i] < 0) {                                                                                <* 
 *>          DEBUG_SORT   yLOG_note    ("already in the right order");                                         <* 
 *>          continue;                                                                                         <* 
 *>       }                                                                                                    <* 
 *>       /+---(save starting)---------------+/                                                                <* 
 *>       c = 0;                                                                                               <* 
 *>       s_hole  = SAVE;                                                                                      <* 
 *>       s_start = s_next  = i;                                                                               <* 
 *>       rc      = 0;                                                                                         <* 
 *>       while (rc >= 0) {                                                                                    <* 
 *>          rc = poly_extern__move ();                                                                        <* 
 *>          ++c;                                                                                              <* 
 *>          if (s_next == s_start)  break;                                                                    <* 
 *>       }                                                                                                    <* 
 *>       s_next  = SAVE;                                                                                      <* 
 *>       rc = poly_extern__move ();                                                                           <* 
 *>       ++c;                                                                                                 <* 
 *>       DEBUG_SORT   yLOG_value   ("chain len" , c);                                                         <* 
 *>    }                                                                                                       <* 
 *>    /+---(complete)-----------------------+/                                                                <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                               <* 
 *>    return 0;                                                                                               <* 
 *> }                                                                                                          <*/

/*> char                                                                                                                                                                                                                                     <* 
 *> poly_extern__gnome_SALTS      (void)                                                                                                                                                                                                     <* 
 *> {                                                                                                                                                                                                                                        <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                                                                                                              <* 
 *>    char        rc          =    0;                                                                                                                                                                                                       <* 
 *>    int         i           =    0;          /+ current index                  +/                                                                                                                                                         <* 
 *>    int         t           =    0;          /+ teleport index                 +/                                                                                                                                                         <* 
 *>    int         x_tmp;                                                                                                                                                                                                                    <* 
 *>    /+---(header)-------------------------+/                                                                                                                                                                                              <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                                                                                                                                                             <* 
 *>    /+---(display)------------------------+/                                                                                                                                                                                              <* 
 *>    /+> printf ("BEFORE...\n");                                                                   <*                                                                                                                                      <* 
 *>     *> for (i = 0; i < s_nextern; ++i) {                                                         <*                                                                                                                                      <* 
 *>     *>    printf ("%3d %2d:%s\n", i, s_externs [s_alts [i]].len, s_externs [s_alts [i]].name);   <*                                                                                                                                      <* 
 *>     *> }                                                                                         <+/                                                                                                                                     <* 
 *>    /+---(gnome)--------------------------+/                                                                                                                                                                                              <* 
 *>    i = 0;                                                                                                                                                                                                                                <* 
 *>    while (i < s_nextern) {                                                                                                                                                                                                               <* 
 *>       if (i > t)  t = i;                                                                                                                                                                                                                 <* 
 *>       /+---(beginning)-------------------+/                                                                                                                                                                                              <* 
 *>       if (i <= 0) {                                                                                                                                                                                                                      <* 
 *>          DEBUG_SORT   yLOG_note    ("bounce off beginning");                                                                                                                                                                             <* 
 *>          ++s_teles;                                                                                                                                                                                                                      <* 
 *>          i = t + 1;                                                                                                                                                                                                                      <* 
 *>          continue;                                                                                                                                                                                                                       <* 
 *>       }                                                                                                                                                                                                                                  <* 
 *>       /+---(compare)---------------------+/                                                                                                                                                                                              <* 
 *>       ++s_comps;                                                                                                                                                                                                                         <* 
 *>       rc = strcmp (s_externs [s_alts[i - 1]].name, s_externs [s_alts [i]].name);                                                                                                                                                         <* 
 *>       if (rc <= 0) {                                                                                                                                                                                                                     <* 
 *>          DEBUG_SORT   yLOG_complex ("correct"   , "%3d %-20.20s v %3d %-20.20s   %c %4d   %5d %5d %5d", i - 1, s_externs [s_alts [i - 1]].name, i, s_externs [s_alts [i]].name, (rc <= 0) ? 'y' : '-', rc, s_comps, s_swaps, s_teles);   <* 
 *>          ++s_teles;                                                                                                                                                                                                                      <* 
 *>          i = t + 1;                                                                                                                                                                                                                      <* 
 *>          continue;                                                                                                                                                                                                                       <* 
 *>       }                                                                                                                                                                                                                                  <* 
 *>       /+---(swap)------------------------+/                                                                                                                                                                                              <* 
 *>       ++s_notes;                                                                                                                                                                                                                         <* 
 *>       DEBUG_SORT   yLOG_complex ("swapped"   , "%3d %-20.20s # %3d %-20.20s   %c %4d   %5d %5d %5d", i - 1, s_externs [s_alts [i - 1]].name, i, s_externs [s_alts [i]].name, (rc <= 0) ? 'y' : '-', rc, s_comps, s_swaps, s_teles);      <* 
 *>       x_tmp          = s_alts [i];                                                                                                                                                                                                       <* 
 *>       s_alts [i]     = s_alts [i - 1];                                                                                                                                                                                                   <* 
 *>       s_alts [i - 1] = x_tmp;                                                                                                                                                                                                            <* 
 *>       /+---(next)------------------------+/                                                                                                                                                                                              <* 
 *>       --i;                                                                                                                                                                                                                               <* 
 *>    }                                                                                                                                                                                                                                     <* 
 *>    /+---(display)------------------------+/                                                                                                                                                                                              <* 
 *>    /+> printf ("AFTER...\n");                                                                    <*                                                                                                                                      <* 
 *>     *> for (i = 0; i < s_nextern; ++i) {                                                         <*                                                                                                                                      <* 
 *>     *>    printf ("%3d %2d:%s\n", i, s_externs [s_alts [i]].len, s_externs [s_alts [i]].name);   <*                                                                                                                                      <* 
 *>     *> }                                                                                         <*                                                                                                                                      <* 
 *>     *> printf ("BEFORE reorder...\n");                                                           <*                                                                                                                                      <* 
 *>     *> for (i = 0; i < s_nextern; ++i) {                                                         <*                                                                                                                                      <* 
 *>     *>    printf ("%3d %3d %2d:%s\n", i, s_alts [i], s_externs [i].len, s_externs [i].name);     <*                                                                                                                                      <* 
 *>     *> }                                                                                         <+/                                                                                                                                     <* 
 *>    poly_extern__reorder_SALTS ();                                                                                                                                                                                                        <* 
 *>    printf ("AFTER reorder...\n");                                                                                                                                                                                                        <* 
 *>    for (i = 0; i < s_nextern; ++i) {                                                                                                                                                                                                     <* 
 *>       printf ("%3d %3d %2d:%s\n", i, s_alts [i], s_externs [i].len, s_externs [i].name);                                                                                                                                                 <* 
 *>    }                                                                                                                                                                                                                                     <* 
 *>    DEBUG_SORT   yLOG_value   ("size"       , s_nextern);                                                                                                                                                                                 <* 
 *>    DEBUG_SORT   yLOG_value   ("compares"   , s_comps);                                                                                                                                                                                   <* 
 *>    DEBUG_SORT   yLOG_value   ("notes"      , s_notes);                                                                                                                                                                                   <* 
 *>    DEBUG_SORT   yLOG_value   ("swaps"      , s_swaps);                                                                                                                                                                                   <* 
 *>    DEBUG_SORT   yLOG_value   ("teleports"  , s_teles);                                                                                                                                                                                   <* 
 *>    /+---(complete)-----------------------+/                                                                                                                                                                                              <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                                                                                                                                                             <* 
 *>    return 0;                                                                                                                                                                                                                             <* 
 *> }                                                                                                                                                                                                                                        <*/


/*> int                                                                               <* 
 *> poly_extern__move_INDEX (void)                                                    <* 
 *> {                                                                                 <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_SORT   yLOG_senter  (__FUNCTION__);                                      <* 
 *>    DEBUG_SORT   yLOG_snote   ("hole");                                            <* 
 *>    DEBUG_SORT   yLOG_sint    (s_hole);                                            <* 
 *>    DEBUG_SORT   yLOG_snote   (s_externs [s_hole].name);                           <* 
 *>    DEBUG_SORT   yLOG_snote   ("next");                                            <* 
 *>    DEBUG_SORT   yLOG_sint    (s_next);                                            <* 
 *>    DEBUG_SORT   yLOG_snote   (s_externs [s_next].name);                           <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    if (s_hole == s_next) {                                                        <* 
 *>       DEBUG_SORT   yLOG_snote   ("no move required");                             <* 
 *>       DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, -1);                               <* 
 *>       return -1;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(move from original)-------------+/                                       <* 
 *>    poly_extern__copy (&s_externs [s_hole], &s_externs [s_next]);                  <* 
 *>    s_externs [s_next].name [0] = '\0';                                            <* 
 *>    s_externs [s_hole].pos = -1;                                                   <* 
 *>    DEBUG_SORT   yLOG_snote   ("moved");                                           <* 
 *>    ++s_swaps;                                                                     <* 
 *>    /+---(save next index)----------------+/                                       <* 
 *>    s_hole = s_next;                                                               <* 
 *>    DEBUG_SORT   yLOG_sint    (s_hole);                                            <* 
 *>    s_next = s_externs [s_next].pos;                                               <* 
 *>    DEBUG_SORT   yLOG_sint    (s_next);                                            <* 
 *>    if (s_hole == s_next) {                                                        <* 
 *>       DEBUG_SORT   yLOG_snote   ("end of chain");                                 <* 
 *>       DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, -2);                               <* 
 *>       return -2;                                                                  <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_SORT   yLOG_sexit   (__FUNCTION__);                                      <* 
 *>    return 1;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                                                              <* 
 *> poly_extern__reorder_INDEX (void)                                                                                 <* 
 *> {                                                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                       <* 
 *>    char        rc          =    0;                                                                                <* 
 *>    int         i           =    0;          /+ current index                  +/                                  <* 
 *>    int         c           =    0;                                                                                <* 
 *>    /+---(header)-------------------------+/                                                                       <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                                      <* 
 *>    /+---(walk list)----------------------+/                                                                       <* 
 *>    for (i = 0; i < s_nextern; ++i) {                                                                              <* 
 *>       /+---(header)----------------------+/                                                                       <* 
 *>       DEBUG_SORT   yLOG_value   ("ROUND"     , i);                                                                <* 
 *>       DEBUG_SORT   yLOG_complex ("check"     , "%3d  %3d  %-20.20s", i, s_externs [i].pos, s_externs [i].name);   <* 
 *>       /+---(filter)----------------------+/                                                                       <* 
 *>       if (s_externs [i].pos < 0) {                                                                                <* 
 *>          DEBUG_SORT   yLOG_note    ("already in the right order");                                                <* 
 *>          continue;                                                                                                <* 
 *>       }                                                                                                           <* 
 *>       /+---(save starting)---------------+/                                                                       <* 
 *>       c = 0;                                                                                                      <* 
 *>       s_hole  = SAVE;                                                                                             <* 
 *>       s_start = s_next  = i;                                                                                      <* 
 *>       rc      = 0;                                                                                                <* 
 *>       while (rc >= 0) {                                                                                           <* 
 *>          rc = poly_extern__move ();                                                                               <* 
 *>          ++c;                                                                                                     <* 
 *>          if (s_next == s_start)  break;                                                                           <* 
 *>       }                                                                                                           <* 
 *>       s_next  = SAVE;                                                                                             <* 
 *>       rc = poly_extern__move ();                                                                                  <* 
 *>       ++c;                                                                                                        <* 
 *>       DEBUG_SORT   yLOG_value   ("chain len" , c);                                                                <* 
 *>    }                                                                                                              <* 
 *>    /+---(complete)-----------------------+/                                                                       <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                                      <* 
 *>    return 0;                                                                                                      <* 
 *> }                                                                                                                 <*/

/*> char                                                                                                                                                                                                                                                   <* 
 *> poly_extern__gnome_INDEX(void)                                                                                                                                                                                                                         <* 
 *> {                                                                                                                                                                                                                                                      <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                                                                                                                            <* 
 *>    char        rc          =    0;                                                                                                                                                                                                                     <* 
 *>    int         i           =    0;          /+ current index                  +/                                                                                                                                                                       <* 
 *>    int         t           =    0;          /+ teleport index                 +/                                                                                                                                                                       <* 
 *>    int         x_tmp;                                                                                                                                                                                                                                  <* 
 *>    /+---(header)-------------------------+/                                                                                                                                                                                                            <* 
 *>    DEBUG_SORT   yLOG_enter   (__FUNCTION__);                                                                                                                                                                                                           <* 
 *>    /+---(gnome)--------------------------+/                                                                                                                                                                                                            <* 
 *>    i = 0;                                                                                                                                                                                                                                              <* 
 *>    while (i < s_nextern) {                                                                                                                                                                                                                             <* 
 *>       if (i > t)  t = i;                                                                                                                                                                                                                               <* 
 *>       /+---(beginning)-------------------+/                                                                                                                                                                                                            <* 
 *>       if (i <= 0) {                                                                                                                                                                                                                                    <* 
 *>          DEBUG_SORT   yLOG_note    ("bounce off beginning");                                                                                                                                                                                           <* 
 *>          ++s_teles;                                                                                                                                                                                                                                    <* 
 *>          i = t + 1;                                                                                                                                                                                                                                    <* 
 *>          continue;                                                                                                                                                                                                                                     <* 
 *>       }                                                                                                                                                                                                                                                <* 
 *>       /+---(compare)---------------------+/                                                                                                                                                                                                            <* 
 *>       ++s_comps;                                                                                                                                                                                                                                       <* 
 *>       rc = strcmp (s_externs [s_externs [i - 1].pos].name, s_externs [s_externs [i].pos].name);                                                                                                                                                        <* 
 *>       if (rc <= 0) {                                                                                                                                                                                                                                   <* 
 *>          DEBUG_SORT   yLOG_complex ("correct"   , "%3d %-20.20s v %3d %-20.20s   %c %4d   %5d %5d %5d", i - 1, s_externs [s_externs [i - 1].pos].name, i, s_externs [s_externs [i].pos].name, (rc <= 0) ? 'y' : '-', rc, s_comps, s_swaps, s_teles);   <* 
 *>          ++s_teles;                                                                                                                                                                                                                                    <* 
 *>          i = t + 1;                                                                                                                                                                                                                                    <* 
 *>          continue;                                                                                                                                                                                                                                     <* 
 *>       }                                                                                                                                                                                                                                                <* 
 *>       /+---(swap)------------------------+/                                                                                                                                                                                                            <* 
 *>       ++s_notes;                                                                                                                                                                                                                                       <* 
 *>       DEBUG_SORT   yLOG_complex ("swapped"   , "%3d %-20.20s # %3d %-20.20s   %c %4d   %5d %5d %5d", i - 1, s_externs [s_externs [i - 1].pos].name, i, s_externs [s_externs [i].pos].name, (rc <= 0) ? 'y' : '-', rc, s_comps, s_swaps, s_teles);      <* 
 *>       x_tmp                 = s_externs [i].pos;                                                                                                                                                                                                       <* 
 *>       s_externs [i].pos     = s_externs [i - 1].pos;                                                                                                                                                                                                   <* 
 *>       s_externs [i - 1].pos = x_tmp;                                                                                                                                                                                                                   <* 
 *>       /+---(next)------------------------+/                                                                                                                                                                                                            <* 
 *>       --i;                                                                                                                                                                                                                                             <* 
 *>    }                                                                                                                                                                                                                                                   <* 
 *>    /+---(display)------------------------+/                                                                                                                                                                                                            <* 
 *>    poly_extern__reorder ();                                                                                                                                                                                                                            <* 
 *>    printf ("AFTER reorder...\n");                                                                                                                                                                                                                      <* 
 *>    for (i = 0; i < s_nextern; ++i) {                                                                                                                                                                                                                   <* 
 *>       printf ("%3d %2d:%s\n", i, s_externs [i].len, s_externs [i].name);                                                                                                                                                                               <* 
 *>    }                                                                                                                                                                                                                                                   <* 
 *>    DEBUG_SORT   yLOG_value   ("size"       , s_nextern);                                                                                                                                                                                               <* 
 *>    DEBUG_SORT   yLOG_value   ("compares"   , s_comps);                                                                                                                                                                                                 <* 
 *>    DEBUG_SORT   yLOG_value   ("notes"      , s_notes);                                                                                                                                                                                                 <* 
 *>    DEBUG_SORT   yLOG_value   ("swaps"      , s_swaps);                                                                                                                                                                                                 <* 
 *>    DEBUG_SORT   yLOG_value   ("teleports"  , s_teles);                                                                                                                                                                                                 <* 
 *>    /+---(complete)-----------------------+/                                                                                                                                                                                                            <* 
 *>    DEBUG_SORT   yLOG_exit    (__FUNCTION__);                                                                                                                                                                                                           <* 
 *>    return 0;                                                                                                                                                                                                                                           <* 
 *> }                                                                                                                                                                                                                                                      <*/




/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_extern__unit       (char *a_question, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   tEXTERN    *u           = NULL;
   int         c           =    0;
   char        s           [LEN_RECD]  = "[]";
   char        t           [LEN_RECD]  = "";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "EXTERN unit      : tag number unknown");
   if (n <  0)       return unit_answer;
   u = s_head;
   while (c < n) {
      if (u == NULL)  break;
      u = u->next;
      ++c;
   }
   /*---(simple)-------------------------*/
   if (u != NULL) sprintf  (s, "[%.20s]", u->name);
   if        (strcmp (a_question, "count"     )     == 0) {
      snprintf (unit_answer, LEN_RECD, "EXTERN count     : %3d", s_count);
   }
   else if   (strcmp (a_question, "entry"     )     == 0) {
      if (u != NULL)  sprintf  (t, "%2d %-22.22s %c %d", u->len, s   , u->type, u->count);
      else            sprintf  (t, "%2d %-22.22s %c %d", 0     , "[]", '-'    , 0       );
      snprintf (unit_answer, LEN_RECD, "EXTERN entry(%2d) : %s", n, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
