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



static FILE *s_file = NULL;           /* source file */
static char  s_name [LEN_RECD] = "";  /* source file name */



/*====================------------------------------------====================*/
/*===----                       source file processing                 ----===*/
/*====================------------------------------------====================*/
static void  o___SOURCES_________o () { return; }

/*> char                                                                              <* 
 *> poly_code__indent       (tFUNC *a_func, char *a_recd)                             <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    int         i           =    0;                                                <* 
 *>    int         x_len       =    0;                                                <* 
 *>    char        x_inside    =   -1;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_INPT   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    DEBUG_INPT   yLOG_point   ("a_func"    , a_func);                              <* 
 *>    --rce;  if (a_func == NULL) {                                                  <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    DEBUG_INPT   yLOG_info    ("->name"    , a_func->name);                        <* 
 *>    DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);                              <* 
 *>    --rce;  if (a_recd == NULL) {                                                  <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);                              <* 
 *>    /+---(check inside)-------------------+/                                       <* 
 *>    x_inside = FUNCS_inside     (a_func);                                          <* 
 *>    if (x_inside != 0) {                                                           <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(calculate indent)---------------+/                                       <* 
 *>    x_len = strlen (a_recd);                                                       <* 
 *>    DEBUG_INPT   yLOG_value   ("x_len"     , x_len);                               <* 
 *>    for (i = 0; i < x_len; ++i) {                                                  <* 
 *>       if (a_recd [i] == ' ')   continue;                                          <* 
 *>       if (i > a_func->WORK_INDENT) a_func->WORK_INDENT = i;                       <* 
 *>       break;                                                                      <* 
 *>    }                                                                              <* 
 *>    DEBUG_INPT   yLOG_value   ("indent"    , a_func->WORK_INDENT);                 <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_INPT   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> poly_code__counts       (tFILE *a_file, tFUNC *a_func, char *a_recd)              <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        x_inside    =   -1;                                                <* 
 *>    char        c           =    0;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_DATA   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    DEBUG_DATA   yLOG_point   ("a_func"    , a_func);                              <* 
 *>    if (a_func == NULL) {                                                          <* 
 *>       DEBUG_DATA   yLOG_note    ("function is null");                             <* 
 *>    } else {                                                                       <* 
 *>       DEBUG_DATA   yLOG_point   ("->work"    , a_func->c_work);                   <* 
 *>       if (a_func->c_work == NULL) {                                               <* 
 *>          DEBUG_DATA   yLOG_note   ("a_func->work null");                          <* 
 *>       } else {                                                                    <* 
 *>          DEBUG_DATA   yLOG_value  ("WORK_BEG"  , a_func->WORK_BEG);               <* 
 *>          DEBUG_DATA   yLOG_value  ("WORK_END"  , a_func->WORK_END);               <* 
 *>       }                                                                           <* 
 *>    }                                                                              <* 
 *>    x_inside = FUNCS_inside     (a_func);                                          <* 
 *>    if (x_inside == 0)    DEBUG_DATA   yLOG_note   ("inside a function");          <* 
 *>    /+---(line counts)--------------------+/                                       <* 
 *>    ++my.COUNT_LINES;                                                              <* 
 *>    ++a_file->i_proj->COUNT_LINES;                                                 <* 
 *>    ++a_file->COUNT_LINES;                                                         <* 
 *>    if (x_inside == 0) ++a_func->COUNT_LINES;                                      <* 
 *>    /+---(code counts)--------------------+/                                       <* 
 *>    ++my.COUNT_CODE;                                                               <* 
 *>    ++a_file->i_proj->COUNT_CODE;                                                  <* 
 *>    ++a_file->COUNT_CODE;                                                          <* 
 *>    if (x_inside == 0) ++a_func->COUNT_CODE;                                       <* 
 *>    /+---(slocl counts)-------------------+/                                       <* 
 *>    if (a_recd [0] != '#') {                                                       <* 
 *>       c = ystrldcnt (a_recd, ';', LEN_RECD);                                      <* 
 *>       DEBUG_DATA   yLOG_value   ("c"         , c);                                <* 
 *>       if (c < 0)  c = 0;                                                          <* 
 *>       DEBUG_DATA   yLOG_note   ("slocl");                                         <* 
 *>       my.COUNT_SLOCL += c;                                                        <* 
 *>       a_file->COUNT_SLOCL += c;                                                   <* 
 *>       a_file->i_proj->COUNT_SLOCL += c;                                           <* 
 *>       if (x_inside == 0) a_func->COUNT_SLOCL += c;                                <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_DATA   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/



/*====================------------------------------------====================*/
/*===----                       source file processing                 ----===*/
/*====================------------------------------------====================*/
static void  o___REVIEW__________o () { return; }

char
CODE_function           (tFUNC *a_func, char *a_recd, char *a_prev)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   int        x_len        =    0;
   char       x_single     =  '-';
   char       x_scope      =  '-';
   char       x_rtype      =  '-';
   char       x_rlong      [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      a_func->c_ready = 'e';
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(return)-------------------------*/
   /*> rc = LINE_function    (a_func, a_prev, a_recd, a_func->c_name, &(a_func->STATS_SINGLE), &(a_func->STATS_SCOPE), &(a_func->STATS_RTYPE), a_func->c_rlong);   <*/
   rc = LINE_function    (a_func, a_prev, a_recd, a_func->c_name, NULL, NULL, NULL, NULL);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(purpose)------------------------*/
   --rce;  if (a_func->STATS_SINGLE == '-') {
      p  = strstr (a_prev, "/*");
      if (p != NULL) {
         x_len = p - a_prev;
         rc = LINE_purpose      (a_func, a_prev + x_len, NULL, a_func->c_purpose, &(a_func->c_ready));
         if (rc < 0) {
            DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
   } else {
      rc = LINE_purpose      (a_func, "/* */", NULL, a_func->c_purpose, &(a_func->c_ready));
   }
   /*---(parameters)---------------------*/
   /*> rc = LINE_params      (a_func, a_recd, &(a_func->STATS_PAUDIT), &(a_func->WORK_PARAMS), &(a_func->WORK_PIN), &(a_func->WORK_POUT), &(a_func->WORK_PBOTH), &(a_func->WORK_PCHG), NULL, &(a_func->WORK_PNUM), &(a_func->WORK_PMULTI), &(a_func->WORK_PFUNC), &(a_func->WORK_PSTRUCT));   <*/
   rc = LINE_params      (a_func, a_recd, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prototype)----------------------*/
   rc = poly_proto_hook  (a_func->c_file, a_func, a_func->c_name);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        helpers                               ----===*/
/*====================------------------------------------====================*/
static void  o___HELPERS_________o () { return; }

char
poly_code_nextfunc      (tFILE *a_file, tFUNC **a_func)
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
   DEBUG_DATA   yLOG_spoint  (a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_func);
   /*---(first time)---------------------*/
   --rce;  if (*a_func == NULL) {
      DEBUG_DATA   yLOG_snote   ("first");
      *a_func = a_file->i_chead;
   }
   /*---(next time)----------------------*/
   else { 
      DEBUG_DATA   yLOG_snote   ("next");
      *a_func = (*a_func)->c_next;
   }
   DEBUG_DATA   yLOG_spoint  (*a_func);
   /*---(trouble)-------------------------------*/
   --rce;  if (*a_func == NULL) {
      DEBUG_DATA   yLOG_snote   ("first/next is null");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)------------------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
poly_code__before       (tFILE *a_file, int a_line, tFUNC **a_func, char *a_curr, char *a_prev)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_full      [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("*a_func"   , *a_func);
   /*---(check function)--------------*/
   if (*a_func == NULL) {
      rc = poly_code_nextfunc (a_file, a_func);
   }
   /*---(advance as needed)-----------*/
   if (*a_func != NULL && (*a_func)->WORK_END > 0) {
      rc = poly_code_nextfunc (a_file, a_func);
   }
   DEBUG_INPT   yLOG_point   ("*a_func"   , *a_func);
   /*---(found header)----------------*/
   if (*a_func != NULL) {
      DEBUG_INPT   yLOG_value   ("line"      , (*a_func)->c_line);
      if (a_line == (*a_func)->c_line) {
         DEBUG_INPT   yLOG_note    ("FUNCTION HEADER FOUND");
         ystrlcpy   (x_full, a_curr   , LEN_RECD);
         ystrltrim  (x_full, ySTR_BOTH, LEN_RECD);
         DEBUG_INPT   yLOG_info    ("x_full"    , x_full);
         CODE_function (*a_func, x_full, a_prev);
      }
   }
   /*---(check single line)-----------*/
   if (*a_func != NULL) {
      if ((*a_func)->STATS_SINGLE == 'y') {
         DEBUG_DATA   yLOG_note    ("single liner entry");
         FUNCS_enter     (*a_func, a_line);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_code__current      (tFILE *a_file, int a_line, tFUNC *a_func, char *a_curr, char *a_prev)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_full      [LEN_RECD]  = "";
   char        x_recd      [LEN_RECD]  = "";
   tFUNC      *x_func      = NULL;
   char        x_inside    =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("a_line"    , a_line);
   DEBUG_INPT   yLOG_point   ("a_curr"    , a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_curr"    , a_curr);
   /*---(prepare)---------------------*/
   ystrlcpy   (x_full, a_curr   , LEN_RECD);
   ystrltrim  (x_full, ySTR_BOTH, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("x_full"    , x_full);
   ystrlcpy   (x_recd, a_curr   , LEN_RECD);
   ystrlunall (x_recd, LEN_RECD);
   DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
   /*---(display)---------------------*/
   if (a_func == NULL) {
      DEBUG_INPT   yLOG_info    ("CURR"      , "no function(s) in file");
   } else {
      DEBUG_INPT   yLOG_complex ("CURR"      , "%4d] %-20.20s %4d %c %4d %4d -- %4d %4d", a_line, a_func->c_name, a_func->c_line, a_func->STATS_SINGLE, a_func->c_beg, a_func->c_end, a_func->WORK_BEG, a_func->WORK_END);
   }
   x_inside = FUNCS_inside     (a_func);
   DEBUG_INPT   yLOG_value   ("x_inside"  , x_inside);
   if (x_inside == 0) {
      DEBUG_INPT   yLOG_note    ("outside all functions, but including headers and { } outside braces");
      x_func = NULL;
   } else {
      DEBUG_INPT   yLOG_note    ("inside function code, but not outside braces");
      x_func = a_func;
   }
   /*---(outside)---------------------*/
   if (rc == 0)  rc = LINE_count_all      (x_func, x_inside, NULL, NULL, NULL, NULL);
   if (rc == 0)  rc = LINE_count_empty    (x_func, x_full, x_inside, NULL, NULL, NULL, NULL);
   if (rc == 0)  rc = LINE_count_comment  (x_func, x_full, x_inside, NULL, NULL, NULL, NULL);
   if (rc == 0)  rc = LINE_count_debug    (x_func, x_full, x_inside, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   if (rc == 0)  rc = LINE_count_unguard  (x_func, x_full, x_inside, NULL, NULL, NULL, NULL, NULL, NULL);
   if (rc == 0) {
      rc = LINE_count_code     (x_func, x_inside, NULL, NULL, NULL, NULL);
      rc = LINE_count_slocl    (x_func, x_full, x_inside, NULL, NULL, NULL, NULL);
      if (x_inside == 1) {
         rc = LINE_exit        (x_func, a_curr, 1, NULL, NULL);
         rc = LINE_choice      (x_func, a_curr, 1, NULL);
         rc = LINE_loop        (x_func, a_curr, 1, NULL, NULL, NULL, NULL, NULL);
         rc = LINE_indent      (x_func, a_curr, 1, NULL);
      }
   }
   /*---(inside)----------------------*/
   /*> else {                                                                                                                                                                                                                                         <* 
    *>    DEBUG_INPT   yLOG_note    ("inside function code");                                                                                                                                                                                         <* 
    *>    LINE_count_all      (a_func,         1, &(my.COUNT_LINES), &(a_file->i_proj->COUNT_LINES), &(a_file->COUNT_LINES), &(a_func->COUNT_LINES));                                                                                                 <* 
    *>    if (rc == 0)  rc = LINE_count_empty    (a_func, x_full, 1, &(my.COUNT_EMPTY), &(a_file->i_proj->COUNT_EMPTY), &(a_file->COUNT_EMPTY), &(a_func->COUNT_EMPTY));                                                                              <* 
    *>    if (rc == 0)  rc = LINE_count_comment  (a_func, x_full, 1, &(my.COUNT_DOCS ), &(a_file->i_proj->COUNT_DOCS ), &(a_file->COUNT_DOCS ), &(a_func->COUNT_DOCS ));                                                                              <* 
    *>    /+> if (rc == 0)  rc = LINE_count_debug    (x_full, 1, &(my.COUNT_DEBUG), &(a_file->i_proj->COUNT_DEBUG), &(a_file->COUNT_DEBUG), &(a_func->COUNT_DEBUG), &(a_func->WORK_DCOUNT), &(a_func->WORK_DEXTRA), &(a_func->STATS_DMACRO));   <+/   <* 
    *>    if (rc == 0)  rc = LINE_count_debug    (a_func, x_full, 1, &(my.COUNT_DEBUG), &(a_file->i_proj->COUNT_DEBUG), &(a_file->COUNT_DEBUG), &(a_func->COUNT_DEBUG), NULL, NULL, &(a_func->STATS_DMACRO));                                         <* 
    *>    if (rc == 0)  rc = LINE_count_unguard  (a_func, x_full, 1, &(my.COUNT_DEBUG), &(a_file->i_proj->COUNT_DEBUG), &(a_file->COUNT_DEBUG), &(a_func->COUNT_DEBUG), &(a_func->WORK_DCOUNT), &(a_func->STATS_DMACRO));                             <* 
    *>    if (rc == 0) {                                                                                                                                                                                                                              <* 
    *>       LINE_count_code     (a_func,         1, &(my.COUNT_CODE ), &(a_file->i_proj->COUNT_CODE ), &(a_file->COUNT_CODE ), &(a_func->COUNT_CODE ));                                                                                              <* 
    *>       LINE_count_slocl    (a_func, x_full, 1, &(my.COUNT_SLOCL), &(a_file->i_proj->COUNT_SLOCL), &(a_file->COUNT_SLOCL), &(a_func->COUNT_SLOCL));                                                                                              <* 
    *>       /+> rc = LINE_exit        (a_func, a_curr, 1, &(a_func->WORK_RETURN), &(a_func->WORK_RCE));   <+/                                                                                                                                        <* 
    *>       rc = LINE_exit        (a_func, a_curr, 1, NULL, NULL);                                                                                                                                                                                   <* 
    *>       /+> rc = LINE_choice      (a_func, a_curr, 1, &(a_func->WORK_CHOICE));       <+/                                                                                                                                                         <* 
    *>       rc = LINE_choice      (a_func, a_curr, 1, NULL);                                                                                                                                                                                         <* 
    *>       /+> rc = LINE_loop        (a_func, a_curr, 1, &(my.COUNT_SLOCL), &(a_file->i_proj->COUNT_SLOCL), &(a_file->COUNT_SLOCL), &(a_func->COUNT_SLOCL), &(a_func->WORK_LOOP));   <+/                                                            <* 
    *>       rc = LINE_loop        (a_func, a_curr, 1, &(my.COUNT_SLOCL), &(a_file->i_proj->COUNT_SLOCL), &(a_file->COUNT_SLOCL), &(a_func->COUNT_SLOCL), NULL);                                                                                      <* 
    *>       /+> rc = LINE_indent      (a_func, a_curr, 1, &(a_func->WORK_INDENT));       <+/                                                                                                                                                         <* 
    *>       rc = LINE_indent      (a_func, a_curr, 1, NULL);                                                                                                                                                                                         <* 
    *>    }                                                                                                                                                                                                                                           <* 
    *> }                                                                                                                                                                                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_code__after        (tFILE *a_file, int a_line, tFUNC *a_func, char *a_curr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_line"    , a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_func"    , a_func);
   if (a_func == NULL) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(single line exit)------------*/
   if (a_func->STATS_SINGLE == 'y') {
      DEBUG_DATA   yLOG_note    ("single liner exit");
      FUNCS_exit      (a_func, a_line);
      /*> poly_vars_summary (a_func, '-');                                            <*/
   }
   /*---(normal enter)----------------*/
   else if (a_func->WORK_BEG <  0) {
      if (a_curr [0] == '{') {
         DEBUG_INPT   yLOG_note    ("multi-line beg brace");
         rc = FUNCS_enter     (a_func, a_line);
         DEBUG_INPT   yLOG_value   ("enter"     , rc);
      }
   }
   /*---(normal exit)-----------------*/
   else if (a_func->WORK_END <  0) {
      if (a_curr [0] == '}') {
         DEBUG_INPT   yLOG_note    ("multi-line end brace");
         rc = FUNCS_exit     (a_func, a_line);
         DEBUG_INPT   yLOG_value   ("exit"      , rc);
         /*> poly_vars_summary (a_func, '-');                                         <*/
         --a_func->COUNT_LINES;
         --a_func->COUNT_CODE;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
poly_code_driver        (tFILE *a_file, int a_beg, int a_end, char a_act)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_curr      [LEN_RECD]  = "";
   char        x_prev      [LEN_RECD]  = "";
   char        x_fixed     [LEN_RECD]  = "";
   int         x_len       =    0;          /* length of input record         */
   int         x_line      =    0;
   tFUNC      *x_func      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open file)----------------------*/
   rc = poly_shared_open ('c', a_file->i_name);
   DEBUG_INPT   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(walk)---------------------------*/
   --rce;  while (rc >= 0) {
      /*---(read)------------------------*/
      rc = poly_shared_read ('c', &x_line, x_curr, x_prev);
      DEBUG_INPT   yLOG_value   ("read"      , rc);
      if (rc < 0)  {
         DEBUG_INPT   yLOG_note    ("reading of line failed or eof");
         break;
      }
      DEBUG_INPT   yLOG_value   ("x_line"    , x_line);
      /*---(check headers)---------------*/
      if (a_file->i_type == 'h') {
         DEBUG_INPT   yLOG_note    ("header file (h) line");
         rc = HEADER__single  (a_file->i_proj, NULL, a_file->i_type, x_curr, NULL);
         DEBUG_INPT   yLOG_value   ("oneliners" , rc);
         rc = poly_code__current (a_file, 0     , NULL  , x_curr, x_prev);
         DEBUG_INPT   yLOG_value   ("current"   , rc);
      }
      /*---(check sources)---------------*/
      else if (a_act == CODE_NORMAL) {
         DEBUG_INPT   yLOG_note    ("source file (c) line");
         rc = poly_code__before  (a_file, x_line, &x_func, x_curr, x_prev);
         rc = poly_code__current (a_file, x_line, x_func, x_curr, x_prev);
         if (x_func != NULL)  rc = poly_vars_find (x_func, x_line, x_curr, '-');
         rc = poly_code__after   (a_file, x_line, x_func, x_curr);
      }
      /*---(specialty)-------------------*/
      else if (x_line > a_beg && x_line < a_end) {
         if (x_func == NULL)  FUNCS_by_file_line  (a_file, x_line, &x_func);
         if (x_func == NULL)  rc = poly_vars_find (x_func, x_line, x_curr, a_act);
      }
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = poly_shared_close ('c');
   DEBUG_INPT   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char poly_code_review (tFILE *a_file) { return poly_code_driver (a_file, 0, 99999, '-'); }



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
poly_code__unit         (char *a_question, int i)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD] = "[]";
   char        r           [LEN_RECD] = "";
   char        s           [LEN_LABEL]= "";
   tFUNC      *u           = NULL;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "CODE unit        : function number unknown");
   if (strcmp (a_question, "work"      )     == 0) {
      FUNCS_by_index     (i, &u);
      if (u != NULL) {
         sprintf  (t, "[%.20s]", u->c_name);
         if (u->WORK_CHOICE > 0)  sprintf (s, " %3dc", u->WORK_CHOICE);
         else                     sprintf (s, "   ·c");
         ystrlcat (r, s, LEN_RECD);
         if (u->WORK_LOOP   > 0)  sprintf (s, " %3dl", u->WORK_LOOP);
         else                     sprintf (s, "   ·l");
         ystrlcat (r, s, LEN_RECD);
         if (u->WORK_RETURN > 0)  sprintf (s, " %3dr", u->WORK_RETURN);
         else                     sprintf (s, "   ·r");
         ystrlcat (r, s, LEN_RECD);
         if (u->WORK_RCE    > 0)  sprintf (s, " %3de", u->WORK_RCE);
         else                     sprintf (s, "   ·e");
         ystrlcat (r, s, LEN_RECD);
         if (u->WORK_INDENT > 0)  sprintf (s, " %3di", u->WORK_INDENT);
         else                     sprintf (s, "   ·i");
         ystrlcat (r, s, LEN_RECD);
         snprintf (unit_answer, LEN_RECD, "CODE work   (%2d) : %-22.22s  %s", i, t, r);
      }  else
         snprintf (unit_answer, LEN_RECD, "CODE work   (%2d) : %-22.22s    -c   -l   -r   -e   -i", i, t);
   }
   else if (strcmp (a_question, "file"      )     == 0) {
      if (s_file != NULL)  sprintf  (t, "[%.20s]", s_name);
      snprintf (unit_answer, LEN_RECD, "CODE file        : %c  %-10p  %s", (s_file == NULL) ? '-' : 'y', s_file, t);
      return unit_answer;
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
