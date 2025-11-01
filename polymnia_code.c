/*============================----beg-of-source---============================*/
#include  "polymnia.h"



static FILE *s_file = NULL;           /* source file */
static char  s_name [LEN_RECD] = "";  /* source file name */



/*====================------------------------------------====================*/
/*===----                         header processing                    ----===*/
/*====================------------------------------------====================*/
static void  o___HEADERS_________o () { return; }

char
poly_code__unquote      (char *a_dst, char *a_src, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *x_beg       = NULL;
   char       *x_end       = NULL;
   int         x_len       =    0;
   /*---(check destination)--------------*/
   --rce;  if (a_dst == NULL) {
      return rce;
   }
   /*---(check source)-------------------*/
   --rce;  if (a_src == NULL) {
      a_dst [0] = '\0';
      return rce;
   }
   /*---(check empty)--------------------*/
   x_len = strlen (a_src);
   if (x_len == 0) {
      a_dst [0] = '\0';
      return 0;
   }
   /*---(set beginning)------------------*/
   x_beg = a_src;
   if (x_beg [0] == '"') {
      ++x_beg;
      --x_len;
   }
   ystrlcpy (a_dst, x_beg, a_max);
   /*---(set ending)---------------------*/
   x_end = a_dst + x_len - 1;
   if (x_end [0] == '"') {
      x_end [0] = '\0';
      --x_len;
   }
   /*---(complete)-----------------------*/
   return 0;
}

/*> char                                                                                                                                          <* 
 *> poly_code__oneliners    (tFILE *a_file, char *a_recd)                                                                                         <* 
 *> {                                                                                                                                             <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                   <* 
 *>    char        rce         =  -10;                                                                                                            <* 
 *>    char       *q           = NULL;                                                                                                            <* 
 *>    char       *r           = NULL;                                                                                                            <* 
 *>    /+---(header)-------------------------+/                                                                                                   <* 
 *>    DEBUG_INPT   yLOG_enter   (__FUNCTION__);                                                                                                  <* 
 *>    /+---(defense)------------------------+/                                                                                                   <* 
 *>    DEBUG_INPT   yLOG_point   ("a_file"    , a_file);                                                                                          <* 
 *>    --rce;  if (a_file == NULL) {                                                                                                              <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                                                                          <* 
 *>       return rce;                                                                                                                             <* 
 *>    }                                                                                                                                          <* 
 *>    DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);                                                                                          <* 
 *>    --rce;  if (a_recd == NULL) {                                                                                                              <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                                                                          <* 
 *>       return rce;                                                                                                                             <* 
 *>    }                                                                                                                                          <* 
 *>    DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);                                                                                          <* 
 *>    /+---(filter)-------------------------+/                                                                                                   <* 
 *>    --rce;  if (strncmp (a_recd, "#define",  7) != 0) {                                                                                        <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                                                                          <* 
 *>       return rce;                                                                                                                             <* 
 *>    }                                                                                                                                          <* 
 *>    /+---(prepare)------------------------+/                                                                                                   <* 
 *>    q = strstr (a_recd, " P_");                                                                                                                <* 
 *>    DEBUG_INPT   yLOG_point   ("q"         , q);                                                                                               <* 
 *>    --rce;  if (q == NULL) {                                                                                                                   <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                                                                          <* 
 *>       return rce;                                                                                                                             <* 
 *>    }                                                                                                                                          <* 
 *>    ++q;                                                                                                                                       <* 
 *>    DEBUG_INPT   yLOG_info    ("q"         , q);                                                                                               <* 
 *>    r = strchr (a_recd, '"');                                                                                                                  <* 
 *>    DEBUG_INPT   yLOG_point   ("r"         , r);                                                                                               <* 
 *>    --rce;  if (r == NULL) {                                                                                                                   <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                                                                          <* 
 *>       return rce;                                                                                                                             <* 
 *>    }                                                                                                                                          <* 
 *>    DEBUG_INPT   yLOG_info    ("r"         , r);                                                                                               <* 
 *>    /+---(master)-------------------+/                                                                                                         <* 
 *>    if      (strncmp (q, "P_FOCUS     ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_focus    , r, LEN_DESC);                                 <* 
 *>    else if (strncmp (q, "P_NICHE     ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_niche    , r, LEN_DESC);                                 <* 
 *>    else if (strncmp (q, "P_SUBJECT   ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_subject  , r, LEN_DESC);                                 <* 
 *>    else if (strncmp (q, "P_PURPOSE   ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_purpose  , r, LEN_HUND);                                 <* 
 *>    /+---(greek)--------------------+/                                                                                                         <* 
 *>    else if (strncmp (q, "P_NAMESAKE  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_namesake , r, LEN_HUND);                                 <* 
 *>    else if (strncmp (q, "P_PRONOUNCE ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_pronounce, r, LEN_TITLE);                                <* 
 *>    else if (strncmp (q, "P_HERITAGE  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_heritage , r, LEN_HUND);                                 <* 
 *>    else if (strncmp (q, "P_BRIEFLY   ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_briefly  , r, LEN_TITLE);                                <* 
 *>    else if (strncmp (q, "P_IMAGERY   ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_imagery  , r, LEN_HUND);                                 <* 
 *>    else if (strncmp (q, "P_REASON    ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_reason   , r, LEN_HUND);                                 <* 
 *>    /+---(oneline)------------------+/                                                                                                         <* 
 *>    else if (strncmp (q, "P_ONELINE   ", 12) == 0)  sprintf (a_file->i_proj->j_oneline, "%s %s", a_file->i_proj->j_namesake, a_file->i_proj->j_subject);   <* 
 *>    /+---(location)-----------------+/                                                                                                         <* 
 *>    else if (strncmp (q, "P_BASENAME  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_progname , r, LEN_TITLE);                                <* 
 *>    else if (strncmp (q, "P_FULLPATH  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_fullpath , r, LEN_HUND);                                 <* 
 *>    else if (strncmp (q, "P_SUFFIX    ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_suffix   , r, LEN_LABEL);                                <* 
 *>    else if (strncmp (q, "P_CONTENT   ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_content  , r, LEN_TITLE);                                <* 
 *>    /+---(chars)--------------------+/                                                                                                         <* 
 *>    else if (strncmp (q, "P_SYSTEM    ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_systems  , r, LEN_HUND);                                 <* 
 *>    else if (strncmp (q, "P_LANGUAGE  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_language , r, LEN_HUND);                                 <* 
 *>    else if (strncmp (q, "P_COMPILER  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_compiler , r, LEN_LABEL);                                <* 
 *>    else if (strncmp (q, "P_CODESIZE  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_codesize , r, LEN_DESC);                                 <* 
 *>    /+---(depends)------------------+/                                                                                                         <* 
 *>    else if (strncmp (q, "P_DEPSTDC   ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_dep_cstd , r, LEN_HUND);                                 <* 
 *>    else if (strncmp (q, "P_DEPPOSIX  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_dep_posix, r, LEN_HUND);                                 <* 
 *>    else if (strncmp (q, "P_DEPCORE   ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_dep_core , r, LEN_HUND);                                 <* 
 *>    else if (strncmp (q, "P_DEPVIKEY  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_dep_vikey, r, LEN_HUND);                                 <* 
*>    else if (strncmp (q, "P_DEPOTHER  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_dep_other, r, LEN_HUND);                                 <* 
*>    else if (strncmp (q, "P_DEPGRAPH  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_dep_graph, r, LEN_HUND);                                 <* 
*>    else if (strncmp (q, "P_DEPSOLO   ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_dep_solo , r, LEN_HUND);                                 <* 
*>    /+---(created)------------------+/                                                                                                         <* 
*>    else if (strncmp (q, "P_AUTHOR    ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_author   , r, LEN_TITLE);                                <* 
*>    else if (strncmp (q, "P_CREATED   ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_created  , r, LEN_LABEL);                                <* 
*>    /+---(version)------------------+/                                                                                                         <* 
*>    else if (strncmp (q, "P_VERMAJOR  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_vermajor , r, LEN_HUND);                                 <* 
*>    else if (strncmp (q, "P_VERMINOR  ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_verminor , r, LEN_HUND);                                 <* 
*>    else if (strncmp (q, "P_VERNUM    ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_vernum   , r, LEN_LABEL);                                <* 
*>    else if (strncmp (q, "P_VERTXT    ", 12) == 0)  poly_code__unquote (a_file->i_proj->j_vertxt   , r, LEN_HUND);                                 <* 
*>    /+---(notes)--------------------+/                                                                                                         <* 
*>    else if (strncmp (q, "P_PRIORITY  ", 12) == 0)  ;                                                                                          <* 
*>    else if (strncmp (q, "P_PRINCIPLE ", 12) == 0)  ;                                                                                          <* 
*>    else if (strncmp (q, "P_REMINDER  ", 12) == 0)  ;                                                                                          <* 
*>    /+---(complete)-----------------------+/                                                                                                   <* 
*>    DEBUG_INPT   yLOG_exit    (__FUNCTION__);                                                                                                  <* 
*>    return 0;                                                                                                                                  <* 
*> }                                                                                                                                             <*/



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
 *>    x_inside = poly_func_inside (a_func);                                          <* 
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

char
poly_code__counts       (tFILE *a_file, tFUNC *a_func, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_inside    =   -1;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_func"    , a_func);
   if (a_func == NULL) {
      DEBUG_DATA   yLOG_note    ("function is null");
   } else {
      DEBUG_DATA   yLOG_point   ("->work"    , a_func->c_work);
      if (a_func->c_work == NULL) {
         DEBUG_DATA   yLOG_note   ("a_func->work null");
      } else {
         DEBUG_DATA   yLOG_value  ("WORK_BEG"  , a_func->WORK_BEG);
         DEBUG_DATA   yLOG_value  ("WORK_END"  , a_func->WORK_END);
      }
   }
   x_inside = poly_func_inside (a_func);
   if (x_inside == 0)    DEBUG_DATA   yLOG_note   ("inside a function");
   /*---(line counts)--------------------*/
   ++my.COUNT_LINES;
   ++a_file->i_proj->COUNT_LINES;
   ++a_file->COUNT_LINES;
   if (x_inside == 0) ++a_func->COUNT_LINES;
   /*---(code counts)--------------------*/
   ++my.COUNT_CODE;
   ++a_file->i_proj->COUNT_CODE;
   ++a_file->COUNT_CODE;
   if (x_inside == 0) ++a_func->COUNT_CODE;
   /*---(slocl counts)-------------------*/
   if (a_recd [0] != '#') {
      c = ystrldcnt (a_recd, ';', LEN_RECD);
      DEBUG_DATA   yLOG_value   ("c"         , c);
      if (c < 0)  c = 0;
      DEBUG_DATA   yLOG_note   ("slocl");
      my.COUNT_SLOCL += c;
      a_file->COUNT_SLOCL += c;
      a_file->i_proj->COUNT_SLOCL += c;
      if (x_inside == 0) a_func->COUNT_SLOCL += c;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                                      <* 
 *> poly_code__reserved     (tFILE *a_file, tFUNC *a_func, char *a_recd)                      <* 
 *> {                                                                                         <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                               <* 
 *>    char        rce         =  -10;                                                        <* 
 *>    char        x_inside    =   -1;                                                        <* 
 *>    /+---(header)-------------------------+/                                               <* 
 *>    DEBUG_INPT   yLOG_enter   (__FUNCTION__);                                              <* 
 *>    /+---(defense)------------------------+/                                               <* 
 *>    DEBUG_INPT   yLOG_point   ("a_file"    , a_file);                                      <* 
 *>    --rce;  if (a_file == NULL) {                                                          <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                      <* 
 *>       return rce;                                                                         <* 
 *>    }                                                                                      <* 
 *>    DEBUG_INPT   yLOG_point   ("a_func"    , a_func);                                      <* 
 *>    DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);                                      <* 
 *>    --rce;  if (a_recd == NULL) {                                                          <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                      <* 
 *>       return rce;                                                                         <* 
 *>    }                                                                                      <* 
 *>    DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);                                      <* 
 *>    /+---(register a code line)-----------+/                                               <* 
 *>    poly_code__counts (a_file, a_func, a_recd);                                            <* 
 *>    DEBUG_INPT   yLOG_note    ("after counts");                                            <* 
 *>    /+---(check inside)-------------------+/                                               <* 
 *>    x_inside = poly_func_inside (a_func);                                                  <* 
 *>    DEBUG_INPT   yLOG_value   ("x_inside"  , x_inside);                                    <* 
 *>    if (x_inside != 0) {                                                                   <* 
 *>       DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                                      <* 
 *>       return rce;                                                                         <* 
 *>    }                                                                                      <* 
 *>    /+---(function level)-----------------+/                                               <* 
 *>    if (a_func != NULL) {                                                                  <* 
 *>       /+---(returns)---------------------+/                                               <* 
 *>       if      (strstr (a_recd, " return rce") != NULL)   poly_cats_logic (a_func, 'R');   <* 
 *>       else if (strstr (a_recd, " return -"  ) != NULL)   poly_cats_logic (a_func, 'R');   <* 
 *>       else if (strstr (a_recd, " return "   ) != NULL)   poly_cats_logic (a_func, 'r');   <* 
 *>       else if (strstr (a_recd, " return;"   ) != NULL)   poly_cats_logic (a_func, 'r');   <* 
 *>       /+---(choices)---------------------+/                                               <* 
 *>       if      (strstr (a_recd, " if "       ) != NULL)   poly_cats_logic (a_func, 'c');   <* 
 *>       else if (strstr (a_recd, " if("       ) != NULL)   poly_cats_logic (a_func, 'c');   <* 
 *>       else if (strstr (a_recd, " else "     ) != NULL)   poly_cats_logic (a_func, 'c');   <* 
 *>       else if (strstr (a_recd, "}else "     ) != NULL)   poly_cats_logic (a_func, 'c');   <* 
 *>       else if (strstr (a_recd, " else{"     ) != NULL)   poly_cats_logic (a_func, 'c');   <* 
 *>       else if (strstr (a_recd, "}else{"     ) != NULL)   poly_cats_logic (a_func, 'c');   <* 
 *>       if      (strstr (a_recd, " case "     ) != NULL)   poly_cats_logic (a_func, 'c');   <* 
 *>       else if (strstr (a_recd, " default "  ) != NULL)   poly_cats_logic (a_func, 'c');   <* 
 *>       else if (strstr (a_recd, " default:"  ) != NULL)   poly_cats_logic (a_func, 'c');   <* 
 *>       /+---(loops)-----------------------+/                                               <* 
 *>       if      (strstr (a_recd, " while "    ) != NULL)   poly_cats_logic (a_func, 'l');   <* 
 *>       else if (strstr (a_recd, " while("    ) != NULL)   poly_cats_logic (a_func, 'l');   <* 
 *>       if      (strstr (a_recd, " do "       ) != NULL)   poly_cats_logic (a_func, 'l');   <* 
 *>       if      (strstr (a_recd, "}do "       ) != NULL)   poly_cats_logic (a_func, 'l');   <* 
 *>       else if (strstr (a_recd, " do("       ) != NULL)   poly_cats_logic (a_func, 'l');   <* 
 *>       else if (strstr (a_recd, "}do("       ) != NULL)   poly_cats_logic (a_func, 'l');   <* 
 *>       if      (strstr (a_recd, " for "      ) != NULL)   poly_cats_logic (a_func, 'L');   <* 
 *>       else if (strstr (a_recd, " for("      ) != NULL)   poly_cats_logic (a_func, 'L');   <* 
 *>       /+---(lcoal static)----------------+/                                               <* 
 *>       if      (strstr (a_recd, " static "   ) != NULL)   ++a_func->WORK_LSTATIC;          <* 
 *>       /+---(done)------------------------+/                                               <* 
 *>    }                                                                                      <* 
 *>    /+---(complete)-----------------------+/                                               <* 
 *>    DEBUG_INPT   yLOG_exit    (__FUNCTION__);                                              <* 
 *>    return 0;                                                                              <* 
 *> }                                                                                         <*/



/*====================------------------------------------====================*/
/*===----                       source file processing                 ----===*/
/*====================------------------------------------====================*/
static void  o___REVIEW__________o () { return; }

char
poly_code_function      (tFUNC *a_func, char *a_recd, char *a_prev)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   int        x_len        =    0;
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
   rc = poly_line_func   (a_prev, a_recd, a_func->c_name, &(a_func->STATS_SINGLE), &(a_func->STATS_SCOPE), &(a_func->STATS_RTYPE), a_func->c_rlong);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(purpose)------------------------*/
   --rce;  if (a_func->STATS_SINGLE == '-') {
      p  = strstr (a_prev, "/*");
      if (p != NULL) {
         x_len = p - a_prev;
         rc = poly_line_purpose (a_prev + x_len, a_func->c_purpose, &(a_func->c_ready));
         if (rc < 0) {
            DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
   } else {
      rc = poly_line_purpose ("/* */", a_func->c_purpose, &(a_func->c_ready));
   }
   /*---(parameters)---------------------*/
   rc = poly_line_params (a_recd, &(a_func->STATS_PAUDIT), &(a_func->WORK_PARAMS), &(a_func->WORK_PIN), &(a_func->WORK_POUT), &(a_func->WORK_PBOTH), &(a_func->WORK_PCHG), &(a_func->WORK_PNUM), &(a_func->WORK_PMULTI), &(a_func->WORK_PFUNC), &(a_func->WORK_PSTRUCT));
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
         poly_code_function (*a_func, x_full, a_prev);
      }
   }
   /*---(check single line)-----------*/
   if (*a_func != NULL) {
      if ((*a_func)->STATS_SINGLE == 'y') {
         DEBUG_DATA   yLOG_note    ("single liner entry");
         poly_func_enter (*a_func, a_line);
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
   x_inside = poly_func_inside (a_func);
   DEBUG_INPT   yLOG_value   ("x_inside"  , x_inside);
   /*---(outside)---------------------*/
   if (x_inside != 1) {
      DEBUG_INPT   yLOG_note    ("outside all functions, but including headers and { } outside braces");
      poly_line_all       (        0, &(my.COUNT_LINES), &(a_file->i_proj->COUNT_LINES), &(a_file->COUNT_LINES), NULL);
      if (rc == 0)  rc = poly_line_empty     (x_full, 0, &(my.COUNT_EMPTY), &(a_file->i_proj->COUNT_EMPTY), &(a_file->COUNT_EMPTY), NULL);
      if (rc == 0)  rc = poly_line_comment   (x_full, 0, &(my.COUNT_DOCS ), &(a_file->i_proj->COUNT_DOCS ), &(a_file->COUNT_DOCS ), NULL);
      if (rc == 0)  rc = poly_line_debug     (x_full, 0, &(my.COUNT_DEBUG), &(a_file->i_proj->COUNT_DEBUG), &(a_file->COUNT_DEBUG), NULL, NULL, NULL, NULL);
      if (rc == 0)  rc = poly_line_unguard   (x_full, 0, &(my.COUNT_DEBUG), &(a_file->i_proj->COUNT_DEBUG), &(a_file->COUNT_DEBUG), NULL, NULL, NULL);
      if (rc == 0) {
         poly_line_code      (        0, &(my.COUNT_CODE ), &(a_file->i_proj->COUNT_CODE ), &(a_file->COUNT_CODE ), &(a_func->COUNT_CODE ));
         poly_line_slocl     (x_full, 0, &(my.COUNT_SLOCL), &(a_file->i_proj->COUNT_SLOCL), &(a_file->COUNT_SLOCL), &(a_func->COUNT_SLOCL));
      }
   }
   /*---(inside)----------------------*/
   else {
      DEBUG_INPT   yLOG_note    ("inside function code");
      poly_line_all       (        1, &(my.COUNT_LINES), &(a_file->i_proj->COUNT_LINES), &(a_file->COUNT_LINES), &(a_func->COUNT_LINES));
      if (rc == 0)  rc = poly_line_empty     (x_full, 1, &(my.COUNT_EMPTY), &(a_file->i_proj->COUNT_EMPTY), &(a_file->COUNT_EMPTY), &(a_func->COUNT_EMPTY));
      if (rc == 0)  rc = poly_line_comment   (x_full, 1, &(my.COUNT_DOCS ), &(a_file->i_proj->COUNT_DOCS ), &(a_file->COUNT_DOCS ), &(a_func->COUNT_DOCS ));
      if (rc == 0)  rc = poly_line_debug     (x_full, 1, &(my.COUNT_DEBUG), &(a_file->i_proj->COUNT_DEBUG), &(a_file->COUNT_DEBUG), &(a_func->COUNT_DEBUG), &(a_func->WORK_DCOUNT), &(a_func->WORK_DEXTRA), &(a_func->STATS_DMACRO));
      if (rc == 0)  rc = poly_line_unguard   (x_full, 1, &(my.COUNT_DEBUG), &(a_file->i_proj->COUNT_DEBUG), &(a_file->COUNT_DEBUG), &(a_func->COUNT_DEBUG), &(a_func->WORK_DCOUNT), &(a_func->STATS_DMACRO));
      if (rc == 0) {
         poly_line_code      (        1, &(my.COUNT_CODE ), &(a_file->i_proj->COUNT_CODE ), &(a_file->COUNT_CODE ), &(a_func->COUNT_CODE ));
         poly_line_slocl     (x_full, 1, &(my.COUNT_SLOCL), &(a_file->i_proj->COUNT_SLOCL), &(a_file->COUNT_SLOCL), &(a_func->COUNT_SLOCL));
         rc = poly_line_exit   (a_curr, 1, &(a_func->WORK_RETURN), &(a_func->WORK_RCE));
         rc = poly_line_choice (a_curr, 1, &(a_func->WORK_CHOICE));
         rc = poly_line_loop   (a_curr, 1, &(my.COUNT_SLOCL), &(a_file->i_proj->COUNT_SLOCL), &(a_file->COUNT_SLOCL), &(a_func->COUNT_SLOCL), &(a_func->WORK_LOOP));
         rc = poly_line_indent (a_curr, 1, &(a_func->WORK_INDENT));
      }
   }
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
      poly_func_exit  (a_func, a_line);
      /*> poly_vars_summary (a_func, '-');                                            <*/
   }
   /*---(normal enter)----------------*/
   else if (a_func->WORK_BEG <  0) {
      if (a_curr [0] == '{') {
         DEBUG_INPT   yLOG_note    ("multi-line beg brace");
         rc = poly_func_enter (a_func, a_line);
         DEBUG_INPT   yLOG_value   ("enter"     , rc);
      }
   }
   /*---(normal exit)-----------------*/
   else if (a_func->WORK_END <  0) {
      if (a_curr [0] == '}') {
         DEBUG_INPT   yLOG_note    ("multi-line end brace");
         rc = poly_func_exit (a_func, a_line);
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
         rc = HEADER__single  (a_file->i_proj, x_curr);
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
         if (x_func == NULL)  poly_func_by_line (a_file, x_line, &x_func);
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
      poly_func_by_index (i, &u);
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
