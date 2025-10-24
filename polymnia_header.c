/*============================----beg-of-source---============================*/
#include  "polymnia.h"


static tPROJ   s_place;


/*---(name)---------------------*/
#define    J_NAME        "s_proj->j_name"
/*---(master)-------------------*/
#define    J_FOCUS       "s_proj->j_focus"
#define    J_NICHE       "s_proj->j_niche"
#define    J_SUBJECT     "s_proj->j_subject"
#define    J_PURPOSE     "s_proj->j_purpose"
/*---(greek)--------------------*/
#define    J_NAMESAKE    "s_proj->j_namesake"
#define    J_PRONOUNCE   "s_proj->j_pronounce"
#define    J_HERITAGE    "s_proj->j_heritage"
#define    J_BRIEFLY     "s_proj->j_briefly"
#define    J_IMAGERY     "s_proj->j_imagery"
#define    J_REASON      "s_proj->j_reason"
/*---(oneline)------------------*/
#define    J_ONELINE     "s_proj->j_oneline"
/*---(location)-----------------*/
#define    J_HOMEDIR     "s_proj->j_homedir"
#define    J_PROGNAME    "s_proj->j_progname"
#define    J_FULLPATH    "s_proj->j_fullpath"
#define    J_SUFFIX      "s_proj->j_suffix"
#define    J_CONTENT     "s_proj->j_content"
/*---(chars)--------------------*/
#define    J_SYSTEMS     "s_proj->j_systems"
#define    J_LANGUAGE    "s_proj->j_language"
#define    J_COMPILER    "s_proj->j_compiler"
#define    J_CODESIZE    "s_proj->j_codesize"
/*---(depends)------------------*/
#define    J_DCSTD       "s_proj->j_dep_cstd"
#define    J_DPOSIX      "s_proj->j_dep_posix"
#define    J_DCORE       "s_proj->j_dep_core"
#define    J_DVIKEY      "s_proj->j_dep_vikey"
#define    J_DOTHER      "s_proj->j_dep_other"
#define    J_DGRAPH      "s_proj->j_dep_graph"
#define    J_DSOLO       "s_proj->j_dep_solo"
/*---(created)------------------*/
#define    J_AUTHOR      "s_proj->j_author"
#define    J_CREATED     "s_proj->j_created"
/*---(version)------------------*/
#define    J_VERMAJOR    "s_proj->j_vermajor"
#define    J_VERMINOR    "s_proj->j_verminor"
#define    J_VERNUM      "s_proj->j_vernum"
#define    J_VERTXT      "s_proj->j_vertxt"
/*---(summary)------------------*/
#define    J_HEADER      "s_proj->j_header"
/*---(end)----------------------*/


const struct {
   char        h_abbr;
   char        h_name        [LEN_LABEL];
   char        h_label       [LEN_LABEL];
   char        h_desc        [LEN_DESC];
   char       *h_point;
   short       h_min;
   short       h_low;
   short       h_high;
   short       h_max;
} static s_header [LEN_HUND] = {
   /*-------base------------label------------description-------------------------pointer-----------------------------------------min-low-hig-max----------------*/
   { 'N' , "P_NAME"        , "name"         , "project name"                    , &(s_place.j_name [0])       - (char*) &s_place,  1,  4, 15, LEN_TITLE         },
   {  1  , ""              , ""             , ""                                , NULL                                          ,  0,  0,  0, 0                 },
   /*-------master----------label------------description-------------------------pointer-----------------------------------------min-low-hig-max----------------*/
   { 'f' , "P_FOCUS"       , "focus"        , "functional focus"                , &(s_place.j_focus [0])      - (char*) &s_place,  5, 10, 30, LEN_DESC          },
   { 'n' , "P_NICHE"       , "niche"        , "niche within focus"              , &(s_place.j_niche [0])      - (char*) &s_place,  5, 10, 30, LEN_DESC          },
   { 's' , "P_SUBJECT"     , "subject"      , "short purpose statement"         , &(s_place.j_subject [0])    - (char*) &s_place, 10, 20, 30, LEN_DESC          },
   { 'p' , "P_PURPOSE"     , "purpose"      , "longer purpose statement"        , &(s_place.j_purpose [0])    - (char*) &s_place, 30, 50, 70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , NULL                                          ,  0,  0,  0, 0                 },
   /*-------greek-----------label------------description-------------------------pointer-----------------------------------------min-low-hig-max----------------*/
   { 'ê' , "P_NAMESAKE"    , "namesake"     , "greek pantheon sponsor"          , &(s_place.j_namesake [0])   - (char*) &s_place, 10, 20, 40, LEN_HUND          },
   { '÷' , "P_PRONOUNCE"   , "pronounce"    , "arapabet namesake guide"         , &(s_place.j_pronounce [0])  - (char*) &s_place,  0,  5, 30, LEN_TITLE         },
   { 'î' , "P_HERITAGE"    , "heritage"     , "longer description of god"       , &(s_place.j_heritage [0])   - (char*) &s_place, 40, 40, 70, LEN_HUND          },
   { 'é' , "P_BRIEFLY"     , "briefly"      , "short description of god"        , &(s_place.j_briefly [0])    - (char*) &s_place,  0, 20, 30, LEN_TITLE         },
   { 'ð' , "P_IMAGERY"     , "imagery"      , "description of the god"          , &(s_place.j_imagery [0])    - (char*) &s_place, 40, 40, 70, LEN_HUND          },
   { 'ø' , "P_REASON"      , "reason"       , "reason patronage makes sense"    , &(s_place.j_reason [0])     - (char*) &s_place, 40, 40, 70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , NULL                                          ,  0,  0,  0, 0                 },
   /*-------oneline---------label------------description-------------------------pointer-----------------------------------------min-low-hig-max----------------*/
   { 'ö' , "P_ONELINE"     , "oneline"      , "reporting suppmary line"         , &(s_place.j_oneline [0])    - (char*) &s_place, 40, 50, 70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , NULL                                          ,  0,  0,  0, 0                 },
   /*-------location--------label------------description-------------------------pointer-----------------------------------------min-low-hig-max----------------*/
   { 'd' , "P_HOMEDIR"     , "homedir"      , "project source directory"        , &(s_place.j_homedir [0])    - (char*) &s_place,  1,  4, 70, LEN_HUND          },
   { 'b' , "P_PROGNAME"    , "progname"     , "run-time executable"             , &(s_place.j_progname [0])   - (char*) &s_place,  1,  4, 20, LEN_TITLE         },
   { 'f' , "P_FULLPATH"    , "fullpath"     , "installed location"              , &(s_place.j_fullpath [0])   - (char*) &s_place, 10, 20, 70, LEN_HUND          },
   { 's' , "P_SUFFIX"      , "suffix"       , "data file suffix"                , &(s_place.j_suffix [0])     - (char*) &s_place,  0,  3,  6, LEN_LABEL         },
   { 'c' , "P_CONTENT"     , "content"      , "data file content description"   , &(s_place.j_content [0])    - (char*) &s_place,  0, 15, 30, LEN_TITLE         },
   {  1  , ""              , ""             , ""                                , NULL                                          ,  0,  0,  0, 0                 },
   /*-------chars-----------label------------description-------------------------pointer-----------------------------------------min-low-hig-max----------------*/
   { 's' , "P_SYSTEMS"     , "systems"      , "operating systems required"      , &(s_place.j_systems [0])    - (char*) &s_place, 40, 50, 70, LEN_HUND          },
   { 'l' , "P_LANGUAGE"    , "language"     , "computer programming language"   , &(s_place.j_language [0])   - (char*) &s_place, 40, 50, 70, LEN_HUND          },
   { 'c' , "P_COMPILER"    , "compiler"     , "specific compiler version"       , &(s_place.j_compiler [0])   - (char*) &s_place,  0,  3, 20, LEN_LABEL         },
   { 'z' , "P_CODESIZE"    , "codesize"     , "general size note"               , &(s_place.j_codesize [0])   - (char*) &s_place, 10, 30, 60, LEN_DESC          },
   {  1  , ""              , ""             , ""                                , NULL                                          ,  0,  0,  0, 0                 },
   /*-------depends---------label------------description-------------------------pointer-----------------------------------------min-low-hig-max----------------*/
   { 'D' , "P_DEPSTDC"     , "dep_stdc"     , "standard-c libraries"            , &(s_place.j_dep_cstd [0])   - (char*) &s_place,  0,  0, 70, LEN_HUND          },
   { 'P' , "P_DPEPOSIX"    , "dep_posix"    , "posix-c libraries"               , &(s_place.j_dep_posix [0])  - (char*) &s_place,  0,  0, 70, LEN_HUND          },
   { 'C' , "P_DPECORE"     , "dep_core"     , "heatherly cored libraries"       , &(s_place.j_dep_core [0])   - (char*) &s_place,  0,  0, 70, LEN_HUND          },
   { 'V' , "P_DPEVIKEY"    , "dep_vikey"    , "heatherly vi-keys libraries"     , &(s_place.j_dep_vikey [0])  - (char*) &s_place,  0,  0, 70, LEN_HUND          },
   { 'O' , "P_DPEOTHER"    , "dep_other"    , "all other libraries"             , &(s_place.j_dep_other [0])  - (char*) &s_place,  0,  0, 70, LEN_HUND          },
   { 'G' , "P_DPEGRAPH"    , "dep_graph"    , "heatherly visual libraries"      , &(s_place.j_dep_graph [0])  - (char*) &s_place,  0,  0, 70, LEN_HUND          },
   { 'S' , "P_DPESOLO"     , "dep_solo"     , "heatherly solo/uver libraries"   , &(s_place.j_dep_solo [0])   - (char*) &s_place,  0,  0, 70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , NULL                                          ,  0,  0,  0, 0                 },
   /*-------when------------label------------description-------------------------pointer-----------------------------------------min-low-hig-max----------------*/
   { 'a' , "P_AUTHOR"      , "author"       , "primary programmer name"         , &(s_place.j_author [0])     - (char*) &s_place,  5, 10, 40, LEN_TITLE         },
   { 'c' , "P_CREATED"     , "created"      , "data first created"              , &(s_place.j_created [0])    - (char*) &s_place,  4,  7, 20, LEN_LABEL         },
   {  1  , ""              , ""             , ""                                , NULL                                          ,  0,  0,  0, 0                 },
   /*-------version---------label------------description-------------------------pointer-----------------------------------------min-low-hig-max----------------*/
   { 'x' , "P_VERMAJOR"    , "vermajor"     , "major version explanation"       , &(s_place.j_vermajor [0])   - (char*) &s_place,  4, 15, 70, LEN_HUND          },
   { 'n' , "P_VERMINOR"    , "verminor"     , "minor version explanation"       , &(s_place.j_verminor [0])   - (char*) &s_place,  4, 15, 70, LEN_HUND          },
   { 'v' , "P_VERNUM"      , "vernum"       , "specific vertion number"         , &(s_place.j_vernum [0])     - (char*) &s_place,  4,  4,  4, LEN_LABEL         },
   { 't' , "P_VERTXT"      , "vertxt"       , "specific version description"    , &(s_place.j_vertxt [0])     - (char*) &s_place, 10, 20, 70, LEN_HUND          },
   {  1  , ""              , ""             , ""                                , NULL                                          ,  0,  0,  0, 0                 },
   /*-------end-------------label------------description-------------------------pointer-----------------------------------------min-low-hig-max----------------*/
   {  0  , "end-of-list"   , ""             , ""                                , NULL                                          ,  0,  0,  0,  0                },
};

/*>                                                                                                                <* 
 *> ##/usr/local/bin/polymnia --htags                                                                              <* 
 *> ##                                                                                                             <* 
 *> ##   polymnia-hymnos (many praises) greek muse and protector of divine hymns, dancing, geometry, and grammar   <* 
 *> ##   version 1.1i, prefixed elements of structures proj (j_), file (i_), and func (c_) for easier finding      <* 
 *> ##   htags reporting file for use with vim-ide                                                                 <* 
 *> ##                                                                                                             <* 
 *> ##   33 headers ·  [-.-.----.------.-.-----.----.-------.--.----]                                              <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   name       N  [polymnia]                                                                                  <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   focus      f  []                                                                                          <* 
 *> ##   niche      n  []                                                                                          <* 
 *> ##   subject    s  []                                                                                          <* 
 *> ##   purpose    p  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   namesake   ê  []                                                                                          <* 
 *> ##   pronounce  ÷  []                                                                                          <* 
 *> ##   heritage   î  []                                                                                          <* 
 *> ##   briefly    é  []                                                                                          <* 
 *> ##   imagery    ð  []                                                                                          <* 
 *> ##   reason     ø  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   one-line   ö  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   homedir    d  [/home/system/polymnia.muse_of_coding_structure]                                            <* 
 *> ##   basename   b  []                                                                                          <* 
 *> ##   fullpath   f  []                                                                                          <* 
 *> ##   suffix     s  []                                                                                          <* 
 *> ##   content    c  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   system     s  []                                                                                          <* 
 *> ##   language   l  []                                                                                          <* 
 *> ##   compiler   c  []                                                                                          <* 
 *> ##   code-size  z  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   dep_cstd   D  []                                                                                          <* 
 *> ##   dep_posix  P  []                                                                                          <* 
 *> ##   dep_core   C  []                                                                                          <* 
 *> ##   dep_vikey  V  []                                                                                          <* 
 *> ##   dep_other  O  []                                                                                          <* 
 *> ##   dep_graph  G  []                                                                                          <* 
 *> ##   dep_solo   S  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   author     a  []                                                                                          <* 
 *> ##   created    c  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
 *> ##                                                                                                             <* 
 *> ##   vermajor   x  []                                                                                          <* 
 *> ##   verminor   n  []                                                                                          <* 
 *> ##   vernum     v  []                                                                                          <* 
 *> ##   vertxt     t  []                                                                                          <* 
 *> ##                                                                                                             <* 
 *> ##   [···´····] ·  [····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´·····]          <* 
*> ##                                                                                                             <* 
*>                                                                                                                <*/

char
poly_header_clean       (tPROJ *a_proj)
{
   /*> for (i = 0; i < LEN_HUND; ++i) {                                               <* 
    *>    if (s_header                                                                <* 
    *> }                                                                              <*/
   /*---(master)-------------------*/
   strcpy (J_FOCUS       , "");
   strcpy (J_NICHE       , "");
   strcpy (J_SUBJECT     , "");
   strcpy (J_PURPOSE     , "");
   /*---(greek)--------------------*/
   strcpy (J_NAMESAKE    , "");
   strcpy (J_PRONOUNCE   , "");
   strcpy (J_HERITAGE    , "");
   strcpy (J_BRIEFLY     , "");
   strcpy (J_IMAGERY     , "");
   strcpy (J_REASON      , "");
   /*---(oneline)------------------*/
   strcpy (J_ONELINE     , "");
   /*---(location)-----------------*/
   strcpy (J_HOMEDIR     , "");
   strcpy (J_PROGNAME    , "");
   strcpy (J_FULLPATH    , "");
   strcpy (J_SUFFIX      , "");
   strcpy (J_CONTENT     , "");
   /*---(chars)--------------------*/
   strcpy (J_SYSTEMS     , "");
   strcpy (J_LANGUAGE    , "");
   strcpy (J_COMPILER    , "");
   strcpy (J_CODESIZE    , "");
   /*---(depends)------------------*/
   strcpy (J_DCSTD       , "");
   strcpy (J_DPOSIX      , "");
   strcpy (J_DCORE       , "");
   strcpy (J_DVIKEY      , "");
   strcpy (J_DOTHER      , "");
   strcpy (J_DGRAPH      , "");
   strcpy (J_DSOLO       , "");
   /*---(created)------------------*/
   strcpy (J_AUTHOR      , "");
   strcpy (J_CREATED     , "");
   /*---(version)------------------*/
   strcpy (J_VERMAJOR    , "");
   strcpy (J_VERMINOR    , "");
   strcpy (J_VERNUM      , "");
   strcpy (J_VERTXT      , "");
   /*---(complete)-----------------*/
   return 0;
}

char
poly_header__single     (tPROJ *a_proj, cchar a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *q           = NULL;
   char       *r           = NULL;
   char        x_data      [LEN_FULL]  = "";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_proj"    , a_proj);
   --rce;  if (a_proj == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_recd"    , a_recd);
   /*---(filter for macros)--------------*/
   if (strncmp (a_recd, "#define ",  8) != 0) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(filter for headers)-------------*/
   q = strstr (a_recd, " P_");
   DEBUG_INPT   yLOG_point   ("q"         , q);
   if (q == NULL) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(clip data payload)--------------*/
   ++q;
   DEBUG_INPT   yLOG_info    ("q"         , q);
   r = strchr (a_recd, '"');
   DEBUG_INPT   yLOG_point   ("r"         , r);
   if (r == NULL) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_INPT   yLOG_info    ("r"         , r);
   /*---(dequote)------------------------*/
   ystrlcpy (x_data, r, LEN_FULL);
   rc = ystrldequote (x_data, LEN_FULL);
   DEBUG_INPT   yLOG_value   ("unquote"   , rc);
   DEBUG_INPT   yLOG_info    ("x_data"    , x_data);
   /*---(master)-------------------*/
   if      (strncmp (q, "P_FOCUS     ", 12) == 0)  ystrlcpy (J_FOCUS       , x_data, LEN_DESC);
   else if (strncmp (q, "P_NICHE     ", 12) == 0)  ystrlcpy (J_NICHE       , x_data, LEN_DESC);
   else if (strncmp (q, "P_SUBJECT   ", 12) == 0)  ystrlcpy (J_SUBJECT     , x_data, LEN_DESC);
   else if (strncmp (q, "P_PURPOSE   ", 12) == 0)  ystrlcpy (J_PURPOSE     , x_data, LEN_HUND);
   /*---(greek)--------------------*/
   else if (strncmp (q, "P_NAMESAKE  ", 12) == 0)  ystrlcpy (J_NAMESAKE    , x_data, LEN_HUND);
   else if (strncmp (q, "P_PRONOUNCE ", 12) == 0)  ystrlcpy (J_PRONOUNCE   , x_data, LEN_TITLE);
   else if (strncmp (q, "P_HERITAGE  ", 12) == 0)  ystrlcpy (J_HERITAGE    , x_data, LEN_HUND);
   else if (strncmp (q, "P_BRIEFLY   ", 12) == 0)  ystrlcpy (J_BRIEFLY     , x_data, LEN_TITLE);
   else if (strncmp (q, "P_IMAGERY   ", 12) == 0)  ystrlcpy (J_IMAGERY     , x_data, LEN_HUND);
   else if (strncmp (q, "P_REASON    ", 12) == 0)  ystrlcpy (J_REASON      , x_data, LEN_HUND);
   /*---(oneline)------------------*/
   else if (strncmp (q, "P_ONELINE   ", 12) == 0)  sprintf  (J_ONELINE     , "%s %s", J_NAMESAKE, J_SUBJECT);
   /*---(location)-----------------*/
   else if (strncmp (q, "P_HOMEDIR   ", 12) == 0)  ystrlcpy (J_HOMEDIR     , x_data, LEN_TITLE);
   else if (strncmp (q, "P_BASENAME  ", 12) == 0)  ystrlcpy (J_PROGNAME    , x_data, LEN_TITLE);
   else if (strncmp (q, "P_FULLPATH  ", 12) == 0)  ystrlcpy (J_FULLPATH    , x_data, LEN_HUND);
   else if (strncmp (q, "P_SUFFIX    ", 12) == 0)  ystrlcpy (J_SUFFIX      , x_data, LEN_LABEL);
   else if (strncmp (q, "P_CONTENT   ", 12) == 0)  ystrlcpy (J_CONTENT     , x_data, LEN_TITLE);
   /*---(chars)--------------------*/
   else if (strncmp (q, "P_SYSTEM    ", 12) == 0)  ystrlcpy (J_SYSTEMS     , x_data, LEN_HUND);
   else if (strncmp (q, "P_LANGUAGE  ", 12) == 0)  ystrlcpy (J_LANGUAGE    , x_data, LEN_HUND);
   else if (strncmp (q, "P_COMPILER  ", 12) == 0)  ystrlcpy (J_COMPILER    , x_data, LEN_LABEL);
   else if (strncmp (q, "P_CODESIZE  ", 12) == 0)  ystrlcpy (J_CODESIZE    , x_data, LEN_DESC);
   /*---(depends)------------------*/
   else if (strncmp (q, "P_DEPSTDC   ", 12) == 0)  ystrlcpy (J_DCSTD       , x_data, LEN_HUND);
   else if (strncmp (q, "P_DEPPOSIX  ", 12) == 0)  ystrlcpy (J_DPOSIX      , x_data, LEN_HUND);
   else if (strncmp (q, "P_DEPCORE   ", 12) == 0)  ystrlcpy (J_DCORE       , x_data, LEN_HUND);
   else if (strncmp (q, "P_DEPVIKEY  ", 12) == 0)  ystrlcpy (J_DVIKEY      , x_data, LEN_HUND);
   else if (strncmp (q, "P_DEPOTHER  ", 12) == 0)  ystrlcpy (J_DOTHER      , x_data, LEN_HUND);
   else if (strncmp (q, "P_DEPGRAPH  ", 12) == 0)  ystrlcpy (J_DGRAPH      , x_data, LEN_HUND);
   else if (strncmp (q, "P_DEPSOLO   ", 12) == 0)  ystrlcpy (J_DSOLO       , x_data, LEN_HUND);
   /*---(created)------------------*/
   else if (strncmp (q, "P_AUTHOR    ", 12) == 0)  ystrlcpy (J_AUTHOR      , x_data, LEN_TITLE);
   else if (strncmp (q, "P_CREATED   ", 12) == 0)  ystrlcpy (J_CREATED     , x_data, LEN_LABEL);
   /*---(version)------------------*/
   else if (strncmp (q, "P_VERMAJOR  ", 12) == 0)  ystrlcpy (J_VERMAJOR    , x_data, LEN_HUND);
   else if (strncmp (q, "P_VERMINOR  ", 12) == 0)  ystrlcpy (J_VERMINOR    , x_data, LEN_HUND);
   else if (strncmp (q, "P_VERNUM    ", 12) == 0)  ystrlcpy (J_VERNUM      , x_data, LEN_LABEL);
   else if (strncmp (q, "P_VERTXT    ", 12) == 0)  ystrlcpy (J_VERTXT      , x_data, LEN_HUND);
   /*---(not found)----------------------*/
   else {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exitr   (__FUNCTION__, 1);
   return 1;
}

char
poly_header_read        (tFILE *a_file)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_type      =  '·';
   char        x_curr      [LEN_RECD]  = "";
   char        x_prev      [LEN_RECD]  = "";
   int         x_line      =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("a_file"    , a_file);
   --rce;  if (a_file == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return  rce;
   }
   /*---(quick-out)----------------------*/
   x_type = a_file->i_type;
   DEBUG_INPT   yLOG_char    ("x_type"    , x_type);
   if (x_type != 'h') {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(open file)----------------------*/
   DEBUG_INPT   yLOG_info    ("i_name"    , a_file->i_name);
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
      rc = poly_header__single  (a_file->i_proj, x_curr);
      DEBUG_INPT   yLOG_value   ("oneliner"  , rc);
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
   return 1;
}

char
poly_header__encode     (char *a_header, char n, char a_abbr, char *a_text, char a_min, char a_low, char a_high, char a_max)
{
   char        rce         =  -10;
   int         x_len       =    0;
   --rce;  if (a_header == NULL)  return rce;
   --rce;  if (a_text   == NULL)  return rce;
   x_len = strlen (a_text);
   if      (x_len == 3 && strcmp (a_text, "n/a" ) == 0)  a_header [n] = '´';
   else if (x_len == 4 && strcmp (a_text, "none") == 0)  a_header [n] = '´';
   else if (x_len     == 0)       a_header [n] = '·';
   else if (x_len     <  a_min)   a_header [n] = '?';
   else if (x_len     <  a_low)   a_header [n] = '!';
   else if (x_len - 1 >= a_max)   a_header [n] = '#';
   else if (x_len     >  a_high)  a_header [n] = '!';
   else                           a_header [n] = a_abbr;
   return 0;
}

/*
 *   _.n.fnsp.gphbir.o.dbfsc.slczd.ac,xnvt._
 */

char
poly_header_summarize   (tPROJ *a_proj)
{
   /*---(base)---------------------------*/
   poly_header__encode (J_HEADER,  2, 'N', J_NAME        ,  1,  4, 15, LEN_TITLE);
   /*---(master)-------------------------*/
   poly_header__encode (J_HEADER,  4, 'f', J_FOCUS       ,  5, 10, 30, LEN_DESC);
   poly_header__encode (J_HEADER,  5, 'n', J_NICHE       ,  5, 10, 30, LEN_DESC);
   poly_header__encode (J_HEADER,  6, 's', J_SUBJECT     , 10, 20, 30, LEN_DESC);
   poly_header__encode (J_HEADER,  7, 'p', J_PURPOSE     , 30, 50, 70, LEN_HUND);
   /*---(greek)-------------*/
   poly_header__encode (J_HEADER,  9, 'ê', J_NAMESAKE    , 10, 20, 40, LEN_HUND);
   poly_header__encode (J_HEADER, 10, '÷', J_PRONOUNCE   ,  0,  5, 30, LEN_TITLE);
   poly_header__encode (J_HEADER, 11, 'î', J_HERITAGE    , 40, 40, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 12, 'é', J_BRIEFLY     ,  0, 20, 30, LEN_TITLE);
   poly_header__encode (J_HEADER, 13, 'ð', J_IMAGERY     , 40, 40, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 14, 'ø', J_REASON      , 40, 40, 70, LEN_HUND);
   /*---(oneline)-----------*/
   poly_header__encode (J_HEADER, 16, 'ö', J_ONELINE     , 40, 50, 70, LEN_HUND);
   /*---(location)----------*/
   poly_header__encode (J_HEADER, 18, 'd', J_HOMEDIR     ,  1,  4, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 19, 'b', J_PROGNAME    ,  1,  4, 20, LEN_TITLE);
   poly_header__encode (J_HEADER, 20, 'f', J_FULLPATH    , 10, 20, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 21, 's', J_SUFFIX      ,  0,  3,  6, LEN_LABEL);
   poly_header__encode (J_HEADER, 22, 'c', J_CONTENT     ,  0, 15, 30, LEN_TITLE);
   /*---(chars)-------------*/
   poly_header__encode (J_HEADER, 24, 's', J_SYSTEMS     , 40, 50, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 25, 'l', J_LANGUAGE    , 40, 50, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 26, 'c', J_COMPILER    ,  0,  3, 20, LEN_LABEL);
   poly_header__encode (J_HEADER, 27, 'z', J_CODESIZE    , 10, 30, 60, LEN_DESC);
   /*---(depends)-----------*/
   poly_header__encode (J_HEADER, 29, 'D', J_DCSTD       ,  0,  0, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 30, 'P', J_DPOSIX      ,  0,  0, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 31, 'C', J_DCORE       ,  0,  0, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 32, 'V', J_DVIKEY      ,  0,  0, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 33, 'O', J_DOTHER      ,  0,  0, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 34, 'G', J_DGRAPH      ,  0,  0, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 35, 'S', J_DSOLO       ,  0,  0, 70, LEN_HUND);
   /*---(when)--------------*/
   poly_header__encode (J_HEADER, 37, 'a', J_AUTHOR      ,  5, 10, 40, LEN_TITLE);
   poly_header__encode (J_HEADER, 38, 'c', J_CREATED     ,  4,  7, 20, LEN_LABEL);
   /*---(versioning)--------*/
   poly_header__encode (J_HEADER, 40, 'x', J_VERMAJOR    ,  4, 15, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 41, 'n', J_VERMINOR    ,  4, 15, 70, LEN_HUND);
   poly_header__encode (J_HEADER, 42, 'v', J_VERNUM      ,  4,  4,  4, LEN_LABEL);
   poly_header__encode (J_HEADER, 43, 't', J_VERTXT      , 10, 20, 70, LEN_HUND);
   /*---(overall)-----------*/
   J_HEADER [0] = '-';
   if      (strchr (J_HEADER, '·') != NULL)  J_HEADER [0] = '#';
   else if (strchr (J_HEADER, '#') != NULL)  J_HEADER [0] = '!';
   /*---(complete)----------*/
   return 0;
}

char
poly_header_htags                (tPROJ *a_proj)
{
}

char
poly_header_quick       (void)
{
   int         i           =    0;
   char        t           [LEN_HUND]  = "";
   char       *x_sep       = "\n##  ---label-- -  ····´····+····´····+····´····+····´····+····´····+····´····+····´····+····´·····  --  ----name---- --ptr --min --low --hig --max  ---description----------------\n\n";
   printf (x_sep);
   for (i = 0; i < LEN_HUND; ++i) {
      if (s_header [i].h_abbr == 0)  break;
      if (s_header [i].h_abbr == 1) {
         printf (x_sep);
         continue;
      }
      printf ("##  %-10.10s %c                                                                                    %2d  %-12.12s  %4d  %3dn  %3dl  %3dh  %3dx  %s\n", s_header [i].h_label, s_header [i].h_abbr, i, s_header [i].h_name, s_header [i].h_point, s_header [i].h_min, s_header [i].h_low, s_header [i].h_high, s_header [i].h_max, s_header [i].h_desc);
   }
   exit(0);
}



